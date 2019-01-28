/* If BASE is undefined we use function names like gsl_name()
   and assume that we are using doubles.

   If BASE is defined we used function names like gsl_BASE_name()
   and use BASE as the base datatype      */

#define BASE_DOUBLE
#define NULL_VECTOR {0, 0, 0, 0, 0}
#define NULL_VECTOR_VIEW {{0, 0, 0, 0, 0}}

#define NULL_MATRIX {0, 0, 0, 0, 0, 0}
#define NULL_MATRIX_VIEW {{0, 0, 0, 0, 0, 0}}

#define BASE double
#define SHORT
#define ATOMIC double
#define MULTIPLICITY 1
#define FP 1
#define IN_FORMAT "%lg"
#define OUT_FORMAT "%g"
#define ATOMIC_IO ATOMIC
#define ZERO 0.0
#define ONE 1.0
#define BASE_EPSILON GSL_DBL_EPSILON

#define CONCAT2x(a,b) a ## _ ## b 
#define CONCAT2(a,b) CONCAT2x(a,b)
#define CONCAT3x(a,b,c) a ## _ ## b ## _ ## c
#define CONCAT3(a,b,c) CONCAT3x(a,b,c)
#define CONCAT4x(a,b,c,d) a ## _ ## b ## _ ## c ## _ ## d
#define CONCAT4(a,b,c,d) CONCAT4x(a,b,c,d)

#ifndef USE_QUALIFIER
#define QUALIFIER
#endif

#ifdef USE_QUALIFIER
#if defined(BASE_DOUBLE)
#define FUNCTION(dir,name) CONCAT3(dir,QUALIFIER,name)
#define TYPE(dir) dir
#define VIEW(dir,name) CONCAT2(dir,name)
#define QUALIFIED_TYPE(dir) QUALIFIER dir
#define QUALIFIED_VIEW(dir,name) CONCAT3(dir,QUALIFIER,name)
#else
#define FUNCTION(a,c) CONCAT4(a,SHORT,QUALIFIER,c)
#define TYPE(dir) CONCAT2(dir,SHORT)
#define VIEW(dir,name) CONCAT3(dir,SHORT,name)
#define QUALIFIED_TYPE(dir) QUALIFIER CONCAT2(dir,SHORT)
#define QUALIFIED_VIEW(dir,name) CONCAT4(dir,SHORT,QUALIFIER,name)
#endif
#if defined(BASE_GSL_COMPLEX)
#define REAL_TYPE(dir) dir
#define REAL_VIEW(dir,name) CONCAT2(dir,name)
#define QUALIFIED_REAL_TYPE(dir) QUALIFIER dir
#define QUALIFIED_REAL_VIEW(dir,name) CONCAT3(dir,QUALIFIER,name)
#else
#define REAL_TYPE(dir) CONCAT2(dir,SHORT_REAL)
#define REAL_VIEW(dir,name) CONCAT3(dir,SHORT_REAL,name)
#define QUALIFIED_REAL_TYPE(dir) QUALIFIER CONCAT2(dir,SHORT_REAL)
#define QUALIFIED_REAL_VIEW(dir,name) CONCAT4(dir,SHORT_REAL,QUALIFIER,name)
#endif
#else
#if defined(BASE_DOUBLE)
#define FUNCTION(dir,name) CONCAT2(dir,name)
#define TYPE(dir) dir
#define VIEW(dir,name) CONCAT2(dir,name)
#define QUALIFIED_TYPE(dir) TYPE(dir)
#define QUALIFIED_VIEW(dir,name) CONCAT2(dir,name)
#else
#define FUNCTION(a,c) CONCAT3(a,SHORT,c)
#define TYPE(dir) CONCAT2(dir,SHORT)
#define VIEW(dir,name) CONCAT3(dir,SHORT,name)
#define QUALIFIED_TYPE(dir) TYPE(dir)
#define QUALIFIED_VIEW(dir,name) CONCAT3(dir,SHORT,name)
#endif
#if defined(BASE_GSL_COMPLEX)
#define REAL_TYPE(dir) dir
#define REAL_VIEW(dir,name) CONCAT2(dir,name)
#define QUALIFIED_REAL_TYPE(dir) dir
#define QUALIFIED_REAL_VIEW(dir,name) CONCAT2(dir,name)
#else
#define REAL_TYPE(dir) CONCAT2(dir,SHORT_REAL)
#define REAL_VIEW(dir,name) CONCAT3(dir,SHORT_REAL,name)
#define QUALIFIED_REAL_TYPE(dir) CONCAT2(dir,SHORT_REAL)
#define QUALIFIED_REAL_VIEW(dir,name) CONCAT3(dir,SHORT_REAL,name)
#endif
#endif

#define STRING(x) #x
#define EXPAND(x) STRING(x)
#define NAME(x) EXPAND(TYPE(x))
