import sys
import subprocess

program_name = sys.argv[1]
max_threads = int(sys.argv[2])
max_size = int(sys.argv[3])

ratio = 2

if "char" in program_name:
    file = open("results_char.csv", 'w')
    file.write("size,num_threads,seq_time,naive_parallel_time,smart_parallel_time,task_parallel_time\n")
elif "vect" in program_name:
    file = open('results_vect.csv', 'w')
    file.write("size,num_threads,vec_autoAdd,addVectors,multVecByNum,scalarProduct\n")
    ratio = 10
else:
    file = open('results_matrix.csv', 'w')
    file.write("size,num_threads,mat_autoAdd,addMatrices,multMatByNum,multMatrices,matByVec\n")

current_size = 100

while current_size <= max_size:
    print("measuring with size " + str(current_size))
    current_num_threads = 1
    while current_num_threads <= max_threads:
        print("\texecuting program with " + str(current_num_threads) + " threads")
        out = subprocess.check_output([program_name, str(current_num_threads), str(current_size)])
        file.write(str(out, 'utf-8'))

        # I choose these value because measure will be performed on 32 cores processors
        if current_num_threads == 1:
            current_num_threads += 1
        elif current_num_threads < 8:
            current_num_threads += 2
        elif current_num_threads < 20:
            current_num_threads += 4
        else:
            current_num_threads += 6
    current_size *= ratio

file.close()
