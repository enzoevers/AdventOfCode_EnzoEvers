OUT_FOLDER=out
GXX=g++
CPP_FLAGS=-std=c++17
LIBS=
LIBS_TEST=-lgtest -lpthread
SRC=$(wildcard ./src/*.cpp)

all:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${LIBS} ${SRC} main.cpp -o ./${OUT_FOLDER}/main

test:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${LIBS} ${LIBS_TEST} ${SRC} test.cpp -o ./${OUT_FOLDER}/test
	./${OUT_FOLDER}/test

clean:
	rm -rf ./${OUT_FOLDER}
