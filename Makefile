# Nitzanwa@gmail.com
# Makefile for MyContainer Project

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g -Iinclude

# Main demonstration
Main: src/Demo.cpp include/MyContainer.hpp
	$(CXX) $(CXXFLAGS) src/Demo.cpp -o demo
	./demo

# Unit tests
test: src/tests/test.cpp include/MyContainer.hpp include/doctest.h
	$(CXX) $(CXXFLAGS) src/tests/test.cpp -o test_runner
	./test_runner

# Memory check with valgrind on demo
valgrind: src/Demo.cpp include/MyContainer.hpp
	$(CXX) $(CXXFLAGS) src/Demo.cpp -o demo
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./demo

# Memory check with valgrind on tests
valgrind-test: src/tests/test.cpp include/MyContainer.hpp include/doctest.h
	$(CXX) $(CXXFLAGS) src/tests/test.cpp -o test_runner
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 ./test_runner

# Clean up
clean:
	rm -f demo test_runner *.o

.PHONY: Main test valgrind valgrind-test clean