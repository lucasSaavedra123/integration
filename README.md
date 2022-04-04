# integration
Simple C library to integrate functions fast

    $gcc pi.c -lm -fopenmp
    $./a.out
    Sequential approach time: 8.666573s
    Sequential approach result: 3.141593
    Parallel approach time: 3.574617s
    Parallel approach result: 3.141593
    Speedup: 2.424476
