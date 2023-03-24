/*-----------------------------------------------------------------------------------
File name : main.cpp
Author(s) : G. Courbat, J. Streckeisen, T. Van Hove
Creation date : 23.03.2022
Description :  This program is testing the base sort and the quick sort algorithms
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#include <cstdint>
#include <iostream>
#include <vector>
#include "SortLib.h"

using namespace std;

int main() {

   cout << "Test Partition... ";
   vector<unsigned> v = generateShuffle<unsigned>(543210, 1'000'000);
   partition(v.begin(), v.end());
   if (checkPartition(v.begin(), v.end()))
      cout << "Partition check is a success" << endl;
   else
      cout << "Partition check failed" << endl;

   cout << "Test QuickSort... ";
   vector<unsigned> w = generateShuffle<unsigned>(543210, 1'000'000);
   quickSort<vector<unsigned>::iterator>(w.begin(), w.end());
   if (is_sorted(w.begin(), w.end()))
      cout << "Sorting is a success" << endl;
   else
      cout << "Sorting has failed" << endl;

   /*------------------TEST BASE SORT---------------------------------------------*/

   cout << "Base sort:" << endl;
   //generating
   cout << "Generating 5 test vectors..." << endl;
   vec<uint8_t> test1 = generateShuffle<uint8_t>(12, 255);
   vec<uint16_t> test2 = generateShuffle<uint16_t>(123, 10000);
   vec<uint32_t> test3 = generateShuffle<uint32_t>(666, 1000000);
   vec<uint64_t> test4 = generateShuffle<uint64_t>(1337, 1000000);
   vec<uint64_t> test5 = generateShuffle<uint64_t>(777, 10000000);

   //sorting
   cout << "Base sorting the 5 test vectors... " << endl;
   baseSort<vector<uint8_t>::iterator, 1>(test1.begin(), test1.end());
   baseSort<vector<uint16_t>::iterator, 2>(test2.begin(), test2.end());
   baseSort<vector<uint32_t>::iterator, 4>(test3.begin(), test3.end());
   baseSort<vector<uint64_t>::iterator, 8>(test4.begin(), test4.end());
   baseSort<vector<uint64_t>::iterator, 16>(test5.begin(), test5.end());

   //testing
   cout << boolalpha << "Is test1 sorted ? : "
        << is_sorted(test1.begin(), test1.end()) << endl;
   cout << "Is test2 sorted ? : " << is_sorted(test2.begin(), test2.end())
        << endl;
   cout << "Is test3 sorted ? : " << is_sorted(test3.begin(), test3.end())
        << endl;
   cout << "Is test4 sorted ? : " << is_sorted(test4.begin(), test4.end())
        << endl;
   cout << "Is test5 sorted ? : " << is_sorted(test5.begin(), test5.end())
        << endl;

   return EXIT_SUCCESS;
}