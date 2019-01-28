; ModuleID = 'instrument.cpp'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }
%"class.std::basic_ostream" = type { i32 (...)**, %"class.std::basic_ios" }
%"class.std::basic_ios" = type { %"class.std::ios_base", %"class.std::basic_ostream"*, i8, i8, %"class.std::basic_streambuf"*, %"class.std::ctype"*, %"class.std::num_put"*, %"class.std::num_get"* }
%"class.std::ios_base" = type { i32 (...)**, i64, i64, i32, i32, i32, %"struct.std::ios_base::_Callback_list"*, %"struct.std::ios_base::_Words", [8 x %"struct.std::ios_base::_Words"], i32, %"struct.std::ios_base::_Words"*, %"class.std::locale" }
%"struct.std::ios_base::_Callback_list" = type { %"struct.std::ios_base::_Callback_list"*, void (i32, %"class.std::ios_base"*, i32)*, i32, i32 }
%"struct.std::ios_base::_Words" = type { i8*, i64 }
%"class.std::locale" = type { %"class.std::locale::_Impl"* }
%"class.std::locale::_Impl" = type { i32, %"class.std::locale::facet"**, i64, %"class.std::locale::facet"**, i8** }
%"class.std::locale::facet" = type <{ i32 (...)**, i32, [4 x i8] }>
%"class.std::basic_streambuf" = type { i32 (...)**, i8*, i8*, i8*, i8*, i8*, i8*, %"class.std::locale" }
%"class.std::ctype" = type <{ %"class.std::locale::facet.base", [4 x i8], %struct.__locale_struct*, i8, [7 x i8], i32*, i32*, i16*, i8, [256 x i8], [256 x i8], i8, [6 x i8] }>
%"class.std::locale::facet.base" = type <{ i32 (...)**, i32 }>
%struct.__locale_struct = type { [13 x %struct.__locale_data*], i16*, i32*, i32*, [13 x i8*] }
%struct.__locale_data = type opaque
%"class.std::num_put" = type { %"class.std::locale::facet.base", [4 x i8] }
%"class.std::num_get" = type { %"class.std::locale::facet.base", [4 x i8] }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external global i8
@w = global i64 1, align 8
@dynInstCounter = global i32 0, align 4
@_ZSt4cout = external global %"class.std::basic_ostream", align 8
@.str = private unnamed_addr constant [51 x i8] c"stepping into the -intFaultInjection- function ...\00", align 1
@.str.1 = private unnamed_addr constant [54 x i8] c"stepping into the -doubleFaultInjection- function ...\00", align 1
@.str.2 = private unnamed_addr constant [53 x i8] c"\0Athe current number of dyn instruction counter: %d \0A\00", align 1
@llvm.global_ctors = appending global [1 x { i32, void ()*, i8* }] [{ i32, void ()*, i8* } { i32 65535, void ()* @_GLOBAL__sub_I_instrument.cpp, i8* null }]

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) #0

declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) #0

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) #1

; Function Attrs: norecurse nounwind uwtable
define i32 @_Z22functionDynInstCounteriPc(i32 %counter, i8* nocapture readnone %OpcodeName) #2 {
  %1 = load i32, i32* @dynInstCounter, align 4, !tbaa !2
  %2 = add nsw i32 %1, 1
  store i32 %2, i32* @dynInstCounter, align 4, !tbaa !2
  ret i32 %2
}

; Function Attrs: uwtable
define i32 @_Z17intFaultInjectioniii(i32 %c_value, i32 %dynInstrID, i32 %bitPosition) #3 {
  %1 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(%"class.std::basic_ostream"* nonnull dereferenceable(272) @_ZSt4cout, i8* nonnull getelementptr inbounds ([51 x i8], [51 x i8]* @.str, i64 0, i64 0), i64 50)
  %2 = load i8*, i8** bitcast (%"class.std::basic_ostream"* @_ZSt4cout to i8**), align 8, !tbaa !6
  %3 = getelementptr i8, i8* %2, i64 -24
  %4 = bitcast i8* %3 to i64*
  %5 = load i64, i64* %4, align 8
  %6 = getelementptr inbounds i8, i8* bitcast (%"class.std::basic_ostream"* @_ZSt4cout to i8*), i64 %5
  %7 = getelementptr inbounds i8, i8* %6, i64 240
  %8 = bitcast i8* %7 to %"class.std::ctype"**
  %9 = load %"class.std::ctype"*, %"class.std::ctype"** %8, align 8, !tbaa !8
  %10 = icmp eq %"class.std::ctype"* %9, null
  br i1 %10, label %11, label %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit

; <label>:11                                      ; preds = %0
  tail call void @_ZSt16__throw_bad_castv() #6
  unreachable

_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit:    ; preds = %0
  %12 = getelementptr inbounds %"class.std::ctype", %"class.std::ctype"* %9, i64 0, i32 8
  %13 = load i8, i8* %12, align 8, !tbaa !12
  %14 = icmp eq i8 %13, 0
  br i1 %14, label %18, label %15

