/*
 * main.cpp
 *
 *  Created on: Feb 8, 2015
 *      Author: amy
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

#include "../mergesort/utils.h"

using namespace std;

/*
 * Forward declaration for functions used to count inversions in an array
 */
pair<size_t, vector<size_t> > countinversions(const vector<size_t>& items);
pair<size_t, vector<size_t> > countsplitinversions(const vector<size_t>& left, const vector<size_t>& right);

int main(int argc, char * argv[])
{
	for(int i = 1; i < argc; ++i)
	{
		vector<size_t> items;

		fstream datafile(argv[i], ios_base::in);
		size_t num;
		while(datafile >> num)
		{
			items.push_back(num);
		}

/*
		cout << "Input: ";
		printItems(items);
*/

		cout << "Inversions in " << argv[i] << " : " << countinversions(items).first << endl;
	}

	return 0;
}

pair<size_t, vector<size_t> >  countinversions(const vector<size_t>& items)
{
	if(items.size() <= 1)
	{
		return pair<size_t, vector<size_t> >(0, items);
	}

	std::vector<size_t>::const_iterator leftBegin = items.begin();
	std::vector<size_t>::const_iterator leftEnd = leftBegin + (items.size()/2);
	std::vector<size_t>::const_iterator rightBegin = leftEnd;
	std::vector<size_t>::const_iterator rightEnd = items.end();
	std::vector<size_t> left(leftBegin, leftEnd);
	std::vector<size_t> right(rightBegin, rightEnd);


	pair<size_t, vector<size_t> > leftSorted(countinversions(left));
	pair<size_t, vector<size_t> > rightSorted(countinversions(right));
	pair<size_t, vector<size_t> > itemsSorted(countsplitinversions(leftSorted.second, rightSorted.second));

/*
	cout << "left" << endl;
	cout << "    presorted: ";
	printItems(left);
	cout << "    postsorted: ";
	printItems(leftSorted.second);
	cout << "    inversions: " << leftSorted.first << endl;

	cout << "right" << endl;
	cout << "    presorted: ";
	printItems(right);
	cout << "    postsorted: ";
	printItems(rightSorted.second);
	cout << "    inversions: " << rightSorted.first << endl;

	cout << "split" << endl;
	cout << "    postsorted: ";
	printItems(itemsSorted.second);
	cout << "    inversions: " << itemsSorted.first << endl;
*/

	return pair<size_t, vector<size_t> >(leftSorted.first + rightSorted.first + itemsSorted.first, itemsSorted.second);
}

pair<size_t, vector<size_t> > countsplitinversions(const vector<size_t>& left, const vector<size_t>& right)
{
	vector<size_t>::const_iterator iterLeft = left.begin();
	vector<size_t>::const_iterator iterRight = right.begin();
	pair<size_t, vector<size_t> > result;
	result.first = 0;

	// While there's still something in either vector, add to resulting vector
	while((iterLeft != left.end()) || (iterRight != right.end()))
	{
		/*
		 *  If the left vector is empty, copy the remaining elements from the
		 *  right vector into the result
		 */
		if(iterLeft == left.end())
		{
			result.second.insert(result.second.end(), iterRight, right.end());
			iterRight = right.end();
		}
		/*
		 *  If the right vector is empty, copy the remaining elements from the
		 *  left vector into the result
		 */
		else if(iterRight == right.end())
		{
			result.second.insert(result.second.end(), iterLeft, left.end());
			iterLeft = left.end();
		}
		/*
		 * Compare the current left and right elements and copy the smaller
		 * of the two into the result
		 */
		else
		{
			if((*iterLeft) < (*iterRight))
			{
				result.second.push_back(*iterLeft);
				++iterLeft;
			}
			else
			{
				result.first += left.end() - iterLeft;
				result.second.push_back(*iterRight);
				++iterRight;
			}
		}
	}

	return result;
}
