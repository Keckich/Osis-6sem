EXE_DIR = exe
TARGET = result

.PHONY: all clean

all: $(TARGET)

main.o: main.cpp
		g++ -pthread -c -o $(EXE_DIR)/main.o main.cpp
algo.o: algo.cpp
		g++ -c -o $(EXE_DIR)/algo.o algo.cpp
$(TARGET): exe main.o algo.o
		g++ -pthread -o $(EXE_DIR)/$(TARGET) $(EXE_DIR)/main.o $(EXE_DIR)/algo.o

exe: 
		mkdir $(EXE_DIR)
clean:
		rm -rf $(EXE_DIR)
