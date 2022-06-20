/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"
#include "cblas.h"	//cblas_dgemm, cblas_dtrmm

/* 
 * Add your BLAS implementation here
 */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");

	// functie blas pentru inmultire de matrici
	double *BtxB = (double *)calloc(N * N, sizeof(double));
	cblas_dgemm(CblasRowMajor, CblasTrans, CblasNoTrans,
				N, N, N, 1.0, B, N, B, N, 1.0, BtxB, N);

	//functie blas pentru inmultit de matrici ce tine
	// cont ca A este superior triunghiulara
	double *BxA = B;
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans, CblasNonUnit,  
               N, N, 1.0, A, N, BxA, N);

	// functie blas pentru inmultire de matrici
	double *BxAxAt = (double *)calloc(N * N, sizeof(double));
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans,
            	N, N, N, 1.0, BxA, N, A, N, 1.0, BxAxAt, N);

	//adunarea matricilor pentru obtinerea rezultatului
	double *res = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[i * N + j] = BxAxAt[i * N + j] + BtxB[i * N + j];
		}
	}

	//eliberarea memoriei
	free(BxAxAt);
	free(BtxB);
	return res;
}
