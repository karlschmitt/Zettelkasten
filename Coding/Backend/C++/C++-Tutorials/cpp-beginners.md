# C++ Tutorial for Absolute Beginners

## 1. What Is C++?

C++ is a powerful programming language used for:

- Desktop applications
- Games
- Operating systems
- Embedded systems
- High-performance software
- Competitive programming

C++ programs are compiled. A compiler converts your source code into a program the computer can execute.

---

## 2. Installing C++

On Windows, install one of these:

- Visual Studio Community
- MinGW-w64
- MSYS2

With Visual Studio Code, you also need:

1. A C++ compiler
2. The Microsoft C/C++ extension
3. A terminal for compiling programs

Check whether a compiler is installed:

```powershell
g++ --version
```

---

## 3. Your First Program

Create a file named `main.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, world!\n";
    return 0;
}
```

Compile it:

```powershell
g++ main.cpp -o main.exe
```

Run it:

```powershell
.\main.exe
```

### Explanation

```cpp
#include <iostream>
```

Includes the library used for input and output.

```cpp
int main()
```

Defines the starting point of the program.

```cpp
std::cout
```

Prints text to the screen.

```cpp
return 0;
```

Indicates that the program finished successfully.

Every C++ statement usually ends with a semicolon:

```cpp
std::cout << "Text";
```

---

## 4. Comments

Comments are ignored by the compiler.

```cpp
// This is a single-line comment

/*
   This is a
   multi-line comment
*/
```

Use comments to explain why code exists, not what obvious code does.

---

## 5. Variables and Data Types

A variable stores a value.

```cpp
int age = 25;
double price = 19.99;
char grade = 'A';
bool isOpen = true;
std::string name = "Alex";
```

For `std::string`, include the string library:

```cpp
#include <string>
```

### Common Types

| Type | Purpose | Example |
|---|---|---|
| `int` | Whole numbers | `42` |
| `double` | Decimal numbers | `3.14` |
| `char` | One character | `'A'` |
| `bool` | True or false | `true` |
| `std::string` | Text | `"Hello"` |

Example:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string name = "Sam";
    int age = 20;

    std::cout << name << " is " << age << " years old.\n";
}
```

Use `const` when a value should not change:

```cpp
const double PI = 3.14159;
```

---

## 6. Input from the User

Use `std::cin` to read input.

```cpp
#include <iostream>

int main() {
    int age;

    std::cout << "Enter your age: ";
    std::cin >> age;

    std::cout << "You are " << age << " years old.\n";
}
```

For text containing spaces, use `std::getline`:

```cpp
#include <iostream>
#include <string>

int main() {
    std::string fullName;

    std::cout << "Enter your full name: ";
    std::getline(std::cin, fullName);

    std::cout << "Hello, " << fullName << "!\n";
}
```

---

## 7. Operators

### Arithmetic Operators

```cpp
int a = 10;
int b = 3;

std::cout << a + b << '\n';
std::cout << a - b << '\n';
std::cout << a * b << '\n';
std::cout << a / b << '\n';
std::cout << a % b << '\n';
```

`%` returns the remainder.

```cpp
10 % 3  // 1
```

### Comparison Operators

```cpp
a == b  // Equal
a != b  // Not equal
a > b   // Greater than
a < b   // Less than
a >= b  // Greater than or equal
a <= b  // Less than or equal
```

### Logical Operators

```cpp
condition1 && condition2  // AND
condition1 || condition2  // OR
!condition                // NOT
```

---

## 8. Conditional Statements

Use `if`, `else if`, and `else` to make decisions.

```cpp
#include <iostream>

int main() {
    int age;

    std::cout << "Enter your age: ";
    std::cin >> age;

    if (age >= 18) {
        std::cout << "Adult\n";
    } else {
        std::cout << "Minor\n";
    }
}
```

### Multiple Conditions

```cpp
int score = 85;

if (score >= 90) {
    std::cout << "A\n";
} else if (score >= 80) {
    std::cout << "B\n";
} else {
    std::cout << "Needs improvement\n";
}
```

---

## 9. Loops

Loops repeat code.

### `for` Loop

Use a `for` loop when you know how many repetitions are needed.

```cpp
for (int i = 1; i <= 5; i++) {
    std::cout << i << '\n';
}
```

Output:

```text
1
2
3
4
5
```

### `while` Loop

Use a `while` loop while a condition remains true.

```cpp
int count = 1;

while (count <= 5) {
    std::cout << count << '\n';
    count++;
}
```

### `do-while` Loop

A `do-while` loop always runs at least once.

```cpp
int number;

do {
    std::cout << "Enter a positive number: ";
    std::cin >> number;
} while (number <= 0);
```

---

## 10. Functions

Functions group reusable code.

```cpp
#include <iostream>

void sayHello() {
    std::cout << "Hello!\n";
}

int main() {
    sayHello();
    sayHello();
}
```

A function can accept parameters:

```cpp
void greet(std::string name) {
    std::cout << "Hello, " << name << "!\n";
}
```

A function can return a value:

```cpp
int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(3, 4);
    std::cout << result << '\n';
}
```

### Function Structure

```cpp
returnType functionName(parameters) {
    // body
    return value;
}
```

---

## 11. Arrays and Vectors

An array stores multiple values of the same type.

```cpp
int numbers[3] = {10, 20, 30};

