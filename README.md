# Process Scheduler Simulation 🤖🚀

## Overview 🌐

This project is a robust process scheduler simulation implemented in C++. The simulation includes various scheduling algorithms (FIFO, RR, SJF, EDF) and supports multiple processors with dynamic process migration, work stealing, and adaptive measures to handle processor overheating. The simulation is driven by an input file containing detailed specifications for processors and individual processes.

## Features 🛠️

- **Data Structures:** Implemented Linked List, Linked Queue, Priority Queue, and Binary Tree to facilitate the simulation.

- **Scheduler Setup:** Loads processor and process information from an input file, specifying details like scheduling algorithms, time slices, deadlines, and more.

  - **Processor Configuration:**
    - Number of processors available in the simulation.
    - Scheduling algorithms for each processor (FIFO, RR, SJF, EDF).
    - Algorithm-specific parameters (e.g., RR time slice, work steal time step, overheating recovery time step).

  - **Process Configuration:**
    - Number of processes 
    - Details about individual processes, including process ID, arrival time, CPU time, expected deadline, and input/output requests (and their percentage).

  - **Simulation Settings:**
    - Initial setup parameters, such as the time step for when a processor may overheat.
    - Interactive, simulation, or silent mode selection for the UI terminal.
    - Probability of process forking.
    - Remaining time to finish (for migration to RR processors).
    - Max waiting time (for migration to FCFS processors).

## Simulation Execution 🕹️

The simulation operates on a time-step basis, transitioning processes through states (new, rdy, run, blk, trm, orph) and processors between busy and idle states.

- **Process Handling:**
  - Process are created and given their required parameters.
  - Processes enter the new state upon arrival.
  - In each time-step, the scheduler checks for the processes whose arrival time matches with the current time step.
  - If a process arrival time matches, it is put in a processor queue and is now in ready state.
  - Process execution based on the chosen scheduling algorithm. Process is then in run state.
  - CPU time decremented each time step until termination.
  - Terminated process is added to the terminated list.

- **Dynamic Behavior:**
  - Process may migrate to other processors during the run state.
    - Migration to RR processors based on remaining time to finish.
    - Migration to FCFS processors based on max waiting time.
  - Process in run state may request for IO, so it is moved to blk list and is put in the blk state.
    - Scheduler treats processes in blk on a FCFS basis.
    - The process which is due to recieve IO access remains in there until the predefine IO duration ends. It then resumes normal scheduling.
  - Forking of processes by a predefined probability.
    - Each process can have at most two direct children.
    - When the parent is terminated, all descendant child forked processes are put in orphan state and terminated.
  - Scheduler every few predefined time-steps, checks for the longest and shortest processors in terms of queue length.
    - The shortest processor steals processes from the longest processor until they are equal. 

- **Processor Overheating:**
  - Overheating is not prevented but managed.
  - Detection of overheating processors.
  - Migration of processes from overheating processors to non-overheating ones.
  - Overheating processors resume operation after a cooling-off period.

- **Error Handling:**
  - Process termination based on predefined kill signals.
  - Each time-step, the scheduler checks if it is time to kill a process.
  - Killed processes are terminated.

- **UI Terminal:**
  - Three modes: interactive, simulation, and silent.
  - Interactive mode waits for user input, simulation runs without waiting, and silent mode generates only the output file.

## Output File Statistics 📊

1. For each process:
   - Termination time, process ID, arrival time, CPU time, IO duration, waiting time, response time, total turnaround duration.
2. Averages:
   - Waiting time, response time, total turnaround duration.
3. Percentages:
   - Process migration, processor work steal, forked processes, killed processes.
4. For each processor:
   - Number of processors using FCFS, SJF, RR, EDF.
   - Processor load and utilization.
5. Average processor utilization.
6. Percentage of processes completed before their expected deadline.

## Example UI Image 📸

![readme stuff](https://github.com/EzzCode/Process-Scheduler/assets/74989261/228d4c52-fd93-4603-94df-a48ea97ead5f)
