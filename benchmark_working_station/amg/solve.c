#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
/*#include <vecLib/cblas.h> */
/*#include <vecLib/clapack.h> */
#include "util.h"

#include "math.h"
//#include "blaswrap.h"
//#include "f2c.h"
#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))
#define FALSE_ (0)
#define TRUE_ (1)
/*
        Input:
                hierarchy:
                nu1:            number of pre-smooth iterations
                nu2:            number of post-smooth iterations
                relax:          intialized relaxation method to use
                nlevels:        number of levels to use in the hierarchy 
                x0:                     initial guess to solution
                b:                      RHS of linear system (MUST be pre-allocated)
                tol:            tolerance 

        Output:
                residuals       array of the residual vector for each level

*/

/* implementation of dgesv_() by using the c implementation from 
 * http://www.netlib.org/clapack/old/double/dgesv.c
 * -Anzheng
 */

/**************** related function implementations of dgesv_() *********************/
static int c__1 = 1;
static float c_b163 = 0.f;
static float c_b164 = 1.f;
static int c__0 = 0;
static double c_b8 = -1.;

typedef float real;
static double c_b12 = 1.;
static int c_n1 = -1;
typedef char *address;
typedef short int shortint;
static double c_b32 = 0.;
typedef struct { float r, i; } complex;
typedef struct { double r, i; } doublecomplex;
typedef long int logical;
typedef short int shortlogical;
typedef char logical1;
typedef char int1;
typedef long long longint;      /* system-dependent */
typedef unsigned long long ulongint;    /* system-dependent */
typedef long int flag;
typedef long int ftnlen;
typedef long int ftnint;

/*external read, write*/
typedef struct
{	flag cierr;
	ftnint ciunit;
	flag ciend;
	char *cifmt;
	ftnint cirec;
} cilist;

//#ifdef KR_headers
//double floor();
//int i_nint(x) real *x;
//#else
//#undef abs

//#ifdef __cplusplus
//extern "C" {
//#endif
int i_nint(real *x)
{
return (int)(*x >= 0 ? floor(*x + .5) : -floor(.5 - *x));
}

double pow_di(double *ap, int *bp)
{
double pow, x;
int n;
unsigned long u;

pow = 1;
x = *ap;
n = *bp;

if(n != 0)
	{
	if(n < 0)
		{
		n = -n;
		x = 1/x;
		}
	for(u = n; ; )
		{
		if(u & 01)
			pow *= x;
		if(u >>= 1)
			x *= x;
		else
			break;
		}
	}
return(pow);
}


int s_cmp(char *a0, char *b0, ftnlen la, ftnlen lb)
{
register unsigned char *a, *aend, *b, *bend;
a = (unsigned char *)a0;
b = (unsigned char *)b0;
aend = a + la;
bend = b + lb;

if(la <= lb)
	{
	while(a < aend)
		if(*a != *b)
			return( *a - *b );
		else
			{ ++a; ++b; }

	while(b < bend)
		if(*b != ' ')
			return( ' ' - *b );
		else	++b;
	}

else
	{
	while(b < bend)
		if(*a == *b)
			{ ++a; ++b; }
		else
			return( *a - *b );
	while(a < aend)
		if(*a != ' ')
			return(*a - ' ');
		else	++a;
	}
return(0);
}

void s_copy(register char *a, register char *b, ftnlen la, ftnlen lb)
{
	register char *aend, *bend;

	aend = a + la;

	if(la <= lb)
		if (a <= b || a >= b + la)
			while(a < aend)
				*a++ = *b++;
		else
			for(b += la; a < aend; )
				*--aend = *--b;

	else {
		bend = b + lb;
		if (a <= b || a >= bend)
			while(b < bend)
				*a++ = *b++;
		else {
			a += lb;
			while(b < bend)
				*--a = *--bend;
			a += lb;
			}
		while(a < aend)
			*a++ = ' ';
		}
	}

int ieeeck_(int *ispec, real *zero, real *one)
{
    /* System generated locals */
    int ret_val;

    /* Local variables */
    real nan1, nan2, nan3, nan4, nan5, nan6, neginf, posinf, negzro, newzro;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  IEEECK is called from the ILAENV to verify that Infinity and */
/*  possibly NaN arithmetic is safe (i.e. will not trap). */

/*  Arguments */
/*  ========= */

/*  ISPEC   (input) int */
/*          Specifies whether to test just for inifinity arithmetic */
/*          or whether to test for infinity and NaN arithmetic. */
/*          = 0: Verify infinity arithmetic only. */
/*          = 1: Verify infinity and NaN arithmetic. */

/*  ZERO    (input) REAL */
/*          Must contain the value 0.0 */
/*          This is passed to prevent the compiler from optimizing */
/*          away this code. */

/*  ONE     (input) REAL */
/*          Must contain the value 1.0 */
/*          This is passed to prevent the compiler from optimizing */
/*          away this code. */

/*  RETURN VALUE:  int */
/*          = 0:  Arithmetic failed to produce the correct answers */
/*          = 1:  Arithmetic produced the correct answers */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */
    ret_val = 1;

    posinf = *one / *zero;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }

    neginf = -(*one) / *zero;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    negzro = *one / (neginf + *one);
    if (negzro != *zero) {
	ret_val = 0;
	return ret_val;
    }

    neginf = *one / negzro;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    newzro = negzro + *zero;
    if (newzro != *zero) {
	ret_val = 0;
	return ret_val;
    }

    posinf = *one / newzro;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }

    neginf *= posinf;
    if (neginf >= *zero) {
	ret_val = 0;
	return ret_val;
    }

    posinf *= posinf;
    if (posinf <= *one) {
	ret_val = 0;
	return ret_val;
    }


/*     Return if we were only asked to check infinity arithmetic */

    if (*ispec == 0) {
	return ret_val;
    }

    nan1 = posinf + neginf;

    nan2 = posinf / neginf;

    nan3 = posinf / posinf;

    nan4 = posinf * *zero;

    nan5 = neginf * negzro;

    nan6 = nan5 * 0.f;

    if (nan1 == nan1) {
	ret_val = 0;
	return ret_val;
    }

    if (nan2 == nan2) {
	ret_val = 0;
	return ret_val;
    }

    if (nan3 == nan3) {
	ret_val = 0;
	return ret_val;
    }

    if (nan4 == nan4) {
	ret_val = 0;
	return ret_val;
    }

    if (nan5 == nan5) {
	ret_val = 0;
	return ret_val;
    }

    if (nan6 == nan6) {
	ret_val = 0;
	return ret_val;
    }

    return ret_val;
} 

/* Subroutine */ int dger_(int *m, int *n, double *alpha, 
	double *x, int *incx, double *y, int *incy, 
	double *a, int *lda)
{
    /* System generated locals */
    int a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    int i__, j, ix, jy, kx, info;
    double temp;
    extern /* Subroutine */ int xerbla_(char *, int *);

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGER   performs the rank 1 operation */

/*     A := alpha*x*y' + A, */

/*  where alpha is a scalar, x is an m element vector, y is an n element */
/*  vector and A is an m by n matrix. */

/*  Arguments */
/*  ========== */

/*  M      - int. */
/*           On entry, M specifies the number of rows of the matrix A. */
/*           M must be at least zero. */
/*           Unchanged on exit. */

/*  N      - int. */
/*           On entry, N specifies the number of columns of the matrix A. */
/*           N must be at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  X      - DOUBLE PRECISION array of dimension at least */
/*           ( 1 + ( m - 1 )*abs( INCX ) ). */
/*           Before entry, the incremented array X must contain the m */
/*           element vector x. */
/*           Unchanged on exit. */

/*  INCX   - int. */
/*           On entry, INCX specifies the increment for the elements of */
/*           X. INCX must not be zero. */
/*           Unchanged on exit. */

/*  Y      - DOUBLE PRECISION array of dimension at least */
/*           ( 1 + ( n - 1 )*abs( INCY ) ). */
/*           Before entry, the incremented array Y must contain the n */
/*           element vector y. */
/*           Unchanged on exit. */

/*  INCY   - int. */
/*           On entry, INCY specifies the increment for the elements of */
/*           Y. INCY must not be zero. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ). */
/*           Before entry, the leading m by n part of the array A must */
/*           contain the matrix of coefficients. On exit, A is */
/*           overwritten by the updated matrix. */

/*  LDA    - int. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. LDA must be at least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 2 Blas routine. */

/*  -- Written on 22-October-1986. */
/*     Jack Dongarra, Argonne National Lab. */
/*     Jeremy Du Croz, Nag Central Office. */
/*     Sven Hammarling, Nag Central Office. */
/*     Richard Hanson, Sandia National Labs. */


/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    --x;
    --y;
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    info = 0;
    if (*m < 0) {
	info = 1;
    } else if (*n < 0) {
	info = 2;
    } else if (*incx == 0) {
	info = 5;
    } else if (*incy == 0) {
	info = 7;
    } else if (*lda < max(1,*m)) {
	info = 9;
    }
    if (info != 0) {
	xerbla_("DGER  ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || *alpha == 0.) {
	return 0;
    }

/*     Start the operations. In this version the elements of A are */
/*     accessed sequentially with one pass through A. */

    if (*incy > 0) {
	jy = 1;
    } else {
	jy = 1 - (*n - 1) * *incy;
    }
    if (*incx == 1) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (y[jy] != 0.) {
		temp = *alpha * y[jy];
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    a[i__ + j * a_dim1] += x[i__] * temp;
/* L10: */
		}
	    }
	    jy += *incy;
/* L20: */
	}
    } else {
	if (*incx > 0) {
	    kx = 1;
	} else {
	    kx = 1 - (*m - 1) * *incx;
	}
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    if (y[jy] != 0.) {
		temp = *alpha * y[jy];
		ix = kx;
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    a[i__ + j * a_dim1] += x[ix] * temp;
		    ix += *incx;
/* L30: */
		}
	    }
	    jy += *incy;
/* L40: */
	}
    }

    return 0;

/*     End of DGER  . */

} /* dger_ */

/* Subroutine */ int dscal_(int *n, double *da, double *dx, 
	int *incx)
{
    /* System generated locals */
    int i__1, i__2;

    /* Local variables */
    int i__, m, mp1, nincx;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */
/* * */
/*     scales a vector by a constant. */
/*     uses unrolled loops for increment equal to one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    if (*n <= 0 || *incx <= 0) {
	return 0;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    nincx = *n * *incx;
    i__1 = nincx;
    i__2 = *incx;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	dx[i__] = *da * dx[i__];
/* L10: */
    }
    return 0;

/*        code for increment equal to 1 */


/*        clean-up loop */

L20:
    m = *n % 5;
    if (m == 0) {
	goto L40;
    }
    i__2 = m;
    for (i__ = 1; i__ <= i__2; ++i__) {
	dx[i__] = *da * dx[i__];
/* L30: */
    }
    if (*n < 5) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__2 = *n;
    for (i__ = mp1; i__ <= i__2; i__ += 5) {
	dx[i__] = *da * dx[i__];
	dx[i__ + 1] = *da * dx[i__ + 1];
	dx[i__ + 2] = *da * dx[i__ + 2];
	dx[i__ + 3] = *da * dx[i__ + 3];
	dx[i__ + 4] = *da * dx[i__ + 4];
/* L50: */
    }
    return 0;
} /* dscal_ */

/* Subroutine */ int dswap_(int *n, double *dx, int *incx, 
	double *dy, int *incy)
{
    /* System generated locals */
    int i__1;

    /* Local variables */
    int i__, m, ix, iy, mp1;
    double dtemp;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     interchanges two vectors. */
/*     uses unrolled loops for increments equal one. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {
	goto L20;
    }

/*       code for unequal increments or equal increments not equal */
/*         to 1 */

    ix = 1;
    iy = 1;
    if (*incx < 0) {
	ix = (-(*n) + 1) * *incx + 1;
    }
    if (*incy < 0) {
	iy = (-(*n) + 1) * *incy + 1;
    }
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = dx[ix];
	dx[ix] = dy[iy];
	dy[iy] = dtemp;
	ix += *incx;
	iy += *incy;
/* L10: */
    }
    return 0;

/*       code for both increments equal to 1 */


/*       clean-up loop */

L20:
    m = *n % 3;
    if (m == 0) {
	goto L40;
    }
    i__1 = m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dtemp = dx[i__];
	dx[i__] = dy[i__];
	dy[i__] = dtemp;
/* L30: */
    }
    if (*n < 3) {
	return 0;
    }
L40:
    mp1 = m + 1;
    i__1 = *n;
    for (i__ = mp1; i__ <= i__1; i__ += 3) {
	dtemp = dx[i__];
	dx[i__] = dy[i__];
	dy[i__] = dtemp;
	dtemp = dx[i__ + 1];
	dx[i__ + 1] = dy[i__ + 1];
	dy[i__ + 1] = dtemp;
	dtemp = dx[i__ + 2];
	dx[i__ + 2] = dy[i__ + 2];
	dy[i__ + 2] = dtemp;
/* L50: */
    }
    return 0;
} /* dswap_ */

int idamax_(int *n, double *dx, int *incx)
{
    /* System generated locals */
    int ret_val, i__1;
    double d__1;

    /* Local variables */
    int i__, ix;
    double dmax__;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     finds the index of element having max. absolute value. */
/*     jack dongarra, linpack, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */


/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    ret_val = 0;
    if (*n < 1 || *incx <= 0) {
	return ret_val;
    }
    ret_val = 1;
    if (*n == 1) {
	return ret_val;
    }
    if (*incx == 1) {
	goto L20;
    }

/*        code for increment not equal to 1 */

    ix = 1;
    dmax__ = abs(dx[1]);
    ix += *incx;
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if ((d__1 = dx[ix], abs(d__1)) <= dmax__) {
	    goto L5;
	}
	ret_val = i__;
	dmax__ = (d__1 = dx[ix], abs(d__1));
L5:
	ix += *incx;
/* L10: */
    }
    return ret_val;

