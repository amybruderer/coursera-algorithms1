/*
 * mergesort.h
 *
 *  Created on: Feb 8, 2015
 *      Author: amy
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <vector>
#include "utils.h"

/*
 * This function takes two sorted vectors and merges them to create a single
 * sorted vector.
 *
 * @param first sorted vector
 * @param second sorted vector
 * @return merged, sorted vector containing all elements from both sorted
 * vectors
 */
template <typename T>
std::vector<T> merge(const std::vector<T>& left, const std::vector<T>& right)
{
	typename std::vector<T>::const_iterator iterLeft = left.begin();
	typename std::vector<T>::const_iterator iterRight = right.begin();
	std::vector<T> result;

	// While there's still something in either vector, add to resulting vector
	while((iterLeft != left.end()) || (iterRight != right.end()))
	{
		/*
		 *  If the left vector is empty, copy the remaining elements from the
		 *  right vector into the result
		 */
		if(iterLeft == left.end())
		{
			result.insert(result.end(), iterRight, right.end());
			iterRight = right.end();
		}
		/*
		 *  If the right vector is empty, copy the remaining elements from the
		 *  left vector into the result
		 */
		else if(iterRight == right.end())
		{
			result.insert(result.end(), iterLeft, left.end());
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
				result.push_back(*iterLeft);
				++iterLeft;
			}
			else
			{
				result.push_back(*iterRight);
				++iterRight;
			}
		}
	}

	return result;
}

/*
 * This function takes a vector which will be sorted and returned.
 *
 * @param vector of items to sort
 * @return sorted vector containing all elements from the original vector
 */
template<typename T>
std::vector<T> mergesort(const std::vector<T>& items)
{
	typename std::vector<T>::size_type numItems = items.size();

	if(numItems <= 1)
	{
		return items;
	}

	typename std::vector<T>::const_iterator leftBegin = items.begin();
	typename std::vector<T>::const_iterator leftEnd = leftBegin + (numItems/2);
	typename std::vector<T>::const_iterator rightBegin = leftEnd;
	typename std::vector<T>::const_iterator rightEnd = items.end();
	typename std::vector<T> left(leftBegin, leftEnd);
	typename std::vector<T> right(rightBegin, rightEnd);

	return merge(mergesort(left), mergesort(right));
}


#endif /* MERGESORT_H_ */
