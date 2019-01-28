; ModuleID = 'kmeans_clustering.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline norecurse nounwind readonly uwtable
define i32 @find_nearest_point(float* nocapture readonly %pt, i32 %nfeatures, float** nocapture readonly %pts, i32 %npts) #0 !dbg !10 {
  tail call void @llvm.dbg.value(metadata float* %pt, i64 0, metadata !14, metadata !57), !dbg !58
  tail call void @llvm.dbg.value(metadata i32 %nfeatures, i64 0, metadata !15, metadata !57), !dbg !59
  tail call void @llvm.dbg.value(metadata float** %pts, i64 0, metadata !16, metadata !57), !dbg !60
  tail call void @llvm.dbg.value(metadata i32 %npts, i64 0, metadata !17, metadata !57), !dbg !61
  tail call void @llvm.dbg.value(metadata float 0x47EFFFFFE0000000, i64 0, metadata !20, metadata !57), !dbg !62
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !19, metadata !57), !dbg !63
  %1 = icmp sgt i32 %npts, 0, !dbg !64
  br i1 %1, label %.lr.ph, label %._crit_edge, !dbg !66

.lr.ph:                                           ; preds = %0, %.lr.ph
  %indvars.iv = phi i64 [ %indvars.iv.next, %.lr.ph ], [ 0, %0 ]
  %index.03 = phi i32 [ %index.1, %.lr.ph ], [ undef, %0 ]
  %max_dist.02 = phi float [ %max_dist.1, %.lr.ph ], [ 0x47EFFFFFE0000000, %0 ]
  %2 = getelementptr inbounds float*, float** %pts, i64 %indvars.iv, !dbg !67
  %3 = load float*, float** %2, align 8, !dbg !67, !tbaa !68
  %4 = tail call float @euclid_dist_2(float* %pt, float* %3, i32 %nfeatures) #4, !dbg !72
  tail call void @llvm.dbg.value(metadata float %4, i64 0, metadata !21, metadata !57), !dbg !73
  %5 = fcmp olt float %4, %max_dist.02, !dbg !74
  tail call void @llvm.dbg.value(metadata float %4, i64 0, metadata !20, metadata !57), !dbg !62
  %max_dist.1 = select i1 %5, float %4, float %max_dist.02, !dbg !76
  %6 = trunc i64 %indvars.iv to i32, !dbg !76
  %index.1 = select i1 %5, i32 %6, i32 %index.03, !dbg !76
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1, !dbg !66
  %lftr.wideiv = trunc i64 %indvars.iv.next to i32, !dbg !66
  %exitcond = icmp eq i32 %lftr.wideiv, %npts, !dbg !66
  br i1 %exitcond, label %._crit_edge, label %.lr.ph, !dbg !66

._crit_edge:                                      ; preds = %.lr.ph, %0
  %index.0.lcssa = phi i32 [ undef, %0 ], [ %index.1, %.lr.ph ]
  ret i32 %index.0.lcssa, !dbg !77
}

; Function Attrs: noinline norecurse nounwind readonly uwtable
define float @euclid_dist_2(float* nocapture readonly %pt1, float* nocapture readonly %pt2, i32 %numdims) #0 !dbg !25 {
  tail call void @llvm.dbg.value(metadata float* %pt1, i64 0, metadata !29, metadata !57), !dbg !78
  tail call void @llvm.dbg.value(metadata float* %pt2, i64 0, metadata !30, metadata !57), !dbg !79
  tail call void @llvm.dbg.value(metadata i32 %numdims, i64 0, metadata !31, metadata !57), !dbg !80
  tail call void @llvm.dbg.value(metadata float 0.000000e+00, i64 0, metadata !33, metadata !57), !dbg !81
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !32, metadata !57), !dbg !82
  %1 = icmp sgt i32 %numdims, 0, !dbg !83
  br i1 %1, label %.lr.ph, label %._crit_edge, !dbg !87

.lr.ph:                                           ; preds = %0, %.lr.ph
  %indvars.iv = phi i64 [ %indvars.iv.next, %.lr.ph ], [ 0, %0 ]
  %ans.02 = phi float [ %8, %.lr.ph ], [ 0.000000e+00, %0 ]
  %2 = getelementptr inbounds float, float* %pt1, i64 %indvars.iv, !dbg !88
  %3 = load float, float* %2, align 4, !dbg !88, !tbaa !89
  %4 = getelementptr inbounds float, float* %pt2, i64 %indvars.iv, !dbg !91
  %5 = load float, float* %4, align 4, !dbg !91, !tbaa !89
  %6 = fsub float %3, %5, !dbg !92
  %7 = fmul float %6, %6, !dbg !93
  %8 = fadd float %ans.02, %7, !dbg !94
  tail call void @llvm.dbg.value(metadata float %8, i64 0, metadata !33, metadata !57), !dbg !81
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1, !dbg !87
  %lftr.wideiv = trunc i64 %indvars.iv.next to i32, !dbg !87
  %exitcond = icmp eq i32 %lftr.wideiv, %numdims, !dbg !87
  br i1 %exitcond, label %._crit_edge, label %.lr.ph, !dbg !87

