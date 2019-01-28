#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "util.h"
#include "mmio.h"

#define EPS 1e-9



/*
 * Compute y = A*x for CSR matrix A and dense vectors x and y
 * A: CSR matrix
 * x: input vector
 * y: output vector (pre-allocated)
*/
void csr_matvec(const csr_matrix* A, const double* x, double* y) {
    int i, jj;
    double sum;
    for(i = 0; i < A->n; i++){
        sum = 0;
        for(jj = A->I[i]; jj < A->I[i+1]; jj++){
            sum += A->V[jj] * x[A->J[jj]];
        }
        y[i] = sum;
    }
}

/* Computes residual b-Ax */
void residual(const csr_matrix* A, const double* x, const double* b, double* Ax, double* res) {
        int i;
        csr_matvec(A, x, Ax);
        for(i=0; i< A->n; i++)
            res[i] = b[i]-Ax[i];
}

/* Computes norm of residual */
void residual_norm(const csr_matrix* A, const double* x, const double* b, double* Ax, double* residuals) {
        int i;
        double norm;

        csr_matvec(A, x, Ax);
        norm = 0.0;
        for(i=0; i< A->n; i++)
            norm += (b[i]-Ax[i]) * (b[i]-Ax[i]);
        *residuals = sqrt(norm);
}


void dot(const double* x, const double* y, const int n, double* dp) {
    int i;
    *dp = 0;
    for (i = 0; i < n; i++)
        *dp += x[i] * y[i];
}

/*
 * Jacobi relaxation
 *
 * A : csr_matrix pointer
 * x0 : initial guess
 * b : right-hand side
 * x : final solution (output)
 * omega: Jacobi weight
 * start, stop, step : start index, final index, stride
 *
 * note: ignores a zero (exactly) diagonal
 * note: no checking of index ranges
 * note: x is only modified in the range of rows
 */
void jacobi(const csr_matrix* A, const double* x0, const double* b,
        double* x, const double omega,
        const int start, const int stop, const int step) {

    int i, j, ja, jb, jj;
    double rsum, diag;
    for(i = start; i != stop; i += step) {
        ja = A->I[i];
        jb = A->I[i+1];
        rsum = 0.0;
        diag = 0.0;

        /* get the row sum and the diagonal */
        for(jj = ja; jj < jb; jj++){
            j = A->J[jj];
            if (i == j)
                diag  = A->V[jj];
            else
                rsum += A->V[jj]*x0[j];
        }

        /* put it together */
        if (diag != 0.0) {
            x[i] = (1.0 - omega) * x0[i] + omega * ((b[i] - rsum)/diag);
        }
    }
}

/* 
 * converts COO format to CSR format, in-place
 *
 * A : CSR matrix
 */
void coo2csr_in(csr_matrix* A) {
    double t, tnext;
    int i, j, k, init, ipos, inext, jnext;
    int *iwk = (int*) malloc((A->n+1) * sizeof(int));

    /* find pointer array for resulting matrix. */
    memset(iwk, 0, (A->n+1) * sizeof(int));
    for (i = 0; i < A->nnz; i++) {
        iwk[A->I[i]+1]++;
    }
    iwk[0] = 0;

    for (i = 1; i < A->n; i++)
        iwk[i] += iwk[i-1]; 

    k = 0;
    for (init = 0; init < A->nnz;) {
        t = A->V[init];
        i = A->I[init];
        j = A->J[init];
        A->I[init] = -1;
        
        while (k < A->nnz) {

            /* save the chased element */
            ipos = iwk[i]; 
            tnext = A->V[ipos];
            inext = A->I[ipos];
            jnext = A->J[ipos];
 
            /* then occupy its location */
            A->V[ipos] = t;
            A->J[ipos] = j;
            /* update pointer information for next element to come in row i
             * and determine next element to be chased */
            iwk[i] = ipos + 1;
            if (A->I[ipos] < 0)
                break;
            t = tnext;
            i = inext;
            j = jnext;
            A->I[ipos] = -1;
            k += 1;
          }
        init++;
        while (init > A->nnz && A->I[init] < 0)
            init++;
    } 

    for(i = 0; i < A->n; i++) 
        A->I[i+1] = iwk[i];
    A->I[0] = 0;
 
    /* sort each row by columns indices */
    for (i = 0; i < A->n; i++) {
        sort(A, i);
    }
    free(iwk); 
}

