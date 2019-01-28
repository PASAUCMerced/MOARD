#ifndef UTILH
#define UTILH

   


typedef struct {
    /* CSR matrix (sorted)
     *
     * I : row pointers
     * J : column indices
     * V : values
     * n : number of rows
     * m : number of columns
     * nnz : number of nonzeros
     */
    int* I;
    int* J;
    double* V;
    int n, m, nnz;
} csr_matrix;

typedef struct
{
    /*
     * A  : operator
     * P  : interpolation
     * R  : restriction
     * x  : solution
     * b  : RHS
     */
    csr_matrix* A;
    csr_matrix* P;
    csr_matrix* R;
    double* x;
    double* b; 
} level;

typedef struct
{
    /*
     * levels : list of level structs (A, P, R)
     * nlevel : number of levels
     */
    level*  levels;
    int     nlevel;
} ml;


void csr_matvec(const csr_matrix* A, const double* x, double* y);
void residual(const csr_matrix* A, const double* x, const double* b, 
        double* Ax, double* res);
void residual_norm(const csr_matrix* A, const double* x, const double* b, 
        double* Ax, double* residuals);
void dot(const double* x, const double* y, const int n, double* dp);
void jacobi(const csr_matrix* A, const double* x0, const double* b, 
        double* x, const double omega, const int start, const int stop, const int step); 

int readMM(const char filename[], csr_matrix* A);

void swapD_ptr(double** a, double** b);
void sort(csr_matrix *A, int i);
void quickSort(csr_matrix *A, int first, int last);

int writeVec(const char filename[], const double* x, int n);

int fp_equal(double a, double b);
void verify(ml ML, char* path);

#endif