/*        code for increment equal to 1 */

L20:
    dmax__ = abs(dx[1]);
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if ((d__1 = dx[i__], abs(d__1)) <= dmax__) {
	    goto L30;
	}
	ret_val = i__;
	dmax__ = (d__1 = dx[i__], abs(d__1));
L30:
	;
    }
    return ret_val;
} /* idamax_ */

/* Subroutine */ int dgetf2_(int *m, int *n, double *a, int *
	lda, int *ipiv, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, i__1, i__2, i__3;
    double d__1;

    /* Local variables */
    int i__, j, jp;
    extern /* Subroutine */ int dger_(int *, int *, double *, 
	    double *, int *, double *, int *, double *, 
	    int *), dscal_(int *, double *, double *, int 
	    *);
    double sfmin;
    extern /* Subroutine */ int dswap_(int *, double *, int *, 
	    double *, int *);
    extern double dlamch_(char *);
    extern int idamax_(int *, double *, int *);
    extern /* Subroutine */ int xerbla_(char *, int *);


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETF2 computes an LU factorization of a general m-by-n matrix A */
/*  using partial pivoting with row interchanges. */

/*  The factorization has the form */
/*     A = P * L * U */
/*  where P is a permutation matrix, L is lower triangular with unit */
/*  diagonal elements (lower trapezoidal if m > n), and U is upper */
/*  triangular (upper trapezoidal if m < n). */

/*  This is the right-looking Level 2 BLAS version of the algorithm. */

/*  Arguments */
/*  ========= */

/*  M       (input) int */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) int */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the m by n matrix to be factored. */
/*          On exit, the factors L and U from the factorization */
/*          A = P*L*U; the unit diagonal elements of L are not stored. */

/*  LDA     (input) int */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  IPIV    (output) int array, dimension (min(M,N)) */
/*          The pivot indices; for 1 <= i <= min(M,N), row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  INFO    (output) int */
/*          = 0: successful exit */
/*          < 0: if INFO = -k, the k-th argument had an illegal value */
/*          > 0: if INFO = k, U(k,k) is exactly zero. The factorization */
/*               has been completed, but the factor U is exactly */
/*               singular, and division by zero will occur if it is used */
/*               to solve a system of equations. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETF2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Compute machine safe minimum */

    sfmin = dlamch_("S");

    i__1 = min(*m,*n);
    for (j = 1; j <= i__1; ++j) {

/*        Find pivot and test for singularity. */

	i__2 = *m - j + 1;
	jp = j - 1 + idamax_(&i__2, &a[j + j * a_dim1], &c__1);
	ipiv[j] = jp;
	if (a[jp + j * a_dim1] != 0.) {

/*           Apply the interchange to columns 1:N. */

	    if (jp != j) {
		dswap_(n, &a[j + a_dim1], lda, &a[jp + a_dim1], lda);
	    }

/*           Compute elements J+1:M of J-th column. */

	    if (j < *m) {
		if ((d__1 = a[j + j * a_dim1], abs(d__1)) >= sfmin) {
		    i__2 = *m - j;
		    d__1 = 1. / a[j + j * a_dim1];
		    dscal_(&i__2, &d__1, &a[j + 1 + j * a_dim1], &c__1);
		} else {
		    i__2 = *m - j;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			a[j + i__ + j * a_dim1] /= a[j + j * a_dim1];
/* L20: */
		    }
		}
	    }

	} else if (*info == 0) {

	    *info = j;
	}

	if (j < min(*m,*n)) {

/*           Update trailing submatrix. */

	    i__2 = *m - j;
	    i__3 = *n - j;
	    dger_(&i__2, &i__3, &c_b8, &a[j + 1 + j * a_dim1], &c__1, &a[j + (
		    j + 1) * a_dim1], lda, &a[j + 1 + (j + 1) * a_dim1], lda);
	}
/* L10: */
    }
    return 0;

/*     End of DGETF2 */

} /* dgetf2_ */

int iparmq_(int *ispec, char *name__, char *opts, int *n, int 
	*ilo, int *ihi, int *lwork)
{
    /* System generated locals */
    int ret_val, i__1, i__2;
    real r__1;

    /* Builtin functions */
    double log(double);
    int i_nint(real *);

    /* Local variables */
    int nh, ns;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */

/*  Purpose */
/*  ======= */

/*       This program sets problem and machine dependent parameters */
/*       useful for xHSEQR and its subroutines. It is called whenever */
/*       ILAENV is called with 12 <= ISPEC <= 16 */

/*  Arguments */
/*  ========= */

/*       ISPEC  (input) int scalar */
/*              ISPEC specifies which tunable parameter IPARMQ should */
/*              return. */

/*              ISPEC=12: (INMIN)  Matrices of order nmin or less */
/*                        are sent directly to xLAHQR, the implicit */
/*                        double shift QR algorithm.  NMIN must be */
/*                        at least 11. */

/*              ISPEC=13: (INWIN)  Size of the deflation window. */
/*                        This is best set greater than or equal to */
/*                        the number of simultaneous shifts NS. */
/*                        Larger matrices benefit from larger deflation */
/*                        windows. */

/*              ISPEC=14: (INIBL) Determines when to stop nibbling and */
/*                        invest in an (expensive) multi-shift QR sweep. */
/*                        If the aggressive early deflation subroutine */
/*                        finds LD converged eigenvalues from an order */
/*                        NW deflation window and LD.GT.(NW*NIBBLE)/100, */
/*                        then the next QR sweep is skipped and early */
/*                        deflation is applied immediately to the */
/*                        remaining active diagonal block.  Setting */
/*                        IPARMQ(ISPEC=14) = 0 causes TTQRE to skip a */
/*                        multi-shift QR sweep whenever early deflation */
/*                        finds a converged eigenvalue.  Setting */
/*                        IPARMQ(ISPEC=14) greater than or equal to 100 */
/*                        prevents TTQRE from skipping a multi-shift */
/*                        QR sweep. */

/*              ISPEC=15: (NSHFTS) The number of simultaneous shifts in */
/*                        a multi-shift QR iteration. */

/*              ISPEC=16: (IACC22) IPARMQ is set to 0, 1 or 2 with the */
/*                        following meanings. */
/*                        0:  During the multi-shift QR sweep, */
/*                            xLAQR5 does not accumulate reflections and */
/*                            does not use matrix-matrix multiply to */
/*                            update the far-from-diagonal matrix */
/*                            entries. */
/*                        1:  During the multi-shift QR sweep, */
/*                            xLAQR5 and/or xLAQRaccumulates reflections and uses */
/*                            matrix-matrix multiply to update the */
/*                            far-from-diagonal matrix entries. */
/*                        2:  During the multi-shift QR sweep. */
/*                            xLAQR5 accumulates reflections and takes */
/*                            advantage of 2-by-2 block structure during */
/*                            matrix-matrix multiplies. */
/*                        (If xTRMM is slower than xGEMM, then */
/*                        IPARMQ(ISPEC=16)=1 may be more efficient than */
/*                        IPARMQ(ISPEC=16)=2 despite the greater level of */
/*                        arithmetic work implied by the latter choice.) */

/*       NAME    (input) character string */
/*               Name of the calling subroutine */

/*       OPTS    (input) character string */
/*               This is a concatenation of the string arguments to */
/*               TTQRE. */

/*       N       (input) int scalar */
/*               N is the order of the Hessenberg matrix H. */

/*       ILO     (input) int */
/*       IHI     (input) int */
/*               It is assumed that H is already upper triangular */
/*               in rows and columns 1:ILO-1 and IHI+1:N. */

/*       LWORK   (input) int scalar */
/*               The amount of workspace available. */

/*  Further Details */
/*  =============== */

/*       Little is known about how best to choose these parameters. */
/*       It is possible to use different values of the parameters */
/*       for each of CHSEQR, DHSEQR, SHSEQR and ZHSEQR. */

/*       It is probably best to choose different parameters for */
/*       different matrices and different parameters at different */
/*       times during the iteration, but this has not been */
/*       implemented --- yet. */


/*       The best choices of most of the parameters depend */
/*       in an ill-understood way on the relative execution */
/*       rate of xLAQR3 and xLAQR5 and on the nature of each */
/*       particular eigenvalue problem.  Experiment may be the */
/*       only practical way to determine which choices are most */
/*       effective. */

/*       Following is a list of default values supplied by IPARMQ. */
/*       These defaults may be adjusted in order to attain better */
/*       performance in any particular computational environment. */

/*       IPARMQ(ISPEC=12) The xLAHQR vs xLAQR0 crossover point. */
/*                        Default: 75. (Must be at least 11.) */

/*       IPARMQ(ISPEC=13) Recommended deflation window size. */
/*                        This depends on ILO, IHI and NS, the */
/*                        number of simultaneous shifts returned */
/*                        by IPARMQ(ISPEC=15).  The default for */
/*                        (IHI-ILO+1).LE.500 is NS.  The default */
/*                        for (IHI-ILO+1).GT.500 is 3*NS/2. */

/*       IPARMQ(ISPEC=14) Nibble crossover point.  Default: 14. */

/*       IPARMQ(ISPEC=15) Number of simultaneous shifts, NS. */
/*                        a multi-shift QR iteration. */

/*                        If IHI-ILO+1 is ... */

/*                        greater than      ...but less    ... the */
/*                        or equal to ...      than        default is */

/*                                0               30       NS =   2+ */
/*                               30               60       NS =   4+ */
/*                               60              150       NS =  10 */
/*                              150              590       NS =  ** */
/*                              590             3000       NS =  64 */
/*                             3000             6000       NS = 128 */
/*                             6000             infinity   NS = 256 */

/*                    (+)  By default matrices of this order are */
/*                         passed to the implicit double shift routine */
/*                         xLAHQR.  See IPARMQ(ISPEC=12) above.   These */
/*                         values of NS are used only in case of a rare */
/*                         xLAHQR failure. */

/*                    (**) The asterisks (**) indicate an ad-hoc */
/*                         function increasing from 10 to 64. */

/*       IPARMQ(ISPEC=16) Select structured matrix multiply. */
/*                        (See ISPEC=16 above for details.) */
/*                        Default: 3. */

/*     ================================================================ */
/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */
    if (*ispec == 15 || *ispec == 13 || *ispec == 16) {

/*        ==== Set the number simultaneous shifts ==== */

	nh = *ihi - *ilo + 1;
	ns = 2;
	if (nh >= 30) {
	    ns = 4;
	}
	if (nh >= 60) {
	    ns = 10;
	}
	if (nh >= 150) {
/* Computing MAX */
	    r__1 = log((real) nh) / log(2.f);
	    i__1 = 10, i__2 = nh / i_nint(&r__1);
	    ns = max(i__1,i__2);
	}
	if (nh >= 590) {
	    ns = 64;
	}
	if (nh >= 3000) {
	    ns = 128;
	}
	if (nh >= 6000) {
	    ns = 256;
	}
/* Computing MAX */
	i__1 = 2, i__2 = ns - ns % 2;
	ns = max(i__1,i__2);
    }

    if (*ispec == 12) {


/*        ===== Matrices of order smaller than NMIN get sent */
/*        .     to xLAHQR, the classic double shift algorithm. */
/*        .     This must be at least 11. ==== */

	ret_val = 75;

    } else if (*ispec == 14) {

/*        ==== INIBL: skip a multi-shift qr iteration and */
/*        .    whenever aggressive early deflation finds */
/*        .    at least (NIBBLE*(window size)/100) deflations. ==== */

	ret_val = 14;

    } else if (*ispec == 15) {

/*        ==== NSHFTS: The number of simultaneous shifts ===== */

	ret_val = ns;

    } else if (*ispec == 13) {

/*        ==== NW: deflation window size.  ==== */

	if (nh <= 500) {
	    ret_val = ns;
	} else {
	    ret_val = ns * 3 / 2;
	}

    } else if (*ispec == 16) {

/*        ==== IACC22: Whether to accumulate reflections */
/*        .     before updating the far-from-diagonal elements */
/*        .     and whether to use 2-by-2 block structure while */
/*        .     doing it.  A small amount of work could be saved */
/*        .     by making this choice dependent also upon the */
/*        .     NH=IHI-ILO+1. */

	ret_val = 0;
	if (ns >= 14) {
	    ret_val = 1;
	}
	if (ns >= 14) {
	    ret_val = 2;
	}

    } else {
/*        ===== invalid value of ispec ===== */
	ret_val = -1;

    }

/*     ==== End of IPARMQ ==== */

    return ret_val;
} /* iparmq_ */


/* Subroutine */ int dgetrs_(char *trans, int *n, int *nrhs, 
	double *a, int *lda, int *ipiv, double *b, int *
	ldb, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, b_dim1, b_offset, i__1;

    /* Local variables */
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *, 
	    int *, int *, double *, double *, int *, 
	    double *, int *), xerbla_(
	    char *, int *), dlaswp_(int *, double *, 
	    int *, int *, int *, int *, int *);
    logical notran;


/*  -- LAPACK routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETRS solves a system of linear equations */
/*     A * X = B  or  A' * X = B */
/*  with a general N-by-N matrix A using the LU factorization computed */
/*  by DGETRF. */

/*  Arguments */
/*  ========= */

/*  TRANS   (input) CHARACTER*1 */
/*          Specifies the form of the system of equations: */
/*          = 'N':  A * X = B  (No transpose) */
/*          = 'T':  A'* X = B  (Transpose) */
/*          = 'C':  A'* X = B  (Conjugate transpose = Transpose) */

/*  N       (input) int */
/*          The order of the matrix A.  N >= 0. */

