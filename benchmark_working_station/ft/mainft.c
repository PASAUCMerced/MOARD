//-------------------------------------------------------------------------//
//                                                                         //
//  This benchmark is a serial C version of the NPB FT code. This C        //
//  version is developed by the Center for Manycore Programming at Seoul   //
//  National University and derived from the serial Fortran versions in    //
//  "NPB3.3-SER" developed by NAS.                                         //
//                                                                         //
//  Permission to use, copy, distribute and modify this software for any   //
//  purpose with or without fee is hereby granted. This software is        //
//  provided "as is" without express or implied warranty.                  //
//                                                                         //
//  Information on NPB 3.3, including the technical report, the original   //
//  specifications, source code, results and information on how to submit  //
//  new results, is available at:                                          //
//                                                                         //
//           http://www.nas.nasa.gov/Software/NPB/                         //
//                                                                         //
//  Send comments or suggestions for this C version to cmp@aces.snu.ac.kr  //
//                                                                         //
//          Center for Manycore Programming                                //
//          School of Computer Science and Engineering                     //
//          Seoul National University                                      //
//          Seoul 151-744, Korea                                           //
//                                                                         //
//          E-mail:  cmp@aces.snu.ac.kr                                    //
//                                                                         //
//-------------------------------------------------------------------------//

//-------------------------------------------------------------------------//
// Authors: Sangmin Seo, Jungwon Kim, Jun Lee, Jeongho Nah, Gangwon Jo,    //
//          and Jaejin Lee                                                 //
//-------------------------------------------------------------------------//

//---------------------------------------------------------------------
// FT benchmark
//---------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include <stdlib.h> //

#include "global.h"
#include "print_results.h"
#include "timers.h"

static char getclass();

logical timers_enabled;

// for checksum data
/* common /sumcomm/ */
static dcomplex sums[NITER_DEFAULT+1];

/* common /mainarrays/ */
static double twiddle[NZ][NY][NX+1];
static dcomplex xnt[NZ][NY][NX+1];
static dcomplex y[NZ][NY][NX+1];
//static dcomplex pad1[128], pad2[128];


/* common /blockinfo/ */
static int fftblock;
//static int fftblockpad;

/* common /workarr/ */
static dcomplex plane[(BLOCKMAX+1)*MAXDIM];
//static dcomplex pad[128];
static dcomplex scr[MAXDIM][BLOCKMAX+1];

static void Swarztrauber(int is, int m, int vlen, int n, int xd1,
                         void *ox, dcomplex exponent[n])
{
  dcomplex (*x)[xd1] = (dcomplex (*)[xd1])ox;

  int i, j, l;
  dcomplex u1, x11, x21;
  int k, n1, li, lj, lk, ku, i11, i12, i21, i22;

  if (timers_enabled) timer_start(4);
  //---------------------------------------------------------------------
  // Perform one variant of the Stockham FFT.
  //---------------------------------------------------------------------
  n1 = n / 2;
  lj = 1;
  li = 1 << m;
  for (l = 1; l <= m; l += 2) {
    lk = lj;
    lj = 2 * lk;
    li = li / 2;
    ku = li;

    for (i = 0; i <= li - 1; i++) {
      i11 = i * lk;
      i12 = i11 + n1;
      i21 = i * lj;
      i22 = i21 + lk;

      if (is >= 1) {
        u1 = exponent[ku+i];
      } else {
        u1 = dconjg(exponent[ku+i]);
      }
      for (k = 0; k <= lk - 1; k++) {
        for (j = 0; j < vlen; j++) {
          x11 = x[i11+k][j];
          x21 = x[i12+k][j];
          scr[i21+k][j] = dcmplx_add(x11, x21);
          scr[i22+k][j] = dcmplx_mul(u1, dcmplx_sub(x11, x21));
        }
      }
    }

    if (l == m) {
      for (k = 0; k < n; k++) {
        for (j = 0; j < vlen; j++) {
          x[k][j] = scr[k][j];
        }
      }
    } else {
      lk = lj;
      lj = 2 * lk;
      li = li / 2;
      ku = li;

      for (i = 0; i <= li - 1; i++) {
        i11 = i * lk;
        i12 = i11 + n1;
        i21 = i * lj;
        i22 = i21 + lk;

        if (is >= 1) {
          u1 = exponent[ku+i];
        } else {
          u1 = dconjg(exponent[ku+i]);
        }
        for (k = 0; k <= lk - 1; k++) {
          for (j = 0; j < vlen; j++) {
            x11 = scr[i11+k][j];
            x21 = scr[i12+k][j];
            x[i21+k][j] = dcmplx_add(x11, x21);
            x[i22+k][j] = dcmplx_mul(u1, dcmplx_sub(x11, x21));
          }
        }
      }
    }
  }
  if (timers_enabled) timer_stop(4);
}


