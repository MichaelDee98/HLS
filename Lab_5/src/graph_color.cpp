#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


#include "ac_int.h"



void coloring(ac_int<6,false> A[6],ac_int<3,false> color_table[6],ac_int<3,false> &color_used){
    ac_int<6,false> temp ;
    
    for(int i = 0; i < 6; i++){
        temp=A[i];
        //std::cout<<"row no. "<<i<<std::endl;
        for(int j = 0; j < 6; j++){
             //std::cout<<" "<<temp[j]<<" ";
            if(temp[j]==1 && color_table[i]==color_table[j]){
                color_table[j]=color_table[j]+1;
            }
            color_used =(color_table[j]>color_used)?color_table[j]:color_used;
        }
        //std::cout<<std::endl;
    } 

}







int main(){
    srand(time(NULL));
    ac_int<3,false> color_used=0 ;
    ac_int<3,false> color_table[6] = {1, 1, 1, 1, 1, 1};
    ac_int<6,false> Adj_G[6] ;
    /*// Random graph
    for(int i = 0;i < 6;i++){
        Adj_G[i][i]=0;
        for(int j = i+1 ; j < 6 ; j++){
            Adj_G[i][j]=rand()&1;
            Adj_G[i][j]=Adj_G[j][i];
        }
    }

    // Printing graph
    std::cout<<"Graph Adj Matrix"<<std::endl;
    for(int i = 0;i < 6;i++){
        for(int j = 0 ; j < 6 ; j++){
        std::cout<<Adj_G[i][j]<<", ";
        }
        std::cout<<std::endl;
    }

    */
    Adj_G[0]=19;
    Adj_G[1]=41;
    Adj_G[2]=20;
    Adj_G[3]=10;
    Adj_G[4]=37;
    Adj_G[5]=50;
    
    /*for(int i = 0; i<6; i++){
        std::cout<<Adj_G[0][i];

    }*/
    
    /*bool Adj_G[6][6] = { 0, 1, 0, 0, 1, 1,
                           1, 0, 1, 0, 0, 1, 
                           0, 1, 0, 1, 0, 0,
                           0, 0, 1, 0, 1, 0,
                           1, 0, 0, 1, 0, 1,
                           1, 1, 0, 0, 1, 0 };*/

    
    coloring(Adj_G,color_table,color_used);
    std::cout<<"Color table ";
    for(int i=0;i<6;i++){
        std::cout<<color_table[i];
    }
    std::cout<<std::endl;
    std::cout<<"Max number of colors "<<color_used<<std::endl;
    return 0;
}