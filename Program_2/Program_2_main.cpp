#include "Program_2_container.h"

//Phuong Pham
//CS 163
//April 2016
//Program 2

//This program is to manipulate ADTs of stacks and queues using their respective
//functions. Push (add new item at top of stack), pop (remove item at top of stack), 
//peek (peek at top item of stack), and display for stack and enqueue (add item at 
//end of queue), dequeue (remove item at front of queue), peek (peek at first item 
//of queue, and display for queue. In this program, the stack imitates a real life 
//situation of a truck delivering its packages. The packages are arranged so that 
//first in is last out (FILO for stack), similar to a package at the front when opening 
//the back of the truck is the first to be deliver and the one in the back is to be
//delivered last. This ADT is managed by a linear linked list of arrays, managed
//by two structs and a class. The size of the array will be determined by the user,
//consider it as how high of a pile packages should be placed in a truck. Then, new
//information will be added at the head node, and each subsequent item in the array.

//The queue ADT imitates a list of customers whose packages are being delivered, and
//is organized in a Circular Linked List fashion. The customer at the top of the list 
//will have his/her package delivered first. New customers are added at the bottom of 
//the list. Note, these two ADTs do not yet work in conjunction. That is, when the 
//application prompt for information about a package, it asks for information about 
//the customer and then information about the package that is stored in the truck. 
//Since the first customer would then have his/her package in the back of the truck, 
//the first customer cannot really have his/her package delivered first.

//However, the user will have options to manipulate these with each ADT's respective
//functions. After asking to enter all of the packages' information, the user may 
//select to display all of the customers in the list or all of the packages in the 
//truck that is presented in a stack. There will also be options to use the push,
//pop, enqueue, dequeue, and peek to manipulate the queue and stack.  



using namespace std;

int main()
{
	char sender[100]; //Store customer information.
	char recipient[100]; //Store customer information.
	char size; //Store package's size.
	char name[100]; //Store name of package, NOT customer's name.
	char content[300]; //Store contents of package.
	char response = 'N'; //Hold response to repeat.
	int response2 = 0; //Hold response for options.
	int max = 0; //Read in maximum size of the array from the user.
	
	//Welcome.
	cout << "\n\nIn this application, the user can enter information regarding" << endl;
	cout << "a package (sender's info, recipient's info, package's size)," << endl;
	cout << "which will be kept in a list. The user will also be prompted to" << endl;
	cout << "enter the package's other information (name and content), which" << endl;
	cout << "will be kept in a stack. Depending on how the user wants to approach" << endl;
	cout << "this, he or she may deliver the packages in reverse order that they were" << endl;
	cout << "placed in the truck (first package loaded all the way in the back) or" << endl;
	cout << "according to the list of the customers." << endl;
	
	cout << "\nWhat should the maximum size of the pile of each stack be in the truck? ";
	cin >> max;
	cin.ignore(100, '\n');
	
	stack my_package(max); //Constructor that read in size of array.
	queue my_list; //Declare instance of class queue.
	
	do
	{
		cout << "\nEnter sender's information: ";
		cin.get(sender, 100);
		cin.ignore(100,'\n');
		
		cout << "\nEnter recipient's information: ";
		cin.get(recipient, 100);
		cin.ignore(100,'\n');
		
		cout << "\nEnter package's size (S/M/L): ";
		cin >> size;
		cin.ignore(100,'\n');
		
		//Starts buildling queue.
		if (my_list.enqueue(sender, recipient, size))
			cout << "Info has been added to list." << endl;
		
		cout << "\nEnter package's name: ";
		cin.get(name, 100);
		cin.ignore(100, '\n');
	
		cout << "\nEnter package's content: ";
		cin.get(content, 100);
		cin.ignore(100, '\n');
		
		//Starts building stack.
		if (my_package.push(name, content))
			cout << "\nPackage information added to stack." << endl;
		
		cout << "\nDo you want to add another (Y/N)? ";
		cin >> response;
		cin.ignore(100, '\n');
		
	} while (toupper(response) == 'Y');
	
	do
	{
		//Displaying options on what users would like to do.
		cout << "\n\nWhat would you like to do?" << endl;
		cout << "Enter 1 to peek at the item currently at the back of the truck." << endl;
		cout << "(Package's name and content at top of stack)." << endl;
		cout << "Enter 2 to peek at the current customer on top of list." << endl;
		cout << "(Sender's and recipient's information and package's size)." << endl;
		cout << "Enter 3 to remove item at back of truck (top of stack)." << endl;
		cout << "Enter 4 to remove customer at top of list." << endl;
		cout << "Enter 5 to display the customer's list." << endl;
		cout << "Enter 6 to display the package's stack (arrangment in truck)." << endl;
		cout << "Enter 7 to quit application." << endl;
		cin >> response2;
		cin.ignore(100, '\n');
		
		if (response2 == 1)
		{
			cout << "\nThis is the item currently at the back of the truck:" << endl;
			my_package.peek();
		}
		
		else if (response2 == 2)
		{
			cout << "\nThis is currently the customer at the top of the list:" << endl;
			my_list.peek();
		}
		
		else if (response2 == 3)
		{
			if (my_package.pop())
			{
				cout << "\nContents of container after removing:" << endl;
				my_package.display();
			}
		
			else
				cout << "\nNothing could be removed. Container is empty." << endl;
		}
		
		else if (response2 == 4)
		{
			if (my_list.dequeue())
			{
				cout << "\nList after removing first: ";
				my_list.display();
			}
		
			else
				cout << "\nNothing removed. List is empty." << endl;
		}
		
		else if (response2 == 5)
		{
			cout << "\nThis is the customer's list:" << endl;
			if (my_list.display());
			else
				cout << "\nList is empty." << endl;
		}
		
		else if (response2 == 6)
		{
			cout << "\nThis is the packages' stack (arrangement in truck):" << endl;
			if (my_package.display());
			else
				cout << "\nTruck is empty." << endl;
		}
	} while (response2 != 7);
	
	return 0;
}