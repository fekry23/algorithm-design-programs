// *********************************************************  
// Program: Group08_num03_primwithoutpq_primwithpq_am_input_files.cpp  
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS 
// Class: TC1V  
// Trimester: 2210
// Member_1: 1191201228 | Muhammad Amir Naqiuddin Bin Salleh | 1191201228@student.mmu.edu.my | 013-3607188
// Member_2: 1191201485 | Muhammad Fekry Bin Saharudin | 1191201485@student.mmu.edu.my | 019-2717757
// Member_3: 1191201486 | Engku Ammar Muzamil Bin Engku Musa | 1191201486@student.mmu.edu.my | 010-9273985
// Member_4: 1191201736 | Syed Muhammad Yusri Bin Syed Abd Rahman | 1191201736@student.mmu.edu.my | 019-2930929 
// *********************************************************
// Task Distribution
// Member_1:  - Question 1 - Question 5
// Member_2:  - Question 2 - Question 3 - Question 4
// Member_3:  - Question 2 - Question 7 - Documentation
// Member_4:  - Question 6 - Video edit presentation
// *********************************************************

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

// Generate a set of n random words and write them to a file
void generateRandInputFile(string filename, int n) {
  
  // open the output file for writing
  ofstream out(filename);
  if (!out.is_open()) { //error handling, if file unable to open, we display an error and terminate the program
    cerr << "Error: Unable to open file for writing: " << filename << endl;
    return;
  }

  // write the number of vertices to the file. Ex: 10, 30, 50, 100, 1000
  out << n << endl;
  
  // write the adjacency matrix to the file
  for (int i = 0; i < n; i++) { //row
    for (int j = 0; j < n; j++) { //column

      int weight = rand() % 100 + 1; // generates a random integer in the range [0, 99] and then adds 1, resulting in a random integer in the range [1, 100].
      out << weight << " ";
    }
    out << endl;
  }

  // close the output file
  out.close();
  
  //Display success result
  cout << "Successfully generated random " << n << " number of vertices" << endl;
}

int main() {
  // seed the random number generator with the leader student ID
  srand(1191201485);

  // generate input files for 10, 30, 50, 100, and 1000 vertices
  generateRandInputFile("primwithoutpq_primwithpq_am_00000010_input.txt", 10);
  generateRandInputFile("primwithoutpq_primwithpq_am_00000030_input.txt", 30);
  generateRandInputFile("primwithoutpq_primwithpq_am_00000050_input.txt", 50);
  generateRandInputFile("primwithoutpq_primwithpq_am_00000100_input.txt", 100);
  generateRandInputFile("primwithoutpq_primwithpq_am_00001000_input.txt", 1000);

  return 0;
}

