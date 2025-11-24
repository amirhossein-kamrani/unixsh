#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {

  while (true)
  {

    char *UserInput;
    UserInput = readline("unixsh> ");
    add_history(UserInput);
    printf("%s\n", UserInput);
    
  }

  return 0;
}