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
    intContainer.addElement(7);
    intContainer.addElement(15);
    intContainer.addElement(6);
    intContainer.addElement(1);
    intContainer.addElement(2);
    intContainer.addElement(15);  // Duplicate
    intContainer.addElement(1);   // Duplicate
    
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
    intContainer.removeElement(15);
    std::cout << "After removal: " << intContainer << std::endl;
    std::cout << "New size: " << intContainer.size() << std::endl;
    
    // Test error handling
    std::cout << "\n--- Testing Error Handling ---" << std::endl;
    try {
        std::cout << "Trying to remove non-existent element 99..." << std::endl;
        intContainer.removeElement(99);
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
    stringContainer.addElement("zebra");
    stringContainer.addElement("apple");
    stringContainer.addElement("dog");
    stringContainer.addElement("cat");
    stringContainer.addElement("elephant");
    
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
    stringContainer.removeElement("dog");
    std::cout << "After removal: " << stringContainer << std::endl;
}

// Test double container
void testDoubleContainer() {
    printHeader("DOUBLE CONTAINER DEMONSTRATION");
    
    MyContainer<double> doubleContainer;
    
    // Add elements
    std::cout << "Adding doubles: 3.14, 2.71, 1.41, 0.57, 2.23" << std::endl;
    doubleContainer.addElement(3.14);
    doubleContainer.addElement(2.71);
    doubleContainer.addElement(1.41);
    doubleContainer.addElement(0.57);
    doubleContainer.addElement(2.23);
    
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
    
    defaultContainer.addElement(100);
    defaultContainer.addElement(50);
    defaultContainer.addElement(75);
    defaultContainer.addElement(25);
    defaultContainer.addElement(90);
    
    std::cout << "Container: " << defaultContainer << std::endl;
    printIteratorResult("Ascending", defaultContainer.begin_ascending_order(), defaultContainer.end_ascending_order());
    printIteratorResult("MiddleOut", defaultContainer.begin_middle_out_order(), defaultContainer.end_middle_out_order());
}

// Test copy operations
void testCopyOperations() {
    printHeader("COPY OPERATIONS DEMONSTRATION");
    
    MyContainer<int> original;
    original.addElement(1);
    original.addElement(2);
    original.addElement(3);
    
    std::cout << "Original container: " << original << std::endl;
    
    // Test copy constructor
    MyContainer<int> copied(original);
    std::cout << "Copied container: " << copied << std::endl;
    
    // Test copy assignment
    MyContainer<int> assigned;
    assigned = original;
    std::cout << "Assigned container: " << assigned << std::endl;
    
    // Modify original to show independence
    original.addElement(4);
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
    singleContainer.addElement('X');
    std::cout << "Single element container: " << singleContainer << std::endl;
    printIteratorResult("Ascending", singleContainer.begin_ascending_order(), singleContainer.end_ascending_order());
    printIteratorResult("MiddleOut", singleContainer.begin_middle_out_order(), singleContainer.end_middle_out_order());
    
    // Two elements
    std::cout << "\n--- Two Elements ---" << std::endl;
    MyContainer<char> twoContainer;
    twoContainer.addElement('B');
    twoContainer.addElement('A');
    std::cout << "Two elements container: " << twoContainer << std::endl;
    printIteratorResult("Ascending", twoContainer.begin_ascending_order(), twoContainer.end_ascending_order());
    printIteratorResult("MiddleOut", twoContainer.begin_middle_out_order(), twoContainer.end_middle_out_order());
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
        
        printHeader("DEMO COMPLETED");
        std::cout << "MyContainer is working correctly." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error during demonstration: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}