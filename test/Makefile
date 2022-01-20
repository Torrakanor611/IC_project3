# add test scripts here
SCRIPTS=tfcm especial lang

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}