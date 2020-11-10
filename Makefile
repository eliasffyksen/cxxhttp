
CXX=clang++
INCLUDE_PATH=./include
FLAGS=-I$(INCLUDE_PATH)

MAIN_SRC=src/main.cpp
SRC=$(wildcard src/*.cpp)
COMMON_SRC=$(filter-out $(MAIN_SRC), $(SRC))
TEST_SRC=$(wildcard tests/*.cpp)


%.hpp.gch: %.hpp
	$(CXX) $(FLAGS) -c -o $@ $<

tests/main.o: tests/main.cpp
	$(CXX) $(FLAGS) -c -o $@ $<

%.o: %.cpp pch.hpp.gch
	$(CXX) $(FLAGS) -c -o $@ $< -include-pch pch.hpp.gch

bin/tests: $(TEST_SRC:.cpp=.o)
	mkdir -p bin
	$(CXX) $(FLAGS) -o $@ $^

tests: bin/tests
	$<

bin/cxxhttp: $(MAIN_SRC:.cpp=.o) $(COMMON_SRC:.cpp=.o)
	mkdir -p bin
	$(CXX) $(FLAGS) -o $@ $^

run: bin/cxxhttp
	$<

clean:
	rm -fr bin
	rm -f src/*.o
	rm -f tests/*.o
	rm -f pch.hpp.gch