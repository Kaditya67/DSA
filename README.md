# Data Structures & Algorithms (DSA) in C++

A comprehensive, beginner-to-advanced collection of classic Data Structures and Algorithms implemented from scratch in **C++**. This repository is organized as a clean reference for learning, revision, interview preparation, and college coursework.

---

## 📚 Topics & Implementations

### 1. Arrays & Searching
- **[`Array_ADT.cpp`](Array_ADT.cpp)**: Array Abstract Data Type (ADT) implementation supporting insertion, deletion, searching, traversal, and dynamic resizing.
- **[`Array_Operations.cpp`](Array_Operations.cpp)**: Common array manipulation operations including linear search, insertion at index, deletion, and display.
- **[`Binary_Search.cpp`](Binary_Search.cpp)**: Efficient $O(\log n)$ iterative and recursive binary search implementations on sorted arrays.

### 2. Linked Lists
- **[`Linkedlist.cpp`](Linkedlist.cpp)**: Singly linked list with node creation, traversal, insertion (at head, tail, or given index), deletion, reversing, and search.
- **[`Circular_Linkedlist.cpp`](Circular_Linkedlist.cpp)**: Circular singly linked list implementation handling head/tail pointer looping and cyclic traversal.
- **[`Double_LinkedList.cpp`](Double_LinkedList.cpp)**: Doubly linked list featuring bidirectional traversal with `next` and `prev` node pointers, bidirectional insertion, and deletion.

### 3. Stacks & Expressions
- **[`Stack_using_array.cpp`](Stack_using_array.cpp)**: Fixed-size LIFO stack implemented with sequential memory, complete with `push`, `pop`, `peek`, `isEmpty`, and `isFull` checks.
- **[`Stack_using_linkedlist.cpp`](Stack_using_linkedlist.cpp)**: Dynamic linked list implementation of a stack supporting unbounded growth without fixed capacity limits.
- **[`Parenthesis_Matching.cpp`](Parenthesis_Matching.cpp)**: Balanced parenthesis validator checking single bracket types `()` using stack push/pop operations.
- **[`Multi_Parenthesis_Matching.cpp`](Multi_Parenthesis_Matching.cpp)**: Multi-bracket balanced symbol verification supporting `()`, `{}`, and `[]`.
- **[`InfixToPostfix.cpp`](InfixToPostfix.cpp)**: Infix to postfix expression conversion implementing operator precedence and associativity via stack.

### 4. Queues
- **[`Queue_using_Array.cpp`](Queue_using_Array.cpp)**: Linear FIFO queue using array buffer with `enqueue`, `dequeue`, front, and rear tracking.
- **[`CircularQueue_using_Array.cpp`](CircularQueue_using_Array.cpp)**: Circular queue overcoming memory waste of linear queues via modulo arithmetic wrap-around index management.
- **[`Queue_using_LinkedList.cpp`](Queue_using_LinkedList.cpp)**: Dynamic queue implementation using singly linked list nodes for $O(1)$ enqueue and dequeue operations.

---

## 🛠️ Prerequisites

To compile and run the code, you need a C++ compiler supporting C++11 or newer:
- **GCC / G++** (`g++`) on Linux / MinGW on Windows
- **Clang** (`clang++`) on macOS / Linux
- **MSVC** on Windows (via Visual Studio Developer Command Prompt)

Verify your compiler installation:
```bash
g++ --version
```

---

## 🚀 How to Compile and Run

Each file is self-contained with its own `main()` function demonstration.

### On Windows (PowerShell / Command Prompt)
```powershell
# Example: Compile and run Binary Search
g++ -std=c++11 Binary_Search.cpp -o Binary_Search.exe
.\Binary_Search.exe

# Example: Compile and run Linked List
g++ -std=c++11 Linkedlist.cpp -o Linkedlist.exe
.\Linkedlist.exe
```

### On Linux / macOS (Terminal)
```bash
# Example: Compile and run Infix to Postfix
g++ -std=c++11 InfixToPostfix.cpp -o InfixToPostfix
./InfixToPostfix
```

---

## 💡 Complexity Overview

| Data Structure / Operation | Access | Search | Insertion | Deletion |
| :--- | :---: | :---: | :---: | :---: |
| **Array** | $O(1)$ | $O(n)$ | $O(n)$ | $O(n)$ |
| **Binary Search (Sorted Array)** | - | $O(\log n)$ | - | - |
| **Singly Linked List** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Doubly Linked List** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Stack (Array / Linked List)** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |
| **Queue (Array / Linked List)** | $O(n)$ | $O(n)$ | $O(1)$ | $O(1)$ |

---

## 🤝 Contributing & Learning

1. Star or fork the repository.
2. Pick any file to run and inspect how pointers, memory allocation, and data flow operate.
3. Test edge cases (e.g. empty lists, single elements, full queues) to deepen your understanding.
