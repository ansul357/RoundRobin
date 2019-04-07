#include <stdio.h>
#include <stdlib.h>
static int n;
int i,j,total_time=0;//Time quantum
float avgtat=0,avgwt=0;
int queue[];
int time=0,front=0,rear=0,q_count=0;//q_count=no. of elements in the queue
struct data
{
    int arri_t,bur_t,comp_t,tat,wt;
    char process_name[30];
    float ntat;
}temp;

main()
{
  printf("Enter the no of process\n");
  scanf("%d",&n);
  struct data aa[n];
  for(i=0;i<n;i++)
  {
      printf("Enter the Details for  the process %d\n",i);
       printf("Enter the  process name\n");
      scanf("%s",&aa[i].process_name);
       printf("Enter the  Arrival Time and Burst Time\n");
      scanf("%d%d",&aa[i].arri_t,&aa[i].bur_t);
  }
  //Queue Sorting
  for(i=0;i<n;i++)
  {
      for(j=1;j>=1;j--)
      {
          if(aa[j].arri_t<aa[j-1].arri_t)
          {
              temp=aa[j-1];
              aa[j-1]=aa[j];
              aa[j]=temp;
          }

      else if(aa[j].arri_t==aa[j-1].arri_t)
      {
          if(aa[j].bur_t<aa[j-1].bur_t)
          {
              temp=aa[j-1];
              aa[j-1]=aa[j];
              aa[j]=temp;
          }
      }

      }


  }
// Finding total time
    total_time+=aa[0].arri_t+aa[0].bur_t;
    for(i=1;i<n;i++)
    {
        if(aa[i].arri_t>total_time)
            total_time=aa[i].arri_t;
            total_time+=aa[i].bur_t;
    }
// Finding the completion Time
  finding(aa);
}
void push(int q)
{
    queue[rear++]=q;
}
int pop()
{
    int x;
    x=queue[front++];
    return x;
}
void check(struct data a[])
{
    while(a[j].arri_t<=time&&j<n)
    {
        q_count++;
        push(j++);
    }
}
void finding(struct data a[])
{
    int temp_st[n],flag=0,count=0,p_process;
    j=0;
    int tq;
    printf("Enter the Time quantum");
    scanf("%d",&tq);
    for(i=0;i<n;i++)
    {
        temp_st[i]=a[i].bur_t;
    }
    time=a[0].arri_t;
    q_count=1;
    push(j++);
    while(time<=total_time)
    {
        if(flag==1||q_count!=0)
        {
            if(flag==0&&count==0)
            {
                p_process=pop();
                count=0;
                flag=1;
            }
            temp_st[p_process]--;
            if(temp_st[p_process]==0)
            {
              time++;
              count=0;
              a[p_process].comp_t=time;
              flag=0;
              q_count--;
              check(a);
              continue;
            }
            count++;
            if(count==tq)
            {
                count=0;
                time++;
                check(a);
                push(p_process);
                flag=0;

            }
            else
            {
                time++;
                check(a);
            }
        }
        else
        {
            time++;
            check(a);
        }
    }
display(a);
}
void display(struct data a[])
{
    printf("pname\tAT\tBT\tCT\tTAT\tWT\n");
    for(i=0;i<n;i++)
    {
        a[i].tat=a[i].comp_t-a[i].arri_t;
        a[i].wt=a[i].tat-a[i].bur_t;
        avgwt=avgwt+a[i].wt;
        avgtat=avgtat+a[i].tat;
     printf("%s\t%d\t%d\t%d\t%d\t%d\n",a[i].process_name,a[i].arri_t,a[i].bur_t,a[i].comp_t,a[i].tat,a[i].wt);
    }

    avgwt=avgwt/n;
     avgtat=avgtat/n;
    printf("The average Weight time for the Scheduling is=%f and Average Turnaround Time=%f\n",avgwt,avgtat);
}

