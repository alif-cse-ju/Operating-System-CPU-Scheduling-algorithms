#include<stdio.h>
#include<stdlib.h>

const int N=105;

struct Process
{
    int problemID;
    int burstTime;
    int arrivalTime;
}process[N];

int waitingTime[N],turnaroundTime[N],tmp[N];

void SRTF(const int& n)
{
    for (int i = 1; i <= n; i++)tmp[i] = process[i].burstTime;

    int complete = 0, t = 0, minimum = INT_MAX;
    int shortest = 0, finishTime;
    bool check = false;

    while (complete != n)
    {
        for(int j = 1; j <= n; j++)
        {
            if((process[j].arrivalTime <= t)  &&  (tmp[j] < minimum) && tmp[j] > 0)
            {
                minimum = tmp[j];
                shortest = j;
                check = true;
            }
        }

        if (!check)
        {
            t++;
            continue;
        }
        tmp[shortest]--;
        minimum = tmp[shortest];
        if(minimum == 0)minimum = INT_MAX;

        if (tmp[shortest] == 0)
        {
            complete++;
            check = false;

            finishTime = t + 1;
            waitingTime[shortest] = finishTime - process[shortest].burstTime - process[shortest].arrivalTime;

            if (waitingTime[shortest] < 0)waitingTime[shortest] = 0;
        }
        t++;
    }

    for (int i = 1; i <= n; i++)turnaroundTime[i] = process[i].burstTime + waitingTime[i];
}

void PrintTable(const int& n)
{
    printf("+-----+------------+--------------+-----------------+\n");
    printf("| PID | Burst Time | Waiting Time | Turnaround Time |\n");
    printf("+-----+------------+--------------+-----------------+\n");

    for(int i=1; i<=n; i++)
    {
        printf("| %2d  |     %2d     |      %2d      |        %2d       |\n"
               , process[i].problemID, process[i].burstTime, waitingTime[i], turnaroundTime[i]);
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
        if(turnaroundTime[i] > 9)printf("\b"); // backspace : remove 1 space
        printf("%d", turnaroundTime[i]);
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
    }

    printf("\nEnter arrival time for each process:\n");
    for(i=1; i<=n; i++)
    {
        printf("Process[%d] : ", i);
        scanf("%d", &process[i].arrivalTime);
    }

    SRTF(n);

    // calculate waiting time and turnaround time
    for(i=1; i<=n; i++)
    {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
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
