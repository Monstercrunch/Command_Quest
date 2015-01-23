#include "console.h"
#include <unistd.h>
#include <string>
#include <locale.h>
#include <iostream>
#include <fstream>

Console::Console()
{
  time = 20000;  
  first_print = true;
}

int Console::getH()
{
  return height;
}

int Console::getW()
{
  return width;
}

void Console::slow_print(WINDOW* win, std::string filename, int margin_y = 0, int margin_x = 0)
{
  setlocale(LC_ALL, "");
  int i = 0;
  int x,y, xmax, ymax;
  char c;
  bool slow = true;
  bool stop = false;
  std::string str = "Appuie sur Entrer pour continuer...";
  std::string empty_str = "                                   ";
  std::string accent;
  std::string text;
  fstream text_file(filename);

  
  noecho();

  if(this->first_print)
    {
      this->first_print = false;      
    }

  //Get the actuel size of the windows
  getmaxyx(win,y,x);
  //Change the scrolling position
  wsetscrreg(win,0,y-3);

  
  while (!text_file.fail())
    {
      getine(text_file, text);
      while(text[i]!='\0')
	{
	  c = text[i];
	  stop = false;
	  if (c=='-')
	    {
	      if(slow)
		{
		  usleep(time*10);
		}
	    }       
	  else if(c=='|')
	    {	  
	      slow = true;
	      stop = true;
	    }
	  else
	    {
	      waddch(win,c);	    
	      wrefresh(win);
	    }
      
	  if(slow)
	    {
	      if(stop)
		{
		  scrollok(win, FALSE);
		  getyx(win,y,x);
		  getmaxyx(win, ymax,xmax);
		  wmove(win,ymax-1,(xmax-str.length())/2);
		  wprintw(win,str.c_str());
		  wrefresh(win);
		  wmove(win,y,x);
		  scrollok(win, TRUE);
		}

	      do
		{
		  if(getch()=='\n')
		    {
		      if(c=='|')
			{
			  slow = true;
			  stop = false;
			  scrollok(win, FALSE);
			  getyx(win,y,x);
			  getmaxyx(win, ymax,xmax);
			  wmove(win,ymax-1,(xmax-empty_str.length())/2);
			  wprintw(win,empty_str.c_str());
			  wrefresh(win);
			  wmove(win,y,x);
			  scrollok(win, TRUE);
			}
		      else
			{
			  slow = false;		      
			}
		    }	 
		}while(stop);
	    }
	  i++;
	}
    }
}

void Console::init()
{
  setlocale(LC_ALL, "");
  initscr();  
  cbreak();
  timeout(50);
  keypad(stdscr, TRUE);
  getmaxyx(stdscr, height, width);
  scrollok(stdscr, TRUE);
}

Console::~Console()
{
  endwin();
}

void Console::draw_box(int margin_y, int margin_x)
{
  margin_y -= 1;
  margin_x -= 1;
  move(margin_y-3, margin_x-1);
  for(int i = 0; i < (this->width-2*margin_x+2); i++)
    {
      printw("_");
    }
  move(margin_y-2, margin_x-2);
  printw("/");
  for(int i = 0; i < (this->width-2*margin_x+2); i++)
    {
      printw(" ");
    }
   printw("\\");
   move(margin_y-1, margin_x-2);
   printw("\\");
   for(int i = 0; i < (this->width-2*margin_x+2); i++)
    {
      printw("_");
    }
   printw("/");

   for(int j = margin_y; j < this->height-2*margin_y+3; j++)
     {
       move(j, margin_x-1);
       printw("|");
       for(int i = 0; i < (this->width-2*margin_x); i++)
	 {
	   printw(" ");
	 }
       printw("|");
     }

   move(this->height-2*margin_y+2, margin_x-2);
   printw("/");
   for(int i = 0; i < (this->width-2*margin_x+2); i++)
     {
       printw(" ");
     }
   printw("\\");
   move(this->height-2*margin_y+3, margin_x-2);
   printw("\\");
   for(int i = 0; i < (this->width-2*margin_x+2); i++)
     {
       printw("_");
     }
   printw("/");

   refresh();
}
   
  