; <label>:15                                      ; preds = %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit
  %16 = getelementptr inbounds %"class.std::ctype", %"class.std::ctype"* %9, i64 0, i32 9, i64 10
  %17 = load i8, i8* %16, align 1, !tbaa !14
  br label %_ZNKSt5ctypeIcE5widenEc.exit

; <label>:18                                      ; preds = %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit
  tail call void @_ZNKSt5ctypeIcE13_M_widen_initEv(%"class.std::ctype"* nonnull %9)
  %19 = bitcast %"class.std::ctype"* %9 to i8 (%"class.std::ctype"*, i8)***
  %20 = load i8 (%"class.std::ctype"*, i8)**, i8 (%"class.std::ctype"*, i8)*** %19, align 8, !tbaa !6
  %21 = getelementptr inbounds i8 (%"class.std::ctype"*, i8)*, i8 (%"class.std::ctype"*, i8)** %20, i64 6
  %22 = load i8 (%"class.std::ctype"*, i8)*, i8 (%"class.std::ctype"*, i8)** %21, align 8
  %23 = tail call signext i8 %22(%"class.std::ctype"* nonnull %9, i8 signext 10)
  br label %_ZNKSt5ctypeIcE5widenEc.exit

_ZNKSt5ctypeIcE5widenEc.exit:                     ; preds = %15, %18
  %.0.i = phi i8 [ %17, %15 ], [ %23, %18 ]
  %24 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo3putEc(%"class.std::basic_ostream"* nonnull @_ZSt4cout, i8 signext %.0.i)
  %25 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo5flushEv(%"class.std::basic_ostream"* nonnull %24)
  store i64 1, i64* @w, align 8, !tbaa !15
  %26 = load i32, i32* @dynInstCounter, align 4, !tbaa !2
  %27 = sub nsw i32 %dynInstrID, %26
  %ispos = icmp sgt i32 %27, -1
  %neg = sub i32 0, %27
  %28 = select i1 %ispos, i32 %27, i32 %neg
  %29 = icmp slt i32 %28, 10
  br i1 %29, label %30, label %36

; <label>:30                                      ; preds = %_ZNKSt5ctypeIcE5widenEc.exit
  %31 = zext i32 %bitPosition to i64
  %32 = shl i64 1, %31
  store i64 %32, i64* @w, align 8, !tbaa !15
  %33 = zext i32 %c_value to i64
  %34 = xor i64 %32, %33
  %35 = trunc i64 %34 to i32
  br label %36

; <label>:36                                      ; preds = %_ZNKSt5ctypeIcE5widenEc.exit, %30
  %.0 = phi i32 [ %35, %30 ], [ %c_value, %_ZNKSt5ctypeIcE5widenEc.exit ]
  ret i32 %.0
}

; Function Attrs: uwtable
define double @_Z20doubleFaultInjectiondii(double %c_value, i32 %dynInstrID, i32 %bitPosition) #3 {
  %1 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(%"class.std::basic_ostream"* nonnull dereferenceable(272) @_ZSt4cout, i8* nonnull getelementptr inbounds ([54 x i8], [54 x i8]* @.str.1, i64 0, i64 0), i64 53)
  %2 = load i8*, i8** bitcast (%"class.std::basic_ostream"* @_ZSt4cout to i8**), align 8, !tbaa !6
  %3 = getelementptr i8, i8* %2, i64 -24
  %4 = bitcast i8* %3 to i64*
  %5 = load i64, i64* %4, align 8
  %6 = getelementptr inbounds i8, i8* bitcast (%"class.std::basic_ostream"* @_ZSt4cout to i8*), i64 %5
  %7 = getelementptr inbounds i8, i8* %6, i64 240
  %8 = bitcast i8* %7 to %"class.std::ctype"**
  %9 = load %"class.std::ctype"*, %"class.std::ctype"** %8, align 8, !tbaa !8
  %10 = icmp eq %"class.std::ctype"* %9, null
  br i1 %10, label %11, label %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit.i.i

; <label>:11                                      ; preds = %0
  tail call void @_ZSt16__throw_bad_castv() #6
  unreachable

_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit.i.i: ; preds = %0
  %12 = getelementptr inbounds %"class.std::ctype", %"class.std::ctype"* %9, i64 0, i32 8
  %13 = load i8, i8* %12, align 8, !tbaa !12
  %14 = icmp eq i8 %13, 0
  br i1 %14, label %18, label %15

; <label>:15                                      ; preds = %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit.i.i
  %16 = getelementptr inbounds %"class.std::ctype", %"class.std::ctype"* %9, i64 0, i32 9, i64 10
  %17 = load i8, i8* %16, align 1, !tbaa !14
  br label %_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit

