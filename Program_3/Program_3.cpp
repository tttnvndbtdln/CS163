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



//Constructor
table::table()
{
	hash_table_size = SIZE;
	hash_table = new node * [SIZE];
	for (int i = 0; i < SIZE; ++i)
		hash_table[i] = NULL;
}



//Destructor
table::~table()
{
	hash_table_size = 0;
	for (int i = 0; i < SIZE; ++i)
	{
		if (hash_table[i])
			destructor(hash_table[i]);
	}
}



//A function called by desctructor to delete all nodes. 
//INPUT: Takes in the head node, allocates a temp node to delete all nodes in the 
//linked list.
//OUTPUT: None. 
void table::destructor(node * & head)
{
	node * current = head;
	while (current)
	{
		current = current -> next;
		delete [] head -> keyword; //Delete dynamic memory
		delete [] head -> description;
		delete head;
		head = current;
	}
	head = NULL;
}



//The hash function determine where in the hash table a keyword should fit. It does 
//this by adding the ASCII values of all of the letters in the keyword. It then mod (%)
//this value by the hash table size and return this value. 
//INPUT: The function takes in the keyword. 
//OUTPUT: The value after modding the ASCII values of all the letter in the
//keywords by the hash table size. This determines what element of the hash table
//(array) the keyword belongs. 
int table::hash_function(char * key)
{
	if (!key)
		return -1;
	int value = 0;
	for (int i = 0; i < strlen(key); ++i)
		value += int(key[i]);
	return value%hash_table_size;
}



//The read in function opens the external data file and then read in the information.
//All of the information is stored in a temporary node.
//The first information the function takes in is the keyword. It calls upon the hash
//function to determine where in the table to store the node. Afterwards, the head
//pointer points to that node. This process is then repeated until the end of file. 
//Note that for each subsequent collision, the temporary node next pointer first points
//to the head node, then the head pointer is updated to point to temp to ensure
//that the node is always added at the beginning of the linear linked list. 
//INPUT: The function takes in no argument and performs first before the application
//can do any input/output.
//OUTPUT: Only return success/failure to main to report if information was read in
//successfully.
int table::read_in()
{
	using namespace std;
	char tempo[300]; //Hold the information reading in. 
	int hash_value = 0;
	node * temp = new node;
	
	ifstream in_file;
	in_file.open(outfile);
	
	if (in_file)
	{
		//Prime the pump. 
		in_file.get(tempo, 100, '\r');
		in_file.ignore(100, '\n');
		
		temp -> keyword = new char[strlen(tempo) + 1]; //Deep copy
		strcpy(temp -> keyword, tempo);
		
		in_file.get(tempo, 300, '\n');
		in_file.ignore(300, '\n');
		
		temp -> description = new char[strlen(tempo) + 1];
		strcpy(temp -> description, tempo);
		
		in_file >> temp -> chapter;
		in_file.ignore(100, '\n');
		
		in_file >> temp -> lower_page;
		in_file.ignore(100, '\n');
		
		in_file >> temp -> higher_page;
		in_file.ignore(100, '\n');
		
		in_file >> temp -> flag;
		in_file.ignore(100, '\n');
		
		hash_value = hash_function(temp -> keyword); //Call hash function
		
		temp -> next = hash_table[hash_value]; //Points temp's next pointer to head
		hash_table[hash_value] = temp; //Update head to temp
		
		while (!in_file.eof()) //Continues reading until end of file
		{
			temp = new node;
			
			in_file.get(tempo, 100, '\r');
			in_file.ignore(100, '\n');
		
			temp -> keyword = new char[strlen(tempo) + 1];
			strcpy(temp -> keyword, tempo);
		
			in_file.get(tempo, 300, '\n');
			in_file.ignore(300, '\n');
		
			temp -> description = new char[strlen(tempo) + 1];
			strcpy(temp -> description, tempo);
		
			in_file >> temp -> chapter;
			in_file.ignore(100, '\n');
		
			in_file >> temp -> lower_page;
			in_file.ignore(100, '\n');
		
			in_file >> temp -> higher_page;
			in_file.ignore(100, '\n');
		
			in_file >> temp -> flag;
			in_file.ignore(100, '\n');
		
			hash_value = hash_function(temp -> keyword);
		
			temp -> next = hash_table[hash_value]; 
			hash_table[hash_value] = temp;
		}
		
		return 1;
	}
	
	return 0;
}



//Insert new topic into the study guide. All of the relevant information is provided by
//the user. All of which are then stored in a temporary node. The hash function is 
//called to determine where this node should reside, provided the keyword, then it
//adds to the linked list similar to the fashion in the read_in function.
//INPUT: This function takes in 6 arguments, all of which are information listed in the
//struct. This includes a dynamically array of the keyword, array of description,
//chapter number, starting page, ending page, and a flag to indcates whether
//further study is needed.
//OUTPUT: Returns success/failure state if item was added. 
int table::insert(char * key_word, char * topic_description, int chap, int start_page,
int end_page, char study)
{
	int hash_value = 0;
	if (hash_value == -1)
		return 0;
	node * temp = new node;
	
	//Store information passed in into temp node
	temp -> keyword = new char[strlen(key_word) + 1]; //Deep copy
	strcpy(temp -> keyword, key_word);
	
	temp -> description = new char[strlen(topic_description) + 1];
	strcpy(temp -> description, topic_description);
	
	temp -> chapter = chap;
	temp -> lower_page = start_page;
	temp -> higher_page = end_page;
	temp -> flag = study;
	
	//Similar to read_in function
	hash_value = hash_function(temp -> keyword);
	
	temp -> next = hash_table[hash_value]; 
	hash_table[hash_value] = temp;
	return 1;
}



