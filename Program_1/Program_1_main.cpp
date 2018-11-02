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

//This file is the main application that interacts with the user.

using namespace std;

int main ()
{
	const char outfile[] = "airport.txt"; //outfile's name.
	
	//Arrays to temporarily read in the information from the user.
	char first_city[SIZE];
	char second_city[SIZE];
	char third_city[SIZE];
	char fourth_city[SIZE];
	char fifth_city[SIZE];
	
	//Chars to read in the administrative information from the user.
	char dom_v_int;
	char immigration;
	char fast_pass;
	
	//Int to, respectively, read in the number of trips the user will take,
	//the number of layovers the user will have, and to read in which trip
	//the user would like to display. The last (order_of_trips) is used to
	//keep track of which trip the application is working on buildling.
	int trips = 0, layovers = 0, display_trip = 0, order_of_trips = 0;
	
	//Variable to catch the return value of the check_time function.
	int time_check = 0;
	
	//Variables to hold the departure and arrival times. 
	float departure_time1 = 0, departure_time2 = 0, arrival_time = 0;
	
	char response = 'N';
	
	//Declare an instance of airport_time_list class.
	airport_time_list list;
	
	if (list.read_and_store(outfile))
		cout << "Airport information read in." << endl;
	else
		cout << "Info not read in." << endl;
	
	//cout << "Here's a list of airports we have." << end;
	//list.display();

	airport trip;
	trip.read_in(outfile);
	
	cout << "\nHow many trips are you planning to take?" << endl;
	cout << "(For example, a two way trip from Portland to" << endl;
	cout << "New York then from New York back to Portland" << endl;
	cout << "would be 2 trips with no layovers.)" << endl;
	cin >> trips;
	cin.ignore(100,'\n');
	
	trip.initiate_itinerary(trips);
	
	do
	{
		cout << "\nFor this trip, how many layovers are there? " << endl;
		cout << "If you have more than 3 layovers, consider choosing" << endl;
		cout << "another flight path, because our programmer is" << endl;
		cout << "not smart enough to help you with more than 3" << endl;
		cout << "layovers." << endl;
		cin >> layovers;
		cin.ignore(100,'\n');
	
		cout << "\nIs this trip domestic or international (D/I)? ";
		cin >> dom_v_int;
		cin.ignore(100,'\n');
	
		cout << "Does immigration applies (Y/N)? ";
		cin >> immigration;
		cin.ignore(100,'\n');
	
		cout << "Do you have fast pass through checkpoints (Y/N)? ";
		cin >> fast_pass;
		cin.ignore(100,'\n');
	
		trip.build_admin(dom_v_int,immigration,fast_pass,order_of_trips);
	
		cout << "Enter first city: ";
		cin.get(first_city,SIZE,'\n');
		cin.ignore(100,'\n');
		
		cout << "Enter departure time from first city." << endl;
		cout << "(Please use 24 hour and decimal time format." << endl;
		cout << "For example, if the departure time is 2:30 PM," << endl;
		cout << "please enter 14.5 for departure time.): ";
		cin >> departure_time1;
		cin.ignore(100,'\n');
	
		cout << "Enter second city: ";
		cin.get(second_city,SIZE,'\n');
		cin.ignore(100,'\n');
		
		cout << "Enter arrival time at second city: ";
		cin >> arrival_time;
		cin.ignore(100,'\n');
		
		cout << "Enter departure time from second city: " << endl;
		cout << "(Enter 0 if this is your destination) ";
		cin >> departure_time2;
		cin.ignore(100,'\n');
	
		if (layovers >= 0)
		{
			if (trip.build_itinerary_two_cities(first_city, second_city, departure_time1,
				departure_time2, arrival_time, order_of_trips))
				cout << "Itinerary built." << endl;
			else
				cout << "Sorry. Try again" << endl;
		}
		
		if (layovers >= 1)
		{
			time_check = trip.check_time(second_city, departure_time2, arrival_time, order_of_trips);
			
			if (time_check == 0)
				cout << "We had errors performing time calculations. Time check not possible." << endl;
			else if (time_check == 1)
				cout << "You will most likely have enough time during the layover." << endl;
			else if (time_check == 2)
				cout << "Caution, you'll have little more than 15 minutes of free time during the layover." << endl;
			else if (time_check == 3)
				cout << "There is a high chance you might miss the flight to your destination!" << endl;
			else
				cout << "Consider changing flight plan, as you will miss your flight." << endl;
			
			cout << "Enter third city: ";
			cin.get(third_city,SIZE,'\n');
			cin.ignore(100,'\n');
			
			cout << "Enter arrival time at third city: ";
			cin >> arrival_time;
			cin.ignore(100,'\n');
			
			cout << "Enter departure time from third city: " << endl;
			cout << "(Enter 0 if this is your destination) ";
			cin >> departure_time1;
			cin.ignore(100,'\n');
		
			if (trip.build_itinerary_three_cities(third_city, departure_time1, arrival_time))
				cout << "Itinerary built." << endl;
			else
				cout << "Sorry. Try again" << endl;
			
			
		}
	
		if (layovers >= 2)
		{
			time_check = trip.check_time(third_city, departure_time1, arrival_time, order_of_trips);
			
			if (time_check == 0)
				cout << "We had errors performing time calculations. Time check not possible." << endl;
			else if (time_check == 1)
				cout << "You will most likely have enough time during the layover." << endl;
			else if (time_check == 2)
				cout << "Caution, you'll have little more than 15 minutes of free time during the layover." << endl;
			else if (time_check == 3)
				cout << "There is a high chance you might miss the flight to your destination!" << endl;
			else
				cout << "Consider changing flight plan, as you will miss your flight." << endl;
			
			cout << "Enter fourth city: ";
			cin.get(fourth_city,SIZE,'\n');
			cin.ignore(100,'\n');
			
			cout << "Enter arrival time at fourth city: ";
			cin >> arrival_time;
			cin.ignore(100,'\n');
			
			cout << "Enter departure time from fourth city: " << endl;
			cout << "(Enter 0 if this is your destination " << endl;
			cin >> departure_time1;
			cin.ignore(100,'\n');
			
			if (trip.build_itinerary_four_cities(fourth_city, departure_time1, arrival_time))
				cout << "Itinerary built." << endl;
			else
				cout << "Sorry. Try again" << endl;
		}
		
		if (layovers == 3)
		{
			time_check = trip.check_time(fourth_city, departure_time1, arrival_time, order_of_trips);
			
			if (time_check == 0)
				cout << "We had errors performing time calculations. Time check not possible." << endl;
			else if (time_check == 1)
				cout << "You will most likely have enough time during the layover." << endl;
			else if (time_check == 2)
				cout << "Caution, you'll have little more than 15 minutes of free time during the layover." << endl;
			else if (time_check == 3)
				cout << "There is a high chance you might miss the flight to your destination!" << endl;
			else
				cout << "Consider changing flight plan, as you will miss your flight." << endl;
			
			cout << "Enter fifth city: ";
			cin.get(fifth_city,SIZE,'\n');
			cin.ignore(100,'\n');
			
			cout << "Enter arrival time at fifth city: ";
			cin >> arrival_time;
			cin.ignore(100,'\n');
			
			if (trip.build_itinerary_five_cities(fifth_city, arrival_time))
				cout << "Itinerary built." << endl;
			else
				cout << "Sorry. Try again" << endl;
		}
		
		++order_of_trips;
		
	} while (order_of_trips < trips);
	
	cout << "Here is your itinerary:" << endl << endl;
	trip.display_itinerary(trips);
	
	cout << "\nDo you want information regarding a trip? ";
	cin >> response;
	cin.ignore(100,'\n');
	
	if (toupper(response) == 'Y')
	{
		cout << "For which trip would you like information on?" << endl;
		cout << "(Enter 1 for first, 2 for second, etc.): ";
		cin >> display_trip;
		cin.ignore(100,'\n');
	
		trip.display_journey(display_trip);
	}
	
	return 0;
}
