#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

// Define the types of tokens we expect
enum TokenType {
    INTEGER,
    PLUS,
    MINUS,
    END_OF_FILE
};

// Structure to hold token data
struct Token {
    TokenType type;
    string value;
};

class Tokenizer {
private:
    string input;
    size_t pos;

public:
    Tokenizer(string text) : input(text), pos(0) {}

    // Function to skip whitespace characters
    void skipWhitespace() {
        while (pos < input.length() && isspace(input[pos])) {
            pos++;
        }
    }

    // Function to handle multi-digit integers
    string getInteger() {
        string result = "";
        while (pos < input.length() && isdigit(input[pos])) {
            result += input[pos];
            pos++;
        }
        return result;
    }

    // Main function to get the next token
    Token getNextToken() {
        skipWhitespace();

        if (pos >= input.length()) {
            return {END_OF_FILE, ""};
        }

        char currentChar = input[pos];

        // Identify Numbers
        if (isdigit(currentChar)) {
            return {INTEGER, getInteger()};
        }

        // Identify Plus Operator
        if (currentChar == '+') {
            pos++;
            return {PLUS, "+"};
        }

        // Identify Minus Operator
        if (currentChar == '-') {
            pos++;
            return {MINUS, "-"};
        }

        // Handle Unknown Characters
        pos++;
        return {END_OF_FILE, "UNKNOWN"};
    }
};

int main() {
    string expression = "150 + 25 - 10";
    cout << "Tokenizing expression: " << expression << endl << endl;

    Tokenizer lexer(expression);
    Token token;

    cout << "TOKENS FOUND:" << endl;
    cout << "------------------------" << endl;
    
    do {
        token = lexer.getNextToken();
        
        string typeStr;
        switch (token.type) {
            case INTEGER:     typeStr = "INTEGER "; break;
            case PLUS:        typeStr = "PLUS    "; break;
            case MINUS:       typeStr = "MINUS   "; break;
            case END_OF_FILE: typeStr = "EOF     "; break;
        }

        if (token.type != END_OF_FILE) {
            cout << "Type: " << typeStr << " | Value: " << token.value << endl;
        }

    } while (token.type != END_OF_FILE);

    return 0;
}