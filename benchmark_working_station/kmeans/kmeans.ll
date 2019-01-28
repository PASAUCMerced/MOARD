; ModuleID = 'kmeans.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [259 x i8] c"Usage: %s [switches] -i filename\0A       -i filename     :  file containing data to be clustered\0A       -b                 :input file is in binary format\0A       -k                 : number of clusters (default is 8) \0A       -t threshold    : threshold value\0A\00", align 1
@stderr = external global %struct._IO_FILE*, align 8
@.str.1 = private unnamed_addr constant [8 x i8] c"i:k:t:b\00", align 1
@optarg = external global i8*, align 8
@.str.2 = private unnamed_addr constant [5 x i8] c"0600\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"Error: no such file (%s)\0A\00", align 1
@.str.4 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c" \09\0A\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c" ,\09\0A\00", align 1
@.str.7 = private unnamed_addr constant [15 x i8] c"I/O completed\0A\00", align 1
@.str.8 = private unnamed_addr constant [23 x i8] c"number of Clusters %d\0A\00", align 1
@.str.9 = private unnamed_addr constant [26 x i8] c"number of Attributes %d\0A\0A\00", align 1
@.str.10 = private unnamed_addr constant [28 x i8] c"python refresh_fm_states.py\00", align 1

; Function Attrs: noinline noreturn nounwind uwtable
define void @usage(i8* %argv0) #0 !dbg !9 {
  tail call void @llvm.dbg.value(metadata i8* %argv0, i64 0, metadata !15, metadata !112), !dbg !113
  tail call void @llvm.dbg.value(metadata i8* getelementptr inbounds ([259 x i8], [259 x i8]* @.str, i32 0, i32 0), i64 0, metadata !16, metadata !112), !dbg !114
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !115, !tbaa !116
  %2 = tail call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %1, i8* getelementptr inbounds ([259 x i8], [259 x i8]* @.str, i64 0, i64 0), i8* %argv0) #8, !dbg !120
  tail call void @exit(i32 -1) #9, !dbg !121
  unreachable, !dbg !121
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.start(i64, i8* nocapture) #2

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #3

; Function Attrs: noreturn nounwind
declare void @exit(i32) #4

; Function Attrs: noinline nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #5 !dbg !17 {
  %cluster_centres = alloca float**, align 8
  %numAttributes = alloca i32, align 4
  %numObjects = alloca i32, align 4
  %line = alloca [1024 x i8], align 16
  tail call void @llvm.dbg.value(metadata i32 %argc, i64 0, metadata !23, metadata !112), !dbg !122
  tail call void @llvm.dbg.value(metadata i8** %argv, i64 0, metadata !24, metadata !112), !dbg !123
  tail call void @llvm.dbg.value(metadata i32 5, i64 0, metadata !26, metadata !112), !dbg !124
  tail call void @llvm.dbg.value(metadata i8* null, i64 0, metadata !27, metadata !112), !dbg !125
  %1 = bitcast float*** %cluster_centres to i8*, !dbg !126
  call void @llvm.lifetime.start(i64 8, i8* %1) #10, !dbg !126
  tail call void @llvm.dbg.value(metadata float** null, i64 0, metadata !30, metadata !112), !dbg !127
  store float** null, float*** %cluster_centres, align 8, !dbg !127, !tbaa !116
  %2 = bitcast i32* %numAttributes to i8*, !dbg !128
  call void @llvm.lifetime.start(i64 4, i8* %2) #10, !dbg !128
  %3 = bitcast i32* %numObjects to i8*, !dbg !129
  call void @llvm.lifetime.start(i64 4, i8* %3) #10, !dbg !129
  %4 = getelementptr inbounds [1024 x i8], [1024 x i8]* %line, i64 0, i64 0, !dbg !130
  call void @llvm.lifetime.start(i64 1024, i8* %4) #10, !dbg !130
  tail call void @llvm.dbg.declare(metadata [1024 x i8]* %line, metadata !35, metadata !112), !dbg !131
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !39, metadata !112), !dbg !132
  tail call void @llvm.dbg.value(metadata float 0x3F50624DE0000000, i64 0, metadata !41, metadata !112), !dbg !133
  br label %.outer6, !dbg !134

.outer6:                                          ; preds = %5, %0
  %isBinaryFile.0.ph = phi i32 [ 0, %0 ], [ 1, %5 ]
  %threshold.0.ph = phi float [ 0x3F50624DE0000000, %0 ], [ %threshold.0.ph8, %5 ]
  %filename.0.ph = phi i8* [ null, %0 ], [ %filename.0.ph12, %5 ]
  %nclusters.0.ph = phi i32 [ 5, %0 ], [ %nclusters.0, %5 ]
  br label %.outer7, !dbg !135

.outer7:                                          ; preds = %.outer6, %9
  %threshold.0.ph8 = phi float [ %threshold.0.ph, %.outer6 ], [ %12, %9 ]
  %filename.0.ph9 = phi i8* [ %filename.0.ph, %.outer6 ], [ %filename.0.ph12, %9 ]
  %nclusters.0.ph10 = phi i32 [ %nclusters.0.ph, %.outer6 ], [ %nclusters.0, %9 ]
  br label %.outer11, !dbg !135

.outer11:                                         ; preds = %.outer7, %7
  %filename.0.ph12 = phi i8* [ %filename.0.ph9, %.outer7 ], [ %8, %7 ]
  %nclusters.0.ph13 = phi i32 [ %nclusters.0.ph10, %.outer7 ], [ %nclusters.0, %7 ]
  br label %5, !dbg !135

; <label>:5                                       ; preds = %.outer11, %13
  %nclusters.0 = phi i32 [ %15, %13 ], [ %nclusters.0.ph13, %.outer11 ]
  %6 = tail call i32 @getopt(i32 %argc, i8** %argv, i8* nonnull getelementptr inbounds ([8 x i8], [8 x i8]* @.str.1, i64 0, i64 0)) #8, !dbg !135
  tail call void @llvm.dbg.value(metadata i32 %6, i64 0, metadata !25, metadata !112), !dbg !137
  switch i32 %6, label %18 [
    i32 -1, label %20
    i32 105, label %7
    i32 98, label %.outer6
    i32 116, label %9
    i32 107, label %13
    i32 63, label %16
  ], !dbg !138

; <label>:7                                       ; preds = %5
  %8 = load i8*, i8** @optarg, align 8, !dbg !139, !tbaa !116
  tail call void @llvm.dbg.value(metadata i8* %8, i64 0, metadata !27, metadata !112), !dbg !125
  br label %.outer11, !dbg !142

; <label>:9                                       ; preds = %5
  %10 = load i8*, i8** @optarg, align 8, !dbg !143, !tbaa !116
  %11 = tail call double @atof(i8* %10) #11, !dbg !144
  %12 = fptrunc double %11 to float, !dbg !144
  tail call void @llvm.dbg.value(metadata float %12, i64 0, metadata !41, metadata !112), !dbg !133
  br label %.outer7, !dbg !145

