#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#define MAX_ARGS 20 

int main() {
  int status;
  pid_t pid;
  char input[100], path[100];
  char *args[MAX_ARGS];
  
  while(1){
    // Print shell prompt
    printf("shell2$** ");
    
    // Read user input
    if(fgets(input, sizeof(input), stdin) == NULL){
      continue; 
    }
    
    // Remove newline character
    input[strcspn(input, "\n")] = 0;

    // Save original input (before tokenizing) to path
    strcpy(path, input);
  
    // If user types "Esc", exit the shell
    if(strcmp(input, "Esc") == 0){
      return 0;
    }

    // If user types "exit" or "Exit", print "Not Supported"
    if((strcmp(input, "exit") == 0) || (strcmp(input, "Exit") == 0)) {
      printf("Not Supported\n");
      continue;
    }

    // If command has no space and is not "history", it's not supported
    if(strchr(input, ' ') == NULL && strcmp(input, "history") != 0){
      printf("Not Supported\n");
      continue;
    }

    // If user types "history", show the command history from history2.txt
    if(strcmp(input, "history") == 0)
    {
      pid = fork();
      if(pid == 0)
      {
        execl("./history", "history", "history2.txt", NULL);
        printf("history failed\n");
        exit(1);
      }
      else{
        wait(NULL);
        continue;
      }
    } 
     
    // Tokenize input string into command and parameters
    int i = 0;
    args[i] = strtok(input, " ");
    while(args[i] != NULL && i < MAX_ARGS - 1){
      i++;
      args[i] = strtok(NULL, " ");
    }
    args[i] = NULL;

    // Fork a child process to execute the command
    pid = fork();
    if(pid == -1){
      perror("fork failed");
      exit(1);
    }
    if(pid == 0){
      // Try to execute the command with arguments
      execvp(args[0], args);
      // If execution fails, print error and exit
      fprintf(stderr, "Not Supported\n");
      exit(1);
    }

    // Parent waits for the child to finish
    wait(&status);

    // If command ran successfully, add it to history
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
      pid = fork();
      if(pid == 0)
      {
        execlp("./history", "history", "history2.txt", path, NULL);
        perror("exec failed\n");
        exit(1);
      }
      else{
        wait(&status);
      }
    }
  }

  return 0;
}
