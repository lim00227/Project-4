#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"

//global line-number counter to be sync'ed.
int line_ctr = 0;

//initialization of mutex locks
pthread_mutex_t line_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t seq_lock = PTHREAD_MUTEX_INITIALIZER;
//at least two mutex locks should be used

//start of the threads
void* process_file(void *param)
{
	char *filename = (char*)param;

	while (1) {
		// get unqiue line number
		pthread_mutex_lock(&line_lock);
		int my_line = line_ctr++;
		pthread_mutex_unlock(&line_lock);

		char *line = read_line(filename, my_line);
		if (line == NULL) {
			break;
		}

		// create new node
		node *newnode = create_node(my_line, line);

		// assign sequence number safely
		pthread_mutex_lock(&seq_lock);
		newnode->seq_no = seq_ctr++;
		pthread_mutex_unlock(&seq_lock);

		// insert safely
		pthread_mutex_lock(&list_lock);
		insert(&head, newnode);
		pthread_mutex_unlock(&list_lock);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	FILE* in_ptr;
	int threads;
	char *filename = NULL;

	if (argc != 3) {
		printf("Incorrect arg count. Enter file name and thread count\n");
		exit(EXIT_FAILURE);
	}

	filename = argv[1]; // added line
	threads = atoi(argv[2]);
	if (threads < 1 || threads > 16) {
		printf("Incorrect number of threads. Enter between 1 and 16\n");
		exit(EXIT_FAILURE);
	}

	// create threads
	pthread_t tid[threads];
	for (int i = 0; i < threads; i++) {
		if (pthread_create(&tid[i], NULL, process_file, filename) != 0) {
			perror("pthread_create failed");
			exit(EXIT_FAILURE);
		}
	}

	// join threads
	for (int i = 0; i < threads; i++) {
		if (pthread_join(tid[i], NULL) != 0) {
			perror("pthread_join failed");
			exit(EXIT_FAILURE);
		}
	}
	
	// safe + single-threaded traversal 
	traversal(head);

	return 0;
}
