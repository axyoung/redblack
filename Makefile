PROGRAM = main.exe
CXXFLAGS = -Wall -g

$(PROGRAM): main.o node.o
	g++ -o $@ $^

clean:
	rm -f $(PROGRAM) *.o

run: $(PROGRAM)
	./$(PROGRAM)

main.o: main.cpp node.h
node.o: node.cpp node.h

