../remove.bash
echo "Set the address on object data "delv_zeta" on Lulesh benchmark ..." 
export INI_ADDR_ON_TDD=14844400
echo "Set the error propagation threshold ..."
export ERR_PROP_THRESHOLD=5
echo "Set the fault masking threshold ..."
export FAULT_MASK_THRESHOLD=0.000000000000001
echo $FAULT_MASK_THRESHOLD
echo "Start running the LULESH trace file sequentially"
for file in ../tracefile/*;
do
  #echo $file
  fname=$(basename "$file" | tail -c 12)
  #echo $fname
  export SERIAL_NUM=$fname
  echo $SERIAL_NUM
  echo "Set the SERIAL_NUM as $SERIAL_NUM"
  echo "start processing the $file ..."
  ./traceAnalysisTool  
  echo "is finishing the $file ..."
done
echo "Moving the final results into the collection folder ..."
mkdir ../result_collection/
mv ../analysis_result/* ../result_collection/
mv ../midd_file/fault_injection* ../result_collection/
#rm ../midd_file/glo* -f
echo "Analysis on $file is completed!"

