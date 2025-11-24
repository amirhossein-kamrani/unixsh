#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

  while (true)
  {

    printf("unixsh>");

    char UserInput[1024];
    fgets(UserInput, 1024, stdin);
    UserInput[strlen(UserInput) - 1] = '\0';

    if (strcmp(UserInput, "exit") == 0)
    {
      break;
    }
    else {
      printf("%s: command not found\n", UserInput);
    }
  }

  return 0;
}