#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 




void coloring(bool A[6][6]){
    int color_table[6] = {1, 1, 1, 1, 1, 1};
    int color = 1;



    for(int i = 0;i < 6;i++){

        for(int j = i+1; j < 6 ; j++){
            if(A[i][j]==1 && color_table[i]==color_table[j]){
                color_table[j] = color_table[j] + 1 ;

            } 
        }
    }
    for(int i=0 ;i<6;i++){
    std::cout<<color_table[i];}


}







int main(){
    srand(time(NULL));



    bool Adj_G[6][6] = { 1, 1, 0, 0, 1, 1,
                         1, 1, 1, 0, 0, 1, 
                         0, 1, 1, 1, 0, 0,
                         0, 0, 1, 1, 1, 0,
                         1, 0, 0, 1, 1, 1,
                         1, 1, 0, 0, 1, 1 };


    coloring(Adj_G);



    return 0;
}