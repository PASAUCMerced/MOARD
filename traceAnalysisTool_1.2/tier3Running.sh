contains(){
    string="$1"
    substring="$2"
    if test "${string#*$substring}" != "$string"
    then
        return 0    # $substring is in $string
    else
        return 1    # $substring is not in $string
    fi
}


for fifile in ../midd_file/*;
do
  #echo $fifile
  finame=$(basename "$fifile")
  export FAULT_INJECTION_RESULT_DIR=$fifile
  suffix=${finame:16:5}
  lsuffix=${finame:16:8}
  export SERIAL_NUM=$suffix
  #echo $SERIAL_NUM
  #arr=$(echo $finame | tr "_" "\n")
  contains $finame "_u_" && contains $finame "bt" && export INI_ADDR_ON_TDD=7043872
  contains $finame "_a_" && contains $finame "cg" && export INI_ADDR_ON_TDD=6509968
  contains $finame "_x_" && contains $finame "cg" && export INI_ADDR_ON_TDD=7736384
  contains $finame "colidx" && contains $finame "cg" && export INI_ADDR_ON_TDD=7226768
  contains $finame "_z_" && contains $finame "cg" && export INI_ADDR_ON_TDD=7758816
  contains $finame "_u_" && contains $finame "mg" && export INI_ADDR_ON_TDD=6955904
  contains $finame "_r_" && contains $finame "mg" && export INI_ADDR_ON_TDD=7699584
  contains $finame "_c_" && contains $finame "mg" && export INI_ADDR_ON_TDD=140726166532496
  contains $finame "plane" && contains $finame "ft" && export INI_ADDR_ON_TDD=6529760
  contains $finame "exp1" && contains $finame "ft" && export INI_ADDR_ON_TDD=140724134630528
  contains $finame "rhoi" && contains $finame "bt" && export INI_ADDR_ON_TDD=7027616
  contains $finame "qs" && contains $finame "bt" && export INI_ADDR_ON_TDD=7141520
  contains $finame "rhoi" && contains $finame "sp" && export INI_ADDR_ON_TDD=6918912
  contains $finame "qs" && contains $finame "sp" && export INI_ADDR_ON_TDD=7049216
  contains $finame "_u_" && contains $finame "sp" && export INI_ADDR_ON_TDD=6790672
  contains $finame "_u_" && contains $finame "lu" && export INI_ADDR_ON_TDD=6679088
  contains $finame "rsd" && contains $finame "lu" && export INI_ADDR_ON_TDD=6776480
  contains $finame "50" && export ERR_PROP_THRESHOLD=50
  contains $finame "30" && export ERR_PROP_THRESHOLD=30
  contains $finame "20" && export ERR_PROP_THRESHOLD=20
  contains $finame "10" && export ERR_PROP_THRESHOLD=10
  contains $finame "_8_"  && export ERR_PROP_THRESHOLD=8
  contains $finame "_4_" && export ERR_PROP_THRESHOLD=4
  contains $finame "_2_" && export ERR_PROP_THRESHOLD=2
 
  contains $finame "0.01" && export FAULT_MASK_THRESHOLD=0.01
  contains $finame "0.04" && export FAULT_MASK_THRESHOLD=0.04
  contains $finame "0.07" && export FAULT_MASK_THRESHOLD=0.07
  contains $finame "0.1"  && export FAULT_MASK_THRESHOLD=0.1
  #echo $INI_ADDR_ON_TDD
  #echo $ERR_PROP_THRESHOLD
  #echo $FAULT_MASK_THRESHOLD

  echo "Start processing the trace ..."
  ./traceAnalysisTool
  echo "is finishing the analysis on trace ..."
  echo "Moving the final results into the collection folder ..."
  mkdir ../result_collection_$lsuffix+$ERR_PROP_THRESHOLD+$FAULT_MASK_THRESHOLD/
  mv ../analysis_result/* ../result_collection_$lsuffix+$ERR_PROP_THRESHOLD+$FAULT_MASK_THRESHOLD/
  #mv ../midd_file/fault_injection*  ../result_collection_$lsuffix+$ERR_PROP_THRESHOLD+$FAULT_MASK_THRESHOLD/  
  rm -f ../midd_file/glo*
  echo "Analysis is completed!"
done
