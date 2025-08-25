run: all
	./out/raytracer
	open img/*.ppm

all: objs
	echo "linking..."
	clang++ -std=c++20 -o out/raytracer out/*.o

objs: src/main.cpp src/camera.cpp
	echo "compiling..."
	clang++ -std=c++20 -Iinclude/ -c -o out/camera.o src/camera.cpp
	clang++ -std=c++20 -Iinclude/ -c -o out/main.o src/main.cpp

.PHONY: clean

clean:
	rm out/*.o
	rm out/raytracer

.PHONY: cleanimg

cleanimg:
	rm img/*
