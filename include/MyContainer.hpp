// Nitzanwa@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace ex4 {
    
    /**
     * MyContainer - A generic container class for comparable types
     * 
     * Template parameter T defaults to int but can be any comparable type (int, double, string, custom classes with operator< defined)
     */
    template<typename T = int> class MyContainer {

    private:
        std::vector<T> elements;  // Internal storage for container elements

    public:
        
        // ================== CONSTRUCTORS & DESTRUCTOR==================
        
        /**
         * Default constructor - creates empty container
         */
        MyContainer() = default;
        
        /**
         * Copy constructor - creates deep copy of another container
         */
        MyContainer(const MyContainer& other) : elements(other.elements) {}
        
        /**
         * Copy assignment operator - assigns content from another container
         */
        MyContainer& operator=(const MyContainer& other) {
            if (this != &other) {
                elements = other.elements;
            }
            return *this;
        }
        
        /**
         * Destructor - default cleanup
         */
        ~MyContainer() = default;

        // ================== BASIC OPERATIONS ==================
        
        /**
         * Add an element to the container
         * @param element The element to add to the container
         */
        void addElement(const T& element) {
            elements.push_back(element);
        }

        /**
         * Remove all occurrences of an element from the container
         * @param element The element to remove
         * @throws std::runtime_error if element is not found in container
         */
        void removeElement(const T& element) {
            auto it = std::find(elements.begin(), elements.end(), element);
            if (it == elements.end()) {
                throw std::runtime_error("Element was not found in the container");
            }
            
            // Remove all occurrences
            elements.erase(
                std::remove(elements.begin(), elements.end(), element),
                elements.end()
            );
        }

        /**
         * Get the number of elements in the container
         * @return The size of the container
         */
        size_t size() const {
            return elements.size();
        }

        /**
         * Check if container is empty
         * @return true if container has no elements
         */
        bool empty() const {
            return elements.empty();
        }

        /**
         * Output operator for printing the container
         * Prints elements in format: [element1, element2, element3]
         * @param os Output stream
         * @param container The container to print
         * @return Reference to the output stream for chaining
         */
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            os << "[";
            if (container.elements.empty()) {
                os << "]";
                return os;
            }
            
            for (size_t i = 0; i < container.elements.size(); ++i) {
                os << container.elements[i];
                if (i < container.elements.size() - 1) { 
                    os << ", ";
                }
            }
            os << "]";
            return os;
        }

        // ================== ITERATOR CLASSES ==================
        
        /**
         * AscendingIterator - sorts elements from smallest to largest
         * Example: [7,15,6,1,2] -> 1,2,6,7,15
         */
        class AscendingIterator {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            AscendingIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : sorted_elements(original_elements), current_index(index) {
                std::sort(sorted_elements.begin(), sorted_elements.end());
            }

            const T& operator*() const { return sorted_elements[current_index]; }
            AscendingIterator& operator++() { ++current_index; return *this; }
            bool operator==(const AscendingIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const AscendingIterator& other) const { return !(*this == other); }
        };

        /**
         * DescendingIterator - sorts elements from largest to smallest
         * Example: [7,15,6,1,2] -> 15,7,6,2,1
         */
        class DescendingIterator {
        private:
            std::vector<T> sorted_elements;
            size_t current_index;

        public:
            DescendingIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : sorted_elements(original_elements), current_index(index) {
                std::sort(sorted_elements.rbegin(), sorted_elements.rend());
            }

            const T& operator*() const { return sorted_elements[current_index]; }
            DescendingIterator& operator++() { ++current_index; return *this; }
            bool operator==(const DescendingIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const DescendingIterator& other) const { return !(*this == other); }
        };

        /**
         * SideCrossIterator - alternates between smallest and largest remaining elements
         * Example: [7,15,6,1,2] -> 1,15,2,7,6
         * Pattern: smallest, largest, 2nd smallest, 2nd largest, middle, etc.
         */
        class SideCrossIterator {
        private:
            std::vector<T> cross_ordered_elements;
            size_t current_index;

        public:
            SideCrossIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : current_index(index) {
                
                std::vector<T> sorted_elements = original_elements;
                std::sort(sorted_elements.begin(), sorted_elements.end());
                
                cross_ordered_elements.reserve(sorted_elements.size());
                
                size_t left = 0;
                size_t right = sorted_elements.size() - 1;
                bool take_from_left = true;
                
                while (left <= right) {
                    if (take_from_left) {
                        cross_ordered_elements.push_back(sorted_elements[left++]);
                    } else {
                        cross_ordered_elements.push_back(sorted_elements[right--]);
                    }
                    take_from_left = !take_from_left;
                }
            }

            const T& operator*() const { return cross_ordered_elements[current_index]; }
            SideCrossIterator& operator++() { ++current_index; return *this; }
            bool operator==(const SideCrossIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const SideCrossIterator& other) const { return !(*this == other); }
        };

        /**
         * ReverseIterator - iterates in reverse insertion order
         * Example: [7,15,6,1,2] -> 2,1,6,15,7
         * Simply reverses the original order without sorting
         */
        class ReverseIterator {
        private:
            std::vector<T> reversed_elements;
            size_t current_index;

        public:
            ReverseIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : reversed_elements(original_elements), current_index(index) {
                std::reverse(reversed_elements.begin(), reversed_elements.end());
            }

            const T& operator*() const { return reversed_elements[current_index]; }
            ReverseIterator& operator++() { ++current_index; return *this; }
            bool operator==(const ReverseIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const ReverseIterator& other) const { return !(*this == other); }
        };

        /**
         * OrderIterator - iterates in natural insertion order
         * Example: [7,15,6,1,2] -> 7,15,6,1,2
         * No modifications - preserves original order
         */
        class OrderIterator {
        private:
            std::vector<T> original_elements;
            size_t current_index;

        public:
            OrderIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : original_elements(original_elements), current_index(index) {
                // No modifications - keep original order
            }

            const T& operator*() const { return original_elements[current_index]; }
            OrderIterator& operator++() { ++current_index; return *this; }
            bool operator==(const OrderIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const OrderIterator& other) const { return !(*this == other); }
        };

        /**
         * MiddleOutIterator - starts from middle, alternates left-right
         * Example: [7,15,6,1,2] -> 6,15,1,7,2
         * Pattern: middle, left1, right1, left2, right2, etc.
         */
        class MiddleOutIterator {
        private:
            std::vector<T> middle_out_elements;
            size_t current_index;

        public:
            MiddleOutIterator(const std::vector<T>& original_elements, size_t index = 0) 
                : current_index(index) {
                
                if (original_elements.empty()) return;
                
                size_t size = original_elements.size();
                size_t middle = size / 2;
                
                middle_out_elements.reserve(size);
                
                // Add middle element first
                middle_out_elements.push_back(original_elements[middle]);
                
                // Add elements at increasing distances from middle
                for (size_t distance = 1; distance < size; ++distance) {
                    // Try left side
                    if (middle >= distance) {
                        middle_out_elements.push_back(original_elements[middle - distance]);
                    }
                    // Try right side
                    if (middle + distance < size) {
                        middle_out_elements.push_back(original_elements[middle + distance]);
                    }
                }
            }

            const T& operator*() const { return middle_out_elements[current_index]; }
            MiddleOutIterator& operator++() { ++current_index; return *this; }
            bool operator==(const MiddleOutIterator& other) const { return current_index == other.current_index; }
            bool operator!=(const MiddleOutIterator& other) const { return !(*this == other); }
        };

        // ================== ITERATOR ACCESS FUNCTIONS ==================
        
        // AscendingOrder iteration
        AscendingIterator begin_ascending_order() const { return AscendingIterator(elements, 0); }
        AscendingIterator end_ascending_order() const { return AscendingIterator(elements, elements.size()); }

        // DescendingOrder iteration
        DescendingIterator begin_descending_order() const { return DescendingIterator(elements, 0); }
        DescendingIterator end_descending_order() const { return DescendingIterator(elements, elements.size()); }

        // SideCrossOrder iteration
        SideCrossIterator begin_side_cross_order() const { return SideCrossIterator(elements, 0); }
        SideCrossIterator end_side_cross_order() const { return SideCrossIterator(elements, elements.size()); }

        // ReverseOrder iteration
        ReverseIterator begin_reverse_order() const { return ReverseIterator(elements, 0); }
        ReverseIterator end_reverse_order() const { return ReverseIterator(elements, elements.size()); }

        // Natural order iteration
        OrderIterator begin_order() const { return OrderIterator(elements, 0); }
        OrderIterator end_order() const { return OrderIterator(elements, elements.size()); }

        // MiddleOutOrder iteration
        MiddleOutIterator begin_middle_out_order() const { return MiddleOutIterator(elements, 0); }
        MiddleOutIterator end_middle_out_order() const { return MiddleOutIterator(elements, elements.size()); }

    }; // End of MyContainer class

} // End of ex4 namespace

#endif // MYCONTAINER_HPP