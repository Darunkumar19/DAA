#include <stdio.h>
#define MAX 50

struct Job{
    char id[5];
    int deadline;
    int profit;
};

void sortJobs(struct Job jobs[], int n)
{
    int i, j;
    struct Job temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (jobs[i].profit < jobs[j].profit)
            {
                temp = jobs[i];
                jobs[i] = jobs[j];
                jobs[j] = temp;
            }
        }
    }
}

int main()
{
    struct Job jobs[MAX];
    int n, i, j, maxD = 0;
    int slot[MAX];
    int totalProfit = 0;

    printf("Enter number of jobs: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter Job id, Profit and Deadline: ");
        scanf("%s %d %d", jobs[i].id,
                              &jobs[i].profit,
                              &jobs[i].deadline);

        if (jobs[i].deadline > maxD)
            maxD = jobs[i].deadline;
    }

    sortJobs(jobs, n);
    for (i = 0; i <= maxD; i++)
        slot[i] = -1;

    for (i = 0; i < n; i++)
    {
        for (j = jobs[i].deadline; j > 0; j--)
        {
            if (slot[j] == -1)
            {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\nJob Sequence:\n");
    for (i = 1; i <= maxD; i++)
    {
        if (slot[i] != -1)
            printf("%s ", jobs[slot[i]].id);
    }

    printf("\nTotal Profit= %d\n", totalProfit);

    return 0;
}