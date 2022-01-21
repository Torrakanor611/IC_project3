# add test scripts here
SCRIPTS=tfcm entropyfcm lang

all: ${SCRIPTS}

%: %.cpp
	g++ $< -o $@

clean:
	rm -f ${SCRIPTS}