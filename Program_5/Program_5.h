#include <iostream>
#include <cctype>
#include <cstring>

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



//Struct to store the information in the vertex.
//i.e. the name of the file.
struct vertex
{
	char * file_name; //Pointer to name of the file. 
	struct node * head; //Pointer to edge list.
};



//Struct to store the edge list.
struct node
{
	vertex * adjacent;
	node * next;
};



class table
{
	public:
		table(int size); //Constructor taking in the maximum 
							 //size of the graph
		~table(); //Destructor
		
		//Insert new vertex (file name) into the graph by inserting into the first
		//available position in the array, unless there is no space available.
		//The file name is provided by the user. 
		//INPUT: The function takes in the file name as a pointer to characters
		//as argument.
		//OUTPUT: Returns success/failure state if item was added.
		int insert_vertex(char * name);
		
		//Insert new edge between two related or connected files. The
		//function will first call the private function find_location to determine
		//the position of the two vertices and then continue to connect them.
		//Since the graph is not directed, the function will establish connections
		//both ways. 
		//INPUT: The function takes in two arguments, one for the current vertex
		//and the other for the second vertex to be connected.
		//OUTPUT: Returns success/failure state if a connection was made.
		int insert_edge(char * current_vertex, char * to_attach);
		
		//Display all of the files related to a file provided by the user. The 
		//function first calls the find_location function to determine the 
		//location of the input function in the array. Then, it calls its recursive
		//counterpart, also a private function, to go through the LLL to 
		//display all of the vertices pointers in that list. 
		//INPUT: The function takes in the name of the file.
		//OUPUT: Display all of the other files related to the input file.
		void display_related(char * current);
		
		//Display all of the files in the graph.
		//INPUT: The function takes in no arguments.
		//OUTPUT: Display every file names.
		void display_all();
		
	private:
		//Find the location of a certain file in the array. Using strcmp, it 
		//compares the input key to the file_name data member of a vertex. 
		//Once it finds a match, it returns the location of the array to the
		//functions above that use it.
		//INPUT: The function takes in the file name as an argument.
		//OUTPUT: Return the location of the file in the array. 
		int find_location(char * key);
		
		//Recursive counterpart of display_related function. 
		//INPUT: Takes in the node pointer (or next node pointer in the 
		//recursive call).
		//OUTPUT: Display all file names in the LLL.
		void display_related_recursive(node * hold);
		
		vertex * adjacency_list;
		int list_size; //Size of the graph.
};