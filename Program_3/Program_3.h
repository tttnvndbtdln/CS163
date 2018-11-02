#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>

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



const int SIZE = 97; //Global constant. Size of the hash table.

const char outfile[] = "hash.txt"; //Name of external data file.
//The external data file lists all of the information in the struct (see below) line by line 
//with pure information. It does not skip lines or has any punctuation marks. 
//An simplified example:
//Stack
//Stack follows FILO
//5
//150
//175
//Y 



//Struct to group together the different information regarding a topic
struct node
{
	char * keyword;
	char * description;
	int chapter;
	int lower_page; //Starting page of the material
	int higher_page; //Ending page of the material
	char flag;
	node * next; //Next pointer 
};



//Table ADT is managed by a class. 
class table
{
	public:
		table(); //Constructor
		~table(); //Destructor
		
		//A function called by desctructor to delete all nodes. 
		//INPUT: Takes in the head node, allocates a temp node to delete all nodes in the 
		//linked list.
		//OUTPUT: None. 
		void destructor(node * & head); 
		
		//The hash function determine where in the hash table a keyword should fit. It does 
		//this by adding the ASCII values of all of the letters in the keyword. It then mod (%)
		//this value by the hash table size and return this value. 
		//INPUT: The function takes in the keyword. 
		//OUTPUT: The value after modding the ASCII values of all the letter in the
		//keywords by the hash table size. This determines what element of the hash table
		//(array) the keyword belongs. 
		int hash_function(char * key); 
		
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
		int read_in(); 
		
		//Insert new topic into the study guide. All of the relevant information is provided by
		//the user. All of which are then stored in a temporary node. The hash function is 
		//called to determine where this node should reside, provided the keyword, then it
		//adds to the linked list similar to the fashion in the read_in function.
		//INPUT: This function takes in 6 arguments, all of which are information listed in the
		//struct. This includes a dynamically array of the keyword, array of description,
		//chapter number, starting page, ending page, and a flag to indcates whether
		//further study is needed.
		//OUTPUT: Returns success/failure state if item was added. 
		int insert(char *, char *, int, int, int, char); 
		
		//Remove an item from the study guide. It takes in the keyword or topic that the
		//user wants to remove and runs it through the hash function to determine where
		//that topic lives. A local node is declared to be the same as the head pointer and
		//traverses until the keywords match. It then deletes the dynamic allocated arrays
		//and then the node. 
		//INPUT: The function takes in the keyword that the user wants to remove.
		//OUTPUT: Return success/failure state if item was removed.
		int remove(char * key_word); 
		
		//Edit the description of an item in the study guide. It takes in the keyword that the
		//user wants to add information, as well as that information the user wants to add. 
		//The hash function is once again and the operations to find the match are similar
		//to the above remove function. Once it finds a match, a temporary array is used
		//to stored the information in the current node's description. Concatenation (strcat)
		//is then used to combine the information passed in by the user. 
		//INPUT: The function takes in the keyword and then additional description from the
		//user
		//OUTPUT: Return success/failure state if description was edited.
		int edit(char * key_word, char * topic_description); 
		
		//Retrieve information about a keyword (provided by the user) and then stored in 
		//a node passed in by reference. If found, the information about that topic is added
		//into the node. The user then has the option to display those information using
		//that node. That node is separated from the actual data stored in the hash table
		//so the integrity of the data is remained. 
		//INPUT: The function takes in the keyword to determine where the topic resides,
		//as well as the pass by referenced node to be modifed if found.
		//OUTPUT: Return success/failure state to the application. 
		bool retrieve(char * key_word, node & found); 
		
		//Display all of the keywords that belons in a certain chapters. 
		//INPUT: Takes in the desired chapter number.
		//OUTPUT: Returns nothing. Simply display. 
		void display_chapter(int chap); 
		
		//Display all keywords stored in the hash table. 
		//INPUT: None.
		//OUTPUT: None. Simply display. 
		void display_all(void) const; 

	private:
		node ** hash_table;
		int hash_table_size;
};
