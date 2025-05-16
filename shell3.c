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

  while(1) {
    printf("shell3$** ");

    // Get user input from the command line
    if(fgets(input, sizeof(input), stdin) == NULL) {
      continue;
    }

    // Remove newline character at the end of the input
    input[strcspn(input, "\n")] = 0;

    // Exit the shell if user types "Esc"
    if(strcmp(input, "Esc") == 0) {
      return 0;
    }

    // Ignore and reject "exit" and "Exit" commands
    if((strcmp(input, "exit") == 0) || (strcmp(input, "Exit") == 0)) {
      printf("Not Supported\n");
      continue;
    }

    // Split the input into command and arguments
    int i = 0;
    args[i] = strtok(input, " ");
    while(args[i] != NULL && i < MAX_ARGS - 1) {
      i++;
      args[i] = strtok(NULL, " ");
    }
    args[i] = NULL; // Mark the end of arguments

    // Check if command is one of the supported ones
    if(strcmp(args[0], "Merge") != 0 && strcmp(args[0], "Size") != 0 && strcmp(args[0], "Delete") != 0) {
      printf("Not Supported\n");
      continue;
    }

    // Build the path to the executable (e.g., ./Merge)
    char *orginal = args[0];
    strcpy(path, "./");
    strcat(path, orginal);

    // Create child process
    pid = fork();
    if(pid == 0) {
      // In child: run the command using execvp
      execvp(path, args);
      perror("exec failed\n"); // If exec fails, show error
      exit(1);
    } else {
      // In parent: wait for child to finish
      wait(NULL);
    }
  }

  return 0;
}