void fftXYZ(int sign, int n1, int n2, int n3,
            dcomplex x[n3][n2][n1+1], dcomplex xout[(n1+1)*n2*n3],
            dcomplex exp1[n1], dcomplex exp2[n2], dcomplex exp3[n3])
{
  int i, j, k, log;
  int bls, ble;
  int len;
  int blkp;

  if (timers_enabled) timer_start(3);

  fftblock = CACHESIZE / n1;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n1);
  if (timers_enabled) timer_start(7);
  for (k = 0; k < n3; k++) {
    for (bls = 0; bls < n2; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n2) ble = n2 - 1;
      len = ble - bls + 1;
      for (j = bls; j <= ble; j++) {
        for (i = 0; i < n1; i++) {
          plane[j-bls+blkp*i] = x[k][j][i];
        }
      }
      Swarztrauber(sign, log, len, n1, blkp, plane, exp1);
      for (j = bls; j <= ble; j++) {
        for (i = 0; i < n1; i++) {
          x[k][j][i] = plane[j-bls+blkp*i];
        }
      }
    }
  }
  if (timers_enabled) timer_stop(7);

  fftblock = CACHESIZE / n2;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n2);
  if (timers_enabled) timer_start(8);
  for (k = 0; k < n3; k++) {
    for (bls = 0; bls < n1; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n1) ble = n1 - 1;
      len = ble - bls + 1;
      Swarztrauber(sign, log, len, n2, n1+1, &x[k][0][bls], exp2);
    }
  }
  if (timers_enabled) timer_stop(8);

  fftblock = CACHESIZE / n3;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n3);
  if (timers_enabled) timer_start(9);
  for (k = 0; k < n2; k++) {
    for (bls = 0; bls < n1; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n1) ble = n1 - 1;
      len = ble - bls + 1;
      for (i = 0; i < n3; i++) {
        for (j = bls; j <= ble; j++) {
          plane[j-bls+blkp*i] = x[i][k][j];
        }
      }
      Swarztrauber(sign, log, len, n3, blkp, plane, exp3);
      for (i = 0; i <= n3-1; i++) {
        for (j = bls; j <= ble; j++) {
          xout[j+(n1+1)*(k+n2*i)] = plane[j-bls+blkp*i];
        }
      }
    }
  }
  if (timers_enabled) timer_stop(9);
  if (timers_enabled) timer_stop(3);
}

