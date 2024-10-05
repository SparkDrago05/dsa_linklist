# CPU Process Scheduling Algorithm

## Approach
The project implements a CPU process scheduling algorithm using a circular linked list. Each process is represented as a node in the list, allowing for efficient management of processes in a cyclic manner. The algorithm assigns CPU time in cycles while handling new process arrivals dynamically. This ensures that processes get fair CPU time and improves overall system responsiveness.

## Assumptions
- Each process has a defined burst time and arrival time.
- The time quantum for the CPU cycles is fixed and can be adjusted based on requirements.
- The input data is validated to ensure that all required fields are present for each process.

## GitHub Link
[GitHub Repository](https://github.com/SparkDrago05/dsa_linklist)

## Challenges Faced
- Implementing the circular linked list structure required careful management of pointers to avoid memory leaks and segmentation faults.
- Dynamically handling new process arrivals while maintaining the scheduling order posed a significant challenge.
- Testing with various input scenarios to ensure the algorithm's robustness and efficiency required thorough validation.
- Specially handle case when there is only one process left during the cycle.

## Screenshots of Output
Below is the screenshot of the output:
   ![Sample Output 1](screenshots/scheduler.png)

## Conclusion
This project successfully demonstrates the implementation of a CPU process scheduling algorithm using a circular linked list, effectively managing process execution while overcoming various challenges. 

---
