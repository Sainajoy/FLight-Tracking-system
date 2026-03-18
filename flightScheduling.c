#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#include "list.h"
#include "queue.h"



// To parse input from program arguments
void parseInput(char **, int *, int *, int *, int *);

// To initialise, create and populate the flight list with random flight data
List createFlightList(int, int, int);

//To initialise queue of the arrived flights and runway availability data
int* initialiseSimulator(Queue*, int);

//Adds the arrived flight into the priority queue
void newFlight(Flight*, Queue);

//Randomly assign an available runway to the flight
void serveFlight(Flight*, int*, int);

//Print the statistical data of the simulation run
void reportStatistics(List, int, int, int);

//Clear dynamically allocated memories
void exitFromTheSimulation(List, Queue, int *);

int main(int argc, char *argv[])
{
    //To be completed

    int noOfFlights, noOfRunways, maxReadyTime, maxServiceTime;
    Queue flightQueue;
    int *runways;          //array to track availability of runways
    int currentClock = 0;  //simulated clock
    int flightsServed = 0;


    srand(time(NULL));

    //Parse to get args
    parseInput(argv, &noOfFlights, &noOfRunways, &maxReadyTime, &maxServiceTime);

    //create flight list
    List flightList = createFlightList(noOfFlights, maxReadyTime, maxServiceTime);

    //initialise simulator
    runways = initialiseSimulator(&flightQueue, noOfRunways);


    //SIMULATION

    //Pointer to next flight that is yet to be added to queue
    struct flightNode *nextArrival = flightList -> head->next;           //defined outside simulation loop to maintain its position as clock goes on

    //Simulation loop
    while (flightsServed < noOfFlights) {
        //condition: all flights must be served

        struct flightNode *flightChecker = flightList -> head -> next;

        //1. Check for completed flights and freeing runways
        //loop through all flights to check if any finished service (departed) at the clock time
        while (flightChecker != NULL) {
            Flight *f = flightChecker -> flightInformation;

            if (f -> runwayNumber != 0) {                                //has to be  on a runway
                int runwayIndex = f -> runwayNumber - 1;                 //change to array indexing

                if (runways[runwayIndex] == 0 && (f -> serviceStartTime + f -> serviceTime== currentClock)) {       //busy and service is complete
                    runways[runwayIndex] = 1;   //change to available
                    flightsServed++;
                }
            }
            flightChecker = flightChecker->next;
        }



        //2. Check for new arrivals in list (ordered by ready time) and move them to priority queue
        while (nextArrival != NULL && nextArrival -> flightInformation -> readyTime == currentClock) {
            newFlight(nextArrival -> flightInformation, flightQueue);
            nextArrival = nextArrival -> next;
        }


        //3. Assign runways for flights waiting in queue if the runway is available
        while (!IsEmptyQueue(flightQueue)) {

            int availableIndex[noOfFlights];                             //array to track number of available runways
            int availableCount = 0;                                      //number of available runways

            for (int i = 0; i < noOfRunways; i++) {
                if (runways[i] == 1) {                                   //if available
                    availableIndex[availableCount] = i + 1;
                    availableCount++;
                }
            }

            //if no runway is available, no flight can take off
            if (availableCount == 0) {
                break;
            }

            //Select a runway randomly
            int randomIndex = rand () % availableCount;
            int runwayIndex = availableIndex[randomIndex];


            //dequeue the highest priority flight
            Flight *readyFlight = Dequeue(flightQueue);


            //update time and serve flight
            readyFlight -> serviceStartTime = currentClock;
            serveFlight(readyFlight, runways, runwayIndex);
        }


        //4. Clock Implementation.
        //If an event is not done, find the time of the next event
        if (flightsServed < noOfFlights) {
                                                                                                      // currentClock ++;  + 1 minute method
            int nextEventTime = -1;   //not yet set

            //check next arrival Time
            if (nextArrival != NULL) {
                int arrTime = nextArrival -> flightInformation -> readyTime;


                if (arrTime > currentClock) {
                    nextEventTime = arrTime;
                }
            }

            //check next departure time
            struct flightNode *checker = flightList -> head -> next;
            while (checker != NULL) {
                Flight *f = checker -> flightInformation;

                if (f -> runwayNumber != 0) {
                    int runwayIndex = f -> runwayNumber - 1;

                    if (runways[runwayIndex] == 0) {
                        int completionTime = f -> serviceStartTime + f -> serviceTime;

                        if (completionTime > currentClock) {

                            if (nextEventTime == -1 || completionTime < nextEventTime) {
                                nextEventTime = completionTime;
                            }
                        }

                    }


                }
                checker = checker -> next;
            }

            //make the skip of time
            if (nextEventTime != -1) {
                currentClock = nextEventTime;
            }
            else {
                currentClock = currentClock + 1;
            }

        }
    }

    //report and free memory
    reportStatistics(flightList, noOfRunways, noOfFlights, currentClock);
    exitFromTheSimulation(flightList, flightQueue, runways);

    return 0;
}

