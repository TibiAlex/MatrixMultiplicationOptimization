/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");

	//calculam transpusele matricilor
	double *At = (double *)calloc(N * N, sizeof(double));
	double *Bt = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			At[j * N + i] = A[i * N + j];
			Bt[j * N + i] = B[i * N + j];
		}

	//calculam BtxB
	double *BtxB = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			BtxB[i * N + j] = 0;

			for (int k = 0; k < N; k++) {
				BtxB[i * N + j] += Bt[i * N + k] * B[k * N + j];
			}
		}
    }

	//calculam AxAt tinand cont ca A este superior triunghiulara
	double *AxAt = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			AxAt[i * N + j] = 0;

			for (int k = i; k < N; k++) {
				AxAt[i * N + j] += A[i * N + k] * At[k * N + j];
			}
		}
    }

	//calculam BxAxAt
	double *BxAxAt = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			BxAxAt[i * N + j] = 0;

			for (int k = 0; k < N; k++) {
				BxAxAt[i * N + j] += B[i * N + k] * AxAt[k * N + j];
			}
		}
    }

	//calculam rezultatul
	double *res = (double *)calloc(N * N, sizeof(double));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			res[i * N + j] = BxAxAt[i * N + j] + BtxB[i * N + j];
		}
	}

	free(At);
	free(Bt);
	free(BtxB);
	free(AxAt);
	free(BxAxAt);
	return res;
}
