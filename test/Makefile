# add test scripts here
SCRIPTS=tfcm especial

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}