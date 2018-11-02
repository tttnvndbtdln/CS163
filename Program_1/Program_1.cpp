#include "Program_1.h"

//Phuong Pham
//CS 163
//April 2016
//Program 1

//This program is designed to help a traveler builds his or her itinerary. The program will first
//read in information from an external file about all of the different airports. Information about
//these airports include the name of the city the airport is located in, the number of customs or
//security checkpoints that it has, the average amount of time someone has to wait at these 
//checkpoints, and the average time to travel between the different gates at an airport. The program
//will then prompt the user for information to build the itinerary. It will first ask about the total
//number of trips that the user will take. Then for each of those trips, the program will asks for
//the number of layovers and administrative information about that trip (e.g. whether the trip is
//international or domestic, if immigration applies, and if the user has a fast pass to travel
//through security checkpoints). The program then starts to build the itinerary and continues to
//asks for information about the cities that the traveler will be going through (up to a maximum of
//3 layovers), as well as pertinent information about those layovers, such as departure and arrival
//times. As the user is doing this, it also attempts to the check if the user will have enough time
//at each layovers in order not to miss the next flight. It does so by comparing the time the user has
//between arrival time and departure time to the sum of the time necessary to go through security
//checkpoints (information that was read in from the external file). Lastly, once all the information
//are entered, it displays the traveler's itinerary and asks if the user wants to see each different
//trip as well, which simply only shows one trip. 

//This file contains the implementation of all the member functions established in the .h file. 

//Class airport_time_list constructor.
airport_time_list::airport_time_list()
{
	head = NULL;
}



//Class airport_time_list destructor.
//Destructor will also destroy the linear linked list
//created (inside while loop below). 
airport_time_list::~airport_time_list()
{
	time_list * current = head;
	while (current != NULL)
	{
		time_list * temp = current -> next;
		if (current -> airport_name)
			delete [] current -> airport_name;
		delete current;
		current = temp;
	}
	head = NULL;
}



//Class airport constructor.
airport::airport()
{
	journeys = NULL;
	tail = NULL;
	head = NULL;
}



//Class airport destructor.
//Destructor will also destroy the array of LLL. 
airport::~airport()
{
	int i = 0;
	
	//while (journeys[i] -> next != NULL)
	//{
		node * current = journeys[i] -> next;
		while (current != NULL)
		{
			node * temp = current -> next;
			if (current -> airport_city)
				delete [] current -> airport_city;
			delete current;
			current = temp;
		}
	//	++i;
	//}
	
	journeys = NULL;
	tail = NULL;
	head = NULL;
}



/*~~~~~~~~~~FINISH CONSTRUCTORS/DESTRUCTORS~~~~~~~~~~*/



//This function will read in airport information
//from the external file and build a LLL of it.
//INPUT: It takes in the name of the external file.
//OUTPUT: Will report success/failure of reading in
//with an int return type.
int airport_time_list::read_and_store(const char * outfile)
{
	using namespace std;
	//A char array to temporarily store the name of the airports
	//read in from the external file and then do a deep copy into the
	//the data member of the struct. 
	char tempo[SIZE]; 
	
	time_list * temp = new time_list; //Starts the LLL
	head = new time_list;
	
	ifstream in_file; 
	in_file.open(outfile);
	
	if (in_file)
	{
		//Prime the pump.
		in_file.get(tempo,100,'\n');
		in_file.ignore(100,'\n');
		
		//Deep copy.
		temp -> airport_name = new char[strlen(tempo) + 1];
		strcpy(temp -> airport_name,tempo);
		
		in_file >> temp -> no_of_customs;
		in_file.ignore(100,'\n');
		
		in_file >> temp -> time_at_customs;
		in_file.ignore(100,'\n');
		
		in_file >> temp -> time_travel_between_gates;
		in_file.ignore(100,'\n');
		
		head = temp;
		time_list * current = head;
		
		while (!in_file.eof())
		{
			temp = new time_list;
			
			in_file.get(tempo,100,'\n');
			in_file.ignore(100,'\n');

			temp -> airport_name = new char[strlen(tempo) + 1];
			strcpy(temp -> airport_name,tempo);
		
			in_file >> temp -> no_of_customs;
			in_file.ignore(100,'\n');
		
			in_file >> temp -> time_at_customs;
			in_file.ignore(100,'\n');
		
			in_file >> temp -> time_travel_between_gates;
			in_file.ignore(100,'\n');
			
			temp -> next = NULL;
			current -> next = temp;
			current = temp;
		}
		return 1;
	}
	
	else
		return 0;
}



//Extra function. Used to display the LLL read
//in from external file. Debug function.
//INPUT: Takes in no argument.
//OUTPUT: Will display the LLL of airport information.
void airport_time_list::display()
{
	using namespace std;
	
	time_list * current = head;
	
	while (current)
	{
		cout << current -> airport_name << endl;
		cout << current -> no_of_customs << endl;
		cout << current -> time_at_customs << endl;
		cout << current -> time_travel_between_gates << endl;
		current = current -> next;
	}
}		



/*~~~~~~~~~~FINISH FIRST DATA STRUCTURE~~~~~~~~~~*/



