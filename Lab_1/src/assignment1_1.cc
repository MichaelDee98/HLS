#include <iostream>
#include <ctime>
#include <cstdlib>



unsigned short int count_ones(unsigned int input_number){
    unsigned short int counter = 0;
    std::cout << "input number = " << input_number <<std::endl;
    int res;

    for (int i = 31; i >= 0; i--){
        res = input_number >> i;
        if (res&1){
            counter = counter + 1;
        }

    }
    return(counter);
}




int main(){
    unsigned short int ones;

    std::srand(std::time(NULL));
    
    ones = count_ones(std::rand());
    std::cout<< ones;


    return 0;
}