; <label>:13                                      ; preds = %5
  %14 = load i8*, i8** @optarg, align 8, !dbg !146, !tbaa !116
  %15 = tail call i32 @atoi(i8* %14) #11, !dbg !147
  tail call void @llvm.dbg.value(metadata i32 %15, i64 0, metadata !26, metadata !112), !dbg !124
  br label %5, !dbg !148

; <label>:16                                      ; preds = %5
  %17 = load i8*, i8** %argv, align 8, !dbg !149, !tbaa !116
  tail call void @usage(i8* %17) #12, !dbg !150
  unreachable

; <label>:18                                      ; preds = %5
  %19 = load i8*, i8** %argv, align 8, !dbg !151, !tbaa !116
  tail call void @usage(i8* %19) #12, !dbg !152
  unreachable

; <label>:20                                      ; preds = %5
  %21 = icmp eq i8* %filename.0.ph12, null, !dbg !153
  br i1 %21, label %22, label %24, !dbg !155

; <label>:22                                      ; preds = %20
  %23 = load i8*, i8** %argv, align 8, !dbg !156, !tbaa !116
  tail call void @usage(i8* %23) #12, !dbg !158
  unreachable

; <label>:24                                      ; preds = %20
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !34, metadata !112), !dbg !159
  store i32 0, i32* %numObjects, align 4, !dbg !160, !tbaa !161
  tail call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !33, metadata !112), !dbg !163
  store i32 0, i32* %numAttributes, align 4, !dbg !164, !tbaa !161
  %25 = icmp eq i32 %isBinaryFile.0.ph, 0, !dbg !165
  br i1 %25, label %73, label %26, !dbg !166

; <label>:26                                      ; preds = %24
  %27 = tail call i32 (i8*, i32, ...) @open(i8* nonnull %filename.0.ph12, i32 0, i8* nonnull getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i64 0, i64 0)) #8, !dbg !167
  tail call void @llvm.dbg.value(metadata i32 %27, i64 0, metadata !44, metadata !112), !dbg !169
  %28 = icmp eq i32 %27, -1, !dbg !170
  br i1 %28, label %29, label %32, !dbg !171

; <label>:29                                      ; preds = %26
  %30 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !172, !tbaa !116
  %31 = tail call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %30, i8* nonnull getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0), i8* nonnull %filename.0.ph12) #8, !dbg !174
  tail call void @exit(i32 1) #9, !dbg !175
  unreachable, !dbg !175

; <label>:32                                      ; preds = %26
  tail call void @llvm.dbg.value(metadata i32* %numObjects, i64 0, metadata !34, metadata !176), !dbg !159
  %33 = call i32 (i32, i32*, i64, ...) bitcast (i32 (...)* @read to i32 (i32, i32*, i64, ...)*)(i32 %27, i32* nonnull %numObjects, i64 4) #8, !dbg !177
  call void @llvm.dbg.value(metadata i32* %numAttributes, i64 0, metadata !33, metadata !176), !dbg !163
  %34 = call i32 (i32, i32*, i64, ...) bitcast (i32 (...)* @read to i32 (i32, i32*, i64, ...)*)(i32 %27, i32* nonnull %numAttributes, i64 4) #8, !dbg !178
  %35 = load i32, i32* %numObjects, align 4, !dbg !179, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %35, i64 0, metadata !34, metadata !112), !dbg !159
  %36 = load i32, i32* %numAttributes, align 4, !dbg !180, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %36, i64 0, metadata !33, metadata !112), !dbg !163
  %37 = mul nsw i32 %36, %35, !dbg !181
  %38 = sext i32 %37 to i64, !dbg !179
  %39 = shl nsw i64 %38, 2, !dbg !182
  %40 = call noalias i8* @malloc(i64 %39) #8, !dbg !183
  %41 = bitcast i8* %40 to float*, !dbg !184
  call void @llvm.dbg.value(metadata float* %41, i64 0, metadata !28, metadata !112), !dbg !185
  %42 = load i32, i32* %numObjects, align 4, !dbg !186, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %42, i64 0, metadata !34, metadata !112), !dbg !159
  %43 = sext i32 %42 to i64, !dbg !186
  %44 = shl nsw i64 %43, 3, !dbg !187
  %45 = call noalias i8* @malloc(i64 %44) #8, !dbg !188
  %46 = bitcast i8* %45 to float**, !dbg !189
  call void @llvm.dbg.value(metadata float** %46, i64 0, metadata !29, metadata !112), !dbg !190
  %47 = load i32, i32* %numObjects, align 4, !dbg !191, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %47, i64 0, metadata !34, metadata !112), !dbg !159
  %48 = load i32, i32* %numAttributes, align 4, !dbg !192, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %48, i64 0, metadata !33, metadata !112), !dbg !163
  %49 = mul nsw i32 %48, %47, !dbg !193
  %50 = sext i32 %49 to i64, !dbg !191
  %51 = shl nsw i64 %50, 2, !dbg !194
  %52 = call noalias i8* @malloc(i64 %51) #8, !dbg !195
  %53 = bitcast i8* %45 to i8**, !dbg !196
  store i8* %52, i8** %53, align 8, !dbg !196, !tbaa !116
  call void @llvm.dbg.value(metadata i32 1, i64 0, metadata !31, metadata !112), !dbg !197
  %54 = load i32, i32* %numObjects, align 4, !dbg !198, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %54, i64 0, metadata !34, metadata !112), !dbg !159
  %55 = icmp sgt i32 %54, 1, !dbg !202
  br i1 %55, label %.lr.ph38, label %._crit_edge39, !dbg !203

.lr.ph38:                                         ; preds = %32
  %56 = load i32, i32* %numAttributes, align 4, !dbg !204
  %57 = sext i32 %56 to i64, !dbg !205
  %58 = load i32, i32* %numObjects, align 4, !dbg !198
  %59 = sext i32 %58 to i64, !dbg !203
  br label %60, !dbg !203

; <label>:60                                      ; preds = %.lr.ph38, %60
  %indvars.iv59 = phi i64 [ 1, %.lr.ph38 ], [ %indvars.iv.next60, %60 ]
  %61 = add nsw i64 %indvars.iv59, -1, !dbg !206
  %62 = getelementptr inbounds float*, float** %46, i64 %61, !dbg !207
  %63 = load float*, float** %62, align 8, !dbg !207, !tbaa !116
  call void @llvm.dbg.value(metadata i32 %56, i64 0, metadata !33, metadata !112), !dbg !163
  %64 = getelementptr inbounds float, float* %63, i64 %57, !dbg !205
  %65 = getelementptr inbounds float*, float** %46, i64 %indvars.iv59, !dbg !208
  store float* %64, float** %65, align 8, !dbg !209, !tbaa !116
  %indvars.iv.next60 = add nuw nsw i64 %indvars.iv59, 1, !dbg !203
  call void @llvm.dbg.value(metadata i32 %58, i64 0, metadata !34, metadata !112), !dbg !159
  %66 = icmp slt i64 %indvars.iv.next60, %59, !dbg !202
  br i1 %66, label %60, label %._crit_edge39, !dbg !203

