/*
Reference: " https://www.geeksforgeeks.org/making-linux-shell-c/ "
To implement a simple shell or command line interpreter
BlazerID: aniketb
Name: Aniket Ashok Bagitkar
To compile: gcc -o uab_sh shell.c -lreadline
To run:./uab_sh
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

int argCount;
char curr_dir[4096];

int getLength(char *buffer)
{
	printf("length is %s",strlen(buffer));
	return(strlen(buffer));
}
char newLine(char buffer[1010])
{
	buffer = strtok(buffer,"\n");
	strcat(buffer,"\n");
	return buffer;
}					

void append_history(char buffer[1000]){
	char file_path[5010];
	strcpy(file_path,curr_dir);
	strcat(file_path,"/uab_sh.log");
	int filedes = open(file_path, O_APPEND | O_CREAT | O_WRONLY, 0755);
	newLine(buffer);
	// for the new line
	buffer = strtok(buffer,"\n");
	strcat(buffer,"\n");
	write(filedes,buffer,strlen(buffer)); 
} 

// processing the input from the user
int send_input(char* str)
{
	printf("\nuab_sh > ");
    char buffer[1080], buf[1000];
    if(fgets(buffer, 1000, stdin) != NULL){
		int len =0;
        if(strlen(&buffer)!=0) {
            append_history(buffer);
            strcpy(str, buffer);
            return 0;
        } else {
            return 1;
        }
    }	
}    
// method to process and  the system commands 
void execStrings(char** parsed)
{
	// Forking a child
	pid_t pid = fork();

	if (pid == -1) {
		printf("\nFailed forking child..");
		return;
	} else if (pid == 0) {
		if (execvp(parsed[0], parsed) < 0) {
			printf("\nCould not execute command..");
		}
		exit(0);
	} else {
		// waiting for child to terminate
		wait(NULL);
		return;
	}
}

// method to implement pipe string commands
void exStringPiped(char** parsed, char** parsedpipe)
{
	int pipeFiledes[2];
	pid_t pipe1;
	pid_t pipe2;

	if (pipe(pipeFiledes) < 0) {
		printf("\nUnable to initilize pipe");
		return;
	}
	pipe1 = fork();
	if (pipe1 < 0) {
		printf("\nfork not done");
		return;
	}

	if (pipe1 == 0) 
	{
		close(pipeFiledes[0]);
		dup2(pipeFiledes[1], STDOUT_FILENO);
		close(pipeFiledes[1]);
		if (execvp(parsed[0],parsed)<0) 
		{
			printf("\ncommand not executed");
			exit(EXIT_FAILURE);
		}
	} 
	else 
	{
		pipe2 = fork();
		if (pipe2 < 0) {
			printf("\nCould not fork");
			return;
		}
		if (pipe2 == 0) {
			close(pipeFiledes[1]);
			dup2(pipeFiledes[0], STDIN_FILENO);
			close(pipeFiledes[0]);
			if (execvp(parsedpipe[0], parsedpipe) < 0) {
				printf("\nCould not execute command 2..");
			    exit(EXIT_FAILURE);
			}
		} else {
			wait(NULL);
			wait(NULL);
		}
	}
}

// This method implements user with help command 
void helpMethod()
{
	printf("\n*Welcome to Help Desk*");
	printf("\nCommands List");
	printf("\n>cd");
	printf("\n>ls");
	printf("\n>exit");
	printf("\n>General commands in Unix");
	printf("\n>pipes handling");
	printf("\n>invalid space handling");
	return;
}

// function for finding pipe
int parsePipe(char* str, char** strpiped)
{
	int i;
	for (i = 0; i < 2; i++) {
		strpiped[i] = strsep(&str, "|");
		if (strpiped[i] == NULL)
			break;
	}

	if (strpiped[1] == NULL)
		return 0; // returns zero if no pipe is found.
	else {
		return 1;
	}
}

// method to implement parsing 
void parseSpace(char* str, char** parsed_p)
{
	int j=0;
	while(j<100){
	parsed_p[j] = strsep(&str, " ");

		if (parsed_p[j] == NULL){
			break;
        }
		if (strlen(parsed_p[j]) == 0)
			j--;
		j++;
	}
    argCount = j;
    parsed_p[j-1] = strtok(parsed_p[j-1],"\n");
}

void printFirstSecond(int first, int second)
{
	 printf("%d, %d, ", first, second); 
}
void printFib(int first, int second, int third, int n, int i){
	for (i=3; i<=n; ++i) {
			printf("%d, ", third);
			first = second;
			second = third;
			third = first + second;
		}
}
// fibonacci implementation
void fibonacci(int n)
{
    int first = 0;
	int second = 1;
	int third = first + second;
	int i;
    
	printFirstSecond(first, second);
	printFib(first, second, third, n, i);
    
} 
            
// method used to implement all the pre existing commands
int selfCommandExec(char** parsed)
{
	int n = 7, changecmd = 0;
	char* list[n];
	char* username;

	list[0] = "quit";
	list[1] = "cd";
	list[2] = "help";
	list[3] = "hello";
	list[4] = "fibonacci";
	list[5] = "list";
	list[6] = "history";

	int i=0;
	while(i<n){
	if (strcmp(parsed[0], list[i]) == 0) {
			changecmd = i + 1;
			break;
		}
	i++;
	}

    int number;
	char *arr[5] = {"ls",NULL};

	char file_path[5111];
	strcpy(file_path,curr_dir);
	strcat(file_path,"/uab_sh.log");

	char *historyArr[10] = {"cat",file_path,NULL};

	switch (changecmd) {
	case 1:
		printf("\nExited Shelln");
		exit(0);
	case 2:
		chdir(parsed[1]);
		return 1;
	case 3:
		helpMethod();
		return 1;
	case 4:
		printf("\n Hello World");
		return 1;
	case 5:
        if(argCount>1){
		    number = atoi(parsed[1]);
        }
        else{
            printf("Enter upto what number you need fibonacci series: ");
            scanf("%d",&number);
        }
        fibonacci(number);
		return 1;
	case 6:
		execStrings(arr);
		return 1;
	case 7:
		execStrings(historyArr);
		return 1;
	default:
		break;
	}
	return 0;
}

int modifyStream(char* string, char** modified, char** modifiedpipe, int y)
{
	// implementatiom of pipe to process the string

	char* strpiped[2];
	int x=3;
	int pipe_done = x-y;
	pipe_done = parsePipe(string, modifiedpipe);
	
	if (pipe_done) {
		parseSpace(strpiped[0], modified);
		parseSpace(strpiped[1], modifiedpipe);
	}
	else
	parseSpace(string, modified);

	if (selfCommandExec(modified))
		return 0;
	else
		return 1 + pipe_done;
}

int main()
{
	char stream[1000], *parsedStrings[100];
	char* parsedStringsPiped[100];
	int runTemp = 0;  
	getcwd(curr_dir, 4096); // to get the path name of the working directory
	int temporary;
	for(;;) { 
		// print shell line
		char path[1200];
		getcwd(path, sizeof(path));
		printf("\nCurrent Directory is : %s", path);

		// taking the input
		if (send_input(stream)){
			temporary= 0;	
			continue;
		}  
		// execution
		runTemp = modifyStream(stream, parsedStrings, parsedStringsPiped, 3);
		// runTemp would run depending on the input, say if 0 then it is said to be no command or a prebuild command, 1 if a simple command and 2 for pipe


			switch(runTemp)
			{
			case 1:
			execStrings(parsedStrings);
			case 2:
			exStringPiped(parsedStrings, parsedStringsPiped);
		    }
	}
	return 0;
}
