#include <bitset>

#include "ac_int.h"

template <int W>
void csd_encode(ac_int<W,true> &num, ac_int<(W+1),false> &x_p, ac_int<(W+1),false> &x_m){
    ac_int<1,false> carry = 0;
    ac_int<2,false> sliced ;
    ac_int<W,false> intermediate;
    ac_int<W+1,false> input_num=0;
    if(num>=0){
    input_num=num;
    //std::cout<<"input num "<<input_num<<std::endl;
    input_num[W]=num[W-1];
    //std::cout<<"input num "<<input_num<<std::endl;
    }else{
        input_num=num;
    }
    x_p = 0;
    x_m = 0;
    
    for (int i = 0; i < W-1; ++i){
        sliced = input_num.template slc<2>(i);
        //std::cout<<"sliced value : " <<sliced<<std::endl;
        if(!carry){
            switch (sliced)
            {
            case 1:
                //std::cout<<"inside case 1" <<std::endl;
                carry = 0;
                x_p[i] = 1;
                x_m[i] = 0;
                break;
            case 3:
               // std::cout<<"inside case 3" <<std::endl;
                carry = 1;
                x_p[i] = 0;
                x_m[i] = 1;
                break;            
            default:
                //std::cout<<"inside case default" <<std::endl;
                carry = 0;
                x_p[i] = 0;
                x_m[i] = 0;            
                break;
            }

        } else {
            switch (sliced)
            {
            case 0:
                //std::cout<<"inside case 0" <<std::endl;
                carry = 0;
                x_p[i] = 1;
                x_m[i] = 0;
                break;
            case 2:
                //std::cout<<"inside case 2" <<std::endl;
                carry = 1;
                x_p[i] = 0;
                x_m[i] = 1;
                break;            
            default:
                if(i==W-1 && sliced==3){
                    //std::cout<<"inside case default carry=1" <<std::endl;
                    carry = 1;
                    x_p[i] = 0;
                    x_p[i+1] = 1;
                    x_m[i-1] = 1;
                    break;
                } else {
                    carry = 1;
                    x_p[i] = 0;
                    x_m[i] = 0;           
                    break;
                
                }
            }
        }
    }
    
    
    std::bitset<W+1> x(x_p);
    std::bitset<W+1> y(x_m);
    std::cout<<"x_m = "<<x_m<<std::endl;
    std::cout<<"x_p = "<<x_p<<std::endl;
}

template <int W>
ac_int<W+1,true> csd_mult(ac_int<W,true> &in, ac_int<W+1,false> &x_p, ac_int<W+1,false> &x_m){
    ac_int<W+1,true> result = 0 ;
    ac_int<W+1,false> shift ;

    for(int i = 0; i < W+1; i++){
        //std::cout<<"iteration "<<i<<std::endl;
        if (x_p[i]==1){
            shift = in<<i; 
            result = result + shift;
        } else if(x_m[i]==1){
            shift = in<<i; 
            result = result - shift;
        }
    }
    return result;
}




int main() {
    const int BITS = 32;
    srand(time(NULL));


    ac_int<BITS+1,false> x_m, x_p;
    ac_int<2*BITS,true> result = 0;
    ac_int<BITS,true> word_to_encode=(-2^(BITS-1))+rand()%(((2^(BITS-1))-1)+2^(BITS-1) + 1);
    ac_int<BITS,true> constant =(-2^(BITS-1))+rand()%(((2^(BITS-1))-1)+2^(BITS-1) + 1); 

    std::cout<<"word_to_encode "<<word_to_encode<<std::endl;
    std::cout<<"constant "<<constant<<std::endl;

    csd_encode<BITS>(word_to_encode,x_m,x_p);
    result = csd_mult<BITS>(constant,x_m,x_p);
    std::cout<<"mul result : "<<result<<std::endl;



    return 0;
}