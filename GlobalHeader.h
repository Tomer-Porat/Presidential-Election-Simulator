#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "DynamicArray.h"
#include "DistrictHeader.h"
#include "PartyHeader.h"
#include "CitizenHeader.h"
#include "CampaignHeader.h"
constexpr int QUIT{10};
constexpr int MAX_DISTRICTS_POSSIBLE{436};
constexpr int MAX_NAME_LEN{ 100 };
constexpr int DIVIDED{ 0 };
constexpr int UNITED{ 1 };
constexpr int REGULAR{ 0 };
constexpr int SIMPLE{ 1 };
constexpr int LOAD1{ 2 };
constexpr int CREATE{ 1 };
constexpr int EXIT1{ 3 };

enum action {ADD_DISTRICT = 1, ADD_CITIZEN, ADD_PARTY, ADD_REP, DISPLAY_DISTRICTS, DISPLAY_CITIZENS, DISPLAY_PARTIES, VOTE, DISPLAY_RESULTS, EXIT, SAVE, LOAD};
void printMainMenu();
//char* initString(int* stringSize, const char* source);
bool isNumeric(string str);
void printOpening();
void printDistrictListOpener();
void printPartiesListOpener();
void printCastVoteOpener();
void printCitizenListOpener();
void printElectionResultsOpener();