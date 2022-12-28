// Name: Muhammad Usman  Reg # 200901104  BS-CS-01-A Assign # 03 OS
// implementing multithreading mergesort 
#include <iostream>
#include <pthread.h> 

using namespace std;

int i;
pthread_t  tid1,tid2,tid3,tid4;  //as i have four cores so i have to declare four threads
int *arr, *res;  


void* sort_array1(void* arg) // sorting first quarter of size of array in thread 1
{

    int size = *((int *)arg); // this is how arguments which is pass thorugh main fucntion using pthread can be assign
    						 // to another variable 

    for (int i = 0; i < size/4; i++) 		// size/4 gives us the first quarter of array
    {
        for (int j = 0; j < size/4; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]); // using bulit in swap function for swaping of greater values with smaller value in an first quarter of array
        }
    }
    return NULL;
}

void* sort_array2(void* arg) // sorting second quarter of size of array in thread 2
{

    int size = *((int*)arg); 

    for (int i = size/4; i < size/2; i++) // size/2 gives us the second quarter of array
    {
        for (int j = size/4; j < size/2; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    return NULL;
}

void* sort_array3(void* arg) // sorting third quarter of size of array in thread 3
{

    int size = *((int*)arg); 

    for (int i = size/2; i < size-size/4; i++) // size-size/2 gives us the third quarter of array
    {
        for (int j = size/2; j < size-size/4; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    return NULL;
}

void* sort_array4(void* arg) 
{

    int size = *((int*)arg); 

    for (int i = size-size/4; i < size; i++) // now reamaining array is the fourth quarter of array
    {
        for (int j = size-size/4; j < size; j++) 
        {
            if (arr[i] < arr[j])
                swap(arr[i], arr[j]);
        }
    }
    return NULL;
}

void merge_array(int arg)			// merge all arrays which are coming from 4 threads 
{
    int size = arg;
    
    int* q1 = arr;
    int* q2 = arr + size/4;
    int* q3 = arr + size/2;
    int* q4 = arr + size - size/4;
    
    int* first_half = new int[size/2];
					// copying the first and second quarter araays in first half
    for (int i = 0; i < size/4; i++)
        first_half[i] = q1[i];
 
    for (int i = size/4, j = 0; i < size/2; i++, j++)
        first_half[i] = q2[j];

    for (int i = 0; i < size/2; i++) {
        for (int j = 0; j < size/2; j++) {
            if (first_half[i] < first_half[j]) { // merging first two quarters
                int temp = first_half[i];
                first_half[i] = first_half[j];
                first_half[j] = temp;
            }
        }
    }
    
    int* second_half = new int[size/2]; 

    for (int i = 0; i < size/4; i++)// copying the third and fourth quarter araays in second half
    	second_half[i] = q3[i];
    	
    for (int i = size/4, j = 0; i < size/2; i++, j++)
    	second_half[i] = q4[j];

    for (int i = size/2; i < size; i++) {
        for (int j = size/2; j < size; j++) {
            if (second_half[i] < second_half[j]) {
                int temp = second_half[i];		// merging second two quarters
                second_half[i] = second_half[j];
                second_half[j] = temp;
            }
        }
    }
    // then  merge the first and second halves 
    
    for (int i = 0, j = 0; i < size/2; i++, j++)
        res[i] = first_half[j];

    for (int i = size/2, j = 0; i < size; i++, j++) {
        res[i] = second_half[j];
     }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (res[i] < res[j]) {
                int temp = res[i];
                res[i] = res[j];
                res[j] = temp;
            }
        }
    }
    
    cout << "Array after mergsorting = "; //printing values after mergesorting
    for (int i = 0; i < size; i++)
        cout << res[i] << " ";

    cout << endl;
}

int main() {
	
    int size;
    pthread_t tid[i];
	
    cout << "Enter size of the array: "; //take user input of total number of elements
    cin >> size;

    arr = new int[size]; //allocate the size to array and res arr
    res = new int[size];

    
    for (int i = 0; i < size; i++)
    {
        cout << "Enter value "<<i<<" = ";	// take user input of values in an array to sort
        cin >> arr[i];
    }
	
    pthread_create(&tid1, NULL, sort_array1,  (void*) &size); //creating 4 thread equivalent to 4 cores with the specified attribute(sizeofarray)  
    pthread_create(&tid2, NULL, sort_array2,  (void*) &size);
    pthread_create(&tid3, NULL, sort_array3,  (void*) &size);
    pthread_create(&tid4, NULL, sort_array4,  (void*) &size);

    for (int i = 1; i < 5; i++)
    {
        pthread_join(tid[i], NULL); // joining all 4 threads using pthread_join
    }
    
    cout << "Array before mergesorting = "; //printing values before mergesorting
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";

    cout << endl;
    
	merge_array(size); // calling merge_array function
	
	pthread_exit(NULL); //terminates the calling thread 
}
