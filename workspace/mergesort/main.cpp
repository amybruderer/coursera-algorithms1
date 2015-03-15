/*
 * main.cpp
 *
 *  Created on: Feb 8, 2015
 *      Author: amy
 */


#include <iostream>
#include <vector>

#include "mergesort.h"
#include "utils.h"

using namespace std;

int main(int argc, char** argv)
{
	vector<int> items;

	items.push_back(4);
	items.push_back(20);
	items.push_back(1);
	items.push_back(5);
	items.push_back(3);
	items.push_back(12);

	cout << "Unsorted items: ";

	printItems(items);

	vector<int> sortedItems = mergesort(items);

	cout << endl << "Sorted items: ";

	printItems(sortedItems);

	cout << endl;

	return 0;
}

