#include "ac_int.h"
#include "ac_fixed.h"


int main(){

    // A //

    ac_int<8,false> a,b;
    ac_int<9,true>  c,d;
    ac_int<18,true> e;

    // maximum value of a and b
    a = 255;
    b = 255; 

    // maximum value of c and d
    c = 255;
    d = 255;

    e = a*b + c*d;
    std::cout<<"e for maximum a,b,c,d : " <<e<<std::endl;

    // maximum value of a and b
    a = 0;
    b = 0;

    // minimum value of d and maximum value of c
    c = 255;
    d = -256;

    e = a*b + c*d;
    std::cout<<"e for maximum c and minimum a,b,d : " <<e<<std::endl;


    // B //

    ac_fixed<5,2,false> f;
    ac_fixed<5,4,true> g;
    ac_fixed<10,6,true> h;

    //Maximum value of f,g
    f = 3.875;
    g = 7.5;

    h = f*g;
    std::cout<<"h for maximum f,g : " <<h<<std::endl;

    //Maximum value of f and minimum value of g
    g = -8;
    h = f*g;
    std::cout<<"h for maximum f and minimum g : " <<h<<std::endl;



    return 0;
}