#include "ac_int.h"

template <int W>
void csd_encode(ac_int<W,true> &num, ac_int<W,false> &x_p, ac_int<W,false> &x_m){
    ac_int<1,false> carry = 0;
    ac_int<2,false> sliced ;
    ac_int<W,false> intermediate;
    x_p = 0;
    x_m = 0;

    for (int i = 0; i < W-1; ++i){
        sliced = num.template slc<2>(i);
        // std::cout<<"sliced value : " <<sliced<<std::endl;
        if(!carry){
            switch (sliced)
            {
            case 1:
                // std::cout<<"inside case 1" <<std::endl;
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
                // std::cout<<"inside case default" <<std::endl;
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
                // std::cout<<"inside case 2" <<std::endl;
                carry = 1;
                x_p[i] = 0;
                x_m[i] = 1;
                break;            
            default:
                // std::cout<<"inside case default carry=1" <<std::endl;
                carry = 1;
                x_p[i] = 0;
                x_m[i] = 0;            
                break;
            }
        }
    }
    std::cout<<"x_p = "<<x_p<<std::endl;
    std::cout<<"x_m = "<<x_m<<std::endl;

}

template <int W>
ac_int<W,true> csd_mult(ac_int<W,true> &in, ac_int<W,false> &x_p, ac_int<W,false> &x_m){
    ac_int<W,true> result = 0 ;
    ac_int<W,false> shift ;

    for(int i = 0; i < W; i++){
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


    ac_int<BITS,false> x_m, x_p;
    ac_int<BITS,true> result;
    ac_int<BITS,true> word_to_encode=(-2^(BITS-1))+rand()%(((2^(BITS-1))-1)+2^(BITS-1) + 1);
    ac_int<BITS,true> constant =(-2^(BITS-1))+rand()%(((2^(BITS-1))-1)+2^(BITS-1) + 1); 

    std::cout<<"word_to_encode "<<word_to_encode<<std::endl;
    std::cout<<"constant "<<constant<<std::endl;

    csd_encode<BITS>(word_to_encode,x_m,x_p);
    result = csd_mult<BITS>(constant,x_m,x_p);
    std::cout<<"mul result : "<<result<<std::endl;



    return 0;
}