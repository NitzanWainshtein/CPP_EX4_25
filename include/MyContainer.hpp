// Nitzanwa@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iomanip>

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
         * Prints elements in format: ["element1", "element2"] for strings
         * or [element1, element2] for other types
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
                // Add quotes for strings to make them clearer
                if constexpr (std::is_same_v<T, std::string>) {
                    os << "\"" << container.elements[i] << "\"";
                } else {
                    os << container.elements[i];
                }
                
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
            const MyContainer<T>* owner;  // Added to fix comparison issue

        public:
            AscendingIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : sorted_elements(original_elements), current_index(index), owner(container_owner) {
                std::sort(sorted_elements.begin(), sorted_elements.end());
            }

            const T& operator*() const { return sorted_elements[current_index]; }
            AscendingIterator& operator++() { ++current_index; return *this; }
            
            // Added postfix operator++
            AscendingIterator operator++(int) {
                AscendingIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const AscendingIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
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
            const MyContainer<T>* owner;

        public:
            DescendingIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : sorted_elements(original_elements), current_index(index), owner(container_owner) {
                std::sort(sorted_elements.rbegin(), sorted_elements.rend());
            }

            const T& operator*() const { return sorted_elements[current_index]; }
            DescendingIterator& operator++() { ++current_index; return *this; }
            
            // Added postfix operator++
            DescendingIterator operator++(int) {
                DescendingIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const DescendingIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
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
            const MyContainer<T>* owner;

        public:
            SideCrossIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : current_index(index), owner(container_owner) {
                
                // Fix: Handle empty container case
                if (original_elements.empty()) {
                    return;
                }
                
                std::vector<T> sorted_elements = original_elements;
                std::sort(sorted_elements.begin(), sorted_elements.end());
                
                cross_ordered_elements.reserve(sorted_elements.size());
                
                size_t left = 0;
                size_t right = sorted_elements.size() - 1;  // Now safe!
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
            
            // Added postfix operator++
            SideCrossIterator operator++(int) {
                SideCrossIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const SideCrossIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
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
            const MyContainer<T>* owner;

        public:
            ReverseIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : reversed_elements(original_elements), current_index(index), owner(container_owner) {
                std::reverse(reversed_elements.begin(), reversed_elements.end());
            }

            const T& operator*() const { return reversed_elements[current_index]; }
            ReverseIterator& operator++() { ++current_index; return *this; }
            
            // Added postfix operator++
            ReverseIterator operator++(int) {
                ReverseIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const ReverseIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
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
            const MyContainer<T>* owner;

        public:
            OrderIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : original_elements(original_elements), current_index(index), owner(container_owner) {
                // No modifications - keep original order
            }

            const T& operator*() const { return original_elements[current_index]; }
            OrderIterator& operator++() { ++current_index; return *this; }
            
            // Added postfix operator++
            OrderIterator operator++(int) {
                OrderIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const OrderIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
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
            const MyContainer<T>* owner;

        public:
            MiddleOutIterator(const std::vector<T>& original_elements, size_t index, const MyContainer<T>* container_owner) 
                : current_index(index), owner(container_owner) {
                
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
            
            // Added postfix operator++
            MiddleOutIterator operator++(int) {
                MiddleOutIterator temp = *this;
                ++current_index;
                return temp;
            }
            
            bool operator==(const MiddleOutIterator& other) const { 
                return owner == other.owner && current_index == other.current_index; 
            }
            bool operator!=(const MiddleOutIterator& other) const { return !(*this == other); }
        };

        // ================== ITERATOR ACCESS FUNCTIONS ==================
        
        // AscendingOrder iteration
        AscendingIterator begin_ascending_order() const { return AscendingIterator(elements, 0, this); }
        AscendingIterator end_ascending_order() const { return AscendingIterator(elements, elements.size(), this); }

        // DescendingOrder iteration
        DescendingIterator begin_descending_order() const { return DescendingIterator(elements, 0, this); }
        DescendingIterator end_descending_order() const { return DescendingIterator(elements, elements.size(), this); }

        // SideCrossOrder iteration
        SideCrossIterator begin_side_cross_order() const { return SideCrossIterator(elements, 0, this); }
        SideCrossIterator end_side_cross_order() const { return SideCrossIterator(elements, elements.size(), this); }

        // ReverseOrder iteration
        ReverseIterator begin_reverse_order() const { return ReverseIterator(elements, 0, this); }
        ReverseIterator end_reverse_order() const { return ReverseIterator(elements, elements.size(), this); }

        // Natural order iteration
        OrderIterator begin_order() const { return OrderIterator(elements, 0, this); }
        OrderIterator end_order() const { return OrderIterator(elements, elements.size(), this); }

        // MiddleOutOrder iteration
        MiddleOutIterator begin_middle_out_order() const { return MiddleOutIterator(elements, 0, this); }
        MiddleOutIterator end_middle_out_order() const { return MiddleOutIterator(elements, elements.size(), this); }

    }; // End of MyContainer class

} // End of ex4 namespace

#endif // MYCONTAINER_HPP