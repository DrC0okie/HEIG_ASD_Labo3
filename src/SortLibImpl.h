/*-----------------------------------------------------------------------------------
File name : SortLibImpl.h
Author(s) : G. Courbat, J. Streckeisen, T. Van Hove
Creation date : 23.03.2022
Description : Implementation of the functions declared in SortLib.h
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#ifndef SORTLIBIMPL_H
#define SORTLIBIMPL_H

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>
#include <type_traits>
#include <vector>
#include "some_bits.h"

template<typename T>
vec<T> generateShuffle(const unsigned seed, size_t nElement) {
   srand(seed);
   vec<T> v(nElement);
   iota(v.begin(), v.end(), 1);
   shuffle(v.begin(), v.end(), std::default_random_engine(seed));
   return v;
}

long long getRandom(long long lower, long long upper) {
   static std::random_device device;
   std::mt19937 generator(device());

   // The distribution must be [lower,upper[ for not generating the upper value
   std::uniform_int_distribution<long long> distribution(lower, upper - 1);
   return distribution(generator);
}

template<typename Iterator>
Iterator partition(Iterator first, Iterator last) {
   Iterator i = std::prev(first), j = std::prev(last);
   do {
      do {
         ++i;
      } while (*i < *std::prev(last));

      do {
         --j;
      } while (j > first && *std::prev(last) < *j);

      if (i >= j)
         break;
      std::swap(*i, *j);
   } while (true);
   std::swap(*i, *std::prev(last));
   return i;
}

template<typename Iterator>
bool checkPartition(Iterator first, Iterator last) {
   Iterator it = partition(first, last);

   //Parsing first -> pivot
   for (auto i = first; i != it; ++i)
      if (*i > *it)
         return false;

   //Parsing pivot -> last - 1
   for (auto i = std::prev(last); i != it; --i)
      if (*i < *it)
         return false;

   return true;
}

template<typename Iterator>
void quickSort(Iterator first, Iterator last) {
   while (first < last) {
      //Random pivot selection in the range [first, last[
      Iterator pivot = first + getRandom(0, std::distance(first, last));
      std::swap(*std::prev(last), *pivot);

      //Pivot index of the partitioned vector
      Iterator i = partition(first, last);

      if (std::distance(first, i) < std::distance(i, last)) {
         quickSort(first, i);
         first = std::next(i);
      } else {
         quickSort(std::next(i), last);
         last = i;
      }
   }
}

template<typename Iterator, typename Fn>
void countingSort(Iterator first, Iterator last, Iterator outputFirst, Fn indexFn,
                  size_t n) {
   //counter array
   std::vector<uint64_t> tmp(n);
   for (auto k = first; k != last; ++k) {
      tmp[indexFn(*k)]++;
   }
   //transformed in an index array
   size_t idx = 0;
   for (auto &k: tmp) {
      size_t temp = k;
      k = idx;
      idx += temp;
   }
   //we move in the output array the elements according to their index
   for (auto k = first; k != last; ++k) {
      *(outputFirst + (long long int) tmp[indexFn(*k)]++) = *k;
   }
}

void interpreter(const size_t &REPR, unsigned &n) {
   //gives the right n for a NBITS
   switch (REPR) {
      case 1:
         n = 2;
         break;
      case 2:
         n = 4;
         break;
      case 4:
         n = 16;
         break;
      case 8:
         n = 256;
         break;
      case 16:
         n = 65536;
         break;
      default:
         throw std::invalid_argument("Wrong base. You must select one of "
                                     "these: 1, 2, 4, 8, 16");
   }
}

template<typename Iterator, size_t NBITS>
void baseSort(Iterator first, Iterator last) {
   using T = typename Iterator::value_type;
   static_assert(std::is_unsigned<T>::value);

   if (NBITS >= std::numeric_limits<T>::digits) {
      throw std::invalid_argument("Number of bits of the selected type are too "
                                  "short for the selected base");
   }

   unsigned n = 0;
   const size_t REPR = NBITS;
   interpreter(REPR, n);

   //a second vector is needed
   std::vector<T> tmp(T(distance(first, last)));

   //flip-flop on iterators instead of copying
   //works only on even base which is the case in this lab
   for (size_t i = 0; i < std::numeric_limits<T>::digits / NBITS; ++i) {
      if (i % 2 == 0) {
         countingSort(first, last, tmp.begin(),
                      SomeBits<T>(NBITS, i), n);
      } else {
         countingSort(tmp.begin(), tmp.end(), first,
                      SomeBits<T>(NBITS, i), n);
      }
   }
}

template<typename T>
void exportCsv(const GenVec2d<T> &data, const std::string
&fileName, OpenMod mode) {
   DataSet dataSet = createDataset(data);
   std::fstream file;
   file.open(fileName + ".csv", mode);

   if (!file.good()) {
      file.close();
      throw std::runtime_error("Cannot open/create the file " + fileName);
   }

   if (mode != std::ios::app)
      file << "sep=," << "\n";
   else file << "\n";

   for (const auto &i: dataSet) {
      for (const auto &j: i) {
         file << "," << j;
      }
      file << std::endl;
   }
   file.close();
}

template<typename T>
DataSet createDataset(const GenVec2d<T> &data) {
   DataSet result(data.size(), std::vector<std::string>(data.at(0).size(), ""));
   for (size_t i = 0; i < data.size(); ++i)
      for (size_t j = 0; j < data.at(0).size(); ++j) {
         std::stringstream ss;
         ss << data.at(i).at(j);
         result.at(i).at(j) = ss.str();
      }
   return result;
}
#endif