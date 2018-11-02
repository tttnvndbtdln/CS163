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



//Class STACK CONSTRUCTOR
stack::stack(int max)
{
	head = NULL;
	top_index = 0;
	MAX = max; //User will specify size of array. 
}



//Class STACK DESTRUCTOR
stack::~stack()
{
	if (head)
	{
		node * current = head; //Current points to first node.
		while (current) //While there is a list.
		{
			current = current -> next; //Traverse current.
			while (top_index > 0) //And there are items in the arrays.
			{
				//Deallocate all dynamic memories.
				delete [] (head -> packages[top_index - 1]).package_name;
				delete [] (head -> packages[top_index - 1]).package_content;
				--top_index;
			}
			delete head -> packages; //Delete the pointer in the node.
			delete head; //Delete the node.
			head = current; //Move head to the next node.
			top_index = MAX; //Reset top_index to MAX to start deleting next node's array.
		}
	}
	head = NULL;
	top_index = 0;
}



//Class QUEUE CONSTRUCTOR
queue::queue()
{
	rear = NULL;
}



//Class QUEUE DESTRUCTOR
queue::~queue()
{
	if (rear) //If there is an item in the list.
	{
		q_node * current = rear -> next; //Current at first node.
		q_node * head = current; //Hang on to start deletion after current traverse.
		rear -> next = NULL; //Establish stopping point.
		while (current)
		{
			delete [] current -> sender_info; //Delete dynamically allocated memories.
			delete [] current -> recipient_info;
			current = current -> next; //Traverse current.
			delete head; //Delete actual node.
			head = current; //Move head to the next node.
		}
	}
	rear = NULL;
}



/*~~~~~START STACK~~~~~*/



//Push new items on top of stack.
//INPUT: This function takes in two parameters: the name and the content of
//the package. It will then store these information into the array that the LLL
//points to.
//OUTPUT: Return success/failure state of adding information to linked list of array
int stack::push(char * name, char * content)
{
	if (!head) //If there is no item.
	{
		head = new node; //New node
		head -> packages = new container[MAX]; //The node will have a pointer to an array
		
		//Start copying the name and content supplied by user using deep copy.
		(head -> packages[top_index]).package_name = new char [strlen(name) + 1];
		strcpy((head -> packages[top_index]).package_name, name);
		
		(head -> packages[top_index]).package_content = new char [strlen(content) + 1];
		strcpy((head -> packages[top_index]).package_content, content);
		
		head -> next = NULL;
		
		//NOTE HERE THAT top_index WILL ALWAYS BE ONE AHEAD OF CURRENT ARRAY'S POSITION.
		//That is, when the new item is added at position array[0], top_index is incremented
		//to 1. When top_index is equal to MAX, the last item in the array should be
		//array[MAX - 1].
		++top_index;
		
		return 1;
	}
	
	else if (top_index == MAX) //If the current array is full. 
	{
		node * temp = head; //Hold on to the first node.
		head = new node; //Head gets new node.
		head -> next = temp; //Connect new node to the previous first node.
		top_index = 0; //Reset top_index.
		
		head -> packages = new container[MAX]; //Node points to new array.
		
		//Deep copy similar to above.
		(head -> packages[top_index]).package_name = new char [strlen(name) + 1];
		strcpy((head -> packages[top_index]).package_name, name);
		
		(head -> packages[top_index]).package_content = new char [strlen(content) + 1];
		strcpy((head -> packages[top_index]).package_content, content);
		
		++top_index;
		return 1;
	}
	
	else
	{
		(head -> packages[top_index]).package_name = new char [strlen(name) + 1];
		strcpy((head -> packages[top_index]).package_name, name);
		
		(head -> packages[top_index]).package_content = new char [strlen(content) + 1];
		strcpy((head -> packages[top_index]).package_content, content);
		
		++top_index;
		return 1;
	}
	
	return 0;
}



//Remove item at the top of the stack.
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int stack::pop(void)
{
	if (!head)
		return 0;
	
	//If popping only one item in an array, need to delete the node.
	else if (top_index == 1)
	{
		node * temp = head -> next;
		delete head;
		head = temp;
		top_index = MAX;
		return 1;
	}
	
	else
	{
		--top_index; //Simply decrement top_index. If push is called again, it will
					 //overwrite what is there. 
		return 1;
	}
}