void parseInput(char *programArguments[], int *noOfFlights, int *noOfRunways, int *maxReadyTime, int *maxServiceTime){
    //To be completed

    *noOfFlights = atoi(programArguments[1]);
    *noOfRunways = atoi(programArguments[2]);
    *maxReadyTime = atoi(programArguments[3]);
    *maxServiceTime = atoi(programArguments[4]);

}

List createFlightList(int numberOfFlights, int maxReadyTime, int maxServiceTime){
    //To be completed

    List flightList = CreateList();
    MakeEmptyList(flightList);

    //populate flight list with random flight data and insert in ascending order
    for(int i = 0; i < numberOfFlights; i++) {
        Flight * flight= createRandomFlight(maxReadyTime, maxServiceTime);
        InsertListOrderedByReadyTime(flightList, flight);
    }
    return flightList;
}

int* initialiseSimulator(Queue* flightQueue, int noOfRunways){
    //To be completed

    //create empty priority queue
    *flightQueue = CreateQueue();


    //array to keep availability of runway
    int * runwayAvailable = (int*)malloc(sizeof(int) * noOfRunways);
    if(runwayAvailable == NULL) {
        printf("Memory allocation error");
        exit(1);
    }

    //initialise each runway time to 1 - available
    for(int i = 0; i < noOfRunways; i++) {
        runwayAvailable[i] = 1;
    }
    return runwayAvailable;
}


void newFlight(Flight* flightData,Queue flightQueue){
    //To be completed

    Enqueue(flightData, flightQueue);

}

// int *runways is the runway array
void serveFlight(Flight* flightData, int* runways, int runwayNumber){
    //To be completed

    //set runway as busy
    runways[runwayNumber - 1] = 0;    //-1 array indexing

    //record runway number
    flightData ->runwayNumber = runwayNumber;
}

void reportStatistics(List flightsDataList, int noOfRunways, int noOfFlights, int clockTime){
    //To be completed

    printf("\n****************Report******************\n");
    printf("The number of runways: %d\n", noOfRunways);
    printf("The number of flights: %d\n", noOfFlights);

    int countE = 0, countI = 0, countD =0;
    int *runwayUsage = (int*)calloc(noOfRunways, sizeof(int)); //calloc to set everything to 0
    int totalWaitTime = 0 , maxWaitTime = 0;

    //Popular airline and destination
    char *popularAirline = NULL;
    char *popularDest = NULL;
    int maxAirlineCount = 0, maxDestCount = 0;


    struct flightNode *current = flightsDataList -> head ->next;


    while (current != NULL) {
        Flight *f = current -> flightInformation;

        //counting types
        if (f -> flightType == 'E') countE++;
        else if (f -> flightType == 'I') countI++;
        else if (f -> flightType == 'D') countD++;

        //counting runway usage
        if (f -> runwayNumber > 0 && f -> runwayNumber <= noOfRunways) {
            runwayUsage [f -> runwayNumber -1] ++;
        }

        //counting queue time: wait and maxWaitTime
        int wait = f->serviceStartTime - f->readyTime;
        totalWaitTime += wait;
        if (wait > maxWaitTime) {
            maxWaitTime = wait;
        }

        //Popular Airline
        int currentAirlineFreq = 0;
        struct flightNode *temp = flightsDataList -> head -> next;
        while (temp != NULL) {
            if (strcmp(f -> airline , temp -> flightInformation -> airline) == 0) {   //compare airline name for the current flight with the rest on the list to check its frequency
                currentAirlineFreq++;
            }
            temp = temp -> next;
        }
        if (currentAirlineFreq > maxAirlineCount) {
            maxAirlineCount = currentAirlineFreq;
            popularAirline = f -> airline;                                           //updated where the current airline count is more than the previous max one
        }


        //Popular Destination                                                        //same logic to airline
        int currentDestFreq = 0;
        temp = flightsDataList -> head -> next;
        while (temp != NULL) {
            if (strcmp(f -> destination , temp -> flightInformation -> destination) == 0) {
                currentDestFreq++;
            }
            temp = temp -> next;
        }
        if (currentDestFreq > maxDestCount) {
            maxDestCount = currentDestFreq;
            popularDest = f -> destination;
        }


        current = current -> next;

    }



    printf("Number of flights for each flight type: \n");
    printf("\tEmergency: %d \n", countE);
    printf("\tInternational: %d \n", countI);
    printf("\tDomestic: %d \n", countD);

    printf("Number of flights for each runway:\n");
    for (int i = 0; i < noOfRunways; i++) {
        printf("\tRunway %d: %d \n", i + 1, runwayUsage[i]);
    }

    printf("Completion time: %d\n", clockTime);

    if (noOfFlights > 0) {
        printf("Average time spent in the queue %.2lf\n", (double)totalWaitTime / noOfFlights);   //double to avoid keep the decimal part
    }
    else {
        printf("Average time spent in the queue: 0\n");
    }

    printf("Maximum waiting time: %d\n", maxWaitTime);
    printf("Popular Airline: %s\n", popularAirline);
    printf("Popular Destination: %s\n", popularDest);


    free(runwayUsage);

}

void exitFromTheSimulation(List flightList, Queue flightQueue, int *runways){
    //To be completed

    deleteList(flightList);
    deleteQueue(flightQueue);
    free(runways);

}