/*  NRHS    (input) int */
/*          The number of right hand sides, i.e., the number of columns */
/*          of the matrix B.  NRHS >= 0. */

/*  A       (input) DOUBLE PRECISION array, dimension (LDA,N) */
/*          The factors L and U from the factorization A = P*L*U */
/*          as computed by DGETRF. */

/*  LDA     (input) int */
/*          The leading dimension of the array A.  LDA >= max(1,N). */

/*  IPIV    (input) int array, dimension (N) */
/*          The pivot indices from DGETRF; for 1<=i<=N, row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS) */
/*          On entry, the right hand side matrix B. */
/*          On exit, the solution matrix X. */

/*  LDB     (input) int */
/*          The leading dimension of the array B.  LDB >= max(1,N). */

/*  INFO    (output) int */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    notran = lsame_(trans, "N");
    if (! notran && ! lsame_(trans, "T") && ! lsame_(
	    trans, "C")) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*nrhs < 0) {
	*info = -3;
    } else if (*lda < max(1,*n)) {
	*info = -5;
    } else if (*ldb < max(1,*n)) {
	*info = -8;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETRS", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *nrhs == 0) {
	return 0;
    }

    if (notran) {

/*        Solve A * X = B. */

/*        Apply row interchanges to the right hand sides. */

	dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c__1);

/*        Solve L*X = B, overwriting B with X. */

	dtrsm_("Left", "Lower", "No transpose", "Unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Solve U*X = B, overwriting B with X. */

	dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &c_b12, &
		a[a_offset], lda, &b[b_offset], ldb);
    } else {

/*        Solve A' * X = B. */

/*        Solve U'*X = B, overwriting B with X. */

	dtrsm_("Left", "Upper", "Transpose", "Non-unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Solve L'*X = B, overwriting B with X. */

	dtrsm_("Left", "Lower", "Transpose", "Unit", n, nrhs, &c_b12, &a[
		a_offset], lda, &b[b_offset], ldb);

/*        Apply row interchanges to the solution vectors. */

	dlaswp_(nrhs, &b[b_offset], ldb, &c__1, n, &ipiv[1], &c_n1);
    }

    return 0;

/*     End of DGETRS */

} /* dgetrs_ */

static double c_b11 = -1.;

logical lsame_(char *ca, char *cb)
{
    /* System generated locals */
    logical ret_val;

    /* Local variables */
    int inta, intb, zcode;


/*  -- LAPACK auxiliary routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  LSAME returns .TRUE. if CA is the same letter as CB regardless of */
/*  case. */

/*  Arguments */
/*  ========= */

/*  CA      (input) CHARACTER*1 */

/*  CB      (input) CHARACTER*1 */
/*          CA and CB specify the single characters to be compared. */

/* ===================================================================== */

/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */

/*     Test if the characters are equal */

    ret_val = *(unsigned char *)ca == *(unsigned char *)cb;
    if (ret_val) {
	return ret_val;
    }

/*     Now test for equivalence if both characters are alphabetic. */

    zcode = 'Z';

/*     Use 'Z' rather than 'A' so that ASCII can be detected on Prime */
/*     machines, on which ICHAR returns a value with bit 8 set. */
/*     ICHAR('A') on Prime machines returns 193 which is the same as */
/*     ICHAR('A') on an EBCDIC machine. */

    inta = *(unsigned char *)ca;
    intb = *(unsigned char *)cb;

    if (zcode == 90 || zcode == 122) {

/*        ASCII is assumed - ZCODE is the ASCII code of either lower or */
/*        upper case 'Z'. */

	if (inta >= 97 && inta <= 122) {
	    inta += -32;
	}
	if (intb >= 97 && intb <= 122) {
	    intb += -32;
	}

    } else if (zcode == 233 || zcode == 169) {

/*        EBCDIC is assumed - ZCODE is the EBCDIC code of either lower or */
/*        upper case 'Z'. */

	if (inta >= 129 && inta <= 137 || inta >= 145 && inta <= 153 || inta 
		>= 162 && inta <= 169) {
	    inta += 64;
	}
	if (intb >= 129 && intb <= 137 || intb >= 145 && intb <= 153 || intb 
		>= 162 && intb <= 169) {
	    intb += 64;
	}

    } else if (zcode == 218 || zcode == 250) {

/*        ASCII is assumed, on Prime machines - ZCODE is the ASCII code */
/*        plus 128 of either lower or upper case 'Z'. */

	if (inta >= 225 && inta <= 250) {
	    inta += -32;
	}
	if (intb >= 225 && intb <= 250) {
	    intb += -32;
	}
    }
    ret_val = inta == intb;

/*     RETURN */

/*     End of LSAME */

    return ret_val;
} /* lsame_ */

/* Subroutine */ int dgemm_(char *transa, char *transb, int *m, int *
	n, int *k, double *alpha, double *a, int *lda, 
	double *b, int *ldb, double *beta, double *c__, 
	int *ldc)
{
    /* System generated locals */
    int a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2, 
	    i__3;

    /* Local variables */
    int i__, j, l, info;
    logical nota, notb;
    double temp;
    int ncola;
    extern logical lsame_(char *, char *);
    int nrowa, nrowb;
    extern /* Subroutine */ int xerbla_(char *, int *);

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGEMM  performs one of the matrix-matrix operations */

/*     C := alpha*op( A )*op( B ) + beta*C, */

/*  where  op( X ) is one of */

/*     op( X ) = X   or   op( X ) = X', */

/*  alpha and beta are scalars, and A, B and C are matrices, with op( A ) */
/*  an m by k matrix,  op( B )  a  k by n matrix and  C an m by n matrix. */

/*  Arguments */
/*  ========== */

/*  TRANSA - CHARACTER*1. */
/*           On entry, TRANSA specifies the form of op( A ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSA = 'N' or 'n',  op( A ) = A. */

/*              TRANSA = 'T' or 't',  op( A ) = A'. */

/*              TRANSA = 'C' or 'c',  op( A ) = A'. */

/*           Unchanged on exit. */

/*  TRANSB - CHARACTER*1. */
/*           On entry, TRANSB specifies the form of op( B ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSB = 'N' or 'n',  op( B ) = B. */

/*              TRANSB = 'T' or 't',  op( B ) = B'. */

/*              TRANSB = 'C' or 'c',  op( B ) = B'. */

/*           Unchanged on exit. */

/*  M      - int. */
/*           On entry,  M  specifies  the number  of rows  of the  matrix */
/*           op( A )  and of the  matrix  C.  M  must  be at least  zero. */
/*           Unchanged on exit. */

/*  N      - int. */
/*           On entry,  N  specifies the number  of columns of the matrix */
/*           op( B ) and the number of columns of the matrix C. N must be */
/*           at least zero. */
/*           Unchanged on exit. */

/*  K      - int. */
/*           On entry,  K  specifies  the number of columns of the matrix */
/*           op( A ) and the number of rows of the matrix op( B ). K must */
/*           be at least  zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry, ALPHA specifies the scalar alpha. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, ka ), where ka is */
/*           k  when  TRANSA = 'N' or 'n',  and is  m  otherwise. */
/*           Before entry with  TRANSA = 'N' or 'n',  the leading  m by k */
/*           part of the array  A  must contain the matrix  A,  otherwise */
/*           the leading  k by m  part of the array  A  must contain  the */
/*           matrix A. */
/*           Unchanged on exit. */

/*  LDA    - int. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program. When  TRANSA = 'N' or 'n' then */
/*           LDA must be at least  max( 1, m ), otherwise  LDA must be at */
/*           least  max( 1, k ). */
/*           Unchanged on exit. */

/*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, kb ), where kb is */
/*           n  when  TRANSB = 'N' or 'n',  and is  k  otherwise. */
/*           Before entry with  TRANSB = 'N' or 'n',  the leading  k by n */
/*           part of the array  B  must contain the matrix  B,  otherwise */
/*           the leading  n by k  part of the array  B  must contain  the */
/*           matrix B. */
/*           Unchanged on exit. */

/*  LDB    - int. */
/*           On entry, LDB specifies the first dimension of B as declared */
/*           in the calling (sub) program. When  TRANSB = 'N' or 'n' then */
/*           LDB must be at least  max( 1, k ), otherwise  LDB must be at */
/*           least  max( 1, n ). */
/*           Unchanged on exit. */

/*  BETA   - DOUBLE PRECISION. */
/*           On entry,  BETA  specifies the scalar  beta.  When  BETA  is */
/*           supplied as zero then C need not be set on input. */
/*           Unchanged on exit. */

/*  C      - DOUBLE PRECISION array of DIMENSION ( LDC, n ). */
/*           Before entry, the leading  m by n  part of the array  C must */
/*           contain the matrix  C,  except when  beta  is zero, in which */
/*           case C need not be set on entry. */
/*           On exit, the array  C  is overwritten by the  m by n  matrix */
/*           ( alpha*op( A )*op( B ) + beta*C ). */

/*  LDC    - int. */
/*           On entry, LDC specifies the first dimension of C as declared */
/*           in  the  calling  (sub)  program.   LDC  must  be  at  least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 3 Blas routine. */

/*  -- Written on 8-February-1989. */
/*     Jack Dongarra, Argonne National Laboratory. */
/*     Iain Duff, AERE Harwell. */
/*     Jeremy Du Croz, Numerical Algorithms Group Ltd. */
/*     Sven Hammarling, Numerical Algorithms Group Ltd. */


/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Parameters .. */
/*     .. */

/*     Set  NOTA  and  NOTB  as  true if  A  and  B  respectively are not */
/*     transposed and set  NROWA, NCOLA and  NROWB  as the number of rows */
/*     and  columns of  A  and the  number of  rows  of  B  respectively. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;
    c_dim1 = *ldc;
    c_offset = 1 + c_dim1;
    c__ -= c_offset;

    /* Function Body */
    nota = lsame_(transa, "N");
    notb = lsame_(transb, "N");
    if (nota) {
	nrowa = *m;
	ncola = *k;
    } else {
	nrowa = *k;
	ncola = *m;
    }
    if (notb) {
	nrowb = *k;
    } else {
	nrowb = *n;
    }

/*     Test the input parameters. */

    info = 0;
    if (! nota && ! lsame_(transa, "C") && ! lsame_(
	    transa, "T")) {
	info = 1;
    } else if (! notb && ! lsame_(transb, "C") && ! 
	    lsame_(transb, "T")) {
	info = 2;
    } else if (*m < 0) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*k < 0) {
	info = 5;
    } else if (*lda < max(1,nrowa)) {
	info = 8;
    } else if (*ldb < max(1,nrowb)) {
	info = 10;
    } else if (*ldc < max(1,*m)) {
	info = 13;
    }
    if (info != 0) {
	xerbla_("DGEMM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || (*alpha == 0. || *k == 0) && *beta == 1.) {
	return 0;
    }

/*     And if  alpha.eq.zero. */

    if (*alpha == 0.) {
	if (*beta == 0.) {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    c__[i__ + j * c_dim1] = 0.;
/* L10: */
		}
/* L20: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L30: */
		}
/* L40: */
	    }
	}
	return 0;
    }

/*     Start the operations. */

    if (notb) {
	if (nota) {

/*           Form  C := alpha*A*B + beta*C. */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (*beta == 0.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = 0.;
/* L50: */
		    }
		} else if (*beta != 1.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L60: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= i__2; ++l) {
		    if (b[l + j * b_dim1] != 0.) {
			temp = *alpha * b[l + j * b_dim1];
			i__3 = *m;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    c__[i__ + j * c_dim1] += temp * a[i__ + l * 
				    a_dim1];
/* L70: */
			}
		    }
/* L80: */
		}
/* L90: */
	    }
	} else {

/*           Form  C := alpha*A'*B + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp = 0.;
		    i__3 = *k;
		    for (l = 1; l <= i__3; ++l) {
			temp += a[l + i__ * a_dim1] * b[l + j * b_dim1];
/* L100: */
		    }
		    if (*beta == 0.) {
			c__[i__ + j * c_dim1] = *alpha * temp;
		    } else {
			c__[i__ + j * c_dim1] = *alpha * temp + *beta * c__[
				i__ + j * c_dim1];
		    }
/* L110: */
		}
/* L120: */
	    }
	}
    } else {
	if (nota) {

/*           Form  C := alpha*A*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		if (*beta == 0.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = 0.;
/* L130: */
		    }
		} else if (*beta != 1.) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			c__[i__ + j * c_dim1] = *beta * c__[i__ + j * c_dim1];
/* L140: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= i__2; ++l) {
		    if (b[j + l * b_dim1] != 0.) {
			temp = *alpha * b[j + l * b_dim1];
			i__3 = *m;
			for (i__ = 1; i__ <= i__3; ++i__) {
			    c__[i__ + j * c_dim1] += temp * a[i__ + l * 
				    a_dim1];
/* L150: */
			}
		    }
/* L160: */
		}
/* L170: */
	    }
	} else {

/*           Form  C := alpha*A'*B' + beta*C */

	    i__1 = *n;
	    for (j = 1; j <= i__1; ++j) {
		i__2 = *m;
		for (i__ = 1; i__ <= i__2; ++i__) {
		    temp = 0.;
		    i__3 = *k;
		    for (l = 1; l <= i__3; ++l) {
			temp += a[l + i__ * a_dim1] * b[j + l * b_dim1];
/* L180: */
		    }
		    if (*beta == 0.) {
			c__[i__ + j * c_dim1] = *alpha * temp;
		    } else {
			c__[i__ + j * c_dim1] = *alpha * temp + *beta * c__[
				i__ + j * c_dim1];
		    }
/* L190: */
		}
/* L200: */
	    }
	}
    }

    return 0;

/*     End of DGEMM . */

} /* dgemm_ */