._crit_edge39:                                    ; preds = %60, %32
  %.lcssa = phi i32 [ %54, %32 ], [ %58, %60 ]
  %67 = load i32, i32* %numAttributes, align 4, !dbg !210, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %67, i64 0, metadata !33, metadata !112), !dbg !163
  %68 = mul nsw i32 %67, %.lcssa, !dbg !211
  %69 = sext i32 %68 to i64, !dbg !212
  %70 = shl nsw i64 %69, 2, !dbg !213
  %71 = call i32 (i32, float*, i64, ...) bitcast (i32 (...)* @read to i32 (i32, float*, i64, ...)*)(i32 %27, float* %41, i64 %70) #8, !dbg !214
  %72 = call i32 (i32, ...) bitcast (i32 (...)* @close to i32 (i32, ...)*)(i32 %27) #8, !dbg !215
  br label %150, !dbg !216

; <label>:73                                      ; preds = %24
  %74 = tail call %struct._IO_FILE* @fopen(i8* nonnull %filename.0.ph12, i8* nonnull getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i64 0, i64 0)) #8, !dbg !217
  tail call void @llvm.dbg.value(metadata %struct._IO_FILE* %74, i64 0, metadata !47, metadata !112), !dbg !219
  %75 = icmp eq %struct._IO_FILE* %74, null, !dbg !220
  br i1 %75, label %78, label %.preheader5, !dbg !221

.preheader5:                                      ; preds = %73
  %76 = call i8* @fgets(i8* %4, i32 1024, %struct._IO_FILE* nonnull %74) #8, !dbg !222
  %77 = icmp eq i8* %76, null, !dbg !224
  br i1 %77, label %._crit_edge35, label %.lr.ph34, !dbg !225

; <label>:78                                      ; preds = %73
  %79 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !226, !tbaa !116
  %80 = tail call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %79, i8* nonnull getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i64 0, i64 0), i8* nonnull %filename.0.ph12) #8, !dbg !228
  tail call void @exit(i32 1) #9, !dbg !229
  unreachable, !dbg !229

.lr.ph34:                                         ; preds = %.preheader5, %.backedge
  %81 = call i8* @strtok(i8* %4, i8* nonnull getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0)) #8, !dbg !230
  %82 = icmp eq i8* %81, null, !dbg !232
  br i1 %82, label %.backedge, label %83, !dbg !233

; <label>:83                                      ; preds = %.lr.ph34
  %84 = load i32, i32* %numObjects, align 4, !dbg !234, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %84, i64 0, metadata !34, metadata !112), !dbg !159
  %85 = add nsw i32 %84, 1, !dbg !234
  call void @llvm.dbg.value(metadata i32 %85, i64 0, metadata !34, metadata !112), !dbg !159
  store i32 %85, i32* %numObjects, align 4, !dbg !234, !tbaa !161
  br label %.backedge, !dbg !235

.backedge:                                        ; preds = %83, %.lr.ph34
  %86 = call i8* @fgets(i8* %4, i32 1024, %struct._IO_FILE* nonnull %74) #8, !dbg !222
  %87 = icmp eq i8* %86, null, !dbg !224
  br i1 %87, label %._crit_edge35, label %.lr.ph34, !dbg !225

._crit_edge35:                                    ; preds = %.backedge, %.preheader5
  call void @rewind(%struct._IO_FILE* nonnull %74) #8, !dbg !236
  br label %88, !dbg !237

; <label>:88                                      ; preds = %91, %._crit_edge35
  %89 = call i8* @fgets(i8* %4, i32 1024, %struct._IO_FILE* nonnull %74) #8, !dbg !238
  %90 = icmp eq i8* %89, null, !dbg !239
  br i1 %90, label %.loopexit3, label %91, !dbg !240

; <label>:91                                      ; preds = %88
  %92 = call i8* @strtok(i8* %4, i8* nonnull getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0)) #8, !dbg !241
  %93 = icmp eq i8* %92, null, !dbg !244
  br i1 %93, label %88, label %.preheader2, !dbg !245

.preheader2:                                      ; preds = %91
  %94 = call i8* @strtok(i8* null, i8* nonnull getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i64 0, i64 0)) #8, !dbg !246
  %95 = icmp eq i8* %94, null, !dbg !249
  br i1 %95, label %.loopexit3, label %.lr.ph33, !dbg !250

.lr.ph33:                                         ; preds = %.preheader2, %.lr.ph33
  %96 = load i32, i32* %numAttributes, align 4, !dbg !251, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %96, i64 0, metadata !33, metadata !112), !dbg !163
  %97 = add nsw i32 %96, 1, !dbg !251
  call void @llvm.dbg.value(metadata i32 %97, i64 0, metadata !33, metadata !112), !dbg !163
  store i32 %97, i32* %numAttributes, align 4, !dbg !251, !tbaa !161
  %98 = call i8* @strtok(i8* null, i8* nonnull getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i64 0, i64 0)) #8, !dbg !246
  %99 = icmp eq i8* %98, null, !dbg !249
  br i1 %99, label %.loopexit3, label %.lr.ph33, !dbg !250

.loopexit3:                                       ; preds = %88, %.lr.ph33, %.preheader2
  %100 = load i32, i32* %numObjects, align 4, !dbg !253, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %100, i64 0, metadata !34, metadata !112), !dbg !159
  %101 = load i32, i32* %numAttributes, align 4, !dbg !254, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %101, i64 0, metadata !33, metadata !112), !dbg !163
  %102 = mul nsw i32 %101, %100, !dbg !255
  %103 = sext i32 %102 to i64, !dbg !253
  %104 = shl nsw i64 %103, 2, !dbg !256
  %105 = call noalias i8* @malloc(i64 %104) #8, !dbg !257
  %106 = bitcast i8* %105 to float*, !dbg !258
  call void @llvm.dbg.value(metadata float* %106, i64 0, metadata !28, metadata !112), !dbg !185
  %107 = load i32, i32* %numObjects, align 4, !dbg !259, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %107, i64 0, metadata !34, metadata !112), !dbg !159
  %108 = sext i32 %107 to i64, !dbg !259
  %109 = shl nsw i64 %108, 3, !dbg !260
  %110 = call noalias i8* @malloc(i64 %109) #8, !dbg !261
  %111 = bitcast i8* %110 to float**, !dbg !262
  call void @llvm.dbg.value(metadata float** %111, i64 0, metadata !29, metadata !112), !dbg !190
  %112 = load i32, i32* %numObjects, align 4, !dbg !263, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %112, i64 0, metadata !34, metadata !112), !dbg !159
  %113 = load i32, i32* %numAttributes, align 4, !dbg !264, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %113, i64 0, metadata !33, metadata !112), !dbg !163
  %114 = mul nsw i32 %113, %112, !dbg !265
  %115 = sext i32 %114 to i64, !dbg !263
  %116 = shl nsw i64 %115, 2, !dbg !266
  %117 = call noalias i8* @malloc(i64 %116) #8, !dbg !267
  %118 = bitcast i8* %110 to i8**, !dbg !268
  store i8* %117, i8** %118, align 8, !dbg !268, !tbaa !116
  call void @llvm.dbg.value(metadata i32 1, i64 0, metadata !31, metadata !112), !dbg !197
  %119 = load i32, i32* %numObjects, align 4, !dbg !269, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %119, i64 0, metadata !34, metadata !112), !dbg !159
  %120 = icmp sgt i32 %119, 1, !dbg !273
  br i1 %120, label %.lr.ph32, label %._crit_edge, !dbg !274

