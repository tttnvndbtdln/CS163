#include <iostream>
#include <cctype>
#include <cstring>

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



/*~~~~~START STACK-RELATED~~~~~*/



//This struct stores the information of the packages that are stored in the truck.
struct container
{
	char * package_name;
	char * package_content;
};	



//Node struct for the Linear Linked List. 
//Each node will container a pointer that points to the previous struct, which
//contains information about the packages, as well as a next pointer.
struct node
{
	container * packages; //dynamically allocated array of containers
	node * next;
};



//The class stack manages the class. 
class stack
{
	public:
		stack(int max); //Constructor that will receive the size of the array.
		~stack(); //Destructor
		
		//Push new item on top of the stack. Previous top will be second to top.
		//INPUT: This function takes in two parameters: the name and the content of
		//the package. It will then store these information into the array that the LLL
		//points to.
		//OUTPUT: Return success/failture state.
		int push(char *, char *);
		
		//Remove item at the top of the stack. Second to top then become top.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int pop(void);
		
		//Peek at the top item of the stack. Makes no changes to stack.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int peek() const;
		
		//Display all items in the stack.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int display();
		
	private:
		node * head; //Head pointer.
		int top_index; //Manages which position in the array the items are being manipulated.
		int MAX; //Max size of array.
};



/*~~~~~START QUEUE-RELATED~~~~~*/



//Nodes that contain information about the customer to be stored in a list.
struct q_node
{
	char * sender_info;
	char * recipient_info;
	char package_size;
	q_node * next;
};



//Class queue that manages the queue via Circular Linked List. 
class queue
{
	public:
		queue(void); //Constructor
		~queue(void); //Destructor
		
		//Add item at the rear of the queue (CLL). Previous last will be second to last.
		//INPUT: This function takes in 3 parameters from user regarding the 
		//customer and store them in the above struct's data members. 
		//OUTPUT: Return success/failture state.
		int enqueue(char *, char *, char);
		
		//Remove item at the beginning of the queue (CLL). Previous second is then first.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int dequeue(void);
		
		//Peek at the first item in the list. Makes no changes to the list.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int peek() const;
		
		//Display all items in the list.
		//INPUT: Take no arguments.
		//OUTPUT: Return success/failture state.
		int display(void) const;
	
	private:
		q_node * rear; //Rear pointer to last node of CLL.
};