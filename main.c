// Simple C Compiler for Arithmetic operations

// import libraries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// First component of the compiler
// Enumeration for different types of tokens
typedef enum
{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_END
} TokenType;

// Structure to represent a certain token
typedef struct
{
    TokenType type;
    int value;
} Token;

// Function to tokenize the input string
Token *tokenize(const char *input)
{
    Token *tokens = malloc(256 * sizeof(Token));
    int pos = 0;

    // Loop through the input string
    while (*input)
    {
        if (isdigit(*input))
        {
            tokens[pos].type = TOKEN_NUMBER;
            // Converting the string to long data
            tokens[pos].value = strol(input, (char **)&input, 10);
            pos++;
        }
        else if (*input == '+')
        {
            tokens[pos].type = TOKEN_PLUS;
            input++;
            pos++;
        }
        else if (*input == '-')
        {
            tokens[pos].type = TOKEN_PLUS;
            input++;
            pos++;
        }
        else
        {
            // Skip any other charecter (spaces)
            input++;
        }
    }
    // Mark the end of the token
    tokens[pos].type = TOKEN_END;
    return tokens;
}