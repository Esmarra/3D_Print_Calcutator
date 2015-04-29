/*=========================================
Program Name :	3D print Calculator Algorithm
Base Language:		English
Created by   :	Esmarra
Creation Date:	17/02/2015
Rework date entries:
    28/05/2015 -> Working with mass and lenght

Program Objectives:
    Build stable algorithm to implement on Html5
Observations:
	Based on Excel Calculator and
Special Thanks:
=========================================*/

#include <iostream>
#include <iomanip> // Using set precision
#include <cstdlib> //Using System

using namespace std;

//=== YOUR VALUES & RATES ===
float machine_payrate = 2.5 ; 					    // Machine Cost per Hour
float human_payrate = 10 ;							// Human Cost per Hour
float profit_margin = 135 ;							// Profit Margin [Percentage]
//=== ######### ######### ===


//=== Calculator input Values ===
float print_time = 0 ; 								// Time in minutes from p.hour and p.minute	[Minutes]
float setup_time = 0 ;								// First Layer / Extruder Heating time 	    [Minutes]
float print_length = 0;                             // Length of the print, after slicing       [Millimeters]
float print_mass = 0 ;								// Print Mass		                        [Grams]
float print_cost = 0 ;                              // Total Cost of the Print                  [Euro]

float babysitting_time = 5 ; 						// Required attention time to print 	    [Minutes]
float nonprinted_partscost = 0 ;					// Non Printed Parts Cost example: Metal Nut Inside print		[Euro]
//=== #########     ######### ===

//=== Other Common Variables ===
int debug = 0;                                      // Set to 1 to get debug feedback
int print_minute = 0 ;                              // Defines print time in minutes
int print_hour = 0 ;                                // Defines print time in minutes
float print_second = 0 ;                            // Defines print time in minutes
char Exit='n';                                      // End Program
char go='n';                                        // Start Program
//=== #########    ######### ===

//=== Functions ===
void run();
float calculate_print_time(int &print_hour,int &print_minute, float &print_second);
//=== ######### ===

struct plastic {
    string name ;
    float diameter;
    float density ;
    float kg_cost ;
    float area;
};

int main(){

    while(Exit=='n'){
        system("cls");
        go='n';
        run();                                      // Main Program is Here

        cout<<"\n \t \t   Do you whish to quit the program ? (y/n): ";
        cin>>Exit;
    }
}

void run(){
    cout<<"\t \t 3D Print Cost Calculator By Esmarra V0.1 28/04/2015  \n \n";

    // Generate PLA STRUCT
    struct plastic PLA;
    PLA.name="PLA" ;
    PLA.diameter=1.75;
    PLA.density=0.00125;
    PLA.kg_cost=34.56;
    PLA.area=PLA.diameter/2 * PLA.diameter/2 * 3.1415926535897932384626433832795 ;

    //RESETS
    print_time = 0;
    setup_time = 0 ;
    print_length =0 ;
    print_mass = 0 ;
    while ( print_time == 0){
        cout <<"\n Type print time: "<<endl;
        cout <<"\t Hours: ";
        cin >> print_hour;
        cout <<"\t Minutes: ";
        cin >> print_minute;
        cout <<"\t Seconds: ";
        cin >> print_second;
        print_time = calculate_print_time(print_hour,print_minute,print_second);
    }

    if( debug == 1) cout << "print time: "<< print_time <<" min."<<endl;

    while ( setup_time == 0 || setup_time >= print_time){
        cout <<"\n Type print setup time(min): ";
        cin >> setup_time;
    }

    if (debug ==1 )cout << "Setup time(min): "<< setup_time <<endl;

    while ( print_length ==0 ){
        cout << "\n Type Total Print Length(mm): ";
        cin >> print_length;
    }

    if (debug ==1 )cout << "Length(mm): "<< print_length <<endl;


    print_mass = PLA.area * print_length * PLA.density;


    print_cost = ((print_time * (machine_payrate / 60)) +
                    ((print_time / 100 * babysitting_time) * (human_payrate / 60 / 10)) +
                        (setup_time * (human_payrate / 60)) + (print_mass * (PLA.kg_cost / 1000)) +
                            nonprinted_partscost) / 100 * (100 + profit_margin);

	cout<<"\n Total Printing Cost : "<<print_cost<<endl;
	cout <<"\n Final Cost : "<< setprecision(3) << print_cost<< "$"<<endl;

}

float calculate_print_time(int &print_hour,int &print_minute, float &print_second){

    float print_time = print_minute + (print_hour*60) + (print_second/60) ;
    return(print_time);
}
