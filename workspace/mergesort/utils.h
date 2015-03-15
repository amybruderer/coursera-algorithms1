/*
 * utils.h
 *
 *  Created on: Feb 8, 2015
 *      Author: amy
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <vector>

template <typename T>
void printItems(const std::vector<T>& vec)
{
	using namespace std;
	cout << "Vector contents: ";
	for(typename vector<T>::const_iterator itr = vec.begin(); itr != vec.end(); ++itr)
	{
		cout << (*itr) << " ";
	}

	cout << endl;
}



#endif /* UTILS_H_ */
