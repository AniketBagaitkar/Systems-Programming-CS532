## Project title:
To implement a simple shell or command line interpreter

## Project Description:
The Shell or Command Line Interpreter is the fundamental user interface provided by an operating
system. In other words, the shell is just another program. For example, the Bash shell is an executable
named bash that is usually located in the /bin directory. So, /bin/bash. My approach to this was when the command is entered it will be parsed and will look for special characters like pipes etc. Will check for any builtin commands and executing them using fork.

## Author:
Aniket Ashok Bagaitkar

## Github Link:
https://github.com/AniketBagaitkar/Systems-Programming-CS532/blob/main/HWbonus/shell.c 

## Acknowledgment:
I will like to thank Dr. Unan and the TA's.

## Getting Started:
Prerequisites/dependencies: 
1. IDE or Code Editor like VScode.
2. Terminal to run linux commands.
3. C compiler and debugger.

Instructions for building the software:
1. Use best software engineering practices to design and implement.
2. Use functions and organize these functions in multiple files if necessary.
3. Use a Makefile to compile and build the multiple files.
4. Implementing basic functionality such as parsing the input and then gradually adding
features.

## Running the test:
To compile: gcc -o uab_sh aniket_bonus.c 
To run:./uab_sh

## How to run test cases:
After running the above command you will be directed to a shell. Once the shell is open, you can run following command 
>>> ls
>>> mkdir
>>> hello
>>> !!

## Sample test cases:
>>> quit 
It will exit the shell and will bring you back to the terminal window.

## Screenshots/Sample Session:
>>> hello

 Hello World
Dir: /mnt/c/Users/anike/Downloads/UAB_education/Systems Programming/HW Bonus
>>> ls
ReadMe.md  a.out  bonus_hw.pdf  shell.c  uab_sh

Dir: /mnt/c/Users/anike/Downloads/UAB_education/Systems Programming/HW Bonus

## Contact Information:
aniketb@uab.edu
314 793 7630