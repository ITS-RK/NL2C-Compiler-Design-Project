NL2C: A Natural Language to C Code Compiler

Overview
NL2C is a small source-to-source compiler that translates a controlled natural-language style input into C code. The project is built using Flex for lexical analysis, Bison for parsing, and C for semantic checking and code generation.

The system is designed to demonstrate how simple natural-language programming constructs can be recognized, validated, and converted into equivalent C programs.

Current Features
- Variable declarations for `integer` and `float`
- Assignments using `set <id> to <expression>`
- Arithmetic expressions with:
  - addition
  - subtraction
  - multiplication
  - division
  - parentheses
  - integer literals
  - float literals
- Type handling:
  - variable type tracking
  - expression type tracking
  - implicit `int` to `float` conversion in assignments
  - type mismatch reporting for invalid assignments
- Print statements using `print <expression>`
- Conditional statements:
  - `if ... then ... else ... end if`
  - nested `if`
- Loop statements:
  - `while ... do ... end while`
  - `for ... from ... to ... step ... do ... end for`
- Comparisons in conditions:
  - `greater than`
  - `less than`
  - `equals`
- Function support:
  - function definitions
  - parameters
  - `return` expressions
  - function calls inside expressions
  - nested function calls
- Code generation to C source files in the `output/` folder
- Basic semantic error detection:
  - undeclared variables
  - redeclaration
  - syntax errors
  - selected type errors

System Workflow
1. Lexical Analysis
   Flex reads the input program and converts keywords, identifiers, literals, and operators into tokens.

2. Parsing
   Bison checks whether the token stream matches the grammar rules of the NL2C language.

3. Semantic Checking
   The compiler performs basic checks such as variable lookup, redeclaration checking, and type compatibility.

4. Code Generation
   If the input is valid, the compiler writes the equivalent C code into a generated `.c` file inside the `output/` directory.

5. Error Handling
   If a syntax or semantic error is found, code generation is marked as failed and the output file is removed.

Project Files
- `nl2c.l` : Flex lexer specification
- `nl2c.y` : Bison parser, semantic logic, and C code generation
- `TestCases/` : sample valid, edge, and error test inputs
- `output/` : generated C files

Build Commands
Run these commands from the project root:

`bison -d nl2c.y`

`flex nl2c.l`

`gcc lex.yy.c nl2c.tab.c -o nl2c.exe`

Run the Compiler
To translate an input file:

`.\nl2c.exe TestCases\valid\T5_functions.txt`

Example output:

`output/T5_functions.c`

Compile Generated C Code
To compile a generated C file:

`gcc output\T5_functions.c -o output\T5_functions.exe`

Run the Generated Program
`.\output\T5_functions.exe`

Example Test Commands
- `.\nl2c.exe TestCases\valid\T12_mixed_all_features.txt`
- `.\nl2c.exe TestCases\edge\X2_nested_calls.txt`
- `.\nl2c.exe TestCases\error\E1_undeclared.txt`

Notes
- Each input file now generates its own output C file inside `output/`.
- The language is intentionally limited and controlled; it does not support unrestricted natural language.
- Function parameters and return values are currently treated as `int`.

Purpose
This project is suitable for compiler design coursework, Flex/Bison learning, and demonstrations of simple natural-language driven code generation into C.
