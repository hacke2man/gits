#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "StringUtil.h"
#include "Windows.h"

#define true 1
#define false 0


int main(void)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();

  char * diff[] = {"git","git","diff",NULL};
  struct WindowContents * firstWin = CreateWindowContents(newwin(LINES/2, COLS/2, 0, 0), diff);

  char *  status[] = {"git","git","status","-sb",NULL};
  struct WindowContents * second = CreateWindowContents(newwin(LINES/2, COLS/2, 0, COLS/2), status);

  char *  log[] = {"git","git","log","--oneline","--graph",NULL};
  struct WindowContents * third = CreateWindowContents(newwin(LINES/2, COLS/2, LINES/2, 0), log);

  int ch=0;
  unsigned int mode = INSPECT;
  while(ch != 27)
  {
    ch = getch();
    switch (mode){
      case INSPECT:
        InspectMode(ch, firstWin);
        wrefresh(firstWin->window);
        break;
    }
    refresh();
  }
  endwin();
}
