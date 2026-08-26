CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*
TIDY_CONFIG=-config='{CheckOptions: [{key: cppcoreguidelines-special-member-functions.AllowMissingMoveFunctions, value: true}]}'
TIDY_EXCLUDE=test.cpp StudentTest.cpp

# All code is in header files (templates + metaprogramming)

all: demo
	./demo

demo: main.o
	$(CXX) $(CXXFLAGS) $^ -o demo

grade: test tidy

test: TestRunner.o student_test
	$(CXX) $(CXXFLAGS) $^ -o test
	./test

student_test: StudentTestRunner.o
	$(CXX) $(CXXFLAGS) $^ -o student_test
	@count=$$(./student_test -ltc | grep -c "^[^[]"); \
	if [ $$count -lt 20 ]; then \
		echo "ERROR: StudentTest.cpp must contain at least 20 test cases (found $$count)"; \
		exit 1; \
	fi

TestRunner.o: test.cpp TypeInfo.hpp MySwap.hpp Formatter.hpp Derivative.hpp PhysicsUnits.hpp DecltypeUtils.hpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

StudentTestRunner.o: StudentTest.cpp $(wildcard *.hpp) doctest.h
	$(CXX) $(CXXFLAGS) --compile StudentTest.cpp -o StudentTestRunner.o

main.o: main.cpp TypeInfo.hpp MySwap.hpp Formatter.hpp Derivative.hpp PhysicsUnits.hpp DecltypeUtils.hpp
	$(CXX) $(CXXFLAGS) --compile main.cpp -o main.o

tidy:
	clang-tidy $(filter-out $(TIDY_EXCLUDE), $(wildcard *.cpp) $(wildcard *.hpp)) $(TIDY_FLAGS) $(TIDY_CONFIG) -- $(CXXFLAGS)
clean:
	rm -f *.o demo test student_test

.PHONY: all test clean tidy student_test grade
