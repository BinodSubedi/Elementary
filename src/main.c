#include "./includes/lexer.h"
#include <stdio.h>
int main(int argsNum, char *args[]) {

  if (argsNum > 1) {

    printf("number of args: %d, and first user argument is: %s\n", argsNum,
           args[1]);

    const char *code = "int";

    int a = 0;

    getNextToken(code, &a);
  }

  return 0;
}
