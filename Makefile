run: all
	./out/raytracer
	open img/*.ppm

all: objs
	echo "linking..."
	clang++ -o out/raytracer out/*.o

objs: src/main.cpp
	echo "compiling..."
	clang++ -c -o out/main.o src/main.cpp

.PHONY: clean

clean:
	rm out/*.o
	rm out/raytracer

.PHONY: cleanimg

cleanimg:
	rm img/*
