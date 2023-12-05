OUT_FOLDER=out
GXX=g++
CPP_FLAGS=-std=c++20 -g -Wall -Wextra -I /usr/local/include
LIBS=
LIBS_TEST=-L/usr/local/lib -lgtest -lgmock -lpthread
SRC=$(wildcard ./src/*.cpp)
TEST=$(wildcard ./test/*.cpp)

.PHONY: app test clean

app:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${SRC} main.cpp -o ./${OUT_FOLDER}/app ${LIBS}

test:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${SRC} ${TEST} -o ./${OUT_FOLDER}/test ${LIBS} ${LIBS_TEST}

clean:
	rm -rf ./${OUT_FOLDER}
