/*
 * quicksort.h
 *
 *  Created on: Feb 15, 2015
 *      Author: amy
 */

#ifndef QUICKSORT_H_
#define QUICKSORT_H_

#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <random>
#include <functional>
#include <cmath>

#include "../../mergesort/utils.h"

/*
 * This function always returns the first parameter as the pivot point for
 * partitioning the vector.
 *
 * @param beginning iterator in vector of items to consider for pivot
 * @param ending iterator in vector of items to consider for pivot
 * @return pivot point around which vector will be partitioned, always first
 */
template<class ForwardIt>
ForwardIt choosepivotfirst(ForwardIt first, ForwardIt last) {
    return first;
}

/*
 * This function always returns the last parameter as the pivot point for
 * partitioning the vector.
 *
 * @param beginning iterator in vector of items to consider for pivot
 * @param ending iterator in vector of items to consider for pivot
 * @return pivot point around which vector will be partitioned, always last
 */
template<class ForwardIt>
ForwardIt choosepivotlast(ForwardIt first, ForwardIt last) {
    return last-1;
}

/*
 * This function uses the "median-of-three" rule to determine the pivot point
 * for partitioning the vector.
 *
 * In more detail, the pivot is chosen as follows:
 * Consider the first, middle, and final elements of the given array. (If the
 * array has odd length it should be clear what the "middle" element is; for
 * an array with even length 2k, use the kth element as the "middle" element.
 * So for the array 4 5 6 7, the "middle" element is the second one ---- 5 and
 * not 6!) Identify which of these three elements is the median (i.e., the one
 * whose value is in between the other two), and use this as your pivot.
 *
 * @param beginning iterator in vector of items to consider for pivot
 * @param ending iterator in vector of items to consider for pivot
 * @return pivot point around which vector will be partitioned, the middle of
 * the sorted three elements
 */
template<class ForwardIt>
ForwardIt choosepivotmedianofthree(ForwardIt first, ForwardIt last) {
    auto numitems = std::distance(first, last);
    auto comp = [](ForwardIt a, ForwardIt b){ return (*a) < (*b); };
    std::set<ForwardIt,decltype(comp)> threeelements(comp);
    threeelements.insert(first);
    threeelements.insert(first + ceil(numitems/2.0) - 1);
    threeelements.insert(last - 1);

    return *((threeelements.size() == 1) ? threeelements.begin() : ++threeelements.begin());
}

/*
 * This function randomly determines a pivot point for partitioning the vector.
 *
 * @param beginning iterator in vector of items to consider for pivot
 * @param ending iterator in vector of items to consider for pivot
 * @return pivot point around which vector will be partitioned
 */
template<class ForwardIt>
ForwardIt choosepivotrandom(ForwardIt first, ForwardIt last) {
    auto numitems = std::distance(first, last);
    ForwardIt pivot;

    if (numitems < 4) {
        pivot = first + (numitems / 2);
    } else {
        // Lower bound of random pivot point, above 25 percent
        auto lowerbound = ((25 * numitems) / 100);

        // Upper bound of random pivot point, 75 percent
        auto upperbound = ((75 * numitems) / 100 - 1);

        // Seed with a real random value, if available
        std::random_device randomdevice;

        // Choose a random pivot between upper and lower bounds
        std::mt19937_64 randomengine(randomdevice());
        std::uniform_int_distribution<> uniformdist(lowerbound, upperbound);

        auto pick = uniformdist(randomdevice);

        pivot = first + pick;
    }

    return pivot;
}

/*
 * This function partitions a vector, as given by the first and last iterators,
 * into three sections: items less than the pivot element, the pivot element,
 * and items greater than the pivot element.
 *
 * @param beginning iterator in vector of items to partition
 * @param ending iterator in vector of items to partition
 * @param pivot iterator around which the other items will be partitioned
 */
template<class ForwardIt>
void partition(ForwardIt first, ForwardIt last, ForwardIt& pivot) {
    // Make sure pivot is at the beginning of items to be partitioned
    if (pivot != first) {
        std::iter_swap(first, pivot);
        pivot = first;
    }

    // Keep track of the leftmost element larger than the pivot
    ForwardIt i = pivot + 1;

    // Compare each remaining element in the vector to the pivot point
    for (ForwardIt j = i; j < last; ++j) {
        /*
         * If the current element is less than the pivot element, swap the
         * current element with the leftmost element larger than the pivot
         */
        if ((*j) < (*pivot)) {
            std::iter_swap(j, i);
            ++i;
        }
    }

    /*
     * Put pivot into correct position, swapping with rightmost element less
     * than pivot
     */
    std::iter_swap(pivot, i - 1);
    pivot = i - 1;
}

/*
 * This function takes beginning and ending points of a vector which will be
 * sorted in place.
 *
 * @param beginning iterator in vector of items to sort
 * @param ending iterator in vector of items to sort
 * @return number of comparisons used during sort
 */
template<class ForwardIt>
size_t quicksort(ForwardIt first, ForwardIt last, ForwardIt (*choosepivot)(ForwardIt first, ForwardIt last)) {
    // No work to be done if there are less than two items
    if (first == last) {
        return 0;
    }

    // Chose pivot.
    ForwardIt pivot = choosepivot(first, last);

    // Partition vector around pivot
    partition(first, last, pivot);

    // Repeat for first half
    auto numcompareleft = quicksort(first, pivot, choosepivot) + std::distance(first, pivot);

    // Repeat for second half
    auto numcompareright = quicksort(pivot + 1, last, choosepivot) + std::distance(pivot + 1, last);

    return numcompareleft + numcompareright;
}

#endif /* QUICKSORT_H_ */
