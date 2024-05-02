#include <iostream>
#include <ostream>
#include <vector>
#include <array>
#include <string>
#include <cctype>
///ANSI terminal color based from https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
enum class TTTColor{
  Black=30,Red,Green,Yellow,Blue,Magenta,Cyan,White
};
enum class TTTType{
  NONE,X,O
};
struct TTTStruct{
  TTTType type;
  TTTColor color;
  int player;
  TTTStruct():type(TTTType::NONE),color(TTTColor::White),player(0){}
};
enum class PlayAgain{
  No, Yes, Invalid
};
using TTTBoard=std::vector<TTTStruct>;
///To print TTTStruct with std::cout, involving X or O, and terminal color.
std::ostream& operator<<(std::ostream& o,const TTTStruct& tttstruct);
void choose_characters(TTTStruct& p1,TTTStruct& p2);
void player_choose_color(int p_number,TTTStruct& p);
void print_board(const TTTBoard& tttb);
void print_valid_moves(const TTTBoard& tttb,std::vector<int>& valid_moves);
///bool represents whether it should continue the loop due to invalid input (true) or is valid input (false).
bool player_move(TTTStruct& p,TTTBoard& tttb);
///bool represents whether there is a 3-in-a-row or tie due to no more space (true) or there is nothing (false).
bool someone_won(const TTTBoard& tttb);
PlayAgain play_again();