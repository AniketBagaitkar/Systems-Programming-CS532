/* Purpose: To read input string through command line arguments and create a table with keywords and count.
To Compile: gcc temp.c -o temp
To run: ./a.out "*Keywords*"< inputfile.txt*/

#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ISEMPTY printf("\nEMPTY LIST:");

struct node
{
    char *Keyword;
    int count;
    struct node *next;
};

typedef struct node fnode;
fnode *newnode, *ptr, *prev, *temp;
fnode *first = NULL, *last = NULL;
fnode* create_node(char*);
void insert_node(char*);
void update_val(char*);
void compare(char* );
void display();

void display(){
        for (ptr = first;ptr != NULL;ptr = ptr->next)
        {    
            printf("%s\t%d\n", ptr->Keyword,ptr->count);
        }
}
void compare(char* check){
    char *token1 = strtok(check, " ");
    while(token1) {
        printf("%s\n",token1);
        for (ptr = first;ptr !=NULL;ptr=ptr->next){
            if(ptr->Keyword==token1){
                ptr->count=ptr->count+1;
                printf("%s",token1);
            }
        }
        token1 = strtok(NULL, " ");    
    }
}
void update_val(char* update){
    for (ptr = first;ptr != NULL;ptr = ptr->next)
        {
            if (ptr->Keyword == update)
            {
                ptr->count = ptr->count++;
            }
        }
}
fnode* create_node(char* Key)
{
    newnode = (fnode *)malloc(sizeof(fnode));
    if (newnode == NULL)
    {
        printf("\nMemory was not allocated");
        return 0;
    }
    else
    {
        newnode->count=0;
        newnode->Keyword = Key;
        newnode->next = NULL;
        return newnode;
    }
}
void insert_node(char* Key)
{
    newnode = create_node(Key);
    if (first == last && last == NULL)
    {
        first = last = newnode;
        first->next = NULL;
        last->next = NULL;
    }
    else
    {
        last->next = newnode;
        last = newnode;
        last->next = NULL;
    }
}
int main(int argc, char *argv[])
{
    char *input = argv[1];
    char a[2000];
    printf("Enter the string");
    gets(a);
    puts(a);
    printf("Parsing the input string '%s'\n", input);
    char *token = strtok(input, " ");
    while(token) {
        insert_node(token);
        token = strtok(NULL, " ");
    }
    char *token1 = strtok(a, " ");
    while(token1) {
        for (ptr = first;ptr !=NULL;ptr=ptr->next){
            if(strcmp(ptr->Keyword,token1)){
                ptr->count=ptr->count+1;
            }
        }
        token1 = strtok(NULL, " ");    
    }
    //compare(a);
    display();
}