CXX=g++
XXFLAGS=-Wall -MMD
EXEC=quadris 
LIBS=-lX11 -L/opt/X11/lib
OBJECTS=main.o cell.o board.o block.o window.o
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${XXFLAGS} ${OBJECTS} -o ${EXEC} ${LIBS}
-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC}