#include "../includes/lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*typedef struct {

  Token token;
  int *newTokenStartIndex

} GetTokenReturn;

*/

static bool isKeyword(const char *val) {
  if (strcmp(val, "int") || strcmp(val, "u8") || strcmp(val, "print")) {
    return true;
  }
  return false;
}

static bool isOperator(const char *val) {
  if (strchr("+-*/", *val) != NULL) {
    return true;
  }
  return false;
}

Token getNextToken(const char *code,
                   int *const TK_Index) { // TK_Index is the starting index for
                                          // new token initialized from 0
  Token token;

  if (code[*TK_Index] != '\0') { // As this situation will not happen, we always
    // check for len end while asking for next token
    while (isspace(code[*TK_Index])) {
      *TK_Index = *TK_Index + 1;
      continue;
    }
  }

  if (isalpha(code[*TK_Index])) {
    char val[16] = "";
    int startPos = *TK_Index;
    int endPos = startPos;

    val[0] = code[startPos];
    *TK_Index = *TK_Index + 1;
    while (isalpha(code[endPos + 1])) {
      endPos++;
      *TK_Index = *TK_Index + 1;
      val[endPos - startPos] = code[endPos];
    }

    val[endPos + 1] = '\0';

    token.type = Token_Number;
    strcpy(token.value, val);

    printf("token type: %d\n token value: %s\n tk_index:%d\n", token.type,
           token.value, *TK_Index);
    return token;
  }

  return token;
}
