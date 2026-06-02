CXX := g++
CFLAGS := -Wall -Wl,-rpath=/usr/local/lib

INCLUDES := \
-I./include/back \
-I./include/back/client \
-I./include/back/bank \
-I./include/front \

VERSION := 0.1.0

DEPENDENCE := $(shell pkg-config --cflags --libs dpp)

SOURCE := $(shell find src -name "*.cpp")

SERVER_ID ?= 0


release:
	$(CXX) $(CFLAGS) $(INCLUDES) $(SOURCE) $(DEPENDENCE) main.cpp -o bot-release -DRELEASE_MODE

debug:
	$(CXX) $(CFLAGS) $(INCLUDES) $(SOURCE) $(DEPENDENCE) main.cpp -o bot-debug -DSERVER_ID=\"$(SERVER_ID)\" -DDEBUG_MODE

clear:
	$(CXX) $(CFLAGS) $(INCLUDES) $(SOURCE) $(DEPENDENCE) main.cpp -o bot-clear -DSERVER_ID=\"$(SERVER_ID)\" -DCLEAR_MODE
