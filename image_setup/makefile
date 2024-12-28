CPP := g++
CPPVERSION := c++17
OPENCV := `pkg-config --cflags --libs opencv4`

image_setup.out: image_setup.o
	$(CPP) -o image_setup.out image_setup.o $(OPENCV) -std=$(CPPVERSION)

image_setup.o: main.cpp
	$(CPP) -c main.cpp -o image_setup.o $(OPENCV) -std=$(CPPVERSION)

clean:
	rm -f image_setup.o image_setup.out
