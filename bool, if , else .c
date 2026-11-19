#include <stdio.h>
#include <stdbool.h> // bool = true or false (1 or 0) 
                     // stdbool.h is a header file that defines the boolean data type in C. It provides the bool type and the constants true and false.


int main() {
    // variable = A reusable container for storing data
    //Behaves as if it were the vale it contains

    bool isOnline = true; //you can also use 0-1 for false-true
    bool isStudent = true;
    bool forSale = false;
    if(isOnline){
        printf("you are ONLINE \n");
    }
    else {
        printf("you are OFFLINE \n");
    }

     if(isStudent){
        printf("you are a Student \n");
    }
    else {
        printf("you are not a Student \n");
    }
 if(forSale){
        printf("that item is for sale \n");
    }
    else {
        printf("that item is not for sale \n");
    }


    return 0;
}

    // variable = A reusable container for storing data
    //            Behaves as if it were the vale it contains