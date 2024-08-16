#include "PrintTools.hpp"


int CountSymbols = 6 + 3 * LengthTable + (1 - LengthTable % 2);

void printMessage(string msg, double speed)
{
    for (size_t i = 0; i < msg.length(); i++)
    {
        printf("%c", msg[i]);

        if (isalpha(msg[i]))
            SLEEP(TimeInterval * speed);

        fflush(stdout);
    }
    
}

static string nstr(string str, unsigned int n)
{
    string result = "";
    while(n--)
        result += str;

    return result;
}

string createHeader()
{
    string result =\
    "\n\r  " + nstr("=",  CountSymbols) + "\n\r" +\
    "  |" + nstr(" ",  (CountSymbols - 11) / 2) + "TIC TAC TOE" + nstr(" ",  (CountSymbols - 11) / 2) + "|\n\r" +\
    "  " + nstr("=",  CountSymbols) + "\n\r";
    return result;
}

string createFooter()
{
    string result = "  | " + nstr(" ", 2 + LengthTable % 2);
    for (size_t i = 0; i < LengthTable; i++)
    {
        result += "  " + (char)(i + 31);
    }
    result += "   |\n\r";
    return result;
}

string createBody(char Table[LengthTable][LengthTable])
{
    string result = "";
    for (size_t i = 0; i < LengthTable; i++)
    {
        result += "  | "s + (char)(i + 31) + nstr(" ", 2 + LengthTable % 2);
        for (size_t j = 0; j < LengthTable; j++)
        {
            result += "  " + Table[i][j];
        }
        result += "   |\n\r";
    }
    return result;
}


void printField(char Table[LengthTable][LengthTable])
{
  system(CommandClearTerminal);
  printf(
    "\n\r  =================\n\r\
  |  TIC TAC TOE  |\n\r\
  =================\n\r\
  | 1   %c  %c  %c   |\n\r\
  |               |\n\r\
  | 2   %c  %c  %c   |\n\r\
  |               |\n\r\
  | 3   %c  %c  %c   |\n\r\
  |               |\n\r\
  | +   1  2  3   |\n\r\
  =================\n\n\r", Table[0][0], Table[0][1], Table[0][2],
    Table[1][0], Table[1][1], Table[1][2],
    Table[2][0], Table[2][1], Table[2][2]
  );
  fflush(stdout);
}