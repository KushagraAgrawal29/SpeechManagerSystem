#include <iostream>
#include "speechManager.h"
using namespace std;

int main(int argc, char const *argv[])
{
    speechManager sm;
    sm.showMenu();  
    
    while (1)
    {
        cout << "Please enter your choice" << endl;
        int choice;
        cin >> choice;
        switch (choice)
        {
            case 0:     // Exit system
                sm.exitSys();
                break;
            case 1:
                sm.startCompetition();  // Start the game
                return 0;
            case 2:
                sm.loadRecord();
                break;
            case 3:
                sm.clearFile(); // Clear data
                break;
            default:
                break;
        }
    }    
    return 0;
}
