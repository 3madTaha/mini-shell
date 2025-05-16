#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define BUF_SIZE 4096

// Reads one word (sequence of characters without space/newline) from file descriptor into buffer
int read_word(int fd, char *buf) {
  int i = 0;
  char ch;
  while (read(fd, &ch, 1) == 1) {
    // If we reach space or newline and already have characters, stop
    if (ch == ' ' || ch == '\n') {
      if (i > 0) break;
      else continue; // Skip leading spaces/newlines
    }
    // Add character to word buffer
    buf[i++] = ch;
  }
  buf[i] = '\0'; // Null-terminate the string
  return i; // Return length of word read
}

// Writes a word followed by a space to the output file descriptor
void return_word(int fd, const char *word) {
  write(fd, word, strlen(word));
  write(fd, " ", 1); // Add space after word
}

int main(int argc, char *argv[]) {
  // Check for valid number of arguments (2 input files, optional output file)
  if (argc != 3 && argc != 4) {
    printf("Missing Parameters\n");
    return 1;
  }

  // Open first and second input files for reading
  int fd1 = open(argv[1], O_RDONLY);
  int fd2 = open(argv[2], O_RDONLY);

  // If either file failed to open, print error and exit
  if (fd1 < 0 || fd2 < 0) {
    const char *err = "Error\n";
    write(1, err, strlen(err));
    if (fd1 >= 0) close(fd1);
    if (fd2 >= 0) close(fd2);
    return 1;
  }

  int fdout = 1; // Default output is standard output (screen)
  if (argc == 4) {
    // If third argument is provided, open it as output file (create/truncate)
    fdout = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 06444);
    if (fdout < 0) {
      const char *err = "Error\n";
      write(1, err, strlen(err));
      close(fd1);
      close(fd2);
      return 1;
    }
  }

  char word[BUF_SIZE];
  int read1, read2;

  // Loop to alternate reading words from both files
  while (1) {
    read1 = read_word(fd1, word);
    if (read1 > 0) {
      return_word(fdout, word);
    }

    read2 = read_word(fd2, word);
    if (read2 > 0) {
      return_word(fdout, word);
    }

    // If both files have no more words, break the loop
    if (read1 <= 0 && read2 <= 0) break;
  }

  // If output is to screen, add a newline at the end
  if (argc == 3)
    write(fdout, "\n", 1);

  // Close all opened files
  close(fd1);
  close(fd2);
  if (argc == 4) close(fdout);

  return 0;
}
