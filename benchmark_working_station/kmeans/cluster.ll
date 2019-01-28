; ModuleID = 'cluster.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define i32 @cluster(i32 %numObjects, i32 %numAttributes, float** %attributes, i32 %num_nclusters, float %threshold, float*** nocapture %cluster_centres) #0 !dbg !7 {
  tail call void @llvm.dbg.value(metadata i32 %numObjects, i64 0, metadata !15, metadata !28), !dbg !29
  tail call void @llvm.dbg.value(metadata i32 %numAttributes, i64 0, metadata !16, metadata !28), !dbg !30
  tail call void @llvm.dbg.value(metadata float** %attributes, i64 0, metadata !17, metadata !28), !dbg !31
  tail call void @llvm.dbg.value(metadata i32 %num_nclusters, i64 0, metadata !18, metadata !28), !dbg !32
  tail call void @llvm.dbg.value(metadata float %threshold, i64 0, metadata !19, metadata !28), !dbg !33
  tail call void @llvm.dbg.value(metadata float*** %cluster_centres, i64 0, metadata !20, metadata !28), !dbg !34
  %1 = sext i32 %numObjects to i64, !dbg !35
  %2 = shl nsw i64 %1, 2, !dbg !36
  %3 = tail call noalias i8* @malloc(i64 %2) #4, !dbg !37
  %4 = bitcast i8* %3 to i32*, !dbg !38
  tail call void @llvm.dbg.value(metadata i32* %4, i64 0, metadata !22, metadata !28), !dbg !39
  tail call void @llvm.dbg.value(metadata i32 %num_nclusters, i64 0, metadata !21, metadata !28), !dbg !40
  tail call void @srand(i32 7) #4, !dbg !41
  %5 = tail call float** @kmeans_clustering(float** %attributes, i32 %numAttributes, i32 %numObjects, i32 %num_nclusters, float %threshold, i32* %4) #4, !dbg !42
  tail call void @llvm.dbg.value(metadata float** %5, i64 0, metadata !23, metadata !28), !dbg !43
  %6 = load float**, float*** %cluster_centres, align 8, !dbg !44, !tbaa !46
  %7 = icmp eq float** %6, null, !dbg !44
  br i1 %7, label %13, label %8, !dbg !50

; <label>:8                                       ; preds = %0
  %9 = bitcast float** %6 to i8**, !dbg !51
  %10 = load i8*, i8** %9, align 8, !dbg !51, !tbaa !46
  tail call void @free(i8* %10) #4, !dbg !53
  %11 = bitcast float*** %cluster_centres to i8**, !dbg !54
  %12 = load i8*, i8** %11, align 8, !dbg !54, !tbaa !46
  tail call void @free(i8* %12) #4, !dbg !55
  br label %13, !dbg !56

; <label>:13                                      ; preds = %0, %8
  store float** %5, float*** %cluster_centres, align 8, !dbg !57, !tbaa !46
  tail call void @free(i8* %3) #4, !dbg !58
  ret i32 0, !dbg !59
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #1

; Function Attrs: nounwind
declare void @srand(i32) #1

declare float** @kmeans_clustering(float**, i32, i32, i32, float, i32*) #2

; Function Attrs: nounwind
declare void @free(i8*) #1

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #3

attributes #0 = { noinline nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone }
attributes #4 = { nobuiltin nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!24, !25, !26}
!llvm.ident = !{!27}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: true, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !6)
!1 = !DIFile(filename: "cluster.c", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!6 = !{!7}
!7 = distinct !DISubprogram(name: "cluster", scope: !1, file: !1, line: 77, type: !8, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: true, variables: !14)
!8 = !DISubroutineType(types: !9)
!9 = !{!5, !5, !5, !10, !5, !12, !13}
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIBasicType(name: "float", size: 32, align: 32, encoding: DW_ATE_float)
!13 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!14 = !{!15, !16, !17, !18, !19, !20, !21, !22, !23}
!15 = !DILocalVariable(name: "numObjects", arg: 1, scope: !7, file: !1, line: 77, type: !5)
!16 = !DILocalVariable(name: "numAttributes", arg: 2, scope: !7, file: !1, line: 78, type: !5)
!17 = !DILocalVariable(name: "attributes", arg: 3, scope: !7, file: !1, line: 79, type: !10)
!18 = !DILocalVariable(name: "num_nclusters", arg: 4, scope: !7, file: !1, line: 80, type: !5)
!19 = !DILocalVariable(name: "threshold", arg: 5, scope: !7, file: !1, line: 81, type: !12)
!20 = !DILocalVariable(name: "cluster_centres", arg: 6, scope: !7, file: !1, line: 82, type: !13)
!21 = !DILocalVariable(name: "nclusters", scope: !7, file: !1, line: 86, type: !5)
!22 = !DILocalVariable(name: "membership", scope: !7, file: !1, line: 87, type: !4)
!23 = !DILocalVariable(name: "tmp_cluster_centres", scope: !7, file: !1, line: 88, type: !10)
!24 = !{i32 2, !"Dwarf Version", i32 4}
!25 = !{i32 2, !"Debug Info Version", i32 3}
!26 = !{i32 1, !"PIC Level", i32 2}
!27 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!28 = !DIExpression()
!29 = !DILocation(line: 77, column: 22, scope: !7)
!30 = !DILocation(line: 78, column: 22, scope: !7)
!31 = !DILocation(line: 79, column: 22, scope: !7)
!32 = !DILocation(line: 80, column: 22, scope: !7)
!33 = !DILocation(line: 81, column: 22, scope: !7)
!34 = !DILocation(line: 82, column: 22, scope: !7)
!35 = !DILocation(line: 90, column: 32, scope: !7)
!36 = !DILocation(line: 90, column: 43, scope: !7)
!37 = !DILocation(line: 90, column: 25, scope: !7)
!38 = !DILocation(line: 90, column: 18, scope: !7)
!39 = !DILocation(line: 87, column: 13, scope: !7)
!40 = !DILocation(line: 86, column: 13, scope: !7)
!41 = !DILocation(line: 94, column: 5, scope: !7)
!42 = !DILocation(line: 96, column: 27, scope: !7)
!43 = !DILocation(line: 88, column: 13, scope: !7)
!44 = !DILocation(line: 103, column: 9, scope: !45)
!45 = distinct !DILexicalBlock(scope: !7, file: !1, line: 103, column: 9)
!46 = !{!47, !47, i64 0}
!47 = !{!"any pointer", !48, i64 0}
!48 = !{!"omnipotent char", !49, i64 0}
!49 = !{!"Simple C/C++ TBAA"}
!50 = !DILocation(line: 103, column: 9, scope: !7)
!51 = !DILocation(line: 104, column: 8, scope: !52)
!52 = distinct !DILexicalBlock(scope: !45, file: !1, line: 103, column: 27)
!53 = !DILocation(line: 104, column: 3, scope: !52)
!54 = !DILocation(line: 105, column: 14, scope: !52)
!55 = !DILocation(line: 105, column: 9, scope: !52)
!56 = !DILocation(line: 106, column: 2, scope: !52)
!57 = !DILocation(line: 107, column: 19, scope: !7)
!58 = !DILocation(line: 110, column: 5, scope: !7)
!59 = !DILocation(line: 112, column: 5, scope: !7)