._crit_edge:                                      ; preds = %.lr.ph, %0
  %ans.0.lcssa = phi float [ 0.000000e+00, %0 ], [ %8, %.lr.ph ]
  ret float %ans.0.lcssa, !dbg !95
}

; Function Attrs: noinline nounwind uwtable
define noalias float** @kmeans_clustering(float** nocapture readonly %feature, i32 %nfeatures, i32 %npoints, i32 %nclusters, float %threshold, i32* nocapture %membership) #1 !dbg !34 {
  tail call void @llvm.dbg.value(metadata float** %feature, i64 0, metadata !38, metadata !57), !dbg !96
  tail call void @llvm.dbg.value(metadata i32 %nfeatures, i64 0, metadata !39, metadata !57), !dbg !97
  tail call void @llvm.dbg.value(metadata i32 %npoints, i64 0, metadata !40, metadata !57), !dbg !98
  tail call void @llvm.dbg.value(metadata i32 %nclusters, i64 0, metadata !41, metadata !57), !dbg !99
  tail call void @llvm.dbg.value(metadata float %threshold, i64 0, metadata !42, metadata !57), !dbg !100
  tail call void @llvm.dbg.value(metadata i32* %membership, i64 0, metadata !43, metadata !57), !dbg !101
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !46, metadata !57), !dbg !102
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !48, metadata !57), !dbg !103
  %1 = sext i32 %nclusters to i64, !dbg !104
  %2 = shl nsw i64 %1, 3, !dbg !105
  %3 = tail call noalias i8* @malloc(i64 %2) #5, !dbg !106
  %4 = bitcast i8* %3 to float**, !dbg !107
  tail call void @llvm.dbg.value(metadata float** %4, i64 0, metadata !51, metadata !57), !dbg !108
  %5 = mul nsw i32 %nclusters, %nfeatures, !dbg !109
  %6 = sext i32 %5 to i64, !dbg !110
  %7 = shl nsw i64 %6, 2, !dbg !111
  %8 = tail call noalias i8* @malloc(i64 %7) #5, !dbg !112
  %9 = bitcast i8* %3 to i8**, !dbg !113
  store i8* %8, i8** %9, align 8, !dbg !113, !tbaa !68
  tail call void @llvm.dbg.value(metadata i32 1, i64 0, metadata !44, metadata !57), !dbg !114
  %10 = icmp sgt i32 %nclusters, 1, !dbg !115
  br i1 %10, label %.lr.ph26, label %.preheader5, !dbg !119

.lr.ph26:                                         ; preds = %0
  %11 = sext i32 %nfeatures to i64, !dbg !120
  br label %14, !dbg !119

.preheader5:                                      ; preds = %14, %0
  %12 = icmp sgt i32 %nclusters, 0, !dbg !121
  br i1 %12, label %.preheader4.lr.ph, label %.preheader3, !dbg !125

.preheader4.lr.ph:                                ; preds = %.preheader5
  %13 = icmp sgt i32 %nfeatures, 0, !dbg !126
  br label %.preheader4, !dbg !125

; <label>:14                                      ; preds = %14, %.lr.ph26
  %indvars.iv51 = phi i64 [ 1, %.lr.ph26 ], [ %indvars.iv.next52, %14 ]
  %15 = add nsw i64 %indvars.iv51, -1, !dbg !131
  %16 = getelementptr inbounds float*, float** %4, i64 %15, !dbg !132
  %17 = load float*, float** %16, align 8, !dbg !132, !tbaa !68
  %18 = getelementptr inbounds float, float* %17, i64 %11, !dbg !120
  %19 = getelementptr inbounds float*, float** %4, i64 %indvars.iv51, !dbg !133
  store float* %18, float** %19, align 8, !dbg !134, !tbaa !68
  %indvars.iv.next52 = add nuw nsw i64 %indvars.iv51, 1, !dbg !119
  %lftr.wideiv53 = trunc i64 %indvars.iv.next52 to i32, !dbg !119
  %exitcond54 = icmp eq i32 %lftr.wideiv53, %nclusters, !dbg !119
  br i1 %exitcond54, label %.preheader5, label %14, !dbg !119

.preheader4:                                      ; preds = %._crit_edge21, %.preheader4.lr.ph
  %indvars.iv47 = phi i64 [ 0, %.preheader4.lr.ph ], [ %indvars.iv.next48, %._crit_edge21 ]
  br i1 %13, label %.lr.ph20, label %._crit_edge21, !dbg !135

.lr.ph20:                                         ; preds = %.preheader4
  %20 = getelementptr inbounds float*, float** %feature, i64 %indvars.iv47, !dbg !136
  %21 = load float*, float** %20, align 8, !dbg !136
  %22 = getelementptr inbounds float*, float** %4, i64 %indvars.iv47, !dbg !137
  %23 = load float*, float** %22, align 8, !dbg !137
  br label %25, !dbg !135

.preheader3:                                      ; preds = %._crit_edge21, %.preheader5
  %24 = icmp sgt i32 %npoints, 0, !dbg !138
  br i1 %24, label %.lr.ph17, label %._crit_edge18, !dbg !142

