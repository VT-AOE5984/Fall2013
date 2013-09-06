// 2-D Gaussian filter example written in C++
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct  DoubleArray{
	int Length;
	int m;
	int n;
	double *data;

	DoubleArray(int nx, int ny){
			m = nx;
			n = ny;
			Length = m*n;
			data = new double [Length];
	}
	
	~DoubleArray(){
		delete data;
	}

	double & operator()(int i, int j){
		return data[j*m+i];
	}

	double *Pointer() {
		return data;
	}
};


main(int argc, char **argv)
{
	// Declare variables
	int i,j,Nx,Ny,starttime,stoptime;
	float CPU_time;
	double w0,w1,w2;
	string inputFile,outputFile;

	//......Initialize the input variables....................
	inputFile = "Tetons.dat";			// Name of the input image
	outputFile = "Smooth-Tetons.dat";	// Name of the output image
	Nx = 2848;							// Dimensions of the image
	Ny = 4288;
	//.....................................................

	printf("Recursive Gaussian Filter \n");
	printf("Nx =%i \n",Nx);
	printf("Ny =%i \n",Ny);
	
	// Arrays to store the input and output data
	DoubleArray A(Nx,Ny);
	DoubleArray B(Nx,Ny);
	
	// Read the A data from a binary file
	FILE *INPUT;
	INPUT = fopen(inputFile.c_str(),"rb");
	fread(A.data,8,Nx*Ny,INPUT);
	fclose(INPUT);
	
	// assign the filter weights
	w0 = 0.4444444444444444;
	w1 = 0.1111111111111111;
	w2 = 0.02777777777777778;
	
	// Create a timer to measure the execution time
	starttime = clock();	// start the timer
	//*****************************************************************************************
	// Run the Gaussian Filter recursively ten times
	for (int count=0; count<10; count++){
		//********** EXECUTE THE GAUSSIAN FILTER **********************************************
		for (j=1; j<Ny-1; j++){
			for (i=1; i<Nx-1; i++){
				// Compute the filter and update the B array
				B(i,j) = w0*A(i,j) + w1*(A(i+1,j)+A(i,j+1)+A(i-1,j)+A(i,j-1))
									+w2*(A(i+1,j+1)+A(i-1,j+1)+A(i-1,j-1)+A(i+1,j-1));
			}
		}
		// Over-write the old array with the new array
		for (j=1; j<Ny-1; j++){
			for (i=1; i<Nx-1; i++){
				A(i,j) = B(i,j);
			}
		}
	}
	//*****************************************************************************************
	stoptime = clock();		// stop the timer
	CPU_time = float(stoptime - starttime)/CLOCKS_PER_SEC*1.0e3;
	printf("CPU time = %f milliseconds \n", CPU_time);
	
	// Write the B data to a binary file
	FILE *OUTPUT;
	OUTPUT = fopen(outputFile.c_str(),"wb");
	fwrite(B.data,8,Nx*Ny,OUTPUT);
	fclose(OUTPUT);
}