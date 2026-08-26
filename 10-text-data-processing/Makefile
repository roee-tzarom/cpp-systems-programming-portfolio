CXX=clang++
CXXFLAGS=-std=c++23 -Werror -Wsign-conversion
TIDY_FLAGS=-checks=bugprone-*,-bugprone-easily-swappable-parameters,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-* --warnings-as-errors=*
TIDY_EXCLUDE=test.cpp main.cpp StudentTest.cpp

SOURCES=DataProcessor.cpp TextAnalyzer.cpp SetOperations.cpp AlgorithmShowcase.cpp
OBJECTS=$(subst .cpp,.o,$(SOURCES))

all: demo
	./demo

demo: main.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

grade: test tidy

test: TestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) TestRunner.o $(OBJECTS) -o test
	./test

student_test: StudentTestRunner.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o student_test
	@count=$$(./student_test -ltc | grep -c "^[^[]"); \
	if [ $$count -lt 20 ]; then \
		echo "ERROR: StudentTest.cpp must contain at least 20 test cases (found $$count)"; \
		exit 1; \
	fi

TestRunner.o: test.cpp DataProcessor.hpp TextAnalyzer.hpp SetOperations.hpp AlgorithmShowcase.hpp doctest.h
	$(CXX) $(CXXFLAGS) -c test.cpp -o TestRunner.o

StudentTestRunner.o: StudentTest.cpp $(wildcard *.hpp) doctest.h
	$(CXX) $(CXXFLAGS) -c StudentTest.cpp -o StudentTestRunner.o

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

DataProcessor.o: DataProcessor.cpp DataProcessor.hpp

TextAnalyzer.o: TextAnalyzer.cpp TextAnalyzer.hpp

SetOperations.o: SetOperations.cpp SetOperations.hpp

AlgorithmShowcase.o: AlgorithmShowcase.cpp AlgorithmShowcase.hpp

main.o: main.cpp DataProcessor.hpp TextAnalyzer.hpp SetOperations.hpp AlgorithmShowcase.hpp

tidy:
	clang-tidy $(filter-out $(TIDY_EXCLUDE), $(wildcard *.cpp)) $(TIDY_FLAGS) -- $(CXXFLAGS)

clean:
	rm -f *.o demo test student_test

.PHONY: all test clean tidy student_test grade