//Peek at the top item of the stack. Makes no changes to stack.
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int stack::peek() const
{
	using namespace std;
	
	if (!head)
		return 0;
	
	else
	{
		int temp = top_index; 
		cout << "\nPackage's name: ";
		//Since top_index is always one ahead of the current position, needs to subtract one.
		cout << (head -> packages[temp - 1]).package_name << endl;
		cout << "Package's content: ";
		cout << (head -> packages[temp - 1]).package_content << endl;
		return 1;
	}
}



//Display all items in the stack.
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int stack::display()
{
	using namespace std;
	
	if (!head)
		return 0;
	
	node * current = head;
	int temp = top_index;
	
	while (current) //Traverse current to display.
	{
		for (; temp > 0; --temp)
		{
			cout << "\nPackage's name: ";
			cout << (current -> packages[temp - 1]).package_name << endl;
			cout << "Package's content: ";
			cout << (current -> packages[temp - 1]).package_content << endl;
		}
		current = current -> next;
	}
	
	return 1;
}



/*~~~~~START QUEUE~~~~~*/




//Add item at the rear of the queue (CLL).
//INPUT: This function takes in 3 parameters from user regarding the 
//customer and store them in the above struct's data members. 
//OUTPUT: Return success/failture state.
int queue::enqueue(char * sender, char * recipient, char size)
{
	if (!rear) //Nothing in queue.
	{
		q_node * temp = new q_node; //New node.
		
		//Deep copy.
		temp -> sender_info = new char [strlen(sender) + 1];
		strcpy(temp -> sender_info, sender);
		
		temp -> recipient_info = new char [strlen(sender) + 1];
		strcpy(temp -> recipient_info, recipient);
		
		temp -> package_size = size;
		
		rear = temp;
		rear -> next = rear; //Set rear to point to itself since it is the only item.
		
		return 1;
	}
	
	else
	{
		q_node * temp = new q_node;
		
		temp -> sender_info = new char [strlen(sender) + 1];
		strcpy(temp -> sender_info, sender);
		
		temp -> recipient_info = new char [strlen(sender) + 1];
		strcpy(temp -> recipient_info, recipient);
		
		temp -> package_size = size;
		
		temp -> next = rear -> next; //Reconnect the circular linked list. 
									 //Temp is now the "last" node, pointing to the first node.
		rear -> next = temp; //Add at the end, so this node come after current rear node.

		rear = temp; //Point rear to the actual last node.
		return 1;
	}
	
	return 0;
}



//Remove item at the beginning of the queue (CLL).
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int queue::dequeue(void)
{
	if (!rear)
		return 0;
	
	if (rear == rear -> next)
	{
		delete rear;
		rear = NULL;
		return 1;
	}
	
	q_node * temp = rear -> next;
	
	rear -> next = temp -> next;
	delete temp;
	
	return 1;
}



//Peek at the first item in the list. Makes no changes to the list.
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int queue::peek() const
{
	using namespace std;
	
	if (!rear)
		return 0;
	
	else
	{
		q_node * temp = rear -> next;
		cout << "\nSender: " << temp -> sender_info << endl;
		cout << "Recipient: " << temp -> recipient_info << endl;
		cout << "Package's size: " << temp -> package_size << endl;
		return 1;
	}
}



//Display all items in the list.
//INPUT: Take no arguments.
//OUTPUT: Return success/failture state.
int queue::display(void) const
{
	using namespace std;
	
	if (!rear)
		return 0;
	
	else
	{
		q_node * temp = rear -> next; //Turning into LLL.
		q_node * head = temp; //Holding on to first node to reconnect later.
		rear -> next = NULL; //Disconnected CLL.
		
		while (temp)
		{
			cout << "\nSender: " << temp -> sender_info << endl;
			cout << "Recipient: " << temp -> recipient_info << endl;
			cout << "Package's size: " << temp -> package_size << endl;
			temp = temp -> next;
		}
		
		rear -> next = head; //Reconnected CLL.
		return 1;
	}
}