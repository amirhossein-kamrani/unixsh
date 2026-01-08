#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pthread.h>

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

struct subgrid {
  int arr[9];
  int index;
};

struct row_column {
  int arr1[9];
  int arr2[9];
  int arr3[9];
  int arr4[9];
  int arr5[9];
  int arr6[9];
  int arr7[9];
  int arr8[9];
  int arr9[9];
  int index;
};

int valid[11];

void *validate_row_column(void *param);
// void *validate_subgrid(void *param);

int main() {

  int Should_Run = 1;
  int Shmid = shmget((key_t) 1, 1024, 0666 | IPC_CREAT);
  int *Shared_Memory = shmat(Shmid, NULL, 0);
  char Directort_Path[100];
  char Buffer[1024] = "";
  char *User_Input;
  char **Arguments;

  while (Should_Run)
  {

    User_Input = readline("unixsh> ");
    add_history(User_Input);

    if (strcmp(User_Input, "!!") == 0) {
      printf("1\n");
      if (strlen(Buffer) == 0) {
        printf("No commands in history\n");
        free(User_Input);
        continue;

      }

      printf("3\n");
      printf("%s\n", User_Input);
      printf("%s\n", Buffer);
      Arguments = parse_input(Buffer);
      
      
    } else {
      printf("4\n");
      printf("%s\n", User_Input);
      strcpy(Buffer, User_Input);
      Arguments = parse_input(User_Input);
      printf("%s\n", Arguments[0]);
      printf("%s\n", Buffer);
    }

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

        if (chdir(Arguments[1]) != 0) {
          perror("cd failed");
        }

      }

      else if (strcmp(Command, "pwd") == 0) {
        printf("%s\n", getcwd(Directort_Path, 100));

      }

      else if (strcmp(Command, "help") == 0) {
        printf("available commands and usage information\n");
        
        printf("exit: Terminate the shell\n");
        printf("cd <directory>: Change working directory\n");
        printf("pwd: Print working directory\n");
        printf("ls: \n");
        printf("echo: \n");
      }

      else if (strcmp(Command, "sudoku_validator") == 0) {
        pthread_t threads[11];
        int thread_indexes[11];
        int return_code;
        struct row_column paramaters;

        for (int i = 1; i <= 9; i++) {
          printf("enter the 1st row: ");
          paramaters.arr1;

        }

        for (int i = 0; i < 11; i++) {
          thread_indexes[i] = i;

          if (i < 2) {
            return_code = pthread_create(&threads[i], NULL, validate_row_column, NULL);
          }

          else {
            // return_code = pthread_create(&threads[i], NULL, validate_subgrid, NULL);
          }
          
          
        }
        
      }

      else {
        printf("Command not found: %s\n", Command);
      }

    } else {
      wait(NULL);
      Should_Run = *Shared_Memory;
      
    }

    free(Arguments);
    free(User_Input);
    
  }

  return 0;
}

void *validate_row_column(void *param) {
  struct row_column *paramaters = param;

  for (int i = 0; i < 8; i++) {
    for (int j = i + 1; j < 9; j++) {

      if (paramaters->arr1[i] == paramaters->arr1[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr2[i] == paramaters->arr2[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr3[i] == paramaters->arr3[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr4[i] == paramaters->arr4[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr5[i] == paramaters->arr5[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr6[i] == paramaters->arr6[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr7[i] == paramaters->arr7[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr8[i] == paramaters->arr8[j]) {
        valid[paramaters->index] = 0;
      }

      else if (paramaters->arr9[i] == paramaters->arr9[j]) {
        valid[paramaters->index] = 0;
      }

    }
  }

  valid[paramaters->index] = 1;
  
}