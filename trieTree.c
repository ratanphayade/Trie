#include <stdio.h>
#include "hashtable.h"

#define MAX 10

typedef struct node *nodeptr;
typedef int (*funcdef)(int, char*, nodeptr*);

char word[MAX];
static int count = 0;
int i = 0;

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
	cid = toascii(data[index]);//data[index] - '0';
	HASH_FIND_INT(*nptr, &cid, dp);
	if(dp)
		if(data[index+1]=='\0'){
			dp->iscomplete = 1;
			return 0;
		} else
			return add_data(index+1, data, &dp->ptr);
    dp = get_node(cid, data, index);
	HASH_ADD_INT(*nptr, id, dp);
	return 1 + add_data(index+1, data, &dp->ptr);
}

int search_data(int index, char *data, nodeptr *nptr){
	int cid = toascii(data[index]);//data[index] - '0';
	nodeptr dp;
	if(data[index]){
		HASH_FIND_INT(*nptr, &cid, dp);
		return (data[index+1]=='\0' && dp->iscomplete)? 1 : search_data(index+1, data, &dp->ptr);
	} else
		return 0;
}

int dfs_print(int length, char *data, nodeptr *nptr){
    nodeptr dp;
    if(!length)
        return 0;
    for(dp=*nptr; dp != NULL; dp=(nodeptr)(dp->hh.next)){
        word[i++] = dp->data;
        if(dp->iscomplete){
            word[i]='\0';
            printf("\n%s",word);
            ++count;
        }
        dfs_print(length-1,"",&dp->ptr);
        --i;
    }
    return count;
}

void print_data(funcdef function, char *stmt){
	int length;
	count = 0;
	printf("\nEnter the max String length to print (For no limit enter -1) : ");
	scanf("%d",&length);
	printf("\n%s : %d \n",stmt,(*function)(length, "", &root));
}

void add_string(funcdef function, char *stmt){
	char data[MAX];
	printf("Enter the String : ");
	scanf("%s",data);
	printf("\n%s : %d \n",stmt ,(*function)(0, data, &root));
}

int main(){
	int ch;
	do{
		printf("\n1. Add String Value");
		printf("\n2. Search String");
		printf("\n3. Print Data");
		printf("\nChoice?");
		scanf("%d",&ch);
		switch(ch){
			case 1 : add_string(&add_data, "Number of Node(s) Created");
				 break;
			case 2 : add_string(&search_data, "Search Status");
				 break;
			case 3 : print_data(&dfs_print, "Total number of records fetched");
				 break;
		}
	}while(ch<4);
	return 0;
}
