# Flight Tracking System

A simulation-based airport runway and flight management system developed in C. The program simulates how flights arrive, wait in queues, and are assigned to available runways using data structures such as linked lists and priority queues.

---

## Features

- Random flight generation
- Runway allocation system
- Flight queue management
- Priority handling for flights
- Event-driven simulation clock
- Runway usage statistics
- Queue waiting time analysis
- Popular airline and destination tracking
- Dynamic memory management

---

## Technologies Used

- C Programming Language
- Linked Lists
- Queues / Priority Queues
- Dynamic Memory Allocation
- Structures and Modular Programming

---

## Project Structure

```bash
.
├── main.c
├── list.c
├── list.h
├── queue.c
├── queue.h
├── flight.h
└── Makefile
```

---

## How It Works

1. Flights are randomly generated with different:
   - Ready times
   - Service times
   - Flight types
   - Airlines
   - Destinations

2. Flights are inserted into a linked list ordered by ready time.

3. As simulation time progresses:
   - Flights arrive
   - Flights enter the priority queue
   - Available runways are assigned

4. The simulation continues until all flights are served.

5. Statistical reports are generated at the end.

---

## Compilation

Compile using GCC:

```bash
gcc main.c list.c queue.c -o flight_simulator
```

---

## Running the Program

```bash
./flight_simulator <number_of_flights> <number_of_runways> <max_ready_time> <max_service_time>
```

### Example

```bash
./flight_simulator 50 3 100 20
```

This example:
- Generates 50 flights
- Uses 3 runways
- Sets maximum ready time to 100
- Sets maximum service time to 20

---

## Example Output

```text
****************Report******************

The number of runways: 3
The number of flights: 50

Number of flights for each flight type:
    Emergency: 5
    International: 20
    Domestic: 25

Completion time: 132
Average time spent in the queue: 4.28
Maximum waiting time: 12
```

---

## Concepts Demonstrated

- Event-driven simulation
- Queue management systems
- Airport runway scheduling
- Dynamic memory handling
- Statistical data analysis
- Modular software design

---

## Author

Joy Saina  
Software Engineering Student  
Middle East Technical University (METU NCC)
