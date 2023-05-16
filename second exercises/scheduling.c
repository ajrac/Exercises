#include<stdio.h>
#include <stdbool.h>
int main(){
    // Initialize variables
    int i = 0, num_processes = 0, total_time = 0, x, output_flag = 0,
    time_quantum =0;
    int wait_time = 0, turnaround_time = 0, arrival_time[10], burst_time[10],
    temp[10];
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = true;
    for(i = 0; i < 10; i++)
    {
        arrival_time[i] = 0;
        burst_time[i] = 0;
        temp[i] = 0;
    }
    // Define Number of Processes
    while(num_processes < 1 || num_processes > 10)
    {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);
        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    }
    // Define Process Details
    x = num_processes;
    for(i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>-1):\t");
        scanf("%d", &arrival_time[i]);
        printf("Burst Time (>0):\t");
        scanf("%d", &burst_time[i]);
        temp[i] = burst_time[i];
        if (arrival_time[i] < 0 && burst_time[i] < 1) {
            printf("Incorrect Values Entered");
            i--;
        }
    }
    // Define Quantum
    if (round_robin_algorithm)
    {
        while(time_quantum < 1)
        {
            printf("\nEnter Time Quantum (>0):\t");
            scanf("%d", &time_quantum);
            if (time_quantum < 1)
            {
                printf("Incorrect Value Entered");
            }
        }
    }
    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\t Turnaround Time\t Waiting Time\n");
    // Perform Scheduling Calculations
    int total_wait_time = 0, total_turnaround_time = 0;
    if (!round_robin_algorithm)
    {
        //Sort processes based on their arrival time
        int j;
        for(i=0; i<num_processes; i++)
        {
            for(j=i+1; j<num_processes; j++)
            {
                if(arrival_time[i] > arrival_time[j])
                {
                    //Swap arrival times
                    int temp = arrival_time[i];
                    arrival_time[i] = arrival_time[j];
                    arrival_time[j] = temp;

                    //Swap burst times
                    temp = burst_time[i];
                    burst_time[i] = burst_time[j];
                    burst_time[j] = temp;
                }
            }
        }

        int waiting_time[10], turnaround_time[10];

        //First process always has waiting time of 0
        waiting_time[0] = 0;

        //Calculate waiting time and turnaround time for each process
        for(i=1; i<num_processes; i++)
        {
            waiting_time[i] = burst_time[i-1] + waiting_time[i-1] - arrival_time[i] + arrival_time[i-1];
            waiting_time[i] = (waiting_time[i]<0)? 0 : waiting_time[i];
            turnaround_time[i] = waiting_time[i] + burst_time[i];
        }


    // Print Process details
    for(i=0; i<num_processes; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], turnaround_time[i], waiting_time[i]);

        // Calculate total wait time and total turnaround time
        total_wait_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    average_wait_time = (float)total_wait_time / num_processes;
    average_turnaround_time = (float)total_turnaround_time / num_processes;
    }
    
    else
    {
        total_wait_time = 0, total_turnaround_time = 0;
        int rem_burst_time[10];

        for (i = 0 ; i < num_processes ; i++)
        {
            rem_burst_time[i] =  burst_time[i];
        }

        while (1)
        {
            bool done = true;

            for (i = 0 ; i < num_processes; i++)
            {
                if (rem_burst_time[i] > 0)
                {
                    done = false;

                    if (rem_burst_time[i] > time_quantum)
                    {
                        total_time += time_quantum;
                        rem_burst_time[i] -= time_quantum;
                    }
                    else
                    {
                        total_time += rem_burst_time[i];
                        wait_time = total_time - burst_time[i];
                        turnaround_time = total_time;
                        rem_burst_time[i] = 0;

                        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i+1, arrival_time[i], burst_time[i], turnaround_time, wait_time);

                        total_wait_time += wait_time;
                        total_turnaround_time += turnaround_time;
                    }
                }
            }

            if (done == true)
            break;
        }

        average_wait_time = (float)total_wait_time / num_processes;
        average_turnaround_time = (float)total_turnaround_time / num_processes;
    }
    // Calculate & Print Average Wait and Turnaround Times
    average_wait_time = 0;
    average_turnaround_time = 0;
    printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
    printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);
    return 0;
}