// Nitzanwa@gmail.com

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <string>
#include <vector>

using namespace ex4;

// Helper function to convert iterator to vector manually (with safety check)
template<typename Container>
std::vector<int> toVector(Container& container, const std::string& iterType) {
    std::vector<int> result;
    
    // Safety check - if container is empty, return empty vector
    if (container.empty()) {
        return result;
    }
    
    if (iterType == "ascending") {
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
    } else if (iterType == "descending") {
        for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
            result.push_back(*it);
        }
    } else if (iterType == "side_cross") {
        for (auto it = container.begin_side_cross_order(); it != container.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
    } else if (iterType == "reverse") {
        for (auto it = container.begin_reverse_order(); it != container.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
    } else if (iterType == "order") {
        for (auto it = container.begin_order(); it != container.end_order(); ++it) {
            result.push_back(*it);
        }
    } else if (iterType == "middle_out") {
        for (auto it = container.begin_middle_out_order(); it != container.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
    }
    
    return result;
}

TEST_CASE("Basic Container Operations") {
    
    SUBCASE("Default constructor and basic operations") {
        MyContainer<int> container;
        CHECK(container.size() == 0);
        CHECK(container.empty() == true);
    }
    
    SUBCASE("Add elements") {
        MyContainer<int> container;
        container.add(5);
        container.add(3);
        container.add(8);
        
        CHECK(container.size() == 3);
        CHECK(container.empty() == false);
    }
    
    SUBCASE("Remove existing element") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        container.add(3);
        
        CHECK_NOTHROW(container.remove(2));
        CHECK(container.size() == 2);
    }
    
    SUBCASE("Remove non-existing element throws exception") {
        MyContainer<int> container;
        container.add(1);
        container.add(2);
        
        CHECK_THROWS_AS(container.remove(99), std::runtime_error);
    }
    
    SUBCASE("Remove all occurrences") {
        MyContainer<int> container;
        container.add(5);
        container.add(3);
        container.add(5);
        container.add(1);
        container.add(5);
        
        CHECK(container.size() == 5);
        container.remove(5);
        CHECK(container.size() == 2);
    }
}

TEST_CASE("Copy Operations") {
    
    SUBCASE("Copy constructor") {
        MyContainer<int> original;
        original.add(1);
        original.add(2);
        original.add(3);
        
        MyContainer<int> copied(original);
        CHECK(copied.size() == original.size());
        
        // Verify independence
        original.add(4);
        CHECK(original.size() == 4);
        CHECK(copied.size() == 3);
    }
    
    SUBCASE("Assignment operator") {
        MyContainer<int> original;
        original.add(10);
        original.add(20);
        
        MyContainer<int> assigned;
        assigned = original;
        CHECK(assigned.size() == original.size());
        
        // Verify independence
        original.add(30);
        CHECK(original.size() == 3);
        CHECK(assigned.size() == 2);
    }
}

TEST_CASE("Iterator Operations - Integer") {
    MyContainer<int> container;
    container.add(7);
    container.add(15);
    container.add(6);
    container.add(1);
    container.add(2);
    
    SUBCASE("Ascending order iterator") {
        auto result = toVector(container, "ascending");
        std::vector<int> expected = {1, 2, 6, 7, 15};
        CHECK(result == expected);
    }
    
    SUBCASE("Descending order iterator") {
        auto result = toVector(container, "descending");
        std::vector<int> expected = {15, 7, 6, 2, 1};
        CHECK(result == expected);
    }
    
    SUBCASE("Side cross order iterator") {
        auto result = toVector(container, "side_cross");
        std::vector<int> expected = {1, 15, 2, 7, 6};
        CHECK(result == expected);
    }
    
    SUBCASE("Reverse order iterator") {
        auto result = toVector(container, "reverse");
        std::vector<int> expected = {2, 1, 6, 15, 7};
        CHECK(result == expected);
    }
    
    SUBCASE("Natural order iterator") {
        auto result = toVector(container, "order");
        std::vector<int> expected = {7, 15, 6, 1, 2};
        CHECK(result == expected);
    }
    
    SUBCASE("Middle out order iterator") {
        auto result = toVector(container, "middle_out");
        std::vector<int> expected = {6, 15, 1, 7, 2};
        CHECK(result == expected);
    }
}

TEST_CASE("String Container") {
    MyContainer<std::string> container;
    container.add("zebra");
    container.add("apple");
    container.add("dog");
    
    SUBCASE("String ascending order") {
        std::vector<std::string> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        std::vector<std::string> expected = {"apple", "dog", "zebra"};
        CHECK(result == expected);
    }
    
    SUBCASE("String removal") {
        CHECK(container.size() == 3);
        container.remove("dog");
        CHECK(container.size() == 2);
        
        CHECK_THROWS_AS(container.remove("cat"), std::runtime_error);
    }
}

TEST_CASE("Edge Cases") {
    
    SUBCASE("Empty container") {
        MyContainer<int> empty;
        
        // Test that empty containers return empty vectors
        CHECK(toVector(empty, "ascending").empty());
        CHECK(toVector(empty, "descending").empty());
        CHECK(toVector(empty, "side_cross").empty());
        CHECK(toVector(empty, "reverse").empty());
        CHECK(toVector(empty, "order").empty());
        CHECK(toVector(empty, "middle_out").empty());
        
        // Test that iterators are equal for empty container
        CHECK(empty.begin_ascending_order() == empty.end_ascending_order());
        CHECK(empty.begin_descending_order() == empty.end_descending_order());
    }
    
    SUBCASE("Single element container") {
        MyContainer<int> single;
        single.add(42);
        
        CHECK(toVector(single, "ascending") == std::vector<int>{42});
        CHECK(toVector(single, "descending") == std::vector<int>{42});
        CHECK(toVector(single, "order") == std::vector<int>{42});
        CHECK(toVector(single, "middle_out") == std::vector<int>{42});
    }
    
    SUBCASE("Two elements container") {
        MyContainer<int> two;
        two.add(5);
        two.add(3);
        
        CHECK(toVector(two, "ascending") == std::vector<int>({3, 5}));
        CHECK(toVector(two, "descending") == std::vector<int>({5, 3}));
        CHECK(toVector(two, "reverse") == std::vector<int>({3, 5}));
        CHECK(toVector(two, "order") == std::vector<int>({5, 3}));
    }
}

TEST_CASE("Default Template Parameter") {
    SUBCASE("MyContainer<> defaults to int") {
        MyContainer<> container;  // Uses default int
        container.add(100);
        container.add(50);
        
        CHECK(container.size() == 2);
        CHECK_NOTHROW(container.remove(50));
        CHECK(container.size() == 1);
    }
}

TEST_CASE("Iterator Consistency") {
    MyContainer<int> container;
    container.add(10);
    container.add(5);
    container.add(15);
    
    SUBCASE("Multiple iterations give same result") {
        auto result1 = toVector(container, "ascending");
        auto result2 = toVector(container, "ascending");
        CHECK(result1 == result2);
    }
    
    SUBCASE("Iterator operations work") {
        auto it = container.begin_ascending_order();
        auto end = container.end_ascending_order();
        
        CHECK(it != end);
        
        int first = *it;
        ++it;
        int second = *it;
        
        CHECK(first < second);  
    }
}

// חדש: טסטים לאופרטור postfix
TEST_CASE("Postfix Iterator Operators") {
    MyContainer<int> container;
    container.add(10);
    container.add(20);
    container.add(30);
    
    SUBCASE("Difference between prefix and postfix operators") {
        auto it1 = container.begin_ascending_order();
        auto it2 = container.begin_ascending_order();
        
        // Prefix (++it) returns iterator after incrementing
        int prefix_val = *(++it1);
        // Postfix (it++) returns original value, then increments
        int postfix_val = *(it2++);
        int next_val = *it2;
        
        CHECK(prefix_val == 20);     // ערך לאחר קידום
        CHECK(postfix_val == 10);    // הערך המקורי
        CHECK(next_val == 20);       // ערך לאחר קידום
    }
    
    SUBCASE("Postfix operators with all iterator types") {
        // Test with ascending iterator
        {
            std::vector<int> result;
            auto it = container.begin_ascending_order();
            while (it != container.end_ascending_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {10, 20, 30};
            CHECK(result == expected);
        }
        
        // Test with descending iterator
        {
            std::vector<int> result;
            auto it = container.begin_descending_order();
            while (it != container.end_descending_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {30, 20, 10};
            CHECK(result == expected);
        }
        
        // Test with side cross iterator
        {
            std::vector<int> result;
            auto it = container.begin_side_cross_order();
            while (it != container.end_side_cross_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {10, 30, 20};
            CHECK(result == expected);
        }
        
        // Test with reverse iterator
        {
            std::vector<int> result;
            auto it = container.begin_reverse_order();
            while (it != container.end_reverse_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {30, 20, 10};
            CHECK(result == expected);
        }
        
        // Test with order iterator
        {
            std::vector<int> result;
            auto it = container.begin_order();
            while (it != container.end_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {10, 20, 30};
            CHECK(result == expected);
        }
        
        // Test with middle out iterator
        {
            std::vector<int> result;
            auto it = container.begin_middle_out_order();
            while (it != container.end_middle_out_order()) {
                result.push_back(*it);
                it++;  // Use postfix operator
            }
            std::vector<int> expected = {20, 10, 30};
            CHECK(result == expected);
        }
    }
    
    SUBCASE("Using postfix in for loop") {
        std::vector<int> result;
        for (auto it = container.begin_ascending_order(); it != container.end_ascending_order(); it++) {
            result.push_back(*it);
        }
        std::vector<int> expected = {10, 20, 30};
        CHECK(result == expected);
    }
}