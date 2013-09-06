// 2-D Gaussian filter example written in C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	// Declare variables
	int i,j,Nx,Ny,starttime,stoptime,count;
	float CPU_time;
	double w0,w1,w2;
	
	//......Initialize the domain size....................
	Nx = 2848;						// Dimensions of the image
	Ny = 4288;
	//.....................................................
	
	printf("Recursive Gaussian Filter \n");
	printf("Nx =%i \n",Nx);
	printf("Ny =%i \n",Ny);

	// Arrays to store the input and output data
	double *A;
	double *B;
	
	// Allocate memory to store the data
	A = (double*) malloc(Nx*Ny*sizeof(double));
	B = (double*) malloc(Nx*Ny*sizeof(double));
	
	// Read the input data from a binary file
	FILE *input;
	input = fopen("Tetons.dat","rb");
	fread(A,8,Nx*Ny,input);
	fclose(input);
	
	// pre-compute the filter weights
	w0 = 0.4444444444444444;
	w1 = 0.1111111111111111;
	w2 = 0.02777777777777778;
	
	// Create a timer to measure the execution time
	starttime = clock();	// start the timer
	for (count=0; count<10; count++){
		//********** EXECUTE THE GAUSSIAN FILTER **********************************************
		// Loop over the domain
		for (j=1; j<Ny-1; j++){
			for (i=1; i<Nx-1; i++){
				// Compute the filter and update the output array
				B[j*Nx+i] = w0*A[j*Nx+i] + w1*(A[j*Nx+i+1] + A[j*Nx+i-1] 
				                                               + A[(j+1)*Nx+i] + A[(j-1)*Nx+i])
				                                               + w2*(A[(j+1)*Nx+i+1] + A[(j+1)*Nx+i-1] 
				                                                                         + A[(j-1)*Nx+i+1] + A[(j-1)*Nx+i-1]); 
			}
		}
	}
	//*************************************************************************************
	stoptime = clock();		// stop the timer
	CPU_time = (double)(stoptime - starttime)/CLOCKS_PER_SEC*1.0e3;
	printf("Time to calculate the filter = %f milliseconds \n", CPU_time);
	
	// Write the output data to a binary file
	FILE *output;
	output = fopen("Smooth-Tetons.dat","wb");
	fwrite(B,8,Nx*Ny,output);
	fclose(output);
	
	// Free the memory
	free(A);
	free(B);
}