; ModuleID = 'floating_point_Binary_32_64_convertor.cpp'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external global i8
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_floating_point_Binary_32_64_convertor.cpp, i8* null }]

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) #0

declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) #0

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) #1

; Function Attrs: norecurse nounwind readnone uwtable
define i64 @_Z7pack754ejj(x86_fp80 %f, i32 %bits, i32 %expbits) #2 {
  %1 = add i32 %bits, -1
  %2 = sub i32 %1, %expbits
  %3 = fcmp oeq x86_fp80 %f, 0xK00000000000000000000
  br i1 %3, label %33, label %4

; <label>:4                                       ; preds = %0
  %5 = fcmp olt x86_fp80 %f, 0xK00000000000000000000
  %6 = fsub x86_fp80 0xK80000000000000000000, %f
  %sign.0 = zext i1 %5 to i64
  %fnorm.0 = select i1 %5, x86_fp80 %6, x86_fp80 %f
  %7 = fcmp ult x86_fp80 %fnorm.0, 0xK40008000000000000000
  br i1 %7, label %.preheader, label %.lr.ph7.preheader

.lr.ph7.preheader:                                ; preds = %4
  br label %.lr.ph7

.preheader.loopexit:                              ; preds = %.lr.ph7
  %.lcssa24 = phi i32 [ %10, %.lr.ph7 ]
  %.lcssa23 = phi x86_fp80 [ %9, %.lr.ph7 ]
  br label %.preheader

.preheader:                                       ; preds = %.preheader.loopexit, %4
  %fnorm.1.lcssa = phi x86_fp80 [ %fnorm.0, %4 ], [ %.lcssa23, %.preheader.loopexit ]
  %shift.0.lcssa = phi i32 [ 0, %4 ], [ %.lcssa24, %.preheader.loopexit ]
  %8 = fcmp olt x86_fp80 %fnorm.1.lcssa, 0xK3FFF8000000000000000
  br i1 %8, label %.lr.ph.preheader, label %._crit_edge

.lr.ph.preheader:                                 ; preds = %.preheader
  br label %.lr.ph

.lr.ph7:                                          ; preds = %.lr.ph7.preheader, %.lr.ph7
  %fnorm.15 = phi x86_fp80 [ %9, %.lr.ph7 ], [ %fnorm.0, %.lr.ph7.preheader ]
  %shift.04 = phi i32 [ %10, %.lr.ph7 ], [ 0, %.lr.ph7.preheader ]
  %9 = fmul x86_fp80 %fnorm.15, 0xK3FFE8000000000000000
  %10 = add nuw nsw i32 %shift.04, 1
  %11 = fcmp ult x86_fp80 %9, 0xK40008000000000000000
  br i1 %11, label %.preheader.loopexit, label %.lr.ph7

.lr.ph:                                           ; preds = %.lr.ph.preheader, %.lr.ph
  %fnorm.22 = phi x86_fp80 [ %12, %.lr.ph ], [ %fnorm.1.lcssa, %.lr.ph.preheader ]
  %shift.11 = phi i32 [ %13, %.lr.ph ], [ %shift.0.lcssa, %.lr.ph.preheader ]
  %12 = fmul x86_fp80 %fnorm.22, 0xK40008000000000000000
  %13 = add nsw i32 %shift.11, -1
  %14 = fcmp olt x86_fp80 %12, 0xK3FFF8000000000000000
  br i1 %14, label %.lr.ph, label %._crit_edge.loopexit

._crit_edge.loopexit:                             ; preds = %.lr.ph
  %.lcssa22 = phi i32 [ %13, %.lr.ph ]
  %.lcssa = phi x86_fp80 [ %12, %.lr.ph ]
  br label %._crit_edge

._crit_edge:                                      ; preds = %._crit_edge.loopexit, %.preheader
  %fnorm.2.lcssa = phi x86_fp80 [ %fnorm.1.lcssa, %.preheader ], [ %.lcssa, %._crit_edge.loopexit ]
  %shift.1.lcssa = phi i32 [ %shift.0.lcssa, %.preheader ], [ %.lcssa22, %._crit_edge.loopexit ]
  %15 = fadd x86_fp80 %fnorm.2.lcssa, 0xKBFFF8000000000000000
  %16 = zext i32 %2 to i64
  %17 = shl i64 1, %16
  %18 = sitofp i64 %17 to float
  %19 = fadd float %18, 5.000000e-01
  %20 = fpext float %19 to x86_fp80
  %21 = fmul x86_fp80 %20, %15
  %22 = fptosi x86_fp80 %21 to i64
  %23 = add i32 %expbits, -1
  %24 = shl i32 1, %23
  %25 = add nsw i32 %24, -1
  %26 = add nsw i32 %25, %shift.1.lcssa
  %27 = sext i32 %26 to i64
  %28 = zext i32 %1 to i64
  %29 = shl i64 %sign.0, %28
  %30 = shl i64 %27, %16
  %31 = or i64 %30, %29
  %32 = or i64 %31, %22
  br label %33

