/* 
Blazer ID: aniketb 
Name : Aniket Ashok Bagaitkar
To compile:gcc -o homework4 homework4.c
To Run: ./homework4 3

*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<fcntl.h>
#include "queue.h"
#define WAITING 0
#define RUNNING 1
#define STOPPED 2
                  
struct jobScheduler{
    int jobid;
    char *command[100];
    int status;
};       

int curr_jobs =0;
char **jobsHistory;
void *function1(void **arg)
{ 
    struct jobScheduler **scheduler = (struct jobScheduler**) arg;
     
}  
         
void function2(struct jobScheduler **scheduler, int P)
{
    for(int i=0;i<sizeof(scheduler)/sizeof(scheduler);i++)
    {
        // printf("%s\n", scheduler[i]->command[0]);
        // printf("%d\n", scheduler[i]->jobid);

         int pid = fork();  
         char * outputfile = malloc(6);   
         sprintf(outputfile, "%d.out", pid);
     char * errorfile = malloc(6);   
     sprintf(errorfile, "%d.err", pid);
       int fd = open(outputfile, O_WRONLY| O_CREAT, 0755);
       int fd1 = open(errorfile, O_WRONLY| O_CREAT, 0755);

        dup2(fd, 1);
        dup2(fd1, 2);
        int status;
        if(pid==0) {
            scheduler[i]->status = RUNNING;
            execvp(scheduler[i]->command[i], scheduler[i]->command); 
            exit(-1);
        }         
        else if(pid>0){
            wait(&status); /* wait for the child process to terminate */   
            scheduler[i]->status = STOPPED;
            WIFEXITED(status);   
        }                         
    } 
}           
            
int main(int argc, char *argv[])
{

    int P = atoi(argv[1]);
    struct jobScheduler **scheduler = malloc(1000 * sizeof(struct jobScheduler));
    
    int jobid = 0;
    pthread_t thread_id1; 
    
    // pthread_create(&thread_id1, NULL, function1, (void**) &scheduler);
    
    // pthread_join(thread_id1, NULL);
                                
    int index=0;
    while(1){ 
        printf("Enter command>"); 
        char *line = NULL;
        size_t maxlen = 0;
        ssize_t n; 
        n = getline(&line, &maxlen, stdin);
        char *first=malloc(100);
        first = strtok(line, " ");

         if(strcmp(first, "submit")==0)
         {
            struct jobScheduler *temp = malloc(1*sizeof(struct jobScheduler)); 
            temp->jobid = jobid;    
            int count=0,j=0;   
            while(first!=NULL)
            {  
                count++;
               if(count>1)
               {
                temp->command[j] = first;
                j++;  
               } 
                temp->status = WAITING;
                first = strtok(NULL, " ");
            }     
           jobid++;
           temp->command[j-1] = strtok(temp->command[j-1],"\n");  
           temp->command[j] =  NULL;
           scheduler[index++] = temp;
           function2(scheduler, P);
           pthread_create(&thread_id1, NULL, function1, temp);
         } 
        else if(strcmp(first,"showjobs")==0)
        {
            
        }
        else if(strcmp(first,"submithistory")==0)
        {
                
        }     
    }
    
    return 0;
}


/* create the queue data structure and initialize it */
queue *queue_init(int n) {
	queue *q = (queue *)malloc(sizeof(queue));
	q->size = n;
	q->buffer = malloc(sizeof(int)*n);
	q->start = 0;
	q->end = 0;
	q->count = 0;

	return q;
}

/* insert an item into the queue, update the pointers and count, and
   return the no. of items in the queue (-1 if queue is null or full) */
int queue_insert(queue *q, int item) {
	if ((q == NULL) || (q->count == q->size))
	   return -1;

	q->buffer[q->end % q->size] = item;	
	q->end = (q->end + 1) % q->size;
	q->count++;

	return q->count;
}

/* delete an item from the queue, update the pointers and count, and 
   return the item deleted (-1 if queue is null or empty) */
int queue_delete(queue *q) {
	if ((q == NULL) || (q->count == 0))
	   return -1;

	int x = q->buffer[q->start];
	q->start = (q->start + 1) % q->size;
	q->count--;

	return x;
}

/* display the contents of the queue data structure */
void queue_display(queue *q) {
	int i;
	if (q != NULL && q->count != 0) {
		printf("queue has %d elements, start = %d, end = %d\n", 
			q->count, q->start, q->end);
		printf("queue contents: ");
		for (i = 0; i < q->count; i++)
	    		printf("%d ", q->buffer[(q->start + i) % q->size]);
		printf("\n");
	} else
		printf("queue empty, nothing to display\n");
}

/* delete the queue data structure */
void queue_destroy(queue *q) {
	free(q->buffer);
	free(q);
}

//  pthread_t thread_id1; 
//             pthread_create(&thread_id1, NULL, function1, NULL);
//             pthread_join(thread_id1, NULL);
// pthread_t thread_id2;
//             pthread_create(&thread_id2, NULL, function2, NULL);
//             pthread_join(thread_id2, NULL);

// char *first, *second;
            // 
            
    //         for(int i=0;i<2;i++)
    // {
    //     printf("jobid %d  status %d", scheduler[i].jobid, scheduler[i].status); 
    // }