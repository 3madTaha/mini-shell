#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

// This function adds a line (input) to a history file
void addto_history(char * filename,char * input)
{
  // Open the file for writing, create if it doesn't exist, append to the end
  int fd =open(filename,O_WRONLY | O_CREAT | O_APPEND,0644);
  if(fd<0)
  {
    // If open fails, print error and exit
    printf("open failed\n");
    exit(1);
  }
  
  // Write the input to the file
  int w = write(fd,input,strlen(input));
  if(w<0)
  {
    // If write fails, print error and exit
    printf("write failed\n");
    exit(1); 
  }
   
  // Write a newline character after the input
  write(fd,"\n",1);

  // Close the file
  close(fd);
}

// This function reads and shows the content of the history file
void show_history(char * filename)
{
  // Open the file for reading
  int fd=open(filename,O_RDONLY);
  if(fd<0)
  {
    // If open fails, show error and exit
    printf("history not available\n");
    exit(1);
  }
  
  int bytes;
  char buffer[100];

  // Read the file and print it to the screen
  while((bytes = read(fd,buffer,sizeof(buffer)))>0)
  {
    write(1,buffer,bytes); // write to stdout (1)
  }

  // Close the file
  close(fd);
}

// Main function
int main(int argc,char* argv[])
{
  // If 2 arguments: show the history file
  if(argc==2)
  {
    show_history(argv[1]);
  }

  // If 3 arguments: add input to the history file
  if(argc==3)
  {
    addto_history(argv[1],argv[2]);
  }
  
  return 0;
}
