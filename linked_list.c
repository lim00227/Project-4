#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pthread.h"
#include "linked_list.h"
char buffer[256];
// initialize head
node *head = NULL;

// sequence counter
int seq_ctr = 0;
// current node
node *cur = NULL;
// line counter
line_ctr = 0;
//Read the file on a line by line basis
char* read_line(char* fname, int line_no) 
{
	FILE *fp = fopen(fname, "r");
	while(fgets(buffer, sizeof(buffer), fp) != NULL) {
		if (line_ctr == line_no) {
			return buffer;
		}
		line_ctr++;
	}
	fclose(fp);
} 

//traverse the linked list
void traversal(node *head)
{
	while(head != NULL) {
		fprintf("%d, %d, %d", seq_no, line_no, content);
		head = head->next;
	}
}

// insert the node into the linked list
void insert(node **phead, node *newnode)
{
	while(phead != NULL) {
		if(phead->next == NULL) {
			phead->next = newnode;
		}
		phead = phead->next;
}

//create a new node structure
node* create_node(int line_no, char *line)
{
	node new;
	new->line_no = line_no;
	new->content = line;
	new->seq_no = seq_ctr;
}
