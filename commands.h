#ifndef COMMANDS_H
#define COMMANDS_H

typedef struct {
  char *name;
  void (*command)(char **args,int argc);
  int argc;
} comm;
void help(char *args[],int argc);
void ls(char *args[],int argc);
void pwd(char *args[],int argc);
void cd(char *args[],int argc);
comm commands[] = {{"help", help, 0}, {"ls", ls,0},{"cd", cd,1}, {"pwd", pwd,0}, {"\0", help, 0}};


#endif
