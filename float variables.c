#include <stdio.h>

int main() {

    // variable = A reusable container for storing data
    //            Behaves as if it were the vale it contains
    float pi =3.14159; //if you need to store more precise values, use double instead of float
    double pi2 = 3.14159265358979323846; //double is more precise than float, but takes up more memory  
    float temperature = 32.5;
    
    printf("the value of pi is %.5f \n", pi); // %.5f stands for float with 5 decimal places
    printf("the value of pi2 is %lf \n", pi2); // %lf stands for long float (double)
    printf("the value of pi2 is %.20lf \n", pi2); // %.20lf stands for long float (double) with 20 decimal places
    printf("the value of temperature is %.1f° \n", temperature); // %.1f stands for float with 1 decimal place


    return 0;
}