/* Subroutine */ int xerbla_(char *srname, int *info)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    XERBLA  is an error handler for the LAPACK routines.   
    It is called by an LAPACK routine if an input parameter has an   
    invalid value.  A message is printed and execution stops.   

    Installers may consider modifying the STOP statement in order to   
    call system-specific exception-handling facilities.   

    Arguments   
    =========   

    SRNAME  (input) CHARACTER*6   
            The name of the routine which called XERBLA.   

    INFO    (input) int   
            The position of the invalid parameter in the parameter list   

            of the calling routine.   

   ===================================================================== 
*/

    printf("** On entry to %6s, parameter number %2i had an illegal value\n",
		srname, *info);

/*     End of XERBLA */

    return 0;
} /* xerbla_ */


/* Subroutine */ int dgesv_(int *n, int *nrhs, double *a, int 
	*lda, int *ipiv, double *b, int *ldb, int *info)
{
/*  -- LAPACK driver routine (version 3.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
i     Courant Institute, Argonne National Lab, and Rice University   
       March 31, 1993   


    Purpose   
    =======   

    DGESV computes the solution to a float system of linear equations   
       A * X = B,   
    where A is an N-by-N matrix and X and B are N-by-NRHS matrices.   

    The LU decomposition with partial pivoting and row interchanges is   
    used to factor A as   
       A = P * L * U,   
    where P is a permutation matrix, L is unit lower triangular, and U is   
    upper triangular.  The factored form of A is then used to solve the   
    system of equations A * X = B.  d

    Arguments   
    =========   

    N       (input) int   
            The number of linear equations, i.e., the order of the   
            matrix A.  N >= 0.   

    NRHS    (input) int   
            The number of right hand sides, i.e., the number of columns   
            of the matrix B.  NRHS >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the N-by-N coefficient matrix A.   
            On exit, the factors L and U from the factorization   
            A = P*L*U; the unit diagonal elements of L are not stored.   

    LDA     (input) int   
            The leading dimension of the array A.  LDA >= max(1,N).   

    IPIV    (output) int array, dimension (N)   
            The pivot indices that define the permutation matrix P;   
            row i of the matrix was interchanged with row IPIV(i).   

    B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)   
            On entry, the N-by-NRHS matrix of right hand side matrix B.   
            On exit, if INFO = 0, the N-by-NRHS solution matrix X.   

    LDB     (input) int   
            The leading dimension of the array B.  LDB >= max(1,N).   

    INFO    (output) int   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   
            > 0:  if INFO = i, U(i,i) is exactly zero.  The factorization   
                  has been completed, but the factor U is exactly   
                  singular, so the solution could not be computed.   

    =====================================================================   


       Test the input parameters.   

       Parameter adjustments */
    /* System generated locals */
    int a_dim1, a_offset, b_dim1, b_offset, i__1;
    /* Local variables */
    extern /* Subroutine */ int dgetrf_(int *, int *, double *, 
	    int *, int *, int *), xerbla_(char *, int *), dgetrs_(char *, int *, int *, double *, 
	    int *, int *, double *, int *, int *);

    a_dim1 = *lda;
    a_offset = 1 + a_dim1 * 1;
    a -= a_offset;
    --ipiv;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1 * 1;
    b -= b_offset;

    /* Function Body */
    *info = 0;
    if (*n < 0) {
	*info = -1;
    } else if (*nrhs < 0) {
	*info = -2;
    } else if (*lda < max(1,*n)) {
	*info = -4;
    } else if (*ldb < max(1,*n)) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGESV ", &i__1);
	return 0;
    }

/*     Compute the LU factorization of A. */

    dgetrf_(n, n, &a[a_offset], lda, &ipiv[1], info);
    if (*info == 0) {

/*        Solve the system A*X = B, overwriting B with X. */

	dgetrs_("No transpose", n, nrhs, &a[a_offset], lda, &ipiv[1], &b[
		b_offset], ldb, info);
    }
    return 0;

/*     End of DGESV */
} /* dgesv_ */

/* Subroutine */ int dlaswp_(int *n, double *a, int *lda, int 
	*k1, int *k2, int *ipiv, int *incx)
{
    /* System generated locals */
    int a_dim1, a_offset, i__1, i__2, i__3, i__4;

    /* Local variables */
    int i__, j, k, i1, i2, n32, ip, ix, ix0, inc;
    double temp;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLASWP performs a series of row interchanges on the matrix A. */
/*  One row interchange is initiated for each of rows K1 through K2 of A. */

/*  Arguments */
/*  ========= */

/*  N       (input) int */
/*          The number of columns of the matrix A. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the matrix of column dimension N to which the row */
/*          interchanges will be applied. */
/*          On exit, the permuted matrix. */

/*  LDA     (input) int */
/*          The leading dimension of the array A. */

/*  K1      (input) int */
/*          The first element of IPIV for which a row interchange will */
/*          be done. */

/*  K2      (input) int */
/*          The last element of IPIV for which a row interchange will */
/*          be done. */

/*  IPIV    (input) int array, dimension (K2*abs(INCX)) */
/*          The vector of pivot indices.  Only the elements in positions */
/*          K1 through K2 of IPIV are accessed. */
/*          IPIV(K) = L implies rows K and L are to be interchanged. */

/*  INCX    (input) int */
/*          The increment between successive values of IPIV.  If IPIV */
/*          is negative, the pivots are applied in reverse order. */

/*  Further Details */
/*  =============== */

/*  Modified by */
/*   R. C. Whaley, Computer Science Dept., Univ. of Tenn., Knoxville, USA */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Interchange row I with row IPIV(I) for each of rows K1 through K2. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    if (*incx > 0) {
	ix0 = *k1;
	i1 = *k1;
	i2 = *k2;
	inc = 1;
    } else if (*incx < 0) {
	ix0 = (1 - *k2) * *incx + 1;
	i1 = *k2;
	i2 = *k1;
	inc = -1;
    } else {
	return 0;
    }

    n32 = *n / 32 << 5;
    if (n32 != 0) {
	i__1 = n32;
	for (j = 1; j <= i__1; j += 32) {
	    ix = ix0;
	    i__2 = i2;
	    i__3 = inc;
	    for (i__ = i1; i__3 < 0 ? i__ >= i__2 : i__ <= i__2; i__ += i__3) 
		    {
		ip = ipiv[ix];
		if (ip != i__) {
		    i__4 = j + 31;
		    for (k = j; k <= i__4; ++k) {
			temp = a[i__ + k * a_dim1];
			a[i__ + k * a_dim1] = a[ip + k * a_dim1];
			a[ip + k * a_dim1] = temp;
/* L10: */
		    }
		}
		ix += *incx;
/* L20: */
	    }
/* L30: */
	}
    }
    if (n32 != *n) {
	++n32;
	ix = ix0;
	i__1 = i2;
	i__3 = inc;
	for (i__ = i1; i__3 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__3) {
	    ip = ipiv[ix];
	    if (ip != i__) {
		i__2 = *n;
		for (k = n32; k <= i__2; ++k) {
		    temp = a[i__ + k * a_dim1];
		    a[i__ + k * a_dim1] = a[ip + k * a_dim1];
		    a[ip + k * a_dim1] = temp;
/* L40: */
		}
	    }
	    ix += *incx;
/* L50: */
	}
    }

    return 0;

/*     End of DLASWP */

} /* dlaswp_ */


