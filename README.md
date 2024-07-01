# Multithreading-elevator-simulation

This project simulates an elevator system using multithreading in C++ with the ncurses library for text-based graphical output. The simulation includes clients (passengers) generating dynamically and interacting with the elevator.

## Components

### `main.cpp`

The main file orchestrates the simulation by initializing threads for various tasks, including generating clients, managing elevator movement, updating the graphical interface, and handling user input for program termination.

### Dependencies

- **ncurses**: Provides functions for creating text-based graphical user interfaces in a terminal.
- **thread**: Utilized for creating and managing concurrent threads.
- **mutex** and **condition_variable**: Ensures thread synchronization and coordination.
- **vector** and **algorithm**: Used for managing collections of clients and performing operations on them.

### Classes

- **`Client`**: Represents a client or passenger with attributes such as destination floor, movement speed, and graphical representation.
  
- **`Elevator`**: Manages the elevator's state, including current position, capacity, movement, and interactions with clients.
  
- **`Scene`**: Handles the initialization and graphical rendering of the simulation environment, displaying floors and client movements.

### Functions

- **`moveElevator()`**: Thread function controlling the elevator's movement and interaction with clients.
  
- **`moveClient()`**: Thread function managing client behavior, including entering the elevator queue, boarding the elevator, and disembarking at the destination floor.
  
- **`windowRefresh()`**: Thread function responsible for updating and refreshing the graphical interface to reflect current simulation state.
  
- **`exitProgram()`**: Thread function listening for user input to gracefully terminate the program.

### Usage

To compile and run the simulation:

1. **Compile**: Use a C++ compiler that supports C++11 or higher with the `-lncurses` flag for linking the ncurses library.
   ```bash
   g++ -std=c++11 -o elevator_simulation main.cpp Client.cpp Elevator.cpp Scene.cpp -lncurses
   ```

2. **Run**: Execute the compiled binary.
   ```bash
   ./elevator_simulation
   ```

3. **Interaction**: Use the spacebar to exit the simulation gracefully.

### Notes

- The simulation assumes a fixed terminal size and a simplified graphical representation for demonstration purposes.
  
- Thread synchronization ensures safe interaction between clients and the elevator system.
  
- Adjustments may be necessary for different terminal sizes or to incorporate more advanced elevator scheduling algorithms.

### Contributors

- [Mateusz Gawłowski](https://github.com/gawlowski-mateusz)