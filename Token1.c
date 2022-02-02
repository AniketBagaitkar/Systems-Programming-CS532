/* Purpose: To read input string through command line arguments and create a table with keywords and count.
To Compile: gcc Token1.c -o Token1
To run: ./Token1 "*Keywords*"< inputfile.txt*/

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
fnode *newnode, *abc, *xyz, *temp;
fnode *first = NULL, *last = NULL;
fnode* create_node(char*);
void insert_node(char*);
void update_val(char*);
void compare(char* );
void display();

void display(){
        for (abc = first;abc != NULL;abc = abc->next)
        {    
            printf("%s\t%d\n", abc->Keyword,abc->count);
        }
}
void compare(char* check){
    char *token1 = strtok(check, " ");
    while(token1) {
        printf("%s\n",token1);
        for (abc = first;abc !=NULL;abc=abc->next){
            if(abc->Keyword==token1){
                abc->count=abc->count+1;
                printf("%s",token1);
            }
        }
        token1 = strtok(NULL, " ");    
    }
}
void update_val(char* update){
    for (abc = first;abc != NULL;abc = abc->next)
        {
            if (abc->Keyword == update)
            {
                abc->count = abc->count++;
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
    fgets(a,2000,stdin);
    puts(a);
    printf("Parsing the input string '%s'\n", input);
    char *token = strtok(input, " ");
    while(token) {
        insert_node(token);
        token = strtok(NULL, " ");
    }
    char *token1 = strtok(a, " ");
    while(token1) {
        for (abc = first;abc !=NULL;abc=abc->next){
            if(strcmp(abc->Keyword,token1)){
                abc->count=abc->count+1;
            }
        }
        token1 = strtok(NULL, " ");    
    }
    //compare(a);
    display();
}