//This function simply allocates memory for the array of LLL.
//It declares journeys to be an array of pointers of trips size.
//INPUT: The number of trips the user would like to take.
//OUTPUT: Success/failure.
int airport::initiate_itinerary(int trips)
{
	//journeys will be an array of pointers that point to node 
	//of type air_details, which will be the first node of every trips.
	if (trips == 0) //Can't have 0 trips. 
		return 0;
	journeys = new air_details * [trips];
	return 1;
}



//This function initialize the itinerary. That is, it builds
//the first node, storing the administrative information in
//the air_details struct.
//INPUT: Administrative information about the flight: domestic vs.
//international, immigration status, and fast pass. These are simply
//stored as characters. It also takes in the order of the flight (int). This
//is a local variable in the application that lets the program
//know which trip this is. 
void airport::build_admin(char dom_v_int, char immigration, char fast_pass, int order)
{
	//Set first head pointer to new node.
	journeys[order] = new air_details;
	
	//Store trip's administrative information into first node, pointed to
	//by first head pointer.
	journeys[order] -> dom_v_int = dom_v_int;
	journeys[order] -> immigration = immigration;
	journeys[order] -> fast_pass = fast_pass;
	journeys[order] -> next = NULL;
}



//This function builds a trip based on only 2 cities (source and 
//destination). 
//INPUT: Names of first and second cities, departure time from first city,
//departure time from second city, arrival time, and the order of the flight,
//respectively. 
//OUTPUT: Returns success/failure state back to calling routine.
int airport::build_itinerary_two_cities(char * first_city, char * second_city,
float depart1, float depart2, float arrival, int order)		
{
	if (depart1 == depart2 || depart2 == arrival)
		return 0; //A person can't be in 2 places at once. 
	
	//Set tail pointer to new node. Tail is pointing to a type of node
	//called node.
	tail = new node;
	
	node * temp = new node; //Create temp node
	
	//Head -> next is now pointing to temp, which is a type of node that is
	//used for the rest of the linked list.
	journeys[order] -> next = temp;
	
	temp -> airport_city = new char [strlen(first_city) + 1];
	strcpy (temp -> airport_city,first_city);
	temp -> departure_time = depart1;
	
	node * current = temp;
	
	temp = new node;
	temp -> airport_city = new char [strlen(second_city) + 1];
	strcpy (temp -> airport_city, second_city);
	temp -> arrival_time = arrival;
	temp -> departure_time = depart2;
	temp -> next = NULL;
	
	current -> next = temp;
	current = current -> next;
	tail = current;
	
	return 1;
}



//Similar to above function of buildling two cities but this time simply 
//add on a third city to the LLL.
//INPUT: Third city's name, departure and arrival times at the city.
//OUTUT: Returns success/failure.
int airport::build_itinerary_three_cities(char * third_city, float depart, float arrival)
{
	if (depart == arrival)
		return 0; //Good luck catching that next flight.
	
	node * temp = new node;
		
	temp -> airport_city = new char [strlen(third_city) + 1];
	strcpy (temp -> airport_city,third_city);
	temp -> arrival_time = arrival;
	temp -> departure_time = depart;
	temp -> next = NULL;
		
	tail -> next = temp;
	tail = temp;
		
	return 1;
}	



//Exactly like the function above but for the fourth city.
//INPUT: Fourth city's name, departure and arrival times at the city.
//OUTUT: Returns success/failure.
int airport::build_itinerary_four_cities(char * fourth_city, float depart, float arrival)
{
	if (depart == arrival)
		return 0;
	
	node * temp = new node;
		
	temp -> airport_city = new char [strlen(fourth_city) + 1];
	strcpy (temp -> airport_city,fourth_city);
	temp -> arrival_time = arrival;
	temp -> departure_time = depart;
	temp -> next = NULL;
		
	tail -> next = temp;
	tail = temp;
		
	return 1;
}	
		
	

//For buildilng the last city (destination).
//INPUT: Only needs the city's name and the arrival time.
//OUTPUT: Returns success/failure. 
int airport::build_itinerary_five_cities(char * fifth_city, float arrival)
{
	node * temp = new node;
		
	temp -> airport_city = new char [strlen(fifth_city) + 1];
	strcpy (temp -> airport_city,fifth_city);
	temp -> arrival_time = arrival;
	temp -> next = NULL;
		
	tail -> next = temp;
	tail = temp;
		
	return 1;
}	



//This is for displaying the entire itinerary. 
//INPUT: Takes in the number of total trips that the user supplied
//at the beginning.
//OUTPUT: Displays the itinerary.
void airport::display_itinerary(int trips)
{
	using namespace std;
	
	if (!journeys[0])
		return;
	
	for (int i = 0; i < trips; ++i)
	{
		air_details * current = journeys[i];
		
		if (toupper(current -> dom_v_int) == 'D')
			cout << "\nTrip is domestic." << endl;
		else
			cout << "\nTrip is international." << endl;

		if (toupper(current -> immigration) == 'Y')
			cout << "Immigration applies." << endl;
		else
			cout << "Immigration does not apply." << endl;
		
		if (toupper(current -> fast_pass) == 'Y')
			cout << "You have a fast pass." << endl;
		else
			cout << "You do not have a fast pass." << endl;
		
		node * temp = current -> next;
		
		if (temp -> next != NULL)
		{
			cout << "First city: " << temp -> airport_city << endl;
			cout << "Departure time: " << temp -> departure_time << endl;
		
			while (temp -> next != NULL)
			{
				temp = temp -> next;
				cout << "City: " << temp -> airport_city << endl;
				cout << "Arrival time: " << temp -> arrival_time << endl;
				
				if (temp -> departure_time != 0)
					cout << "Departure time: " << temp -> departure_time << endl;
			}
		}
	}
}



