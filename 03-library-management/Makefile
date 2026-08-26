CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*
TIDY_EXCLUDE=test.cpp main.cpp StudentTest.cpp

SOURCES=Book.cpp LibraryCard.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo
	./demo

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

grade: test tidy

test: TestRunner.o $(OBJECTS) student_test
	$(CXX) $(CXXFLAGS) TestRunner.o $(OBJECTS) -o test
	./test

tidy:
	clang-tidy $(filter-out $(TIDY_EXCLUDE), $(wildcard *.cpp)) $(TIDY_FLAGS) -- $(CXXFLAGS)

student_test: StudentTestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o student_test
	@count=$$(./student_test -ltc | grep -c "^[^[]"); \
	if [ $$count -lt 20 ]; then \
		echo "ERROR: StudentTest.cpp must contain at least 20 test cases (found $$count)"; \
		exit 1; \
	fi

StudentTestRunner.o: StudentTest.cpp doctest.h
	$(CXX) $(CXXFLAGS) --compile StudentTest.cpp -o StudentTestRunner.o

TestRunner.o: test.cpp doctest.h
	$(CXX) $(CXXFLAGS) --compile test.cpp -o TestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f *.o demo test student_test

.PHONY: all test tidy student_test clean grade
