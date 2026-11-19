#include <stdio.h>

int main(){

    // format specifier = special tokens that begin with a % symbol
    //                    followed by a character that specifies the data type 
    //                    and optional modifiers (width, precision, flags).
    //                    they control how data is displayed or interpreted.

    //width = minimum number of characters to be printed
    
    int age = 20; // int = whole numbers (4 bytes in modern systems)
    float price = 10.99; // float = single-precision decimal number (4 bytes)
    double pi = 3.1415926535; // double = double-precision decimal number (8 bytes) 
    char currency = '$'; // char = single character (1 byte)
    char name[] = "Leo"; // char[] = array of characters (size varies)
    printf("%d \n", age); // %d stands for integer
    printf("%f \n", price); // %f stands for float
    printf("%lf \n", pi); // %lf stands for double (use lf for double)
    printf("%c \n", currency); // %c stands for character
    printf("%s \n", name); // %s stands for string

    int num1 =1;
    int num2= 10;
    int num3 = 100;
     printf("%3d\n", num1);
    printf("%3d\n", num2);// the number 3 specifies the minimum numbers of characters to print
    printf("%3d\n", num3);



   

    return 0;
}