#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <set>
#include <algorithm>
#include <deque>
#include <iomanip>
#include "competitor.h"
using namespace std;

#define COMPETITOELISTPATH "competitorList.txt"

class speechManager
{
private:
    vector<int> vPreContest;    
    vector<int> vFirstGroup;    
    vector<int> vSecondGroup;   
    vector<int> vIntermediaryHeat;  
    vector<int> vVictory;   
    map<int, Competitor> mSpeaker; 
    int competitorNum;  
    int turn;   
    bool fileIsEmpty;   
    map<int, vector<string> > m_Record;     

    void getCompetitorNum();    
    void test();
    void initSys(); 
    void createCompetitor();    
    void drawLosts();   
    void getKeyboard(); 
    double computeScore(); 
    void giveAMark(vector<int> & vCP);  
    void printResult(vector<int> & vCP);    
    void printCompetitorId(vector<int> & vCP);  
    void promoted(vector<int> & contestant, vector<int> & vV);  
    void writeCSV();    

public:
    speechManager(/* args */);
    void showMenu();
    void exitSys();
    void startCompetition();
    void loadRecord();
    void clearFile();
    ~speechManager();
};

class MyCompare
{
public:
    bool operator()(const Competitor &p1, const Competitor &p2)
    {
        return p1.score > p2.score;
    }
};


