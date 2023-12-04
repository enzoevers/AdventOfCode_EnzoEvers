OUT_FOLDER=out
GXX=g++
GOOGLE_TEST_INCLUDE=/usr/local/include
CPP_FLAGS=-std=c++17 -g -Wall -Wextra -I $(GOOGLE_TEST_INCLUDE)
LIBS=
LIBS_TEST=-L/usr/local/lib -lgtest -lpthread
SRC=$(wildcard ./src/*.cpp)
TEST=$(wildcard ./test/*.cpp)

.PHONY: app test clean

app:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${SRC} main.cpp -o ./${OUT_FOLDER}/main ${LIBS}

test:
	mkdir -p ${OUT_FOLDER}
	${GXX} ${CPP_FLAGS} ${SRC} ${TEST} -o ./${OUT_FOLDER}/test ${LIBS} ${LIBS_TEST}

clean:
	rm -rf ./${OUT_FOLDER}
