#include "Program_5.h"

using namespace std;

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



int main()
{
	//Welcome.
	cout << "\n\nGreetings. In this application, a user may add files from a computer to be stored. The user" << endl
		   << "\tmay also establish any connections or relations between two files. Any file may have as many" << endl
		   << "\tor as few connections as possible. The user can then see which files are connected or" << endl
		   << "\trelated to a certain file. The user may also select to see all of the files that he or she has entered." << endl;
	
	int max = 0; //Temporary variable to store maximum number of files.
	cout << "\n\nWhat is the maximum number of files? ";
	cin >> max;
	cin.ignore(100, '\n');
	
	table my_files(max); //Instance of class table, as well as calling constructor
								//to establish maximum number of files.
	char name[100], name2[100]; //Variables to hold the names of the files input.
	char response = 'N'; //Variable to hold response of user.
	
	do
	{
		cout << "\nEnter file name: ";
		cin.get(name, 100);
		cin.ignore(100, '\n');
		
		if (my_files.insert_vertex(name))
			cout << "\nInsertion successful." << endl;
		else
			cout << "\nCould not insert." << endl;
		
		cout << "\nAgain (Y/N)?: ";
		cin >> response;
		cin.ignore(100, '\n');
		
	} while (toupper(response) == 'Y');
	
	do
	{
		cout << "\nEnter two file names that are related:";
		cout << "\nEnter name of first file: ";
		cin.get(name, 100);
		cin.ignore(100, '\n');
		
		cout << "\nEnter name of second file: ";
		cin.get(name2, 100);
		cin.ignore(100, '\n');
		my_files.insert_edge(name, name2);
		
		cout << "\nAgain (Y/N)?: ";
		cin >> response;
		cin.ignore(100, '\n');
		
	} while (toupper(response) == 'Y');
	
	cout << "\nEnter file name to search for related files: ";
	cin.get(name, 100);
	cin.ignore(100, '\n');
	
	my_files.display_related(name);
	
	cout << "\nDo you wish to see all of the files (Y/N)? ";
	cin >> response;
	cin.ignore(100, '\n');
	
	if (toupper(response) == 'Y')
	{
		cout << "\nThis is all of the files:";
		my_files.display_all();
	}
	
	return 0;
}
