#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
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

  int Should_Run = 1;
  int Shmid = shmget((key_t) 1, 1024, 0666 | IPC_CREAT);
  int *Shared_Memory = shmat(Shmid, NULL, 0);
  char Directort_Path[100];

  while (Should_Run)
  {

    char *User_Input;
    User_Input = readline("unixsh> ");
    add_history(User_Input);

    char **Arguments = parse_input(User_Input);
    char *Command = Arguments[0];

    pid_t pid = fork();

    if (pid < 0) {
      perror("Fork faild");
      continue;

    } else if (pid == 0) {

      if (strcmp(Command, "exit") == 0) {
        *Shared_Memory = 0;
        Should_Run = *Shared_Memory;

      }
      
      else if (strcmp(Command, "cd") == 0) {
        chdir(Arguments[1]);

        if (chdir(Arguments[1]) != 0) {
          perror("cd failed");

        }

      }

      else if (strcmp(Command, "pwd") == 0) {
        printf("%s\n", getcwd(Directort_Path, 100));
        
      }

    } else {
      wait(NULL);
      Should_Run = *Shared_Memory;
      
    }

    free(User_Input);
    
  }

  return 0;
}