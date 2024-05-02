#include "tic-tac-toe.hpp"
int main(){
  while(true){
    TTTStruct p1,p2;
    choose_characters(p1,p2);
    TTTBoard tttb(9,TTTStruct()); //Fill the board with spaces (Or TTTStruct())
    while(true){
      while(player_move(p1,tttb)){};
      if(someone_won(tttb)) break;
      while(player_move(p2,tttb)){};
      if(someone_won(tttb)) break;
    }
    while(true){
      switch(play_again()){
        case PlayAgain::No: goto no;
        case PlayAgain::Yes: goto yes;
        case PlayAgain::Invalid:;
      }
    }
    yes:;
  }
  no:;
}