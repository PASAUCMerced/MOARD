echo "Set the address on object data 'x' on CG benchmark ..."
export INI_ADDR_ON_TDD=7736384
echo "Set the error propagation threshold ..."
export ERR_PROP_THRESHOLD=2
echo "Set the fault masking threshold ..."
export FAULT_MASK_THRESHOLD=0.01
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool  
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_2/
mv ../analysis_result/* ../result_collection_2/
mv ../midd_file/fault_injection* ../result_collection_2/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=4
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_4/
mv ../analysis_result/* ../result_collection_4/
mv ../midd_file/fault_injection* ../result_collection_4/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=8
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_8/
mv ../analysis_result/* ../result_collection_8/
mv ../midd_file/fault_injection* ../result_collection_8/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=10
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_10/
mv ../analysis_result/* ../result_collection_10/
mv ../midd_file/fault_injection* ../result_collection_10/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=20
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_20/
mv ../analysis_result/* ../result_collection_20/
mv ../midd_file/fault_injection* ../result_collection_20/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=30
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_30/
mv ../analysis_result/* ../result_collection_30/
mv ../midd_file/fault_injection* ../result_collection_30/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

export ERR_PROP_THRESHOLD=50
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_50/
mv ../analysis_result/* ../result_collection_50/
mv ../midd_file/fault_injection* ../result_collection_50/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

#----------------------------------------------------------#
#---------------------The Next Sub Session-----------------#
#----------------------------------------------------------#
echo "Set the error propagation threshold ..."
export ERR_PROP_THRESHOLD=10
echo "Set the fault masking threshold ..."
export FAULT_MASK_THRESHOLD=0.1
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_0.1/
mv ../analysis_result/* ../result_collection_0.1/
mv ../midd_file/fault_injection* ../result_collection_0.1/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

echo "Set the fault masking threshold ..."
export FAULT_MASK_THRESHOLD=0.07
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_0.07/
mv ../analysis_result/* ../result_collection_0.07/
mv ../midd_file/fault_injection* ../result_collection_0.07/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

echo "Set the fault masking threshold ..."
export FAULT_MASK_THRESHOLD=0.04
echo "Start running the CG trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 6)
  #echo $fname
  export SERIAL_NUM=$fname
  #echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection_0.04/
mv ../analysis_result/* ../result_collection_0.04/
mv ../midd_file/fault_injection* ../result_collection_0.04/
rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

