OPT:=-O2 -multi

CXX = u++					# compiler
CXXFLAGS = -g -Wall -Wno-unused-label -MMD ${OPT}
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}	# makefile name

OBJECTS1 = main.o config.o bank.o bottlingplant.o nameserver.o parent.o printer.o student.o truck.o vendingmachine.o watcard.o watcardoffice.o  # list of object files
EXEC1 = soda

OBJECTS = ${OBJECTS1}		# all object files
DEPENDS = ${OBJECTS:.o=.d}			# substitute ".o" with ".d"
EXECS = ${EXEC1}			# all executables

.PHONY : all clean

all : ${EXECS}					# build all executables

#############################################################

${EXECS} : ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@

#############################################################

${OBJECTS} : ${MAKEFILE_NAME}			# OPTIONAL : changes to this file => recompile

-include ${DEPENDS}

clean :						# remove files that can be regenerated
	rm -f *.d *.o ${EXECS} 
