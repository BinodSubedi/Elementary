#include "../includes/lexer.h"
#include <aio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In future we can create AST struct having ASTNode inside it, so
// that we have head and tail and don't have to rebuild broken connections
// Ok, I guess I have to do that now

// TODO:: Clean up list
// 1.) The ast malloc allocation
// 2.) All the ASTNodes allocations
// 3.) Make be create a node initialization function
//
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
// We need to do the same for variable as we don't want to create duplicates
AST *ast;
Token current_token;
bool mainEntered = false;

void nextNode(const char *code, int *const TK_Index) {
  current_token = getNextToken(code, TK_Index);
}

// we will do this later, first let's see if everthing initially works or not
void parseCFuntionParenInternals() { // Its Call function paren internals,means
                                     // when
                                     // calling function
  ASTNode *node = malloc(sizeof(ASTNode));
};

//************************************************

void parseExpressionParenInternals(
    const char *code, int *const TK_Index, ASTNode *chainedNode,
    ASTNode *latestNode) { // like with int a = (2+3/3)/3, here in
  // char parenStack[33] = "";
  //
  // int headIdx = 32;
  // parenStack[headIdx--] = '(';
  nextNode(code, TK_Index);
  while (current_token.type != Token_RParen) {

    if (current_token.type == Token_LParen) {
      parseExpressionParenInternals(code, TK_Index, chainedNode, latestNode);
    } else if (current_token.type == Token_Number ||
               strchr("+-*", current_token.value[0])) {

      // Just append to the chained node

    } else if (strchr("/", current_token.value[0])) {
      // here we are saving time and just operate on the item as soon as we see
      // divide

      nextNode(code, TK_Index);
      if (current_token.type == Token_Number) {

        char *endptr;

        int divider = strtol(current_token.value, &endptr, 10);
        int divisor = strtol(latestNode->val, &endptr, 10);

        if (*endptr == '\0') {
          int finalVal = divisor / divider;
          snprintf(latestNode->val, sizeof(latestNode->val), "%d", finalVal);
        }

      } else {
        // throw out error
      }

    } else if (current_token.type == Token_RParen) {

      // here chain through every node and first find divide and then multiply
      // step wise
    }
  }

  ASTNode *node = malloc(sizeof(ASTNode));
};

void parseAssignment(const char *code, int *const TK_Index) {
  // we will mantain a node chain
  // but wont connect to main ast tree until we simplify all expression to
  // + and -
  // DONOT FORGET to conncect to main ast tree

  // best approach here seems like tower of hanoi or something, at least use of
  // stack to figure out processing

  ASTNode *node = malloc(sizeof(ASTNode));
  ASTNode *latestNode;

  // Here I probably have to check up with presence of bracket and
  // step by step simplify / and * expression into just + and - expression

  while (current_token.type != Token_SemiColon) {

    if (current_token.type == Token_LParen) {
      parseExpressionParenInternals(code, TK_Index, node, latestNode);
    } else if (current_token.type == Token_Number ||
               current_token.type == Token_Operator) {
      // Just append to the chain node and finally out of while loop
      // do the divide first and multiply second, step wise
    }
  }

  /*
  if (current_token.type == Token_LParen) {
    nextNode(code, TK_Index);

  } else if (current_token.type == Token_Number) {

    //

  } else if (current_token.type == Token_String) {
    // concate String
  }

  // after checking everything

  if (current_token.type == Token_SemiColon) {
    nextNode(code, TK_Index);

  } else {
    // error, code line not ended here
  }
  */
};

//************************************************

/*
void parseBracesInternals(const char *code, int *const TK_Index) {

  ASTNode *node = malloc(sizeof(ASTNode));
};
*/

// Probably need conditional and loop paren parser, we will do that later

void parseLFuntionParenInternals(
    const char *code,
    int *const TK_Index) { // Its Label function paren internals,means when
                           // creating function
  // we gonna still pass from here to BracesInternals
  // where both function internal and scoped eleements will be
  // analyzed and with closing braces, it will return the node

  if (current_token.type == Token_TypeKeyword) {

    // Looping until all parameters inside
    while (current_token.type == Token_TypeKeyword) {
      nextNode(code, TK_Index);
      if (current_token.type == Token_Identifier) {
        ASTNode *node = malloc(sizeof(ASTNode));
        node->right = NULL;
        node->type = Token_TypeKeyword;
        strcpy(node->val, current_token.value);

        node->left = ast->tail;
        ast->tail->right = node;
        ast->tail = node;
        nextNode(code, TK_Index);
        if (current_token.type == Token_Comma) {
          // ignore comma
          nextNode(code, TK_Index);
        } else if (current_token.type == Token_RParen) {
          nextNode(code, TK_Index);
          if (current_token.type == Token_LBraces) {

            nextNode(code, TK_Index);

          } else {

            // Error out here, expected curly braces
          }
        } else {
          // Error out because here something went wrong
        }
      }
    }

  } else {
    // error out with message
  }
};

ASTNode *parseTerm(const char *code, int *const TK_Index) {
  ASTNode *node = malloc(sizeof(ASTNode));

  if (current_token.type == Token_TypeKeyword) {

    ast->head = ast->tail = node;

    node->type = Token_TypeKeyword;
    strcpy(node->val, current_token.value);

    node->left = node->right = NULL;

    nextNode(code, TK_Index);

    ASTNode *newNode = malloc(
        sizeof(ASTNode)); // for filtering between identifier and LabelKeyword

    newNode->left = newNode->right = NULL; // Just initializing with null

    strcpy(newNode->val, current_token.value);

    newNode->left = ast->tail;
    ast->tail->right = newNode;
    ast->tail = newNode;

    nextNode(code, TK_Index);

    // Setting newNode label type either be functionLabel or identifier
    // By the way, we ignore the token "(" or "=" cause we are only using them
    // to properly identify function labels or normal variable name
    if (strcmp(current_token.value, "(") == 0) {
      newNode->type = Token_LabelKeyword;
      // Possibly checking in with parseLBracesInternal
      // TODO: Here some work is do be done possibly calling
      // parseLBracesInternal Function

      nextNode(code, TK_Index);
      // Don't need to do below because we already have pointer to the newNode2
      // in [struct AST] ast tail
      // newNode2->right = parseLFuntionParenInternals(code, TK_Index);
      parseLFuntionParenInternals(code, TK_Index);
      // after calling this, we can run parseTerm again
      parseTerm(code, TK_Index);

    } else if (strcmp(current_token.value, "=") == 0) {
      newNode->type = Token_Identifier;
      // will be returned from outer return statement
      // but need to pass to parseAssignment function to build whole
      // section code unit

      nextNode(code, TK_Index);
      parseAssignment(code, TK_Index);
      parseTerm(code, TK_Index);
    }
  } else if (current_token.type == Token_Identifier) {
    // Here we see about assignment or whatever

    node->type = Token_Identifier;
    node->right = NULL;
    strcpy(node->val, current_token.value);
    node->left = ast->tail;
    ast->tail = node;
    nextNode(code, TK_Index);

    if (strcmp(current_token.value, "=") == 0) {

      // pass to parseAssignment function which will handle assignment and
      // possibly will call this function again
      nextNode(code, TK_Index);
      parseAssignment(code, TK_Index);
      // data will be assigned here and will call parseTerm again so,
      // if same assignment situation comes again and again it will do recursion
      // calls else checks other option and when reached Token_EOF, it returns
      parseTerm(code, TK_Index);

    } else {
      // throw error cause if not =, token doesnot make sense
    }
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
    ast = malloc(10000 * (sizeof(size_t) * 2));
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
