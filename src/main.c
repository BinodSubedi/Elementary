#include "./includes/lexer.h"
#include <stdio.h>
#include <string.h>
int main(int argsNum, char *args[]) {

  if (argsNum > 1) {

    printf("number of args: %d, and first user argument is: %s\n", argsNum,
           args[1]);

    const char *code = "int a = 12";

    int a = 0;

    while (strcmp(&code[a], "\0") != 0) {
      getNextToken(code, &a);
    }
  }

  return 0;
}
