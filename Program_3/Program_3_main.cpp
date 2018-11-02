#include "Program_3.h"

//Phuong Pham
//CS 163
//May 2016
//Program 3


//The purpose of this program is to build a "study guide" consisting information about
//a topic including the topic's title, a description that the user knows about the topic,
//the chapter number that the topic is located in the textbook, the starting page of
//the material, the ending page of the topic, and a flag to indicate whether further
//study is needed. The study guide is first created by importing these information from
//an external file named "hash.txt". The user may then perform a number of actions
//on the study guide, including adding new topic to be studied, remove an item from
//the study guide, edit the description of a topic as studying is done on the topic,
//retrieve the information about a topic (then display if the user wants to), displaying
//all of the topics (keywords) in a certain chapter, and displaying all of the topics
//(keywords). 

//This program is implemented using a table abstract data type using a hash table with
//chaining as the collision resolution technique. Per hashing, the size of the table is chosen
//to be the prime number 97 (size of the array). Any collisions (same data, or in this
//case, the keyword or topic) will be added using a linear linked list. It is predicted that in
//a realistic version of a study guide created this way, collision is a rare if happens at
//all since each topics should be separated (no duplicates) and if any additional
//information is needed to be added, a function to edit the description can simply be 
//called. Nevertheless, the technique exists to safeguard any risk of collision. The ADT is
//managed by a class with public functions performing tasks as mentioned above by
//the user and the private members including the pointer to the pointer to the first node
//of the linear linked list (the first item with that certain keyword), as well as the size
//of the hash table. The grouping of the different information about a topic will be
//stored in a struct, with a next pointer. Each instance of the struct is then a node.

using namespace std;

int main()
{
	table study_guide; //Declare instance of class table
	node found; //Declare instance of node found to be retrieved
	
	char key_word[100]; //Store keyword/topic
	char topic_description[300]; //Store description.
	int chap = 0, start_page = 0, end_page = 0; //Store chapter number, starting page, and ending page.
	char study; //Flag if further study is needed (Y/N).
	char response = 'N'; //Hold response for repeat. 
	int response2 = 0, temp = 0; //Hold reponse for options, temp to catch function returns. 
	
	//Welcome.
	cout << "\n\nGreetings. In this application, a study guide is first created using information" << endl;
	cout << "from an external data file. This study guide will comprise of information including the keyword" << endl;
	cout << "of the topic needed to study, the description of what the topic is about, the" << endl;
	cout << "chapter number that the topic is located in the textbook, the starting page" << endl;
	cout << "of the topic, the ending page of the topic, and a flag on whether further study is" << endl;
	cout << "needed on the topic. The user may then perform a multitude of actions, including" << endl;
	cout << "but not limited to adding a new topic to study, remove a topic, display the topic," << endl;
	cout << "etc." << endl; 
	
	//Information is imported to build a study guide. 
	if (study_guide.read_in())
		cout << "\nInformation was read in successfully." << endl;
	else
		cout << "\nInformation read in not possible." << endl;

	do
	{
		cout << "\n\nWhat would you like to do?" << endl;
		cout << "Enter 1 to enter a new item for your study guide." << endl;
		cout << "Enter 2 to remove an item (and all of its information) according to a keyword." << endl;
		cout << "Enter 3 to edit the description of an item." << endl;
		cout << "Enter 4 to retrieve information about an item using a keyword." << endl;
		cout << "Enter 5 to display all topics in a chapter." << endl;
		cout << "Enter 6 to display all topics." << endl;
		cout << "Enter 7 to quit application." << endl;
		cin >> response2;
		cin.ignore(100, '\n');
		
		if (response2 == 1)
		{
			cout << "Enter keyword: ";
			cin.get(key_word, 100);
			cin.ignore(100, '\n');
			
			cout << "Enter description: ";
			cin.get(topic_description, 300);
			cin.ignore(300, '\n');
			
			cout << "Enter chapter number: ";
			cin >> chap;
			cin.ignore(100, '\n');
			
			cout << "Enter the beginning page: ";
			cin >> start_page;
			cin.ignore(100, '\n');
			
			cout << "Enter the finishing page: ";
			cin >> end_page;
			cin.ignore(100, '\n');
			
			cout << "Would you like to study this subject again (Y/N)? ";
			cin >> study;
			cin.ignore(100, '\n');
			
			if (study_guide.insert(key_word, topic_description, chap, start_page, end_page, study))
				cout << "Insert successful." << endl;
			else
				cout << "Insert not possible." << endl;
		}
		
		else if (response2 == 2)
		{
			cout << "Enter keyword to remove: ";
			cin >> key_word;
			cin.ignore(100, '\n');
			temp = study_guide.remove(key_word);
			if (temp == 1)
				cout << "Removal successful." << endl;
			else
				cout << "Could not remove." << endl;
		}
		
		else if (response2 == 3)
		{
			cout << "Enter keyword to edit description of: ";
			cin >> key_word;
			cin.ignore(100, '\n');
			
			cout << "Add description: ";
			cin.get(topic_description, 300);
			cin.ignore(300, '\n');
			if (study_guide.edit(key_word, topic_description))
				cout << "Description changed." << endl;
			else
				cout << "Could not change description" << endl;
		}
		
		else if (response2 == 4)
		{
			cout << "Enter keyword to retrieve: ";
			cin.get(key_word, 100);
			cin.ignore(100, '\n');
			
			if (study_guide.retrieve(key_word, found))
				cout << "Retrieve successful." << endl;
			else
				cout << "Could not retrieve." << endl;
			
			cout << "Do you want to display retrieved information? (Y/N)?";
			cin >> response;
			cin.ignore(100, '\n');
			
			if (toupper(response) == 'Y')
			{
				cout << "Found: " << endl;
				cout << "\nKeyword: " << found.keyword << endl;
				cout << "Description: " << found.description << endl;
				cout << "Chapter: " << found.chapter << endl;
				cout << "Lower page: " << found.lower_page << endl;
				cout << "Higher page: " << found.higher_page << endl;
				cout << "Need further study? " << found.flag << endl;
			}
		}
		
		else if (response2 == 5)
		{
			cout << "Enter chapter you would like to display all keywords of: ";
			cin >> chap;
			cin.ignore(100, '\n');
			
			study_guide.display_chapter(chap);
		}
		
		else if (response2 == 6)
			study_guide.display_all();
	} while (response2 != 7);

	return 0;
}

















