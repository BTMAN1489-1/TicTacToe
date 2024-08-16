#include<iostream>
#include<stdio.h>
#include<string>
#include<climits>

#ifndef _WIN32
#include<unistd.h>
#define CommandClearTerminal "clear"
#define SLEEP(A) (usleep((A)*1000))
#else
#include <windows.h>
#define CommandClearTerminal "cls"
#define SLEEP(A) (Sleep((A)))
#endif

using namespace std;

#define EMPTY_CHAR '_'
#define USER_CHAR 'X'
#define AI_CHAR 'O'

#define IOError -1
#define OK 0

#define MaxLengthNotation 1
#define TimeInterval 60
#define LengthTable 3
#define LevelLow 0.8 * LengthTable
#define LevelMedium LengthTable
#define LevelHard INT_MAX