.lr.ph32:                                         ; preds = %.loopexit3
  %121 = load i32, i32* %numAttributes, align 4, !dbg !275
  %122 = sext i32 %121 to i64, !dbg !276
  %123 = load i32, i32* %numObjects, align 4, !dbg !269
  %124 = sext i32 %123 to i64, !dbg !274
  br label %125, !dbg !274

; <label>:125                                     ; preds = %.lr.ph32, %125
  %indvars.iv57 = phi i64 [ 1, %.lr.ph32 ], [ %indvars.iv.next58, %125 ]
  %126 = add nsw i64 %indvars.iv57, -1, !dbg !277
  %127 = getelementptr inbounds float*, float** %111, i64 %126, !dbg !278
  %128 = load float*, float** %127, align 8, !dbg !278, !tbaa !116
  call void @llvm.dbg.value(metadata i32 %121, i64 0, metadata !33, metadata !112), !dbg !163
  %129 = getelementptr inbounds float, float* %128, i64 %122, !dbg !276
  %130 = getelementptr inbounds float*, float** %111, i64 %indvars.iv57, !dbg !279
  store float* %129, float** %130, align 8, !dbg !280, !tbaa !116
  %indvars.iv.next58 = add nuw nsw i64 %indvars.iv57, 1, !dbg !274
  call void @llvm.dbg.value(metadata i32 %123, i64 0, metadata !34, metadata !112), !dbg !159
  %131 = icmp slt i64 %indvars.iv.next58, %124, !dbg !273
  br i1 %131, label %125, label %._crit_edge, !dbg !274

._crit_edge:                                      ; preds = %125, %.loopexit3
  call void @rewind(%struct._IO_FILE* nonnull %74) #8, !dbg !281
  call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !31, metadata !112), !dbg !197
  br label %.outer.outer, !dbg !282

.outer.outer:                                     ; preds = %.lr.ph, %._crit_edge
  %i.2.ph.ph = phi i32 [ 0, %._crit_edge ], [ %144, %.lr.ph ]
  br label %.outer, !dbg !283

.outer:                                           ; preds = %134, %.outer.outer
  %132 = call i8* @fgets(i8* %4, i32 1024, %struct._IO_FILE* nonnull %74) #8, !dbg !283
  %133 = icmp eq i8* %132, null, !dbg !284
  br i1 %133, label %148, label %134, !dbg !285

; <label>:134                                     ; preds = %.outer
  %135 = call i8* @strtok(i8* %4, i8* nonnull getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0)) #8, !dbg !286
  %136 = icmp ne i8* %135, null, !dbg !289
  %137 = load i32, i32* %numAttributes, align 4, !dbg !290
  %138 = icmp sgt i32 %137, 0, !dbg !294
  %or.cond = and i1 %136, %138, !dbg !295
  br i1 %or.cond, label %.lr.ph.preheader, label %.outer, !dbg !295

.lr.ph.preheader:                                 ; preds = %134
  %139 = sext i32 %i.2.ph.ph to i64, !dbg !296
  br label %.lr.ph, !dbg !296

.lr.ph:                                           ; preds = %.lr.ph.preheader, %.lr.ph
  %indvars.iv = phi i64 [ %139, %.lr.ph.preheader ], [ %indvars.iv.next, %.lr.ph ]
  %j.030 = phi i32 [ 0, %.lr.ph.preheader ], [ %145, %.lr.ph ]
  %i.329 = phi i32 [ %i.2.ph.ph, %.lr.ph.preheader ], [ %144, %.lr.ph ]
  %140 = call i8* @strtok(i8* null, i8* nonnull getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i64 0, i64 0)) #8, !dbg !296
  %141 = call double @atof(i8* %140) #11, !dbg !298
  %142 = fptrunc double %141 to float, !dbg !300
  %143 = getelementptr inbounds float, float* %106, i64 %indvars.iv, !dbg !301
  store float %142, float* %143, align 4, !dbg !302, !tbaa !303
  %144 = add nsw i32 %i.329, 1, !dbg !305
  call void @llvm.dbg.value(metadata i32 %144, i64 0, metadata !31, metadata !112), !dbg !197
  %145 = add nuw nsw i32 %j.030, 1, !dbg !306
  call void @llvm.dbg.value(metadata i32 %145, i64 0, metadata !32, metadata !112), !dbg !308
  %146 = load i32, i32* %numAttributes, align 4, !dbg !290, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %146, i64 0, metadata !33, metadata !112), !dbg !163
  %147 = icmp slt i32 %145, %146, !dbg !294
  %indvars.iv.next = add i64 %indvars.iv, 1, !dbg !309
  br i1 %147, label %.lr.ph, label %.outer.outer, !dbg !309

; <label>:148                                     ; preds = %.outer
  %149 = call i32 @fclose(%struct._IO_FILE* nonnull %74) #8, !dbg !310
  br label %150