std::cout << numbers[0] << '\n';
```

Indexes start at zero:

```text
numbers[0] is the first item
numbers[1] is the second item
numbers[2] is the third item
```

Modern C++ commonly uses `std::vector`:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {10, 20, 30};

    numbers.push_back(40);

    for (int number : numbers) {
        std::cout << number << '\n';
    }
}
```

Useful vector operations:

```cpp
numbers.size();       // Number of elements
numbers.push_back(5); // Add an element
numbers.pop_back();   // Remove the last element
numbers[0];           // Access an element
```

---

## 12. References

A reference is another name for an existing variable.

```cpp
int value = 10;
int& reference = value;

reference = 20;

std::cout << value; // 20
```

References are useful when passing values to functions without copying them.

```cpp
void doubleValue(int& number) {
    number *= 2;
}

int main() {
    int value = 5;
    doubleValue(value);

    std::cout << value; // 10
}
```

Use `const` references when a function should read but not modify data:

```cpp
void printName(const std::string& name) {
    std::cout << name << '\n';
}
```

---

## 13. Classes and Objects

A class defines a custom type.

```cpp
#include <iostream>
#include <string>

class Person {
public:
    std::string name;
    int age;

    void introduce() {
        std::cout << "My name is " << name
                  << " and I am " << age << ".\n";
    }
};

int main() {
    Person person;

    person.name = "Taylor";
    person.age = 30;
    person.introduce();
}
```

### Constructor

A constructor initializes an object.

```cpp
class Person {
public:
    std::string name;
    int age;

    Person(std::string personName, int personAge) {
        name = personName;
        age = personAge;
    }
};
```

Use it like this:

```cpp
Person person("Taylor", 30);
```

### Encapsulation

Keep data private and provide public functions to access it.

```cpp
class BankAccount {
private:
    double balance = 0;

public:
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    double getBalance() const {
        return balance;
    }
};
```

---

## 14. Pointers

A pointer stores a memory address.

```cpp
int value = 42;
int* pointer = &value;

std::cout << value << '\n';
std::cout << *pointer << '\n';
```

Meaning:

- `&value` gets the address of `value`
- `pointer` stores that address
- `*pointer` accesses the value at that address

Pointers are important, but beginners should first become comfortable with variables, functions, vectors, and references.

---

## 15. File Input and Output

Write to a file:

```cpp
#include <fstream>

int main() {
    std::ofstream file("output.txt");

    file << "This text is saved in a file.\n";
}
```

Read from a file:

```cpp
#include <fstream>
#include <iostream>
#include <string>

int main() {
    std::ifstream file("output.txt");
    std::string line;

    while (std::getline(file, line)) {
        std::cout << line << '\n';
    }
}
```

---

## 16. Error Handling

Exceptions handle unexpected problems.

```cpp
#include <iostream>
#include <stdexcept>

int divide(int a, int b) {
    if (b == 0) {
        throw std::runtime_error("Cannot divide by zero");
    }

    return a / b;
}

int main() {
    try {
        std::cout << divide(10, 0);
    } catch (const std::exception& error) {
        std::cout << "Error: " << error.what() << '\n';
    }
}
```

---

## 17. A Complete Beginner Project

This program calculates the average of several numbers.

```cpp
#include <iostream>
#include <vector>

int main() {
    int count;
    double total = 0;

    std::cout << "How many numbers? ";
    std::cin >> count;

    if (count <= 0) {
        std::cout << "The count must be positive.\n";
        return 1;
    }

    std::vector<double> numbers;

    for (int i = 0; i < count; i++) {
        double number;

        std::cout << "Enter number " << i + 1 << ": ";
        std::cin >> number;

        numbers.push_back(number);
        total += number;
    }

    double average = total / numbers.size();

    std::cout << "Average: " << average << '\n';
}
```

Compile and run:

```powershell
g++ main.cpp -std=c++17 -Wall -Wextra -o main.exe
.\main.exe
```

Compiler options:

- `-std=c++17` enables C++17
- `-Wall` enables common warnings
- `-Wextra` enables additional warnings

---

## 18. Beginner Practice Exercises

1. Print your name, age, and favorite color.
2. Create a calculator for two numbers.
3. Determine whether a number is even or odd.
4. Print numbers from 1 to 100.
5. Find the largest value in a vector.
6. Create a number-guessing game.
7. Create a simple bank account class.
8. Read a text file and count its lines.
9. Create a to-do list using a vector.
10. Build a menu-driven console application.

---

## 19. Recommended Learning Order

Study these topics in order:

1. Syntax and program structure
2. Variables and data types
3. Input and output
4. Operators
5. Conditions
6. Loops
7. Functions
8. Vectors and strings
9. References
10. Classes
11. Pointers
12. File handling
13. Standard Library algorithms
14. Larger projects

The best way to learn C++ is to write small programs regularly, compile them, read compiler errors, and improve them.
