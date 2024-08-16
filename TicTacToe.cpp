#include "dependencies.h"
#include "PrintTools.hpp"

using namespace std;

int Level = LevelHard;

enum GameState { WIN = 10, LOSE = -10, DRAW = 0, CONTINUE = -1 };

struct cords
{
  int x;
  int y;
};

int getUserCords(cords* userCords)
{
  int status = 0;
  string inputData;
  getline(cin, inputData);
  string X, Y;
  string* buffer = &X;
  for (size_t i = 0; i < inputData.length(); i++)
  {
    if (isdigit(inputData[i]))
        {
          if (buffer->length()>=MaxLengthNotation)
            return IOError;
            
          buffer->push_back(inputData[i]);
        }

    else if(!(buffer->empty()))
    {
    buffer->push_back('\0');
      if (Y.empty())
          buffer = &Y;
      else break;
    }
  }

  if (X.empty() || Y.empty())
    return IOError;

  userCords->x = stoi(X);
  userCords->y = stoi(Y);

  if(userCords->x > 3 || userCords->y > 3)
    return IOError;
  
  (userCords->x)--;
  (userCords->y)--;


  return OK;
}


int getGameState(char Table[LengthTable][LengthTable], char player1, char player2, int count, int weight)
{
  for (size_t i = 0; i < LengthTable; i++)
  {
    if (Table[i][0] == player1 && Table[i][1] == player1 && Table[i][2] == player1 || Table[0][i] == player1 && Table[1][i] == player1 && Table[2][i] == player1)
    {
      return WIN - weight;
    }
    else if (Table[i][0] == player2 && Table[i][1] == player2 && Table[i][2] == player2 || Table[0][i] == player2 && Table[1][i] == player2 && Table[2][i] == player2)
    {
      return LOSE + weight;
    }
  }

  if (Table[0][0] == player1 && Table[1][1] == player1 && Table[2][2] == player1 || Table[0][2] == player1 && Table[1][1] == player1 && Table[2][0] == player1)
  {
      return WIN - weight;
  }
  else if (Table[0][0] == player2 && Table[1][1] == player2 && Table[2][2] == player2 || Table[0][2] == player2 && Table[1][1] == player2 && Table[2][0] == player2)
  {
      return LOSE + weight;
  }

  return count >= 9 ? DRAW : CONTINUE;
}


int minmax(char Table[LengthTable][LengthTable], int depth, bool is_maximazing, int count) {
  int state = getGameState(Table, AI_CHAR, USER_CHAR, count + depth, depth);
  if (state != CONTINUE || depth >= Level) return state;
  int score, best_score;
  if (is_maximazing)
  {
    best_score = INT_MIN;
    for (size_t i = 0; i < LengthTable; i++)
    {
      for (size_t j = 0; j < LengthTable; j++)
      {
        if (Table[i][j] == EMPTY_CHAR) {
          Table[i][j] = AI_CHAR;
          score = minmax(Table, depth + 1, false, count);
          Table[i][j] = EMPTY_CHAR;
          if (score > best_score) {
            best_score = score;
          }
        }
      }
    }
  }
  else
  {
    best_score = INT_MAX;
    for (size_t i = 0; i < LengthTable; i++)
    {
      for (size_t j = 0; j < LengthTable; j++)
      {
        if (Table[i][j] == EMPTY_CHAR) {
          Table[i][j] = USER_CHAR;
          score = minmax(Table, depth + 1, true, count);
          Table[i][j] = EMPTY_CHAR;
          if (score < best_score) {
            best_score = score;
          }
        }
      }
    }
  }
  return best_score;
}


int getAICords(cords* AICords, char Table[LengthTable][LengthTable], int count) {
  int best_score = INT_MIN;
  int score = 0;
  for (size_t i = 0; i < LengthTable; i++) {
    for (size_t j = 0; j < LengthTable; j++)
    {
      if (Table[i][j] == EMPTY_CHAR) {
        Table[i][j] = AI_CHAR;
        score = minmax(Table, 0, false, count + 1);
        Table[i][j] = EMPTY_CHAR;
        if (score > best_score) {
          best_score = score;
          AICords->x = i;
          AICords->y = j;

        }
      }
    }

  }
  return OK;
}


int main()
{
  char Table[LengthTable][LengthTable] = { {}, {}, {} };
  for (size_t i = 0; i < LengthTable; i++)
  {
    for (size_t j = 0; j < LengthTable; j++)
    {
      Table[i][j] = EMPTY_CHAR;
    }
  }

  cords userCords, AICords;
  int count = 0;
  int StateGame;
  system(CommandClearTerminal);
  printMessage("|Welcome to Tic-Tac Toe|\n\r", 1);
  SLEEP(1000);
  printMessage("\n\rPlease, choose a level\n\r", 1);
  printMessage("1)Pussy\n\r2)Human\n\r3)Crazy\n\r\n\r", 0.5);
  int levelNumber;
  cin >> levelNumber;
  cin.ignore(256, '\n');
  switch (levelNumber)
  {
  case 1:
    Level = LevelLow;
    printMessage("Not bad. You're a pussy.", 1);
    SLEEP(1000);
    break;
  case 2:
    Level = LevelMedium;
    printMessage("Good. You're a human.", 1);
    SLEEP(1000);
    break;
  case 3:
    Level = LevelHard;
    printMessage("Perfect. You're a crazy.", 1);
    SLEEP(1000);
    break;
  default:
    printMessage("Bad. You're a dumb.", 1);
    SLEEP(1000);
    return 0;
  }

  while (true)
  {
    printField(Table);
    printMessage("Your step:\t", 1);
    int status = getUserCords(&userCords);

    if (status != OK) {
      printMessage("\n\tBad enter!\n\r", 0.5);
      SLEEP(1000);
      continue;
    }

    if (Table[userCords.x][userCords.y] != EMPTY_CHAR) {
      printMessage("\n\tThe step is already taken.\n\r", 0.5);
      SLEEP(1000);
      continue;
    }

    Table[userCords.x][userCords.y] = USER_CHAR;
    count++;

    StateGame = getGameState(Table, USER_CHAR, AI_CHAR, count, 0);

    printField(Table);

    switch (StateGame)
    {
    case WIN:
      printMessage("\n\rThis game is yours!\n\r", 1);
      return 0;

    case DRAW:
      printMessage("\n\rDraw...\n\r", 1);
      return 0;
    }
    
    getAICords(&AICords, Table, count);
    Table[AICords.x][AICords.y] = AI_CHAR;
    count++;

    StateGame = getGameState(Table, USER_CHAR, AI_CHAR, count, 0);

    printField(Table);

    switch (StateGame)
    {
    
    case LOSE:
    printMessage("\n\rYou lose, loser!!!\n\r", 1);
    while (true)
      printMessage("HA-HA-HA!!!\n\r", 0.3);
      SLEEP(1000);
    return 0;

    case DRAW:
      printMessage("\n\rDraw...\n\r", 1);
      return 0;
    }

  }

  /*
    =================
    |  TIC TAC TOE  |
    =================
    | 1   _  _  _   |
    |        |
    | 2   _  _  _   |
    |        |
    | 3   _  _  _   |
    |        |
    | +   1  2  3   |
    =================

  */
}