//This is similar to the above function but only display a certain trip.
//INPUT: Takes in the trip that the user wants to see (1 for first trip, etc.)
//OUTPUT: Displays the appropriate trip.
void airport::display_journey(int display)
{
	using namespace std;
	
	if (!journeys[display - 1])
		return;
	
	air_details * current = journeys[display - 1];
	
	if (toupper(current -> dom_v_int) == 'D')
		cout << "Trip is domestic." << endl;
	else
		cout << "Trip is international." << endl;

	if (toupper(current -> immigration) == 'Y')
		cout << "Immigration applies." << endl;
	else
		cout << "Immigration does not apply." << endl;
		
	if (toupper(current -> fast_pass) == 'Y')
		cout << "You have a fast pass." << endl;
	else
		cout << "You do not have a fast pass." << endl;
		
	node * temp = current -> next;
		
	if (temp -> next != NULL)
	{
		cout << "First city: " << temp -> airport_city << endl;
		cout << "Departure time: " << temp -> departure_time << endl;
		
		while (temp -> next != NULL)
		{
			temp = temp -> next;
			cout << "City: " << temp -> airport_city << endl;
			cout << "Arrival time: " << temp -> arrival_time << endl;
				
			if (temp -> departure_time != 0)
				cout << "Departure time: " << temp -> departure_time << endl;
		}
	}
}

	

//This function compares the time that the traveler has at an airport and the
//time listed in the external file to see if the user will have enough time not
//to miss the flight.
//INPUT: Name of the city, departure time, arrival time, and the order of the trip
//to see which trip it is. 
//OUTPUT: Return an int letting the application know approximately the amount of time
//(e.g. 0 for errors, 1 for will make it on time, 2 for running close, 3 for right
//time, and 4 for definitely late and will be missing flight).
int airport::check_time(char * city, float depart2, float arrival, int order)
{
	using namespace std;
	
	char temp_city[100];
	float sum_of_time = 0, actual_time = 0;
	
	air_details * temp = journeys[order];
	time_list * current = head;
	
	cout << city << endl;
	cout << current -> airport_name << endl;
	
	while (current)
	{
		if (strcmp(city, current -> airport_name) == 0)
		{
			if (toupper(temp -> fast_pass) == 'N')
				sum_of_time = current -> no_of_customs * current -> time_at_customs + current -> time_travel_between_gates;
			else
				sum_of_time = current -> time_travel_between_gates;
			
			actual_time = depart2 - arrival;
				
			if (sum_of_time - actual_time >= 0.5)
				return 1;
				
			else if (sum_of_time - actual_time >= 0.25)
				return 2;
				
			else if (sum_of_time - actual_time >= 0)
				return 3;
				
			else
				return 4;
		}
		current = current -> next;
	}
	
	return 0;
}



//Somehow the list read in from the external file is destroyed and/or the head pointer
//is reset to NULL, so this function was created to read in the file again.
//INPUT: Name of the external file.
//OUTPUT: None. Simply create the LLL like above. 
void airport::read_in(const char * outfile)
{
	using namespace std;
	char tempo[SIZE];
	int i = 0;
	
	time_list * temp = new time_list;
	head = new time_list;
	
	ifstream in_file;
	in_file.open(outfile);
	
	if (in_file)
	{
		in_file.get(tempo,100,'\n');
		in_file.ignore(100,'\n');
		
		temp -> airport_name = new char[strlen(tempo) + 1];
		strcpy(temp -> airport_name,tempo);
		
		in_file >> temp -> no_of_customs;
		in_file.ignore(100,'\n');
		
		in_file >> temp -> time_at_customs;
		in_file.ignore(100,'\n');
		
		in_file >> temp -> time_travel_between_gates;
		in_file.ignore(100,'\n');
		
		head = temp;
		time_list * current = head;
		
		while (!in_file.eof())
		{
			temp = new time_list;
			
			in_file.get(tempo,100,'\n');
			in_file.ignore(100,'\n');

			temp -> airport_name = new char[strlen(tempo) + 1];
			strcpy(temp -> airport_name,tempo);
		
			in_file >> temp -> no_of_customs;
			in_file.ignore(100,'\n');
		
			in_file >> temp -> time_at_customs;
			in_file.ignore(100,'\n');
		
			in_file >> temp -> time_travel_between_gates;
			in_file.ignore(100,'\n');
						temp -> next = NULL;
			current -> next = temp;
			current = temp;
		}
	}
}