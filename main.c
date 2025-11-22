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
            tokens[pos].value = strtol(input, (char **)&input, 10);
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

// Second component of the compiler
// parser definitions
// Functions to
// 1- Parse the tokens
// 2- Evaluate the expressions
int parse(Token *tokens, int *result)
{
    int pos = 0; // A
    if (tokens[pos].type != TOKEN_NUMBER)
    {
        return 0; // invalid expression
    }
    *result = tokens[pos].value;
    pos++;

    // Loop through the tokens and evaluate the expression
    while (tokens[pos].type != TOKEN_END)
    {
        if (tokens[pos].type == TOKEN_PLUS)
        {
            pos++;
            if (tokens[pos].type != TOKEN_NUMBER)
            {
                return 0;
            }

            *result += tokens[pos].value;
        }
        else if (tokens[pos].type == TOKEN_MINUS)
        {
            pos++;
            if (tokens[pos].type != TOKEN_NUMBER)
            {
                return 0;
            }
            *result -= tokens[pos].value;
        }
        else
        {
            //Invalid token
            return 0;
        }
        pos++;
    }
    return 1; //successfull parsing!!
}


// Third component of compiler
void generate_assembly(Token *tokens ){
    int pos = 0;
    // Load the first number -> register
    printf("Load %d\n" , tokens[pos].value);
    pos++;

    while (tokens[pos].type != TOKEN_END) 
    {
        if(tokens[pos].type == TOKEN_PLUS){
            pos++;
            printf("Add %d\n" , tokens[pos].value);
        }else if(tokens[pos].type == TOKEN_MINUS){
            pos++;
            printf("Sub %d\n" , tokens[pos].value);
        }
        pos++;
    }
    
}

// main function
int main(){
    // input string
    char input[256];
    printf("Enter an arithmetic expression (e.g. 5 + 4 - 3) : ");
    // Reading the input form the user
    fgets(input , sizeof(input) , stdin);

    // Removing newline charecter if exists
    size_t len = strlen(input);
    // condition
    if(len > 0 && input[len - 1] == '\n'){
        input[len - 1] = '\0';
    }

    // tokenize the input
    Token *tokens = tokenize(input);

    int result;

    if(parse(tokens , &result)){
        printf("Parsed result = %d\n" , result);
        // Generate the assembly-line instructions
        generate_assembly(tokens);
    }else {
        printf("Invalid Expression");
    }
    free(tokens);
    return 0;

}
