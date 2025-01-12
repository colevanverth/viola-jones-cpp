CPP := g++
CPPVERSION := c++17
OPENCV := `pkg-config --cflags --libs opencv4`
FILES := src/vjlearner.cpp src/integral_image.cpp src/wlearner.cpp src/wavelet.cpp src/pool.cpp
I_DIR := include/

train: 
	$(CPP) -I $(I_DIR) -o build/train.out $(OPENCV) src/train.cpp $(FILES) --std=$(CPPVERSION)

webcam:
	$(CPP) -I $(I_DIR) -o build/webcam.out $(OPENCV) src/webcam.cpp $(FILES) --std=$(CPPVERSION)

test:
	$(CPP) -I $(I_DIR) -o build/test.out $(OPENCV) tests/test.cpp $(FILES) --std=$(CPPVERSION)

clean:
	rm -rf build/*
