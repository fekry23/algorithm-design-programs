// *********************************************************  
// Program: Group08_num04_huffmancoding_input_files.cpp 
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

// Generate a random word with a length between 1 and 10 characters
string generateWord() {
  const string alphabet = "abcdefghijklmnopqrstuvwxyz";
  string word;
  int length = rand() % 10 + 1; //length of characters between 1 and 10 characters
  for (int i = 0; i < length; i++) {
    word += alphabet[rand() % 26]; //place random characters inside string variable named "word"
  }
  return word;
}

// Generate a set of n random words and write them to a file
void generateRandInputFile(string filename, int n) {
  
  // open the output file for writing
  ofstream out(filename);
  if (!out.is_open()) { //error handling, if file unable to open, we display an error and terminate the program
    cerr << "Error: Unable to open file for writing: " << filename << endl;
    return;
  }

  // write the number of words to the file. Ex: 10, 50, 100, 1000, and 10000
  out << n << endl;

  // generate n random words and write them to the file
  for (int i = 0; i < n; i++) {
    out << generateWord() << endl;
  }

  // close the output file
  out.close();
  
  //Display success result
  cout << "Successfully generated random " << n << " number of words" << endl;
}

int main() {
  // seed the random number generator with the leader student ID
  srand(1191201485);

  // generate input files for 10, 50, 100, 1000, and 10000 words
  generateRandInputFile("huffmancoding_00000010_input.txt", 10);
  generateRandInputFile("huffmancoding_00000050_input.txt", 50);
  generateRandInputFile("huffmancoding_00000100_input.txt", 100);
  generateRandInputFile("huffmancoding_00001000_input.txt", 1000);
  generateRandInputFile("huffmancoding_00010000_input.txt", 10000);

  return 0;
}

