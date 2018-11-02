#include "Program_5.h"

//Phuong Pham
//CS 163
//May 2016
//Program 5

//The purpose of this program is to create a simple weighted graph abstraction
//using adjacency list. The data will be stored in an array of vertices where
//each element has a vertex that stores the information and a head pointer
//to a linear linked list of edges for adjacent vertices.

//The information that will be stored in each vertex will be a file name (from a
//computer). This information will be managed by a struct called vertex. In
//addition to this piece of information, the struct will also have a head
//pointer to the first node of a linear linked list. This LLL will have a node
//for each of the other vertices that the current vertext is connected or 
//related to (edges).

//The linear linked list of edges will be managed by a separate struct. One of
//the data members is a pointer to a vertex, so that each node is a
//representation of a connection between the current vertex and the vertex
//that the pointer points to. It also has a next pointer to point to the next 
//node, representing the other vertices that the current vertex has
//relationships with.

//The table ADT will be used with functions to insert new vertices (adding
//new file names), insert new edges (create relationships between two files),
//display all vertices that are related or connected to a vertex that was
//requested by the application, and a function to display all of the vertices
//(i.e. all of the files stored in the graph). The graph will also have a private
//function to locate the position of a given file name in the array of vertices. 
//This is used to determine where in the array a certain file name is located
//for use of inserting new edges between certain files and to display all of 
//the files related to a file. In addition, the private section also contain the 
//recursive part of the display vertices that are related to a certain file. 
//The recursive part is placed in the private section to protect the integrity
//of the node pointer and the public wrapper function is used to read in the 
//file name from the application. The private section also contains the 
//array of vertices elements and a variable to keep track of the size of 
//the graph. 



//Constructor taking in the maximum size of the graph.
table::table(int size)
{
	adjacency_list = new vertex[size];
	for (int i = 0; i < size; ++i)
	{
		adjacency_list[i].file_name = NULL;
		adjacency_list[i].head = NULL;
	}
	list_size = size;
}



//Destructor
table::~table()
{
	for (int i = 0; i < list_size; ++i)
	{
		if (adjacency_list[i].file_name)
		{
			node * current = adjacency_list[i].head; //Hold on to head pointer
			node * previous = NULL;
			while (current)
			{
				previous = current;
				current = current -> next;
				delete previous; //Delete node
			}
		}
		delete [] adjacency_list[i].file_name; //Release dynamic memory.
		adjacency_list[i].file_name = NULL;
		adjacency_list[i].head = NULL;
	}
	delete [] adjacency_list;
	
	list_size = 0;
}



//Insert new vertex (file name) into the graph by inserting into the first
//available position in the array, unless there is no space available.
//The file name is provided by the user. 
//INPUT: The function takes in the file name as a pointer to characters
//as argument.
//OUTPUT: Returns success/failure state if item was added.
int table::insert_vertex(char * name)
{
	int temp = 0;
	while (adjacency_list[temp].file_name != NULL && temp < list_size)
		++temp;
	if (adjacency_list[temp].file_name != NULL)
		return 0;
	else
	{
		adjacency_list[temp].file_name = new char[strlen(name) + 1];
		strcpy(adjacency_list[temp].file_name, name);
		return 1;
	}
}



int table::find_location(char * key)
{
	int temp = 0;
	while (temp < list_size)
	{
		if (strcmp(adjacency_list[temp].file_name, key) == 0)
			return temp;
		++temp;
	}
	return -1;
}



//Insert new edge between two related or connected files. The
//function will first call the private function find_location to determine
//the position of the two vertices and then continue to connect them.
//Since the graph is not directed, the function will establish connections
//both ways. 
//INPUT: The function takes in two arguments, one for the current vertex
//and the other for the second vertex to be connected.
//OUTPUT: Returns success/failure state if a connection was made.
int table::insert_edge(char * current_vertex, char * to_attach)
{
	int temp = find_location(current_vertex);
	int temp2 = find_location(to_attach);
	if (temp == -1 || temp2 == -1)
		return 0;
	else
	{
		node * hold = new node;
		hold -> adjacent = &adjacency_list[temp2];
		hold -> next = adjacency_list[temp].head;
		adjacency_list[temp].head = hold;
		
		hold = new node;
		hold -> adjacent = &adjacency_list[temp];
		hold -> next = adjacency_list[temp2].head;
		adjacency_list[temp2].head = hold;
		return 1;
	}
}



//Display all of the files related to a file provided by the user. The 
//function first calls the find_location function to determine the 
//location of the input function in the array. Then, it calls its recursive
//counterpart, also a private function, to go through the LLL to 
//display all of the vertices pointers in that list. 
//INPUT: The function takes in the name of the file.
//OUPUT: Display all of the other files related to the input file.
void table::display_related(char * current)
{
	using namespace std;
	int temp = find_location(current);
	if (temp == -1)
		return;
	node * hold = adjacency_list[temp].head;
	display_related_recursive(hold);
}



//Recursive counterpart of display_related function. 
//INPUT: Takes in the node pointer (or next node pointer in the 
//recursive call).
//OUTPUT: Display all file names in the LLL.
void table::display_related_recursive(node * hold)
{
	using namespace std;
	if (!hold)
		return;
	cout << (hold -> adjacent) -> file_name << endl;
	display_related_recursive(hold -> next);
}



//Display all of the files in the graph.
//INPUT: The function takes in no arguments.
//OUTPUT: Display every file names.
void table::display_all()
{
	using namespace std;
	for (int i = 0; i < list_size ; ++i)
	{
		vertex temp = adjacency_list[i];
		if (temp.file_name)
			cout << endl << temp.file_name << endl;
	}
}





