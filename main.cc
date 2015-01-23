#include "console.cc"

using namespace std;


int main()
{
  Console console;
  console.init();
  
  WINDOW* intro = newwin(console.getH()-10, console.getW()-30, 5, 15);
  stringstream text;
  string textbis;
  console.draw_box(5,15);
  
  
   

  textbis = text.str();
  console.slow_print(intro, "test", 5, 10);
  text.str("");
  text  << "\nAh !- Ca y est !- Xor l'indecis !!! :D|\n";
  textbis = text.str();
  console.slow_print(intro, "test", 5, 10);

  

  return 0;
}