void XYZfft(int sign, int n1, int n2, int n3,
            dcomplex x[n3][n2][n1+1], dcomplex xout[(n1+1)*n2*n3],
            dcomplex exp1[n1], dcomplex exp2[n2], dcomplex exp3[n3])
{
  int i, j, k, log;
  int bls, ble;
  int len;
  int blkp;

  if (timers_enabled) timer_start(3);

  fftblock = CACHESIZE / n1;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n1);
  if (timers_enabled) timer_start(7);
  for (k = 0; k < n3; k++) {
    for (bls = 0; bls < n2; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n2) ble = n2 - 1;
      len = ble - bls + 1;
      for (j = bls; j <= ble; j++) {
        for (i = 0; i < n1; i++) {
          plane[j-bls+blkp*i] = x[k][j][i];
        }
      }
      Swarztrauber(sign, log, len, n1, blkp, plane, exp1);
      for (j = bls; j <= ble; j++) {
        for (i = 0; i < n1; i++) {
          x[k][j][i] = plane[j-bls+blkp*i];
        }
      }
    }
  }
  if (timers_enabled) timer_stop(7);

  fftblock = CACHESIZE / n2;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n2);
  if (timers_enabled) timer_start(8);
  for (k = 0; k < n3; k++) {
    for (bls = 0; bls < n1; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n1) ble = n1 - 1;
      len = ble - bls + 1;
      Swarztrauber(sign, log, len, n2, n1+1, &x[k][0][bls], exp2);
    }
  }
  if (timers_enabled) timer_stop(8);

  fftblock = CACHESIZE / n3;
  if (fftblock >= BLOCKMAX) fftblock = BLOCKMAX;
  blkp = fftblock + 1;
  log = ilog2(n3);
  if (timers_enabled) timer_start(9);
  for (k = 0; k < n2; k++) {
    for (bls = 0; bls < n1; bls += fftblock) {
      ble = bls + fftblock - 1;
      if (ble > n1) ble = n1 - 1;
      len = ble - bls + 1;
      for (i = 0; i < n3; i++) {
        for (j = bls; j <= ble; j++) {
          plane[j-bls+blkp*i] = x[i][k][j];
        }
      }
      Swarztrauber(sign, log, len, n3, blkp, plane, exp3);
      for (i = 0; i <= n3-1; i++) {
        for (j = bls; j <= ble; j++) {
          xout[j+(n1+1)*(k+n2*i)] = plane[j-bls+blkp*i];
        }
      }
    }
  }
  if (timers_enabled) timer_stop(9);
  if (timers_enabled) timer_stop(3);
}

void appft(int niter, double *total_time, logical *verified)
{
  int i, j, k, kt, n12, n22, n32, ii, jj, kk, ii2, ik2;
  double ap;

  dcomplex exp1[NX], exp2[NY], exp3[NZ];

  for (i = 1; i <= 15; i++) {
    timer_clear(i);
  }         

  timer_start(2);      
  compute_initial_conditions(NX, NY, NZ, xnt);

  CompExp(NX, exp1);
  CompExp(NY, exp2);
  CompExp(NZ, exp3);          
  XYZfft(1, NX, NY, NZ, xnt, (dcomplex *)y, exp1, exp2, exp3); //off
  timer_stop(2);

  timer_start(1);
  if (timers_enabled) timer_start(13);

  n12 = NX / 2;
  n22 = NY / 2;
  n32 = NZ / 2;
  ap = -4.0 * ALPHA * (PI * PI);
  for (i = 0; i < NZ; i++) {
    ii = i - (i / n32) * NZ;
    ii2 = ii * ii;
    for (k = 0; k < NY; k++) {
      kk = k - (k / n22) * NY;
      ik2 = ii2 + kk*kk;
      for (j = 0; j < NX; j++) {
        jj = j - (j / n12) * NX;
        twiddle[i][k][j] = exp(ap*(double)(jj*jj + ik2));
      }
    }
  }
  if (timers_enabled) timer_stop(13);

  if (timers_enabled) timer_start(12);
  compute_initial_conditions(NX, NY, NZ, xnt);
  if (timers_enabled) timer_stop(12);
  if (timers_enabled) timer_start(15);
  XYZfft(1, NX, NY, NZ, xnt, (dcomplex *)y, exp1, exp2, exp3); //off
  if (timers_enabled) timer_stop(15);

  for (kt = 1; kt <= niter; kt++) {
    if (timers_enabled) timer_start(11);
    evolve(NX, NY, NZ, xnt, y, twiddle);
    if (timers_enabled) timer_stop(11);
    if (timers_enabled) timer_start(15);
    fftXYZ(-1, NX, NY, NZ, xnt, (dcomplex *)xnt, exp1, exp2, exp3); //
    if (timers_enabled) timer_stop(15);
    if (timers_enabled) timer_start(10);
    CalculateChecksum(&sums[kt], kt, NX, NY, NZ, xnt);
    if (timers_enabled) timer_stop(10);
  }

  // Verification test.
  if (timers_enabled) timer_start(14);
  verify(NX, NY, NZ, niter, sums, verified);
  if (timers_enabled) timer_stop(14);
  timer_stop(1);

  *total_time = timer_read(1);
  if (!timers_enabled) return;

  printf(" FT subroutine timers \n");
  printf(" %26s =%9.4f\n", "FT total                  ", timer_read(1));
  printf(" %26s =%9.4f\n", "WarmUp time               ", timer_read(2));
  printf(" %26s =%9.4f\n", "fftXYZ body               ", timer_read(3));
  printf(" %26s =%9.4f\n", "Swarztrauber              ", timer_read(4));
  printf(" %26s =%9.4f\n", "X time                    ", timer_read(7));
  printf(" %26s =%9.4f\n", "Y time                    ", timer_read(8));
  printf(" %26s =%9.4f\n", "Z time                    ", timer_read(9));
  printf(" %26s =%9.4f\n", "CalculateChecksum         ", timer_read(10));
  printf(" %26s =%9.4f\n", "evolve                    ", timer_read(11));
  printf(" %26s =%9.4f\n", "compute_initial_conditions", timer_read(12));
  printf(" %26s =%9.4f\n", "twiddle                   ", timer_read(13));
  printf(" %26s =%9.4f\n", "verify                    ", timer_read(14));
  printf(" %26s =%9.4f\n", "fftXYZ                    ", timer_read(15));
  printf(" %26s =%9.4f\n", "Benchmark time            ", *total_time);
}



