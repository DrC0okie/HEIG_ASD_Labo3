/*-----------------------------------------------------------------------------------
File name : SortLib.h
Author(s) : G. Courbat, J. Streckeisen, T. Van Hove
Creation date : 23.03.2022
Description : Common library used for this laboratory
Remark(s) :
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#ifndef SORTLIB_H
#define SORTLIB_H

#include <fstream>
#include <string>
#include <vector>

template<typename T>
using vec = std::vector<T>;
template<typename T>
using GenVec2d = std::vector<vec<T>>;
using OpenMod = std::ios::openmode;
using DataSet = GenVec2d<std::string>;

/** @brief Returns a vector<T> of random T elements
 * @tparam T data type
 * @param seed The seed used to generate random numbers
 * @param nElement Number of elements to generate in the vector
 * @return A vector<T> with random T values */
template<typename T >
std::vector<T> generateShuffle(unsigned seed, size_t nElement);

/** @details Exports a 2-dimension vector data in a csv file
 * @tparam T The vector type
 * @param dataSet Data to be exported 1st dim: Quantity of data 2nd dim: the results
 * @param path The path of the csv file */
template<typename T>
void exportCsv(const std::vector<std::vector<T>> &data, const std::string
&fileName, std::ios::openmode mode = std::ios::out);

/** @brief Function that returns a random long long number
 * @param lower Lower bound
 * @param upper Upper Bound
 * @return A long long random number between [lower, upper[ */
long long getRandom(long long lower, long long upper);

/** @brief Partitioning algorithm returning the pivot that delimits the
 * partitioned areas
 * @tparam Iterator Iterator type
 * @param first Upper bound iterator
 * @param last Lower bound iterator
 * @return An iterator pointing to the pivot position */
template<typename Iterator>
Iterator partition(Iterator first, Iterator last);

/** @brief Verifies that the partition function does work properly
 * @tparam Iterator Iterator type
 * @param first Upper bound iterator
 * @param last Lower bound iterator
 * @return true if the partition algorithm is correct, false if not */
template<typename Iterator>
bool checkPartition(Iterator first, Iterator last);

/** @brief quickSort algorithm using semi-recursive call with a random pivot
 * @tparam Iterator Iterator type
 * @param first Upper bound iterator
 * @param last Lower bound iterator */
template<typename Iterator>
void quickSort(Iterator first, Iterator last);

/** @brief Stable sorting algorithm: counts integers with a certain base and sort
 * them
 * @tparam Iterator Type of the Iterator
 * @tparam Fn Type of foncteur/class SomeBits
 * @param first Upper bound iterator
 * @param last Lower bound iterator
 * @param output_first Output iterator containing the results of the sorting.
 * @param index_fn Key function used to find the right counting index of an element
 * @param N the number of counters in the temporary container */
template<typename Iterator, typename Fn>
void countingSort(Iterator first, Iterator last, Iterator outputFirst, Fn
indexFn, size_t n);

/**@brief base sort uses a stable sorting algorithm (counting sort) to sort
 * elements of a certain base and certain selected bits.
 * @tparam Iterator Type of the Iterator
 * @tparam NBITS number of bits in which the base will be represented
 * @param first Upper bound iterator
 * @param last Lower bound iterator
 */
template<typename Iterator, size_t NBITS>
void baseSort(Iterator first, Iterator last);

/** @brief Function used to create a 2dvector<string> where the tested values will
 * be stored to be exported to csv
 * be stored to be exported to csv
 * @tparam T Datatype of the 2dvector
 * @param data The 2dVector
 * @return a 2dvector<string> */
template<typename T>
DataSet createDataset(const std::vector<std::vector<T>> &data);

/** @brief
 * @param REPR
 * @param n
 */
void interpreter(const size_t& REPR, unsigned &n);
#include "SortLibImpl.h"
#endif

