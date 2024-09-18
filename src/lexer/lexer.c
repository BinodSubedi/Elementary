#include "../includes/lexer.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool isKeyword(const char *val) {
  if (strcmp(val, "int") == 0 || strcmp(val, "u8") == 0 ||
      strcmp(val, "print") == 0 || strcmp(val, "main") == 0 ||
      strcmp(val, "void") == 0 || strcmp(val, "return") == 0) {
    return true;
  }

  return false;
}

static TokenType identifierKeywordFilter(const char *val) {
  if (isKeyword(val)) {
    if (strcmp(val, "int") == 0 || strcmp(val, "u8") == 0 ||
        strcmp(val, "void") == 0) {
      return Token_TypeKeyword;
    } else if (strcmp(val, "print") == 0) {
      return Token_FunctionKeyword;
    } else if (strcmp(val, "main") == 0) {
      return Token_MainFunction;
    } else if (strcmp(val, "return") == 0) {
      return Token_ReturnKeyword;
    }
  }
  return Token_Identifier;
}

static bool isOperator(const char *val) {
  if (strchr("+-*/", *val) != NULL) {
    return true;
  }
  return false;
}

Token *getNextToken(const char *code,
                    int *const TK_Index) { // TK_Index is the starting index for
                                           // new token initialized from 0
  Token *token;
  token = malloc(sizeof(Token));

  if (code[*TK_Index] != '\0') { // As this situation will not happen, we always
    // check for len end while asking for next token
    while (isspace(code[*TK_Index])) {
      *TK_Index = *TK_Index + 1;
      continue;
    }
  }
  // else {
  //  return NULL;
  //}

  switch (code[*TK_Index]) {
    char val[16];

  case '=':
    val[0] = '=';
    val[1] = '\0';
    token->type = Token_Assign;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
    break;
  case '(':
    val[0] = '(';
    val[1] = '\0';
    token->type = Token_LParen;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;

    break;
  case ')':
    val[0] = ')';
    val[1] = '\0';
    token->type = Token_RParen;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;

    break;
  case '{':
    val[0] = '{';
    val[1] = '\0';
    token->type = Token_LBraces;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
    break;
  case '}':
    val[0] = '}';
    val[1] = '\0';
    token->type = Token_RBraces;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
    break;
  case ',':
    val[0] = ',';
    val[1] = '\0';
    token->type = Token_Comma;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
    break;
  case ';':
    val[0] = ';';
    val[1] = '\0';
    token->type = Token_SemiColon;
    strcpy(token->value, val);
    *TK_Index = *TK_Index + 1;
    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
    break;
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

    val[endPos - startPos + 1] = '\0';

    token->type = identifierKeywordFilter(val);
    strcpy(token->value, val);

    printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
           token->value, *TK_Index);
    return token;
  }

  if (isdigit(code[*TK_Index])) {
    char val[16] = "";
    int startPos = *TK_Index;
    int endPos = startPos;

    val[0] = code[startPos];
    *TK_Index = *TK_Index + 1;
    while (isdigit(code[endPos + 1])) {
      endPos++;
      *TK_Index = *TK_Index + 1;
      val[endPos - startPos] = code[endPos];
      printf("loopy");
    }

    val[endPos - startPos + 1] = '\0';

    token->type = Token_Number;
    strcpy(token->value, val);

    // printf("token->type: %d\n token->value: %s\n tk_index:%d\n", token->type,
    //      token->value, *TK_Index);
    return token;
  }

  return token;
}
