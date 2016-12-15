billiard.exe: sphere.o hole.o object.o main.o
	g++ -Wall -o billiards.exe sphere.o hole.o object.o main.o -lglut -lGLU -lGL -lm
sphere.o: sphere.cpp util.h
	g++ -Wall -c sphere.cpp 
hole.o: hole.cpp util.h
	g++ -Wall -c hole.cpp
object.o: object.cpp
	g++ -Wall -c object.cpp
main.o: main.cpp
	g++ -Wall -c main.cpp
clean:
	rm -f *.o billiards.exe
