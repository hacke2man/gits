#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define true 1
#define false 0
#include <signal.h>

char * GetLine(char * str);
char * ProgToString(char * array[3]);
unsigned int NumLines(char * str);