; <label>:33                                      ; preds = %0, %._crit_edge
  %.0 = phi i64 [ %32, %._crit_edge ], [ 0, %0 ]
  ret i64 %.0
}

; Function Attrs: norecurse nounwind readnone uwtable
define x86_fp80 @_Z9unpack754mjj(i64 %i, i32 %bits, i32 %expbits) #2 {
  %1 = icmp eq i64 %i, 0
  br i1 %1, label %37, label %2

; <label>:2                                       ; preds = %0
  %3 = add i32 %bits, -1
  %4 = sub i32 %3, %expbits
  %5 = zext i32 %4 to i64
  %6 = shl i64 1, %5
  %7 = add nsw i64 %6, -1
  %8 = and i64 %7, %i
  %9 = uitofp i64 %8 to x86_fp80
  %10 = sitofp i64 %6 to x86_fp80
  %11 = fdiv x86_fp80 %9, %10
  %12 = fadd x86_fp80 %11, 0xK3FFF8000000000000000
  %13 = add i32 %expbits, -1
  %14 = shl i32 1, %13
  %15 = add nsw i32 %14, -1
  %16 = lshr i64 %i, %5
  %17 = zext i32 %expbits to i64
  %18 = shl i64 1, %17
  %19 = add nsw i64 %18, -1
  %20 = and i64 %16, %19
  %21 = zext i32 %15 to i64
  %22 = sub i64 %20, %21
  %23 = icmp sgt i64 %22, 0
  br i1 %23, label %.lr.ph6.preheader, label %.preheader

.lr.ph6.preheader:                                ; preds = %2
  br label %.lr.ph6

.preheader.loopexit:                              ; preds = %.lr.ph6
  %.lcssa18 = phi i64 [ %26, %.lr.ph6 ]
  %.lcssa17 = phi x86_fp80 [ %25, %.lr.ph6 ]
  br label %.preheader

.preheader:                                       ; preds = %.preheader.loopexit, %2
  %result.0.lcssa = phi x86_fp80 [ %12, %2 ], [ %.lcssa17, %.preheader.loopexit ]
  %shift.0.lcssa = phi i64 [ %22, %2 ], [ %.lcssa18, %.preheader.loopexit ]
  %24 = icmp slt i64 %shift.0.lcssa, 0
  br i1 %24, label %.lr.ph.preheader, label %._crit_edge

.lr.ph.preheader:                                 ; preds = %.preheader
  br label %.lr.ph

.lr.ph6:                                          ; preds = %.lr.ph6.preheader, %.lr.ph6
  %result.04 = phi x86_fp80 [ %25, %.lr.ph6 ], [ %12, %.lr.ph6.preheader ]
  %shift.03 = phi i64 [ %26, %.lr.ph6 ], [ %22, %.lr.ph6.preheader ]
  %25 = fmul x86_fp80 %result.04, 0xK40008000000000000000
  %26 = add nsw i64 %shift.03, -1
  %27 = icmp sgt i64 %shift.03, 1
  br i1 %27, label %.lr.ph6, label %.preheader.loopexit

.lr.ph:                                           ; preds = %.lr.ph.preheader, %.lr.ph
  %result.12 = phi x86_fp80 [ %28, %.lr.ph ], [ %result.0.lcssa, %.lr.ph.preheader ]
  %shift.11 = phi i64 [ %29, %.lr.ph ], [ %shift.0.lcssa, %.lr.ph.preheader ]
  %28 = fmul x86_fp80 %result.12, 0xK3FFE8000000000000000
  %29 = add nsw i64 %shift.11, 1
  %30 = icmp slt i64 %shift.11, -1
  br i1 %30, label %.lr.ph, label %._crit_edge.loopexit

._crit_edge.loopexit:                             ; preds = %.lr.ph
  %.lcssa = phi x86_fp80 [ %28, %.lr.ph ]
  br label %._crit_edge

