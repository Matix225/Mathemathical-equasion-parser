# Mathemathical equasion parser

This project is a mathematical expression parser and evaluator written in C++, which converts standard infix expressions into Reverse Polish Notation (RPN / ONP) and evaluates them using a stack-based approach.
It supports arithmetic operations, parentheses, and unary negation, while also performing full syntax validation before evaluation.

---

## Features

- Tokenization of mathematical expressions
- Support for:
  - Addition `+`
  - Subtraction `-`
  - Multiplication `*`
  - Division `/`
  - Parentheses `()`
  - Unary negation (e.g. `-5`, `-(3+2)`)
- Syntax validation for incorrect expressions
- Conversion from infix notation to ONP (RPN)
- Evaluation using a stack-based algorithm
---

##  Example Usage
Enter equation: (2 + 3) * 4
20

Enter equation: -5 + 2 * (10 - 3)
9

---

##  How It Works

The program processes expressions in 3 main stages:
### 1. Tokenization
The input string is split into meaningful tokens:
- numbers (operands)
- operators
- parentheses
- unary minus (negation)

### 2. Syntax Validation
The parser checks:
- correct order of tokens
- matching parentheses
- invalid operator placement
- malformed expressions

### 3. Conversion to ONP (RPN)
Uses a stack-based algorithm (Shunting Yard algorithm) to convert infix notation into Reverse Polish Notation.

### 4. Evaluation
The ONP expression is evaluated using a stack:
- numbers are pushed onto the stack
- operators pop operands, compute results, and push back the result

---

## Technologies Used

- C++17
- STL (`vector`, `string`, `iostream`)

---

## License
This project is open-source and free to use for educational purposes.
