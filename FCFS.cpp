#include<stdio.h>

const int N=100+5;

struct Process
{
    int problemID;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
}process[N];

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
    printf("Enter total number of process : ");
    scanf("%d",&n);
    printf("Enter burst time for each process:\n");
    for(i=1; i<=n; i++)
    {
        process[i].problemID = i;
        printf("Process[%d] : ", i);
        scanf("%d", &process[i].burstTime);
        process[i].waitingTime = process[i].turnaroundTime = 0;
    }

    // calculate waiting time and turnaround time
    process[1].turnaroundTime = process[1].burstTime;
    for(i=2; i<=n; i++)
    {
        process[i].waitingTime = process[i-1].waitingTime + process[i-1].burstTime;
        process[i].turnaroundTime = process[i].waitingTime + process[i].burstTime;

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

