/*
Name: Aniket Ashok Bagaitkar
BlazerID: aniketb
To compile: gcc readdir.c -o readdir
To Execute: ./readdir <filepath>
*/
#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include <getopt.h>

void recursMethod(char *argv)
{
  struct dirent *dirent; 
  char path[1000]; 
  DIR *parentDir= opendir (argv); 
  
  if (parentDir == NULL) { 
    return;
  }   
  int count = 1;
  
  while((dirent = readdir(parentDir)) != NULL){
     if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
    {
      // Construct new path from our base path

      printf("%s\n", dirent->d_name);
      strcpy(path, argv);
      strcat(path, "/");
      strcat(path, dirent->d_name);
      recursMethod( path);
    } 
  } 
  closedir (parentDir); 
}


int main (int argc, char **argv) {
   int option;
   if (argc < 2) { 
    printf ("Usage: %s <dirname>\n", argv[0]); 
    exit(-1);
  }  
  recursMethod( argv[1]);
  return 0; 
}
