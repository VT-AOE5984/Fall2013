CC=icc
CXX=icc
FORT=ifort

# build all of the executables at once
all:GaussFilter-C GaussFilter-CXX GaussFilter-Fort

#build individual executables here (-O0 flag turns off optimization)
GaussFilter-C:GaussFilter.c
	$(CC) -O0 -o GaussFilter-C GaussFilter.c

GaussFilter-CXX:GaussFilter.cpp
	$(CXX) -O0 -o GaussFilter-CXX GaussFilter.cpp

GaussFilter-Fort:GaussFilter.F90
	$(FORT) -O0 -o GaussFilter-Fort GaussFilter.F90

# Remove all of the compiled executables
clean:
	rm GaussFilter-C GaussFilter-CXX GaussFilter-Fort
