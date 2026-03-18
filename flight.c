//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"

//This function will create a dynamically allocated flight with random values and return its address.
Flight * createRandomFlight(int maxReadyTime, int maxServiceTime){
    //To be completed

    Flight* flight = (Flight*)malloc(sizeof(Flight));

    //Flight type
    int x = rand() % 3 + 1;
    if (x == 3){
      flight -> flightType = 'E';
    }
    else if (x == 2){
      flight -> flightType = 'I';
    }
    else flight -> flightType = 'D';

    //Ready time
    flight -> readyTime = rand () % (maxReadyTime + 1);

    //Service time
    flight -> serviceTime = rand () % (maxServiceTime + 1);

    //Service start time
    flight -> serviceStartTime = 0;

    //Runway number
    flight -> runwayNumber = 0;

    //Airlines
    char airlines [38][3] = {"AQ","DM","BJ","RL","GB","ZA","VX","JP","ML","VF","DW","SU","SM","KJ","YE","VJ","QH","HD","UJ",
                             "EI","EG","RV","ZI","KI","QB","LD","UX","NX","HM","CY","AA","AZ","EK","ED","ZW","YI","GN","ZB"};
    int i = rand () % 38;
    strcpy (flight -> airline, airlines[i]);

    //Destinations
    char destinations[38][4] = { "JYH", "DWI", "ABJ", "ABG", "ABX", "CYD", "AES", "ADR", "AEK","TKJ", "UCR", "AFL", "AAW", "AAZ", "ACQ", "AFF", "FLA", "ADO","LMU",
                                 "EIN", "EUK", "ROU", "AAF", "AAG", "AAJ", "AHK", "AEA","AMU", "SEY", "LCA", "MAP", "CAI", "MCM", "AXE", "AWI", "RSI","AGN", "ABN"};
    int j = rand () % 38;
    strcpy (flight -> destination, destinations[j]);

    return flight;
}

//This function gets a flights address and prints its values.
void printFlightInformation(Flight* flight){
    if(flight != NULL){
        printf("%c %2d %2d %2d %2d %3s %4s\n", flight->flightType, flight->readyTime, flight->serviceTime, flight->serviceStartTime, flight->runwayNumber, flight->airline, flight->destination);
    }
}

