/*
	Compile : g++ -o OpenMP  OpenMP-Strassen.cpp -fopenmp
	Run : ./OpenMP SIZE THRESHOLD #PROC
*/

#include <omp.h>
#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>
#include <fstream>
#include <iostream>
#include <ctime>
template < typename T >
T **Allocate2DArray( int nRows, int nCols)
{
    //(step 1) allocate memory for array of elements of column
    T **ppi = new T*[nRows];

    //(step 2) allocate memory for array of elements of each row
    T *curPtr = new T [nRows * nCols];

    // Now point the pointers in the right place
    for( int i = 0; i < nRows; ++i)
    {
        *(ppi + i) = curPtr;
         curPtr += nCols;
    }
    return ppi;
}

template < typename T >
void Free2DArray(T** Array)
{
    delete [] *Array;
    delete [] Array;
}

/*#define THRESHOLD  32768*/ /* product size below which matmultleaf is used */  
int THRESHOLD;

void seqMatMult(int m, int n, int p, int** A, int** B, int** C)   
{    
  for (int i = 0; i < m; i++)   
		for (int j = 0; j < n; j++)    
		{          
			C[i][j] = 0.0;   
			for (int k = 0; k < p; k++)   
				C[i][j] += A[i][k]*B[k][j];   
		}   
}  
  
void matmultleaf(int mf, int ml, int nf, int nl, int pf, int pl, int **A, int **B, int **C)    
/*  
  subroutine that uses the simple triple loop to multiply  
  a submatrix from A with a submatrix from B and store the  
  result in a submatrix of C.   
*/  
// mf, ml; /* first and last+1 i index */  
// nf, nl; /* first and last+1 j index */  
// pf, pl; /* first and last+1 k index */  
{      
	for (int i = mf; i < ml; i++)   
		for (int j = nf; j < nl; j++) {
			C[i][j] = 0.0;  
			for (int k = pf; k < pl; k++)   
				C[i][j] += A[i][k]*B[k][j];  
		} 
}   
  

void copyQtrMatrix(int **X, int m, int **Y, int mf, int nf)
{
	for (int i = 0; i < m; i++) 
		X[i] = &Y[mf+i][nf];
}

void AddMatBlocks(int **T, int m, int n, int **X, int **Y)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			T[i][j] = X[i][j] + Y[i][j];
}

void SubMatBlocks(int **T, int m, int n, int **X, int **Y)
{
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			T[i][j] = X[i][j] - Y[i][j];
}


