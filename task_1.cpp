// Design and Implement a CPU Process Scheduling Algorithm using a Linked List. Processes
// will be represented as nodes in the list, and the scheduling algorithm should cycle
// through the processes, assigning CPU time to each process until all processes have
// completed their execution.
// Task:
//     • Each process should have the following attributes: process_id, execution_time, and remaining_time.
//     • The scheduler assigns a fixed amount of CPU time to each process in each cycle. After the time is assigned, the process's remaining_time will be reduced by that amount.
//     • If a process completes its execution (i.e., remaining_time becomes 0), it should be removed from the circular linked list.
//     • The system should display the state of processes after each cycle, indicating which process is running and its remaining time.
//     • Show the state of the system after each cycle.
// Optional Task:
// Your system should simulate a scenario where a new process can arrive at any time. For example, the program should handle an event that inserts a new process into the list while the scheduler is running.

#include <iostream>
#include <string>
using namespace std;

int PROCESS_TIME = 3;

struct Node
{
    int process_id;
    int execution_time;
    int remaining_time;
    Node *next;
    Node(int pid, int et) : process_id(pid), execution_time(et), remaining_time(et), next(nullptr) {}
};

class CircularLinkedList
{
private:
    Node *tail; // Last node in the list so it will be easy to access add nodes. Plus, we can access the head node by tail->next.
    int size;
    int cycles; // Keep track of the cycles run

public:
    CircularLinkedList() : tail(nullptr), size(0), cycles(0) {}

    // Add a new process node to the circular list
    void addNode(int process_id, int execution_time)
    {
        Node *newNode = new Node(process_id, execution_time);

        if (tail == nullptr)
        {
            // If the list is empty, the new node will be the head and the tail
            tail = newNode;
            tail->next = tail; // Point to itself
        }
        else
        {
            // If the list is not empty, add the new node after the tail and update the tail
            newNode->next = tail->next; // newNode points to the head
            tail->next = newNode;       // tail points to the newNode
            tail = newNode;             // Update the tail to the newNode
        }
        size++;
    }

    // Remove a process node from the circular list
    void removeNode(Node *node)
    {
        // If the list is empty, return
        if (tail == nullptr)
            return;

        Node *temp = tail->next; // Start from the head
        Node *prev = tail;       // Keep track of the previous node

        do
        {
            if (temp == node)
            {
                // Link the previous node to the next node
                prev->next = temp->next;
                // Check if the node to remove is the tail
                if (temp == tail)
                {
                    tail = prev == tail ? nullptr : prev;
                }
                delete temp;
                size--;
                return;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != tail->next); // Stop when we reach the head again
    }

    // Display the process nodes in the circular list
    void display()
    {
        // If the list is empty, return
        if (tail == nullptr)
            return;

        Node *temp = tail->next;
        do
        {
            cout << "(P" << temp->process_id << ", Remaining: " << temp->remaining_time << "), ";
            temp = temp->next;
        } while (temp != tail->next);
        cout << endl
             << endl;
    }

    // Schedule method to cycle through the processes and assign CPU time to each process.
    void schedule(int timePerProcess)
    {
        // If the list is empty, return
        if (tail == nullptr)
            return;

        Node *temp = tail->next; // Start from the head

        cout << "Cycle " << ++cycles << ": \n";
        do
        {
            if (size == 1)
                continue;

            // Subtract time from the remaining time
            if (temp->remaining_time > timePerProcess)
            {
                temp->remaining_time -= timePerProcess;
            }
            else
            {
                temp->remaining_time = 0; // Process will complete
            }

            // Check if the process completed
            if (temp->remaining_time == 0)
            {
                cout << "Process P" << temp->process_id << " Completes!\n";
                Node *toRemove = temp;
                temp = temp->next;    // Move to the next node before removing the current node
                removeNode(toRemove); // Remove the current node
                if (size == 0)
                    break;
                continue;
            }
            temp = temp->next; // Move to the next process
        } while (temp != tail->next);

        // Handled separately because if only one process is left while executing the loop, it will not be handled in the loop
        if (size == 1)
        {
            // Subtract time from the remaining time
            if (temp->remaining_time > timePerProcess)
            {
                temp->remaining_time -= timePerProcess;
            }
            else
            {
                cout << "Process P" << temp->process_id << " Completes!\n";
                removeNode(temp); // Remove the current node
            }
        }

        // Check if all processes are completed
        if (size == 0)
        {
            cout << "All Processes Completed!\n";
        }
        // Display the current state of processes before deletion
        display();
    }

    // Add new process during runtime
    void addProcessDuringScheduling(int process_id, int execution_time)
    {
        cout << "New process arrives: P" << process_id << " (Remaining: " << execution_time << ")\n\n";
        addNode(process_id, execution_time);
    }
};

int main()
{
    CircularLinkedList processList;

    // Adding initial processes
    processList.addNode(1, 10);
    processList.addNode(2, 8);
    processList.addNode(3, 8);

    cout << "Initial Processes:\n";
    processList.display();

    cout << "CPU Time per Process per Cycle: " << PROCESS_TIME << "\n\n";

    // Run scheduler for initial processes
    processList.schedule(PROCESS_TIME);

    // Optional: Simulating new process arrival while scheduling
    processList.addProcessDuringScheduling(4, 15);
    processList.schedule(PROCESS_TIME);
    processList.schedule(PROCESS_TIME);
    processList.schedule(PROCESS_TIME);
    processList.schedule(PROCESS_TIME);
    processList.schedule(PROCESS_TIME);

    return 0;
}
