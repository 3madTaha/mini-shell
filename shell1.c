#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc) 
{
  pid_t pid;
  int status;
  char input[100];

  while(1)
  {
    // Print shell prompt
    printf("shell1$** ");
    
    // Read user input
    if(fgets(input,sizeof(input),stdin)==NULL){
      continue;
    }
    
    // Remove newline character from the input
    input[strcspn(input,"\n")]=0;
    
    // If user enters "Esc", exit the shell
    if(strcmp(input,"Esc")==0){
      return 0;
    }
    
    // If user enters "exit", "Exit", or a command with spaces – not supported
    if((strcmp(input,"exit")==0) || (strcmp(input,"Exit")==0) || (strchr(input,' ')!=NULL))
    {
      fprintf(stderr,"Not Supported\n");
      continue;
    }
    
    // If user enters "history", show command history from history1.txt
    if(strcmp(input,"history")==0)
    {
      pid = fork();
      if(pid == 0)
      {
        execl("./history", "history", "history1.txt", NULL);
        printf("history failed\n");
        exit(1);
      }
      else{
        wait(NULL);
        continue;
      }
    } 
 
    // Fork a new process to run the command
    pid = fork();
    if(pid == -1)
    {
      perror("fork failed\n");
      exit(1);
    }
    
    if(pid == 0)
    {
      // Try to execute the input command (without parameters)
      execlp(input, input, NULL);
      // If it fails, print error
      fprintf(stderr,"Not Supported\n");
      exit(1);
    }
    else{
      // Parent process waits for the child to finish
      wait(&status);
    }

    // If the command executed successfully, add it to history
    if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
      pid = fork();
      if(pid == 0)
      {
        execlp("./history", "history", "history1.txt", input, NULL);
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
