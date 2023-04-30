#include <stdio.h>
#include <math.h>


double f1(double x) 
{
    return x*x*x -19;
}
double derivada_f1(double x) 
{
    return 3*x*x;
}
double derivada2_f1(double x) 
{
    return 6*x;
}

double f2(double x) 
{
    return pow(x, 5) - (7.3)*pow(x, 4) + (2.24)*pow(x, 3) + (30.106)*pow(x, 2) - (42.1)*x + 15.94;
}
double derivada_f2(double x) 
{
    return 5*pow(x, 4) - 29.2*pow(x, 3) + 6.72*pow(x, 2) + 60.212*x - 42.1;
}
double derivada2_f2(double x) 
{
    return 20*pow(x, 3) - 87.6*pow(x, 2) + 13.44*x + 60.212;;
}

double f3(double x) 
{
    return (x-0.9)* pow(M_E, -4*(x-0.9)*(x-0.9));
}
double derivada_f3(double x) 
{
    return (((-8)*x + 7.2)*(x-0.9)) * pow(M_E, -4*(x-0.9)*(x-0.9));
}
double derivada2_f3(double x) 
{
    return 64*(-0.3915 + 2.055*x - 2.7*pow(x, 2) + pow(x, 3)) * pow(M_E, -4*(x-0.9)*(x-0.9));
}



int main()
{
    double numero = f3(2);
    printf("resultado: %.15f", numero);



    return 0;
}