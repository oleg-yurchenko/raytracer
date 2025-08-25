run: all
	./out/raytracer
	open img/*.ppm

all: objs
	echo "linking..."
	clang++ -std=c++20 -o out/raytracer out/*.o

objs: camera hittable_list sphere main
	echo "compiling..."

camera: src/camera.cpp
	clang++ -std=c++20 -Iinclude/ -c -o out/camera.o src/camera.cpp

hittable_list: src/hittable_list.cpp
	clang++ -std=c++20 -Iinclude/ -c -o out/hittable_list.o src/hittable_list.cpp

sphere: src/sphere.cpp
	clang++ -std=c++20 -Iinclude/ -c -o out/sphere.o src/sphere.cpp


main: src/main.cpp
	clang++ -std=c++20 -Iinclude/ -c -o out/main.o src/main.cpp


.PHONY: clean

clean:
	rm out/*.o
	rm out/raytracer

.PHONY: cleanimg

cleanimg:
	rm img/*