._crit_edge:                                      ; preds = %._crit_edge.loopexit, %.preheader
  %result.1.lcssa = phi x86_fp80 [ %result.0.lcssa, %.preheader ], [ %.lcssa, %._crit_edge.loopexit ]
  %31 = zext i32 %3 to i64
  %32 = shl i64 1, %31
  %33 = and i64 %32, %i
  %34 = icmp ne i64 %33, 0
  %35 = select i1 %34, x86_fp80 0xKBFFF8000000000000000, x86_fp80 0xK3FFF8000000000000000
  %36 = fmul x86_fp80 %35, %result.1.lcssa
  br label %37

; <label>:37                                      ; preds = %0, %._crit_edge
  %.0 = phi x86_fp80 [ %36, %._crit_edge ], [ 0xK00000000000000000000, %0 ]
  ret x86_fp80 %.0
}

; Function Attrs: norecurse nounwind readnone uwtable
define i64 @_Z10pack754_32e(x86_fp80 %f) #2 {
  %1 = fcmp oeq x86_fp80 %f, 0xK00000000000000000000
  br i1 %1, label %_Z7pack754ejj.exit, label %2

; <label>:2                                       ; preds = %0
  %3 = fcmp olt x86_fp80 %f, 0xK00000000000000000000
  %4 = fsub x86_fp80 0xK80000000000000000000, %f
  %sign.0.i = zext i1 %3 to i64
  %fnorm.0.i = select i1 %3, x86_fp80 %4, x86_fp80 %f
  %5 = fcmp ult x86_fp80 %fnorm.0.i, 0xK40008000000000000000
  br i1 %5, label %.preheader.i, label %.lr.ph7.i.preheader

.lr.ph7.i.preheader:                              ; preds = %2
  br label %.lr.ph7.i

.preheader.i.loopexit:                            ; preds = %.lr.ph7.i
  %.lcssa18 = phi i32 [ %8, %.lr.ph7.i ]
  %.lcssa17 = phi x86_fp80 [ %7, %.lr.ph7.i ]
  br label %.preheader.i

.preheader.i:                                     ; preds = %.preheader.i.loopexit, %2
  %fnorm.1.lcssa.i = phi x86_fp80 [ %fnorm.0.i, %2 ], [ %.lcssa17, %.preheader.i.loopexit ]
  %shift.0.lcssa.i = phi i32 [ 0, %2 ], [ %.lcssa18, %.preheader.i.loopexit ]
  %6 = fcmp olt x86_fp80 %fnorm.1.lcssa.i, 0xK3FFF8000000000000000
  br i1 %6, label %.lr.ph.i.preheader, label %._crit_edge.i

.lr.ph.i.preheader:                               ; preds = %.preheader.i
  br label %.lr.ph.i

.lr.ph7.i:                                        ; preds = %.lr.ph7.i.preheader, %.lr.ph7.i
  %fnorm.15.i = phi x86_fp80 [ %7, %.lr.ph7.i ], [ %fnorm.0.i, %.lr.ph7.i.preheader ]
  %shift.04.i = phi i32 [ %8, %.lr.ph7.i ], [ 0, %.lr.ph7.i.preheader ]
  %7 = fmul x86_fp80 %fnorm.15.i, 0xK3FFE8000000000000000
  %8 = add nuw nsw i32 %shift.04.i, 1
  %9 = fcmp ult x86_fp80 %7, 0xK40008000000000000000
  br i1 %9, label %.preheader.i.loopexit, label %.lr.ph7.i

.lr.ph.i:                                         ; preds = %.lr.ph.i.preheader, %.lr.ph.i
  %fnorm.22.i = phi x86_fp80 [ %10, %.lr.ph.i ], [ %fnorm.1.lcssa.i, %.lr.ph.i.preheader ]
  %shift.11.i = phi i32 [ %11, %.lr.ph.i ], [ %shift.0.lcssa.i, %.lr.ph.i.preheader ]
  %10 = fmul x86_fp80 %fnorm.22.i, 0xK40008000000000000000
  %11 = add nsw i32 %shift.11.i, -1
  %12 = fcmp olt x86_fp80 %10, 0xK3FFF8000000000000000
  br i1 %12, label %.lr.ph.i, label %._crit_edge.i.loopexit

._crit_edge.i.loopexit:                           ; preds = %.lr.ph.i
  %.lcssa16 = phi i32 [ %11, %.lr.ph.i ]
  %.lcssa = phi x86_fp80 [ %10, %.lr.ph.i ]
  br label %._crit_edge.i

