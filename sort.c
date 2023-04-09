// Nicholas Mistry


#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated

void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}


void heapify(int arr[], int n, int i) {
  
  int largest = i; // start largest as root
  int l = 2*i + 1; // left
  int r = 2*i + 2; // right


  // Look at branches of the tree and try to find the largest root
  if (l < n && arr[l] > arr[largest]) {
    largest = l;
  }
  
  if (r < n && arr[r] > arr[largest]) {
    largest = r;
  }
  // Recursively find the largest
  if (largest != i) {
    swap(&arr[i], &arr[largest]);
    heapify(arr, n, largest);
  }
}

void buildMaxHeap(int arr[], int n) {
  int node = (n/2) - 1;
  for (int i=node;i >=0; i--) {
    heapify(arr,n,i);
  }
}

void heapSort(int arr[], int n)
{
  // Find largest, swap then build sorted array
  
  buildMaxHeap(arr,n); // Call Max Heap which would allow us to access the largest node
  // Heap sort
  for (int i = n - 1; i >= 0; i--) {
    swap(&arr[0], &arr[i]);
    heapify(arr, i, 0);
  }

  // Call Max Heap, Swap, then Heapify
  
}
void merge(int pData[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
  // Count Extra Memory Allocated
    int *LEFT = (int*) malloc(n1*sizeof(int));
    extraMemoryAllocated = extraMemoryAllocated + n1;
    int *RIGHT = (int*) malloc(n2*sizeof(int));
    extraMemoryAllocated = extraMemoryAllocated + n2;

    // insert info into LEFT and RIGHT tail arrays
    for (i = 0; i < n1; i++) {
      LEFT[i] = pData[l + i];
    }
    for (j = 0; j < n2; j++) {
       RIGHT[j] = pData[m + 1+ j];
    }
  // Reset back to 0 and set k equal to l
    i = 0;
    j = 0;
    k = l;
  // Begin the merge!
    while (i < n1 && j < n2) {
      if (LEFT[i] <= RIGHT[j]) { // Compare values and build the array
        pData[k] = LEFT[i]; // Build with Left
            i++;
      } else {
        pData[k] = RIGHT[j]; // build with right
        j++;
      }
      k++;
    }
// Put the remaining elements if exists
    while (i < n1) {
      pData[k] = LEFT[i];
      i++;
      k++;
    }
   
    while (j < n2) {
      pData[k] = RIGHT[j];
      j++;
      k++;
      }
      // Free the temp arrays
    free(LEFT);
    free(RIGHT);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
  if (l < r) {
    int middle_point = (l+r)/2;

    // Recursively divide and merge
    mergeSort(pData, l, middle_point);
    mergeSort(pData, middle_point+1, r);

    merge(pData, l, middle_point, r);
  }
    
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
    FILE* inFile = fopen(inputFileName,"r");
    int dataSz = 0;
    int i, n, *data;
    *ppData = NULL;
    
    if (inFile)
    {
        fscanf(inFile,"%d\n",&dataSz);
        *ppData = (int *)malloc(sizeof(int) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i=0;i<dataSz;++i)
        {
            fscanf(inFile, "%d ",&n);
            data = *ppData + i;
            *data = n;
        }

        fclose(inFile);
    }
    
    return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
    int i, sz = dataSz - 100;
    printf("\tData:\n\t");
    for (i=0;i<100 && i<dataSz;++i) // Fix, Added check to make sure i<dataSz
    {
        printf("%d ",pData[i]);
    }
    printf("\n\t");
    
    for (i=sz;i<dataSz && i>0;++i) // Fix, only iterate for i above 0
    {
        printf("%d ",pData[i]);
    }
    printf("\n\n");
}

int main(void)
{
    clock_t start, end;
    int i;
    double cpu_time_used;
    char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
    
    for (i=0;i<4;++i)
    {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);
        
        if (dataSz <= 0)
            continue;
        
        pDataCopy = (int *)malloc(sizeof(int)*dataSz);
    
        printf("---------------------------\n");
        printf("Dataset Size : %d\n",dataSz);
        printf("---------------------------\n");
        
        printf("Heap Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        heapSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
        printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
        printArray(pDataCopy, dataSz);
        
        free(pDataCopy);
        free(pDataSrc);
    }
    
}
