echo "the benchmark is: $BENCHMARK ..."
echo "the data object is: $TAR_DATA ..."
export INI_ADDR_ON_TDD=$(<../INI_ADDR_ON_TDD.txt) 
echo "the memory address of $TAR_DATA is: $INI_ADDR_ON_TDD ..."
echo "the error propagation threshould is: $ERR_PROP_THRESHOLD ..."
echo "the fault masking threshould is: $FAULT_MASK_THRESHOLD ..."
echo "Set the SERIAL_NUM as $SERIAL_NUM ..."

for file in ../tracefile/*;
do
  echo $file
  #fname=$(basename "$file" | tail -c 6)
  #echo $fname
  echo "start processing the $file ..."
  gdb ./traceAnalysisTool  
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection/
ls ../midd_file/
mv ../analysis_result/* ../result_collection/
#for f in ../midd_file/fault_injection*; do mv "$f" "$f_$ERR_PROP_THRESHOLD_$FAULT_MASK_THRESHOLD"; done
cp ../midd_file/fault_injection* ../faultInjectionSites/orgFaultInjectionSites/
mv ../midd_file/fault_injection* ../result_collection/
#rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"
