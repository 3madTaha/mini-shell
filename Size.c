#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
  // Check if exactly one argument (filename) is provided
  if(argc != 2) {
    printf("Not Supported\n");
    exit(1);
  }

  // Open the file for reading
  int fd = open(argv[1], O_RDONLY);
  if(fd < 0) {
    perror("openning file failed\n"); // Print error if open fails
    exit(1);
  }

  char buff[100];
  int count, size;

  // Read the file in chunks and count the total number of characters
  while((count = read(fd, buff, sizeof(buff))) > 0) {
    for (int i = 0; i < count; i++) {
      size++; // Count each character read with spaces and /n for new line
    }
  }

  // Close the file
  close(fd);

  // Print the total size (number of characters)
  printf("%d\n", size);

  return 0;
}
