// Name Abrham Tamiru
// Class (CECS 325-02)
// Project Name (Prog 5 – Sorting contest using threading)
// Due Date (4/06/2023)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <cstdlib> 
#include <thread>
#include <fstream>
#include <string>

using namespace std;

const int MAX_SIZE = 1000000;
const int thread_size = 8;

void bubbleSort(int arr[], int n)
{
    for ( int i =0; i<n ; i++)
    {
        for (int j=i+1; j<n ;j++)
        {
            if (arr[j]<arr[i])
            {
                swap(arr[i],arr[j]);
            }
        }
    }
}


int* merge(int* arr1, int* arr2, int size_1, int size_2) //merge two arrays 
{
    int* merged = new int[size_1 + size_2];
    int i = 0, j = 0, k = 0;
    while (i < size_1 && j < size_2) 
    {
        if (arr1[i] < arr2[j]) 
        {
            merged[k] = arr1[i];
            i++;
        }
        else 
        {
            merged[k] = arr2[j];
            j++;
        }
        k++;
    }

    while (i < size_1) 
    {
        merged[k] = arr1[i];
        k++;
        i++;
    }

    while (j < size_2) 
    {
        merged[k] = arr2[j];
        k++;
        j++;
    }

    return merged;
}
void sort_thread(int *arr_section, int threadNum) 
{
    bubbleSort(arr_section, MAX_SIZE/thread_size);
  
}
int main(int argc, char* argv[])
{

    if (argc > 2 or argc <2) 
    {
        cout<<"It accepts 1 command line arguments "<<endl;
        cout<< " arg 1: input file"<<endl;
        exit(0);
    }

    // the  command line argument
    string input_file = argv[1]; 
    
    ifstream infile(argv[1]);
    if(!infile) // check the input file(numbers.dat) is openable
    {
        cout<<"Unable to open the input file"<<endl;
        exit(0);
    }  
  
    int rand_num;
    int size=0;
    int arr[MAX_SIZE];
    
    while (infile >> rand_num && size<=MAX_SIZE)
    {
        arr[size]=rand_num;
        size++;
    }
    
    int* arr_section[thread_size];
    for(int i=0; i<thread_size; i++)
    {
        arr_section[i]=&arr[i*MAX_SIZE/thread_size];
    }

    thread thread1(sort_thread, arr_section[0],1);
    thread thread2(sort_thread, arr_section[1],2);
    thread thread3(sort_thread, arr_section[2],3);
    thread thread4(sort_thread, arr_section[3],4);
    thread thread5(sort_thread, arr_section[4],5);
    thread thread6(sort_thread, arr_section[5],6);
    thread thread7(sort_thread, arr_section[6],7);
    thread thread8(sort_thread, arr_section[7],8);

    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    thread5.join();
    thread6.join();
    thread7.join();
    thread8.join();

    //merge two threads 
    int *merged1 = merge(arr_section[0], arr_section[1], size / 8 , size / 8); 
    int *merged2 = merge(arr_section[2], arr_section[3], size / 8 , size / 8);
    int *merged3 = merge(arr_section[4], arr_section[5], size / 8 , size / 8);
    int *merged4 = merge(arr_section[6], arr_section[7], size / 8 , size / 8);
    
    // Merge the two threads from the above 
    int* merged_12 = merge(merged1, merged2, size / 4, size / 4);
    int* merged_34 = merge(merged3, merged4, size / 4, size / 4);
    
    int* final_merge = merge(merged_12, merged_34, size / 2, size / 2);

    for (int i=0 ; i<size;i++) 
    {
        cout<<*final_merge++<< "\n";
    }

    infile.close();
    return 0;
}