._crit_edge.i:                                    ; preds = %._crit_edge.i.loopexit, %.preheader.i
  %fnorm.2.lcssa.i = phi x86_fp80 [ %fnorm.1.lcssa.i, %.preheader.i ], [ %.lcssa, %._crit_edge.i.loopexit ]
  %shift.1.lcssa.i = phi i32 [ %shift.0.lcssa.i, %.preheader.i ], [ %.lcssa16, %._crit_edge.i.loopexit ]
  %13 = fadd x86_fp80 %fnorm.2.lcssa.i, 0xKBFFF8000000000000000
  %14 = fmul x86_fp80 %13, 0xK40168000000000000000
  %15 = fptosi x86_fp80 %14 to i64
  %16 = add nsw i32 %shift.1.lcssa.i, 127
  %17 = sext i32 %16 to i64
  %18 = shl nuw nsw i64 %sign.0.i, 31
  %19 = shl nsw i64 %17, 23
  %20 = or i64 %15, %18
  %21 = or i64 %20, %19
  br label %_Z7pack754ejj.exit

_Z7pack754ejj.exit:                               ; preds = %0, %._crit_edge.i
  %.0.i = phi i64 [ %21, %._crit_edge.i ], [ 0, %0 ]
  ret i64 %.0.i
}

; Function Attrs: norecurse nounwind readnone uwtable
define i64 @_Z10pack754_64e(x86_fp80 %f) #2 {
  %1 = fcmp oeq x86_fp80 %f, 0xK00000000000000000000
  br i1 %1, label %_Z7pack754ejj.exit, label %2

; <label>:2                                       ; preds = %0
  %3 = fcmp olt x86_fp80 %f, 0xK00000000000000000000
  %4 = fsub x86_fp80 0xK80000000000000000000, %f
  %sign.0.i = zext i1 %3 to i64
  %fnorm.0.i = select i1 %3, x86_fp80 %4, x86_fp80 %f
  %5 = fcmp ult x86_fp80 %fnorm.0.i, 0xK40008000000000000000
  br i1 %5, label %.preheader.i, label %.lr.ph7.i.preheader

.lr.ph7.i.preheader:                              ; preds = %2
  br label %.lr.ph7.i

.preheader.i.loopexit:                            ; preds = %.lr.ph7.i
  %.lcssa18 = phi i32 [ %8, %.lr.ph7.i ]
  %.lcssa17 = phi x86_fp80 [ %7, %.lr.ph7.i ]
  br label %.preheader.i

.preheader.i:                                     ; preds = %.preheader.i.loopexit, %2
  %fnorm.1.lcssa.i = phi x86_fp80 [ %fnorm.0.i, %2 ], [ %.lcssa17, %.preheader.i.loopexit ]
  %shift.0.lcssa.i = phi i32 [ 0, %2 ], [ %.lcssa18, %.preheader.i.loopexit ]
  %6 = fcmp olt x86_fp80 %fnorm.1.lcssa.i, 0xK3FFF8000000000000000
  br i1 %6, label %.lr.ph.i.preheader, label %._crit_edge.i

.lr.ph.i.preheader:                               ; preds = %.preheader.i
  br label %.lr.ph.i

.lr.ph7.i:                                        ; preds = %.lr.ph7.i.preheader, %.lr.ph7.i
  %fnorm.15.i = phi x86_fp80 [ %7, %.lr.ph7.i ], [ %fnorm.0.i, %.lr.ph7.i.preheader ]
  %shift.04.i = phi i32 [ %8, %.lr.ph7.i ], [ 0, %.lr.ph7.i.preheader ]
  %7 = fmul x86_fp80 %fnorm.15.i, 0xK3FFE8000000000000000
  %8 = add nuw nsw i32 %shift.04.i, 1
  %9 = fcmp ult x86_fp80 %7, 0xK40008000000000000000
  br i1 %9, label %.preheader.i.loopexit, label %.lr.ph7.i

.lr.ph.i:                                         ; preds = %.lr.ph.i.preheader, %.lr.ph.i
  %fnorm.22.i = phi x86_fp80 [ %10, %.lr.ph.i ], [ %fnorm.1.lcssa.i, %.lr.ph.i.preheader ]
  %shift.11.i = phi i32 [ %11, %.lr.ph.i ], [ %shift.0.lcssa.i, %.lr.ph.i.preheader ]
  %10 = fmul x86_fp80 %fnorm.22.i, 0xK40008000000000000000
  %11 = add nsw i32 %shift.11.i, -1
  %12 = fcmp olt x86_fp80 %10, 0xK3FFF8000000000000000
  br i1 %12, label %.lr.ph.i, label %._crit_edge.i.loopexit

