#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "ac_channel.h"
#include "ac_int.h"

typedef ac_int<4,false> dtype;

class RunLengthEncode{
private:
    // internal state
    dtype input_number, prev_num;
    ac_int<7,false> countnum, count ;

public:
    // constructor- init internal state
    RunLengthEncode(){count = 0 ; countnum = 0;}
    //top-level interface
    void run (ac_channel<dtype> &in, ac_channel<dtype> &out)
    {   
        if(in.available(1)){
            count += 1; 
            //std::cout<<"count "<<count<<std::endl;                // counting inputs from FIFO
            input_number = in.read();   // reading input number
            if(count == 1) {
                // only for the first number
                countnum += 1;
                prev_num = input_number;
            }else {
                if(input_number==prev_num){
                    // counting repeated numbers
                    countnum+=1; }
                else{
    /* when the number is changing first we write the number and the number of appearance
        and then we set the countnum = 1 for the first appearance of the different number  */
                    out.write(prev_num);
                    out.write(countnum);
                    countnum = 1 ;
                    prev_num = input_number;
                } 
                if(count == 10){
                    //std::cout<<"input number "<<input_number<<std::endl;
                    //std::cout<<"countnum "<<countnum<<std::endl;
                    out.write(input_number);
                    out.write(countnum);
                }  

            }
                
        }
    }
};


int main(){
    int v1, v2, i;
    ac_channel<ac_int<4,false> > in;
    ac_channel<ac_int<4,false> > out;

    srand(time(NULL));
    
    RunLengthEncode runlength;

    // random input number generation and random appearance number
    for (int j = 0; j < 10; j=j+i){
        v2 = rand()% 3 + 1;
        v1 = rand() % 15;
        i = 1;
        if(v2 + j < 10) {
            for (i = 0; i < v2; i++){
                in.write(v1);
                std::cout << "writing " << v1 << std::endl;
            }
        } 
        else{
            in.write(v1);
            std::cout << "writing " << v1 << std::endl;
                
        } 
    }

    for(int i = 0; i < 10; i++){
        runlength.run(in, out);
        
    }

    std::cout<<std::endl<<"emptying stream" << std::endl;
    
    do{
        std::cout<<out.read()<<std::endl;
    }while(out.available(1));

    return 0;
}