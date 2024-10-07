
# Philosophers Dining Simulation

## Introduction

This project is an implementation of the **Dining Philosophers Problem** using threads and mutexes in C. The problem is a classic synchronization problem involving philosophers who alternate between thinking, eating, and sleeping, but they must share limited forks to eat.

Each philosopher is represented by a thread, and forks are represented by mutexes. The simulation ensures that no philosopher starves and respects constraints on the number of meals philosophers need to eat.

## How It Works

In this simulation:
- Philosophers sit at a round table with one fork between each pair of philosophers.
- To eat, a philosopher needs to pick up both the left and right forks.
- Philosophers alternate between thinking, eating, and sleeping.
- The simulation ends when all philosophers have eaten a required number of meals or when one philosopher dies because they haven’t eaten in a specified amount of time.

## Requirements

- You must have `gcc` installed on your machine to compile the project.
- `pthread` library for thread management.

## Compilation

To compile the project, run the following command in your terminal:

```bash
gcc -Wall -Wextra -Werror -pthread -o philo *.c
```

This will create an executable file named `philo`.

## Usage

Once compiled, you can run the simulation with the following arguments:

```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

- `number_of_philosophers`: The number of philosophers (minimum 2, maximum 200).
- `time_to_die`: The time (in milliseconds) a philosopher can go without eating before dying.
- `time_to_eat`: The time (in milliseconds) a philosopher spends eating.
- `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping.
- `[number_of_meals]`: Optional. The number of meals each philosopher must eat before the simulation ends. If not provided, the simulation will only stop if a philosopher dies.

### Example

```bash
./philo 5 800 200 200 7
```

This command starts a simulation with:
- 5 philosophers,
- 800 ms before a philosopher dies if they don't eat,
- 200 ms for eating,
- 200 ms for sleeping,
- and each philosopher must eat 7 times before the simulation ends.

## Project Structure

- **main.c**: Entry point of the program. It initializes the simulation and starts the threads.
- **philo.h**: Header file containing the structures and function prototypes.
- **args_checker.c**: Functions for validating command-line arguments.
- **data_init.c**: Functions for initializing simulation data and cleaning up resources.
- **routine.c**: Contains the routine executed by each philosopher thread.
- **monitoring.c**: Functions to monitor the philosophers' status (e.g., checking if any philosopher has died).
- **threads.c**: Functions to create and manage the threads for philosophers and the monitor.
- **utils.c**: Utility functions like time management and custom sleep functions.

## Key Features

- **Thread Synchronization**: Each philosopher's actions are synchronized using mutexes to prevent race conditions and deadlocks.
- **Monitor Thread**: A dedicated thread monitors the state of all philosophers to detect if one dies or if all have eaten the required meals.
- **Graceful Cleanup**: All dynamically allocated memory is freed, and mutexes are destroyed when the simulation ends.

## Known Limitations

- The simulation may encounter slight delays due to the operating system's thread scheduling and usleep function, which can affect the timing of the philosophers' actions.
- Philosophers may spend time waiting for forks if adjacent philosophers are eating, but the implementation prevents deadlocks through alternating fork picking behavior.

## Example Output

```bash
1728291666170 1 is thinking
1728291666175 2 is thinking
1728291666180 1 has taken a fork
1728291666180 1 has taken a fork
1728291666180 1 is eating
1728291666185 2 has taken a fork
...
```

## Error Handling

The program handles the following errors:
- Invalid command-line arguments (e.g., negative values, insufficient arguments).
- Memory allocation failures.
- Thread creation failures.

## Further Development

Potential improvements or extensions:
- Implement a different strategy for fork picking to prevent philosophers from waiting too long for forks.
- Add logging to track the performance and behavior of the simulation.
- Implement additional features like philosophers standing up from the table after eating.

## Conceptual Diagram
```
┌───────────────────────────────────────────────────────────────────────┐
│                          Program Startup                              │
└───────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌───────────────────────────────────────────────────────────────────────┐
│    Initialization of threads (one thread for each philosopher)        │
└───────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌───────────────────────────────────────────────────────────────────────┐
│      Initialization of forks (mutexes) between each philosopher       │
│        Each fork is represented by a mutex                            │
└───────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
        ┌─────────────────────────────────────────────────────────┐
        │ Each philosopher (thread) starts their life cycle:      │
        │   - Thinking                                            │
        │   - Eating                                              │
        │   - Sleeping                                            │
        └─────────────────────────────────────────────────────────┘
                                │
                                ▼
 ┌─────────────────────────────────────────────────────────────────────┐
 │   Philosopher attempts to pick up two forks:                        │
 │      - Locking the two mutexes (left and right forks)               │
 │      - If unavailable, they must wait                               │
 └─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
┌───────────────────────────────────────────────────────────────────────┐
│ Philosopher picks up both available forks and starts eating           │
│    - Timer to measure eating duration                                 │
│    - If time without eating exceeds `time_to_die`, the philosopher    │
│      dies, and the simulation stops                                   │
└───────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
 ┌─────────────────────────────────────────────────────────────────────┐
 │   After eating, the philosopher puts down the forks (unlock mutexes)│
 └─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
 ┌─────────────────────────────────────────────────────────────────────┐
 │   The philosopher moves to the "sleeping" state for `time_to_sleep` │
 │   - Timer for the sleeping duration                                 │
 └─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
 ┌─────────────────────────────────────────────────────────────────────┐
 │   The philosopher wakes up and moves to the "thinking" state        │
 └─────────────────────────────────────────────────────────────────────┘
                                │
                                ▼
           ┌─────────────────────────────────────────────────────┐
           │  Cycle repeats: Thinking → Eating → Sleeping        │
           │  - The simulation continues until a philosopher dies│
           │    or all philosophers have eaten enough times      │
           └─────────────────────────────────────────────────────┘
                                │
                                ▼
        ┌─────────────────────────────────────────────────────────┐
        │    Simulation ends when a philosopher dies              │
        └─────────────────────────────────────────────────────────┘
```
### Step-by-step explanations:

