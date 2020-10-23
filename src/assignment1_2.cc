#include <iostream>
#include <ctime>
#include <cstdlib>

unsigned int checksum(unsigned int input_num, bool reccursive_flag){
    std::cout << "input_num = " << input_num << std::endl;
    std::cout << "reccursive_flag = " << reccursive_flag << std::endl;
    unsigned int remainder = input_num%10;
    unsigned int int_div = input_num/10; 
    unsigned int checksum_value = 0 ;
    unsigned int interm_sum;
    int i;

    for (i=1; int_div>0; i++){
        if(i%2==0 && remainder <= 4 && reccursive_flag == 0){
            checksum_value = checksum_value+remainder*2;
        } else if (i%2==0 && remainder > 4 && reccursive_flag == 0) {
            
            interm_sum=checksum(remainder*2,1);
            std::cout <<"interm_sum = " <<interm_sum<< std::endl;
            checksum_value = checksum_value + interm_sum;

        } else {
            checksum_value = checksum_value+remainder;
        }
        std::cout << "checksum = " << checksum_value<<std::endl;
        std::cout <<"remainder = " << remainder << std::endl; 
        std::cout <<"int_div = " << int_div << std::endl;
        std::cout <<"i = " << i << std::endl;
        remainder = int_div%10;
        int_div = int_div/10; 
        
    }
    std::cout <<"i = " << i << std::endl;
    if(i%2==0 && remainder < 4 && reccursive_flag == 0){
            checksum_value = checksum_value+remainder*2;
        } else if (i%2==0 && remainder > 4 && reccursive_flag == 0) {
            
            interm_sum=checksum(remainder*2,1);
            std::cout <<"interm_sum = " <<interm_sum<< std::endl;
            checksum_value = checksum_value + interm_sum;

        } else {
            checksum_value = checksum_value+remainder;
        }

    std::cout << "checksum = " << checksum_value<<std::endl;
    return checksum_value;
}




int main(){
    unsigned int checksum_output;
    std::srand(std::time(NULL));

    checksum_output = checksum(std::rand(),0);
    std::cout<< checksum_output;

    return 0;
}
