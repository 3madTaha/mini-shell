#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
  pid_t pid;
  int status;
  char input[100], path[100];

  while(1)
  {
    // Print menu for user to choose a shell
    printf("Enter <shell1> to run linux commands without parameters\n");
    printf("Enter <shell2> to run linux commands with parameters\n");
    printf("Enter <shell3> to run linux commands tp file editing\n");
    printf("Shell$** ");
    
    // Read user input
    scanf("%s", input);
    
    // If user types "Exit", delete history files and exit the program
    if(strcmp(input,"Exit")==0) {
      unlink("history1.txt");
      unlink("history2.txt");
      return 0;
    }

    // Check if the input is one of the valid shell names
    if(strcmp(input,"shell1")==0 || strcmp(input,"shell2")==0 || strcmp(input,"shell3")==0)
    {
      // Build the path to the shell executable (e.g., "./shell1")
      strcpy(path,"./");
      strcat(path,input);

      // Create a child process
      pid = fork();
      if(pid < 0)
      {
        // If fork fails, print error and exit
        perror("fork failed");
        exit(1);
      }

      if(pid == 0)
      {
        // In the child process: execute the shell program
        execlp(path, input, NULL);
        // If execlp fails, print error and exit child process
        perror("execlp failed");
        exit(1);
      }
      else
      {
        // Parent process waits for the child to finish
        wait(&status);
      }
    }
    else
    {
      // If input is not valid, print error message
      printf("Not Supported\n");
    }
  }

  return 0; 
}
