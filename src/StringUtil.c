#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define true 1
#define false 0
#include <signal.h>
#include "StringUtil.h"

unsigned int NumLines(char * str)
{
  int i = 0;
  while(GetLine(str) != NULL)
  {
    i++;
  }
  return i - 1;
}

//Pulls a line from a string
char * GetLine(char * str)
{
  static int start = 0;
  if( start == -1 || str == NULL)
  {
    start = 0;
    return NULL;
  }
  unsigned int spot = start;
  char * ch = &str[spot];

  while(*ch != '\n' && *ch != '\0')
  {
    ch = &str[spot];
    spot++;
  }

  char * outstring;
  if(*ch == '\n'){
    *ch = '\0';
    outstring = malloc(sizeof(char) * strlen(&str[start]) + 1);
    strcpy(outstring, &str[start]);
    start = spot;
    *ch = '\n';
  }else{
    outstring = malloc(sizeof(char) * strlen(&str[start]) + 1);
    strcpy(outstring, &str[start]);
    start = -1;
  }

  return outstring;
}

char * ProgToString(char ** array){
  int pipes[2];
  pipe(pipes);

  if(fork() == 0){
    dup2(pipes[1], STDOUT_FILENO);
    close(pipes[0]);
    close(pipes[1]);
    execvp(array[0], &array[0]);
    printf("%d", EOF);
    _Exit(0);
  }else{
    wait(0);
    close(pipes[1]);
    FILE *stream = fdopen (pipes[0], "r");
    char * out = malloc(8000 * sizeof(char));
    out[0] = '\0';
    char temp[301];
    temp[0] = '\0';
    while(fgets(temp, 300, stream))
    {
        strcat(out, temp);
    }

    fclose(stream);
    return out;
  }
}
