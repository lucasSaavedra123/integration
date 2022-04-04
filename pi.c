#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "integrate.h"


double a_function(double x){
    double a = x * x;
    double b = 1;
    double c = b - a;

    return 4 * sqrt(c);
}

int main(){
    double time_one, time_two, sequential_time, parallel_time, sequential_result, parallel_result;

    time_one = omp_get_wtime();
    sequential_result = sequential_integrate(a_function, 0, 1, 1000000000);
    time_two = omp_get_wtime();
    sequential_time = time_two - time_one;

    time_one = omp_get_wtime();
    parallel_result = integrate(a_function, 0, 1, 1000000000);
    time_two = omp_get_wtime();
    parallel_time = time_two - time_one;

    printf("Sequential approach time: %lfs\n", sequential_time);
    printf("Sequential approach result: %lf\n", sequential_result);
    printf("Parallel approach time: %lfs\n", parallel_time);
    printf("Parallel approach result: %lf\n", parallel_result);
    printf("Speedup: %lf\n", sequential_time/parallel_time);

    return 0;
}
