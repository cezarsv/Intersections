CC = g++
#CPP_FLAGS =  -Wall -g -O3 -std=c++0x
CPP_FLAGS =  -Wall -g -O3 -std=c++11
INCLUDES= -I.

TARGET_DIR = output

TARGET = $(TARGET_DIR)/IntersectCalculator
OBJS = $(TARGET_DIR)/main.o $(TARGET_DIR)/IntersectCalculator.o $(TARGET_DIR)/jsoncpp.o

TARGET_TEST = $(TARGET_DIR)/IntersectCalculatorTest
OBJS_TEST =  $(TARGET_DIR)/TestDriver.o $(TARGET_DIR)/IntersectCalculator.o $(TARGET_DIR)/jsoncpp.o

all: clean test project

build: test project

project: $(TARGET)
test: $(TARGET_TEST)

run_test:
	$(TARGET_TEST)

$(TARGET_DIR)/%.o: %.cpp
	$(CC) $(CPP_FLAGS) $(INCLUDES) -o $(TARGET_DIR)/$*.o -c $*.cpp

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

$(TARGET_TEST): $(OBJS_TEST)
	$(CC) -o $(TARGET_TEST) $(OBJS_TEST)

clean:
	rm -f $(OBJS) $(TARGET) $(OBJS_TEST) $(TARGET_TEST)

