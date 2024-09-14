#include "../includes/lexer.h"
#include <cstdlib>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {

  TokenType type;
  char val[16];
  struct Node *left;
  struct Node *right;

} ASTNode;

Token current_token;
bool mainEntered = false;

void nextNode(const char *code, int *const TK_Index) {
  current_token = getNextToken(code, TK_Index);
}

ASTNode *parseTerm(const char *code, int *const TK_Index) {
  ASTNode *node = malloc(sizeof(ASTNode));

  if (current_token.type == Token_TypeKeyword) {

    node->type = Token_TypeKeyword;
    strcpy(node->val, current_token.value);

    node->left = node->right = NULL;

    nextNode(code, TK_Index);

    ASTNode *newNode1 = malloc(
        sizeof(ASTNode)); // for filtering between identifier and LabelKeyword
    ASTNode *newNode2 = malloc(sizeof(ASTNode));

    newNode1->left = newNode1->right = NULL; // Just initializing with null
    newNode2->left = newNode2->right = NULL;

    strcpy(newNode1->val, current_token.value);

    node->right = newNode1;

    nextNode(code, TK_Index);

    newNode1->right = newNode2;

    strcpy(newNode2->val, current_token.value);
    newNode2->type = current_token.type;

    // Setting newNode1 label type either be functionLabel or identifier
    if (strcmp(newNode2->val, "(") == 0) {
      newNode1->type = Token_LabelKeyword;
      // Possibly checking in with parseLBracesInternal
      // TODO: Here some work is do be done possibly calling
      // parseLBracesInternal Function

    } else if (strcmp(newNode2->val, "=") == 0) {
      newNode1->type = Token_Identifier;
      // will be returned from outer return statement
    }
  } else if (current_token.type == Token_Identifier) {
    // Here we see abput assignment or whatever
  }

  return node;
};

// Probably need conditional and loop paren parser, we will do that later

ASTNode *
parseLFuntionParenInternals() { // Its Label function paren internals,means when
                                // creating function
  ASTNode *node = malloc(sizeof(ASTNode));

  return node;
};

ASTNode *
parseCFuntionParenInternals() { // Its Call function paren internals,means when
                                // calling function
  ASTNode *node = malloc(sizeof(ASTNode));

  return node;
};

ASTNode *parseExpressionParenInternals() { // Possibly by expression it means
                                           // loops and conditional
  ASTNode *node = malloc(sizeof(ASTNode));

  return node;
};

ASTNode *parseBracesInternals() {
  ASTNode *node = malloc(sizeof(ASTNode));

  return node;
};

ASTNode *parseAssignment() {
  ASTNode *node = malloc(sizeof(ASTNode));

  return node;
};

ASTNode *parseStatement(const char *code, int *const TK_Index) {
  ASTNode *node;

  if (current_token.type == Token_TypeKeyword) {
    // For function start or variable initialization

    // two type because we can even have global variable outside functions
    // int a = 1 + 2
    // int func1 (){}
    // So, chaining nodes up to third token
    node = parseTerm(code, TK_Index);

  } else if (current_token.type ==
             Token_LBraces) { // May be I don't need it though cause we will
                              // always start in function
    // For shadowing variable, scope inside braces only
    // I will do this later
  } else if (current_token.type == Token_ExitCode) {
    // Probably don't need now for intial testing
  }

  return node;
}
