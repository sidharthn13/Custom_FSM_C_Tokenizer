# Custom Finite State Machine for tokenizing C programs:
## Table Of Contents:
1. [Introduction:](#Introduction)
2. [Features:](#Features)
3. [How To Use:](#How-To-Use)
4. [Design Of FSM:](#Design-Of-FSM)
## Introduction:
A tokenizer or a lexer is the first stage of compilation of a C program. It is a program that reads the source code and classifies lexemes or particular symbols into tokens. These tokens are then used by the following stages of compilation. The canonical approach to building a lexer is to use regular expression matching to generate tokens. The underlying principle behind regex matching is the use of Finite State Machines. 

This project does not use a regex library native to C programming. Instead a custom finite state machine has been implemented to generate tokens from a C source file. The primary objective in mind while this program was being written was to learn more about the tokenization process and learn how to create and manage states of an FSM to build a custom regex engine.
## Features:
- The current version is designed to handle errors when invalid symbols are read
- It generates the following types of tokens:
    1. Keywords
    2. Identifier
    3. Punctuators
    4. Numeric Constants
    5. String Constants
    6. Operators
- It generates an error message when invalid symbols are entered.
- It makes use of hashmaps for operator and keyword lookup and keeps track of the current and previous states of the FSM to perform lexeme printing and token assignment.
- The current version of the project -V1.0 does not support tokenizing of preprocessor directives and comments
## How To Use:
- Clone the repository (git clone link_to_repository)
- Compile the source files (gcc main.c FSM.c lookupTables.c)
- Run the executable file and provide path to the target C source file (./a.out src.c)

[A sample source C program](https://i.pinimg.com/736x/b2/84/c5/b284c5d492e6299a3bbe92a8a6cd604d.jpg)

[Using the tokenizer on sample file(1)](https://i.pinimg.com/736x/5f/4a/fd/5f4afddba3d7a77ff0f51b36dde39078.jpg)

[Using the tokenizer on sample file(2)](https://i.pinimg.com/736x/92/d8/0e/92d80ec30e43574c97380c09b9c85ebe.jpg)

- If no command line arguments are given at the time of running the executable file, or if invalid path is provided, the program will display the following error message and will terminate.

[File path is not provided](https://i.pinimg.com/736x/c5/ab/69/c5ab698886e325f6947cb6ed9e53c20e.jpg)
## Design Of FSM:
- The FSM keeps track of current state and previous state.
- The FSM is initialized with previous state and current state set to zero.
- Each state represents a specific lexical category (e.g., identifier, keyword, numeric constant, operator, etc.).
- The FSM transitions between states based on the input character read from the source file and the current state of the FSM.
- Transitions between states are determined by switch-case statements in the fsmUpdateState function.
- A loop is initialized and input character is read, based on the symbol and the current state, FSM states are updated. If the current state does not match the previous state, specific operation are done which includes printing lexeme and it corresponding token type(based on value of previous state), printing delimiting character(based on current state).
- The FSM provides error handling for invalid lexemes or symbols.

__The following table describes various states of the FSM:__

|     __Symbol__      |     __State__    |            __Description__            |
|-----------------|--------------|-----------------------------------|
|                 |      0       | Idle state. FSM returns to state 0 when it is reset. Set after encountering delimiting symbols or lexeme print operation is performed |
|       _         |      1       | Lexeme categorized as identifier  |
|  [A-Z], [a-z]   |     1,2      | Could be a keyword or identifier  |
|  punctuators    |      3       | Acts as delimiters and prints token for previous state |
|    numbers      |    2,4,8     | Could be a numeric constant, be part of a string(if current state is 8) or an identifier(if the current state is 2) |
|       .         |    5,6,8     | Could be part of a floating point number, part of a string(if current state is 8) or be an operator(if current state is not 4) |
|      +,-        |    6,7,8     | Could be an operator(if couldBeSignedInt flag = 0), be the sign of a number(if couldBeSignedInt flag = 1) or be part of a string(if current state =8) |
| other operators |     6,8      | Could be an operator or be part of a string(if current state = 8) |
|   \n,\t,\r," "  |     0,8      | Could be part of a string(if current state = 8). Otherwise acts as delimiting characters |
|   End Of File   |     100      | Marks the end of the C source file |
|     Others      |      9       | Signifies invalid symbol. Program throws an error and then terminates |
|Current State = 8|     -8       | This state is set to print the characters in string without adding to buffer. This is done to prevent buffer overflow errors in case the string is very long |
|Current State = 8|     -9       | This state is set to print the token type for string constants when a second " symbol is encountered |