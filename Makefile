# add test scripts here
SCRIPTS=lang findlang

CPP=g++
DEPS=src/fcm.hpp

all: ${SCRIPTS}

lang: src/lang.cpp
	@ mkdir -p ./bin
	$(CPP) -o ./bin/lang src/lang.cpp src/fcm.hpp

findlang: src/findlang.cpp
	@ mkdir -p ./bin
	$(CPP) -o ./bin/findlang src/findlang.cpp src/fcm.hpp

clean:
	rm -f bin/lang bin/findlang