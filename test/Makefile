# add test scripts here
SCRIPTS=tfcm

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}