; <label>:150                                     ; preds = %148, %._crit_edge39
  %attributes.0 = phi float** [ %46, %._crit_edge39 ], [ %111, %148 ]
  %buf.0 = phi float* [ %41, %._crit_edge39 ], [ %106, %148 ]
  call void @llvm.dbg.value(metadata i32 1, i64 0, metadata !40, metadata !112), !dbg !311
  %151 = call i32 (i8*, ...) @printf(i8* nonnull getelementptr inbounds ([15 x i8], [15 x i8]* @.str.7, i64 0, i64 0)) #8, !dbg !312
  %152 = bitcast float** %attributes.0 to i8**, !dbg !313
  %153 = load i8*, i8** %152, align 8, !dbg !313, !tbaa !116
  %154 = bitcast float* %buf.0 to i8*, !dbg !314
  %155 = load i32, i32* %numObjects, align 4, !dbg !315, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %155, i64 0, metadata !34, metadata !112), !dbg !159
  %156 = load i32, i32* %numAttributes, align 4, !dbg !316, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %156, i64 0, metadata !33, metadata !112), !dbg !163
  %157 = mul nsw i32 %156, %155, !dbg !317
  %158 = sext i32 %157 to i64, !dbg !315
  %159 = shl nsw i64 %158, 2, !dbg !318
  %160 = call i8* @memcpy(i8* %153, i8* %154, i64 %159) #8, !dbg !319
  call void @llvm.dbg.value(metadata i32 0, i64 0, metadata !31, metadata !112), !dbg !197
  call void @llvm.dbg.value(metadata float** null, i64 0, metadata !30, metadata !112), !dbg !127
  store float** null, float*** %cluster_centres, align 8, !dbg !320, !tbaa !116
  %161 = load i32, i32* %numObjects, align 4, !dbg !324, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %161, i64 0, metadata !34, metadata !112), !dbg !159
  %162 = load i32, i32* %numAttributes, align 4, !dbg !325, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %162, i64 0, metadata !33, metadata !112), !dbg !163
  call void @llvm.dbg.value(metadata float*** %cluster_centres, i64 0, metadata !30, metadata !176), !dbg !127
  %163 = call i32 @cluster(i32 %161, i32 %162, float** %attributes.0, i32 %nclusters.0, float %threshold.0.ph8, float*** nonnull %cluster_centres) #8, !dbg !326
  %164 = call i32 (i8*, ...) @printf(i8* nonnull getelementptr inbounds ([23 x i8], [23 x i8]* @.str.8, i64 0, i64 0), i32 %nclusters.0) #8, !dbg !327
  %165 = load i32, i32* %numAttributes, align 4, !dbg !328, !tbaa !161
  call void @llvm.dbg.value(metadata i32 %165, i64 0, metadata !33, metadata !112), !dbg !163
  %166 = call i32 (i8*, ...) @printf(i8* nonnull getelementptr inbounds ([26 x i8], [26 x i8]* @.str.9, i64 0, i64 0), i32 %165) #8, !dbg !329
  %167 = call i32 @system(i8* nonnull getelementptr inbounds ([28 x i8], [28 x i8]* @.str.10, i64 0, i64 0)) #8, !dbg !330
  %168 = bitcast float** %attributes.0 to i8*, !dbg !331
  call void @free(i8* %168) #8, !dbg !332
  %169 = bitcast float*** %cluster_centres to i8***, !dbg !333
  %170 = load i8**, i8*** %169, align 8, !dbg !333, !tbaa !116
  %171 = load i8*, i8** %170, align 8, !dbg !333, !tbaa !116
  call void @free(i8* %171) #8, !dbg !334
  %172 = bitcast float*** %cluster_centres to i8**, !dbg !335
  %173 = load i8*, i8** %172, align 8, !dbg !335, !tbaa !116
  call void @free(i8* %173) #8, !dbg !336
  call void @free(i8* %154) #8, !dbg !337
  call void @llvm.lifetime.end(i64 1024, i8* %4) #10, !dbg !338
  call void @llvm.lifetime.end(i64 4, i8* nonnull %3) #10, !dbg !340
  call void @llvm.lifetime.end(i64 4, i8* nonnull %2) #10, !dbg !342
  call void @llvm.lifetime.end(i64 8, i8* %1) #10, !dbg !344
  ret i32 0, !dbg !346
}

declare i32 @getopt(i32, i8**, i8*) #3

; Function Attrs: nounwind readonly
declare double @atof(i8*) #6

; Function Attrs: nounwind readonly
declare i32 @atoi(i8*) #6

declare i32 @open(i8*, i32, ...) #3

declare i32 @read(...) #3

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #7

declare i32 @close(...) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.lifetime.end(i64, i8* nocapture) #2

declare %struct._IO_FILE* @fopen(i8*, i8*) #3

declare i8* @fgets(i8*, i32, %struct._IO_FILE*) #3

; Function Attrs: nounwind
declare i8* @strtok(i8*, i8*) #7

declare void @rewind(%struct._IO_FILE*) #3

declare i32 @fclose(%struct._IO_FILE*) #3

declare i32 @printf(i8*, ...) #3

; Function Attrs: nounwind
declare i8* @memcpy(i8*, i8*, i64) #7

declare i32 @cluster(i32, i32, float**, i32, float, float***) #3

declare i32 @system(i8*) #3

; Function Attrs: nounwind
declare void @free(i8*) #7

; Function Attrs: nounwind readnone
declare void @llvm.dbg.value(metadata, i64, metadata, metadata) #1

