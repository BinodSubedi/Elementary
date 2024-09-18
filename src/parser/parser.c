#include "../includes/parser.h"
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

// ast is initialized in parseCode function and will be freed after getting code
// in generate unit cause we also need to check for function existence and
// no-use kind of a error detection and optimization
// We need to do the same for variable as we don't want to create duplicates
AST *ast;
Token *current_token;
bool mainEntered = false;

const char *codeBlock;
int idxCode = 0;

void nextNode() {
  printf("is there somebody here\n");

  if (ast->head != NULL) {
    free(current_token);
  }

  current_token = getNextToken(codeBlock, &idxCode);
  printf("michael angelo\n");
}

ASTNode *createNode() {

  ASTNode *node = malloc(sizeof(ASTNode));

  node->left = node->right = NULL;

  if (ast->head == NULL || ast->tail == NULL) {
    ast->head = ast->tail = node;
  }

  return node;
};

// we will do this later, first let's see if everthing initially works or not
void parseCFuntionParenInternals() { // Its Call function paren internals,means
                                     // when
                                     // calling function
  ASTNode *node = malloc(sizeof(ASTNode));
};

//************************************************

void parseExpressionParenInternals(
    int *const TK_Index,
    ASTNode *latestNode) { // like with int a = (2+3/3)/3, here in
  //

  ASTNode *stackTopNode = latestNode;
  nextNode();
  while (current_token->type != Token_RParen) {

    if (current_token->type == Token_LParen) {
      parseExpressionParenInternals(TK_Index, latestNode);
    } else if (current_token->type == Token_Number ||
               strchr("+-*", current_token->value[0])) {

      // Just append to the chained node
      if (strcmp(latestNode->val, "start") != 0) {
        ASTNode *newNode = createNode();

        latestNode->right = newNode;
        newNode->left = latestNode;
        latestNode = newNode;
        strcpy(latestNode->val, current_token->value);
      }

      strcpy(latestNode->val, current_token->value);

    } else if (strchr("/", current_token->value[0])) {
      // here we are saving time and just operate on the item as soon as we see
      // divide

      nextNode();
      if (current_token->type == Token_Number) {

        char *endptr;

        int divider = strtol(current_token->value, &endptr, 10);
        int divisor = strtol(latestNode->val, &endptr, 10);

        if (*endptr == '\0') {
          int finalVal = divisor / divider;

          ASTNode *newNode = createNode();
          latestNode->right = newNode;
          newNode->left = latestNode;
          latestNode = newNode;
          snprintf(latestNode->val, sizeof(latestNode->val), "%d", finalVal);
        }

      } else {
        // throw out error
      }

    } else if (current_token->type == Token_RParen) {

      // here chain through every node and first find divide and then multiply
      // step wise
      //
      nextNode();

      ASTNode *loopingNode = stackTopNode->right;

      while (loopingNode->right != NULL) {
        if (strcmp(loopingNode->val, "/") == 0) {
          // srink 3 elements to first element and free other two astNode memory
          // allocation without creating reference after free error

          char *endChar;
          int neumerator = strtol(loopingNode->left->val, &endChar, 10);
          int denominator = strtol(loopingNode->right->val, &endChar, 10);

          if (*endChar == '\0') {

            int finalVal = neumerator / denominator;

            snprintf(latestNode->val, sizeof(loopingNode->left->val), "%d",
                     finalVal);

            loopingNode->left->right = loopingNode->right->right;
            loopingNode->right->right->left = loopingNode->left;

            ASTNode *replacenode = loopingNode->right->right;

            free(loopingNode->right);
            free(loopingNode);

            loopingNode = replacenode;
          }
        }

        loopingNode = loopingNode->right;
      }

      // For resetting to the top most node to do the multiplication operation
      loopingNode = stackTopNode->right;

      while (loopingNode->right != NULL) {
        if (strcmp(loopingNode->val, "*") == 0) {
          // srink 3 elements to first element and free other two astNode memory
          // allocation without creating reference after free error

          char *endChar;
          int neumerator = strtol(loopingNode->left->val, &endChar, 10);
          int denominator = strtol(loopingNode->right->val, &endChar, 10);

          if (*endChar == '\0') {

            int finalVal = neumerator * denominator;

            snprintf(latestNode->val, sizeof(loopingNode->left->val), "%d",
                     finalVal);

            loopingNode->left->right = loopingNode->right->right;
            loopingNode->right->right->left = loopingNode->left;

            ASTNode *replacenode = loopingNode->right->right;

            free(loopingNode->right);
            free(loopingNode);

            loopingNode = replacenode;
          }
        }
      }
    }

    // ASTNode *node = malloc(sizeof(ASTNode));
  }
};