double dlamch_(char *cmach)
{
    /* Initialized data */

    static logical first = TRUE_;

    /* System generated locals */
    int i__1;
    double ret_val;

    /* Builtin functions */
    double pow_di(double *, int *);

    /* Local variables */
    static double t;
    int it;
    static double rnd, eps, base;
    int beta;
    static double emin, prec, emax;
    int imin, imax;
    logical lrnd;
    static double rmin, rmax;
    double rmach;
    extern logical lsame_(char *, char *);
    double small;
    static double sfmin;
    extern /* Subroutine */ int dlamc2_(int *, int *, logical *, 
	    double *, int *, double *, int *, double *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMCH determines double precision machine parameters. */

/*  Arguments */
/*  ========= */

/*  CMACH   (input) CHARACTER*1 */
/*          Specifies the value to be returned by DLAMCH: */
/*          = 'E' or 'e',   DLAMCH := eps */
/*          = 'S' or 's ,   DLAMCH := sfmin */
/*          = 'B' or 'b',   DLAMCH := base */
/*          = 'P' or 'p',   DLAMCH := eps*base */
/*          = 'N' or 'n',   DLAMCH := t */
/*          = 'R' or 'r',   DLAMCH := rnd */
/*          = 'M' or 'm',   DLAMCH := emin */
/*          = 'U' or 'u',   DLAMCH := rmin */
/*          = 'L' or 'l',   DLAMCH := emax */
/*          = 'O' or 'o',   DLAMCH := rmax */

/*          where */

/*          eps   = relative machine precision */
/*          sfmin = safe minimum, such that 1/sfmin does not overflow */
/*          base  = base of the machine */
/*          prec  = eps*base */
/*          t     = number of (base) digits in the mantissa */
/*          rnd   = 1.0 when rounding occurs in addition, 0.0 otherwise */
/*          emin  = minimum exponent before (gradual) underflow */
/*          rmin  = underflow threshold - base**(emin-1) */
/*          emax  = largest exponent before overflow */
/*          rmax  = overflow threshold  - (base**emax)*(1-eps) */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Save statement .. */
/*     .. */
/*     .. Data statements .. */
/*     .. */
/*     .. Executable Statements .. */

    if (first) {
	dlamc2_(&beta, &it, &lrnd, &eps, &imin, &rmin, &imax, &rmax);
	base = (double) beta;
	t = (double) it;
	if (lrnd) {
	    rnd = 1.;
	    i__1 = 1 - it;
	    eps = pow_di(&base, &i__1) / 2;
	} else {
	    rnd = 0.;
	    i__1 = 1 - it;
	    eps = pow_di(&base, &i__1);
	}
	prec = eps * base;
	emin = (double) imin;
	emax = (double) imax;
	sfmin = rmin;
	small = 1. / rmax;
	if (small >= sfmin) {

/*           Use SMALL plus a bit, to avoid the possibility of rounding */
/*           causing overflow when computing  1/sfmin. */

	    sfmin = small * (eps + 1.);
	}
    }

    if (lsame_(cmach, "E")) {
	rmach = eps;
    } else if (lsame_(cmach, "S")) {
	rmach = sfmin;
    } else if (lsame_(cmach, "B")) {
	rmach = base;
    } else if (lsame_(cmach, "P")) {
	rmach = prec;
    } else if (lsame_(cmach, "N")) {
	rmach = t;
    } else if (lsame_(cmach, "R")) {
	rmach = rnd;
    } else if (lsame_(cmach, "M")) {
	rmach = emin;
    } else if (lsame_(cmach, "U")) {
	rmach = rmin;
    } else if (lsame_(cmach, "L")) {
	rmach = emax;
    } else if (lsame_(cmach, "O")) {
	rmach = rmax;
    }

    ret_val = rmach;
    first = FALSE_;
    return ret_val;

/*     End of DLAMCH */

} /* dlamch_ */


/* *********************************************************************** */

/* Subroutine */ int dlamc1_(int *beta, int *t, logical *rnd, logical 
	*ieee1)
{
    /* Initialized data */

    static logical first = TRUE_;

    /* System generated locals */
    double d__1, d__2;

    /* Local variables */
    double a, b, c__, f, t1, t2;
    static int lt;
    double one, qtr;
    static logical lrnd;
    static int lbeta;
    double savec;
    extern double dlamc3_(double *, double *);
    static logical lieee1;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMC1 determines the machine parameters given by BETA, T, RND, and */
/*  IEEE1. */

/*  Arguments */
/*  ========= */

/*  BETA    (output) int */
/*          The base of the machine. */

/*  T       (output) int */
/*          The number of ( BETA ) digits in the mantissa. */

/*  RND     (output) LOGICAL */
/*          Specifies whether proper rounding  ( RND = .TRUE. )  or */
/*          chopping  ( RND = .FALSE. )  occurs in addition. This may not */
/*          be a reliable guide to the way in which the machine performs */
/*          its arithmetic. */

/*  IEEE1   (output) LOGICAL */
/*          Specifies whether rounding appears to be done in the IEEE */
/*          'round to nearest' style. */

/*  Further Details */
/*  =============== */

/*  The routine is based on the routine  ENVRON  by Malcolm and */
/*  incorporates suggestions by Gentleman and Marovich. See */

/*     Malcolm M. A. (1972) Algorithms to reveal properties of */
/*        floating-point arithmetic. Comms. of the ACM, 15, 949-951. */

/*     Gentleman W. M. and Marovich S. B. (1974) More on algorithms */
/*        that reveal properties of floating point arithmetic units. */
/*        Comms. of the ACM, 17, 276-277. */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Save statement .. */
/*     .. */
/*     .. Data statements .. */
/*     .. */
/*     .. Executable Statements .. */

    if (first) {
	one = 1.;

/*        LBETA,  LIEEE1,  LT and  LRND  are the  local values  of  BETA, */
/*        IEEE1, T and RND. */

/*        Throughout this routine  we use the function  DLAMC3  to ensure */
/*        that relevant values are  stored and not held in registers,  or */
/*        are not affected by optimizers. */

/*        Compute  a = 2.0**m  with the  smallest positive int m such */
/*        that */

/*           fl( a + 1.0 ) = a. */

	a = 1.;
	c__ = 1.;

/* +       WHILE( C.EQ.ONE )LOOP */
L10:
	if (c__ == one) {
	    a *= 2;
	    c__ = dlamc3_(&a, &one);
	    d__1 = -a;
	    c__ = dlamc3_(&c__, &d__1);
	    goto L10;
	}
/* +       END WHILE */

/*        Now compute  b = 2.0**m  with the smallest positive int m */
/*        such that */

/*           fl( a + b ) .gt. a. */

	b = 1.;
	c__ = dlamc3_(&a, &b);

/* +       WHILE( C.EQ.A )LOOP */
L20:
	if (c__ == a) {
	    b *= 2;
	    c__ = dlamc3_(&a, &b);
	    goto L20;
	}
/* +       END WHILE */

/*        Now compute the base.  a and c  are neighbouring floating point */
/*        numbers  in the  interval  ( beta**t, beta**( t + 1 ) )  and so */
/*        their difference is beta. Adding 0.25 to c is to ensure that it */
/*        is truncated to beta and not ( beta - 1 ). */

	qtr = one / 4;
	savec = c__;
	d__1 = -a;
	c__ = dlamc3_(&c__, &d__1);
	lbeta = (int) (c__ + qtr);

/*        Now determine whether rounding or chopping occurs,  by adding a */
/*        bit  less  than  beta/2  and a  bit  more  than  beta/2  to  a. */

	b = (double) lbeta;
	d__1 = b / 2;
	d__2 = -b / 100;
	f = dlamc3_(&d__1, &d__2);
	c__ = dlamc3_(&f, &a);
	if (c__ == a) {
	    lrnd = TRUE_;
	} else {
	    lrnd = FALSE_;
	}
	d__1 = b / 2;
	d__2 = b / 100;
	f = dlamc3_(&d__1, &d__2);
	c__ = dlamc3_(&f, &a);
	if (lrnd && c__ == a) {
	    lrnd = FALSE_;
	}

/*        Try and decide whether rounding is done in the  IEEE  'round to */
/*        nearest' style. B/2 is half a unit in the last place of the two */
/*        numbers A and SAVEC. Furthermore, A is even, i.e. has last  bit */
/*        zero, and SAVEC is odd. Thus adding B/2 to A should not  change */
/*        A, but adding B/2 to SAVEC should change SAVEC. */

	d__1 = b / 2;
	t1 = dlamc3_(&d__1, &a);
	d__1 = b / 2;
	t2 = dlamc3_(&d__1, &savec);
	lieee1 = t1 == a && t2 > savec && lrnd;

/*        Now find  the  mantissa, t.  It should  be the  int part of */
/*        log to the base beta of a,  however it is safer to determine  t */
/*        by powering.  So we find t as the smallest positive int for */
/*        which */

/*           fl( beta**t + 1.0 ) = 1.0. */

	lt = 0;
	a = 1.;
	c__ = 1.;

/* +       WHILE( C.EQ.ONE )LOOP */
L30:
	if (c__ == one) {
	    ++lt;
	    a *= lbeta;
	    c__ = dlamc3_(&a, &one);
	    d__1 = -a;
	    c__ = dlamc3_(&c__, &d__1);
	    goto L30;
	}
/* +       END WHILE */

    }

    *beta = lbeta;
    *t = lt;
    *rnd = lrnd;
    *ieee1 = lieee1;
    first = FALSE_;
    return 0;

/*     End of DLAMC1 */

} /* dlamc1_ */


/* *********************************************************************** */

/* Subroutine */ int dlamc2_(int *beta, int *t, logical *rnd, 
	double *eps, int *emin, double *rmin, int *emax, 
	double *rmax)
{
    /* Initialized data */

    static logical first = TRUE_;
    static logical iwarn = FALSE_;

    /* Format strings */
    static char fmt_9999[] = "(//\002 WARNING. The value EMIN may be incorre"
	    "ct:-\002,\002  EMIN = \002,i8,/\002 If, after inspection, the va"
	    "lue EMIN looks\002,\002 acceptable please comment out \002,/\002"
	    " the IF block as marked within the code of routine\002,\002 DLAM"
	    "C2,\002,/\002 otherwise supply EMIN explicitly.\002,/)";

    /* System generated locals */
    int i__1;
    double d__1, d__2, d__3, d__4, d__5;

    /* Builtin functions */
    double pow_di(double *, int *);
    //int s_wsfe(cilist *), do_fio(int *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    double a, b, c__;
    int i__;
    static int lt;
    double one, two;
    logical ieee;
    double half;
    logical lrnd;
    static double leps;
    double zero;
    static int lbeta;
    double rbase;
    static int lemin, lemax;
    int gnmin;
    double small;
    int gpmin;
    double third;
    static double lrmin, lrmax;
    double sixth;
    extern /* Subroutine */ int dlamc1_(int *, int *, logical *, 
	    logical *);
    extern double dlamc3_(double *, double *);
    logical lieee1;
    extern /* Subroutine */ int dlamc4_(int *, double *, int *), 
	    dlamc5_(int *, int *, int *, logical *, int *, 
	    double *);
    int ngnmin, ngpmin;

    /* Fortran I/O blocks */
    static cilist io___58 = { 0, 6, 0, fmt_9999, 0 };



/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMC2 determines the machine parameters specified in its argument */
/*  list. */

/*  Arguments */
/*  ========= */

/*  BETA    (output) int */
/*          The base of the machine. */

/*  T       (output) int */
/*          The number of ( BETA ) digits in the mantissa. */

/*  RND     (output) LOGICAL */
/*          Specifies whether proper rounding  ( RND = .TRUE. )  or */
/*          chopping  ( RND = .FALSE. )  occurs in addition. This may not */
/*          be a reliable guide to the way in which the machine performs */
/*          its arithmetic. */

/*  EPS     (output) DOUBLE PRECISION */
/*          The smallest positive number such that */

/*             fl( 1.0 - EPS ) .LT. 1.0, */

/*          where fl denotes the computed value. */

/*  EMIN    (output) int */
/*          The minimum exponent before (gradual) underflow occurs. */

/*  RMIN    (output) DOUBLE PRECISION */
/*          The smallest normalized number for the machine, given by */
/*          BASE**( EMIN - 1 ), where  BASE  is the floating point value */
/*          of BETA. */

/*  EMAX    (output) int */
/*          The maximum exponent before overflow occurs. */

/*  RMAX    (output) DOUBLE PRECISION */
/*          The largest positive number for the machine, given by */
/*          BASE**EMAX * ( 1 - EPS ), where  BASE  is the floating point */
/*          value of BETA. */

/*  Further Details */
/*  =============== */

/*  The computation of  EPS  is based on a routine PARANOIA by */
/*  W. Kahan of the University of California at Berkeley. */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Save statement .. */
/*     .. */
/*     .. Data statements .. */
/*     .. */
/*     .. Executable Statements .. */

    if (first) {
	zero = 0.;
	one = 1.;
	two = 2.;

/*        LBETA, LT, LRND, LEPS, LEMIN and LRMIN  are the local values of */
/*        BETA, T, RND, EPS, EMIN and RMIN. */

/*        Throughout this routine  we use the function  DLAMC3  to ensure */
/*        that relevant values are stored  and not held in registers,  or */
/*        are not affected by optimizers. */

/*        DLAMC1 returns the parameters  LBETA, LT, LRND and LIEEE1. */

	dlamc1_(&lbeta, &lt, &lrnd, &lieee1);

/*        Start to find EPS. */

	b = (double) lbeta;
	i__1 = -lt;
	a = pow_di(&b, &i__1);
	leps = a;

/*        Try some tricks to see whether or not this is the correct  EPS. */

	b = two / 3;
	half = one / 2;
	d__1 = -half;
	sixth = dlamc3_(&b, &d__1);
	third = dlamc3_(&sixth, &sixth);
	d__1 = -half;
	b = dlamc3_(&third, &d__1);
	b = dlamc3_(&b, &sixth);
	b = abs(b);
	if (b < leps) {
	    b = leps;
	}

	leps = 1.;

/* +       WHILE( ( LEPS.GT.B ).AND.( B.GT.ZERO ) )LOOP */
L10:
	if (leps > b && b > zero) {
	    leps = b;
	    d__1 = half * leps;
/* Computing 5th power */
	    d__3 = two, d__4 = d__3, d__3 *= d__3;
/* Computing 2nd power */
	    d__5 = leps;
	    d__2 = d__4 * (d__3 * d__3) * (d__5 * d__5);
	    c__ = dlamc3_(&d__1, &d__2);
	    d__1 = -c__;
	    c__ = dlamc3_(&half, &d__1);
	    b = dlamc3_(&half, &c__);
	    d__1 = -b;
	    c__ = dlamc3_(&half, &d__1);
	    b = dlamc3_(&half, &c__);
	    goto L10;
	}
/* +       END WHILE */

	if (a < leps) {
	    leps = a;
	}

/*        Computation of EPS complete. */

/*        Now find  EMIN.  Let A = + or - 1, and + or - (1 + BASE**(-3)). */
/*        Keep dividing  A by BETA until (gradual) underflow occurs. This */
/*        is detected when we cannot recover the previous A. */

	rbase = one / lbeta;
	small = one;
	for (i__ = 1; i__ <= 3; ++i__) {
	    d__1 = small * rbase;
	    small = dlamc3_(&d__1, &zero);
/* L20: */
	}
	a = dlamc3_(&one, &small);
	dlamc4_(&ngpmin, &one, &lbeta);
	d__1 = -one;
	dlamc4_(&ngnmin, &d__1, &lbeta);
	dlamc4_(&gpmin, &a, &lbeta);
	d__1 = -a;
	dlamc4_(&gnmin, &d__1, &lbeta);
	ieee = FALSE_;

	if (ngpmin == ngnmin && gpmin == gnmin) {
	    if (ngpmin == gpmin) {
		lemin = ngpmin;
/*            ( Non twos-complement machines, no gradual underflow; */
/*              e.g.,  VAX ) */
	    } else if (gpmin - ngpmin == 3) {
		lemin = ngpmin - 1 + lt;
		ieee = TRUE_;
/*            ( Non twos-complement machines, with gradual underflow; */
/*              e.g., IEEE standard followers ) */
	    } else {
		lemin = min(ngpmin,gpmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else if (ngpmin == gpmin && ngnmin == gnmin) {
	    if ((i__1 = ngpmin - ngnmin, abs(i__1)) == 1) {
		lemin = max(ngpmin,ngnmin);
/*            ( Twos-complement machines, no gradual underflow; */
/*              e.g., CYBER 205 ) */
	    } else {
		lemin = min(ngpmin,ngnmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else if ((i__1 = ngpmin - ngnmin, abs(i__1)) == 1 && gpmin == gnmin)
		 {
	    if (gpmin - min(ngpmin,ngnmin) == 3) {
		lemin = max(ngpmin,ngnmin) - 1 + lt;
/*            ( Twos-complement machines with gradual underflow; */
/*              no known machine ) */
	    } else {
		lemin = min(ngpmin,ngnmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else {
/* Computing MIN */
	    i__1 = min(ngpmin,ngnmin), i__1 = min(i__1,gpmin);
	    lemin = min(i__1,gnmin);
/*         ( A guess; no known machine ) */
	    iwarn = TRUE_;
	}
	first = FALSE_;
/* ** */
/* Comment out this if block if EMIN is ok
	if (iwarn) {
	    first = TRUE_;
	    s_wsfe(&io___58);
	    do_fio(&c__1, (char *)&lemin, (ftnlen)sizeof(int));
	    e_wsfe();
	}
 ** */

/*        Assume IEEE arithmetic if we found denormalised  numbers above, */
/*        or if arithmetic seems to round in the  IEEE style,  determined */
/*        in routine DLAMC1. A true IEEE machine should have both  things */
/*        true; however, faulty machines may have one or the other. */

	ieee = ieee || lieee1;

/*        Compute  RMIN by successive division by  BETA. We could compute */
/*        RMIN as BASE**( EMIN - 1 ),  but some machines underflow during */
/*        this computation. */

	lrmin = 1.;
	i__1 = 1 - lemin;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d__1 = lrmin * rbase;
	    lrmin = dlamc3_(&d__1, &zero);
/* L30: */
	}

/*        Finally, call DLAMC5 to compute EMAX and RMAX. */

	dlamc5_(&lbeta, &lt, &lemin, &ieee, &lemax, &lrmax);
    }

    *beta = lbeta;
    *t = lt;
    *rnd = lrnd;
    *eps = leps;
    *emin = lemin;
    *rmin = lrmin;
    *emax = lemax;
    *rmax = lrmax;

    return 0;


/*     End of DLAMC2 */

} /* dlamc2_ */


/* *********************************************************************** */

double dlamc3_(double *a, double *b)
{
    /* System generated locals */
    double ret_val;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMC3  is intended to force  A  and  B  to be stored prior to doing */
/*  the addition of  A  and  B ,  for use in situations where optimizers */
/*  might hold one of these in a register. */

/*  Arguments */
/*  ========= */

/*  A       (input) DOUBLE PRECISION */
/*  B       (input) DOUBLE PRECISION */
/*          The values A and B. */

/* ===================================================================== */

/*     .. Executable Statements .. */

    ret_val = *a + *b;

    return ret_val;

/*     End of DLAMC3 */

} /* dlamc3_ */


/* *********************************************************************** */

/* Subroutine */ int dlamc4_(int *emin, double *start, int *base)
{
    /* System generated locals */
    int i__1;
    double d__1;

    /* Local variables */
    double a;
    int i__;
    double b1, b2, c1, c2, d1, d2, one, zero, rbase;
    extern double dlamc3_(double *, double *);


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMC4 is a service routine for DLAMC2. */

/*  Arguments */
/*  ========= */

/*  EMIN    (output) int */
/*          The minimum exponent before (gradual) underflow, computed by */
/*          setting A = START and dividing by BASE until the previous A */
/*          can not be recovered. */

/*  START   (input) DOUBLE PRECISION */
/*          The starting point for determining EMIN. */

/*  BASE    (input) int */
/*          The base of the machine. */

/* ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    a = *start;
    one = 1.;
    rbase = one / *base;
    zero = 0.;
    *emin = 1;
    d__1 = a * rbase;
    b1 = dlamc3_(&d__1, &zero);
    c1 = a;
    c2 = a;
    d1 = a;
    d2 = a;
/* +    WHILE( ( C1.EQ.A ).AND.( C2.EQ.A ).AND. */
/*    $       ( D1.EQ.A ).AND.( D2.EQ.A )      )LOOP */
L10:
    if (c1 == a && c2 == a && d1 == a && d2 == a) {
	--(*emin);
	a = b1;
	d__1 = a / *base;
	b1 = dlamc3_(&d__1, &zero);
	d__1 = b1 * *base;
	c1 = dlamc3_(&d__1, &zero);
	d1 = zero;
	i__1 = *base;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d1 += b1;
/* L20: */
	}
	d__1 = a * rbase;
	b2 = dlamc3_(&d__1, &zero);
	d__1 = b2 / rbase;
	c2 = dlamc3_(&d__1, &zero);
	d2 = zero;
	i__1 = *base;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    d2 += b2;
/* L30: */
	}
	goto L10;
    }
/* +    END WHILE */

    return 0;

/*     End of DLAMC4 */

} /* dlamc4_ */


/* *********************************************************************** */

/* Subroutine */ int dlamc5_(int *beta, int *p, int *emin, 
	logical *ieee, int *emax, double *rmax)
{
    /* System generated locals */
    int i__1;
    double d__1;

    /* Local variables */
    int i__;
    double y, z__;
    int try__, lexp;
    double oldy;
    int uexp, nbits;
    extern double dlamc3_(double *, double *);
    double recbas;
    int exbits, expsum;


/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     November 2006 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DLAMC5 attempts to compute RMAX, the largest machine floating-point */
/*  number, without overflow.  It assumes that EMAX + abs(EMIN) sum */
/*  approximately to a power of 2.  It will fail on machines where this */
/*  assumption does not hold, for example, the Cyber 205 (EMIN = -28625, */
/*  EMAX = 28718).  It will also fail if the value supplied for EMIN is */
/*  too large (i.e. too close to zero), probably with overflow. */

/*  Arguments */
/*  ========= */

/*  BETA    (input) int */
/*          The base of floating-point arithmetic. */

/*  P       (input) int */
/*          The number of base BETA digits in the mantissa of a */
/*          floating-point value. */

/*  EMIN    (input) int */
/*          The minimum exponent before (gradual) underflow. */

/*  IEEE    (input) LOGICAL */
/*          A logical flag specifying whether or not the arithmetic */
/*          system is thought to comply with the IEEE standard. */

/*  EMAX    (output) int */
/*          The largest exponent before overflow */

/*  RMAX    (output) DOUBLE PRECISION */
/*          The largest machine floating-point number. */

/* ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     First compute LEXP and UEXP, two powers of 2 that bound */
/*     abs(EMIN). We then assume that EMAX + abs(EMIN) will sum */
/*     approximately to the bound that is closest to abs(EMIN). */
/*     (EMAX is the exponent of the required number RMAX). */

    lexp = 1;
    exbits = 1;
L10:
    try__ = lexp << 1;
    if (try__ <= -(*emin)) {
	lexp = try__;
	++exbits;
	goto L10;
    }
    if (lexp == -(*emin)) {
	uexp = lexp;
    } else {
	uexp = try__;
	++exbits;
    }

/*     Now -LEXP is less than or equal to EMIN, and -UEXP is greater */
/*     than or equal to EMIN. EXBITS is the number of bits needed to */
/*     store the exponent. */

    if (uexp + *emin > -lexp - *emin) {
	expsum = lexp << 1;
    } else {
	expsum = uexp << 1;
    }

/*     EXPSUM is the exponent range, approximately equal to */
/*     EMAX - EMIN + 1 . */

    *emax = expsum + *emin - 1;
    nbits = exbits + 1 + *p;

/*     NBITS is the total number of bits needed to store a */
/*     floating-point number. */

    if (nbits % 2 == 1 && *beta == 2) {

/*        Either there are an odd number of bits used to store a */
/*        floating-point number, which is unlikely, or some bits are */
/*        not used in the representation of numbers, which is possible, */
/*        (e.g. Cray machines) or the mantissa has an implicit bit, */
/*        (e.g. IEEE machines, Dec Vax machines), which is perhaps the */
/*        most likely. We have to assume the last alternative. */
/*        If this is true, then we need to reduce EMAX by one because */
/*        there must be some way of representing zero in an implicit-bit */
/*        system. On machines like Cray, we are reducing EMAX by one */
/*        unnecessarily. */

	--(*emax);
    }

    if (*ieee) {

/*        Assume we are on an IEEE machine which reserves one exponent */
/*        for infinity and NaN. */

	--(*emax);
    }

/*     Now create RMAX, the largest machine number, which should */
/*     be equal to (1.0 - BETA**(-P)) * BETA**EMAX . */

/*     First compute 1.0 - BETA**(-P), being careful that the */
/*     result is less than 1.0 . */

    recbas = 1. / *beta;
    z__ = *beta - 1.;
    y = 0.;
    i__1 = *p;
    for (i__ = 1; i__ <= i__1; ++i__) {
	z__ *= recbas;
	if (y < 1.) {
	    oldy = y;
	}
	y = dlamc3_(&y, &z__);
/* L20: */
    }
    if (y >= 1.) {
	y = oldy;
    }

/*     Now multiply by BETA**EMAX to get RMAX. */

    i__1 = *emax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__1 = y * *beta;
	y = dlamc3_(&d__1, &c_b32);
/* L30: */
    }

    *rmax = y;
    return 0;

/*     End of DLAMC5 */

} /* dlamc5_ */


/* Subroutine */ int dtrsm_(char *side, char *uplo, char *transa, char *diag, 
	int *m, int *n, double *alpha, double *a, int *
	lda, double *b, int *ldb)
{
    /* System generated locals */
    int a_dim1, a_offset, b_dim1, b_offset, i__1, i__2, i__3;

    /* Local variables */
    int i__, j, k, info;
    double temp;
    logical lside;
    extern logical lsame_(char *, char *);
    int nrowa;
    logical upper;
    extern /* Subroutine */ int xerbla_(char *, int *);
    logical nounit;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DTRSM  solves one of the matrix equations */

/*     op( A )*X = alpha*B,   or   X*op( A ) = alpha*B, */

/*  where alpha is a scalar, X and B are m by n matrices, A is a unit, or */
/*  non-unit,  upper or lower triangular matrix  and  op( A )  is one  of */

/*     op( A ) = A   or   op( A ) = A'. */

/*  The matrix X is overwritten on B. */

/*  Arguments */
/*  ========== */

/*  SIDE   - CHARACTER*1. */
/*           On entry, SIDE specifies whether op( A ) appears on the left */
/*           or right of X as follows: */

/*              SIDE = 'L' or 'l'   op( A )*X = alpha*B. */

/*              SIDE = 'R' or 'r'   X*op( A ) = alpha*B. */

/*           Unchanged on exit. */

/*  UPLO   - CHARACTER*1. */
/*           On entry, UPLO specifies whether the matrix A is an upper or */
/*           lower triangular matrix as follows: */

/*              UPLO = 'U' or 'u'   A is an upper triangular matrix. */

/*              UPLO = 'L' or 'l'   A is a lower triangular matrix. */

/*           Unchanged on exit. */

/*  TRANSA - CHARACTER*1. */
/*           On entry, TRANSA specifies the form of op( A ) to be used in */
/*           the matrix multiplication as follows: */

/*              TRANSA = 'N' or 'n'   op( A ) = A. */

/*              TRANSA = 'T' or 't'   op( A ) = A'. */

/*              TRANSA = 'C' or 'c'   op( A ) = A'. */

/*           Unchanged on exit. */

/*  DIAG   - CHARACTER*1. */
/*           On entry, DIAG specifies whether or not A is unit triangular */
/*           as follows: */

/*              DIAG = 'U' or 'u'   A is assumed to be unit triangular. */

/*              DIAG = 'N' or 'n'   A is not assumed to be unit */
/*                                  triangular. */

/*           Unchanged on exit. */

/*  M      - int. */
/*           On entry, M specifies the number of rows of B. M must be at */
/*           least zero. */
/*           Unchanged on exit. */

/*  N      - int. */
/*           On entry, N specifies the number of columns of B.  N must be */
/*           at least zero. */
/*           Unchanged on exit. */

/*  ALPHA  - DOUBLE PRECISION. */
/*           On entry,  ALPHA specifies the scalar  alpha. When  alpha is */
/*           zero then  A is not referenced and  B need not be set before */
/*           entry. */
/*           Unchanged on exit. */

/*  A      - DOUBLE PRECISION array of DIMENSION ( LDA, k ), where k is m */
/*           when  SIDE = 'L' or 'l'  and is  n  when  SIDE = 'R' or 'r'. */
/*           Before entry  with  UPLO = 'U' or 'u',  the  leading  k by k */
/*           upper triangular part of the array  A must contain the upper */
/*           triangular matrix  and the strictly lower triangular part of */
/*           A is not referenced. */
/*           Before entry  with  UPLO = 'L' or 'l',  the  leading  k by k */
/*           lower triangular part of the array  A must contain the lower */
/*           triangular matrix  and the strictly upper triangular part of */
/*           A is not referenced. */
/*           Note that when  DIAG = 'U' or 'u',  the diagonal elements of */
/*           A  are not referenced either,  but are assumed to be  unity. */
/*           Unchanged on exit. */

/*  LDA    - int. */
/*           On entry, LDA specifies the first dimension of A as declared */
/*           in the calling (sub) program.  When  SIDE = 'L' or 'l'  then */
/*           LDA  must be at least  max( 1, m ),  when  SIDE = 'R' or 'r' */
/*           then LDA must be at least max( 1, n ). */
/*           Unchanged on exit. */

/*  B      - DOUBLE PRECISION array of DIMENSION ( LDB, n ). */
/*           Before entry,  the leading  m by n part of the array  B must */
/*           contain  the  right-hand  side  matrix  B,  and  on exit  is */
/*           overwritten by the solution matrix  X. */

/*  LDB    - int. */
/*           On entry, LDB specifies the first dimension of B as declared */
/*           in  the  calling  (sub)  program.   LDB  must  be  at  least */
/*           max( 1, m ). */
/*           Unchanged on exit. */


/*  Level 3 Blas routine. */


/*  -- Written on 8-February-1989. */
/*     Jack Dongarra, Argonne National Laboratory. */
/*     Iain Duff, AERE Harwell. */
/*     Jeremy Du Croz, Numerical Algorithms Group Ltd. */
/*     Sven Hammarling, Numerical Algorithms Group Ltd. */


/*     .. External Functions .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. Parameters .. */
/*     .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    b_dim1 = *ldb;
    b_offset = 1 + b_dim1;
    b -= b_offset;

    /* Function Body */
    lside = lsame_(side, "L");
    if (lside) {
	nrowa = *m;
    } else {
	nrowa = *n;
    }
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");

    info = 0;
    if (! lside && ! lsame_(side, "R")) {
	info = 1;
    } else if (! upper && ! lsame_(uplo, "L")) {
	info = 2;
    } else if (! lsame_(transa, "N") && ! lsame_(transa, 
	     "T") && ! lsame_(transa, "C")) {
	info = 3;
    } else if (! lsame_(diag, "U") && ! lsame_(diag, 
	    "N")) {
	info = 4;
    } else if (*m < 0) {
	info = 5;
    } else if (*n < 0) {
	info = 6;
    } else if (*lda < max(1,nrowa)) {
	info = 9;
    } else if (*ldb < max(1,*m)) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("DTRSM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (*alpha == 0.) {
	i__1 = *n;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		b[i__ + j * b_dim1] = 0.;
/* L10: */
	    }
/* L20: */
	}
	return 0;
    }

/*     Start the operations. */

    if (lside) {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*inv( A )*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L30: */
			}
		    }
		    for (k = *m; k >= 1; --k) {
			if (b[k + j * b_dim1] != 0.) {
			    if (nounit) {
				b[k + j * b_dim1] /= a[k + k * a_dim1];
			    }
			    i__2 = k - 1;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= b[k + j * b_dim1] * a[
					i__ + k * a_dim1];
/* L40: */
			    }
			}
/* L50: */
		    }
/* L60: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L70: */
			}
		    }
		    i__2 = *m;
		    for (k = 1; k <= i__2; ++k) {
			if (b[k + j * b_dim1] != 0.) {
			    if (nounit) {
				b[k + j * b_dim1] /= a[k + k * a_dim1];
			    }
			    i__3 = *m;
			    for (i__ = k + 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= b[k + j * b_dim1] * a[
					i__ + k * a_dim1];
/* L80: */
			    }
			}
/* L90: */
		    }
/* L100: */
		}
	    }
	} else {

/*           Form  B := alpha*inv( A' )*B. */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    i__2 = *m;
		    for (i__ = 1; i__ <= i__2; ++i__) {
			temp = *alpha * b[i__ + j * b_dim1];
			i__3 = i__ - 1;
			for (k = 1; k <= i__3; ++k) {
			    temp -= a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L110: */
			}
			if (nounit) {
			    temp /= a[i__ + i__ * a_dim1];
			}
			b[i__ + j * b_dim1] = temp;
/* L120: */
		    }
/* L130: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    for (i__ = *m; i__ >= 1; --i__) {
			temp = *alpha * b[i__ + j * b_dim1];
			i__2 = *m;
			for (k = i__ + 1; k <= i__2; ++k) {
			    temp -= a[k + i__ * a_dim1] * b[k + j * b_dim1];
/* L140: */
			}
			if (nounit) {
			    temp /= a[i__ + i__ * a_dim1];
			}
			b[i__ + j * b_dim1] = temp;
