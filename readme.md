
# The first version of the speech contest management system

### Features
Select the function to be performed numerically:
    0.Exit the administrator program
    1.Start the game
    2.Read past game records  
    3.Delete local record
    

### Main API
private:
    vector<int> vPreContest;    // List of contestants
    vector<int> vFirstGroup;    // List of first group members in the first round
    vector<int> vSecondGroup;   // List of first round and second group members
    vector<int> vIntermediaryHeat;  // Second round personnel list
    vector<int> vVictory;   // Final list of winners
    map<int, Competitor> mSpeaker;  // Store participant ID and personnel information
    int competitorNum;  // Number of participants
    int turn;   // Game rounds
    bool fileIsEmpty;   // Whether the data file is empty
    map<int, vector<string> > m_Record;     // Store data read from the file

    void getCompetitorNum();    // Get the number of participants
    void test();
    void initSys(); // system initialization
    void createCompetitor();    // Create an participating employee
    void drawLosts();   // First round draw
    void getKeyboard(); // Wait for keyboard input
    double computeScore(); // Calculate score
    void giveAMark(vector<int> & vCP);  // Score
    void printResult(vector<int> & vCP);    // Print results
    void printCompetitorId(vector<int> & vCP);  // Print contestant ID
    void promoted(vector<int> & contestant, vector<int> & vV);  // promotion
    void writeCSV();    // Write to local file and save

public:
    speechManager(/* args */);
    void showMenu();
    void exitSys();
    void startCompetition();
    void loadRecord();
    void clearFile();
    ~speechManager();