._crit_edge.i.loopexit:                           ; preds = %.lr.ph.i
  %.lcssa16 = phi i32 [ %11, %.lr.ph.i ]
  %.lcssa = phi x86_fp80 [ %10, %.lr.ph.i ]
  br label %._crit_edge.i

._crit_edge.i:                                    ; preds = %._crit_edge.i.loopexit, %.preheader.i
  %fnorm.2.lcssa.i = phi x86_fp80 [ %fnorm.1.lcssa.i, %.preheader.i ], [ %.lcssa, %._crit_edge.i.loopexit ]
  %shift.1.lcssa.i = phi i32 [ %shift.0.lcssa.i, %.preheader.i ], [ %.lcssa16, %._crit_edge.i.loopexit ]
  %13 = fadd x86_fp80 %fnorm.2.lcssa.i, 0xKBFFF8000000000000000
  %14 = fmul x86_fp80 %13, 0xK40338000000000000000
  %15 = fptosi x86_fp80 %14 to i64
  %16 = add nsw i32 %shift.1.lcssa.i, 1023
  %17 = zext i32 %16 to i64
  %18 = shl nuw i64 %sign.0.i, 63
  %19 = shl i64 %17, 52
  %20 = or i64 %15, %18
  %21 = or i64 %20, %19
  br label %_Z7pack754ejj.exit

_Z7pack754ejj.exit:                               ; preds = %0, %._crit_edge.i
  %.0.i = phi i64 [ %21, %._crit_edge.i ], [ 0, %0 ]
  ret i64 %.0.i
}

; Function Attrs: norecurse nounwind readnone uwtable
define x86_fp80 @_Z12unpack754_32m(i64 %i) #2 {
  %1 = icmp eq i64 %i, 0
  br i1 %1, label %_Z9unpack754mjj.exit, label %2

; <label>:2                                       ; preds = %0
  %3 = and i64 %i, 8388607
  %4 = uitofp i64 %3 to x86_fp80
  %5 = fmul x86_fp80 %4, 0xK3FE88000000000000000
  %6 = fadd x86_fp80 %5, 0xK3FFF8000000000000000
  %7 = lshr i64 %i, 23
  %8 = and i64 %7, 255
  %9 = add nsw i64 %8, -127
  %10 = icmp ugt i64 %8, 127
  br i1 %10, label %.lr.ph6.i.preheader, label %.preheader.i

.lr.ph6.i.preheader:                              ; preds = %2
  %11 = lshr i64 %i, 23
  %12 = and i64 %11, 255
  %13 = add nuw nsw i64 %11, 1
  %14 = add nsw i64 %12, -128
  %xtraiter = and i64 %13, 7
  %lcmp.mod = icmp eq i64 %xtraiter, 0
  br i1 %lcmp.mod, label %.lr.ph6.i.preheader.split, label %.lr.ph6.i.prol.preheader

.lr.ph6.i.prol.preheader:                         ; preds = %.lr.ph6.i.preheader
  br label %.lr.ph6.i.prol

.lr.ph6.i.prol:                                   ; preds = %.lr.ph6.i.prol.preheader, %.lr.ph6.i.prol
  %result.04.i.prol = phi x86_fp80 [ %15, %.lr.ph6.i.prol ], [ %6, %.lr.ph6.i.prol.preheader ]
  %shift.03.i.prol = phi i64 [ %16, %.lr.ph6.i.prol ], [ %9, %.lr.ph6.i.prol.preheader ]
  %prol.iter = phi i64 [ %prol.iter.sub, %.lr.ph6.i.prol ], [ %xtraiter, %.lr.ph6.i.prol.preheader ]
  %15 = fmul x86_fp80 %result.04.i.prol, 0xK40008000000000000000
  %16 = add nsw i64 %shift.03.i.prol, -1
  %prol.iter.sub = add i64 %prol.iter, -1
  %prol.iter.cmp = icmp eq i64 %prol.iter.sub, 0
  br i1 %prol.iter.cmp, label %.lr.ph6.i.preheader.split.loopexit, label %.lr.ph6.i.prol, !llvm.loop !2

.lr.ph6.i.preheader.split.loopexit:               ; preds = %.lr.ph6.i.prol
  %.lcssa14 = phi i64 [ %16, %.lr.ph6.i.prol ]
  %.lcssa13 = phi x86_fp80 [ %15, %.lr.ph6.i.prol ]
  br label %.lr.ph6.i.preheader.split

