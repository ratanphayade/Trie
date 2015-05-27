#include <stdio.h>
#include "hashtable.h"

typedef struct node *nodeptr;
typedef int (*funcdef)(int, char*, nodeptr*);

struct node {
	int iscomplete;
	int id;
	char data;
	nodeptr ptr;
	UT_hash_handle hh;
};

nodeptr root = NULL;

nodeptr get_node(int id, char *data, int index){
        nodeptr dp = (nodeptr)malloc(sizeof(struct node));
	dp->id = id;
	dp->data = data[index];
	dp->ptr = NULL;
	dp->iscomplete = (data[index+1]=='\0')? 1 : 0;
	return dp;
}

int add_data(int index, char *data, nodeptr *nptr){
	nodeptr dp;
	int cid;
	if(data[index]=='\0')
		return 0;
	cid = data[index] - '0';
	HASH_FIND_INT(*nptr, &cid, dp);
	if(dp)
		if(data[index+1]=='\0'){
			dp->iscomplete = 1;
			return 0;
		}
		else
			return add_data(index+1, data, &dp->ptr);
    	dp = get_node(cid, data, index);
	HASH_ADD_INT(*nptr, id, dp);
	return 1 + add_data(index+1, data, &dp->ptr);
}

int search_data(int index, char *data, nodeptr *nptr){
	int cid = data[index] - '0';
	nodeptr dp;
	if(data[index]){
		HASH_FIND_INT(*nptr, &cid, dp);
		return (data[index+1]=='\0' && dp->iscomplete)? 1 : search_data(index+1, data, &dp->ptr);
	} else
		return 0;
}

void print_data(){
    nodeptr dp;
    if(root == NULL)
    	printf("No Data Available");
    for(dp=root; dp != NULL; dp=(nodeptr)(dp->hh.next)) 
        printf("id %d: name %c\n", dp->id, dp->data);
}


void add_string(funcdef function, char *stmt){
	char data[10];
	printf("Enter the String : ");
	scanf("%s",data);
	printf("\n%s : %d \n",stmt ,(*function)(0, data, &root));
}


int main(){
	int ch;
	do{
		printf("\n1. Add String Value");
		printf("\n2. Search String");
		printf("\nChoice?");
		scanf("%d",&ch);
		switch(ch){
			case 1 : add_string(&add_data, "Number of Node(s) Created");
				 break;
			case 2 : add_string(&search_data, "");
				 break;
			case 3 : print_data();
				 break;
		}
	}while(ch<3);
	return 0;
}
