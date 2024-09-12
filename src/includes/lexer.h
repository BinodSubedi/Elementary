#ifndef Lexer
#define Lexer

typedef enum {
  Token_Identifier,  // Variable Name
  Token_TypeKeyword, // Like int, String, print
  Token_FunctionKeyword,
  Token_Number,
  Token_String,
  Token_Operator,
  Token_Assign,
  Token_LParen,
  Token_RightParen,
  Token_LBraces,
  Token_RBraces,
  Token_SemiColon,
  Token_LineEnd // \n
} TokenType;

typedef struct {
  TokenType type;
  char value[16];
} Token;

Token getNextToken(const char *code, int *const TK_Index);

#endif // !Lexer
