CC=g++
CFLAGS=-g -Wall
#Enable all warnings
DOXCONFIG=Doxyfile

#Build, archive, document code
all: build archive doc

build: college

college: college.o collegemain.o course.o
	$(CC) $(CFLAGS) -o college college.o collegemain.o course.o

college.o: college.cc college.h
	$(CC) $(CFLAGS) -c college.cc

collegemain.o: collegemain.cc college.h course.h
	$(CC) $(CFLAGS) -c collegemain.cc

course.o: course.cc course.h
	$(CC) $(CFLAGS) -c course.cc

doczip: college.tgz

college.tgz: college Makefile README.md html Doxyfile
	tar -cvz --exclude=*.o --exclude='college.tgz' -f college.tgz *

doc: html

#Update documentation files
html: $(DOXCONFIG) *.cc *.h
	doxygen $(DOXCONFIG)

#Clean up old .o files, executable, and archived file
clean:
	-rm -f *.o college college.tgz
	-rm -rf html