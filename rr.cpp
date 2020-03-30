#include<stdio.h> 
#include<conio.h>
void round(int num,int rem_time[10],int Cur_t,int arri_Time[10], int bsT[10]);
main() 
{
	int Proc_num,j,num_proc,C_Time,RemProc,count,time_quan,wait,tat,arri_Time[10],bsT[10],rem_time[10],x=1;
	count = 0;
	wait = 0;
	tat = 0;
	printf("Enter number of processes "); 
	scanf("%d",&num_proc);
	RemProc = num_proc;
	printf("\nEnter the arrival time and burst time of the processes\n");
	for(Proc_num = 0;Proc_num < num_proc;Proc_num++) 
	{
		printf("\nProcess P%d\n",Proc_num+1);
		printf("Arrival time = "); 
		scanf("%d",&arri_Time[Proc_num]);
		printf("Burst time = "); 
		scanf("%d",&bsT[Proc_num]); 
		rem_time[Proc_num]=bsT[Proc_num]; 
	} 
	printf("The details of time quantum are as follows:\n");
	printf("The time quantum for first round is 6.\n"); 
	time_quan=6;
	C_Time=0;
	for(Proc_num=0;RemProc!=0;) 
	{
		if(rem_time[Proc_num]<=time_quan && rem_time[Proc_num]>0)
		{ 
			C_Time+=rem_time[Proc_num]; 
			rem_time[Proc_num]=0; 
			count=1; 
		} 
		else if(rem_time[Proc_num]>0)
		{ 
			rem_time[Proc_num]-=time_quan; 
			C_Time+=time_quan; 
		} 
		if(rem_time[Proc_num]==0 && count==1)			
		{ 
		    printf("%d",Proc_num);
			RemProc--;				
			printf("P %d",Proc_num+1); 
			printf("\t\t\t%d",C_Time-arri_Time[Proc_num]);
			printf("\t\t\t%d\n",C_Time-bsT[Proc_num]-arri_Time[Proc_num]);
			wait+=C_Time-arri_Time[Proc_num]-bsT[Proc_num]; 
			tat+=C_Time-arri_Time[Proc_num]; 
			count=0;              
		} 
		if(Proc_num==num_proc-1)
		{
			x++;
			if(x==2)
			{
				Proc_num=0;
				time_quan=10;
				
				printf("The time quantum for second round is 10. \n");
			}
			else
			{
				break;
			}
		}
		else if(C_Time >= arri_Time[Proc_num+1])
		{
			Proc_num++;
		}
		else
		{
			Proc_num=0;
		}
	}
	round(num_proc,rem_time,C_Time,arri_Time,bsT);
	return 0;
}
void round(int no,int rem_time[10],int Cur_t,int arT[10], int bsT[10])
{	
	float avg_wait,avg_tut;
    int i,j,n=no,temp,btime[20],Proc_num[20],w_time[20],tut_t[20],total=0,loc;
    for(i=0;i<n;i++)
    {
        btime[i]=rem_time[i];
        w_time[i]=Cur_t-arT[i]-btime[i];
		Proc_num[i]=i+1;
    }
    for(i=0;i<n;i++)
    {
        loc=i;
        for(j=i+1;j<n;j++)
        {
            if(btime[j]<btime[loc])
			{
            	loc=j;
            }
        }
        temp=btime[i];
        btime[i]=btime[loc];
        btime[loc]=temp;
        temp=Proc_num[i];
        Proc_num[i]=Proc_num[loc];
        Proc_num[loc]=temp;
    }	
    for(i=1;i<n;i++)
    {
        for(j=0;j<i;j++)
		{
        	w_time[i]+=btime[j];
        }
        total+=w_time[i];
    }
    avg_wait=(float)total/n;
    total=0;
    printf("\nProcess\t\tBurst time\t\twaiting time\t\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tut_t[i]=btime[i]+w_time[i];
        total=total + tut_t[i];
        printf("\nP%d\t\t\t%d\t\t\t%d\t\t\t%d",Proc_num[i],btime[i],w_time[i],tut_t[i]);
    }
    avg_tut=(float)total/n;
    printf("\n\nAverage waiting time = %f",avg_wait);
    printf("\n Average turnaround time = %f\n",avg_tut);
}