/* L150: */
		    }
/* L160: */
		}
	    }
	}
    } else {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*B*inv( A ). */

	    if (upper) {
		i__1 = *n;
		for (j = 1; j <= i__1; ++j) {
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L170: */
			}
		    }
		    i__2 = j - 1;
		    for (k = 1; k <= i__2; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= a[k + j * a_dim1] * b[
					i__ + k * b_dim1];
/* L180: */
			    }
			}
/* L190: */
		    }
		    if (nounit) {
			temp = 1. / a[j + j * a_dim1];
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L200: */
			}
		    }
/* L210: */
		}
	    } else {
		for (j = *n; j >= 1; --j) {
		    if (*alpha != 1.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + j * b_dim1] = *alpha * b[i__ + j * b_dim1]
				    ;
/* L220: */
			}
		    }
		    i__1 = *n;
		    for (k = j + 1; k <= i__1; ++k) {
			if (a[k + j * a_dim1] != 0.) {
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= a[k + j * a_dim1] * b[
					i__ + k * b_dim1];
/* L230: */
			    }
			}
/* L240: */
		    }
		    if (nounit) {
			temp = 1. / a[j + j * a_dim1];
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + j * b_dim1] = temp * b[i__ + j * b_dim1];
/* L250: */
			}
		    }