; <label>:25                                      ; preds = %25, %.lr.ph20
  %indvars.iv43 = phi i64 [ 0, %.lr.ph20 ], [ %indvars.iv.next44, %25 ]
  %26 = getelementptr inbounds float, float* %21, i64 %indvars.iv43, !dbg !136
  %27 = bitcast float* %26 to i32*, !dbg !136
  %28 = load i32, i32* %27, align 4, !dbg !136, !tbaa !89
  %29 = getelementptr inbounds float, float* %23, i64 %indvars.iv43, !dbg !137
  %30 = bitcast float* %29 to i32*, !dbg !143
  store i32 %28, i32* %30, align 4, !dbg !143, !tbaa !89
  %indvars.iv.next44 = add nuw nsw i64 %indvars.iv43, 1, !dbg !135
  %lftr.wideiv45 = trunc i64 %indvars.iv.next44 to i32, !dbg !135
  %exitcond46 = icmp eq i32 %lftr.wideiv45, %nfeatures, !dbg !135
  br i1 %exitcond46, label %._crit_edge21, label %25, !dbg !135

._crit_edge21:                                    ; preds = %25, %.preheader4
  %indvars.iv.next48 = add nuw nsw i64 %indvars.iv47, 1, !dbg !125
  %lftr.wideiv49 = trunc i64 %indvars.iv.next48 to i32, !dbg !125
  %exitcond50 = icmp eq i32 %lftr.wideiv49, %nclusters, !dbg !125
  br i1 %exitcond50, label %.preheader3, label %.preheader4, !dbg !125

.lr.ph17:                                         ; preds = %.preheader3, %.lr.ph17
  %indvars.iv39 = phi i64 [ %indvars.iv.next40, %.lr.ph17 ], [ 0, %.preheader3 ]
  %31 = getelementptr inbounds i32, i32* %membership, i64 %indvars.iv39, !dbg !144
  store i32 -1, i32* %31, align 4, !dbg !145, !tbaa !146
  %indvars.iv.next40 = add nuw nsw i64 %indvars.iv39, 1, !dbg !142
  %lftr.wideiv41 = trunc i64 %indvars.iv.next40 to i32, !dbg !142
  %exitcond42 = icmp eq i32 %lftr.wideiv41, %npoints, !dbg !142
  br i1 %exitcond42, label %._crit_edge18, label %.lr.ph17, !dbg !142

._crit_edge18:                                    ; preds = %.lr.ph17, %.preheader3
  %32 = tail call noalias i8* @calloc(i64 %1, i64 4) #5, !dbg !148
  %33 = bitcast i8* %32 to i32*, !dbg !149
  tail call void @llvm.dbg.value(metadata i32* %33, i64 0, metadata !49, metadata !57), !dbg !150
  %34 = tail call noalias i8* @malloc(i64 %2) #5, !dbg !151
  %35 = bitcast i8* %34 to float**, !dbg !152
  tail call void @llvm.dbg.value(metadata float** %35, i64 0, metadata !52, metadata !57), !dbg !153
  %36 = tail call noalias i8* @calloc(i64 %6, i64 4) #5, !dbg !154
  %37 = bitcast i8* %34 to i8**, !dbg !155
  store i8* %36, i8** %37, align 8, !dbg !155, !tbaa !68
  tail call void @llvm.dbg.value(metadata i32 1, i64 0, metadata !44, metadata !57), !dbg !114
  %38 = icmp sgt i32 %nclusters, 1, !dbg !156
  br i1 %38, label %.lr.ph15, label %.preheader2, !dbg !160

.lr.ph15:                                         ; preds = %._crit_edge18
  %39 = sext i32 %nfeatures to i64, !dbg !161
  br label %43, !dbg !160

.preheader2:                                      ; preds = %43, %._crit_edge18
  %40 = icmp sgt i32 %nfeatures, 0, !dbg !162
  %41 = icmp sgt i32 %nclusters, 0, !dbg !170
  %42 = icmp sgt i32 %nfeatures, 0, !dbg !174
  br label %.backedge, !dbg !179

; <label>:43                                      ; preds = %43, %.lr.ph15
  %indvars.iv35 = phi i64 [ 1, %.lr.ph15 ], [ %indvars.iv.next36, %43 ]
  %44 = add nsw i64 %indvars.iv35, -1, !dbg !181
  %45 = getelementptr inbounds float*, float** %35, i64 %44, !dbg !182
  %46 = load float*, float** %45, align 8, !dbg !182, !tbaa !68
  %47 = getelementptr inbounds float, float* %46, i64 %39, !dbg !161
  %48 = getelementptr inbounds float*, float** %35, i64 %indvars.iv35, !dbg !183
  store float* %47, float** %48, align 8, !dbg !184, !tbaa !68
  %indvars.iv.next36 = add nuw nsw i64 %indvars.iv35, 1, !dbg !160
  %lftr.wideiv37 = trunc i64 %indvars.iv.next36 to i32, !dbg !160
  %exitcond38 = icmp eq i32 %lftr.wideiv37, %nclusters, !dbg !160
  br i1 %exitcond38, label %.preheader2, label %43, !dbg !160

