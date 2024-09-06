#include <stdio.h>
int main(int argsNum, char *args[]) {

  if (argsNum > 1) {

    printf("number of args: %d, and first user argument is: %s\n", argsNum,
           args[1]);
  }

  return 0;
}
