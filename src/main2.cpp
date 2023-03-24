/*-----------------------------------------------------------------------------------
File name : main2.cpp
Author(s) : G. Courbat, J. Streckeisen, T. Van Hove
Creation date : 23.03.2022
Description :  This program calculates the execution time of the quick sort and the
               base sort algorithms. Average of 10 run for each algorithm with every
               number of element. Those are 10/100/1'000/10'000/100'000/1'000'000
Compiler : Mingw-w64 g++ 11.2.0
-----------------------------------------------------------------------------------*/
#include <chrono>
#include <iostream>
#include <vector>
#include "SortLib.h"

using namespace std;
using I = vector<unsigned int>::iterator;

const vector<size_t> NB_VALUE = {10,100,1000,10000,100000,1000000};
const string FILENAME = "statistics";
const int SEED = 303, NB_RUN = 10;

/* @brief This function calculate time of given sorting algorithm on a vector
 * @param v vector on which the sort is applied
 * @param function sorting algorithm
 * @return the execution time in miliseconds */
template<typename T ,typename Iterator>
double calculate_time(vector<T> &v, void (*function)(Iterator,Iterator));

/* @brief This function test time on a single algorithme for each number of element
 * @param v input vector
 * @param function sort function
 * @return A vector of duration in miliseconde for each number of element */
template<typename Iterator>
vector<double> test_algorithm(void (*function)(Iterator,Iterator));

int main() {
   vector<vector<double>> time_results;

   auto sort_algorithms = {
      quickSort<I>,
      baseSort<I,1>,
      baseSort<I,2>,
      baseSort<I,4>,
      baseSort<I,8>,
      baseSort<I,16>
   };

   for (auto &sort_algorithm:sort_algorithms) {
      time_results.push_back(test_algorithm(sort_algorithm));
   }
   exportCsv(time_results,FILENAME);

   return EXIT_SUCCESS;
}
template<typename Iterator>
vector<double> test_algorithm(void (*function)(Iterator,Iterator)){
   vector<double> time;
   vector<unsigned int> generated_vector;
   for(size_t i : NB_VALUE){
      generated_vector = generateShuffle<unsigned int>(SEED, (i));
      time.push_back(calculate_time(generated_vector,function));
   }
   return time;
}

template<typename T ,typename Iterator>
double calculate_time(vector<T> &v, void (*function)(Iterator,Iterator)) {
   using std::chrono::high_resolution_clock;
   using std::chrono::duration;

   duration<double, std::milli> time_elapsed{};
   //Create a copy that we can reuse for each run
   vector<T> copy_v = v;

   for (size_t i = 0; i < NB_RUN; ++i) {
      high_resolution_clock::time_point t1 = high_resolution_clock::now();
      function(copy_v.begin(),copy_v.end());
      high_resolution_clock::time_point t2 = high_resolution_clock::now();
      time_elapsed += (t2-t1);
      //Reset the copy
      copy_v = v;
   }
   time_elapsed = time_elapsed / NB_RUN;
   return time_elapsed.count();// miliseconds
}