/* L260: */
		}
	    }
	} else {

/*           Form  B := alpha*B*inv( A' ). */

	    if (upper) {
		for (k = *n; k >= 1; --k) {
		    if (nounit) {
			temp = 1. / a[k + k * a_dim1];
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L270: */
			}
		    }
		    i__1 = k - 1;
		    for (j = 1; j <= i__1; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = a[j + k * a_dim1];
			    i__2 = *m;
			    for (i__ = 1; i__ <= i__2; ++i__) {
				b[i__ + j * b_dim1] -= temp * b[i__ + k * 
					b_dim1];
/* L280: */
			    }
			}
/* L290: */
		    }
		    if (*alpha != 1.) {
			i__1 = *m;
			for (i__ = 1; i__ <= i__1; ++i__) {
			    b[i__ + k * b_dim1] = *alpha * b[i__ + k * b_dim1]
				    ;
/* L300: */
			}
		    }
/* L310: */
		}
	    } else {
		i__1 = *n;
		for (k = 1; k <= i__1; ++k) {
		    if (nounit) {
			temp = 1. / a[k + k * a_dim1];
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + k * b_dim1] = temp * b[i__ + k * b_dim1];
/* L320: */
			}
		    }
		    i__2 = *n;
		    for (j = k + 1; j <= i__2; ++j) {
			if (a[j + k * a_dim1] != 0.) {
			    temp = a[j + k * a_dim1];
			    i__3 = *m;
			    for (i__ = 1; i__ <= i__3; ++i__) {
				b[i__ + j * b_dim1] -= temp * b[i__ + k * 
					b_dim1];
/* L330: */
			    }
			}
/* L340: */
		    }
		    if (*alpha != 1.) {
			i__2 = *m;
			for (i__ = 1; i__ <= i__2; ++i__) {
			    b[i__ + k * b_dim1] = *alpha * b[i__ + k * b_dim1]
				    ;
/* L350: */
			}
		    }
/* L360: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRSM . */

} /* dtrsm_ */

int ilaenv_(int *ispec, char *name__, char *opts, int *n1, 
	int *n2, int *n3, int *n4)
{
    /* System generated locals */
    int ret_val;
    int i__;
    char c1[1], c2[1], c3[1], c4[1];
    int ic, nb, iz, nx;
    logical cname;
    int nbmin;
    logical sname;
    extern int ieeeck_(int *, float *, float *);
    char subnam[1];
    extern int iparmq_(int *, char *, char *, int *, int *, 
	    int *, int *);

    ftnlen name_len, opts_len;

    name_len = strlen (name__);
    opts_len = strlen (opts);

/*  -- LAPACK auxiliary routine (version 3.2) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     January 2007 */

/*     .. Scalar Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  ILAENV is called from the LAPACK routines to choose problem-dependent */
/*  parameters for the local environment.  See ISPEC for a description of */
/*  the parameters. */

/*  ILAENV returns an int */
/*  if ILAENV >= 0: ILAENV returns the value of the parameter specified by ISPEC */
/*  if ILAENV < 0:  if ILAENV = -k, the k-th argument had an illegal value. */

/*  This version provides a set of parameters which should give good, */
/*  but not optimal, performance on many of the currently available */
/*  computers.  Users are encouraged to modify this subroutine to set */
/*  the tuning parameters for their particular machine using the option */
/*  and problem size information in the arguments. */

/*  This routine will not function correctly if it is converted to all */
/*  lower case.  Converting it to all upper case is allowed. */

/*  Arguments */
/*  ========= */

/*  ISPEC   (input) int */
/*          Specifies the parameter to be returned as the value of */
/*          ILAENV. */
/*          = 1: the optimal blocksize; if this value is 1, an unblocked */
/*               algorithm will give the best performance. */
/*          = 2: the minimum block size for which the block routine */
/*               should be used; if the usable block size is less than */
/*               this value, an unblocked routine should be used. */
/*          = 3: the crossover point (in a block routine, for N less */
/*               than this value, an unblocked routine should be used) */
/*          = 4: the number of shifts, used in the nonsymmetric */
/*               eigenvalue routines (DEPRECATED) */
/*          = 5: the minimum column dimension for blocking to be used; */
/*               rectangular blocks must have dimension at least k by m, */
/*               where k is given by ILAENV(2,...) and m by ILAENV(5,...) */
/*          = 6: the crossover point for the SVD (when reducing an m by n */
/*               matrix to bidiagonal form, if max(m,n)/min(m,n) exceeds */
/*               this value, a QR factorization is used first to reduce */
/*               the matrix to a triangular form.) */
/*          = 7: the number of processors */
/*          = 8: the crossover point for the multishift QR method */
/*               for nonsymmetric eigenvalue problems (DEPRECATED) */
/*          = 9: maximum size of the subproblems at the bottom of the */
/*               computation tree in the divide-and-conquer algorithm */
/*               (used by xGELSD and xGESDD) */
/*          =10: ieee NaN arithmetic can be trusted not to trap */
/*          =11: infinity arithmetic can be trusted not to trap */
/*          12 <= ISPEC <= 16: */
/*               xHSEQR or one of its subroutines, */
/*               see IPARMQ for detailed explanation */

/*  NAME    (input) CHARACTER*(*) */
/*          The name of the calling subroutine, in either upper case or */
/*          lower case. */

/*  OPTS    (input) CHARACTER*(*) */
/*          The character options to the subroutine NAME, concatenated */
/*          into a single character string.  For example, UPLO = 'U', */
/*          TRANS = 'T', and DIAG = 'N' for a triangular routine would */
/*          be specified as OPTS = 'UTN'. */

/*  N1      (input) int */
/*  N2      (input) int */
/*  N3      (input) int */
/*  N4      (input) int */
/*          Problem dimensions for the subroutine NAME; these may not all */
/*          be required. */

/*  Further Details */
/*  =============== */

/*  The following conventions have been used when calling ILAENV from the */
/*  LAPACK routines: */
/*  1)  OPTS is a concatenation of all of the character options to */
/*      subroutine NAME, in the same order that they appear in the */
/*      argument list for NAME, even if they are not used in determining */
/*      the value of the parameter specified by ISPEC. */
/*  2)  The problem dimensions N1, N2, N3, N4 are specified in the order */
/*      that they appear in the argument list for NAME.  N1 is used */
/*      first, N2 second, and so on, and unused problem dimensions are */
/*      passed a value of -1. */
/*  3)  The parameter value returned by ILAENV is checked for validity in */
/*      the calling subroutine.  For example, ILAENV is used to retrieve */
/*      the optimal blocksize for STRTRI as follows: */

/*      NB = ILAENV( 1, 'STRTRI', UPLO // DIAG, N, -1, -1, -1 ) */
/*      IF( NB.LE.1 ) NB = MAX( 1, N ) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Executable Statements .. */

    switch (*ispec) {
	case 1:  goto L10;
	case 2:  goto L10;
	case 3:  goto L10;
	case 4:  goto L80;
	case 5:  goto L90;
	case 6:  goto L100;
	case 7:  goto L110;
	case 8:  goto L120;
	case 9:  goto L130;
	case 10:  goto L140;
	case 11:  goto L150;
	case 12:  goto L160;
	case 13:  goto L160;
	case 14:  goto L160;
	case 15:  goto L160;
	case 16:  goto L160;
    }

/*     Invalid value for ISPEC */

    ret_val = -1;
    return ret_val;

L10:

/*     Convert NAME to upper case if the first character is lower case. */

    ret_val = 1;
    s_copy(subnam, name__, (ftnlen)1, name_len);
    ic = *(unsigned char *)subnam;
    iz = 'Z';
    if (iz == 90 || iz == 122) {

/*        ASCII character set */

	if (ic >= 97 && ic <= 122) {
	    *(unsigned char *)subnam = (char) (ic - 32);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if (ic >= 97 && ic <= 122) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic - 32);
		}
/* L20: */
	    }
	}

    } else if (iz == 233 || iz == 169) {

/*        EBCDIC character set */

	if (ic >= 129 && ic <= 137 || ic >= 145 && ic <= 153 || ic >= 162 && 
		ic <= 169) {
	    *(unsigned char *)subnam = (char) (ic + 64);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if (ic >= 129 && ic <= 137 || ic >= 145 && ic <= 153 || ic >= 
			162 && ic <= 169) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic + 64);
		}
/* L30: */
	    }
	}

    } else if (iz == 218 || iz == 250) {

/*        Prime machines:  ASCII+128 */

	if (ic >= 225 && ic <= 250) {
	    *(unsigned char *)subnam = (char) (ic - 32);
	    for (i__ = 2; i__ <= 6; ++i__) {
		ic = *(unsigned char *)&subnam[i__ - 1];
		if (ic >= 225 && ic <= 250) {
		    *(unsigned char *)&subnam[i__ - 1] = (char) (ic - 32);
		}
/* L40: */
	    }
	}
    }

    *(unsigned char *)c1 = *(unsigned char *)subnam;
    sname = *(unsigned char *)c1 == 'S' || *(unsigned char *)c1 == 'D';
    cname = *(unsigned char *)c1 == 'C' || *(unsigned char *)c1 == 'Z';
    if (! (cname || sname)) {
	return ret_val;
    }
    s_copy(c2, subnam + 1, (ftnlen)1, (ftnlen)2);
    s_copy(c3, subnam + 3, (ftnlen)1, (ftnlen)3);
    s_copy(c4, c3 + 1, (ftnlen)1, (ftnlen)2);

    switch (*ispec) {
	case 1:  goto L50;
	case 2:  goto L60;
	case 3:  goto L70;
    }

L50:

/*     ISPEC = 1:  block size */

/*     In these examples, separate code is provided for setting NB for */
/*     float and complex.  We assume that NB will take the same value in */
/*     single or double precision. */

    nb = 1;

    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	} else if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, 
		"RQF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)
		1, (ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3) 
		== 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 32;
	    } else {
		nb = 32;
	    }
	} else if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "PO", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	} else if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 32;
	} else if (sname && s_cmp(c3, "GST", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	} else if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 32;
	} else if (s_cmp(c3, "GST", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 64;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nb = 32;
	    }
	}
    } else if (s_cmp(c2, "GB", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		if (*n4 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    } else {
		if (*n4 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    }
	}
    } else if (s_cmp(c2, "PB", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		if (*n2 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    } else {
		if (*n2 <= 64) {
		    nb = 1;
		} else {
		    nb = 32;
		}
	    }
	}
    } else if (s_cmp(c2, "TR", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (s_cmp(c2, "LA", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "UUM", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nb = 64;
	    } else {
		nb = 64;
	    }
	}
    } else if (sname && s_cmp(c2, "ST", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "EBZ", (ftnlen)1, (ftnlen)3) == 0) {
	    nb = 1;
	}
    }
    ret_val = nb;
    return ret_val;

L60:

/*     ISPEC = 2:  minimum block size */

    nbmin = 2;
    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "RQF", (
		ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)1, (
		ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3) == 0)
		 {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	} else if (s_cmp(c3, "TRI", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 2;
	    } else {
		nbmin = 2;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRF", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nbmin = 8;
	    } else {
		nbmin = 8;
	    }
	} else if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nbmin = 2;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nbmin = 2;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	} else if (*(unsigned char *)c3 == 'M') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nbmin = 2;
	    }
	}
    }
    ret_val = nbmin;
    return ret_val;

L70:

