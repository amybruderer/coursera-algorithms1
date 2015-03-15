/*
 * main.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: amy
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "quicksort.h"
#include "../../mergesort/utils.h"

using namespace std;

vector<size_t> GetItemsFromFile(const char * filename);

int main(int argc, char * argv[]) {
    string datafile("/home/amy/Development/coursera/algorithms1/workspace/quicksort/data/QuickSort.txt");
    string outputpath("/home/amy/Development/coursera/algorithms1/workspace/quicksort/output/");
    if(argc == 2) {
        datafile = argv[1];
    }
/*
    {
        vector<int> items { 3, 8, 2, 5, 1, 4, 7, 6 };

        cout << "Unsorted items: ";

        printItems(items);
    }

    {
        vector<int> items { 3, 8, 2, 5, 1, 4, 7, 6 };

        auto numcomparedfirst = quicksort(items.begin(), items.end(),
                choosepivotfirst);

        cout << endl << "Using choosepivotfirst" << endl
                << "Number of comparisons: " << numcomparedfirst << endl
                << "Sorted items: ";

        printItems(items);
    }

    {
        vector<int> items { 3, 8, 2, 5, 1, 4, 7, 6 };

        auto numcomparedlast = quicksort(items.begin(), items.end(),
                choosepivotlast);

        cout << endl << "Using choosepivotlast" << endl
                << "Number of comparisons: " << numcomparedlast << endl
                << "Sorted items: ";

        printItems(items);
    }

    {
        vector<int> items { 8, 2, 1, 9, 5, 7, 4, 3 };

        auto numcomparedmedianofthree = quicksort(items.begin(), items.end(),
                choosepivotmedianofthree);

        cout << endl << "Using choosepivotmedianofthree" << endl
                << "Number of comparisons: " << numcomparedmedianofthree << endl
                << "Sorted items: ";

        printItems(items);
    }

    {
        vector<int> items { 3, 8, 2, 5, 1, 4, 7, 6 };

        auto numcomparedrandom = quicksort(items.begin(), items.end(),
                choosepivotrandom);

        cout << endl << "Using choosepivotrandom" << endl
                << "Number of comparisons: " << numcomparedrandom << endl
                << "Sorted items: ";

        printItems(items);
    }

    cout << endl;

*/
    {
        vector<size_t> items = GetItemsFromFile(datafile.c_str());

        auto numcomparedfirst = quicksort(items.begin(), items.end(),
                choosepivotfirst);

        cout << endl << "Using choosepivotfirst on datafile" << endl
                << "Number of comparisons: " << numcomparedfirst << endl;

        fstream outputfile(outputpath + "QuickSortFirst.txt", ios_base::out);
        for(typename vector<size_t>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
        {
            outputfile << (*itr) << endl;
        }
    }

    {
        vector<size_t> items = GetItemsFromFile(datafile.c_str());

        auto numcomparedlast = quicksort(items.begin(), items.end(),
                choosepivotlast);

        cout << endl << "Using choosepivotlast on datafile" << endl
                << "Number of comparisons: " << numcomparedlast << endl;

        fstream outputfile(outputpath + "QuickSortLast.txt", ios_base::out);
        for(typename vector<size_t>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
        {
            outputfile << (*itr) << endl;
        }
    }

    {
        vector<size_t> items = GetItemsFromFile(datafile.c_str());

        auto numcomparedmedianofthree = quicksort(items.begin(), items.end(),
                choosepivotmedianofthree);

        cout << endl << "Using choosepivotmedianofthree on datafile" << endl
                << "Number of comparisons: " << numcomparedmedianofthree << endl;

        fstream outputfile(outputpath + "QuickSortMedianOfThree.txt", ios_base::out);
        for(typename vector<size_t>::const_iterator itr = items.begin(); itr != items.end(); ++itr)
        {
            outputfile << (*itr) << endl;
        }
    }

    return 0;
}

vector<size_t> GetItemsFromFile(const char * filename) {
    vector<size_t> items;

    fstream datafile(filename, ios_base::in);
    size_t num;
    while(datafile >> num)
    {
        items.push_back(num);
    }

    return items;
}
