import numpy as np
import os
import sys

os.system("cat ./orgFaultInjectionSites/* > ./fault_injection_sites_cat")
suffix= "_"+os.getenv('BENCHMARK')+"_"

def unique_txt(file_name):
    arr = np.loadtxt(file_name, dtype='string')
    arr_copy = np.copy(arr)
    arr_copy = np.delete(arr_copy,2,1)
    arr_copy = np.delete(arr_copy,5,1)
    b = np.ascontiguousarray(arr_copy).view(np.dtype((np.void,
        arr_copy.dtype.itemsize * arr_copy.shape[1])))
    _, idx = np.unique(b, return_index=True)

    idx = np.sort(idx)
    unique_arr = arr[idx]
    #print idx
    np.savetxt ("./fault_sites_sampling_index", idx, fmt='%i')
    return unique_arr

file_name="fault_injection_sites_cat"
c = unique_txt(file_name)
#print c
np.savetxt ("./sampFaultInjectionSites/fault_injection"+suffix+"sampling", c, fmt='%s')

#remove the middle files
os.system("rm -f fault_sites_sampling_index")
os.system("rm -f fault_injection_sites_cat")

#end
