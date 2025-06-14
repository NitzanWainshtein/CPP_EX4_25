# CPP_EX4_25

**Author:** Nitzan Wainshtein       
**ID:** 209086263    
**Email:** Nitzanwa@gmail.com    
**Github repo:** https://github.com/NitzanWainshtein/CPP_EX4_25
 

##  Overview

MyContainer is a generic template-based container class that supports any comparable type (int, double, string, etc.) and provides six different iteration patterns. The container allows dynamic addition and removal of elements while maintaining various traversal orders through specialized iterators.

##  Core Operations

MyContainer provides the following basic operations:
- `add(element)` - Add an element to the container
- `remove(element)` - Remove all occurrences of an element from the container
- `size()` - Get the number of elements in the container
- `empty()` - Check if the container is empty
- Stream output operator (`<<`) - Print container contents in a readable format

##  Project Structure

```
CPP_EX4_25/
├── Makefile                    # Build configuration
├── README.md                   # Project documentation
├── include/
│   ├── MyContainer.hpp         # Main container implementation
│   └── doctest.h              # Testing framework
└── src/
    ├── Demo.cpp               # Demonstration program
    └── tests/
        └── test.cpp           # Unit tests
```

##  Prerequisites

### Installation (Ubuntu/Debian)
```bash
sudo apt-get update
sudo apt-get install build-essential g++ valgrind make
```

##  Building and Running

### Available Commands

| Command | Description |
|---------|-------------|
| `make Main` | Compile and run demonstration program |
| `make test` | Compile and run unit tests |
| `make valgrind` | Run demo with memory leak detection |
| `make valgrind-test` | Run tests with memory leak detection |
| `make clean` | Remove all build artifacts |

### Usage Examples: Working with Different Types
```cpp
// String container
MyContainer<std::string> stringContainer;
stringContainer.add("apple");
stringContainer.add("banana");

// Double container
MyContainer<double> doubleContainer;
doubleContainer.add(3.14);
doubleContainer.add(2.71);
```

##  Iterator Types

MyContainer provides six different iteration patterns:

### 1. AscendingOrder - Smallest to largest
```
Input:  [7, 15, 6, 1, 2] → Output: 1, 2, 6, 7, 15
```

### 2. DescendingOrder - Largest to smallest
```
Input:  [7, 15, 6, 1, 2] → Output: 15, 7, 6, 2, 1
```

### 3. SideCrossOrder - Alternating smallest/largest
```
Input:  [7, 15, 6, 1, 2] → Output: 1, 15, 2, 7, 6
```

### 4. ReverseOrder - Reverse insertion order
```
Input:  [7, 15, 6, 1, 2] → Output: 2, 1, 6, 15, 7
```

### 5. Order - Natural insertion order
```
Input:  [7, 15, 6, 1, 2] → Output: 7, 15, 6, 1, 2
```

### 6. MiddleOutOrder - Middle, then alternating left-right
```
Input:  [7, 15, 6, 1, 2] → Output: 6, 15, 1, 7, 2
```

### Iterator Usage Example
```cpp
MyContainer<int> container;
container.add(7);
container.add(15);
container.add(6);

// Use different iteration patterns
for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
    std::cout << *it << " ";  // Output: 6 7 15
}

for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
    std::cout << *it << " ";  // Output: 15 7 6
}
```

##  Features

- **Generic Template Design** - Works with any comparable type
- **Multiple Iterator Patterns** - Six different traversal methods
- **Memory Safe** - RAII-based design with automatic memory management
- **Exception Safety** - Proper error handling with descriptive messages
- **Copy Operations** - Full support for copy constructor and assignment operator
- **Default Template Parameter** - MyContainer<> defaults to int type

##  Quality Assurance
- **Zero Memory Leaks** - Verified with Valgrind
- **100% Test Coverage** - All functionality tested
- **Multiple Type Support** - Tested with int, string, double, and char types
- **Edge Case Handling** - Empty containers, single elements, and duplicate removal
- **Iterator Consistency** - Both prefix (++it) and postfix (it++) operators supported