void strassenMMult(int ml, int nl, int pl, int **A, int **B, int **C)
{
	if (((float)ml)*((float)nl)*((float)pl) <= THRESHOLD)   
		matmultleaf(0, ml, 0, nl, 0, pl, A, B, C); 

	else {
		int m2 = ml/2;
		int n2 = nl/2;
		int p2 = pl/2;

		int **M1 = Allocate2DArray< int >(m2, n2);
		int **M2 = Allocate2DArray< int >(m2, n2);
		int **M3 = Allocate2DArray< int >(m2, n2);
		int **M4 = Allocate2DArray< int >(m2, n2);
		int **M5 = Allocate2DArray< int >(m2, n2);
		int **M6 = Allocate2DArray< int >(m2, n2);
		int **M7 = Allocate2DArray< int >(m2, n2);

		int **wAM1 = Allocate2DArray< int >(m2, p2);
		int **wBM1 = Allocate2DArray< int >(p2, n2);
		int **wAM2 = Allocate2DArray< int >(m2, p2);
		int **wBM3 = Allocate2DArray< int >(p2, n2);
		int **wBM4 = Allocate2DArray< int >(p2, n2);
		int **wAM5 = Allocate2DArray< int >(m2, p2);
		int **wAM6 = Allocate2DArray< int >(m2, p2);
		int **wBM6 = Allocate2DArray< int >(p2, n2);
		int **wAM7 = Allocate2DArray< int >(m2, p2);
		int **wBM7 = Allocate2DArray< int >(p2, n2);

		int **A11 = new int*[m2];
		int **A12 = new int*[m2];
		int **A21 = new int*[m2];
		int **A22 = new int*[m2];

		int **B11 = new int*[p2];
		int **B12 = new int*[p2];
		int **B21 = new int*[p2];
		int **B22 = new int*[p2];

		int **C11 = new int*[m2];
		int **C12 = new int*[m2];
		int **C21 = new int*[m2];
		int **C22 = new int*[m2];

		copyQtrMatrix(A11, m2, A,  0,  0);
		copyQtrMatrix(A12, m2, A,  0, p2);
		copyQtrMatrix(A21, m2, A, m2,  0);
		copyQtrMatrix(A22, m2, A, m2, p2);

		copyQtrMatrix(B11, p2, B,  0,  0);
		copyQtrMatrix(B12, p2, B,  0, n2);
		copyQtrMatrix(B21, p2, B, p2,  0);
		copyQtrMatrix(B22, p2, B, p2, n2);

		copyQtrMatrix(C11, m2, C,  0,  0);
		copyQtrMatrix(C12, m2, C,  0, n2);
		copyQtrMatrix(C21, m2, C, m2,  0);
		copyQtrMatrix(C22, m2, C, m2, n2);

#pragma omp task
		{
	// M1 = (A11 + A22)*(B11 + B22)
		AddMatBlocks(wAM1, m2, p2, A11, A22);
		AddMatBlocks(wBM1, p2, n2, B11, B22);
		strassenMMult(m2, n2, p2, wAM1, wBM1, M1);
		}

#pragma omp task
		{
	//M2 = (A21 + A22)*B11
		AddMatBlocks(wAM2, m2, p2, A21, A22);
		strassenMMult(m2, n2, p2, wAM2, B11, M2);
		}

#pragma omp task
		{
	//M3 = A11*(B12 - B22)
		SubMatBlocks(wBM3, p2, n2, B12, B22);
		strassenMMult(m2, n2, p2, A11, wBM3, M3);
		}

#pragma omp task
		{
	//M4 = A22*(B21 - B11)
		SubMatBlocks(wBM4, p2, n2, B21, B11);
		strassenMMult(m2, n2, p2, A22, wBM4, M4);
		}

#pragma omp task
		{
	//M5 = (A11 + A12)*B22
		AddMatBlocks(wAM5, m2, p2, A11, A12);
		strassenMMult(m2, n2, p2, wAM5, B22, M5);
		}

#pragma omp task
		{
	//M6 = (A21 - A11)*(B11 + B12)
		SubMatBlocks(wAM6, m2, p2, A21, A11);
		AddMatBlocks(wBM6, p2, n2, B11, B12);
		strassenMMult(m2, n2, p2, wAM6, wBM6, M6);
		}

#pragma omp task
		{
	//M7 = (A12 - A22)*(B21 + B22)
		SubMatBlocks(wAM7, m2, p2, A12, A22);
		AddMatBlocks(wBM7, p2, n2, B21, B22);
		strassenMMult(m2, n2, p2, wAM7, wBM7, M7);
		}
#pragma omp taskwait

		for (int i = 0; i < m2; i++)
			for (int j = 0; j < n2; j++) {
				C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];
				C12[i][j] = M3[i][j] + M5[i][j];
				C21[i][j] = M2[i][j] + M4[i][j];
				C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];
			}

		Free2DArray< int >(M1);
		Free2DArray< int >(M2);
		Free2DArray< int >(M3);
		Free2DArray< int >(M4);
		Free2DArray< int >(M5);
		Free2DArray< int >(M6);
		Free2DArray< int >(M7);

		Free2DArray< int >(wAM1);
		Free2DArray< int >(wBM1);
		Free2DArray< int >(wAM2);
		Free2DArray< int >(wBM3);
		Free2DArray< int >(wBM4);
		Free2DArray< int >(wAM5);
		Free2DArray< int >(wAM6);
		Free2DArray< int >(wBM6);
		Free2DArray< int >(wAM7);
		Free2DArray< int >(wBM7);

		delete[] A11; delete[] A12; delete[] A21; delete[] A22;
		delete[] B11; delete[] B12; delete[] B21; delete[] B22;
		delete[] C11; delete[] C12; delete[] C21; delete[] C22;
	}
}
              
void matmultS(int m, int n, int p, int **A, int **B, int **C)
{   
#pragma omp parallel 
  {
#pragma omp single
	  {
    strassenMMult(m, n, p, A, B, C);
	  }
  }
}  

  
int main(int argc, char* argv[])   
{      

  int size = atoi(argv[1]);
  THRESHOLD = atoi(argv[2]);
  int proc = atoi(argv[3]);
  double start, end;

  int **A = Allocate2DArray< int >(size, size);
  int **B = Allocate2DArray< int >(size, size);
  int **C = Allocate2DArray< int >(size, size);

  int i, j;   


        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j){
            B[i][j] = 0;
            A[i][j] = 1;

            }

        for (int i = 0; i < size; ++i)
            B[i][i] = 1;

omp_set_dynamic(0);     // Explicitly disable dynamic teams
omp_set_num_threads(proc);

start = omp_get_wtime();
  matmultS(size, size, size, A, B, C);
  end = omp_get_wtime();

  double elapsed_secs = end - start;

        /*checking result if correct*/

        std::ofstream myfile;
  myfile.open ("results.txt",std::ofstream::app);

        bool correctness = true;
        for (int i = 0; i < size; ++i)
            for (int j = 0; j < size; ++j)
                if(C[i][j] != A[i][j]) correctness = false;
        if(correctness){
            printf("OpenMP - Correct: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec \n",  size, THRESHOLD,omp_get_max_threads(),elapsed_secs );
            myfile<<"OpenMP - Correct: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<omp_get_max_threads()<<" , Exec time = " << elapsed_secs << "\n";
        }
        else{
            printf("OpenMP - Incorrect: matrix size = %d, Threshold = %d,# of proc = %d, Exec time = %lf sec \n",  size, THRESHOLD,omp_get_max_threads(),elapsed_secs );
            myfile<<"OpenMP - Incorrect: matrix size = " <<size<<", Threshold = "<< THRESHOLD<<",# of proc = "<<omp_get_max_threads()<<" , Exec time = " << elapsed_secs << "\n";
        }
  myfile.close();



  Free2DArray< int >(A);
  Free2DArray< int >(B);
  Free2DArray< int >(C);

  return 0;   
}  