; <label>:18                                      ; preds = %_ZSt13__check_facetISt5ctypeIcEERKT_PS3_.exit.i.i
  tail call void @_ZNKSt5ctypeIcE13_M_widen_initEv(%"class.std::ctype"* nonnull %9)
  %19 = bitcast %"class.std::ctype"* %9 to i8 (%"class.std::ctype"*, i8)***
  %20 = load i8 (%"class.std::ctype"*, i8)**, i8 (%"class.std::ctype"*, i8)*** %19, align 8, !tbaa !6
  %21 = getelementptr inbounds i8 (%"class.std::ctype"*, i8)*, i8 (%"class.std::ctype"*, i8)** %20, i64 6
  %22 = load i8 (%"class.std::ctype"*, i8)*, i8 (%"class.std::ctype"*, i8)** %21, align 8
  %23 = tail call signext i8 %22(%"class.std::ctype"* nonnull %9, i8 signext 10)
  br label %_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit

_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit: ; preds = %15, %18
  %.0.i.i.i = phi i8 [ %17, %15 ], [ %23, %18 ]
  %24 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo3putEc(%"class.std::basic_ostream"* nonnull @_ZSt4cout, i8 signext %.0.i.i.i)
  %25 = tail call dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo5flushEv(%"class.std::basic_ostream"* nonnull %24)
  %26 = load i32, i32* @dynInstCounter, align 4, !tbaa !2
  %27 = tail call i32 (i8*, ...) @printf(i8* nonnull getelementptr inbounds ([53 x i8], [53 x i8]* @.str.2, i64 0, i64 0), i32 %26)
  store i64 1, i64* @w, align 8, !tbaa !15
  %28 = load i32, i32* @dynInstCounter, align 4, !tbaa !2
  %29 = sub nsw i32 %dynInstrID, %28
  %ispos = icmp sgt i32 %29, -1
  %neg = sub i32 0, %29
  %30 = select i1 %ispos, i32 %29, i32 %neg
  %31 = icmp slt i32 %30, 10
  br i1 %31, label %32, label %41

; <label>:32                                      ; preds = %_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit
  %33 = zext i32 %bitPosition to i64
  %34 = shl i64 1, %33
  store i64 %34, i64* @w, align 8, !tbaa !15
  %35 = fpext double %c_value to x86_fp80
  %36 = tail call i64 @_Z10pack754_64e(x86_fp80 %35)
  %37 = load i64, i64* @w, align 8, !tbaa !15
  %38 = xor i64 %37, %36
  %39 = tail call x86_fp80 @_Z12unpack754_64m(i64 %38)
  %40 = fptrunc x86_fp80 %39 to double
  br label %41

; <label>:41                                      ; preds = %_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit, %32
  %.0 = phi double [ %40, %32 ], [ %c_value, %_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_.exit ]
  ret double %.0
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) #4

declare x86_fp80 @_Z12unpack754_64m(i64) #0

declare i64 @_Z10pack754_64e(x86_fp80) #0

declare dereferenceable(272) %"class.std::basic_ostream"* @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(%"class.std::basic_ostream"* dereferenceable(272), i8*, i64) #0

declare dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo3putEc(%"class.std::basic_ostream"*, i8 signext) #0

declare dereferenceable(272) %"class.std::basic_ostream"* @_ZNSo5flushEv(%"class.std::basic_ostream"*) #0

; Function Attrs: noreturn
declare void @_ZSt16__throw_bad_castv() #5

declare void @_ZNKSt5ctypeIcE13_M_widen_initEv(%"class.std::ctype"*) #0

; Function Attrs: uwtable
define internal void @_GLOBAL__sub_I_instrument.cpp() #3 section ".text.startup" {
  tail call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* nonnull @_ZStL8__ioinit)
  %1 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init", %"class.std::ios_base::Init"* @_ZStL8__ioinit, i64 0, i32 0), i8* nonnull @__dso_handle) #1
  ret void
}

attributes #0 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { norecurse nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { noreturn }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"PIC Level", i32 2}
!1 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!2 = !{!3, !3, i64 0}
!3 = !{!"int", !4, i64 0}
!4 = !{!"omnipotent char", !5, i64 0}
!5 = !{!"Simple C/C++ TBAA"}
!6 = !{!7, !7, i64 0}
!7 = !{!"vtable pointer", !5, i64 0}
!8 = !{!9, !10, i64 240}
!9 = !{!"_ZTSSt9basic_iosIcSt11char_traitsIcEE", !10, i64 216, !4, i64 224, !11, i64 225, !10, i64 232, !10, i64 240, !10, i64 248, !10, i64 256}
!10 = !{!"any pointer", !4, i64 0}
!11 = !{!"bool", !4, i64 0}
!12 = !{!13, !4, i64 56}
!13 = !{!"_ZTSSt5ctypeIcE", !10, i64 16, !11, i64 24, !10, i64 32, !10, i64 40, !10, i64 48, !4, i64 56, !4, i64 57, !4, i64 313, !4, i64 569}
!14 = !{!4, !4, i64 0}
!15 = !{!16, !16, i64 0}
!16 = !{!"long", !4, i64 0}
