#include <stdio.h>
#include <omp.h>

double integrate(double (*)(double), double, double, int);
double finitesimal_area(double (*)(double), double, double);
double sequential_integrate(double (*)(double), double, double, int);


double sequential_integrate(double (*math_function)(double), double xi, double xf, int number_of_steps){
    double current_x = xi;
    double integration = 0.0;
    double delta_x = (xf-xi)/number_of_steps;

    while(current_x < xf){
        integration += finitesimal_area(math_function, current_x, delta_x);
        current_x += delta_x;
    }

    return integration;
}

double integrate(double (*math_function)(double), double xi, double xf, int number_of_steps){
    int number_of_cores = omp_get_num_procs();
    double interval_between_cores = (xf-xi)/number_of_cores;
    double number_of_steps_per_core = number_of_steps/number_of_cores;
    double total_integration = 0;
    int id;
    double local_xi, local_xf;

#pragma omp parallel private(id, local_xi, local_xf) num_threads(number_of_cores) reduction(+:total_integration) 
{
    id = omp_get_thread_num();
    local_xi = xi + id * interval_between_cores;
    local_xf = local_xi + interval_between_cores;

    total_integration += sequential_integrate(math_function, local_xi, local_xf, number_of_steps_per_core);
}

    return total_integration;
}


double finitesimal_area(double (*math_function)(double), double x, double delta_x){
    return math_function(x) * delta_x;
}
