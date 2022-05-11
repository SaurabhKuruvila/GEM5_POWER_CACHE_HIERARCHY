#include <stdio.h>
#include <stdlib.h>

#define NUM 5         /* number of arrays */

#define NBUCKET 1024 /* bucket size */
// #define NBUCKET 9216 /* bucket size */
// #define NBUCKET 16382 /* bucket size */

#define INTERVAL 10   /* bucket range */

#define NARRAY NBUCKET * INTERVAL

struct Node
{
    int data;
    struct Node *next;
};

void BucketSort(int arr[]);
struct Node *InsertionSort(struct Node *list);
void print(int arr[]);
void printBuckets(struct Node *list);
int getBucketIndex(int value);

void BucketSort(int arr[])
{
    int i, j;
    struct Node **buckets;
    buckets = (struct Node **)malloc(sizeof(struct Node *) * NBUCKET);
    for (i = 0; i < NBUCKET; ++i)
    {
        buckets[i] = NULL;
    }

    for (i = 0; i < NARRAY; ++i)
    {
        struct Node *current;
        int pos = getBucketIndex(arr[i]);
        current = (struct Node *)malloc(sizeof(struct Node));
        current->data = arr[i];
        current->next = buckets[pos];
        buckets[pos] = current;
    }

    /* sorting bucket using Insertion Sort */
    for (i = 0; i < NBUCKET; ++i)
    {
        buckets[i] = InsertionSort(buckets[i]);
    }

    for (j = 0, i = 0; i < NBUCKET; ++i)
    {
        struct Node *node;
        node = buckets[i];
        while (node)
        {
            if(j < NARRAY)
            {
                arr[j++] = node->data;
                node = node->next;
            }
        }
    }
    
    for (i = 0; i < NBUCKET; ++i)
    {
        struct Node *node;
        node = buckets[i];
        while (node)
        {
            struct Node *tmp;
            tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(buckets);
    return;
}

/* Insertion Sort */
struct Node *InsertionSort(struct Node *list)
{
    struct Node *k, *nodeList;
    if (list == NULL || list->next == NULL)
    {
        return list;
    }

    nodeList = list;
    k = list->next;
    nodeList->next = NULL;
    while (k != NULL)
    {
        struct Node *ptr;
        /* check if insert before first */
        if (nodeList->data > k->data)
        {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = nodeList;
            nodeList = tmp;
            continue;
        }

        for (ptr = nodeList; ptr->next != NULL; ptr = ptr->next)
        {
            if (ptr->next->data > k->data)
                break;
        }

        if (ptr->next != NULL)
        {
            struct Node *tmp;
            tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        }
        else
        {
            ptr->next = k;
            k = k->next;
            ptr->next->next = NULL;
            continue;
        }
    }
    return nodeList;
}

int getBucketIndex(int value) { return value / INTERVAL; }

void print(int ar[])
{
    int i;
    for (i = 0; i < NARRAY; ++i)
    {
        printf("%d ", ar[i]);
    }
    printf("\n");
}

void printBuckets(struct Node *list)
{
    struct Node *cur = list;
    while (cur)
    {
        printf("%d ", cur->data);
        cur = cur->next;
    }
}

int main(void)
{
    int array[NUM][NARRAY];
    printf("Bucket Sort [%d Arrays] [Total Size: %ld Bytes]\n", NUM, sizeof(array));
    for (int iter = 0; iter < NUM; iter++)
    {
        for (int i = 0; i < NARRAY; i++)
        {
            array[iter][i] = iter + i ;
        }
        // print(array[iter]);
        BucketSort(array[iter]);
        // print(array[iter]);
    }
    // getc(stdin);
    return 0;
}