/*
Course: CS315-001
Project: HW2 Pokemon Sorting
Purpose:
Author: Tiffany Clark
Citation: I got the idea to use a struct from //https://www.youtube.com/watch?v=NFvxA-57LLA. Used pseudocode that Dr. Harrison provided
          in the shared OneNote. 
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

struct Pokemon 
{
    double num;
    int stat;

};


//Function that prints the original array of stats
void Print_Original_Arr(int arr[], int size)
{
    cout << "Original Array Given: ";
    for (auto i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Insertion sort for the array of stats
void Insertion_Sort(int arr[], int num, int& Insertion_Count)
{
    int i, key, j;
    for (i = 1; i < num; i++)
    {
        key = arr[i];
        j = i - 1;

        //Move elements of arr that are greater than key
        //to one position ahead of their current position
        while (j >=0  && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
            Insertion_Count++;
        }
        arr[j + 1] = key;
    }
}



//Function that swaps two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
    
}

//Partition function
int partition(int arr[], int low, int high, int& Quicksort_Count)
{
    
    int pivot = arr[high];
    int i = (low -1);

    for (int j = low; j <= high - 1; j++)
    {
        Quicksort_Count++;
        if(arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
            
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);

}
//Quicksort for the array of stats
void Quicksort(int arr[], int low, int high, int& Quicksort_Count)
{
    if(low < high)
    {
        int pi = partition(arr, low, high, Quicksort_Count);
        Quicksort(arr, low, pi - 1, Quicksort_Count);
        Quicksort(arr, pi + 1, high, Quicksort_Count);
    }
    
}

//Merge two arrays 
void merge(int arr[], int const left, int const mid, int const right, int& Mergesort_Count)
{
    auto const Sub_Arr_One = mid - left + 1;
    auto const Sub_Arr_Two = right - mid;

    auto *Left_Arr = new int[Sub_Arr_One];
    auto *Right_Arr = new int[Sub_Arr_Two];

    for(auto i = 0; i < Sub_Arr_One; i++)
    {
        Left_Arr[i] = arr[left + i];
    }
    for(auto j = 0; j < Sub_Arr_Two; j++)
    {
        Right_Arr[j] = arr[mid + 1 + j];
    }

    auto Sub_Arr_One_Index = 0;
    auto Sub_Arr_Two_Index = 0;
    int Merged_Arr_Index = left;

    while(Sub_Arr_One_Index < Sub_Arr_One && Sub_Arr_Two_Index < Sub_Arr_Two)
    {
        Mergesort_Count++;
        if(Left_Arr[Sub_Arr_One_Index] <= Right_Arr[Sub_Arr_Two_Index])
        {
            arr[Merged_Arr_Index] = Left_Arr[Sub_Arr_One_Index];
            Sub_Arr_One_Index++;

        }
        else
        {
            arr[Merged_Arr_Index] = Right_Arr[Sub_Arr_Two_Index];
            Sub_Arr_Two_Index++;
        }
        Merged_Arr_Index++;
    }

    while(Sub_Arr_One_Index < Sub_Arr_One )
    {
        arr[Merged_Arr_Index] = Left_Arr[Sub_Arr_One_Index];
        Sub_Arr_One_Index++;
        Merged_Arr_Index++;
    }

    while(Sub_Arr_Two_Index < Sub_Arr_Two)
    {
        arr[Merged_Arr_Index] = Right_Arr[Sub_Arr_Two_Index];
        Sub_Arr_Two_Index++;
        Merged_Arr_Index++;
    }

    delete[] Left_Arr;
    delete[] Right_Arr;

}

//Mergesort for the array of stats 
void mergeSort(int arr[], int const begin, int const end, int& Mergesort_Count)
{
    if(begin < end)
    {
        auto mid = begin + (end - begin)/2;
        mergeSort(arr, begin, mid, Mergesort_Count);
        mergeSort(arr, mid + 1, end, Mergesort_Count);
        merge(arr, begin, mid, end, Mergesort_Count);
    }
    else
    {
        return;
    }
   
}



//Function that prints the sorted stats array
void Print_Sorted_Array(int arr[], int num)
{
    int i;
    for (i = 0; i < num; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

//Sorts the struct by stats
bool SortByStats(Pokemon &p1, Pokemon &p2)
{
    return p1.stat < p2.stat;
}

//Prints the sorted struct
void print(Pokemon arr[], int size)
{
    for (int i=0; i<size; i++)
    {
        cout << arr[i].num << ' ';
        cout << arr[i].stat << endl;
    }
}



//Driver code
int main()
{
    
    int const SIZE = 100000;

    //Array of the 9 csv files
    string files[9] = {"pokemonRandomLarge.csv", "pokemonRandomMedium.csv", "pokemonRandomSmall.csv", "pokemonReverseSortedLarge.csv", "pokemonReverseSortedMedium.csv", "pokemonReverseSortedSmall.csv", "pokemonSortedLarge.csv","pokemonSortedMedium.csv","pokemonSortedSmall.csv"};
    //Loops through all the datasets and performs the sorting algorithms
    for (int i = 0; i < 8; i++)
    {
        ifstream myfile;
        myfile.open(files[i]);
        cout << "File Name: " << files[i] << endl;
        Pokemon p_arr[SIZE];
        Pokemon temp;
        string line = "";
        getline(myfile, line);
        line = "";
        int index = 0;
        int counter = 0;
        int Mergesort_Count = 0;
        int Insertion_Count = 0;
        int Quicksort_Count = 0;
        vector<int> s;


        while(getline(myfile, line))
        {
            istringstream linestream(line);
            string item;

            getline(linestream, item, ',');
            temp.num = atof(item.c_str());

            getline(linestream, item, ',');
            stringstream ss(item);
            ss >> temp.stat;
            s.push_back(temp.stat);

            p_arr[index] = temp;
            index++;
            counter++;
        }

        cout << "Original Order of Data Given: " << endl;
        for (int i = 0; i < counter; i++)
        {
            cout << "Pokemon Number: " << p_arr[i].num << " Stats: " << p_arr[i].stat << endl;
        }
        cout << endl;

        //Copies the elements of the vector to an array
        int len = counter;
        int arr[len];
        for(int i = 0; i < len; i++)
        {
            arr[i] = s[i];
        }
        Print_Original_Arr(arr, len);
        cout << "Sorted Array Using Insertion Sort Method: ";
        Insertion_Sort(arr, len, Insertion_Count);
        Print_Sorted_Array(arr, len);
        cout << "Number of comparisons made: " << Insertion_Count << endl;
        cout << "Sorted Array Using Quicksort Method: ";
        Quicksort(arr, 0, len - 1, Quicksort_Count);
        Print_Sorted_Array(arr, len);
        cout << "Number of comparisons made: " << Quicksort_Count << endl;
        cout << "Sorted Array Using Mergesort Method: ";
        mergeSort(arr, 0, len - 1, Mergesort_Count);
        Print_Sorted_Array(arr, len);
        cout << "Number of comparisons made: " << Mergesort_Count << endl;
        cout << endl << endl;
        cout << "Sorted Struct: " << endl;
        sort(p_arr, p_arr+len, SortByStats);
        print(p_arr, len);
        cout << endl;



    }
    
    
   

    return 0;


}
