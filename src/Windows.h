
#include <ncurses.h>
enum Modes{
  NORMAL,
  COMMAND,
  INSPECT
};

struct WindowContents {
  WINDOW * window;
  unsigned int line;
  unsigned int height;
  unsigned int endLine;
  char * content;
};

void PrintLineRange(WINDOW * window, char * str, unsigned int start, unsigned int end);
void InitWindow(struct WindowContents * windowContents);
void InspectMode(int input, struct WindowContents * windowContents);
struct WindowContents * CreateWindowContents(WINDOW * window, char ** content);
