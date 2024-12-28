CPP := g++
CPPVERSION := c++17
OPENCV := `pkg-config --cflags --libs opencv4`

integral_image.out: main.o helpers.o
	$(CPP) -o integral_image.out main.o helpers.o $(OPENCV) -std=$(CPPVERSION)

main.o: main.cpp
	$(CPP) -c main.cpp $(OPENCV) -std=$(CPPVERSION)
	
helpers.o: helpers.cpp helpers.h
	$(CPP) -c helpers.cpp -o helpers.o $(OPENCV) -std=$(CPPVERSION)

test: helpers.o test.o
	$(CPP) -o test.out helpers.o test.o $(OPENCV) -std=$(CPPVERSION)

test.o: test.cpp
	$(CPP) -c test.cpp $(OPENCV) -std=$(CPPVERSION)

clean:
	rm -f main.o helpers.o integral_image.out test.o test.out