int main(int argc, char *argv[])
{
  int niter;
  char Class;
  double total_time, mflops;
  logical verified;

  FILE *fp;
  if ((fp = fopen("timer.flag", "r")) != NULL) {
    timers_enabled = true;
    fclose(fp);
  } else {
    timers_enabled = false;
  }

  niter = NITER_DEFAULT;

  printf("\n\n NAS Parallel Benchmarks (NPB3.3-SER-C) - FT Benchmark\n\n");
  printf(" Size                : %4dx%4dx%4d\n", NX, NY, NZ);
  printf(" Iterations          :     %10d\n", niter);
  printf("\n");

  Class = getclass();

  appft(niter, &total_time, &verified);

  if (total_time != 0.0) {
    mflops = 1.0e-6 * (double)NTOTAL *
            (14.8157 + 7.19641 * log((double)NTOTAL)
             + (5.23518 + 7.21113 * log((double)NTOTAL)) * niter)
            / total_time;
  } else {
    mflops = 0.0;
  }

  print_results("FT", Class, NX, NY, NZ, niter,
                total_time, mflops, "          floating point", verified, 
                NPBVERSION, COMPILETIME, CS1, CS2, CS3, CS4, 
                CS5, CS6, CS7);

  return 0;
}


static char getclass()
{
  if ((NX == 64) && (NY == 64) &&                 
      (NZ == 64) && (NITER_DEFAULT == 6)) {
    return 'S';
  } else if ((NX == 128) && (NY == 128) &&
             (NZ == 32) && (NITER_DEFAULT == 6)) {
    return 'W';
  } else if ((NX == 256) && (NY == 256) &&
             (NZ == 128) && (NITER_DEFAULT == 6)) {
    return 'A';
  } else if ((NX == 512) && (NY == 256) &&
             (NZ == 256) && (NITER_DEFAULT == 20)) {
    return 'B';
  } else if ((NX == 512) && (NY == 512) &&
             (NZ == 512) && (NITER_DEFAULT == 20)) {
    return 'C';
  } else if ((NX == 2048) && (NY == 1024) &&
             (NZ == 1024) && (NITER_DEFAULT == 25)) {
    return 'D';
  } else {
    return 'U';
  }
}

