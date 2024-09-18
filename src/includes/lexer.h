#ifndef Lexer
#define Lexer

typedef enum {
  Token_Identifier,      // Variable Name
  Token_TypeKeyword,     // Like int, u8
  Token_FunctionKeyword, // By function I mean internal elements like print,
                         // format, max, min etc
  Token_LabelKeyword, // Label means userCreated function name like add(1,2) or
  // similar

  Token_FunctionParam,
  Token_ReturnKeyword,
  Token_MainFunction,
  Token_Number,
  Token_String,
  Token_Operator,
  Token_Assign,
  Token_LParen,
  Token_RParen,
  Token_LBraces,
  Token_RBraces,
  Token_Comma,
  Token_SemiColon,
  Token_ExitCode,
  Token_LineEnd // \n
} TokenType;

typedef struct {
  TokenType type;
  char value[16];
} Token;

Token *getNextToken(const char *code, int *const TK_Index);

#endif // !Lexer
