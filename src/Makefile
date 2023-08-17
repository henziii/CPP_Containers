# "c" for C(Obvious) "cc" or "cpp" for C++
PLANG = cc
# if u want to change language than change compiler too
CC = g++
CWWW = -Wall -Werror -Wextra -pedantic
# $(CWWW) can be ereased if u want to insert these flags later
CFLAGS = $(CWWW) -std=c++17 -g

SOURCES = $(wildcard *.$(PLANG))
OBJECTS = $(SOURCES:.$(PLANG)=.o)
SOURCES_TESTS = $(wildcard ./tests/*.$(PLANG))
OBJECTS_TESTS = $(SOURCES_TESTS:.$(PLANG)=.o)
EXECUTABLE = containers
# u can change those flags to change test framework
TEST_FLAGS =  -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage 
 

all: test

%.o: %.$(PLANG)
	$(CC) $(CFLAGS) -c $^  -o $@ 

test: $(OBJECTS_TESTS) $(OBJECTS)
	$(CC) $^ -o $(EXECUTABLE) $(TEST_FLAGS)
	rm -rf *.o
	rm -rf tests/*.o 
	./$(EXECUTABLE)

gcov_report: clean 
	$(CC) -o $(EXECUTABLE) --coverage $(SOURCES_TESTS) $(SOURCES) $(TEST_FLAGS) $(CFLAGS) 
	./$(EXECUTABLE)
	mkdir report
	gcovr --html-details -o report/coverage.html
	open ./report/coverage.html
	make clean_without_report


clean_without_report:
	rm -rf $(OBJECTS) $(OBJECTS_TESTS) $(EXECUTABLE) *gcda *gcno *info ./tests/*.gcda ./tests/*.gcno

clean_report:
	rm -rf ./report

clean: clean_without_report clean_report
