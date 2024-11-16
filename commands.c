#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
