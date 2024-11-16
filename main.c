#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
comm getCommand(char **args, comm c[]) {
  for (size_t i = 0; strcmp(c[i].name, "\0") != 0; i++) {
    if (strcmp(c[i].name, args[0]) == 0) {
      return c[i];
    }
  }
  return c[0];
}

int proccesCommand(char **argv, int argc) {
  if (argc < 1) {
    commands[0].command(argv, argc);
    return 1;
  }

  comm c = getCommand(argv, commands);
  if (argc > c.argc) {
    c.command(argv, argc);
  } else {

    commands[0].command(argv, argc);
  }
  return 0;
}

void getinput() {

  char input[100];  // Buffer to hold the input line
  char *inputs[15]; // Array to store pointers to tokens (words)
  int count = 0;    // Counter for number of words

  if (fgets(input, sizeof(input), stdin) == NULL) {
    printf("Error reading input.\n");
    return;
  }

  size_t len = strlen(input);
  if (len > 0 && input[len - 1] == '\n') {
    input[len - 1] = '\0';
  }

  char *token = strtok(input, " ");
  while (token != NULL && count < 15) {
    inputs[count] = malloc(strlen(token) + 1);
    if (inputs[count] == NULL) {
      printf("Memory allocation failed.\n");
      return;
    }
    strcpy(inputs[count], token);
    count++;

    token = strtok(NULL, " ");
  }

  proccesCommand(inputs, count);
}

int main() {

  for (;;) {
    getinput();
    printf("\n");
  }

  return 0;
}
