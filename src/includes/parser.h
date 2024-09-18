#include "../includes/lexer.h"
#ifndef PARSER
#define PARSER

typedef struct Node {

  TokenType type;
  char val[16];
  struct Node *left;
  struct Node *right;

} ASTNode;

typedef struct {

  // Here I gonna have LabelArray, to store all existing functions name
  // and also have LabelCallArray to see all called function to find
  // non-existing or un-used function
  ASTNode *head;
  ASTNode *tail;

} AST;

ASTNode *parseCode(const char *code);

#endif