/*     ISPEC = 3:  crossover point */

    nx = 0;
    if (s_cmp(c2, "GE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "QRF", (ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "RQF", (
		ftnlen)1, (ftnlen)3) == 0 || s_cmp(c3, "LQF", (ftnlen)1, (
		ftnlen)3) == 0 || s_cmp(c3, "QLF", (ftnlen)1, (ftnlen)3) == 0)
		 {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	} else if (s_cmp(c3, "HRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	} else if (s_cmp(c3, "BRD", (ftnlen)1, (ftnlen)3) == 0) {
	    if (sname) {
		nx = 128;
	    } else {
		nx = 128;
	    }
	}
    } else if (s_cmp(c2, "SY", (ftnlen)1, (ftnlen)2) == 0) {
	if (sname && s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nx = 32;
	}
    } else if (cname && s_cmp(c2, "HE", (ftnlen)1, (ftnlen)2) == 0) {
	if (s_cmp(c3, "TRD", (ftnlen)1, (ftnlen)3) == 0) {
	    nx = 32;
	}
    } else if (sname && s_cmp(c2, "OR", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nx = 128;
	    }
	}
    } else if (cname && s_cmp(c2, "UN", (ftnlen)1, (ftnlen)2) == 0) {
	if (*(unsigned char *)c3 == 'G') {
	    if (s_cmp(c4, "QR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "RQ", 
		    (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "LQ", (ftnlen)1, (
		    ftnlen)2) == 0 || s_cmp(c4, "QL", (ftnlen)1, (ftnlen)2) ==
		     0 || s_cmp(c4, "HR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(
		    c4, "TR", (ftnlen)1, (ftnlen)2) == 0 || s_cmp(c4, "BR", (
		    ftnlen)1, (ftnlen)2) == 0) {
		nx = 128;
	    }
	}
    }
    ret_val = nx;
    return ret_val;

L80:

/*     ISPEC = 4:  number of shifts (used by xHSEQR) */

    ret_val = 6;
    return ret_val;

L90:

/*     ISPEC = 5:  minimum column dimension (not used) */

    ret_val = 2;
    return ret_val;

L100:

/*     ISPEC = 6:  crossover point for SVD (used by xGELSS and xGESVD) */

    ret_val = (int) ((float) min(*n1,*n2) * 1.6f);
    return ret_val;

L110:

/*     ISPEC = 7:  number of processors (not used) */

    ret_val = 1;
    return ret_val;

L120:

/*     ISPEC = 8:  crossover point for multishift (used by xHSEQR) */

    ret_val = 50;
    return ret_val;

L130:

/*     ISPEC = 9:  maximum size of the subproblems at the bottom of the */
/*                 computation tree in the divide-and-conquer algorithm */
/*                 (used by xGELSD and xGESDD) */

    ret_val = 25;
    return ret_val;

L140:

/*     ISPEC = 10: ieee NaN arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__1, &c_b163, &c_b164);
    }
    return ret_val;

L150:

/*     ISPEC = 11: infinity arithmetic can be trusted not to trap */

/*     ILAENV = 0 */
    ret_val = 1;
    if (ret_val == 1) {
	ret_val = ieeeck_(&c__0, &c_b163, &c_b164);
    }
    return ret_val;

L160:

/*     12 <= ISPEC <= 16: xHSEQR or one of its subroutines. */

    ret_val = iparmq_(ispec, name__, opts, n1, n2, n3, n4)
	    ;
    return ret_val;

/*     End of ILAENV */

} /* ilaenv_ */


/* Subroutine */ int dgetrf_(int *m, int *n, double *a, int *
	lda, int *ipiv, int *info)
{
    /* System generated locals */
    int a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;

    /* Local variables */
    int i__, j, jb, nb;
    //extern /* Subroutine */ int dgemm_(char *, char *, int *, int *, 
	  //  int *, double *, double *, int *, double *, 
	    //int *, double *, double *, int *);
    int iinfo;
	    //double *, int *, dgetf2_(
	    //int *, int *, double *, int *, int *, int 
	    //*), xerbla_(char *, int *);
    extern int ilaenv_(int *, char *, char *, int *, int *, 
	    int *, int *);
    extern /* Subroutine */ int dlaswp_(int *, double *, int *, 
	    int *, int *, int *, int *);


/*  -- LAPACK routine (version 3.1) -- */
/*     Univ. of Tennessee, Univ. of California Berkeley and NAG Ltd.. */
/*     March 2008 */

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*  DGETRF computes an LU factorization of a general M-by-N matrix A */
/*  using partial pivoting with row interchanges. */

/*  The factorization has the form */
/*     A = P * L * U */
/*  where P is a permutation matrix, L is lower triangular with unit */
/*  diagonal elements (lower trapezoidal if m > n), and U is upper */
/*  triangular (upper trapezoidal if m < n). */

/*  This is the Crout Level 3 BLAS version of the algorithm. */

/*  Arguments */
/*  ========= */

/*  M       (input) int */
/*          The number of rows of the matrix A.  M >= 0. */

/*  N       (input) int */
/*          The number of columns of the matrix A.  N >= 0. */

/*  A       (input/output) DOUBLE PRECISION array, dimension (LDA,N) */
/*          On entry, the M-by-N matrix to be factored. */
/*          On exit, the factors L and U from the factorization */
/*          A = P*L*U; the unit diagonal elements of L are not stored. */

/*  LDA     (input) int */
/*          The leading dimension of the array A.  LDA >= max(1,M). */

/*  IPIV    (output) int array, dimension (min(M,N)) */
/*          The pivot indices; for 1 <= i <= min(M,N), row i of the */
/*          matrix was interchanged with row IPIV(i). */

/*  INFO    (output) int */
/*          = 0:  successful exit */
/*          < 0:  if INFO = -i, the i-th argument had an illegal value */
/*          > 0:  if INFO = i, U(i,i) is exactly zero. The factorization */
/*                has been completed, but the factor U is exactly */
/*                singular, and division by zero will occur if it is used */
/*                to solve a system of equations. */

/*  ===================================================================== */

/*     .. Parameters .. */
/*     .. */
/*     .. Local Scalars .. */
/*     .. */
/*     .. External Subroutines .. */
/*     .. */
/*     .. External Functions .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
/*     .. Executable Statements .. */

/*     Test the input parameters. */

    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;
    --ipiv;

    /* Function Body */
    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGETRF", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0) {
	return 0;
    }

/*     Determine the block size for this environment. */

    nb = ilaenv_(&c__1, "DGETRF", " ", m, n, &c_n1, &c_n1);
    if (nb <= 1 || nb >= min(*m,*n)) {

/*        Use unblocked code. */

	dgetf2_(m, n, &a[a_offset], lda, &ipiv[1], info);
    } else {

/*        Use blocked code. */

	i__1 = min(*m,*n);
	i__2 = nb;
	for (j = 1; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
/* Computing MIN */
	    i__3 = min(*m,*n) - j + 1;
	    jb = min(i__3,nb);

/*           Update current block. */

	    i__3 = *m - j + 1;
	    i__4 = j - 1;
	    dgemm_("No transpose", "No transpose", &i__3, &jb, &i__4, &c_b11, 
		    &a[j + a_dim1], lda, &a[j * a_dim1 + 1], lda, &c_b12, &a[
		    j + j * a_dim1], lda);

/*           Factor diagonal and subdiagonal blocks and test for exact */
/*           singularity. */

	    i__3 = *m - j + 1;
	    dgetf2_(&i__3, &jb, &a[j + j * a_dim1], lda, &ipiv[j], &iinfo);

/*           Adjust INFO and the pivot indices. */

	    if (*info == 0 && iinfo > 0) {
		*info = iinfo + j - 1;
	    }
/* Computing MIN */
	    i__4 = *m, i__5 = j + jb - 1;
	    i__3 = min(i__4,i__5);
	    for (i__ = j; i__ <= i__3; ++i__) {
		ipiv[i__] = j - 1 + ipiv[i__];
/* L10: */
	    }

/*           Apply interchanges to column 1:J-1 */

	    i__3 = j - 1;
	    i__4 = j + jb - 1;
	    dlaswp_(&i__3, &a[a_offset], lda, &j, &i__4, &ipiv[1], &c__1);

	    if (j + jb <= *n) {

/*              Apply interchanges to column J+JB:N */

		i__3 = *n - j - jb + 1;
		i__4 = j + jb - 1;
		dlaswp_(&i__3, &a[(j + jb) * a_dim1 + 1], lda, &j, &i__4, &
			ipiv[1], &c__1);

		i__3 = *n - j - jb + 1;
		i__4 = j - 1;
		dgemm_("No transpose", "No transpose", &jb, &i__3, &i__4, &
			c_b11, &a[j + a_dim1], lda, &a[(j + jb) * a_dim1 + 1], 
			 lda, &c_b12, &a[j + (j + jb) * a_dim1], lda);

/*              Compute block row of U. */

		i__3 = *n - j - jb + 1;
		dtrsm_("Left", "Lower", "No transpose", "Unit", &jb, &i__3, &
			c_b12, &a[j + j * a_dim1], lda, &a[j + (j + jb) * 
			a_dim1], lda);
	    }
/* L20: */
	}
    }
    return 0;

/*     End of DGETRF */

} /* dgetrf_ */

/***********************End of the inmplementations******************/

double* solve(ml hierarchy, int nu1, int nu2, int nlevels, double x0[], 
                                double b0[], double tol, int maxiter)
{
    int i, j, ITER;
    const double omega = 2.0/3.0;
    csr_matrix* A = hierarchy.levels[0].A;

    double* residuals = (double*) calloc(maxiter, sizeof(double));
    double* x_copy    = (double*) malloc(A->n * sizeof(double));
    double* A_dense   = (double*) malloc(hierarchy.levels[nlevels-1].A->m*hierarchy.levels[nlevels-1].A->n*sizeof(double));
    int* ipiv         = (int*) malloc(sizeof(int)*hierarchy.levels[nlevels-1].A->n);
    printf("the mem address of ipiv is: %p \n", ipiv);  //az
    double* Ax        = (double*) malloc(sizeof(double) * A->n);
    double* temp      = (double*) malloc(sizeof(double) * A->n);

    for (i=0; i<A->n; i++) {
        hierarchy.levels[0].x[i] = x0[i];
        hierarchy.levels[0].b[i] = b0[i];
    }
    assert(nu1 % 2 == 0 && "nu1 must be even");
    assert(nu2 % 2 == 0 && "nu2 must be even");
    printf("Solving %d x %d prolem with %d levels to a tolerance of %g\n\n", A->n, A->m, nlevels, tol);
    residual_norm(A, hierarchy.levels[0].x, hierarchy.levels[0].b, Ax, &residuals[0]);
    ITER = 0;

    //while(ITER < maxiter && residuals[ITER] > tol) {
    while(ITER < 1 && residuals[ITER] > tol) {
        ITER++;
        /*
         for (j = 0; j < A->n; j++)
            x_copy[j] = hierarchy.levels[0].x[j];
        */

        /* traverse down */
        for(i =0; i < nlevels-1; i++) {
            /* smooth x */
            A = hierarchy.levels[i].A;
            for (j=0; j < nu1; j++) {
                jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                swapD_ptr(&hierarchy.levels[i].x, &x_copy);
                /* Not efficient but currently swaping  pointers causes the fault injector segfault */
                /*
                 * if(nu1 % 2 == 1) {
                    if (j % 2 == 0)
                        jacobi(A, x_copy, hierarchy.levels[i].b, hierarchy.levels[i].x, omega, 0, A->m, 1);
                    else
                        jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                }
                else {
                    if (j % 2 == 0)
                        jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                    else
                        jacobi(A, x_copy, hierarchy.levels[i].b, hierarchy.levels[i].x, omega, 0, A->m, 1);
                }
                */
            }

            /* restrict residual */
            residual(A, hierarchy.levels[i].x, hierarchy.levels[i].b, Ax, temp);
            printf("the mem address of hierarchy.levels[0].R.V is: %p \n", hierarchy.levels[0].R->V);  //az
            csr_matvec(hierarchy.levels[i].R, temp, hierarchy.levels[i+1].b);

            /* populate x */
            for (j = 0; j < hierarchy.levels[i+1].A->m; j++) {
                hierarchy.levels[i+1].x[j] = 0.0;
                //x_copy[j] = 0.0;
            }
        }


        /* convert A from csr to dense */
        A = hierarchy.levels[nlevels-1].A;
        for(i=0; i< A->n * A->m; i++)
            A_dense[i] = 0.0;
        for(i = 0; i < A->n; i++) {
            for(j = A->I[i]; j < A->I[i+1]; j++) {
                int col_ind = A->J[j];
                A_dense[i + A->n*col_ind] = A->V[j];    /*column major*/
            }
        }

        /* coarse-grid solve */
        int nrhs = 1, n = A->n, lda = A->n, ldb = A->n, info;
        dgesv_(&n, &nrhs, A_dense, &lda, ipiv, hierarchy.levels[nlevels-1].b, &ldb, &info);
        for (j = 0; j < A->n; j++)
            hierarchy.levels[nlevels-1].x[j] = hierarchy.levels[nlevels-1].b[j];

        /* traverse up */
        for(i = nlevels-2; i >= 0; i--) {
            A = hierarchy.levels[i].A;
            int length = hierarchy.levels[i].P->n;

            /* prolongate x */
            csr_matvec(hierarchy.levels[i].P, hierarchy.levels[i+1].x, Ax);

            /* correct x */
            for(j = 0; j < length; j++) {
                hierarchy.levels[i].x[j] = hierarchy.levels[i].x[j] + Ax[j];
                //x_copy[j] = hierarchy.levels[i].x[j];
            }

            /* post smooth */
            for(j = 0; j < nu2; j++) {
                jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                swapD_ptr(&hierarchy.levels[i].x, &x_copy);
                /* Not efficient but currently swaping  pointers causes the fault injector segfault */
                /*
                 * if(nu1 % 2 == 1) {
                    if (j % 2 == 0)
                        jacobi(A, x_copy, hierarchy.levels[i].b, hierarchy.levels[i].x, omega, 0, A->m, 1);
                    else 
                        jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                }
                else {
                    if (j % 2 == 0)
                        jacobi(A, hierarchy.levels[i].x, hierarchy.levels[i].b, x_copy, omega, 0, A->m, 1);
                    else
                        jacobi(A, x_copy, hierarchy.levels[i].b, hierarchy.levels[i].x, omega, 0, A->m, 1);
                }
                */
            }
        }
        residual_norm(hierarchy.levels[0].A, hierarchy.levels[0].x, hierarchy.levels[0].b, Ax, &residuals[ITER]);
    }
    free(x_copy);
    free(A_dense);
    free(ipiv);
    free(Ax);
    free(temp);

    return residuals;
}

