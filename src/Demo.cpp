// Nitzanwa@gmail.com

#include "MyContainer.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace ex4;

// Helper function to print section headers
void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "  " << title << std::endl;
    std::cout << std::string(60, '=') << std::endl;
}

// Helper function to print iterator results
template<typename Iterator>
void printIteratorResult(const std::string& name, Iterator begin, Iterator end) {
    std::cout << std::setw(20) << std::left << (name + ":") << " ";
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

// Test int container
void testIntegerContainer() {
    printHeader("INTEGER CONTAINER DEMO");
    
    MyContainer<int> intContainer;
    
    // Add elements
    std::cout << "Adding elements: 7, 15, 6, 1, 2, 15, 1" << std::endl;
    intContainer.add(7);
    intContainer.add(15);
    intContainer.add(6);
    intContainer.add(1);
    intContainer.add(2);
    intContainer.add(15);  // Duplicate
    intContainer.add(1);   // Duplicate
    
    std::cout << "Container: " << intContainer << std::endl;
    std::cout << "Size: " << intContainer.size() << std::endl;
    std::cout << "Empty: " << (intContainer.empty() ? "Yes" : "No") << std::endl;
    
    std::cout << "\n--- All Iterator Patterns ---" << std::endl;
    printIteratorResult("Ascending", intContainer.begin_ascending_order(), intContainer.end_ascending_order());
    printIteratorResult("Descending", intContainer.begin_descending_order(), intContainer.end_descending_order());
    printIteratorResult("SideCross", intContainer.begin_side_cross_order(), intContainer.end_side_cross_order());
    printIteratorResult("Reverse", intContainer.begin_reverse_order(), intContainer.end_reverse_order());
    printIteratorResult("Order", intContainer.begin_order(), intContainer.end_order());
    printIteratorResult("MiddleOut", intContainer.begin_middle_out_order(), intContainer.end_middle_out_order());
    
    // Test removal
    std::cout << "\n--- Testing Removal ---" << std::endl;
    std::cout << "Removing element 15 (appears twice)..." << std::endl;
    intContainer.remove(15);
    std::cout << "After removal: " << intContainer << std::endl;
    std::cout << "New size: " << intContainer.size() << std::endl;
    
    // Test error handling
    std::cout << "\n--- Testing Error Handling ---" << std::endl;
    try {
        std::cout << "Trying to remove non-existent element 99..." << std::endl;
        intContainer.remove(99);
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
    }
}

// Test string container
void testStringContainer() {
    printHeader("STRING CONTAINER DEMONSTRATION");
    
    MyContainer<std::string> stringContainer;
    
    // Add elements
    std::cout << "Adding strings: \"zebra\", \"apple\", \"dog\", \"cat\", \"elephant\"" << std::endl;
    stringContainer.add("zebra");
    stringContainer.add("apple");
    stringContainer.add("dog");
    stringContainer.add("cat");
    stringContainer.add("elephant");
    
    std::cout << "Container: " << stringContainer << std::endl;
    std::cout << "Size: " << stringContainer.size() << std::endl;
    
    std::cout << "\n--- String Iterator Patterns ---" << std::endl;
    printIteratorResult("Ascending", stringContainer.begin_ascending_order(), stringContainer.end_ascending_order());
    printIteratorResult("Descending", stringContainer.begin_descending_order(), stringContainer.end_descending_order());
    printIteratorResult("SideCross", stringContainer.begin_side_cross_order(), stringContainer.end_side_cross_order());
    printIteratorResult("Reverse", stringContainer.begin_reverse_order(), stringContainer.end_reverse_order());
    printIteratorResult("Order", stringContainer.begin_order(), stringContainer.end_order());
    printIteratorResult("MiddleOut", stringContainer.begin_middle_out_order(), stringContainer.end_middle_out_order());
    
    // Test removal
    std::cout << "\n--- Testing String Removal ---" << std::endl;
    std::cout << "Removing \"dog\"..." << std::endl;
    stringContainer.remove("dog");
    std::cout << "After removal: " << stringContainer << std::endl;
}

// Test double container
void testDoubleContainer() {
    printHeader("DOUBLE CONTAINER DEMONSTRATION");
    
    MyContainer<double> doubleContainer;
    
    // Add elements
    std::cout << "Adding doubles: 3.14, 2.71, 1.41, 0.57, 2.23" << std::endl;
    doubleContainer.add(3.14);
    doubleContainer.add(2.71);
    doubleContainer.add(1.41);
    doubleContainer.add(0.57);
    doubleContainer.add(2.23);
    
    std::cout << "Container: " << doubleContainer << std::endl;
    std::cout << "Size: " << doubleContainer.size() << std::endl;
    
    std::cout << "\n--- Double Iterator Patterns ---" << std::endl;
    printIteratorResult("Ascending", doubleContainer.begin_ascending_order(), doubleContainer.end_ascending_order());
    printIteratorResult("Descending", doubleContainer.begin_descending_order(), doubleContainer.end_descending_order());
    printIteratorResult("SideCross", doubleContainer.begin_side_cross_order(), doubleContainer.end_side_cross_order());
    printIteratorResult("Reverse", doubleContainer.begin_reverse_order(), doubleContainer.end_reverse_order());
    printIteratorResult("Order", doubleContainer.begin_order(), doubleContainer.end_order());
    printIteratorResult("MiddleOut", doubleContainer.begin_middle_out_order(), doubleContainer.end_middle_out_order());
}

// Test default template parameter
void testDefaultType() {
    printHeader("DEFAULT TYPE (INT) DEMONSTRATION");
    
    MyContainer<> defaultContainer;  // Uses default int type
    
    std::cout << "Creating MyContainer<> (default int type)" << std::endl;
    std::cout << "Adding elements: 100, 50, 75, 25, 90" << std::endl;
    
    defaultContainer.add(100);
    defaultContainer.add(50);
    defaultContainer.add(75);
    defaultContainer.add(25);
    defaultContainer.add(90);
    
    std::cout << "Container: " << defaultContainer << std::endl;
    printIteratorResult("Ascending", defaultContainer.begin_ascending_order(), defaultContainer.end_ascending_order());
    printIteratorResult("MiddleOut", defaultContainer.begin_middle_out_order(), defaultContainer.end_middle_out_order());
}

// Test copy operations
void testCopyOperations() {
    printHeader("COPY OPERATIONS DEMONSTRATION");
    
    MyContainer<int> original;
    original.add(1);
    original.add(2);
    original.add(3);
    
    std::cout << "Original container: " << original << std::endl;
    
    // Test copy constructor
    MyContainer<int> copied(original);
    std::cout << "Copied container: " << copied << std::endl;
    
    // Test copy assignment
    MyContainer<int> assigned;
    assigned = original;
    std::cout << "Assigned container: " << assigned << std::endl;
    
    // Modify original to show independence
    original.add(4);
    std::cout << "\nAfter adding 4 to original:" << std::endl;
    std::cout << "Original: " << original << std::endl;
    std::cout << "Copied: " << copied << std::endl;
    std::cout << "Assigned: " << assigned << std::endl;
}

// Test edge cases
void testEdgeCases() {
    printHeader("EDGE CASES DEMONSTRATION");
    
    // Empty container
    std::cout << "--- Empty Container ---" << std::endl;
    MyContainer<int> emptyContainer;
    std::cout << "Empty container: " << emptyContainer << std::endl;
    std::cout << "Size: " << emptyContainer.size() << std::endl;
    std::cout << "Empty: " << (emptyContainer.empty() ? "Yes" : "No") << std::endl;
    
    // Single element
    std::cout << "\n--- Single Element ---" << std::endl;
    MyContainer<char> singleContainer;
    singleContainer.add('X');
    std::cout << "Single element container: " << singleContainer << std::endl;
    printIteratorResult("Ascending", singleContainer.begin_ascending_order(), singleContainer.end_ascending_order());
    printIteratorResult("MiddleOut", singleContainer.begin_middle_out_order(), singleContainer.end_middle_out_order());
    
    // Two elements
    std::cout << "\n--- Two Elements ---" << std::endl;
    MyContainer<char> twoContainer;
    twoContainer.add('B');
    twoContainer.add('A');
    std::cout << "Two elements container: " << twoContainer << std::endl;
    printIteratorResult("Ascending", twoContainer.begin_ascending_order(), twoContainer.end_ascending_order());
    printIteratorResult("MiddleOut", twoContainer.begin_middle_out_order(), twoContainer.end_middle_out_order());
}

// Test postfix operators (new addition)
void testPostfixOperators() {
    printHeader("POSTFIX OPERATORS DEMONSTRATION");
    
    MyContainer<int> container;
    for (int i = 1; i <= 5; ++i) {
        container.add(i);
    }
    
    std::cout << "Container: " << container << std::endl;
    
    std::cout << "\n--- Prefix vs Postfix Demonstration ---" << std::endl;
    
    // Test with ascending iterator
    std::cout << "\nAscending Iterator:" << std::endl;
    auto ascIt = container.begin_ascending_order();
    
    // Prefix (++it)
    std::cout << "Using prefix (++it):" << std::endl;
    std::cout << "Initial value: " << *ascIt << std::endl;
    std::cout << "Return value of ++it: " << *(++ascIt) << std::endl;
    std::cout << "Value after operation: " << *ascIt << std::endl;
    
    // Reset iterator
    ascIt = container.begin_ascending_order();
    
    // Postfix (it++)
    std::cout << "\nUsing postfix (it++):" << std::endl;
    std::cout << "Initial value: " << *ascIt << std::endl;
    std::cout << "Return value of it++: " << *(ascIt++) << std::endl;
    std::cout << "Value after operation: " << *ascIt << std::endl;
    
    // Test with other iterators
    std::cout << "\nTesting all iterator types with postfix:" << std::endl;
    
    std::cout << "Descending: ";
    for (auto it = container.begin_descending_order(); it != container.end_descending_order(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "SideCross: ";
    for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Reverse: ";
    for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "Order: ";
    for (auto it = container.begin_order(); it != container.end_order(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    std::cout << "MiddleOut: ";
    for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); it++) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::cout <<""<< std::endl;
    std::cout << "           MyContainer demo : " << std::endl;
    std::cout << std::string(60, '_') << std::endl;
    
    try {
        testIntegerContainer();
        testStringContainer();
        testDoubleContainer();
        testDefaultType();
        testCopyOperations();
        testEdgeCases();
        testPostfixOperators();  // New test for postfix operators
        
        printHeader("DEMO COMPLETED");
        std::cout << "MyContainer is working correctly." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during demonstration: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}