.lr.ph6.i.preheader.split:                        ; preds = %.lr.ph6.i.preheader.split.loopexit, %.lr.ph6.i.preheader
  %result.04.i.unr = phi x86_fp80 [ %6, %.lr.ph6.i.preheader ], [ %.lcssa13, %.lr.ph6.i.preheader.split.loopexit ]
  %shift.03.i.unr = phi i64 [ %9, %.lr.ph6.i.preheader ], [ %.lcssa14, %.lr.ph6.i.preheader.split.loopexit ]
  %.lcssa.unr = phi x86_fp80 [ undef, %.lr.ph6.i.preheader ], [ %.lcssa13, %.lr.ph6.i.preheader.split.loopexit ]
  %17 = icmp ult i64 %14, 7
  br i1 %17, label %._crit_edge.i.loopexit, label %.lr.ph6.i.preheader.split.split

.lr.ph6.i.preheader.split.split:                  ; preds = %.lr.ph6.i.preheader.split
  br label %.lr.ph6.i

.preheader.i:                                     ; preds = %2
  %18 = icmp ult i64 %8, 127
  br i1 %18, label %.lr.ph.i.preheader, label %._crit_edge.i

.lr.ph.i.preheader:                               ; preds = %.preheader.i
  br label %.lr.ph.i

.lr.ph6.i:                                        ; preds = %.lr.ph6.i, %.lr.ph6.i.preheader.split.split
  %result.04.i = phi x86_fp80 [ %result.04.i.unr, %.lr.ph6.i.preheader.split.split ], [ %27, %.lr.ph6.i ]
  %shift.03.i = phi i64 [ %shift.03.i.unr, %.lr.ph6.i.preheader.split.split ], [ %28, %.lr.ph6.i ]
  %19 = fmul x86_fp80 %result.04.i, 0xK40008000000000000000
  %20 = fmul x86_fp80 %19, 0xK40008000000000000000
  %21 = fmul x86_fp80 %20, 0xK40008000000000000000
  %22 = fmul x86_fp80 %21, 0xK40008000000000000000
  %23 = fmul x86_fp80 %22, 0xK40008000000000000000
  %24 = fmul x86_fp80 %23, 0xK40008000000000000000
  %25 = fmul x86_fp80 %24, 0xK40008000000000000000
  %26 = add nsw i64 %shift.03.i, -7
  %27 = fmul x86_fp80 %25, 0xK40008000000000000000
  %28 = add nsw i64 %shift.03.i, -8
  %29 = icmp sgt i64 %26, 1
  br i1 %29, label %.lr.ph6.i, label %._crit_edge.i.loopexit.unr-lcssa

.lr.ph.i:                                         ; preds = %.lr.ph.i.preheader, %.lr.ph.i
  %result.12.i = phi x86_fp80 [ %30, %.lr.ph.i ], [ %6, %.lr.ph.i.preheader ]
  %shift.11.i = phi i64 [ %31, %.lr.ph.i ], [ %9, %.lr.ph.i.preheader ]
  %30 = fmul x86_fp80 %result.12.i, 0xK3FFE8000000000000000
  %31 = add nsw i64 %shift.11.i, 1
  %32 = icmp slt i64 %shift.11.i, -1
  br i1 %32, label %.lr.ph.i, label %._crit_edge.i.loopexit9

._crit_edge.i.loopexit.unr-lcssa:                 ; preds = %.lr.ph6.i
  %.lcssa11 = phi x86_fp80 [ %27, %.lr.ph6.i ]
  br label %._crit_edge.i.loopexit

._crit_edge.i.loopexit:                           ; preds = %.lr.ph6.i.preheader.split, %._crit_edge.i.loopexit.unr-lcssa
  %.lcssa = phi x86_fp80 [ %.lcssa.unr, %.lr.ph6.i.preheader.split ], [ %.lcssa11, %._crit_edge.i.loopexit.unr-lcssa ]
  br label %._crit_edge.i

._crit_edge.i.loopexit9:                          ; preds = %.lr.ph.i
  %.lcssa12 = phi x86_fp80 [ %30, %.lr.ph.i ]
  br label %._crit_edge.i

