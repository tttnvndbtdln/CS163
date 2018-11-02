#include "Program_4.h"

//Phuong Pham
//CS 163
//Program 4
//May 2016

//The purpose of this program is to build a "study guide" consisting of information about certain 
//topics in a certain class. Information along with the topic include the topic's title, a description
//that the user knows about the topic, the chapter number that the topic is located in the
//textbook, the starting page of the material, the ending page of the topic, and a flag to indicate
//whether further study is needed on the material. This study guide is entirely generated by the 
//user. That is, all information on this study guide must come from the user. The user may then 
//perform a number of actions about the study guide, including adding new topics to the study 
//guide, removing a topic from the study guide (along with all of its relevant information), edit
//the description of the study guide as the student progresses in his/her studying, retrieve 
//information about a certain topic (then display if the main application would like to do so),
//displaying all topics whose first letter is within a range of letters provided by the user
//(e.g. display all topics whose words' first letter are within the range of A through M), and
//displaying all topics in the study guide. 

//This program is implemented using a table abstract data type using a binary search tree as 
//the data structure to store the information about each topic in the study guide. This gives 
//us the advantage of a logarithmic algorithm for insert, remove, and retrieve, which are
//usually the operations for working with a study guide. It also provides us with the flexibility
//of displaying the data in sorted order and the ability to display the data in a range. 

//A struct is first used to store all of the information about the topic, including two pointers to
//point to the two children of the parent's node. A class is established with all of the operations
//the user can perform in its public sections and the root pointer to the tree is placed under the
//private section. Furthermore, in order to maintain the integrity of the data stored, no node
//pointers should exist (pass in to the functions from main) and so the functions in the public
//sections will simply call the private functions. The private functions are the ones that actually
//perform the operations recursively, since it needs to be passed in the node pointer to do so.  



//Class constructor
table::table()
{
	root = NULL;
}



//Class destructor
table::~table()
{
	destroy(root); //Call private function to destroy tree
}



//This function is called by the destructor (its private recursive counterpart) to 
//recursively calls the function itself and delete every nodes in the tree.
//INPUT: Function takes in the root pointer of the tree.
//OUTPUT: No output.
void table::destroy(node * & root)
{
	if (!root)
		return;
	destroy(root -> left);
	destroy(root -> right);
	delete [] root -> keyword; //deallocate memory
	delete [] root -> description;
	delete root; //delete node
	root = NULL;
}



//Insert new topic into the study guide. All of the information is provided
//by the main application. This function then calls its private counterpart so that 
//that function can recursively calls itself with root -> left and root -> right.
//INPUT: This function takes in 6 arguments, all of which are information listed
//in the stuct. This includes a dynamically array of the keyword, array of
//description, chapter number, starting page, ending page, and a flag to
//indicates whether further study is needed.
//OUTPUT: Returns success/failure state if item was added.
int table::insert(char * key_word, char * topic_description, int chap, int low_page, int high_page, char study)
{
	if (insert(root, key_word, topic_description, chap, low_page, high_page, study))
		return 1;
	return 0;
}




//Private insert function. Takes in all of the information passed by the public insert
//function as well as the pointer or next pointer. This recursive calls ensure traversal
//to a leaf in order to add the new topic.
//INPUT: This function takes in 6 arguments, all of which are information listed
//in the stuct. This includes a dynamically array of the keyword, array of
//description, chapter number, starting page, ending page, and a flag to
//indicates whether further study is needed. It also takes in the node pointer.
//OUTPUT: Return success/failure state back to the public insert function. 
int table::insert(node * & root, char * key_word, char * topic_description, int chap, int low_page, int high_page, char study)
{
	if (!root)
	{
		root = new node; //Root gets new node
		root -> keyword = new char[strlen(key_word) + 1]; //Deep copy of dynamic memory
		strcpy(root -> keyword, key_word);
		
		root -> description = new char[strlen(topic_description) + 1];
		strcpy(root -> description, topic_description);
		
		root -> chapter = chap;
		root -> start_page = low_page;
		root -> end_page = high_page;
		root -> flag = study;
		
		root -> left = NULL;
		root -> right = NULL;
		
		return 1;
	}
	if (key_word[0] < ((root -> keyword)[0]))
		return insert(root -> left, key_word, topic_description, chap, low_page, high_page, study);
	return insert(root -> right, key_word, topic_description, chap, low_page, high_page, study);
}



//Remove an item from the study guide. It takes in the keyword or topic
//that the user wants to remove. This function calls its private counterpart so
//that that funciton can recursively calls itself with root -> left and root -> right.
//INPUT: The funciton takes in the keyword or topic that the usert wants to remove.
//OUPUT: Return success/failure state if item was removed.
int table::remove(char * key_word)
{
	if (remove(root, key_word)) //Calls private function
		return 1;
	return 0;
}



