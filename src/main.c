#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "StringUtil.h"
#include "Windows.h"
#include <limits.h>

#define true 1
#define false 0


int main(void)
{
  initscr();
  raw();
  keypad(stdscr, TRUE);
  /* noecho(); */
  /* curs_set(0); */

  char cwd[PATH_MAX];
  getcwd(cwd, PATH_MAX);

  char gitdir[PATH_MAX + 10];
  gitdir[0]='\0';
  strcat(gitdir, "--git-dir=");
  strcpy(&gitdir[strlen(gitdir)], cwd);
  strcat(gitdir, "/.git");

  char worktree[PATH_MAX + 11];
  worktree[0]='\0';
  strcat(worktree, "--work-tree=");
  strcpy(&worktree[strlen(worktree)], cwd);


  char * diff[] = {"git", gitdir, worktree,"diff",NULL};
  struct WindowContents * viewWin = CreateWindowContents(newwin(LINES, (2*COLS)/3, 0, COLS/3), diff);

  char *  status[] = {"git", gitdir, worktree,"status","-sb",NULL};
  struct WindowContents * statusWin = CreateWindowContents(newwin(LINES/3, COLS/3, 0, 0), status);

  char * log[] = {"git", gitdir, worktree,"log","--oneline","--graph",NULL};
  struct WindowContents * logWin = CreateWindowContents(newwin(LINES/3, COLS/3, LINES/3, 0), log);

  char *  stash[] = {"git", gitdir, worktree, "stash", "list", NULL};
  struct WindowContents * stashWin = CreateWindowContents(newwin(LINES/3, COLS/3, (2*LINES)/3, 0), stash);

  int ch=0;
  unsigned int mode = INSPECT;
  while(ch != 27)
  {
    ch = getch();
    switch (mode){
      case INSPECT:
        InspectMode(ch, viewWin);
        /* wrefresh(viewWin->window); */
        wmove(viewWin->window, 0, 0);
        move(LINES/3,COLS);
        printw("");
        break;
    }
    refresh();
  }
  endwin();
}