._crit_edge.i:                                    ; preds = %._crit_edge.i.loopexit9, %._crit_edge.i.loopexit, %.preheader.i
  %result.1.lcssa.i = phi x86_fp80 [ %6, %.preheader.i ], [ %.lcssa, %._crit_edge.i.loopexit ], [ %.lcssa12, %._crit_edge.i.loopexit9 ]
  %33 = trunc i64 %i to i32
  %34 = icmp slt i32 %33, 0
  %35 = select i1 %34, x86_fp80 0xKBFFF8000000000000000, x86_fp80 0xK3FFF8000000000000000
  %36 = fmul x86_fp80 %35, %result.1.lcssa.i
  br label %_Z9unpack754mjj.exit

_Z9unpack754mjj.exit:                             ; preds = %0, %._crit_edge.i
  %.0.i = phi x86_fp80 [ %36, %._crit_edge.i ], [ 0xK00000000000000000000, %0 ]
  ret x86_fp80 %.0.i
}

; Function Attrs: norecurse nounwind readnone uwtable
define x86_fp80 @_Z12unpack754_64m(i64 %i) #2 {
  %1 = icmp eq i64 %i, 0
  br i1 %1, label %_Z9unpack754mjj.exit, label %2

; <label>:2                                       ; preds = %0
  %3 = and i64 %i, 4503599627370495
  %4 = uitofp i64 %3 to x86_fp80
  %5 = fmul x86_fp80 %4, 0xK3FCB8000000000000000
  %6 = fadd x86_fp80 %5, 0xK3FFF8000000000000000
  %7 = lshr i64 %i, 52
  %8 = and i64 %7, 2047
  %9 = add nsw i64 %8, -1023
  %10 = icmp ugt i64 %8, 1023
  br i1 %10, label %.lr.ph6.i.preheader, label %.preheader.i

.lr.ph6.i.preheader:                              ; preds = %2
  %11 = lshr i64 %i, 52
  %12 = and i64 %11, 2047
  %13 = add nuw nsw i64 %11, 1
  %14 = add nsw i64 %12, -1024
  %xtraiter = and i64 %13, 7
  %lcmp.mod = icmp eq i64 %xtraiter, 0
  br i1 %lcmp.mod, label %.lr.ph6.i.preheader.split, label %.lr.ph6.i.prol.preheader

.lr.ph6.i.prol.preheader:                         ; preds = %.lr.ph6.i.preheader
  br label %.lr.ph6.i.prol

.lr.ph6.i.prol:                                   ; preds = %.lr.ph6.i.prol.preheader, %.lr.ph6.i.prol
  %result.04.i.prol = phi x86_fp80 [ %15, %.lr.ph6.i.prol ], [ %6, %.lr.ph6.i.prol.preheader ]
  %shift.03.i.prol = phi i64 [ %16, %.lr.ph6.i.prol ], [ %9, %.lr.ph6.i.prol.preheader ]
  %prol.iter = phi i64 [ %prol.iter.sub, %.lr.ph6.i.prol ], [ %xtraiter, %.lr.ph6.i.prol.preheader ]
  %15 = fmul x86_fp80 %result.04.i.prol, 0xK40008000000000000000
  %16 = add nsw i64 %shift.03.i.prol, -1
  %prol.iter.sub = add i64 %prol.iter, -1
  %prol.iter.cmp = icmp eq i64 %prol.iter.sub, 0
  br i1 %prol.iter.cmp, label %.lr.ph6.i.preheader.split.loopexit, label %.lr.ph6.i.prol, !llvm.loop !4

.lr.ph6.i.preheader.split.loopexit:               ; preds = %.lr.ph6.i.prol
  %.lcssa14 = phi i64 [ %16, %.lr.ph6.i.prol ]
  %.lcssa13 = phi x86_fp80 [ %15, %.lr.ph6.i.prol ]
  br label %.lr.ph6.i.preheader.split

.lr.ph6.i.preheader.split:                        ; preds = %.lr.ph6.i.preheader.split.loopexit, %.lr.ph6.i.preheader
  %result.04.i.unr = phi x86_fp80 [ %6, %.lr.ph6.i.preheader ], [ %.lcssa13, %.lr.ph6.i.preheader.split.loopexit ]
  %shift.03.i.unr = phi i64 [ %9, %.lr.ph6.i.preheader ], [ %.lcssa14, %.lr.ph6.i.preheader.split.loopexit ]
  %.lcssa.unr = phi x86_fp80 [ undef, %.lr.ph6.i.preheader ], [ %.lcssa13, %.lr.ph6.i.preheader.split.loopexit ]
  %17 = icmp ult i64 %14, 7
  br i1 %17, label %._crit_edge.i.loopexit, label %.lr.ph6.i.preheader.split.split