.backedge:                                        ; preds = %._crit_edge8, %._crit_edge12, %.preheader2
  %delta.0 = phi float [ 0.000000e+00, %.preheader2 ], [ %delta.0., %._crit_edge12 ], [ 0.000000e+00, %._crit_edge8 ]
  %i.4 = phi i32 [ 0, %.preheader2 ], [ %72, %._crit_edge12 ], [ 0, %._crit_edge8 ]
  %49 = icmp slt i32 %i.4, %npoints, !dbg !179
  br i1 %49, label %50, label %.preheader1, !dbg !185

.preheader1:                                      ; preds = %.backedge
  br i1 %41, label %.preheader, label %._crit_edge8, !dbg !186

; <label>:50                                      ; preds = %.backedge
  %51 = sext i32 %i.4 to i64, !dbg !187
  %52 = getelementptr inbounds float*, float** %feature, i64 %51, !dbg !187
  %53 = load float*, float** %52, align 8, !dbg !187, !tbaa !68
  %54 = tail call i32 @find_nearest_point(float* %53, i32 %nfeatures, float** %4, i32 %nclusters) #4, !dbg !188
  tail call void @llvm.dbg.value(metadata i32 %54, i64 0, metadata !47, metadata !57), !dbg !189
  %55 = getelementptr inbounds i32, i32* %membership, i64 %51, !dbg !190
  %56 = load i32, i32* %55, align 4, !dbg !190, !tbaa !146
  %57 = icmp eq i32 %56, %54, !dbg !192
  %58 = fadd float %delta.0, 1.000000e+00, !dbg !193
  tail call void @llvm.dbg.value(metadata float %58, i64 0, metadata !50, metadata !57), !dbg !195
  %delta.0. = select i1 %57, float %delta.0, float %58, !dbg !196
  store i32 %54, i32* %55, align 4, !dbg !197, !tbaa !146
  %59 = sext i32 %54 to i64, !dbg !198
  %60 = getelementptr inbounds i32, i32* %33, i64 %59, !dbg !198
  %61 = load i32, i32* %60, align 4, !dbg !199, !tbaa !146
  %62 = add nsw i32 %61, 1, !dbg !199
  store i32 %62, i32* %60, align 4, !dbg !199, !tbaa !146
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !45, metadata !57), !dbg !200
  br i1 %40, label %.lr.ph11, label %._crit_edge12, !dbg !201

.lr.ph11:                                         ; preds = %50
  %63 = load float*, float** %52, align 8, !dbg !202
  %64 = getelementptr inbounds float*, float** %35, i64 %59, !dbg !203
  %65 = load float*, float** %64, align 8, !dbg !203
  br label %66, !dbg !201

; <label>:66                                      ; preds = %66, %.lr.ph11
  %indvars.iv31 = phi i64 [ 0, %.lr.ph11 ], [ %indvars.iv.next32, %66 ]
  %67 = getelementptr inbounds float, float* %63, i64 %indvars.iv31, !dbg !202
  %68 = load float, float* %67, align 4, !dbg !202, !tbaa !89
  %69 = getelementptr inbounds float, float* %65, i64 %indvars.iv31, !dbg !203
  %70 = load float, float* %69, align 4, !dbg !204, !tbaa !89
  %71 = fadd float %68, %70, !dbg !204
  store float %71, float* %69, align 4, !dbg !204, !tbaa !89
  %indvars.iv.next32 = add nuw nsw i64 %indvars.iv31, 1, !dbg !201
  %lftr.wideiv33 = trunc i64 %indvars.iv.next32 to i32, !dbg !201
  %exitcond34 = icmp eq i32 %lftr.wideiv33, %nfeatures, !dbg !201
  br i1 %exitcond34, label %._crit_edge12, label %66, !dbg !201

._crit_edge12:                                    ; preds = %66, %50
  %72 = add nsw i32 %i.4, 1, !dbg !205
  tail call void @llvm.dbg.value(metadata i32 %72, i64 0, metadata !44, metadata !57), !dbg !114
  br label %.backedge, !dbg !207

.preheader:                                       ; preds = %.preheader1, %._crit_edge
  %indvars.iv27 = phi i64 [ %indvars.iv.next28, %._crit_edge ], [ 0, %.preheader1 ]
  %73 = getelementptr inbounds i32, i32* %33, i64 %indvars.iv27, !dbg !208
  br i1 %42, label %.lr.ph, label %._crit_edge, !dbg !211

.lr.ph:                                           ; preds = %.preheader
  %74 = load i32, i32* %73, align 4, !dbg !208
  %75 = icmp sgt i32 %74, 0, !dbg !212
  %76 = getelementptr inbounds float*, float** %35, i64 %indvars.iv27, !dbg !213
  %77 = sitofp i32 %74 to float, !dbg !214
  %78 = getelementptr inbounds float*, float** %4, i64 %indvars.iv27, !dbg !215
  %79 = getelementptr inbounds float*, float** %35, i64 %indvars.iv27, !dbg !216
  %80 = load float*, float** %79, align 8, !dbg !216
  br label %81, !dbg !211

