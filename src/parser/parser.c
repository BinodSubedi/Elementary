#include "../includes/lexer.h"
#include <aio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// In future we can create AST struct having ASTNode inside it, so
// that we have head and tail and don't have to rebuild broken connections
// Ok, I guess I have to now

// TODO:: Clean up list
// The ast malloc allocation
// All the ASTNodes allocations
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

// ast is initialized in parseCode function and will be freed after getting code
// in generate unit cause we also need to check for function existence and
// no-use kind of a error detection and optimization
AST *ast;
Token current_token;
bool mainEntered = false;

void nextNode(const char *code, int *const TK_Index) {
  current_token = getNextToken(code, TK_Index);
}

// Probably need conditional and loop paren parser, we will do that later

void parseLFuntionParenInternals(
    const char *code,
    int *const TK_Index) { // Its Label function paren internals,means when
                           // creating function
  // we gonna still pass from here to BracesInternals
  // where both function internal and scoped eleements will be
  // analyzed and with closing braces, it will return the node
  ASTNode *node = malloc(sizeof(ASTNode));

  if (current_token.type == Token_TypeKeyword) {

    // Looping until all parameters inside
    while (current_token.type == Token_TypeKeyword) {
      node->left = NULL;
      node->type = Token_TypeKeyword;
      strcpy(node->val, current_token.value);
    }

  } else {
    // error out with message
  }
};

void parseCFuntionParenInternals() { // Its Call function paren internals,means
                                     // when
                                     // calling function
  ASTNode *node = malloc(sizeof(ASTNode));
};

void parseExpressionParenInternals() { // Possibly by expression it means
                                       // loops and conditional
  ASTNode *node = malloc(sizeof(ASTNode));
};

void parseBracesInternals() { ASTNode *node = malloc(sizeof(ASTNode)); };

void parseAssignment(const char *code, int *const TK_Index) {
  ASTNode *node = malloc(sizeof(ASTNode));
};

ASTNode *parseTerm(const char *code, int *const TK_Index) {
  ASTNode *node = malloc(sizeof(ASTNode));

  if (current_token.type == Token_TypeKeyword) {

    ast->head = ast->tail = node;

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

    newNode1->left = ast->tail;
    ast->tail->right = newNode1;
    ast->tail = newNode1;

    nextNode(code, TK_Index);

    // newNode1->right = newNode2;

    strcpy(newNode2->val, current_token.value);
    newNode2->type = current_token.type;

    // Setting newNode1 label type either be functionLabel or identifier
    if (strcmp(newNode2->val, "(") == 0) {
      newNode1->type = Token_LabelKeyword;
      // Possibly checking in with parseLBracesInternal
      // TODO: Here some work is do be done possibly calling
      // parseLBracesInternal Function
      newNode2->left = ast->tail;
      ast->tail->right = newNode2;
      ast->tail = newNode2;

      nextNode(code, TK_Index);
      // Don't need to do below because we already have pointer to the newNode2
      // in [struct AST] ast tail
      // newNode2->right = parseLFuntionParenInternals(code, TK_Index);
      parseLFuntionParenInternals(code, TK_Index);

    } else if (strcmp(newNode2->val, "=") == 0) {
      newNode1->type = Token_Identifier;
      // will be returned from outer return statement
      // but need to pass to parseAssignment function to build whole
      // section code unit
      newNode2->left = ast->tail;
      ast->tail->right = newNode2;
      ast->tail = newNode2;

      nextNode(code, TK_Index);
      parseAssignment(code, TK_Index);
    }
  } else if (current_token.type == Token_Identifier) {
    // Here we see about assignment or whatever
  }

  return node;
};

ASTNode *parseCode(const char *code, int *const TK_Index) {
  ASTNode *node;

  if (current_token.type == Token_TypeKeyword) {
    // For function start or variable initialization

    // two type because we can even have global variable outside functions
    // int a = 1 + 2
    // int func1 (){}
    // So, chaining nodes up to third token
    ast = malloc(10000 * sizeof(size_t));
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