.lr.ph6.i.preheader.split.split:                  ; preds = %.lr.ph6.i.preheader.split
  br label %.lr.ph6.i

.preheader.i:                                     ; preds = %2
  %18 = icmp ult i64 %8, 1023
  br i1 %18, label %.lr.ph.i.preheader, label %._crit_edge.i

.lr.ph.i.preheader:                               ; preds = %.preheader.i
  br label %.lr.ph.i

.lr.ph6.i:                                        ; preds = %.lr.ph6.i, %.lr.ph6.i.preheader.split.split
  %result.04.i = phi x86_fp80 [ %result.04.i.unr, %.lr.ph6.i.preheader.split.split ], [ %27, %.lr.ph6.i ]
  %shift.03.i = phi i64 [ %shift.03.i.unr, %.lr.ph6.i.preheader.split.split ], [ %28, %.lr.ph6.i ]
  %19 = fmul x86_fp80 %result.04.i, 0xK40008000000000000000
  %20 = fmul x86_fp80 %19, 0xK40008000000000000000
  %21 = fmul x86_fp80 %20, 0xK40008000000000000000
  %22 = fmul x86_fp80 %21, 0xK40008000000000000000
  %23 = fmul x86_fp80 %22, 0xK40008000000000000000
  %24 = fmul x86_fp80 %23, 0xK40008000000000000000
  %25 = fmul x86_fp80 %24, 0xK40008000000000000000
  %26 = add nsw i64 %shift.03.i, -7
  %27 = fmul x86_fp80 %25, 0xK40008000000000000000
  %28 = add nsw i64 %shift.03.i, -8
  %29 = icmp sgt i64 %26, 1
  br i1 %29, label %.lr.ph6.i, label %._crit_edge.i.loopexit.unr-lcssa

.lr.ph.i:                                         ; preds = %.lr.ph.i.preheader, %.lr.ph.i
  %result.12.i = phi x86_fp80 [ %30, %.lr.ph.i ], [ %6, %.lr.ph.i.preheader ]
  %shift.11.i = phi i64 [ %31, %.lr.ph.i ], [ %9, %.lr.ph.i.preheader ]
  %30 = fmul x86_fp80 %result.12.i, 0xK3FFE8000000000000000
  %31 = add nsw i64 %shift.11.i, 1
  %32 = icmp slt i64 %shift.11.i, -1
  br i1 %32, label %.lr.ph.i, label %._crit_edge.i.loopexit9

._crit_edge.i.loopexit.unr-lcssa:                 ; preds = %.lr.ph6.i
  %.lcssa11 = phi x86_fp80 [ %27, %.lr.ph6.i ]
  br label %._crit_edge.i.loopexit

._crit_edge.i.loopexit:                           ; preds = %.lr.ph6.i.preheader.split, %._crit_edge.i.loopexit.unr-lcssa
  %.lcssa = phi x86_fp80 [ %.lcssa.unr, %.lr.ph6.i.preheader.split ], [ %.lcssa11, %._crit_edge.i.loopexit.unr-lcssa ]
  br label %._crit_edge.i

._crit_edge.i.loopexit9:                          ; preds = %.lr.ph.i
  %.lcssa12 = phi x86_fp80 [ %30, %.lr.ph.i ]
  br label %._crit_edge.i

._crit_edge.i:                                    ; preds = %._crit_edge.i.loopexit9, %._crit_edge.i.loopexit, %.preheader.i
  %result.1.lcssa.i = phi x86_fp80 [ %6, %.preheader.i ], [ %.lcssa, %._crit_edge.i.loopexit ], [ %.lcssa12, %._crit_edge.i.loopexit9 ]
  %33 = icmp slt i64 %i, 0
  %34 = select i1 %33, x86_fp80 0xKBFFF8000000000000000, x86_fp80 0xK3FFF8000000000000000
  %35 = fmul x86_fp80 %34, %result.1.lcssa.i
  br label %_Z9unpack754mjj.exit

_Z9unpack754mjj.exit:                             ; preds = %0, %._crit_edge.i
  %.0.i = phi x86_fp80 [ %35, %._crit_edge.i ], [ 0xK00000000000000000000, %0 ]
  ret x86_fp80 %.0.i
}

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_floating_point_Binary_32_64_convertor.cpp() #3 section ".text.startup" {
  tail call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* nonnull @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i64 0, i32 0), i8* nonnull @__dso_handle) #1
  ret void
}

attributes #0 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { norecurse nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.unroll.disable"}
!4 = distinct !{!4, !3}
