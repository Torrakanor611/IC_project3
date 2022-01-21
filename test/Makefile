# add test scripts here
SCRIPTS=tfcm entropyfcm

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}