//Retrieve information about a keyword (provided by the user) and then stored in 
//a node passed in by reference. If found, the information about that topic is added
//into the node. The user then has the option to display those information using
//that node. That node is separated from the actual data stored in the hash table
//so the integrity of the data is remained. 
//INPUT: The function takes in the keyword to determine where the topic resides,
//as well as the pass by referenced node to be modifed if found.
//OUTPUT: Return success/failure state to the application. 
bool table::retrieve(char * key_word, node & found)
{
	int hash_value = 0;
	bool success = false;
	
	if (!key_word)
		return success;

	hash_value = hash_function(key_word);

	node * current = hash_table[hash_value];
	while (current)
	{
		if (strcmp(current -> keyword, key_word) == 0)
		{
			//Store information from the hash table into the node passed in
			found.keyword = new char[strlen(current -> keyword) + 1];
			strcpy(found.keyword, current -> keyword);
			
			found.description = new char[strlen(current -> description) + 1];
			strcpy(found.description, current -> description);
			
			found.chapter = current -> chapter;
			found.lower_page = current -> lower_page;
			found.higher_page = current -> higher_page;
			found.flag = current -> flag;
			success = true;
		}
		current = current -> next;
	}
	return success;
}



//Remove an item from the study guide. It takes in the keyword or topic that the
//user wants to remove and runs it through the hash function to determine where
//that topic lives. A local node is declared to be the same as the head pointer and
//traverses until the keywords match. It then deletes the dynamic allocated arrays
//and then the node. 
//INPUT: The function takes in the keyword that the user wants to remove.
//OUTPUT: Return success/failure state if item was removed.
int table::remove(char * key_word)
{
	if (!key_word)
		return 0;
	
	int hash_value = 0;
	hash_value = hash_function(key_word);
	
	node * current = hash_table[hash_value];
	node * previous = NULL;
	
	if (strcmp(current -> keyword, key_word) == 0)
	{
		hash_table[hash_value] = current -> next;
		delete [] current -> keyword;
		delete [] current -> description;
		delete current;
		current = NULL;
		return 1;
	}
	else
	{
		while (current)
		{
			if (strcmp(current -> keyword, key_word) == 0)
			{
				previous -> next = current -> next;
				delete [] current -> keyword;
				delete [] current -> description;
				delete current;
				current = NULL;
				return 1;
			}
			previous = current;
			current = current -> next;
		}
	}
	return 0;
}



//Edit the description of an item in the study guide. It takes in the keyword that the
//user wants to add information, as well as that information the user wants to add. 
//The hash function is once again and the operations to find the match are similar
//to the above remove function. Once it finds a match, a temporary array is used
//to stored the information in the current node's description. Concatenation (strcat)
//is then used to combine the information passed in by the user. 
//INPUT: The function takes in the keyword and then additional description from the
//user
//OUTPUT: Return success/failure state if description was edited.
int table::edit(char * key_word, char * topic_description)
{
	int hash_value = 0;
	char * temp;
	if (!key_word)
		return 0;
	
	hash_value = hash_function(key_word);
	node * current = hash_table[hash_value];
	while (current)
	{
		if (strcmp(current -> keyword, key_word) == 0)
		{
			//Copy information from the current node into a temporary array
			temp = new char[strlen(current -> description) + 1];
			strcpy(temp, current -> description);
			return 1;
		}
		current = current -> next;
	}
	
	//Concatenate the array of the passed in array (topic_description) to the temp array
	strcat(temp, topic_description);
	
	current = hash_table[hash_value];
	while (current)
	{
		if (strcmp(current -> keyword, key_word) == 0)
		{
			//Delete current description
			if (current -> description)
				delete [] current -> description;
			//Copy the temp array into the current description
			current -> description = new char[strlen(temp) + 1];
			strcpy(current -> description, temp);
			return 1;
		}
		current = current -> next;
	}
	
	return 0;
}



//Display all of the keywords that belons in a certain chapters. 
//INPUT: Takes in the desired chapter number.
//OUTPUT: Returns nothing. Simply display. 
void table::display_chapter(int chap)
{
	using namespace std;
	
	if (chap == 0)
		return;
	for (int i = 0; i < SIZE; ++i)
	{
		node * current = hash_table[i];
		while (current)
		{
			if (current -> chapter == chap)
				cout << current -> keyword << endl;
			current = current -> next;
		}
	}
}



//Display all keywords stored in the hash table. 
//INPUT: None.
//OUTPUT: None. Simply display. 
void table::display_all(void) const
{
	using namespace std;
	
	for (int i = 0; i < SIZE; ++i)
	{
		node * current = hash_table[i];
		while (current)
		{
			cout << "\nKeyword: " << current -> keyword << endl;
			cout << "Description: " << current -> description << endl;
			cout << "Chapter: " << current -> chapter << endl;
			cout << "Lower page: " << current -> lower_page << endl;
			cout << "Higher page: " << current -> higher_page << endl;
			cout << "Need further study? " << current -> flag << endl;
			current = current -> next;
		}
	}
}























/*
	while (current)
	{
		if (strcmp(current -> keyword, key_word) == 0)
		{
			temp = new char[strlen(current -> description) + 1];
			strcpy(temp, current -> description);
		}
		current = current -> next;
	}
	
	cout << "Temp: " << temp << endl;
	strcat(temp, topic_description);
	cout << "Temp after: " << temp << endl;
	
	current = hash_table[hash_value];
	
	while (current)
	{
		if (strcmp(current -> keyword, key_word) == 0)
		{
			cout << "Before deleting: " << current -> description << endl;
			delete [] current -> description;
			current -> description = new char[strlen(temp) + 1];
			strcpy((*current).description, temp);
			cout << "Final: " << current -> description << endl;
			return 1;
		}
		current = current -> next;
	}*/