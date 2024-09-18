#include "./includes/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argsNum, char *args[]) {

  if (argsNum > 1) {

    printf("number of args: %d, and first user argument is: %s\n", argsNum,
           args[1]);

    char *codeBlock;

    codeBlock = malloc(1000);

    strcpy(codeBlock, "void main(int b){int a = 10;}");

    parseCode(codeBlock);
  }

  return 0;
}
