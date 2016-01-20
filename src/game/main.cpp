//
// main.cpp for gomoku in /home/guiz/School/rendu/gomoku/src/
//
// Made by Guiz
// Login   <briard_g@epitech.eu>
//
// Started on  Thu Dec  3 17:15:18 2015 Guiz
// Last update Thu Dec  3 17:16:41 2015 Guiz
//

#include "Board.hh"
#include "GameEngine.hh"
#include "Heuristic.hh"

#ifdef _DEBUG
#include <iomanip>

/*
** No comments, it helps a lot */
void  printInfluencialGOBAN(std::array<Heuristic::Cell, 361>& goban, int const& playerInfluence)
{
  Heuristic::influence  tab[361];
  std::string s[7] = {"\033[0m", "\033[031m", "\033[032m", "\033[033m", "\033[034m", "\033[035m", "\033[037m"};
  for (int y = 0; y < 19; y++)
    for (int x = 0; x < 19; x++)
      tab[y * 19 + x] = Heuristic::decryptData(Heuristic::mesureInfluence(x, y, goban));

  std::cout << std::endl  << s[playerInfluence] << "Influencial Map of actual GOBAN state for PLAYER  " << playerInfluence << s[0] << std::endl << std::endl;
  for (int x = 0; x < 19; x++)
    std::cout << std::setw(9) << x << "   ";
  std::cout << std::endl << std::endl;
  for (int y = 0; y < 19; y++)
    {
      for (int i = 0; i < 3; i++)
      {
        if (i == 1) std::cout << std::setw(3) << y << " "; else std::cout << "    ";
        for (int x = 0; x < 19; x++)
        {
          int  cellValue = goban[POS(x, y)] & 0x07;
          int  cellColor = cellValue;
          if (cellColor == 0)
            for (int k = 0; k < 8; k++)
              {
                int maxStreak = (tab[y * 19 + x].paths[k] >> (4 * (playerInfluence - 1))) & 0x07;
                cellColor = (cellColor > maxStreak ? cellColor : maxStreak);
                if (cellColor == 4)
                  break;
              }
          else cellColor = cellValue;
          for (int j = 0; j < 3; j++)
              {
                if (i != 1 || j != 1)
                {
//                  int index = i * 3 + j;
                 int cellV = (int)((tab[y * 19 + x].paths[(i * 3 + j) >= 4 ? (i * 3 + j -1) : (i * 3 + j) ]) >> (4 * (playerInfluence - 1))) & 0x07;
                 std::cout <<  s[cellValue > 0 ? cellValue : (cellColor == 0 ? 0 : cellColor +  2)] << "[" << cellV << "]"<< s[0];
//                  std::cout <<  s[cellValue > 0 ? cellValue : (cellColor == 0 ? 0 : cellColor +  2)] << "[" << (((int)tab[y * 19 + x].paths[index]) >> 4) << "]"<< s[0];
                }
                else
                  std::cout <<  s[cellValue] << "[" << cellValue  << "]"<< s[0];
              }
            std::cout << "   ";
        }
        std::cout << std::endl;
      }
    std::cout << std::endl;
    }
  std::cout << std::endl;
}

#endif /* _DEBUG */


int main() {

  Board obj;

  GameEngine    engine(obj);

#ifdef _DEBUG
  std::array<Heuristic::Cell, 361> goban = {0};

  goban[POS(8, 8)] = 1;
  goban[POS(0, 0)] = 1;
  goban[POS(1, 1)] = 1;
  goban[POS(2, 6)] = 1;
  goban[POS(3, 3)] = 1;
  goban[POS(4, 4)] = 1;
  goban[POS(5, 5)] = 1;
  goban[POS(15, 6)] = 1;
  goban[POS(6, 6)] = 1;
  goban[POS(2, 3)] = 1;
  goban[POS(15, 15)] = 1;
  goban[POS(15, 18)] = 1;
  goban[POS(12, 5)] = 2;
  goban[POS(5, 13)] = 2;
  goban[POS(13, 13)] = 2;
  goban[POS(6, 14)] = 2;
  goban[POS(2, 18)] = 2;
  goban[POS(14, 15)] = 2;
  goban[POS(15, 18)] = 2;
  goban[POS(15, 6)] = 1;
  goban[POS(6, 8)] = 1;
  goban[POS(4, 5)] = 2;
  printInfluencialGOBAN(goban, 1);
  printInfluencialGOBAN(goban, 2);


#endif

  engine.init();
  engine.run();
  return (0);
}
