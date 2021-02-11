TARGET = result
EXE_DIR = exe
TESTS_DIR = tests

.PHONY: all clean 

all: $(TARGET)

clean: clean_tests
		rm -rf $(EXE_DIR) 
clean_tests:
		rm -rf $(TESTS_DIR)/output[0123456789]*.txt


main.o: main.cpp
		g++ -c -o $(EXE_DIR)/main.o main.cpp
algo.o: algo.cpp
		g++ -c -o $(EXE_DIR)/algo.o algo.cpp
$(TARGET): exe main.o algo.o
		g++ -o $(EXE_DIR)/$(TARGET) $(EXE_DIR)/main.o $(EXE_DIR)/algo.o
exe:
		mkdir ${EXE_DIR}
tests: clean_tests all
		chmod ugo+x run_tests.sh
		./run_tests.sh
				


