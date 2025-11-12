##  Set Project — Data Structures (AVL & LLRB Trees)

**C implementation of a Set ADT using AVL and Left-Leaning Red-Black Trees**

###  Project Objective

This project implements the **Abstract Data Type (ADT) “Set”**, allowing users to manipulate integer collections — performing insertion, removal, membership checking, union, and intersection operations.

The distinctive aspect of this implementation is **data structure abstraction**: the user can choose, at runtime, between two **balanced tree implementations** to represent the set:

* **AVL Tree** (Height-balanced)
* **LLRB Tree** (Left-Leaning Red-Black Tree)

This design demonstrates modularity and performance comparison between two self-balancing binary search trees.

---

###  Implemented Functionalities

| Operation      | Description                                                |
| -------------- | ---------------------------------------------------------- |
| `Create`       | Creates a new set using the chosen structure (AVL or LLRB) |
| `Insert`       | Inserts an element into the set                            |
| `Remove`       | Removes a specific element                                 |
| `Belongs`      | Checks if an element exists in the set                     |
| `Union`        | Returns a new set containing all elements from A ∪ B       |
| `Intersection` | Returns a new set containing elements from A ∩ B           |
| `Print`        | Displays all elements of the set                           |

---

###  Project Structure

| File                      | Purpose                                           |
| ------------------------- | ------------------------------------------------- |
| `main.c`                  | Main program and user interface                   |
| `Conjunto.h / Conjunto.c` | ADT “Set” — interface between AVL and LLRB        |
| `AVL.h / AVL.c`           | Implementation of the AVL tree                    |
| `LLRB.h / LLRB.c`         | Implementation of the Left-Leaning Red-Black Tree |
| `Makefile`                | Automated build, run, and clean commands          |
| `*.in / *.out`            | Example input/output files for testing            |

---

###  Note on Language

> The codebase (variables, comments, and function names) was developed using **Portuguese**, following academic project requirements.
> However, this README and the Makefile are written in **English** for clarity and accessibility.

---

###  Compilation and Execution

#### 🔹 Option 1 — Using the Makefile (recommended)

If you’re on **Linux** or using **Cygwin** on Windows:

```bash
# Navigate to the project folder
cd path/to/project

# Compile all source files
make all

# Run the program
make run

# Clean and recompile
make clean
```

The resulting executable will be named **`main`**.

---

#### 🔹 Option 2 — Manual Compilation (without Makefile)

```bash
gcc Conjunto.c AVL.c LLRB.c main.c -o main -std=c99 -Wall
./main
```

---

###  How to Run

The program reads data from **standard input (stdin)** — either typed manually or redirected from a file.

To run using an input file:

```bash
./main < 1.in > output.txt
```

---

###  Input Format

The input file follows this structure:

```
type
nA
nB
elements_of_A
elements_of_B
option
[optional_element]
```

* `type` → `0` for AVL, `1` for LLRB
* `nA`, `nB` → number of elements in sets A and B
* `option`:

  * `1` → Check if element belongs to A
  * `2` → Union of A and B
  * `3` → Intersection of A and B
  * `4` → Remove an element from A

---

###  Example Inputs and Outputs

#### Example 1 — Membership Check

**Input (1.in):**

```
0 (will choose AVL data structure)
5 (5 elements in A)
3 (3 elements in B)
1 2 3 4 5 (insert the elements to A)
7 3 8 (insert the elements to B)
1 (option 1 that checks if an element is inside A)
2 (is 2 in A?)
```

**Output (1.out):**

```
Pertence(Belongs)
```

If the element was not present, the output would be:

```
Nao Pertence(Does not belong)
```

---

#### Example 2 — Union of Two Sets

**Input (2.in):**

```
1
5
3
1 2 3 4 5
7 2 8
2
```

**Output (2.out):**

```
1 2 3 4 5 7 8
```

---

###  Data Structures Overview

#### **AVL Tree**

An AVL tree is a **self-balancing binary search tree** where the height difference between subtrees is maintained at most 1.
Each node contains:

```c
struct no {
    int key;
    struct no *left, *right;
    int balanceFactor;
    int height;
};
```

All main operations (insert, remove, search) have time complexity **O(log n)**.

---

#### **LLRB Tree**

A Left-Leaning Red-Black Tree (LLRB) is a simplified implementation of red-black trees that maintains balance using **rotations and color flipping**.
Each node contains:

```c
struct no_ {
    int key;
    struct no_ *left, *right;
    int color; // 1 = Red, 0 = Black
};
```

The average complexity for operations is also **O(log n)**, but with fewer rotations than AVL.

---

###  Key Concepts Demonstrated

* Abstract Data Type (ADT)
* Encapsulation and Implementation Hiding
* Balanced Binary Search Trees (AVL and LLRB)
* Recursion and Tree Traversal
* Modular Programming and Memory Management
* Automated Compilation with Makefile

---

###  Testing

The repository includes input and output test files to verify all functionalities:

* `1.in / 1.out` → Membership check
* `2.in / 2.out` → Union
* `3.in / 3.out` → Intersection
* `4.in / 4.out` → Removal

To test:

```bash
./main < 2.in
```

---

###  Authors

This project was developed for the course **SCC0202 — Algorithms and Data Structures I**,
supervised by **Prof. Rudinei Goularte**.

Developed by:

* Wiltord N Mosingi
* Gabriel Demba

---

