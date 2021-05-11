#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define true 1
#define false 0

char * func(char * array[3]){
  int pipes[2];
  pipe(pipes);

  if(fork() == 0){
    dup2(pipes[1], STDOUT_FILENO);
    close(pipes[0]);
    close(pipes[1]);
    execvp(array[0], &array[1]);
    putc('\0', stdout);
    _Exit(0);
  }else{
    wait(0);
    close(pipes[1]);
    FILE *stream = fdopen (pipes[0], "r");

    char * out = malloc(4000 * sizeof(char));
    out[0] = '\0';
    char temp[150];
    while(fgets(temp, 150, stream))
    {
        strcat(out, temp);
    }


    fclose(stream);
    return out;
  }
}

#include <signal.h>
char * GetLine(char * str)
{
  /* raise(SIGINT); */
  static int start = 0;
  if( start == -1)
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
    outstring = malloc(sizeof(char) * 150);
    strcpy(outstring, &str[start]);
    start += spot;
  }else{
    outstring = malloc(sizeof(char) * 150);
    strcpy(outstring, &str[start]);
    start = -1;
  }

  return outstring;
}

int main(void)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  char * a[] = {"git","git","s",NULL};
  char * s = func(a);

  char * c;

  int i = 0;
  while(c != NULL)
  {
    c = GetLine(s);
    if(c != NULL)
      printw(c);
    move(i, 0);
  }
    refresh();

  int ch=0;
  while(ch != 27)
  {
      ch = getch();
      switch (ch) {
          default:
              break;
      }
  }
  endwin();
}
