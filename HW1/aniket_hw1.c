/*

Name: Aniket Ashok Bagaitkar
BlazerID: aniketb
To compile: gcc -o aniket_hw1 aniket_hw1.c
To run: ./aniket_hw1 <keywords>
Replace keywords with string you want and replace file with your file.

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct words_count { // This structure is declared to store the keyword and count of each keyword in the text from the standard input
    char *key;
    int count;
};

int main(int argc, char *argv[]) { 
    int word_count = argc;
    // an array of structure pointer to store the keyword and its corresponding count 
    // used dynamic allocation to store 
    struct words_count *keywords_list = malloc(sizeof(struct words_count)*word_count);     
    for (int i=0; i<word_count-1; i++) { 
        int tmp = i;
         keywords_list[i].count=0;
        keywords_list[i].key = argv[tmp+1];
    }   
    char *line = NULL;  
    size_t maxlen=0; ssize_t n;    
    while ((n = getline(&line, &maxlen, stdin)) > 0) { // getLine method to read the entire line at a time.  
        char *token;
        token = strtok(line, " ");
        while (token != NULL) {
            for (int j=0; j<word_count-1; j++) {
                // checking for a new line - by using strstr method to check substring, if found it will be replaced by null character
                if (strstr(token, "\n"))
                    token[strlen(token) - 1] = '\0';  
                // if the token is found in the file or list of words, then the count is incremented
                if (strcmp(token, keywords_list[j].key) == 0)
                    keywords_list[j].count++;
            }
            token = strtok(NULL, " ");
        }
    } 
    int index = 0;
    while(index<word_count-1){
        printf("word %s has frequency %d\n", keywords_list[index].key, keywords_list[index].count);
        index++;
    }
    free(keywords_list);
}
