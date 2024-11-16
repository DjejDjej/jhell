#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
  char *name;
  void (*command)(char **args, int argc);
  int argc;
} comm;
void help(char *args[], int argc);
void ls(char *args[], int argc);
void pwd(char *args[], int argc);
void cd(char *args[], int argc);
void touch(char *args[], int argc);
void rm(char *args[], int argc);
void mdir(char *args[], int argc);
void exec(char *args[], int argc);
void clear(char *args[], int argc);
void prompt();
comm commands[] = {{"help", help, 0},   {"ls", ls, 0},  {"cd", cd, 1},
                   {"touch", touch, 1}, {"rm", rm, 1},  {"pwd", pwd, 0},
                   {"mkdir", mdir, 0},{"exec", exec, 1},{"clear", clear,0}, {"\0", help, 0}};

#endif
