#include <iostream>
#include <ctime>

#define N 200
#define M 200

void median(short img[N][M], short out[N][M], short p[5] ){
    ROW:for(int i = 0; i < N; i++){
        COL:for(int j = 0; j < 10; j++){
            if(j==0){
                p[0]=0;
                p[1]=0;
                p[2]=img[i][0];
                p[3]=img[i][1];
                p[4]=img[i][2];
                out[i][0]=(p[0]+p[1]+p[2]+p[3]+p[4])/5;
            }else{
                out[i][0]=(p[0]+p[1]+p[2]+p[3]+p[4])/5;
            }
            p[0] = p[1];
            p[1] = p[2];
            p[2] = p[3];
            p[3] = p[4];
            p[4] = (j<M-3)?img[i][j+3]: 0;
        }
    }
}





int main(){
    short img[N][M];
    short out[N][M];
    short p[5];

    std::srand(std::time(NULL));
    std::cout<<"Image"<<std::endl;
    // Fill the img array
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 10; j++){
            img[i][j]=rand()%10; // Filling the array with values between 0-255
            std::cout<<" "<<img[j]<<" ";
        }
        std::cout<<std::endl;
    }

    median(img, out, p);

    return 0 ;
}