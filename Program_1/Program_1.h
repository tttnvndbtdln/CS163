#include <iostream>
#include <cstring>
#include <cctype>
#include <fstream>

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

//This .h file stores all of the data structures that the program uses, including structs to manage
//the airport information, structs to manage the flight information, and the classes that manage 
//all of them.

const int SIZE = 100; //Global constant

//This struct node will store information about the
//first data structure (LLL to store the airport
//information (number of customs, time spent at each
//customs/immigration checkpoints, and the total time
//spent traveling from gate to gate.
//This struct is not called node because there is
//another struct called node that was made before this
//one.
struct time_list
{
	char * airport_name;
	int no_of_customs;
	float time_at_customs;
	float time_travel_between_gates;
	time_list * next;
};


//This class will manage the previous struct time_list
//by reading in information from the external file and
//storing the information in a LLL using the struct.
class airport_time_list
{
	public:
		airport_time_list(); //Constructor
		~airport_time_list(); //Destructor
		
		//This function will read in airport information
		//from the external file and build a LLL of it.
		//INPUT: It takes in the name of the external file.
		//OUTPUT: Will report success/failure of reading in
		//with an int return type.
		int read_and_store(const char *);
		
		//Extra function. Used to display the LLL read
		//in from external file. Debug function.
		//INPUT: Takes in no argument.
		//OUTPUT: Will display the LLL of airport information.
		void display();
	
	private:
		//Head pointer pointing to the first node
		//which will be the first airport reading in
		//from the external file.
		time_list * head;
};



//~~~~~~~~~~END OF FIRST DATA STRUCTURE~~~~~~~~~~



//Struct to display the trip details for the
//second data structure (after the first node
//of administrative information; see below).
struct node
{
	char * airport_city;
	float arrival_time;
	float departure_time;
	node * next;
};



//Struct to display only the first node for the
//second data structure (admin info about flight).
struct air_details
{
	char dom_v_int;
	char immigration;
	char fast_pass;
	
	//The next pointer of this struct is not to itself
	//but rather to a node containing information about
	//the rest of the flight details (see struct above).
	node * next;
};



//This class manages both the previous structs in building a
//traveler's itinerary. 
class airport
{
	public:
		airport(); //Constructor to initialize all data members
		~airport(); //Destructor to deallocate memories
		
		//This function simply allocates memory for the array of LLL.
		//It declares journeys to be an array of pointers of trips size.
		//INPUT: The number of trips the user would like to take.
		//OUTPUT: Success/failure.
		int initiate_itinerary(int);
		
		//This function initialize the itinerary. That is, it builds
		//the first node, storing the administrative information in
		//the air_details struct.
		//INPUT: Administrative information about the flight: domestic vs.
		//international, immigration status, and fast pass. These are simply
		//stored as characters. It also takes in the order of the flight (int). This
		//is a local variable in the application that lets the program
		//know which trip this is. 
		void build_admin(char, char, char, int);
		
		//This function builds a trip based on only 2 cities (source and 
		//destination). 
		//INPUT: Names of first and second cities, departure time from first city,
		//departure time from second city, arrival time, and the order of the flight,
		//respectively. 
		//OUTPUT: Returns success/failure state back to calling routine.
		int build_itinerary_two_cities(char *, char *, float, float, float, int);
		
		//Similar to above function of buildling two cities but this time simply 
		//add on a third city to the LLL.
		//INPUT: Third city's name, departure and arrival times at the city.
		//OUTUT: Returns success/failure.
		int build_itinerary_three_cities(char *, float, float);
		
		//Exactly like the function above but for the fourth city.
		//INPUT: Fourth city's name, departure and arrival times at the city.
		//OUTUT: Returns success/failure.
		int build_itinerary_four_cities(char *, float, float);
		
		//For buildilng the last city (destination).
		//INPUT: Only needs the city's name and the arrival time.
		//OUTPUT: Returns success/failure. 
		int build_itinerary_five_cities(char *, float);
		
		//This is for displaying the entire itinerary. 
		//INPUT: Takes in the number of total trips that the user supplied
		//at the beginning.
		//OUTPUT: Displays the itinerary.
		void display_itinerary(int);
		
		//This is similar to the above function but only display a certain trip.
		//INPUT: Takes in the trip that the user wants to see (1 for first trip, etc.)
		//OUTPUT: Displays the appropriate trip.
		void display_journey(int);
		
		//This function compares the time that the traveler has at an airport and the
		//time listed in the external file to see if the user will have enough time not
		//to miss the flight.
		//INPUT: Name of the city, departure time, arrival time, and the order of the trip
		//to see which trip it is. 
		//OUTPUT: Return an int letting the application know approximately the amount of time
		//(e.g. 0 for errors, 1 for will make it on time, 2 for running close, 3 for right
		//time, and 4 for definitely late and will be missing flight).
		int check_time(char *, float, float, int);
		
		//Somehow the list read in from the external file is destroyed and/or the head pointer
		//is reset to NULL, so this function was created to read in the file again.
		//INPUT: Name of the external file.
		//OUTPUT: None. Simply create the LLL like above. 
		void read_in(const char *);
		
	private:
		air_details ** journeys; //An array of pointers
		node * tail; //Tail pointer (Was not used)
		time_list * head;
};