void parseAssignment(int *const TK_Index) {
  // we will mantain a node chain
  // but wont connect to main ast tree until we simplify all expression to
  // + and -
  // DONOT FORGET to conncect to main ast tree

  // best approach here seems like tower of hanoi or something, at least use
  // of stack to figure out processing
  //

  ASTNode *node = malloc(sizeof(ASTNode));

  ast->tail->right = node;
  node->left = ast->tail;
  ast->tail = node;

  ASTNode *latestNode = node;

  latestNode->right = NULL;
  strcpy(latestNode->val, "start");

  // Here I probably have to check up with presence of bracket and
  // step by step simplify / and * expression into just + and - expression

  while (current_token->type != Token_SemiColon) {

    if (current_token->type == Token_LParen) {
      parseExpressionParenInternals(TK_Index, latestNode);
    } else if (current_token->type == Token_Number ||
               current_token->type == Token_Operator) {
      // Just append to the chain node

      if (strcmp(latestNode->val, "start") != 0) {

        ASTNode *newNode = createNode();

        newNode->left = latestNode;
        strcpy(newNode->val, current_token->value);
        latestNode->right = newNode;
      } else {

        printf("up here!!");

        strcpy(latestNode->val, current_token->value);
        printf("what is it::%s\n", current_token->value);
      }

      nextNode();
      printf("next node@@@@@@@::%s\n", current_token->value);
    }
  }

  // To skip semi-colon
  nextNode();
  printf("next node@@@@@@1::%s\n", current_token->value);

  // do the divide first and multiply second, step wise

  ASTNode *loopingNode = node;

  while (loopingNode->right != NULL) {
    if (strcmp(loopingNode->val, "/") == 0) {
      // srink 3 elements to first element and free other two astNode memory
      // allocation without creating reference after free error

      char *endChar;
      char *newEndChar;
      int neumerator = strtol(loopingNode->left->val, &endChar, 10);
      int denominator = strtol(loopingNode->right->val, &newEndChar, 10);

      if (*endChar == '\0' && *newEndChar == '\0') {

        int finalVal = neumerator / denominator;

        snprintf(latestNode->val, sizeof(loopingNode->left->val), "%d",
                 finalVal);

        loopingNode->left->right = loopingNode->right->right;
        loopingNode->right->right->left = loopingNode->left;

        ASTNode *replacenode = loopingNode->right->right;

        free(loopingNode->right);
        free(loopingNode);

        loopingNode = replacenode;
      }
    }

    loopingNode = loopingNode->right;
  }

  // For resetting to the top most node to do the multiplication operation
  loopingNode = node;

  while (loopingNode->right != NULL) {
    if (strcmp(loopingNode->val, "*") == 0) {
      // srink 3 elements to first element and free other two astNode memory
      // allocation without creating reference after free error

      char *endChar;
      char *newEndChar;
      int neumerator = strtol(loopingNode->left->val, &endChar, 10);
      int denominator = strtol(loopingNode->right->val, &newEndChar, 10);

      if (*endChar == '\0' && *newEndChar == '\0') {

        int finalVal = neumerator * denominator;

        snprintf(latestNode->val, sizeof(loopingNode->left->val), "%d",
                 finalVal);

        loopingNode->left->right = loopingNode->right->right;
        loopingNode->right->right->left = loopingNode->left;

        ASTNode *replacenode = loopingNode->right->right;

        free(loopingNode->right);
        free(loopingNode);

        loopingNode = replacenode;
      }
    }
  }

  printf("next node@@@@@@2::%s\n", current_token->value);

  //***************************
  /*
  if (current_token->type == Token_LParen) {
    nextNode();

  } else if (current_token->type == Token_Number) {

    //

  } else if (current_token->type == Token_String) {
    // concate String
  }

  // after checking everything

  if (current_token->type == Token_SemiColon) {
    nextNode();

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
    int *const TK_Index) { // Its Label function paren internals,means when
                           // creating function
  // we gonna still pass from here to BracesInternals
  // where both function internal and scoped eleements will be
  // analyzed and with closing braces, it will return the node

  if (current_token->type == Token_TypeKeyword) {

    // Looping until all parameters inside
    while (current_token->type == Token_TypeKeyword) {

      ASTNode *node = malloc(sizeof(ASTNode));
      node->right = NULL;
      node->type = Token_TypeKeyword;
      strcpy(node->val, current_token->value);

      node->left = ast->tail;
      ast->tail->right = node;
      ast->tail = node;

      nextNode();
      if (current_token->type == Token_Identifier) {
        printf("identifier\n");
        ASTNode *innerNode = malloc(sizeof(ASTNode));
        innerNode->right = NULL;
        innerNode->type = Token_FunctionParam;
        strcpy(innerNode->val, current_token->value);

        innerNode->left = ast->tail;
        ast->tail->right = innerNode;
        ast->tail = innerNode;

        printf("First node value::%s\n Second node value::%s\n", node->val,
               innerNode->val);

        nextNode();
        if (current_token->type == Token_Comma) {
          // ignore comma
          nextNode();
        } else if (current_token->type == Token_RParen) {

          nextNode();

        } else {
          // Error out because here something went wrong
        }
      }
    }

  } else if (current_token->type == Token_RParen) {

    nextNode();
  } else {
    // error
  }

  if (current_token->type == Token_LBraces) {

    // skipping ')' and '{'
    nextNode();

    printf("Left Braces-----");

  } else {
    // error out with message
  }
};

void parseTerm(int *TK_Index) {

  if (current_token == NULL) {
    return;
  }

  printf("current token------::%s\n", current_token->value);
  ASTNode *node = createNode();

  if (current_token->type == Token_TypeKeyword) {

    /*
    if (ast->tail == NULL) {
      ast->head = ast->tail = node;
    }
    */

    node->type = Token_TypeKeyword;
    strcpy(node->val, current_token->value);

    node->left = node->right = NULL;

    nextNode();

    ASTNode *newNode = malloc(
        sizeof(ASTNode)); // for filtering between identifier and LabelKeyword

    // newNode->left = newNode->right = NULL; // Just initializing with null

    strcpy(newNode->val, current_token->value);

    printf("function name::%s\n", newNode->val);

    // editing
    //
    node->right = newNode;

    // Just doing this becasuse we assigned the node while creating
    // in case there is NULL in ast head and tail
    if (ast->head != node) {
      node->left = ast->tail;
      ast->tail->right = node;
      ast->tail = node;
    }

    newNode->left = ast->tail;
    ast->tail->right = newNode;
    ast->tail = newNode;

    nextNode();

    // Setting newNode label type either be functionLabel or identifier
    // By the way, we ignore the token "(" or "=" cause we are only using them
    // to properly identify function labels or normal variable name
    if (strcmp(current_token->value, "(") == 0) {
      newNode->type = Token_LabelKeyword;
      // Possibly checking in with parseLBracesInternal
      // TODO: Here some work is do be done possibly calling
      // parseLBracesInternal Function

      nextNode();
      // Don't need to do below because we already have pointer to the
      // newNode2 in [struct AST] ast tail newNode2->right =
      // parseLFuntionParenInternals(code, TK_Index);
      printf("checking brackets\n");
      parseLFuntionParenInternals(TK_Index);
      // after calling this, we can run parseTerm again
      parseTerm(TK_Index);
      return;

    } else if (strcmp(current_token->value, "=") == 0) {
      newNode->type = Token_Identifier;
      // will be returned from outer return statement
      // but need to pass to parseAssignment function to build whole
      // section code unit
      nextNode();
      // error around here
      printf("here here\n");

      parseAssignment(TK_Index);
      parseTerm(TK_Index);
      return;
    }
  } else if (current_token->type == Token_Identifier) {
    // Here we see about assignment or whatever

    node->type = Token_Identifier;
    node->right = NULL;
    strcpy(node->val, current_token->value);
    node->left = ast->tail;
    ast->tail = node;
    nextNode();

    if (strcmp(current_token->value, "=") == 0) {

      // pass to parseAssignment function which will handle assignment and
      // possibly will call this function again
      nextNode();
      parseAssignment(TK_Index);
      // data will be assigned here and will call parseTerm again so,
      // if same assignment situation comes again and again it will do
      // recursion calls else checks other option and when reached Token_EOF,
      // it returns
      parseTerm(TK_Index);
      return;

    } else {
      // throw error cause if not =, token doesnot make sense
    }
  }
};

ASTNode *parseCode(const char *code) {
  ASTNode *node;

  codeBlock = code;

  // initializing

  // ast only has size for two pointer of machine size, cause right now it's
  // only storing two pointers those being head and tail
  ast = malloc(sizeof(AST));
  ast->head = NULL;
  ast->tail = NULL;

  nextNode();

  if (current_token->type == Token_TypeKeyword) {
    // For function start or variable initialization

    // two type because we can even have global variable outside functions
    // int a = 1 + 2
    // int func1 (){}
    // So, chaining nodes up to third token
    parseTerm(&idxCode);

  } else if (current_token->type ==
             Token_LBraces) { // May be I don't need it though cause we will
                              // always start in function
    // For shadowing variable, scope inside braces only
    // I will do this later
  } else if (current_token->type == Token_ExitCode) {
    // Probably don't need now for intial testing
  }

  ASTNode *looper = ast->head;

  while (looper != NULL) {
    printf("parser::::::\nThe node type issss::%d\nThe node value issss::%s\n",
           looper->type, looper->val);

    looper = looper->right;
  }
  return ast->head;
}
