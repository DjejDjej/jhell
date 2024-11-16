#define _POSIX_C_SOURCE 200809L // Enable POSIX features for popen
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
void help(char **args, int argc) { printf("find help - %s \n", args[0]); }
void ls(char **args, int argc) {
  struct dirent *de;

  char *path = "."; // "." means the current directory

  if (argc >= 2) {
    path = args[1];
  }
  if (access(path, R_OK) != 0) {
    printf("no permisions for this folder\n");
    return;
  }

  DIR *dr = opendir(path);

  if (dr == NULL) { // opendir returns NULL if directory couldn't be opened
    printf("Could not open current directory\n");
  }

  while ((de = readdir(dr)) != NULL)
    if (strcmp(de->d_name, "..") != 0 && (strcmp(de->d_name, ".") != 0)) {
      printf("%s\n", de->d_name);
    }
}

void pwd(char **args, int argc) {

  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s\n", cwd);
  } else {
    printf("getcwd() error");
  }
}

void touch(char **args, int argc) {

  char *path = args[1];
  FILE *fptr;

  fptr = fopen(path, "w");

  if (fptr == NULL) {
    printf("Error openning file");
  }
}

void exec(char **args, int argc) {

  char buffer[1024];

  char *cmd = args[1];

  FILE *fp;
  fp = popen(cmd, "r");

  if (fp == NULL) {
    printf("popen failed");
  }

  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("%s", buffer);
  }

  // Close the file pointer
  if (pclose(fp) == -1) {
    printf("pclose failed");
  }
}

void mdir(char **args, int argc) {

  struct stat st = {0};
  char *path = args[1];
  if (stat(path, &st) == -1) {
    mkdir(path, 0777);
  } else {
    printf("error creating folder");
  }
}

void echo(char **args, int argc) {
  // doesnt work, do not try

  char *txt = args[2];

  if (argc == 1) {
    printf("ee");
    printf("%s\n", txt);
  }
  if (argc == 2) {
    char *path = args[2];
    FILE *fptr;

    // Open a file in writing mode
    fptr = fopen(path, "w");

    // Write some text to the file
    fprintf(fptr, txt);

    // Close the file
    fclose(fptr);
    printf("HERE");
  }
}
void rm(char **args, int argc) {

  char *path = args[1];

  if (remove(path) != 0) {

    printf("Couldnt delete this file");
  }
}

void clear(char **args, int argc) { system("clear"); }

void cd(char **args, int argc) {

  char *path = args[1];
  if (access(path, R_OK) != 0) {
    printf("no permisions for this folder\n");
    return;
  }
  if (access(path, X_OK) != 0) {
    printf("no permisions for this folder\n");
    return;
  }

  if (chdir(path) != 0) {
    printf("Error changing folder.\n");
  }
}

void prompt() {
  char cwd[1024];
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    printf("%s$: ", cwd);
  }
}