//Private remove function. Takes in the topic keyword passed in by the public remove
//function and the pointer. This function ensures every special case of removal is covered 
//and to remove the appropriate node.
//INPUT: Keyword passed in by public remove function and the root pointer.
//OUTPUT: Return success/failure state back to public remove function.
int table::remove(node * & root, char * key_word)
{
	if (!root)
		return 0; //Returns failure if no list, at a leaf (through recursion, or no match.
	
	if (strcmp(root -> keyword, key_word) == 0) //If there's a match
	{
		if (root -> left == NULL && root -> right == NULL) //Match at a leaf
		{
			delete [] root -> keyword;
			delete [] root -> description;
			delete root; //Simply delete node
			root = NULL;
			return 1;
		}
	
		else if (root -> right == NULL && root -> left != NULL) //Match at a node with only a left child
		{
			node * temp = root -> left; //Hold on to child
			delete [] root -> keyword;
			delete [] root -> description;
			delete root;
			root = temp; //Adoption takes over
			return 1;
		}
		
		else if (root -> right != NULL && root -> left == NULL) //Match at a node with only a right child
		{
			node * temp = root -> right;
			delete [] root -> keyword;
			delete [] root -> description;
			delete root;
			root = temp;
			return 1;
		}
		
		else if (root -> right -> left == NULL && root -> left != NULL) //Match whose right child is the in order succesor
		{
			node * temp = root -> right;
			delete [] root -> keyword;
			delete [] root -> description;
			
			//Essentially copy the data from the in order successor into the node to be deleted.
			root -> keyword = new char[strlen(temp -> keyword) + 1];
			strcpy(root -> keyword, temp -> keyword);
			
			root -> description = new char[strlen(temp -> description) + 1];
			strcpy(root -> description, temp -> description);
			
			root -> chapter = temp -> chapter;
			root -> start_page = temp -> start_page;
			root -> end_page = temp -> end_page;
			root -> flag = temp -> flag;
			
			root -> right = temp -> right; //Adoption 
			delete [] temp -> keyword; //Delete the node originally stored data of in order successor
			delete [] temp -> description;
			delete temp;
			return 1;
		}
		
		else //Two children otherwise
		{
			node * current = root -> right;
			node * previous = NULL;
			
			while (current -> left) //Traverse until in order successor is found
			{
				previous = current;
				current = current -> left;
			}
			
			delete [] root -> keyword; 
			delete [] root -> description;
			
			root -> keyword = new char[strlen(current -> keyword) + 1];
			strcpy(root -> keyword, current -> keyword);
			
			root -> description = new char[strlen(current -> description) + 1];
			strcpy(root -> description, current -> description);
			
			root -> chapter = current -> chapter;
			root -> start_page = current -> start_page;
			root -> end_page = current -> end_page;
			root -> flag = current -> flag;
			
			previous -> left = current -> right;
			delete [] current -> keyword;
			delete [] current -> description;
			delete current;
			return 1;
		}
	}
	
	if (key_word[0] < ((root -> keyword)[0]))
		return remove(root -> left, key_word);
	return remove(root -> right, key_word);
}



//
int table::edit(char * key_word, char * topic_description)
{
	if (edit(root, key_word, topic_description))
		return 1;
	return 0;
}



//
int table::edit(node * root, char * key_word, char * topic_description)
{
	if (strcmp(root -> keyword, key_word) == 0)
	{
		char * temp = new char[strlen(root -> description) + strlen(topic_description) + 1];
		strcpy(temp, root -> description); //Store in a temporary array
		
		strcat(temp, topic_description); //Concatenation
		
		delete [] root -> description;
		root -> description = new char[strlen(temp) + 1];
		strcpy(root -> description, temp); //Copy the temp into the actual data member
		return 1;
	}
	
	if (key_word[0] < ((root -> keyword)[0]))
		return edit(root -> left, key_word, topic_description);
	return edit(root -> right, key_word, topic_description);
}



//
int table::retrieve(node & found, char * key_word)
{
	if (retrieve(root, found, key_word))
		return 1;
	return 0;
}



//
int table::retrieve(node * root, node & found, char * key_word)
{
	if (strcmp(root -> keyword, key_word) == 0)
	{
		found.keyword = new char[strlen(root -> keyword) + 1];
		strcpy(found.keyword, root -> keyword);
		
		found.description = new char[strlen(root -> description) + 1];
		strcpy(found.description, root -> description);
		
		found.chapter = root -> chapter;
		found.start_page = root -> start_page;
		found.end_page = root -> end_page;
		found.flag = root -> flag;
		return 1;
	}
	
	if (key_word[0] < ((root -> keyword)[0]))
		return retrieve(root -> left, found, key_word);
	return retrieve(root -> right, found, key_word);
}



//
void table::display_range(char start_range, char end_range)
{
	display_range(root, start_range, end_range);
}



//
void table::display_range(node * root, char start_range, char end_range)
{
	using namespace std;
	if (!root)
		return;
	if ((root -> keyword)[0] >= start_range && (root -> keyword)[0] <= end_range)
		cout << root -> keyword << endl;
	display_range(root -> left, start_range, end_range);
	display_range(root -> right, start_range, end_range);
}



//
void table::display_all()
{
	display_all(root);
}



//
void table::display_all(node * root)
{
	using namespace std;
	if (root)
	{
		if (root -> left)
			display_all(root -> left);
		cout << endl << root -> keyword << endl;
		if (root -> right)
			display_all(root -> right);
	}
	else
		return;
}