1) Program Startup: The program starts by initializing the simulation parameters (number of philosophers, time before death, eating time, etc.).

2) Thread and Fork Initialization: Each philosopher is a thread, and each fork between two philosophers is represented by a mutex to control concurrent access.

3) Philosopher Cycle: Each philosopher goes through a cycle of three actions: thinking, eating, and sleeping. They can only eat if they successfully acquire both forks (mutexes) on their left and right.

4) Fork Management: Forks are picked up using mutexes. If a philosopher cannot acquire a fork because a neighbor is using it, they wait until it becomes available.

5) Time to Die Check: Each philosopher has a time_to_die limit. If a philosopher doesn't eat within this limit, they die, and the simulation stops immediately.

6) Simulation End: The simulation stops if a philosopher dies or if all philosophers have eaten the required number of times (if this parameter is provided).


This diagram outlines the key steps and interactions between philosopher threads and shared resources (forks) while managing time constraints and synchronization.

# Test cases
- **Command**: `./philo 1 800 200 200` - Philosopher should not eat and should die.
- **Command**: `./philo 5 800 200 200` - No Philosopher should die.
- **Command**: `./philo 5 800 200 200 7`- No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
- **Command**: `./philo 4 410 200 200` - No Philosopher should die.
- **Command**: `./philo 4 310 200 100` - One Philosopher should die.

# Specific cases
These special cases test the robustness and stability of the program under various edge conditions, including invalid input, extreme timing, and thread management limits.

### **Special Case 1: No Philosopher**
- **Command**: `./philo 0 800 200 200`

- **What should happen**: The program should display an error message indicating that there must be at least 2 philosophers for the simulation to work. It should not attempt to run the simulation.

---

### **Special Case 2: One Philosopher**
- **Command**: `./philo 1 800 200 200`

- **What should happen**: The philosopher will die because they will never have access to two forks to eat. The program should detect that the philosopher exceeds the 800 ms without eating and display that the philosopher has died after thinking and trying to take a fork without success.

---

### **Special Case 3: Negative Time**
- **Command**: `./philo 3 -800 200 200`

- **What should happen**: The program should refuse to start and display an error, as the time to die cannot be negative. This allows testing if the program correctly handles invalid input.

---

### **Special Case 4: Eating Time Greater Than Time to Die**
- **Command**: `./philo 5 200 300 200`

- **What should happen**: Several philosophers should die because the eating time (300 ms) is greater than the time to die (200 ms). Even if they take the forks and start eating, they won’t be able to finish their meal before dying.

---

### **Special Case 5: Very Short Sleep Time**
- **Command**: `./philo 4 800 200 1`

- **What should happen**: The simulation will become extremely fast since the philosophers only sleep for 1 ms after eating. This tests the program’s ability to run quickly and without errors under short sleep periods.

---

### **Special Case 6: Simulation with a Large Number of Philosophers**
- **Command**: `./philo 1000 800 200 200`

- **What should happen**: The program should run normally, even with a large number of philosophers. This tests the thread management and fork synchronization for a high number of participants. You should check that all philosophers are eating properly and that no one dies prematurely.

---

### **Special Case 7: All Philosophers Eat at the Same Time (Deadlock Test)**
- **Command**: `./philo 5 800 200 200`

- **What might happen**: If each philosopher attempts to take a fork simultaneously (in a deadlock scenario), all the philosophers could wait indefinitely for a fork. This case tests the management of shared resources (the forks) and how the program handles potential deadlock situations.

---

### **Special Case 8: Extremely Short Time to Die**
- **Command**: `./philo 5 50 200 200`

- **What should happen**: All philosophers will die very quickly because they won’t be able to eat before reaching the 50 ms threshold. This tests whether the program can handle very short time values correctly without slowdown or blockage.

---

### **Special Case 9: Extremely Large Number of Required Meals**
- **Command**: `./philo 4 800 200 200 1000000`

- **What should happen**: The program should run normally, but this test highlights the performance when the philosophers are required to eat an extremely large number of meals (1,000,000). The simulation should run without crashing, but it might take a long time.

---

### **Special Case 10: No Required Meals but Infinite Time**
- **Command**: `./philo 4 1000 500 500 -1`

- **What should happen**: No philosopher should die as they have enough time to eat (1000 ms to die, 500 ms to eat and sleep), and the simulation should continue indefinitely since no required meal count has been set. This tests if the program can run indefinitely without performance or memory issues.

---

### **Special Case 11: Malformatted Arguments**
- **Command**: `./philo 5 800 abc 200`

- **What should happen**: The program should display an error because the argument for the eating time is invalid (`abc`). This tests if the program correctly verifies the validity of input arguments and handles formatting errors.

---

### **Special Case 12: Too Many Philosophers (Thread Management Limit)**
- **Command**: `./philo 100000 800 200 200`

- **What should happen**: The program might fail or become very slow because the operating system could hit a limit on the number of threads it can manage. This test checks how the program handles system limits and whether it provides appropriate error messages if exceeded.

---

### **Special Case 13: Philosophers Sleep Much Longer Than They Eat**
- **Command**: `./philo 5 1000 100 900`

- **What should happen**: No philosopher should die, but the program should run more slowly because the philosophers spend much more time sleeping (900 ms) than eating (100 ms). This case tests situations where the philosophers' actions take vastly different amounts of time.
