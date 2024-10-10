#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int findNumLines(FILE *fp);
int writeDestFileSUM(FILE *fp, int b, int c, int S);
int writeDestFileDIF(FILE *fp, int b, int c, int a);


FILE *srcFP, *destFP;
int numLines, *data;

//not EVERY case, confused how to get that... this will def give at least one LMAO (if exists :pray:)//

//merge sort for nlogn time
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    //temp arrays
    int leftArr[n1], rightArr[n2];

    //copy data to temp arrays
    for (i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    //the merge in mergesort
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    //copy remaining elemensts (left)
    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    //copy remaining elements (right)
    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

//the subarray to be sorted is in the index range [left-right]
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
      
        //calculate the midpoint
        int mid = left + (right - left) / 2;

        //sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        //merge in mergesort
        merge(arr, left, mid, right);
    }
}

// Function to print all keys where a = b - c using a two-pointer approach
//function
//print key where a = b - c
//pointers from left and right to close in on correct pair
//move right pointer for smaller
//move left pointer for larger
void difference(int arr[], int n) {
    //the sort in mergesort (for nlogn time)
    //printf("about to merge\n");
    mergeSort(arr, 0, n-1);

    //START TIME
    clock_t start_time = clock();

    //for each element a
    for (int a_index = 0; a_index < n; a_index++) {
        //printf("diff for start\n");
        int a = arr[a_index]; //a = a lol

        //two pointers to find pairs (b, c) so b - c = a
        int left = 0;
        int right = n - 1;
        //printf("left: %d, right %d\n", left, right);

        while (left < right) {
            //printf("diff while");
            int b = arr[right];
            int c = arr[left];
            int diff = b - c; //difference = b - c

            //printf("testing. b = %d, c = %d, a = %d\n", b, c, a);

            if (diff == a) {
                //FOUND IT
                //printf("Found case: a = %d, b = %d, c = %d\n", a, b, c);
                printf("case: %d - %d = %d\n", b, c, a);
                writeDestFileDIF(destFP, b, c, a);
                left++;
                right--;

                //for finding one
                //time (success)
                clock_t end_time = clock();
                double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
                printf("Running time: %f seconds\n", time_spent);
                return;
                
            } else if (diff > a) {
                //decrease b by moving the right pointer left (difference larger)
                if((left == right+1) && (right != n-1)) { //if right next to eachother and still not found, go back to check if left bound was the problem. 
                    left++;
                    right++;
                }
                else {
                    right--;
                }
                
            } else {
                //move right and left back to check for more cases (for edge cases)
                left++;
                if(right != n-1){
                    right++;
                }
                

            }
        }
    }

    //time (fail)
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    // for finding one
    printf("No pairs found, ");
    printf("running time: %f seconds\n", time_spent);
}

void summs(int arr[], int n, int S) {
    //the sort in mergesort (for nlogn time)
    mergeSort(arr, 0, n-1);

    //START TIME
    clock_t start_time = clock();

    //for each element a

    //two pointers to find pairs (b, c) so b + c = S = sum
    int left = 0;
    int right = n - 1;

    while (left < right) {
        int b = arr[right];
        int c = arr[left];
        int sum = b + c; //sum = b + c

        if (sum == S) {
            //FOUND IT
            //printf("Found case: a = %d, b = %d, c = %d\n", a, b, c);
            //printf("case: %d + %d = %d\n", b, c, S);
            writeDestFileSUM(destFP, b, c, S);
            left++;
            right--;

/*
            //for finding one
            //time (success)
            clock_t end_time = clock();
            double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            printf("Running time: %f seconds\n", time_spent);
            return;
*/            
        } else if (sum < S) {
            //sum too small increase sum
            left++;
        } else {
            //sum too large decrease sum
            right--;

        }
    }

    //time (fail)
    clock_t end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    //for finding one
    //printf("No pairs found, ");
    printf("running time: %f seconds\n", time_spent);
}


int main(int argc, char* argv[]) {
    int i;
    int S = -1;
    char str[100];

    if(argc!=3) {
    printf("Usage: progname <input_file> <output_file>");
    exit(0);
    }

    if((srcFP =fopen(argv[1], "r")) == NULL) {
    perror("Error opening input file");
    exit(0);
    }

    numLines = findNumLines(srcFP);
    data = (int *) malloc(numLines * sizeof(int));
    int count = 0;

    for(i=0; i<=numLines; i++) {
        fgets(str, 100, srcFP);
        //printf("%s ", str);
        //if read str[0] = 'S', S = str[0].toint()
        //if read str[0] = '/', ignore line
        //printf("str[0] = %c\n", str[0]);
        if(str[0] == 'S') {
            //S = 5;
            fgets(str, 100, srcFP);
            S = atoi(str);
            //sum = true;
        }
        else if(str[0] == '/' || str[0] == '\n') {
            printf("comment/space detected\n");
        }
        else if (str[0] > 47 && str[0] < 58) {
            sscanf(str, "%lld", &(data[count]));
            count++;
            //printf("we found one (%s), count: %d\n", str, count);
        }
        else {
            printf("char not recognized lil bro\n");
        }

    }

  if((destFP = fopen(argv[2], "w")) == NULL) {
    perror("Error opening output file");
    exit(0);
  }
  
  //writeDestFile(destFP);


/*
    //have to make array from reading in argv[1]
    
    if (argc > 1) {
        int arr[] = argv[1]
    }
    else{}
    int arr[] = {14, 89, 18, 105, 23, 4, 35, 99, 67, 76, 198, 20, 5, 38, 55, 2, 30, 19,
                487, 11, 40, 10, 13, 27, 22, 45, 37, 231, 46, 17, 731, 49, 167, 234, 59, 91, 179, 201};
    
    

    //call to actual func
    char y;
    printf("sum or difference (s or d): ");
    scanf("%c", &y);
*/
//int n = sizeof(data) / sizeof(data[0]);
//printf("About to choose, S = %d\nalso here is n(%d) compared to numlines (%d) compared to count (%d)\n", S, n, numLines, count);
    if(S == -1) {
        printf("going into difference\n");
        difference(data, count);
    }
    else {
        summs(data, count, S);
    }
    
    fclose(srcFP);
    fclose(destFP);
    return 0;
}

int writeDestFileDIF(FILE *fp, int b, int c, int a) {
  //int i;
  //for(i = 0; i < numLines; i++)
    //fprintf(fp, "%d\n", data[i]*data[i]);
    //fprintf(fp, "case: %d - %d = %d\n", b, c, a); //long print
    fprintf(fp, "%d\n", a); //short print
}

int writeDestFileSUM(FILE *fp, int b, int c, int S) {
  //int i;
  //for(i = 0; i < numLines; i++)
    //fprintf(fp, "%d\n", data[i]*data[i]);
    //fprintf(fp, "case: %d + %d = %d\n", b, c, S); //long print
    fprintf(fp, "%d + %d\n", b, c); //short print
}

//returns file size as number of lines in the file
int findNumLines(FILE *fp) {

  int numLines = 0;
  char str[100];

  while(!feof(fp)) {
    fgets(str, 100, fp);
    numLines++;
  }
  
  numLines--;//the above increments count even when EOF reached
  
  if(fseek(fp, 0L, SEEK_SET) == EOF) {
    perror("Error while seeking to begining of file");
    exit(0);
  }

  return numLines;
}