/*
 * Read a matrix market file using mmio, then put into the csr_matrix structure
 * 
 * filename : mm file
 * A : CSR matrix
 */
int readMM(const char filename[], csr_matrix* A) {
    int ret_code, i;
    MM_typecode matcode;
    FILE *f;;


    if ((f = fopen(filename, "r")) == NULL) 
        return -1;

    if (mm_read_banner(f, &matcode) != 0)
    {
        printf("Could not process Matrix Market banner.\n");
        return -1;
    }



    if (mm_is_complex(matcode) && mm_is_matrix(matcode) && 
            mm_is_sparse(matcode) )
    {
        printf("Sorry, this application does not support ");
        printf("Market Market type: [%s]\n", mm_typecode_to_str(matcode));
        return -1;
    }

    /* find out size of sparse matrix .... */

    if ((ret_code = mm_read_mtx_crd_size(f, &A->n, &A->m, &A->nnz)) !=0)
        return -1;

    A->I = (int *) malloc(A->nnz * sizeof(int));
    A->J = (int *) malloc(A->nnz * sizeof(int));
    A->V = (double *) malloc(A->nnz * sizeof(double));


    /* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
    /*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
    /*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

    for (i=0; i<A->nnz; i++)
    {
        fscanf(f, "%d %d %lg\n", &A->I[i], &A->J[i], &A->V[i]);
        A->I[i]--;  /* adjust from 1-based to 0-based */
        A->J[i]--;
    }

    if (f !=stdin) 
        fclose(f);
    coo2csr_in(A);

    return 0;
}

/*
 * Stores a  csr_matrix into matrix market file using mmio
 *
 * filename : mm file
 * A       : CSR matrix
 */
int writeMM(const char filename[], const csr_matrix* A) {
    FILE* f;
    MM_typecode matcode;
    int i;

    if ((f = fopen(filename, "w")) == NULL) 
        return -1;
    mm_write_banner(f, matcode);
    mm_write_mtx_crd_size(f, A->n, A->m, A->nnz);
    for (i = 0; i < A->nnz; i++)
        fprintf(f, "%d %d %lg\n", A->I[i]+1, A->J[i]+1, A->V[i]);
    fclose(f);
    return 0;
}

/*
 * Dumps a vector to a file on disk
 *
 * filename : file on disk to write to
 * x : vector to write
 * n : number of elements
*/
int writeVec(const char filename[], const double* x, int n) {
    FILE* f;
    int i;
    if ((f = fopen(filename, "w")) == NULL) 
        return -1;
    for (i = 0; i < n; i++)
        fprintf(f, "%lg\n", x[i]);
    fclose(f);
    return 0;
}


/* 
 * Exchanges two integers 
 */
void swapI(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}


/* 
 * Exchanges two doubles 
 */
void swapD(double* a, double* b) {
    double t = *a;
    *a = *b;
    *b = t;
}

/* 
 * Exchanges two double pointers
 */
void swapD_ptr(double** a, double** b) {
    double* t = *a;
    *a = *b;
    *b = t;
}

/* 
 * sorts row i's contents by column index 
 *
 * A : CSR matrix to sort the rows
 * i : row number to sort
 */
void sort(csr_matrix *A, int i) {
    int max, k;
    max = A->I[i+1]-1;
    for (k = A->I[i+1]-2; k > A->I[i]; k--)
        if (A->J[max] < A->J[k])
            max = k;

    swapI(&A->J[A->I[i+1]-1], &A->J[max]);
    swapD(&A->V[A->I[i+1]-1], &A->V[max]);
    quickSort(A, A->I[i], A->I[i+1]-2);
}

