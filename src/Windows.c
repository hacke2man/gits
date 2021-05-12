#include "Windows.h"
#include "StringUtil.h"
#include <curses.h>
#include <stdlib.h>

struct WindowContents * CreateWindowContents(WINDOW * window, char ** command)
{
  struct WindowContents * windowContents = malloc(sizeof(struct WindowContents));
  char * lineString;
  windowContents->window = window;
  windowContents->height = getmaxy(windowContents->window) - 2;
  windowContents->content = ProgToString(command);
  windowContents->line = 0;
  windowContents->endLine = NumLines(windowContents->content);
  box(windowContents->window, 0, 0);

  PrintLineRange(
      windowContents->window,
      windowContents->content,
      windowContents->line,
      windowContents->line + windowContents->height
      );
  refresh();
  wrefresh(windowContents->window);

  return windowContents;
}

void InspectMode(int input, struct WindowContents * windowContents)
{
  switch (input) {
    case 106:
      if(windowContents->line + windowContents->height < windowContents->endLine)
        windowContents->line++;
      PrintLineRange(
          windowContents->window,
          windowContents->content,
          windowContents->line,
          windowContents->line + windowContents->height
          );
      break;
    case 107:
      if(windowContents->line > 0)
        windowContents->line--;
      PrintLineRange(
          windowContents->window,
          windowContents->content,
          windowContents->line,
          windowContents->line + windowContents->height
          );
      break;
    default:
      wrefresh(windowContents->window);
      break;
  }
}

void PrintLineRange(WINDOW * window, char * str, unsigned int start, unsigned int end)
{
  for(int i = 0; i < start; i++)
  {
    GetLine(str);
  }

  int x = getmaxx(window) - 2;
  char clearstring[x];
  for(int i = 0; i < x; i++)
    clearstring[i] = ' ';
  clearstring[x-1] = '\0';

  char *temp;
  for(int i = 0; i < (end - start); i ++)
  {
    temp = GetLine(str);
    if(temp != NULL)
    {
      wmove(window, i + 1, 1);
      wprintw(window, clearstring);
      wmove(window, i + 1, 1);
      wprintw(window, temp);
    } else
     break;
  }

  GetLine(NULL);
}
