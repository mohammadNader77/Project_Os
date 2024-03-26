#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct Process
{
    char processName[20];   // Process name
    int arrivalTime;        // Arrival time
    int burstTime;          // Burst time
    int priority;           // Priority value
    int remainingTime;      // Remaining burst time
    int completionTime;     // Completion time
    int waitingTime;        // Waiting time
    int turnaroundTime;     // Turnaround time
    int responseTime;       // Response time

};

void addProcess(struct Process processes[], int n);
void sortProcess(struct Process processes[], int n);
void preemptiveSJFScheduling(struct Process processes[], int n);
void fcfsScheduling(struct Process processes[], int n);
void roundRobinScheduling(struct Process processes[], int n, int timeQuantum);
void priorityPreemptiveScheduling(struct Process processes[], int n);


int main()
{
    struct Process processes[20];  // Array to store process information
    int n;
    int timeQuantum;

    // Get the number of processes from the user
    printf("Enter the number of processes: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > 20)
    {
        printf("Invalid number of processes. Please enter a positive integer up to 20.\n");
        return 1;
    }
    // Get process details from the user
    printf("\nEnter Process Details:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        printf("Process Name: ");
        if (scanf("%s", processes[i].processName) != 1)
        {
            printf("Invalid process name. Please enter a string.\n");
            return 1;
        }

        printf("Arrival Time: ");
        if (scanf("%d", &processes[i].arrivalTime) != 1 || processes[i].arrivalTime < 0)
        {
            printf("Invalid arrival time. Please enter a non-negative integer.\n");
            return 1;
        }


        processes[i].remainingTime = processes[i].burstTime;
    }

    // Get the selected scheduling algorithm from the user
    printf("\nSelecet Scheduling\n");
    // Configuration menu
    int choice;
    while (1)
    {
        printf("\n 1.Preemptive Shortest Job First (SJF) Scheduling\n");
        printf(" 2.FCFS Scheduling\n");
        printf(" 3.Round Robin Scheduling\n");
        printf(" 4.PriorityPreemptive Scheduling\n");
        printf(" 0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            preemptiveSJFScheduling(processes, n);
            break;

        case 2:
            fcfsScheduling(processes, n);
            break;

        case 3:
            roundRobinScheduling(processes, n, timeQuantum);
            break;

        case 4:
            priorityPreemptiveScheduling(processes, n);
            break;

        case 0:
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
        printf("\n");
    }

    return 0;
}



// Function to implement preemptive SJFS scheduling
void preemptiveSJFScheduling(struct Process processes[], int n)
{


    for (int i = 0; i < n; i++)
    {
        // User input for burst time of each process
        printf("Process %d:\n", i + 1);
        printf("Burst Time: ");
        if (scanf("%d", &processes[i].burstTime) != 1 || processes[i].burstTime <= 0)
        {
            // Invalid input handling for negative or non-integer burst time
            printf("Invalid burst time. Please enter a positive integer.\n");
            return ;
        }

        // Initialize remaining time for each process
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Call the function Sort the processes based on arrival time
    sortProcess(processes,n);


    int currentTime = 0;  //current time
    int completedProcesses = 0; //completed processes
    bool isProcessExecuted[20] = { false }; // Boolean array to track if a process is executed or not
    int previousProcessIndex = -1;

    // Find the process with the smallest burst time among the arrived and incomplete processes
    int findShortestBurstTimeIndex()
    {
        int shortestBurstTime = -1;
        int shortestBurstTimeIndex = -1;
        for (int i = 0; i < n; i++)
        {
            if (!isProcessExecuted[i] && processes[i].arrivalTime <= currentTime)
            {
                if (shortestBurstTime == -1 || processes[i].remainingTime < shortestBurstTime)
                {
                    shortestBurstTime = processes[i].remainingTime;
                    shortestBurstTimeIndex = i;
                }
            }
        }

        return shortestBurstTimeIndex;
    }



    // Generate Gantt Chart
    printf("\n*************************************Gantt Chart*****************************************\n\n\n");
    printf("%d",currentTime);
    // Execute SJF scheduling algorithm until all processes are completed
    while (completedProcesses < n)
    {
        int shortestBurstTimeIndex = findShortestBurstTimeIndex();

        if (shortestBurstTimeIndex != -1)
        {
            if (previousProcessIndex != shortestBurstTimeIndex)
            {
                printf("-> %d [%s] ", currentTime, processes[shortestBurstTimeIndex].processName);
            }
            else
            {
                printf("  ");
            }

            processes[shortestBurstTimeIndex].remainingTime--;
            currentTime++;

            if (processes[shortestBurstTimeIndex].remainingTime == 0)
            {
                processes[shortestBurstTimeIndex].completionTime = currentTime;
                processes[shortestBurstTimeIndex].turnaroundTime = processes[shortestBurstTimeIndex].completionTime - processes[shortestBurstTimeIndex].arrivalTime;
                processes[shortestBurstTimeIndex].waitingTime = processes[shortestBurstTimeIndex].turnaroundTime - processes[shortestBurstTimeIndex].burstTime;
                processes[shortestBurstTimeIndex].responseTime = processes[shortestBurstTimeIndex].waitingTime;
                isProcessExecuted[shortestBurstTimeIndex] = true;
                completedProcesses++;
            }

            previousProcessIndex = shortestBurstTimeIndex;
        }
        else
        {
            currentTime++;
        }
    }

    printf("->%d", currentTime);
    printf("\n-----------------------------------------------------------------------------------------");

    // Calculate average performance metrics
    int totalWT = 0, totalRT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
    {
        totalWT += processes[i].waitingTime;
        totalRT += processes[i].responseTime;
        totalTAT += processes[i].turnaroundTime;
    }

    float avgWT = (float) totalWT / n;
    float avgRT = (float) totalRT / n;
    float avgTAT = (float) totalTAT / n;

    // Display process details
    printf("\nProcess\t Arrival Time \tBurst Time \tCompletion Time \tWaiting Time \tTurnaround Time \tResponse Time");
    for (int i = 0; i < n; i++)
        printf("\n%s\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\t\t\t %d", processes[i].processName, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime, processes[i].responseTime);

    printf("\n-----------------------------------------------------------------------------------------");

    // Display average performance metrics
    printf("\n\nAverage Waiting Time = %f", avgWT);
    printf("\nAverage Response Time = %f", avgRT);
    printf("\nAverage Turnaround Time = %f", avgTAT);


    printf("\n-----------------------------------------------------------------------------------------");

    // Generate performance report
    printf("\n\nPerformance Report:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %s:\n", processes[i].processName);
        printf("Waiting Time: %d\n", processes[i].waitingTime);
        printf("Turnaround Time: %d\n", processes[i].turnaroundTime);
        printf("Response Time: %d\n", processes[i].responseTime);
        printf("Completion Time: %d\n\n", processes[i].completionTime);
    }

}


// Function to implement FCFS scheduling
void fcfsScheduling(struct Process processes[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);
        //enter the burst time
        printf("Burst Time: ");
        if (scanf("%d", &processes[i].burstTime) != 1 || processes[i].burstTime <= 0)
        {
            printf("Invalid burst time. Please enter a positive integer.\n");
            return ;
        }
        processes[i].remainingTime = processes[i].burstTime;
    }

    // Sort the processes based on arrival time
    sortProcess(processes,n);

    int currentTime = 0;


    // Generate Gantt Chart
    printf("\n*************************************Gantt Chart*****************************************\n\n\n");
    printf("%d",currentTime);
    for (int i = 0; i < n; i++)
    {
        if (processes[i].arrivalTime > currentTime)
        {
            currentTime = processes[i].arrivalTime;
        }

        printf("->%d [%s] ", currentTime, processes[i].processName);
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        processes[i].responseTime = processes[i].waitingTime;

        currentTime = processes[i].completionTime;
    }
    printf("->%d", currentTime);
    printf("\n-----------------------------------------------------------------------------------------");

    // Calculate average performance metrics
    int totalWT = 0, totalRT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
    {
        totalWT += processes[i].waitingTime;
        totalRT += processes[i].responseTime;
        totalTAT += processes[i].turnaroundTime;
    }
    float avgWT = (float)totalWT / n;
    float avgRT = (float)totalRT / n;
    float avgTAT = (float)totalTAT / n;

    // Display process details
    printf("\nProcess\t Arrival Time \tBurst Time \tCompletion Time \tWaiting Time \tTurnaround Time \tResponse Time");
    for (int i = 0; i < n; i++)
        printf("\n%s\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\t\t\t %d", processes[i].processName, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime, processes[i].responseTime);
    printf("\n-----------------------------------------------------------------------------------------");

    // Display average performance metrics
    printf("\n\nAverage Waiting Time = %f", avgWT);
    printf("\nAverage Response Time = %f", avgRT);
    printf("\nAverage Turnaround Time = %f", avgTAT);


    printf("\n-----------------------------------------------------------------------------------------");

    // Generate performance report
    printf("\n\nPerformance Report:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %s:\n", processes[i].processName);
        printf("Waiting Time: %d\n", processes[i].waitingTime);
        printf("Turnaround Time: %d\n", processes[i].turnaroundTime);
        printf("Response Time: %d\n", processes[i].responseTime);
        printf("Completion Time: %d\n\n", processes[i].completionTime);
    }

}
// Function to implement Round Robin scheduling
void roundRobinScheduling(struct Process processes[], int n, int timeQuantum)
{
    //enter the time quantum from user
    printf("Enter the time quantum: ");
    if (scanf("%d", &timeQuantum) != 1 || timeQuantum <= 0)
    {
        printf("Invalid time quantum. Please enter a positive integer.\n");
        return ;
    }


    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);

        //enter the burst time
        printf("Burst Time: ");
        if (scanf("%d", &processes[i].burstTime) != 1 || processes[i].burstTime <= 0)
        {
            printf("Invalid burst time. Please enter a positive integer.\n");
            return ;
        }
        processes[i].remainingTime = processes[i].burstTime;
    }
    // call function Sort the processes based on arrival time
    sortProcess(processes,n);

    int currentTime = 0;
    int completedProcesses = 0;
    int currentProcessIndex = 0;
    int remainingProcesses = n;


    // Generate Gantt Chart
    printf("\n*************************************Gantt Chart*****************************************\n\n\n");
    printf("%d",currentTime);
    while (completedProcesses < n)
    {
        if (processes[currentProcessIndex].remainingTime > 0)
        {
            int executionTime = (processes[currentProcessIndex].remainingTime <= timeQuantum)
                                ? processes[currentProcessIndex].remainingTime : timeQuantum;

            processes[currentProcessIndex].remainingTime -= executionTime;
            currentTime += executionTime;

            if (processes[currentProcessIndex].remainingTime == 0)
            {
                completedProcesses++;
                remainingProcesses--;
                processes[currentProcessIndex].completionTime = currentTime;
                processes[currentProcessIndex].turnaroundTime = processes[currentProcessIndex].completionTime - processes[currentProcessIndex].arrivalTime;
                processes[currentProcessIndex].waitingTime = processes[currentProcessIndex].turnaroundTime - processes[currentProcessIndex].burstTime;
                processes[currentProcessIndex].responseTime = processes[currentProcessIndex].waitingTime;
            }

            printf(" -> [%s] %d", processes[currentProcessIndex].processName, currentTime);
        }

        currentProcessIndex = (currentProcessIndex + 1) % n;




    }
    printf("\n\n");

    printf("\n-----------------------------------------------------------------------------------------");

    // Calculate average performance metrics
    int totalWT = 0, totalRT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
    {
        totalWT += processes[i].waitingTime;
        totalRT += processes[i].responseTime;
        totalTAT += processes[i].turnaroundTime;
    }
    float avgWT = (float) totalWT / n;
    float avgRT = (float) totalRT / n;
    float avgTAT = (float) totalTAT / n;

    // Display process details
    printf("\n\nProcess\t Arrival Time \tBurst Time \tCompletion Time \tWaiting Time \tTurnaround Time \tResponse Time");
    for (int i = 0; i < n; i++)
        printf("\n%s\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\t\t\t %d", processes[i].processName, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime, processes[i].responseTime);
    printf("\n-----------------------------------------------------------------------------------------");

    // Display average performance metrics
    printf("\n\nAverage Waiting Time = %f", avgWT);
    printf("\nAverage Response Time = %f", avgRT);
    printf("\nAverage Turnaround Time = %f", avgTAT);
    printf("\n-----------------------------------------------------------------------------------------");

    // Generate performance report
    printf("\n\nPerformance Report:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %s:\n", processes[i].processName);
        printf("Waiting Time: %d\n", processes[i].waitingTime);
        printf("Turnaround Time: %d\n", processes[i].turnaroundTime);
        printf("Response Time: %d\n", processes[i].responseTime);
        printf("Completion Time: %d\n\n", processes[i].completionTime);
    }
}