/*
 * Sorts column by column index. Data values change place as well.
 *
 * A: CSR matrix to be sorted
 * first: Left bound on column and value array
 * last: Right bound on column and value array
*/
void quickSort(csr_matrix *A, int first, int last) {

    int lower, upper, pivot;

    lower = first +1 ;
    upper = last;
    swapI(&A->J[first], &A->J[first + (last-first)/2]); 
    swapD(&A->V[first], &A->V[first + (last-first)/2]);
    pivot = A->J[first];
        
    for (; lower <= upper; lower++)
    {
        while(A->J[lower] < pivot)
            lower++;
        while(A->J[upper] > pivot)
            upper--;
        if (lower < upper)
        {
            swapI(&A->J[lower], &A->J[upper]);
            swapD(&A->V[lower], &A->V[upper]);
            upper--;
        }
    }
    swapI(&A->J[first], &A->J[upper]);
    swapD(&A->V[first], &A->V[upper]);

    if(first < upper-1)
        quickSort(A, first, upper-1);
    if(upper+1 < last)
        quickSort(A, upper+1, last);
}


int fp_equal(double a, double b) {
    return (fabs(a-b) < EPS);
}

/* Verifies the solution of a fault injected run and original system */
void verify(ml ML, char* path) {

    int i, mismatch = 0;
    csr_matrix A_gold;
    double* xstar, *bstar;
    csr_matrix* A = ML.levels[0].A;

    /* read A */
    printf("\n\nVerifying System and Solution\n----------------------------------\n");
    readMM(path, &A_gold);
    printf("Read matrix file:    %s\n", path);

    /* scalar data in CSR matrix */
    if (A_gold.n != A->n)
        printf("Missmatch in A->n: 1\n");
    else
        printf("Missmatch in A->n: 0\n");
    if (A_gold.m != A->m)
        printf("Missmatch in A->m: 1\n");
    else
        printf("Missmatch in A->m: 0\n");
    if (A_gold.nnz != A->nnz)
        printf("Missmatch in A->nnz: 1\n");
    else
        printf("Missmatch in A->nnz: 0\n");

    /* array data in CSR matrix */
    for (i = 0; i < A_gold.nnz; i++) {
        if (!fp_equal( A_gold.V[i], ML.levels[0].A->V[i]))
            mismatch++;
    }
    printf("Mismatches in A->V: %d\n", mismatch);

    mismatch = 0;
    for (i = 0; i < A_gold.nnz; i++) {
        if (A_gold.J[i] != ML.levels[0].A->J[i])
            mismatch++;
    }
    printf("Mismatches in A->J: %d\n", mismatch);

    mismatch = 0;
    for (i = 0; i < A_gold.n +1; i++) {
        if (A_gold.I[i] != ML.levels[0].A->I[i])
            mismatch++;
    }
    printf("Mismatches in A->I: %d\n", mismatch);

    /* setting b0 based on xstar */
    xstar = (double*) malloc(sizeof(double)*A_gold.n);
    bstar = (double*) malloc(sizeof(double)*A_gold.n);
    for (i=0; i < A_gold.n; i++)
        xstar[i] = 1.0;
    csr_matvec(&A_gold, xstar, bstar);

    /* check b */
    mismatch = 0;
    for (i=0; i<A_gold.n; i++) {
        if (!fp_equal( bstar[i], ML.levels[0].b[i]))
            mismatch++;
    }
    printf("Mismatchs in b: %d\n", mismatch);



    /* Verify to true solution */
    double diffNorm = 0.0, norm = 0.0;
    for (i=0; i < A_gold.n; i++)
    {
        double tmp = (xstar[i] - ML.levels[0].x[i]);
        diffNorm += tmp*tmp;
        norm += xstar[i]*xstar[i];
    }
    printf("L2-Norm diff: %g\n", sqrt(diffNorm));
    printf("Relative Error: %g\n", sqrt(diffNorm)/sqrt(norm));

    free(xstar);
    free(bstar);
    free(A_gold.I);
    free(A_gold.J);
    free(A_gold.V);
}
