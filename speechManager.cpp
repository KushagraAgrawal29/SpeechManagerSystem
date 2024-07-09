#include "speechManager.h"

speechManager::speechManager(/* args */)
{
	this->initSys();
	this->getCompetitorNum();
}

speechManager::~speechManager()
{}

/*******************************************

* Function name: void speechManager::initSys()
* Function: System initialization, initially ensuring that each container is empty
* Parameters: none
* Return value: None
********************************************/
void speechManager::initSys()
{
	// Empty container
	this->vPreContest.clear();  
	this->vIntermediaryHeat.clear();
	this->vVictory.clear();
	this->mSpeaker.clear();
	this->turn = 1;
}

/*******************************************

* Function name: void speechManager::showMenu()
* Function: Display main menu
* Parameters: none
* Return value: None
********************************************/
void speechManager::showMenu()
{
    cout << "********************************************" << endl;
	cout << "*************  Welcome to the speech contest ************" << endl;
	cout << "*************  1.Start a speech contest  *************" << endl;
	cout << "*************  2.View previous records  *************" << endl;
	cout << "*************  3.Clear match record  *************" << endl;
	cout << "*************  0.Exit the competition program  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

/*******************************************
* Function name: void speechManager::exit()
* Function: Exit the system
* Parameters: none
* Return value: None
********************************************/
void speechManager::exitSys()
{
	cout << "Welcome next time" << endl;
	exit(0);
}

/*******************************************
* Function name: void speechManager::getCompetitorNum()
* Function: Get the number of contestants
* Parameters: none
* Return value: None
********************************************/
void speechManager::getCompetitorNum()
{
	ifstream ifs;
	string name;
	int index = 0;
	ifs.open(COMPETITOELISTPATH, ios::in);
	if (!ifs.is_open())
	{
		cout << "getCompetitorNum file generation failed" << endl;
	}
	while (ifs >> name)
	{
		index++;
	}
	this->competitorNum = index;
	ifs.close();
}

/*******************************************
* Function name: test
* Function: test function
* Parameters:
* return value:
********************************************/
void speechManager::test()
{
	this->createCompetitor();
	map<int, Competitor>::iterator pos = mSpeaker.find(10001);
	for (map<int, Competitor>::iterator it = mSpeaker.begin(); it != mSpeaker.end(); it++)
	{
		map<int, Competitor>::iterator pos = mSpeaker.find(it->first);
		if (pos != mSpeaker.end())
		{
			cout << "element found key = " << (*pos).first << " value = " << (*pos).second.name << endl;
		}
		else
		{
			cout << "element not found" << endl;
		}
		cout << endl;	
	}	
	this->drawLosts();
}

/*******************************************
* Function name: void speechManager::createCompetitor()
* Function: Create employees and store employee names and IDs in the map
* Parameters:
* return value:
********************************************/
void speechManager::createCompetitor()
{
	ifstream ifs;
	string name;
	int index = 10001;
	ifs.open(COMPETITOELISTPATH, ios::in);
	if (!ifs.is_open())
	{
		cout << "getCompetitorNum file generation failed" << endl;
	}
	while (ifs >> name)
	{
		this->mSpeaker.insert(pair<int, Competitor>(index, Competitor(name, index)));
		this->vPreContest.push_back(index);
		index++;
	}
	this->competitorNum = index;
	ifs.close();
}

void speechManager::drawLosts()
{
	cout << "No. << " << this->turn << " >> Round contestants are drawing lots"<<endl;
	cout << "---------------------" << endl;
	cout << "The order of speeches after the draw is as follows:" << endl;
	if (turn == 1)
	{
		random_shuffle(vPreContest.begin(), vPreContest.end()); 
		int count = 1;
		bool flag = true;
		cout << "First group of people:";
		for (vector<int>::iterator it = vPreContest.begin(); it != vPreContest.end(); it++)
		{
			if (count <= 6)
			{	
				cout << *it << " ";
				vFirstGroup.push_back(*it);
			}
			else
			{
				if (flag)
				{
					cout << "\nThe second group of people:";
					flag = false;
				}				
				cout << *it << " ";
				vSecondGroup.push_back(*it);
			}
			count++;		
		}
		cout << endl;	
		return;
	}	
}

void speechManager::startCompetition()
{
	system("clear");
	this->createCompetitor();	
	this->printCompetitorId(vPreContest); 
	cout << endl;	  
	this->drawLosts();		
	cout << "------------- No."<< this->turn << "The official round of competition begins:------------- " << endl;
	this->getKeyboard();	
	system("clear");
	cout << "------------- No."<< this->turn << "Round results:------------- " << endl;
	this->giveAMark(vPreContest);		
	cout << "Score of the first group" << endl;
	this->printResult(vFirstGroup);		
	cout << "Score of the Second group" << endl;
	this->printResult(vSecondGroup);		
	this->getKeyboard();	
	cout << "------------- No."<< this->turn << "Round promotion personnel:------------- " << endl;
	this->promoted(vFirstGroup, vIntermediaryHeat);
	this->promoted(vSecondGroup, vIntermediaryHeat);
	this->turn ++ ;
	cout << "------------- No."<< this->turn << "Round participants:------------- " << endl;
	this->printCompetitorId(vIntermediaryHeat);
	this->getKeyboard();
	system("clear");
	cout << "------------- No."<< this->turn << "Round results:------------- " << endl;
	this->giveAMark(vIntermediaryHeat);
	this->printResult(vIntermediaryHeat);
	system("clear");
	cout << "------------- Competition winners:------------- " << endl;
	this->promoted(vIntermediaryHeat, vVictory);
	this->writeCSV();
}

void speechManager::getKeyboard()
{
	cout << "Please enter any characters to continue...";
	char keyInput;
	cin >> keyInput;
}
/**********************************************
* Function name: double speechManager::computeScore()
* Function: Score each player, randomly generate a score, remove the highest score and the lowest score and calculate the average score
* Parameters: none
* Return value: None
*********************************************/
double speechManager::computeScore()
{
	deque<int> sScore;	
	for (int i = 0; i < 10; i++)
	{
		sScore.push_back(rand() % 41 + 60); 
	}
	sort(sScore.begin(), sScore.end());
	sScore.pop_back();
	sScore.pop_front();  
	int sum = 0;
	for (deque<int>::iterator dit = sScore.begin(); dit != sScore.end(); dit++)
	{
		sum += *dit; 
	}
	double avg = (double)sum / (double)(sScore.size());
	return avg;	
}

/**********************************************
* Function name: void speechManager::giveAMark()
* Function: Score the contestants and the final score
* Parameters:
* return value:
*********************************************/
void speechManager::giveAMark(vector<int> & vCP)
{
	map<int, double> sScore;	
	for (vector<int>::iterator i = vCP.begin(); i != vCP.end(); i++)
	{
		sScore.insert(pair<int, double>(*i, this->computeScore()));
	}	
	
	for (map<int, double>::iterator it = sScore.begin(); it != sScore.end(); it++)
	{
		map<int, Competitor>::iterator pos = mSpeaker.find(it->first);
		if (pos != mSpeaker.end())
		{
			(*pos).second.score = it->second;
		}
		else
		{
			cout << "err" << endl;
		}	
	}	
}

void speechManager::printResult(vector<int> & vCP)
{
	
	for (vector<int>::iterator i = vCP.begin(); i != vCP.end(); i++)
	{
		map<int, Competitor>::iterator pos = mSpeaker.find(*i);
		cout << "serial number" << *i << "\tname" << setw(10) << left 
			<< (*pos).second.name << "\t-score" << (*pos).second.score << endl;
	}	
}

/*******************************************
* Function name: void speechManager::printCompetitorId(vector<int> & vCP)
* Function: Print the list of contestants (ID)
* Parameters:
* return value:
********************************************/
void speechManager::printCompetitorId(vector<int> & vCP)
{
	switch (this->turn)
	{
	case 0:
		cout << "Participants in the first round:";
		break;
	case 1:
		cout << "Participants in the second round:";
		break;
	case 2:
		cout << "Winner list:";
		break;
	default:
		break;
	}
	for (vector<int>::iterator it = vCP.begin(); it != vCP.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

/*******************************************
* Function name:
* Function: Calculate promotion list
* Parameters:
* return value:
********************************************/
void speechManager::promoted(vector<int> & contestant, vector<int> & vV)
{
	set<Competitor, MyCompare> sScore;	
	for (vector<int>::iterator i = contestant.begin(); i != contestant.end(); i++)
	{
		map<int, Competitor>::iterator pos = mSpeaker.find(*i);
		sScore.insert(pos->second);
	}		
	set<Competitor, MyCompare>::iterator iter1 = sScore.begin();	
	advance(iter1, 3);	
	sScore.erase(iter1, sScore.end());
	for (set<Competitor, MyCompare>::iterator i = sScore.begin(); i != sScore.end(); i++)
	{
		cout << i->id << " " << i->name << " " << i->score << endl;
		vV.push_back(i->id);
	}	
}

void speechManager::writeCSV()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);  

	
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		map<int, Competitor>::iterator pos = mSpeaker.find(*it);
		ofs << *it << ","
			<< (*pos).second.name << "," << (*pos).second.score << ",";
	}
	ofs << endl;
    
	ofs.close();
    
	cout << "Record has been saved" << endl;
}

void speechManager::loadRecord()
{
	ifstream ifs("speech.csv", ios::in);

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "file does not exist!" << endl;
		ifs.close();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "File is empty!" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	this->fileIsEmpty = false;

	ifs.putback(ch); 

	string data;
	int index = 0;
	vector<string>v;
	while (ifs >> data)
	{
		// cout << data << endl;
		int pos = -1;
		int start = 0;

		while (true)
		{
			pos = data.find(",", start); 
			if (pos == -1)
			{
				break; 
			}
			string tmp = data.substr(start, pos - start); 
			v.push_back(tmp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}	
	ifs.close();
	if (fileIsEmpty)
	{
		cout << "No data currently" << endl;
		return;
	}
	
	for (map<int, vector<string> >::iterator i = m_Record.begin(); i != m_Record.end(); i++)
	{
		cout << "id\tname score\tid name socre\tid\tname score" << endl;
		for (vector<string>::iterator i = v.begin(); i != v.end(); i++)
		{
			cout << *i << "  ";
		}
	}
	cout << endl;
}

/************************************************
* Function name:
* Function: Clear file contents
* Parameters:
* return value:
*********************************************/
void speechManager::clearFile()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out);
	ofs.close();
	cout << "Data has been cleared" << endl;
}