attributes #0 = { noinline noreturn nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noinline nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nobuiltin nounwind }
attributes #9 = { nobuiltin noreturn nounwind }
attributes #10 = { nounwind }
attributes #11 = { nobuiltin nounwind readonly }
attributes #12 = { nobuiltin }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!108, !109, !110}
!llvm.ident = !{!111}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: true, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !8)
!1 = !DIFile(filename: "kmeans.c", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!2 = !{}
!3 = !{!4, !6, !7}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIBasicType(name: "float", size: 32, align: 32, encoding: DW_ATE_float)
!6 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64, align: 64)
!7 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!8 = !{!9, !17}
!9 = distinct !DISubprogram(name: "usage", scope: !1, file: !1, line: 85, type: !10, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: true, variables: !14)
!10 = !DISubroutineType(types: !11)
!11 = !{null, !12}
!12 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !{!15, !16}
!15 = !DILocalVariable(name: "argv0", arg: 1, scope: !9, file: !1, line: 85, type: !12)
!16 = !DILocalVariable(name: "help", scope: !9, file: !1, line: 86, type: !12)
!17 = distinct !DISubprogram(name: "main", scope: !1, file: !1, line: 97, type: !18, isLocal: false, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: true, variables: !22)
!18 = !DISubroutineType(types: !19)
!19 = !{!20, !20, !21}
!20 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!22 = !{!23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !39, !40, !41, !42, !44, !47}
!23 = !DILocalVariable(name: "argc", arg: 1, scope: !17, file: !1, line: 97, type: !20)
!24 = !DILocalVariable(name: "argv", arg: 2, scope: !17, file: !1, line: 97, type: !21)
!25 = !DILocalVariable(name: "opt", scope: !17, file: !1, line: 98, type: !20)
!26 = !DILocalVariable(name: "nclusters", scope: !17, file: !1, line: 101, type: !20)
!27 = !DILocalVariable(name: "filename", scope: !17, file: !1, line: 102, type: !12)
!28 = !DILocalVariable(name: "buf", scope: !17, file: !1, line: 103, type: !4)
!29 = !DILocalVariable(name: "attributes", scope: !17, file: !1, line: 104, type: !6)
!30 = !DILocalVariable(name: "cluster_centres", scope: !17, file: !1, line: 105, type: !6)
!31 = !DILocalVariable(name: "i", scope: !17, file: !1, line: 106, type: !20)
!32 = !DILocalVariable(name: "j", scope: !17, file: !1, line: 106, type: !20)
!33 = !DILocalVariable(name: "numAttributes", scope: !17, file: !1, line: 108, type: !20)
!34 = !DILocalVariable(name: "numObjects", scope: !17, file: !1, line: 109, type: !20)
!35 = !DILocalVariable(name: "line", scope: !17, file: !1, line: 110, type: !36)
!36 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 8192, align: 8, elements: !37)
!37 = !{!38}
!38 = !DISubrange(count: 1024)
!39 = !DILocalVariable(name: "isBinaryFile", scope: !17, file: !1, line: 111, type: !20)
!40 = !DILocalVariable(name: "nloops", scope: !17, file: !1, line: 112, type: !20)
!41 = !DILocalVariable(name: "threshold", scope: !17, file: !1, line: 113, type: !5)
!42 = !DILocalVariable(name: "timing", scope: !17, file: !1, line: 114, type: !43)
!43 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!44 = !DILocalVariable(name: "infile", scope: !45, file: !1, line: 142, type: !20)
!45 = distinct !DILexicalBlock(scope: !46, file: !1, line: 141, column: 23)
!46 = distinct !DILexicalBlock(scope: !17, file: !1, line: 141, column: 9)
!47 = !DILocalVariable(name: "infile", scope: !48, file: !1, line: 163, type: !49)
!48 = distinct !DILexicalBlock(scope: !46, file: !1, line: 162, column: 10)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !51, line: 48, baseType: !52)
!51 = !DIFile(filename: "/usr/include/stdio.h", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!52 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !53, line: 245, size: 1728, align: 64, elements: !54)
!53 = !DIFile(filename: "/usr/include/libio.h", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!54 = !{!55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !75, !76, !77, !78, !82, !84, !86, !90, !93, !95, !96, !97, !98, !99, !103, !104}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !52, file: !53, line: 246, baseType: !20, size: 32, align: 32)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !52, file: !53, line: 251, baseType: !12, size: 64, align: 64, offset: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !52, file: !53, line: 252, baseType: !12, size: 64, align: 64, offset: 128)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !52, file: !53, line: 253, baseType: !12, size: 64, align: 64, offset: 192)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !52, file: !53, line: 254, baseType: !12, size: 64, align: 64, offset: 256)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !52, file: !53, line: 255, baseType: !12, size: 64, align: 64, offset: 320)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !52, file: !53, line: 256, baseType: !12, size: 64, align: 64, offset: 384)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !52, file: !53, line: 257, baseType: !12, size: 64, align: 64, offset: 448)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !52, file: !53, line: 258, baseType: !12, size: 64, align: 64, offset: 512)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !52, file: !53, line: 260, baseType: !12, size: 64, align: 64, offset: 576)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !52, file: !53, line: 261, baseType: !12, size: 64, align: 64, offset: 640)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !52, file: !53, line: 262, baseType: !12, size: 64, align: 64, offset: 704)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !52, file: !53, line: 264, baseType: !68, size: 64, align: 64, offset: 768)
!68 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!69 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !53, line: 160, size: 192, align: 64, elements: !70)
!70 = !{!71, !72, !74}
!71 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !69, file: !53, line: 161, baseType: !68, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !69, file: !53, line: 162, baseType: !73, size: 64, align: 64, offset: 64)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !69, file: !53, line: 166, baseType: !20, size: 32, align: 32, offset: 128)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !52, file: !53, line: 266, baseType: !73, size: 64, align: 64, offset: 832)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !52, file: !53, line: 268, baseType: !20, size: 32, align: 32, offset: 896)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !52, file: !53, line: 272, baseType: !20, size: 32, align: 32, offset: 928)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !52, file: !53, line: 274, baseType: !79, size: 64, align: 64, offset: 960)
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !80, line: 131, baseType: !81)
!80 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!81 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !52, file: !53, line: 278, baseType: !83, size: 16, align: 16, offset: 1024)
!83 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !52, file: !53, line: 279, baseType: !85, size: 8, align: 8, offset: 1040)
!85 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !52, file: !53, line: 280, baseType: !87, size: 8, align: 8, offset: 1048)
!87 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 8, align: 8, elements: !88)
!88 = !{!89}
!89 = !DISubrange(count: 1)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !52, file: !53, line: 284, baseType: !91, size: 64, align: 64, offset: 1088)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !92, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !53, line: 154, baseType: null)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !52, file: !53, line: 293, baseType: !94, size: 64, align: 64, offset: 1152)
!94 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !80, line: 132, baseType: !81)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !52, file: !53, line: 302, baseType: !7, size: 64, align: 64, offset: 1216)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !52, file: !53, line: 303, baseType: !7, size: 64, align: 64, offset: 1280)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !52, file: !53, line: 304, baseType: !7, size: 64, align: 64, offset: 1344)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !52, file: !53, line: 305, baseType: !7, size: 64, align: 64, offset: 1408)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !52, file: !53, line: 306, baseType: !100, size: 64, align: 64, offset: 1472)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !101, line: 62, baseType: !102)
!101 = !DIFile(filename: "/opt/pasa_lib/llvm-3.8.0/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/home/azguolu/ARAT-0.1/benchmark_working_station/kmeans")
!102 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !52, file: !53, line: 308, baseType: !20, size: 32, align: 32, offset: 1536)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !52, file: !53, line: 310, baseType: !105, size: 160, align: 8, offset: 1568)
!105 = !DICompositeType(tag: DW_TAG_array_type, baseType: !13, size: 160, align: 8, elements: !106)
!106 = !{!107}
!107 = !DISubrange(count: 20)
!108 = !{i32 2, !"Dwarf Version", i32 4}
!109 = !{i32 2, !"Debug Info Version", i32 3}
!110 = !{i32 1, !"PIC Level", i32 2}
!111 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!112 = !DIExpression()
!113 = !DILocation(line: 85, column: 18, scope: !9)
!114 = !DILocation(line: 86, column: 11, scope: !9)
!115 = !DILocation(line: 92, column: 13, scope: !9)
!116 = !{!117, !117, i64 0}
!117 = !{!"any pointer", !118, i64 0}
!118 = !{!"omnipotent char", !119, i64 0}
!119 = !{!"Simple C/C++ TBAA"}
!120 = !DILocation(line: 92, column: 5, scope: !9)
!121 = !DILocation(line: 93, column: 5, scope: !9)
!122 = !DILocation(line: 97, column: 14, scope: !17)
!123 = !DILocation(line: 97, column: 27, scope: !17)
!124 = !DILocation(line: 101, column: 20, scope: !17)
!125 = !DILocation(line: 102, column: 20, scope: !17)
!126 = !DILocation(line: 105, column: 12, scope: !17)
!127 = !DILocation(line: 105, column: 20, scope: !17)
!128 = !DILocation(line: 108, column: 12, scope: !17)
!129 = !DILocation(line: 109, column: 12, scope: !17)
!130 = !DILocation(line: 110, column: 12, scope: !17)
!131 = !DILocation(line: 110, column: 20, scope: !17)
!132 = !DILocation(line: 111, column: 20, scope: !17)
!133 = !DILocation(line: 113, column: 20, scope: !17)
!134 = !DILocation(line: 118, column: 2, scope: !17)
!135 = !DILocation(line: 118, column: 15, scope: !136)
!136 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 1)
!137 = !DILocation(line: 98, column: 20, scope: !17)
!138 = !DILocation(line: 118, column: 2, scope: !136)
!139 = !DILocation(line: 120, column: 32, scope: !140)
!140 = distinct !DILexicalBlock(scope: !141, file: !1, line: 119, column: 22)
!141 = distinct !DILexicalBlock(scope: !17, file: !1, line: 118, column: 51)
!142 = !DILocation(line: 121, column: 23, scope: !140)
!143 = !DILocation(line: 124, column: 38, scope: !140)
!144 = !DILocation(line: 124, column: 33, scope: !140)
!145 = !DILocation(line: 125, column: 23, scope: !140)
!146 = !DILocation(line: 126, column: 40, scope: !140)
!147 = !DILocation(line: 126, column: 35, scope: !140)
!148 = !DILocation(line: 127, column: 23, scope: !140)
!149 = !DILocation(line: 128, column: 29, scope: !140)
!150 = !DILocation(line: 128, column: 23, scope: !140)
!151 = !DILocation(line: 130, column: 28, scope: !140)
!152 = !DILocation(line: 130, column: 22, scope: !140)
!153 = !DILocation(line: 135, column: 18, scope: !154)
!154 = distinct !DILexicalBlock(scope: !17, file: !1, line: 135, column: 9)
!155 = !DILocation(line: 135, column: 9, scope: !17)
!156 = !DILocation(line: 135, column: 30, scope: !157)
!157 = !DILexicalBlockFile(scope: !154, file: !1, discriminator: 1)
!158 = !DILocation(line: 135, column: 24, scope: !157)
!159 = !DILocation(line: 109, column: 20, scope: !17)
!160 = !DILocation(line: 137, column: 32, scope: !17)
!161 = !{!162, !162, i64 0}
!162 = !{!"int", !118, i64 0}
!163 = !DILocation(line: 108, column: 20, scope: !17)
!164 = !DILocation(line: 137, column: 19, scope: !17)
!165 = !DILocation(line: 141, column: 9, scope: !46)
!166 = !DILocation(line: 141, column: 9, scope: !17)
!167 = !DILocation(line: 143, column: 23, scope: !168)
!168 = distinct !DILexicalBlock(scope: !45, file: !1, line: 143, column: 13)
!169 = !DILocation(line: 142, column: 13, scope: !45)
!170 = !DILocation(line: 143, column: 57, scope: !168)
!171 = !DILocation(line: 143, column: 13, scope: !45)
!172 = !DILocation(line: 144, column: 21, scope: !173)
!173 = distinct !DILexicalBlock(scope: !168, file: !1, line: 143, column: 64)
!174 = !DILocation(line: 144, column: 13, scope: !173)
!175 = !DILocation(line: 145, column: 13, scope: !173)
!176 = !DIExpression(DW_OP_deref)
!177 = !DILocation(line: 147, column: 9, scope: !45)
!178 = !DILocation(line: 148, column: 9, scope: !45)
!179 = !DILocation(line: 152, column: 41, scope: !45)
!180 = !DILocation(line: 152, column: 52, scope: !45)
!181 = !DILocation(line: 152, column: 51, scope: !45)
!182 = !DILocation(line: 152, column: 65, scope: !45)
!183 = !DILocation(line: 152, column: 34, scope: !45)
!184 = !DILocation(line: 152, column: 25, scope: !45)
!185 = !DILocation(line: 103, column: 20, scope: !17)
!186 = !DILocation(line: 153, column: 41, scope: !45)
!187 = !DILocation(line: 153, column: 51, scope: !45)
!188 = !DILocation(line: 153, column: 34, scope: !45)
!189 = !DILocation(line: 153, column: 25, scope: !45)
!190 = !DILocation(line: 104, column: 20, scope: !17)
!191 = !DILocation(line: 154, column: 41, scope: !45)
!192 = !DILocation(line: 154, column: 52, scope: !45)
!193 = !DILocation(line: 154, column: 51, scope: !45)
!194 = !DILocation(line: 154, column: 65, scope: !45)
!195 = !DILocation(line: 154, column: 34, scope: !45)
!196 = !DILocation(line: 154, column: 23, scope: !45)
!197 = !DILocation(line: 106, column: 20, scope: !17)
!198 = !DILocation(line: 155, column: 21, scope: !199)
!199 = !DILexicalBlockFile(scope: !200, file: !1, discriminator: 1)
!200 = distinct !DILexicalBlock(scope: !201, file: !1, line: 155, column: 9)
!201 = distinct !DILexicalBlock(scope: !45, file: !1, line: 155, column: 9)
!202 = !DILocation(line: 155, column: 20, scope: !199)
!203 = !DILocation(line: 155, column: 9, scope: !199)
!204 = !DILocation(line: 156, column: 47, scope: !200)
!205 = !DILocation(line: 156, column: 45, scope: !200)
!206 = !DILocation(line: 156, column: 41, scope: !200)
!207 = !DILocation(line: 156, column: 29, scope: !200)
!208 = !DILocation(line: 156, column: 13, scope: !200)
!209 = !DILocation(line: 156, column: 27, scope: !200)
!210 = !DILocation(line: 158, column: 38, scope: !45)
!211 = !DILocation(line: 158, column: 37, scope: !45)
!212 = !DILocation(line: 158, column: 27, scope: !45)
!213 = !DILocation(line: 158, column: 51, scope: !45)
!214 = !DILocation(line: 158, column: 9, scope: !45)
!215 = !DILocation(line: 160, column: 9, scope: !45)
!216 = !DILocation(line: 161, column: 5, scope: !45)
!217 = !DILocation(line: 164, column: 23, scope: !218)
!218 = distinct !DILexicalBlock(scope: !48, file: !1, line: 164, column: 13)
!219 = !DILocation(line: 163, column: 15, scope: !48)
!220 = !DILocation(line: 164, column: 45, scope: !218)
!221 = !DILocation(line: 164, column: 13, scope: !48)
!222 = !DILocation(line: 168, column: 16, scope: !223)
!223 = !DILexicalBlockFile(scope: !48, file: !1, discriminator: 1)
!224 = !DILocation(line: 168, column: 42, scope: !223)
!225 = !DILocation(line: 168, column: 9, scope: !223)
!226 = !DILocation(line: 165, column: 21, scope: !227)
!227 = distinct !DILexicalBlock(scope: !218, file: !1, line: 164, column: 54)
!228 = !DILocation(line: 165, column: 13, scope: !227)
!229 = !DILocation(line: 166, column: 13, scope: !227)
!230 = !DILocation(line: 169, column: 17, scope: !231)
!231 = distinct !DILexicalBlock(scope: !48, file: !1, line: 169, column: 17)
!232 = !DILocation(line: 169, column: 39, scope: !231)
!233 = !DILocation(line: 169, column: 17, scope: !48)
!234 = !DILocation(line: 170, column: 27, scope: !231)
!235 = !DILocation(line: 170, column: 17, scope: !231)
!236 = !DILocation(line: 171, column: 9, scope: !48)
!237 = !DILocation(line: 172, column: 9, scope: !48)
!238 = !DILocation(line: 172, column: 16, scope: !223)
!239 = !DILocation(line: 172, column: 42, scope: !223)
!240 = !DILocation(line: 172, column: 9, scope: !223)
!241 = !DILocation(line: 173, column: 17, scope: !242)
!242 = distinct !DILexicalBlock(scope: !243, file: !1, line: 173, column: 17)
!243 = distinct !DILexicalBlock(scope: !48, file: !1, line: 172, column: 51)
!244 = !DILocation(line: 173, column: 39, scope: !242)
!245 = !DILocation(line: 173, column: 17, scope: !243)
!246 = !DILocation(line: 175, column: 24, scope: !247)
!247 = !DILexicalBlockFile(scope: !248, file: !1, discriminator: 1)
!248 = distinct !DILexicalBlock(scope: !242, file: !1, line: 173, column: 45)
!249 = !DILocation(line: 175, column: 47, scope: !247)
!250 = !DILocation(line: 175, column: 17, scope: !247)
!251 = !DILocation(line: 175, column: 69, scope: !252)
!252 = !DILexicalBlockFile(scope: !248, file: !1, discriminator: 2)
!253 = !DILocation(line: 182, column: 41, scope: !48)
!254 = !DILocation(line: 182, column: 52, scope: !48)
!255 = !DILocation(line: 182, column: 51, scope: !48)
!256 = !DILocation(line: 182, column: 65, scope: !48)
!257 = !DILocation(line: 182, column: 34, scope: !48)
!258 = !DILocation(line: 182, column: 25, scope: !48)
!259 = !DILocation(line: 183, column: 41, scope: !48)
!260 = !DILocation(line: 183, column: 51, scope: !48)
!261 = !DILocation(line: 183, column: 34, scope: !48)
!262 = !DILocation(line: 183, column: 25, scope: !48)
!263 = !DILocation(line: 184, column: 41, scope: !48)
!264 = !DILocation(line: 184, column: 52, scope: !48)
!265 = !DILocation(line: 184, column: 51, scope: !48)
!266 = !DILocation(line: 184, column: 65, scope: !48)
!267 = !DILocation(line: 184, column: 34, scope: !48)
!268 = !DILocation(line: 184, column: 23, scope: !48)
!269 = !DILocation(line: 185, column: 21, scope: !270)
!270 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 1)
!271 = distinct !DILexicalBlock(scope: !272, file: !1, line: 185, column: 9)
!272 = distinct !DILexicalBlock(scope: !48, file: !1, line: 185, column: 9)
!273 = !DILocation(line: 185, column: 20, scope: !270)
!274 = !DILocation(line: 185, column: 9, scope: !270)
!275 = !DILocation(line: 186, column: 47, scope: !271)
!276 = !DILocation(line: 186, column: 45, scope: !271)
!277 = !DILocation(line: 186, column: 41, scope: !271)
!278 = !DILocation(line: 186, column: 29, scope: !271)
!279 = !DILocation(line: 186, column: 13, scope: !271)
!280 = !DILocation(line: 186, column: 27, scope: !271)
!281 = !DILocation(line: 187, column: 9, scope: !48)
!282 = !DILocation(line: 189, column: 9, scope: !48)
!283 = !DILocation(line: 189, column: 16, scope: !223)
!284 = !DILocation(line: 189, column: 42, scope: !223)
!285 = !DILocation(line: 189, column: 9, scope: !223)
!286 = !DILocation(line: 190, column: 17, scope: !287)
!287 = distinct !DILexicalBlock(scope: !288, file: !1, line: 190, column: 17)
!288 = distinct !DILexicalBlock(scope: !48, file: !1, line: 189, column: 51)
!289 = !DILocation(line: 190, column: 39, scope: !287)
!290 = !DILocation(line: 191, column: 25, scope: !291)
!291 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 1)
!292 = distinct !DILexicalBlock(scope: !293, file: !1, line: 191, column: 13)
!293 = distinct !DILexicalBlock(scope: !288, file: !1, line: 191, column: 13)
!294 = !DILocation(line: 191, column: 24, scope: !291)
!295 = !DILocation(line: 190, column: 17, scope: !288)
!296 = !DILocation(line: 192, column: 31, scope: !297)
!297 = distinct !DILexicalBlock(scope: !292, file: !1, line: 191, column: 45)
!298 = !DILocation(line: 192, column: 26, scope: !299)
!299 = !DILexicalBlockFile(scope: !297, file: !1, discriminator: 1)
!300 = !DILocation(line: 192, column: 26, scope: !297)
!301 = !DILocation(line: 192, column: 17, scope: !297)
!302 = !DILocation(line: 192, column: 24, scope: !297)
!303 = !{!304, !304, i64 0}
!304 = !{!"float", !118, i64 0}
!305 = !DILocation(line: 193, column: 18, scope: !297)
!306 = !DILocation(line: 191, column: 41, scope: !307)
!307 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 2)
!308 = !DILocation(line: 106, column: 23, scope: !17)
!309 = !DILocation(line: 191, column: 13, scope: !291)
!310 = !DILocation(line: 196, column: 9, scope: !48)
!311 = !DILocation(line: 112, column: 20, scope: !17)
!312 = !DILocation(line: 200, column: 2, scope: !17)
!313 = !DILocation(line: 202, column: 9, scope: !17)
!314 = !DILocation(line: 202, column: 24, scope: !17)
!315 = !DILocation(line: 202, column: 29, scope: !17)
!316 = !DILocation(line: 202, column: 40, scope: !17)
!317 = !DILocation(line: 202, column: 39, scope: !17)
!318 = !DILocation(line: 202, column: 53, scope: !17)
!319 = !DILocation(line: 202, column: 2, scope: !17)
!320 = !DILocation(line: 207, column: 25, scope: !321)
!321 = distinct !DILexicalBlock(scope: !322, file: !1, line: 205, column: 30)
!322 = distinct !DILexicalBlock(scope: !323, file: !1, line: 205, column: 5)
!323 = distinct !DILexicalBlock(scope: !17, file: !1, line: 205, column: 5)
!324 = !DILocation(line: 208, column: 17, scope: !321)
!325 = !DILocation(line: 209, column: 17, scope: !321)
!326 = !DILocation(line: 208, column: 9, scope: !321)
!327 = !DILocation(line: 220, column: 2, scope: !17)
!328 = !DILocation(line: 221, column: 39, scope: !17)
!329 = !DILocation(line: 221, column: 2, scope: !17)
!330 = !DILocation(line: 222, column: 2, scope: !17)
!331 = !DILocation(line: 236, column: 10, scope: !17)
!332 = !DILocation(line: 236, column: 5, scope: !17)
!333 = !DILocation(line: 237, column: 10, scope: !17)
!334 = !DILocation(line: 237, column: 5, scope: !17)
!335 = !DILocation(line: 238, column: 10, scope: !17)
!336 = !DILocation(line: 238, column: 5, scope: !17)
!337 = !DILocation(line: 239, column: 5, scope: !17)
!338 = !DILocation(line: 241, column: 1, scope: !339)
!339 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 4)
!340 = !DILocation(line: 241, column: 1, scope: !341)
!341 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 5)
!342 = !DILocation(line: 241, column: 1, scope: !343)
!343 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 6)
!344 = !DILocation(line: 241, column: 1, scope: !345)
!345 = !DILexicalBlockFile(scope: !17, file: !1, discriminator: 9)
!346 = !DILocation(line: 240, column: 5, scope: !17)
