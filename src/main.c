#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

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
      close(pipes[1]);
      FILE *stream = fdopen (pipes[0], "r");;

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

int main(void)
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    move(LINES/2,COLS/2);
    printw("");
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
}
