#include<stdio.h>
#include<stdlib.h>

const int N=105;

struct Process
{
    int problemID;
    int burstTime;
    int arrivalTime;
    int waitingTime;
    int finishingTime;
    int turnaroundTime;
}process[N];

void SJF(const int& n)
{
    int complete,currentTime,index,minimum;

    index = -1;
    complete = 0;
    currentTime = 0;
    minimum = INT_MAX;

    while(complete < n)
    {
        for(int i=1; i<=n; i++)
        {
            if(process[i].arrivalTime <= currentTime)
            {
                if(process[i].burstTime < minimum  &&  process[i].finishingTime == 0)
                {
                    index = i;
                    minimum = process[i].burstTime;
                }
            }
        }

        if(index > 0)
        {
            complete++;
            minimum = INT_MAX;
            currentTime += process[index].burstTime;
            process[index].finishingTime = currentTime;
            process[index].turnaroundTime = process[index].finishingTime - process[index].arrivalTime;
            process[index].waitingTime =  process[index].turnaroundTime- process[index].burstTime;

            index = -1;
        }
        else currentTime++;
    }
}

void PrintTable(const int& n)
{
    printf("+-----+------------+--------------+-----------------+\n");
    printf("| PID | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("+-----+------------+--------------+-----------------+\n");

    for(int i=1; i<=n; i++)
    {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
               , process[i].problemID, process[i].burstTime, process[i].waitingTime, process[i].turnaroundTime);
        printf("+-----+------------+--------------+-----------------+\n");
    }
}

void PrintGanttChart(const int& n)
{
    int i, j;
    printf(" ");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=process[i].burstTime; j++)printf("--");
        printf(" ");
    }
    printf("\n|");

    for(i=1; i<=n; i++)
    {
        for(j=1; j<process[i].burstTime; j++)printf(" ");
        printf("P%d", process[i].problemID);
        for(j=1; j<process[i].burstTime; j++)printf(" ");
        printf("|");
    }
    printf("\n ");

    for(i=1; i<=n; i++)
    {
        for(j=1; j<=process[i].burstTime; j++)printf("--");
        printf(" ");
    }
    printf("\n");

    printf("0");
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=process[i].burstTime; j++)printf("  ");
        if(process[i].turnaroundTime > 9)printf("\b"); // backspace : remove 1 space
        printf("%d", process[i].turnaroundTime);
    }
    printf("\n");
}

int main()
{
    int i,n,totalWaitingTime=0,totalTurnaroundTime=0;
    printf("SHORTEST JOB FIRST SCHEDULING ALGORITHM\n");
    printf("=======================================\n\n");

    printf("Enter total number of process : ");
    scanf("%d",&n);
    printf("\nEnter burst time for each process:\n");
    for(i=1; i<=n; i++)
    {
        process[i].problemID = i;
        printf("Process[%d] : ", i);
        scanf("%d", &process[i].burstTime);
        process[i].waitingTime = process[i].turnaroundTime = 0;
    }

    printf("\nEnter arrival time for each process:\n");
    for(i=1; i<=n; i++)
    {
        printf("Process[%d] : ", i);
        scanf("%d", &process[i].arrivalTime);
    }

    SJF(n);

    // calculate waiting time and turnaround time
    for(i=1; i<=n; i++)
    {
        totalWaitingTime += process[i].waitingTime;
        totalTurnaroundTime += process[i].turnaroundTime;
    }

    // print table
    printf("\n\n");
    PrintTable(n);
    printf("\n");
    printf("Total Waiting Time      : %-2d\n", totalWaitingTime);
    printf("Average Waiting Time    : %-2.2lf\n", (double)totalWaitingTime / (double) n);
    printf("Total Turnaround Time   : %-2d\n", totalTurnaroundTime);
    printf("Average Turnaround Time : %-2.2lf\n", (double)totalTurnaroundTime / (double) n);

    // print Gantt chart
    printf("\n\n");
    puts("          Gantt Chart          ");
    puts("          ***********          ");
    PrintGanttChart(n);

    return 0;
}