; <label>:81                                      ; preds = %89, %.lr.ph
  %indvars.iv = phi i64 [ 0, %.lr.ph ], [ %indvars.iv.next, %89 ]
  br i1 %75, label %82, label %89, !dbg !217

; <label>:82                                      ; preds = %81
  %83 = load float*, float** %76, align 8, !dbg !213, !tbaa !68
  %84 = getelementptr inbounds float, float* %83, i64 %indvars.iv, !dbg !213
  %85 = load float, float* %84, align 4, !dbg !213, !tbaa !89
  %86 = fdiv float %85, %77, !dbg !218
  %87 = load float*, float** %78, align 8, !dbg !215, !tbaa !68
  %88 = getelementptr inbounds float, float* %87, i64 %indvars.iv, !dbg !215
  store float %86, float* %88, align 4, !dbg !219, !tbaa !89
  br label %89, !dbg !215

; <label>:89                                      ; preds = %82, %81
  %90 = getelementptr inbounds float, float* %80, i64 %indvars.iv, !dbg !216
  store float 0.000000e+00, float* %90, align 4, !dbg !220, !tbaa !89
  %indvars.iv.next = add nuw nsw i64 %indvars.iv, 1, !dbg !211
  %lftr.wideiv = trunc i64 %indvars.iv.next to i32, !dbg !211
  %exitcond = icmp eq i32 %lftr.wideiv, %nfeatures, !dbg !211
  br i1 %exitcond, label %._crit_edge, label %81, !dbg !211

._crit_edge:                                      ; preds = %89, %.preheader
  store i32 0, i32* %73, align 4, !dbg !221, !tbaa !146
  %indvars.iv.next28 = add nuw nsw i64 %indvars.iv27, 1, !dbg !186
  %lftr.wideiv29 = trunc i64 %indvars.iv.next28 to i32, !dbg !186
  %exitcond30 = icmp eq i32 %lftr.wideiv29, %nclusters, !dbg !186
  br i1 %exitcond30, label %._crit_edge8, label %.preheader, !dbg !186

._crit_edge8:                                     ; preds = %._crit_edge, %.preheader1
  %91 = fcmp ogt float %delta.0, %threshold, !dbg !222
  br i1 %91, label %.backedge, label %92, !dbg !224

; <label>:92                                      ; preds = %._crit_edge8
  %93 = load i8*, i8** %37, align 8, !dbg !225, !tbaa !68
  tail call void @free(i8* %93) #5, !dbg !226
  tail call void @free(i8* %34) #5, !dbg !227
  tail call void @free(i8* %32) #5, !dbg !228
  ret float** %4, !dbg !229
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #2

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #3

