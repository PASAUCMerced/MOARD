#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

#include "util.h"
#include "solve.h"


#define NUM_EVENTS 2
int main(int argc, char** argv)
{
    csr_matrix* A, *P, *R;
    ml ML;
    double* x0, *xstar, *b0, *residuals;
    int i, numSweep = 4, numIter = 1000;
    char path [1000];
    FILE* f;
    double tol = 1e-6;

    if (argc != 2) {
        printf("Error Usage: ./AMG.out /path/to/matrices\n");
        exit(argc);
    }

    printf("\n\n\n            Initializing Matrices\n---------------------------------------------------\n");
    strcpy(path, argv[1]);
    int len = strlen(path);
    strcat(path, "/info.txt");

    printf("Reading Directory:    %s\n", argv[1]);
    if ((f = fopen(path, "r")) == NULL) 
        return -1;

    fscanf(f, "%d", &ML.nlevel);
    printf("Number of Levels:    %d\n", ML.nlevel );
    A = (csr_matrix*) malloc(ML.nlevel * sizeof(csr_matrix));
    P = (csr_matrix*) malloc(ML.nlevel * sizeof(csr_matrix));
    R = (csr_matrix*) malloc(ML.nlevel * sizeof(csr_matrix));

    for (i = 0; i < ML.nlevel; i++) {
        /* read A */
        strcpy(path+len, "/A");
        sprintf(path + len + 2, "%d", i);
        strcat(path, ".mtx");
        readMM(path, &A[i]);
        printf("Read matrix file:    %s\n", path);

        /* read P */
        if (i < ML.nlevel-1) {
            path[len+1] = 'P';
            readMM(path, &P[i]);
            printf("Read matrix file:    %s\n", path);
        }

        /* read R */
        if (i < ML.nlevel-1) {
            path[len+1] = 'R';
            readMM(path, &R[i]);
            printf("Read matrix file:    %s\n\n", path);
        }
    }

    ML.levels = (level*) malloc(sizeof(level) * ML.nlevel);
    for (i = 0; i < ML.nlevel-1; i++) {
        ML.levels[i].A = &A[i];
        ML.levels[i].P = &P[i];
        ML.levels[i].R = &R[i];
    }

    /* Coarsest level doesn't have P and R matrices */
    ML.levels[i].A = &A[i];
    ML.levels[i].P = NULL;
    ML.levels[i].R = NULL;


    for (i = 0; i < ML.nlevel; i++) {
        ML.levels[i].x = (double*) malloc(sizeof(double) * ML.levels[i].A->n);
        ML.levels[i].b = (double*) malloc(sizeof(double) * ML.levels[i].A->n);
    }
    x0 = (double*) malloc(sizeof(double) * A[0].n);
    xstar = (double*) malloc(sizeof(double)*A[0].n);
    for(i = 0; i < A[0].n; i++) {
        x0[i] = rand() % 100;
        xstar[i] = 1.0;
    }
    b0 = calloc(A[0].n, sizeof(double));

    /* setting b0 based on xstar */
    csr_matvec(ML.levels[0].A, xstar, b0);

    /*solve Ax = b */
    printf("\n\n\n            Solving     Ax = b\n---------------------------------------------------\n");

    residuals = solve(ML, numSweep, numSweep, ML.nlevel, x0, b0, tol, numIter);
    for (i = 0; i < numIter; i++) {
        printf("residual[%d] = %g\n", i, residuals[i]);
        if (residuals[i] < tol)
            break;
    }
    printf("\n\nSolved ( %s ) to tolerance of %g in %d iterations!\n",
            i < numIter ? "YES" : "NO", tol, i);
    if (i < numIter) system("python refresh_fm_states.py");

#ifdef VERIFY_SYSTEM
    strcpy(path+len, "/A");
    sprintf(path + len + 2, "%d", 0);
    strcat(path, ".mtx");
    verify(ML, path);
#endif

#ifdef MATPLOTLIB
    printf("\nFor graphing in python:\n");
    printf("iteration = [");
    for (i =0; i < numIter; i++)
        printf("%d ,", i+1);
    printf("]\nresidual = [");
    for (i = 0; i < numIter; i++)
        printf("%g ,", residuals[i]);
    printf("]\n");
#endif

    // Freeing Memory
    for (i = 0; i < ML.nlevel-1; i++) {
        free(ML.levels[i].A->I);
        free(ML.levels[i].A->J);
        free(ML.levels[i].A->V);

        free(ML.levels[i].P->I);
        free(ML.levels[i].P->J);
        free(ML.levels[i].P->V);

        free(ML.levels[i].R->I);
        free(ML.levels[i].R->J);
        free(ML.levels[i].R->V);

        free(ML.levels[i].x);
        free(ML.levels[i].b);
    }
    free(ML.levels[i].A->I);
    free(ML.levels[i].A->J);
    free(ML.levels[i].A->V);
    free(ML.levels);

    free(A);
    free(P);
    free(R);
    free(x0);
    free(xstar);
    free(b0);

    return 0;
}
