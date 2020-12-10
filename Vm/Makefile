CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = Vm
OBJECTS = main.o Model.o VmModel.o Reader.o FileReader.o Text.o VmText.o Writer.o FileWriter.o TerminalViewController.o ncursesViewController.o View.o VmTextView.o Controller.o KeyboardController.o VmKeyboardController.o Action.o Update.o Cursor.o VmCursor.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lncurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
