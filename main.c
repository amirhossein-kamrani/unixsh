#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <readline/readline.h>
#include <readline/history.h>

char **parse_input(char *input) {
  int Index = 1;
  char **Tokens = malloc(1024 * sizeof(char *));
  char *Token;
  Token = strtok(input, " \n");
  Tokens[0] = Token;

  while (Token != NULL)
  {
    Token = strtok(NULL, " ");
    Tokens[Index] = Token;
    Index++;
  }

  Tokens[Index] = NULL;
  
  return Tokens;
}

int main() {

  while (true)
  {

    char *UserInput;
    UserInput = readline("unixsh> ");
    add_history(UserInput);

    char **Arguments = parse_input(UserInput);
    char Command = Arguments[0];

    pid_t pid = fork();

    if (pid < 0) {

      perror("Fork faild");
      continue;

    } else if (pid = 0) {

    } else {

    }

    free(UserInput);
    
  }

  return 0;
}