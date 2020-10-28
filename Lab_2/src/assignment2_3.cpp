#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "ac_channel.h"
#include "ac_int.h"

void runlength_encode(ac_channel<ac_int<4,false> > &in, ac_channel<ac_int<4,false> > &out){

    ac_int<4,false> input_number, nxt_num;
    ac_int<7,false> count = 0;

    if(in.available(10)){
        input_number = in.read();
        count += 1;
        for(int i = 1; i < 10; i++){
            nxt_num = in.read();
            if(input_number==nxt_num){
                count+=1;
            } else {
                out.write(input_number);
                out.write(count);
                input_number=nxt_num;
                count = 1;
            } 
        }
        out.write(nxt_num);
        out.write(count);
    }

}





int main(){
    int v1, v2, i;
    ac_channel<ac_int<4,false> > in;
    ac_channel<ac_int<4,false> > out;

    srand(time(NULL));
    

    for (int j = 0; j < 10; j=j+i){
        v2 = rand()% 3 + 1;
        v1 = rand() % 15;
        if(v2 + j < 10) {
            for (i = 0; i < v2; i++){
                in.write(v1);
                std::cout << "writing " << v1 << std::endl;
                runlength_encode(in,out);
            }
        } 
        else {
                in.write(v1);
                std::cout << "writing " << v1 << std::endl;
                runlength_encode(in,out);
        }
        
        
    }

    std::cout<<std::endl<<"emptying stream" << std::endl;
    
    do{
        std::cout<<out.read()<<std::endl;

    }while(out.available(1));
    return 0;
}


