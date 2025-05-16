#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
  int status;

  // Check if user provided exactly one argument (the file to delete)
  if(argc != 2) {
    printf("Not Supported\n");
    exit(1);
  }

  // Create a new child process
  pid_t pid = fork();

  // If fork fails, print error and exit
  if(pid == -1) {
    printf("dork failed\n");
    exit(1);
  }

  // In child process: try to run "rm <filename>" to delete the file
  if(pid == 0) {
    execlp("rm", "rm", argv[1], NULL);
    // If execlp fails, print error and exit
    perror("execlp failed");
    exit(1);
  }
  else {
    // Parent waits for the child to finish
    wait(&status);
  }

  return 0;
}
