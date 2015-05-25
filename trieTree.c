#include <stdio.h>
#include "hashtable.h"

typedef struct node *nodeptr;

struct node {
	int iscomplete;
	int id;
	char *data;
	nodeptr ptr;
	UT_hash_handle hh;
};

nodeptr root = NULL;

nodeptr get_node(int id, char *data, int index){
    nodeptr dp = (nodeptr)malloc(sizeof(struct node));
	dp->id = id;
	dp->data = (char*)malloc(sizeof(char)+index+1);
	strncpy(dp->data,data,index);
	dp->ptr = NULL;
	dp->iscomplete = (data[index+1=='\0'])? 1 : 0;
	return dp;
}

int add_data(int index, char *data, nodeptr *nptr){
	nodeptr dp;
	int cid;
	if(data[index]=='\0')
		return 0;
	cid = data[index] - '0';
	HASH_FIND_INT(*nptr, &cid, dp);
	if(dp != NULL)
		return add_data(index+1, data, &dp->ptr);
    dp = get_node(cid, data, index);
	HASH_ADD_INT(*nptr, id, dp);
	printf("\n %d \n",cid);
	return 1 + add_data(index+1, data, &dp->ptr);
}

void print_data(){
    nodeptr dp;
    if(root == NULL)
    	printf("No Data Available");
    for(dp=root; dp != NULL; dp=(nodeptr)(dp->hh.next)) {
        printf("id %d: name %c\n", dp->id, dp->data);
    }
}


void add_string(){
	char data[10];
	printf("Enter the String : ");
	scanf("%s",data);
	printf("\n\n *%d* ",add_data(0, data, &root));
}


int main(){
	int ch;
	do{
		printf("1. Add String Value");
		printf("\nChoice?");
		scanf("%d",&ch);
		switch(ch){
			case 1 : add_string();
				 break;
			case 2 : print_data();
				 break;
		}
	}while(ch<3);
	return 0;
}
