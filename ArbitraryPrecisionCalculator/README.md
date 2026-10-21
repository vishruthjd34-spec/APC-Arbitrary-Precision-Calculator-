# 🧮 Arbitrary Precision Calculator in C

A command-line calculator that performs **addition, subtraction, multiplication and division on integers of virtually unlimited size** — far beyond what `int` or even `long long` can hold.

![Language](https://img.shields.io/badge/Language-C-blue)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20WSL-lightgrey)
![Data Structure](https://img.shields.io/badge/Data%20Structure-Doubly%20Linked%20List-green)

---

## 📖 About

A normal `int` overflows at about 2 billion and `unsigned long long` at about 18 quintillion. This project removes that limit by storing every number as a **doubly linked list where each node holds one digit**. Arithmetic is then done digit by digit, exactly the way you learned it on paper — carry for addition and multiplication, borrow for subtraction, and repeated subtraction for division.

It was built to practise core C and data-structure concepts: **doubly linked lists, dynamic memory (`malloc` / `free`), command-line arguments, string handling** and **modular programming** (multiple `.c` / `.h` files).

---

## 💡 How a Number Is Stored

Each digit lives in its own node, with links in both directions so we can walk from the last digit to the first (needed for carry / borrow):

```
 "9087"

 NULL ◄── [9] ◄──► [0] ◄──► [8] ◄──► [7] ──► NULL
          head                       tail
```

For addition, the program starts from the **tails** of both lists, adds digits with the carry, and builds the result by inserting each new digit at the **front** of the result list.

```
   9 0 8 7
 +   1 2 3
 ---------
   9 2 1 0
```

---

## ✨ Features

| | Feature | Description |
|---|---|---|
| ➕ | **Addition** | Digit-by-digit addition with carry |
| ➖ | **Subtraction** | Digit-by-digit subtraction with borrow |
| ✖️ | **Multiplication** | Long multiplication, adding shifted partial products |
| ➗ | **Division** | Long division using repeated subtraction (integer quotient) |
| ➖➕ | **Negative numbers** | Sign of both operands and of the result is handled automatically |
| 🧹 | **Leading zeros removed** | `007` is treated as `7`, and results never show extra zeros |
| 🚫 | **Divide-by-zero check** | Prints an error instead of crashing |
| ♾️ | **No size limit** | Limited only by available memory |

---

## 🗂️ Project Structure

```
ArbitraryPrecisionCalculator/
├── main.c        # 🚪 Entry point — reads arguments, handles signs, calls the operation
├── apc.h         # 📐 Node structure, macros and all function declarations
├── apc.c         # 🧰 List helpers: create, insert, delete, print, compare, validate
├── add.c         # ➕ addition()
├── sub.c         # ➖ subtraction()
├── mul.c         # ✖️ multiplication()
├── div.c         # ➗ division()
├── Makefile      # 🔧 Build shortcuts
├── .gitignore    # 🙈 Ignores compiled binaries
└── README.md     # 📄 You are here
```

---

## 🧩 Data Structure

```c
typedef struct node
{
    struct node *prev;
    int data;              // one digit (0-9)
    struct node *next;
} node;
```

### 🧰 Helper functions (`apc.c`)

| Function | Purpose |
|---|---|
| `cla_validation()` | Checks that exactly 3 arguments were given |
| `create_list()` | Converts the digit string into a linked list |
| `insert_first()` / `insert_last()` | Add a digit at the front / back of a list |
| `delete_list()` | Frees every node of a list |
| `print_list()` | Prints the digits of a list |
| `compare_list()` | Finds which operand is larger (by length, then digit by digit) |
| `list_len()` | Counts the digits in a list |
| `remove_pre_zeros()` | Strips leading zeros |

---

## 🚀 Getting Started

### ✅ Prerequisites

- A C compiler such as **GCC**
- Linux, macOS, or Windows with **WSL / MinGW**

### 📥 Clone the repository

```bash
git clone https://github.com/<your-username>/<your-repo-name>.git
cd <your-repo-name>
```

### 🔧 Build

Using make:

```bash
make
```

Or directly with GCC:

```bash
gcc -Wall -o a.out main.c apc.c add.c sub.c mul.c div.c
```

### 🧹 Clean build files

```bash
make clean
```

---

## 🎮 How to Use

```bash
./a.out <operand1> <operator> <operand2>
```

| Operator | Operation |
|---|---|
| `+` | Addition |
| `-` | Subtraction |
| `x` or `X` | Multiplication |
| `/` | Division (integer quotient) |

> ⚠️ **Use `x`, not `*`, for multiplication.** In the terminal, `*` is expanded by the shell into file names before the program sees it. Writing `\*` also works.

Put a `-` in front of a number to make it negative, for example `-25`.

---

## 🖥️ Sample Run

```bash
./a.out 123 + 456
Result : 579

./a.out 99999999999999999999 + 1
Result : 100000000000000000000

./a.out 5 - 10
Result : -5

./a.out -5 - -3
Result : -2

./a.out 12345678901234567890 x 98765432109876543210
Result : 1219326311370217952237463801111263526900

./a.out 100 / 7
Result : 14

./a.out 12345678901234567890123 / 123
Result : 100371373180768844635

./a.out 5 / 0
Error: Division by zero
Result : 0

./a.out 1 2
./a.out operand1 operator operand2
```

All of the results above were checked against Python's built-in big integers.

---

## ⚙️ How Each Operation Works

| Operation | Method |
|---|---|
| **Addition** | Walk both lists from the tail, add the digits plus the carry, store `sum % 10`, carry `sum / 10` |
| **Subtraction** | Always subtract the smaller from the larger; borrow 10 when a digit is too small; the sign is decided in `main.c` |
| **Multiplication** | Multiply the first number by each digit of the second, shift each partial product by adding zeros, then add all partial products |
| **Division** | Bring down one digit at a time; subtract the divisor while the remainder is ≥ divisor; the number of subtractions is the next quotient digit |

### 🔀 Sign handling (in `main.c`)

| Expression | What happens |
|---|---|
| `a + b` (same signs) | Add, keep the sign |
| `a + b` (different signs) | Subtract smaller from larger; result takes the sign of the larger |
| `a - b` | Converted to addition or subtraction depending on both signs |
| `a x b`, `a / b` | Result is negative only if exactly one operand is negative |

---

## 🧠 Concepts Used

- 🔗 Doubly linked lists
- 🧮 Dynamic memory allocation: `malloc`, `free`
- 💻 Command-line arguments (`argc`, `argv`)
- 🔤 String to digit conversion (`ch - '0'`)
- ➕ Manual carry and borrow arithmetic
- 🧩 Modular code with multiple source and header files
- 🔁 Loops, `switch-case`

---

## ⚠️ Known Limitations

- Only **integers** are supported — there are no decimals, and division returns only the quotient (no remainder)
- Input is **not checked for non-digit characters** — something like `abc + 1` gives a meaningless result
- Invalid operators print `Invalid operator`, but a result line is still printed afterwards
- Division is done by repeated subtraction, so it becomes slow for very large quotients

---

## 🔮 Future Improvements

- [ ] ✅ Validate that operands contain only digits (and an optional leading `-`)
- [ ] 🧮 Support the remainder / modulo operator
- [ ] 🔢 Support decimal numbers
- [ ] ⚡ Faster multiplication (Karatsuba) and division
- [ ] 🧹 Free the operand and result lists before exiting
- [ ] 🔁 Interactive mode that keeps asking for expressions

---

## 👨‍💻 Author

**Vishruth J D**

---

⭐ If you found this project helpful, consider giving it a star on GitHub!