// Function to implement Priority Preemptive scheduling
void priorityPreemptiveScheduling(struct Process processes[], int n)
{

    for (int i = 0; i < n; i++)
    {
        printf("Process %d:\n", i + 1);

        //enter the priority
        printf("Priority: ");
        if (scanf("%d", &processes[i].priority) != 1 || processes[i].priority < 0)
        {
            printf("Invalid priority. Please enter a non-negative integer.\n");
            return;
        }
        //enter the burst time
        printf("Burst Time: ");
        if (scanf("%d", &processes[i].burstTime) != 1 || processes[i].burstTime <= 0)
        {
            printf("Invalid burst time. Please enter a positive integer.\n");
            return ;
        }
        processes[i].remainingTime = processes[i].burstTime;
    }
    sortProcess(processes, n);



    int currentTime = 0;
    int completedProcesses = 0;
    int remainingProcesses = n;

    // Generate Gantt Chart
    printf("\n*************************************Gantt Chart*****************************************\n\n\n");
    printf("%d", currentTime);

    while (completedProcesses < n)
    {
        int highestPriority = -1;
        int highestPriorityIndex = -1;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0)
            {
                if (highestPriority == -1 || processes[i].priority < highestPriority)
                {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex != -1)
        {
            processes[highestPriorityIndex].remainingTime--;
            currentTime++;

            if (processes[highestPriorityIndex].remainingTime == 0)
            {
                completedProcesses++;
                remainingProcesses--;
                processes[highestPriorityIndex].completionTime = currentTime;
                processes[highestPriorityIndex].turnaroundTime = processes[highestPriorityIndex].completionTime - processes[highestPriorityIndex].arrivalTime;
                processes[highestPriorityIndex].waitingTime = processes[highestPriorityIndex].turnaroundTime - processes[highestPriorityIndex].burstTime;
                processes[highestPriorityIndex].responseTime = processes[highestPriorityIndex].waitingTime;
            }

            printf(" -> [%s] %d", processes[highestPriorityIndex].processName, currentTime);
        }
        else
        {

            currentTime++;
        }

    }
    printf("\n");


    // Calculate average performance metrics
    int totalWT = 0, totalRT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++)
    {
        totalWT += processes[i].waitingTime;
        totalRT += processes[i].responseTime;
        totalTAT += processes[i].turnaroundTime;
    }
    float avgWT = (float) totalWT / n;
    float avgRT = (float) totalRT / n;
    float avgTAT = (float) totalTAT / n;
    printf("\n-----------------------------------------------------------------------------------------");

    // Display process details including priority
    printf("\nProcess\t Arrival Time \tBurst Time\tCompletion Time \tWaiting Time \tTurnaround Time \tResponse Time");
    for (int i = 0; i < n; i++)
        printf("\n%s\t\t %d\t\t %d\t\t %d\t\t\t %d\t\t %d\t\t\t %d", processes[i].processName, processes[i].arrivalTime, processes[i].burstTime, processes[i].completionTime, processes[i].waitingTime, processes[i].turnaroundTime, processes[i].responseTime);

    printf("\n-----------------------------------------------------------------------------------------");

    // Display average performance metrics
    printf("\n\nAverage Waiting Time = %f", avgWT);
    printf("\nAverage Response Time = %f", avgRT);
    printf("\nAverage Turnaround Time = %f", avgTAT);

    printf("\n----------------------------------------------------------------------\n");
    // Generate performance report
    printf("\n\nPerformance Report:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %s:\n", processes[i].processName);
        printf("Waiting Time: %d\n", processes[i].waitingTime);
        printf("Turnaround Time: %d\n", processes[i].turnaroundTime);
        printf("Response Time: %d\n", processes[i].responseTime);
        printf("Completion Time: %d\n\n", processes[i].completionTime);
    }
}

//Function to sort process based on arrival time
void sortProcess(struct Process processes[], int n)
{
    // Sort the processes based on arrival time

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (processes[j].arrivalTime < processes[minIndex].arrivalTime)
                minIndex = j;
        }
        struct Process temp = processes[i];
        processes[i] = processes[minIndex];
        processes[minIndex] = temp;
    }
}
