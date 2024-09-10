# Philosophers

## Conceptual Diagram

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

### Step-by-step explanations:
```
    Program Startup: The program starts by initializing the simulation parameters (number of philosophers, time before death, eating time, etc.).

    Thread and Fork Initialization: Each philosopher is a thread, and each fork between two philosophers is represented by a mutex to control concurrent access.

    Philosopher Cycle: Each philosopher goes through a cycle of three actions: thinking, eating, and sleeping. They can only eat if they successfully acquire both forks (mutexes) on their left and right.

    Fork Management: Forks are picked up using mutexes. If a philosopher cannot acquire a fork because a neighbor is using it, they wait until it becomes available.

    Time to Die Check: Each philosopher has a time_to_die limit. If a philosopher doesn't eat within this limit, they die, and the simulation stops immediately.

    Simulation End: The simulation stops if a philosopher dies or if all philosophers have eaten the required number of times (if this parameter is provided).
```

This diagram outlines the key steps and interactions between philosopher threads and shared resources (forks) while managing time constraints and synchronization.
