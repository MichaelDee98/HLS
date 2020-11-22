#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


// Generating a BFS list 
void BFS_list(bool A[][6],int (&queue)[6]){
    bool visited[6]={1,0,0,0,0,0};
    
    int index =0;
    int queue_index = 0;
    queue[index]=0;
    index++;
    for(int i = queue[queue_index] ; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(A[i][j]==1 && visited[j]!=1){
                //std::cout<<"Found v on "<<j<<std::endl;
                queue[index]=j;
                index++;
                visited[j]=1;
                //for(int i=0 ;i<6;i++){
                // std::cout<<visited[i];}
                // std::cout<<std::endl;
            }
            
        } 
        queue_index++;
    }

    std::cout<<"Initiating queue ";
    for(int i=0 ;i<6;i++){
    std::cout<<queue[i];}  
    std::cout<<std::endl;

}

// Examining if the chosen color for the node is valid
void safe_coloring(bool A[][6],int (&color_table)[6],int node, int j){
    
    color_table[j]=color_table[j]+1;
    for(int i = 0; i < 6; i++){
        //std::cout<<"Examining node "<<i<<std::endl;
        if(A[j][i]==1 && color_table[j]==color_table[i]){
            std::cout<<"Backtracking"<<std::endl;
            safe_coloring(A,color_table,node,j);
        }
    }
}

// Top module
void coloring(bool A[][6], int (&queue)[6], int (&color_table)[6]){ 

    BFS_list(A,queue);

    for(int i = 0;i < 6;i++){
        std::cout<<"Visiting node "<<queue[i]<<std::endl;
        for(int j = queue[i]; j < 6 ; j++){
            if(A[queue[i]][j]==1 && color_table[queue[i]]==color_table[j]){
               // std::cout<<"At E between  "<<queue[i]<<" and "<<j<<", "<<queue[i]<<" has "<<color_table[queue[i]]<<" and "<<j<<" has "<<color_table[j]<<std::endl;
                safe_coloring(A,color_table,queue[i],j);
                //std::cout<<"After, "<<j<<" has "<<color_table[j]<<std::endl;
            }  
        }
    }

    for(int i=0 ;i<6;i++){
   std::cout<<color_table[i];}


}




int main(){
    srand(time(NULL));
    bool visited[6]={0,0,0,0,0,0};
    int queue[6]={0,0,0,0,0,0};
    int color_table[6] = {1, 1, 1, 1, 1, 1};
    bool Adj_G[6][6];

    // Random graph
    for(int i = 0;i < 6;i++){
        Adj_G[i][i]=0;
        for(int j = i+1 ; j < 6 ; j++){
            Adj_G[i][j]=rand()&1;
            Adj_G[j][i]=Adj_G[i][j];
        }
    }
    // Printint graph
    std::cout<<"Graph Adj Matrix"<<std::endl;
    for(int i = 0;i < 6;i++){
        for(int j = 0 ; j < 6 ; j++){
        std::cout<<Adj_G[i][j]<<", ";
        }
        std::cout<<std::endl;
    }

    /*bool Adj_G[6][6] = {0, 1, 0, 0, 1, 1,
                          1, 0, 1, 0, 0, 1, 
                          0, 1, 0, 1, 0, 0,
                          0, 0, 1, 0, 1, 0,
                          1, 0, 0, 1, 0, 1,
                          1, 1, 0, 0, 1, 0 };
    */

    
    coloring(Adj_G,queue,color_table);


    return 0;
}