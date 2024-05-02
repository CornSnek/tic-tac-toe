#include "tic-tac-toe.hpp"
std::ostream& operator<<(std::ostream& o,const TTTStruct& tttstruct){
  o<<"\x1b["<<std::to_string(static_cast<int>(tttstruct.color))<<";1m";
  switch(tttstruct.type){
    case TTTType::NONE: o<<' '; break;
    case TTTType::X: o<<'X'; break;
    case TTTType::O: o<<'O';
  }
  o<<"\x1b[0m";
  return o;
}
#define TTTColorNamePrint(Color) case TTTColor::Color: return #Color;
const char* print_tttcolor(TTTColor tttcolor){
  std::cout<<"\x1b["<<std::to_string(static_cast<int>(tttcolor))<<";1m";
  switch(tttcolor){
    TTTColorNamePrint(Black)
    TTTColorNamePrint(Red)
    TTTColorNamePrint(Green)
    TTTColorNamePrint(Yellow)
    TTTColorNamePrint(Blue)
    TTTColorNamePrint(Magenta)
    TTTColorNamePrint(Cyan)
    TTTColorNamePrint(White)
    default: return "INVALID COLOR";
  }
}
#define PrintChooseColorsColor(num,Color)\
std::cout<<"\x1b[0m"<<num<<") "<<print_tttcolor(TTTColor::Color)<<std::endl
void print_choose_colors(){
  PrintChooseColorsColor(1,Black);
  PrintChooseColorsColor(2,Red);
  PrintChooseColorsColor(3,Green);
  PrintChooseColorsColor(4,Yellow);
  PrintChooseColorsColor(5,Blue);
  PrintChooseColorsColor(6,Magenta);
  PrintChooseColorsColor(7,Cyan);
  PrintChooseColorsColor(8,White);
  std::cout<<"\x1b[0m";
}
void choose_characters(TTTStruct& p1,TTTStruct& p2){
  p1.player=1;
  p2.player=2;
  while(true){
    std::cout<<"Player 1, choose X/x or O/o"<<std::endl;
    std::string input;
    std::cin>>input;
    if(input.size()!=1){
      std::cout<<"Invalid string '"<<input<<"'."<<std::endl;
      continue;
    }
    if(tolower(input[0])=='o'){
      p1.type=TTTType::O;
      p2.type=TTTType::X;
      break;
    }else if(tolower(input[0])=='x'){
      p1.type=TTTType::X;
      p2.type=TTTType::O;
      break;
    }else std::cout<<"Invalid character '"<<input<<"'."<<std::endl;
  }
  player_choose_color(1,p1);
  player_choose_color(2,p2);
}
void player_choose_color(int p_number,TTTStruct& p){
  while(true){
    std::cout<<"Player "<<p_number<<": Choose your color"<<std::endl;
    print_choose_colors();
    std::string input;
    std::cin>>input;
    if(input.size()!=1){
      std::cout<<"Invalid string '"<<input<<"'."<<std::endl;
      continue;
    }
    switch(input[0]){
      case '1': p.color=TTTColor::Black; goto done; //Break outside the while(true) loop because switch considers break; as breaking out of switch(input).
      case '2': p.color=TTTColor::Red; goto done;
      case '3': p.color=TTTColor::Green; goto done;
      case '4': p.color=TTTColor::Yellow; goto done;
      case '5': p.color=TTTColor::Blue; goto done;
      case '6': p.color=TTTColor::Magenta; goto done;
      case '7': p.color=TTTColor::Cyan; goto done;
      case '8': p.color=TTTColor::White; goto done;
      default: std::cout<<"Invalid color!"<<std::endl;
    }
  }
  done:;
}
void print_board(const TTTBoard& tttb){
  std::cout<<tttb[0]<<'|'<<tttb[1]<<'|'<<tttb[2]<<std::endl;
  std::cout<<"-+-+-"<<std::endl;
  std::cout<<tttb[3]<<'|'<<tttb[4]<<'|'<<tttb[5]<<std::endl;
  std::cout<<"-+-+-"<<std::endl;
  std::cout<<tttb[6]<<'|'<<tttb[7]<<'|'<<tttb[8]<<std::endl;
}
void print_valid_moves(const TTTBoard& tttb,std::vector<int>& valid_moves){
  //This macro either prints a number and places the number in the valid_moves vector, or it only places the occupied X/O by a player.
  #define XOOrNum(num) if(tttb[num].player==0){ std::cout<<num+1; valid_moves.push_back(num); }else std::cout<<tttb[num];
  XOOrNum(0); std::cout<<'|'; XOOrNum(1); std::cout<<'|'; XOOrNum(2); std::cout<<std::endl;
  std::cout<<"-+-+-"<<std::endl;
  XOOrNum(3); std::cout<<'|'; XOOrNum(4); std::cout<<'|'; XOOrNum(5); std::cout<<std::endl;
  std::cout<<"-+-+-"<<std::endl;
  XOOrNum(6); std::cout<<'|'; XOOrNum(7); std::cout<<'|'; XOOrNum(8); std::cout<<std::endl;
}
bool player_move(TTTStruct& p,TTTBoard& tttb){
  std::vector<int> valid_moves;
  std::cout<<"Player "<<p.player<<" ("<<p<<") it's your turn."<<std::endl;
  print_valid_moves(tttb,valid_moves);
  std::string input;
  std::cin>>input;
  if(input.size()!=1){
    std::cout<<"Invalid string '"<<input<<"'."<<std::endl;
    return true;
  }
  int input_as_num;
  //Subtract input by '0' to convert to input_as_num. 1 is subtracted because we're inputting for 1 to 9 instead of 0 to 8 (For tttb).
  input_as_num=input[0]-'0'-1;
  bool is_valid=false;
  for(size_t i=0;i<valid_moves.size();i++){ //Search all valid input numbers to make is_valid true.
    if(valid_moves[i]==input_as_num){
      is_valid=true;
      break;
    }
  }
  if(!is_valid) std::cout<<'\''<<input<<"' is an invalid move!"<<std::endl;
  else tttb[input_as_num]=p;
  return !is_valid;
}
const std::array<std::array<size_t,3>,8> WinIndicesArray{std::array<size_t,3>{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
bool someone_won(const TTTBoard& tttb){
  for(const auto& tttstruct:tttb) if(tttstruct.player==0) goto no_tie_yet;
  print_board(tttb);
  std::cout<<"It's a tie!"<<std::endl;
  return true;
  no_tie_yet:
  for(const auto& wi:WinIndicesArray){
    int this_player_num;
    bool player_num_b=false;
    for(size_t i=0;i<3;i++){
      //Player 0 is space.
      if(tttb[wi[i]].player==0) goto no_match;
      //If player has been matched, and is the same player.
      else if(player_num_b&&this_player_num!=tttb[wi[i]].player) goto no_match;
      this_player_num=tttb[wi[i]].player;
      player_num_b=true;
    }
    print_board(tttb);
    std::cout<<"Player "<<this_player_num<<" wins!"<<std::endl;
    return true;
    no_match:;
  }
  return false;
}
PlayAgain play_again(){
  std::string input;
  std::cout<<"Play again? 'Y/y' or 'N/n'"<<std::endl;
  std::cin>>input;
  if(input.size()!=1){
    std::cout<<"Invalid string '"<<input<<"'."<<std::endl;
    return PlayAgain::Invalid;
  }
  if(tolower(input[0])=='n') return PlayAgain::No;
  else if(tolower(input[0])=='y') return PlayAgain::Yes;
  else std::cout<<"Invalid character '"<<input<<"'."<<std::endl;
  return PlayAgain::Invalid;
}