attributes #0 = { noinline norecurse nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone }
attributes #4 = { nobuiltin }
attributes #5 = { nobuiltin nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!53, !54, !55}
!llvm.ident = !{!56}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: true, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !9)
!1 = !DIFile(filename: "kmeans_clustering.c", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!2 = !{}
!3 = !{!4, !5, !7}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DIBasicType(name: "float", size: 32, align: 32, encoding: DW_ATE_float)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !8, size: 64, align: 64)
!8 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !{!10, !25, !34}
!10 = distinct !DISubprogram(name: "find_nearest_point", scope: !1, file: !1, line: 77, type: !11, isLocal: false, isDefinition: true, scopeLine: 81, flags: DIFlagPrototyped, isOptimized: true, variables: !13)
!11 = !DISubroutineType(types: !12)
!12 = !{!8, !5, !8, !4, !8}
!13 = !{!14, !15, !16, !17, !18, !19, !20, !21}
!14 = !DILocalVariable(name: "pt", arg: 1, scope: !10, file: !1, line: 77, type: !5)
!15 = !DILocalVariable(name: "nfeatures", arg: 2, scope: !10, file: !1, line: 78, type: !8)
!16 = !DILocalVariable(name: "pts", arg: 3, scope: !10, file: !1, line: 79, type: !4)
!17 = !DILocalVariable(name: "npts", arg: 4, scope: !10, file: !1, line: 80, type: !8)
!18 = !DILocalVariable(name: "index", scope: !10, file: !1, line: 82, type: !8)
!19 = !DILocalVariable(name: "i", scope: !10, file: !1, line: 82, type: !8)
!20 = !DILocalVariable(name: "max_dist", scope: !10, file: !1, line: 83, type: !6)
!21 = !DILocalVariable(name: "dist", scope: !22, file: !1, line: 87, type: !6)
!22 = distinct !DILexicalBlock(scope: !23, file: !1, line: 86, column: 28)
!23 = distinct !DILexicalBlock(scope: !24, file: !1, line: 86, column: 5)
!24 = distinct !DILexicalBlock(scope: !10, file: !1, line: 86, column: 5)
!25 = distinct !DISubprogram(name: "euclid_dist_2", scope: !1, file: !1, line: 100, type: !26, isLocal: false, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: true, variables: !28)
!26 = !DISubroutineType(types: !27)
!27 = !{!6, !5, !5, !8}
!28 = !{!29, !30, !31, !32, !33}
!29 = !DILocalVariable(name: "pt1", arg: 1, scope: !25, file: !1, line: 100, type: !5)
!30 = !DILocalVariable(name: "pt2", arg: 2, scope: !25, file: !1, line: 101, type: !5)
!31 = !DILocalVariable(name: "numdims", arg: 3, scope: !25, file: !1, line: 102, type: !8)
!32 = !DILocalVariable(name: "i", scope: !25, file: !1, line: 104, type: !8)
!33 = !DILocalVariable(name: "ans", scope: !25, file: !1, line: 105, type: !6)
!34 = distinct !DISubprogram(name: "kmeans_clustering", scope: !1, file: !1, line: 115, type: !35, isLocal: false, isDefinition: true, scopeLine: 121, flags: DIFlagPrototyped, isOptimized: true, variables: !37)
!35 = !DISubroutineType(types: !36)
!36 = !{!4, !4, !8, !8, !8, !6, !7}
!37 = !{!38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52}
!38 = !DILocalVariable(name: "feature", arg: 1, scope: !34, file: !1, line: 115, type: !4)
!39 = !DILocalVariable(name: "nfeatures", arg: 2, scope: !34, file: !1, line: 116, type: !8)
!40 = !DILocalVariable(name: "npoints", arg: 3, scope: !34, file: !1, line: 117, type: !8)
!41 = !DILocalVariable(name: "nclusters", arg: 4, scope: !34, file: !1, line: 118, type: !8)
!42 = !DILocalVariable(name: "threshold", arg: 5, scope: !34, file: !1, line: 119, type: !6)
!43 = !DILocalVariable(name: "membership", arg: 6, scope: !34, file: !1, line: 120, type: !7)
!44 = !DILocalVariable(name: "i", scope: !34, file: !1, line: 123, type: !8)
!45 = !DILocalVariable(name: "j", scope: !34, file: !1, line: 123, type: !8)
!46 = !DILocalVariable(name: "n", scope: !34, file: !1, line: 123, type: !8)
!47 = !DILocalVariable(name: "index", scope: !34, file: !1, line: 123, type: !8)
!48 = !DILocalVariable(name: "loop", scope: !34, file: !1, line: 123, type: !8)
!49 = !DILocalVariable(name: "new_centers_len", scope: !34, file: !1, line: 124, type: !7)
!50 = !DILocalVariable(name: "delta", scope: !34, file: !1, line: 125, type: !6)
!51 = !DILocalVariable(name: "clusters", scope: !34, file: !1, line: 126, type: !4)
!52 = !DILocalVariable(name: "new_centers", scope: !34, file: !1, line: 127, type: !4)
!53 = !{i32 2, !"Dwarf Version", i32 4}
!54 = !{i32 2, !"Debug Info Version", i32 3}
!55 = !{i32 1, !"PIC Level", i32 2}
!56 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!57 = !DIExpression()
!58 = !DILocation(line: 77, column: 32, scope: !10)
!59 = !DILocation(line: 78, column: 32, scope: !10)
!60 = !DILocation(line: 79, column: 32, scope: !10)
!61 = !DILocation(line: 80, column: 32, scope: !10)
!62 = !DILocation(line: 83, column: 11, scope: !10)
!63 = !DILocation(line: 82, column: 16, scope: !10)
!64 = !DILocation(line: 86, column: 16, scope: !65)
!65 = !DILexicalBlockFile(scope: !23, file: !1, discriminator: 1)
!66 = !DILocation(line: 86, column: 5, scope: !65)
!67 = !DILocation(line: 88, column: 34, scope: !22)
!68 = !{!69, !69, i64 0}
!69 = !{!"any pointer", !70, i64 0}
!70 = !{!"omnipotent char", !71, i64 0}
!71 = !{!"Simple C/C++ TBAA"}
!72 = !DILocation(line: 88, column: 16, scope: !22)
!73 = !DILocation(line: 87, column: 15, scope: !22)
!74 = !DILocation(line: 89, column: 18, scope: !75)
!75 = distinct !DILexicalBlock(scope: !22, file: !1, line: 89, column: 13)
!76 = !DILocation(line: 89, column: 13, scope: !22)
!77 = !DILocation(line: 94, column: 5, scope: !10)
!78 = !DILocation(line: 100, column: 28, scope: !25)
!79 = !DILocation(line: 101, column: 28, scope: !25)
!80 = !DILocation(line: 102, column: 28, scope: !25)
!81 = !DILocation(line: 105, column: 11, scope: !25)
!82 = !DILocation(line: 104, column: 9, scope: !25)
!83 = !DILocation(line: 107, column: 16, scope: !84)
!84 = !DILexicalBlockFile(scope: !85, file: !1, discriminator: 1)
!85 = distinct !DILexicalBlock(scope: !86, file: !1, line: 107, column: 5)
!86 = distinct !DILexicalBlock(scope: !25, file: !1, line: 107, column: 5)
!87 = !DILocation(line: 107, column: 5, scope: !84)
!88 = !DILocation(line: 108, column: 17, scope: !85)
!89 = !{!90, !90, i64 0}
!90 = !{!"float", !70, i64 0}
!91 = !DILocation(line: 108, column: 24, scope: !85)
!92 = !DILocation(line: 108, column: 23, scope: !85)
!93 = !DILocation(line: 108, column: 32, scope: !85)
!94 = !DILocation(line: 108, column: 13, scope: !85)
!95 = !DILocation(line: 110, column: 5, scope: !25)
!96 = !DILocation(line: 115, column: 35, scope: !34)
!97 = !DILocation(line: 116, column: 35, scope: !34)
!98 = !DILocation(line: 117, column: 35, scope: !34)
!99 = !DILocation(line: 118, column: 35, scope: !34)
!100 = !DILocation(line: 119, column: 35, scope: !34)
!101 = !DILocation(line: 120, column: 35, scope: !34)
!102 = !DILocation(line: 123, column: 20, scope: !34)
!103 = !DILocation(line: 123, column: 32, scope: !34)
!104 = !DILocation(line: 131, column: 36, scope: !34)
!105 = !DILocation(line: 131, column: 46, scope: !34)
!106 = !DILocation(line: 131, column: 29, scope: !34)
!107 = !DILocation(line: 131, column: 19, scope: !34)
!108 = !DILocation(line: 126, column: 14, scope: !34)
!109 = !DILocation(line: 132, column: 46, scope: !34)
!110 = !DILocation(line: 132, column: 36, scope: !34)
!111 = !DILocation(line: 132, column: 58, scope: !34)
!112 = !DILocation(line: 132, column: 29, scope: !34)
!113 = !DILocation(line: 132, column: 17, scope: !34)
!114 = !DILocation(line: 123, column: 14, scope: !34)
!115 = !DILocation(line: 133, column: 16, scope: !116)
!116 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 1)
!117 = distinct !DILexicalBlock(scope: !118, file: !1, line: 133, column: 5)
!118 = distinct !DILexicalBlock(scope: !34, file: !1, line: 133, column: 5)
!119 = !DILocation(line: 133, column: 5, scope: !116)
!120 = !DILocation(line: 134, column: 37, scope: !117)
!121 = !DILocation(line: 137, column: 16, scope: !122)
!122 = !DILexicalBlockFile(scope: !123, file: !1, discriminator: 1)
!123 = distinct !DILexicalBlock(scope: !124, file: !1, line: 137, column: 5)
!124 = distinct !DILexicalBlock(scope: !34, file: !1, line: 137, column: 5)
!125 = !DILocation(line: 137, column: 5, scope: !122)
!126 = !DILocation(line: 139, column: 20, scope: !127)
!127 = !DILexicalBlockFile(scope: !128, file: !1, discriminator: 1)
!128 = distinct !DILexicalBlock(scope: !129, file: !1, line: 139, column: 9)
!129 = distinct !DILexicalBlock(scope: !130, file: !1, line: 139, column: 9)
!130 = distinct !DILexicalBlock(scope: !123, file: !1, line: 137, column: 33)
!131 = !DILocation(line: 134, column: 33, scope: !117)
!132 = !DILocation(line: 134, column: 23, scope: !117)
!133 = !DILocation(line: 134, column: 9, scope: !117)
!134 = !DILocation(line: 134, column: 21, scope: !117)
!135 = !DILocation(line: 139, column: 9, scope: !127)
!136 = !DILocation(line: 140, column: 30, scope: !128)
!137 = !DILocation(line: 140, column: 13, scope: !128)
!138 = !DILocation(line: 144, column: 16, scope: !139)
!139 = !DILexicalBlockFile(scope: !140, file: !1, discriminator: 1)
!140 = distinct !DILexicalBlock(scope: !141, file: !1, line: 144, column: 5)
!141 = distinct !DILexicalBlock(scope: !34, file: !1, line: 144, column: 5)
!142 = !DILocation(line: 144, column: 5, scope: !139)
!143 = !DILocation(line: 140, column: 28, scope: !128)
!144 = !DILocation(line: 145, column: 3, scope: !140)
!145 = !DILocation(line: 145, column: 17, scope: !140)
!146 = !{!147, !147, i64 0}
!147 = !{!"int", !70, i64 0}
!148 = !DILocation(line: 148, column: 30, scope: !34)
!149 = !DILocation(line: 148, column: 23, scope: !34)
!150 = !DILocation(line: 124, column: 14, scope: !34)
!151 = !DILocation(line: 150, column: 32, scope: !34)
!152 = !DILocation(line: 150, column: 22, scope: !34)
!153 = !DILocation(line: 127, column: 14, scope: !34)
!154 = !DILocation(line: 151, column: 32, scope: !34)
!155 = !DILocation(line: 151, column: 20, scope: !34)
!156 = !DILocation(line: 152, column: 16, scope: !157)
!157 = !DILexicalBlockFile(scope: !158, file: !1, discriminator: 1)
!158 = distinct !DILexicalBlock(scope: !159, file: !1, line: 152, column: 5)
!159 = distinct !DILexicalBlock(scope: !34, file: !1, line: 152, column: 5)
!160 = !DILocation(line: 152, column: 5, scope: !157)
!161 = !DILocation(line: 153, column: 43, scope: !158)
!162 = !DILocation(line: 171, column: 21, scope: !163)
!163 = !DILexicalBlockFile(scope: !164, file: !1, discriminator: 1)
!164 = distinct !DILexicalBlock(scope: !165, file: !1, line: 171, column: 10)
!165 = distinct !DILexicalBlock(scope: !166, file: !1, line: 171, column: 10)
!166 = distinct !DILexicalBlock(scope: !167, file: !1, line: 160, column: 35)
!167 = distinct !DILexicalBlock(scope: !168, file: !1, line: 160, column: 9)
!168 = distinct !DILexicalBlock(scope: !169, file: !1, line: 160, column: 9)
!169 = distinct !DILexicalBlock(scope: !34, file: !1, line: 156, column: 8)
!170 = !DILocation(line: 177, column: 20, scope: !171)
!171 = !DILexicalBlockFile(scope: !172, file: !1, discriminator: 1)
!172 = distinct !DILexicalBlock(scope: !173, file: !1, line: 177, column: 9)
!173 = distinct !DILexicalBlock(scope: !169, file: !1, line: 177, column: 9)
!174 = !DILocation(line: 178, column: 24, scope: !175)
!175 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 1)
!176 = distinct !DILexicalBlock(scope: !177, file: !1, line: 178, column: 13)
!177 = distinct !DILexicalBlock(scope: !178, file: !1, line: 178, column: 13)
!178 = distinct !DILexicalBlock(scope: !172, file: !1, line: 177, column: 37)
!179 = !DILocation(line: 160, column: 20, scope: !180)
!180 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!181 = !DILocation(line: 153, column: 39, scope: !158)
!182 = !DILocation(line: 153, column: 26, scope: !158)
!183 = !DILocation(line: 153, column: 9, scope: !158)
!184 = !DILocation(line: 153, column: 24, scope: !158)
!185 = !DILocation(line: 160, column: 9, scope: !180)
!186 = !DILocation(line: 177, column: 9, scope: !171)
!187 = !DILocation(line: 162, column: 37, scope: !166)
!188 = !DILocation(line: 162, column: 18, scope: !166)
!189 = !DILocation(line: 123, column: 25, scope: !34)
!190 = !DILocation(line: 164, column: 14, scope: !191)
!191 = distinct !DILexicalBlock(scope: !166, file: !1, line: 164, column: 14)
!192 = !DILocation(line: 164, column: 28, scope: !191)
!193 = !DILocation(line: 164, column: 44, scope: !194)
!194 = !DILexicalBlockFile(scope: !191, file: !1, discriminator: 1)
!195 = !DILocation(line: 125, column: 14, scope: !34)
!196 = !DILocation(line: 164, column: 14, scope: !166)
!197 = !DILocation(line: 167, column: 24, scope: !166)
!198 = !DILocation(line: 170, column: 10, scope: !166)
!199 = !DILocation(line: 170, column: 32, scope: !166)
!200 = !DILocation(line: 123, column: 17, scope: !34)
!201 = !DILocation(line: 171, column: 10, scope: !163)
!202 = !DILocation(line: 172, column: 30, scope: !164)
!203 = !DILocation(line: 172, column: 5, scope: !164)
!204 = !DILocation(line: 172, column: 27, scope: !164)
!205 = !DILocation(line: 160, column: 31, scope: !206)
!206 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 2)
!207 = !DILocation(line: 160, column: 9, scope: !206)
!208 = !DILocation(line: 179, column: 21, scope: !209)
!209 = distinct !DILexicalBlock(scope: !210, file: !1, line: 179, column: 21)
!210 = distinct !DILexicalBlock(scope: !176, file: !1, line: 178, column: 41)
!211 = !DILocation(line: 178, column: 13, scope: !175)
!212 = !DILocation(line: 179, column: 40, scope: !209)
!213 = !DILocation(line: 180, column: 23, scope: !209)
!214 = !DILocation(line: 180, column: 43, scope: !209)
!215 = !DILocation(line: 180, column: 6, scope: !209)
!216 = !DILocation(line: 181, column: 5, scope: !210)
!217 = !DILocation(line: 179, column: 21, scope: !210)
!218 = !DILocation(line: 180, column: 41, scope: !209)
!219 = !DILocation(line: 180, column: 21, scope: !209)
!220 = !DILocation(line: 181, column: 23, scope: !210)
!221 = !DILocation(line: 183, column: 23, scope: !178)
!222 = !DILocation(line: 187, column: 20, scope: !223)
!223 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 1)
!224 = !DILocation(line: 187, column: 5, scope: !223)
!225 = !DILocation(line: 190, column: 10, scope: !34)
!226 = !DILocation(line: 190, column: 5, scope: !34)
!227 = !DILocation(line: 191, column: 5, scope: !34)
!228 = !DILocation(line: 192, column: 5, scope: !34)
!229 = !DILocation(line: 194, column: 5, scope: !34)
