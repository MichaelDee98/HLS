#include <stdlib.h>     /* srand, rand */
#include <time.h> 

#include "ac_channel.h"
#include "ac_int.h"

typedef ac_int<4,false> Card;

class BlackJack{
private :
    //internal state
    ac_int<4,false> cnt, count_card;
    ac_int<5,false> res;
    Card card;

public :
    // constructor-init internal state
    BlackJack() {cnt = 0; count_card = 0; res = 0; }


    void run(ac_channel<Card> &in_card, bool &end_round, bool &win){

        if(in_card.available(1) && end_round == 0){
            card = in_card.read();
            cnt++;
            if(card > 1){
                res +=card;
            } else {
                res += 11;
            }

            if(res > 21){
                //std::cout<<"res > 21"<<std::endl;
                win = 0;
                end_round = 1;
            } else if (res == 21){
                //std::cout<<"res == 21"<<std::endl;
                win = 1;
                end_round = 1;
            } else if (res == 22 && cnt == 2){
                //std::cout<<"res == 22 && cnt == 2"<<std::endl;
                win = 1 ;
                end_round = 1;
            }else if(res < 21 && cnt == 5){
                //std::cout<<"res < 21 && cnt == 5"<<std::endl;
                win = 1;
                end_round = 1;
            }else {
                //std::cout<<"else"<<std::endl;
                win = 0;
                end_round = 0;
            }

            if(cnt == 5){
                end_round = 1;
            }
            std::cout<<"res "<<res<<std::endl;
            std::cout<<"win "<<win<<std::endl;
            std::cout<<"end_round "<<end_round<<std::endl;
        }

    }
};


int main(){
    int v1;
    bool end_round = 0, win = 0;
    ac_channel<Card> in_card;

    BlackJack game;


    srand(time(NULL));
    
    for (int i = 0; i < 5; i++){
        v1 = rand()% 9 + 1;
        std::cout<<"card "<<v1<<std::endl;
        in_card.write(v1);
    }

    for (int i = 0; i < 5; i++){
        game.run(in_card, end_round, win);
    }

    return 0;
}