/*
 * Tema 2 ASC
 * 2022 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");

	//calculam transpusele matricilor
	double *At = (double *)calloc(N * N, sizeof(double));
	double *Bt = (double *)calloc(N * N, sizeof(double));
	for (register int i = 0; i < N; ++i) {
		register double *at = At + i;
		register double *bt = Bt + i;
		register double *a = A + i * N;
		register double *b = B + i * N;

		for (register int j = 0; j < N; j++) {
			*at = *a;
			*bt = *b;
			at += N;
			bt += N;
			a++;
			b++;
		}
	}

	//calculam BtxB
	double *BtxB = (double *)calloc(N * N, sizeof(double));
	for (register int i = 0; i < N; i++) {
		register double *orig_pa = Bt + i * N;
        register double *orig_pc = BtxB + i * N;
        register double *orig_pb = B;

		for (register int k = 0; k < N; k++) {
			register double *pc = orig_pc;
    		register double *pb = orig_pb;
			register double va = *orig_pa;

			for (register int j = 0; j < N; j++) {
				*pc += va * *pb;
                 pc++;
                 pb++;
			}
			orig_pa++;
            orig_pb += N;
		}
    }

	//calculam AxAt tinand cont ca A este superior triunghiulara
	double *AxAt = (double *)calloc(N * N, sizeof(double));
	for (register int i = 0; i < N; i++) {
		register double *orig_pa = A + i * N;

		for (register int j = 0; j < N; j++) {
			register double *pa = orig_pa + i;
    		register double *pb = At + i * N + j;
			register double suma = 0.0;

			for (register int k = i; k < N; k++) {
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			AxAt[i * N + j] = suma;
		}
    }

	//calculam BxAxAt
	double *BxAxAt = (double *)calloc(N * N, sizeof(double));
	for (register int i = 0; i < N; i++) {
		register  double *orig_pa = B + i * N;
        register double *orig_pc = BxAxAt + i * N;
        register double *orig_pb = AxAt;

		for (register int k = 0; k < N; k++) {
			register double *pb = orig_pb;
            register double *pc = orig_pc;
            register double va = *orig_pa;

			for (register int j = 0; j < N; j++) {
				*pc += va * *pb;
                 pc++;
                 pb++;
			}
			orig_pa++;
            orig_pb += N;
		}
    }

	//calculam rezultatul
	double *res = (double *)calloc(N * N, sizeof(double));
	for(register int i = 0; i < N; i++) {
		register double *res_ptr = res + i * N;
		register double *BxAxAt_ptr = BxAxAt + i * N;
		register double *BtxB_ptr = BtxB + i * N;

		for(register int j = 0; j < N; j++) {
			*res_ptr = *BxAxAt_ptr + *BtxB_ptr;
			res_ptr++;
			BxAxAt_ptr++;
			BtxB_ptr++;
		}
	}

	free(At);
	free(Bt);
	free(BtxB);
	free(AxAt);
	free(BxAxAt);
	return res;	
}
