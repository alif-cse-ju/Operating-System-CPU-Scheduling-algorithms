#include<stdio.h>

const int N=100+5;

int main()
{
      int i, limit, total = 0, x, counter = 0, timeQuantum;
      int waitTime = 0, turnaroundTime = 0, arrivalTime[N], burstTime[N], temp[N];
      double averageWaitTime, averageTurnaroundTime;
      printf("\nEnter Total Number of Processes:\t");
      scanf("%d", &limit);
      x = limit;
      for(i = 0; i < limit; i++)
      {
            printf("\nEnter Details of Process[%d]\n", i + 1);
            printf("Arrival Time:\t");
            scanf("%d", &arrivalTime[i]);
            printf("Burst Time:\t");
            scanf("%d", &burstTime[i]);
            temp[i] = burstTime[i];
      }
      printf("\nEnter Time Quantum:\t");
      scanf("%d", &timeQuantum);
      printf("\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
      total = 0, i = 0;
      while(x != 0)
      {
            if(temp[i] <= timeQuantum && temp[i] > 0)
            {
                  total = total + temp[i];
                  temp[i] = 0;
                  counter = 1;
            }
            else if(temp[i] > 0)
            {
                  temp[i] = temp[i] - timeQuantum;
                  total = total + timeQuantum;
            }
            if(temp[i] == 0 && counter == 1)
            {
                  x--;
                  printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burstTime[i], total - arrivalTime[i], total - arrivalTime[i] - burstTime[i]);
                  waitTime = waitTime + total - arrivalTime[i] - burstTime[i];
                  turnaroundTime = turnaroundTime + total - arrivalTime[i];
                  counter = 0;
            }
            if(i == limit - 1)i = 0;
            else if(arrivalTime[i + 1] <= total)i++;
            else i = 0;
      }
      averageWaitTime = waitTime * 1.0 / limit;
      averageTurnaroundTime = turnaroundTime * 1.0 / limit;
      printf("\n\nAverage Waiting Time:\t%lf", averageWaitTime);
      printf("\nAvg Turnaround Time:\t%lf\n", averageTurnaroundTime);
      return 0;
}
