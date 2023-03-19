// *********************************************************  
// Program: Group08_num02_huffmancoding_00000003_output.cpp 
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
#include <fstream>
#include <unordered_map>
#include <queue>
#include <string>
#include <chrono>
#include <bitset>
#include <cmath>
#include <iomanip>

using namespace std;

// A Huffman tree node
struct Node {
    char c; 											//characters
    int freq; 											//frequency
    Node *left, *right;
};

// Comparison function to sort the nodes in descending order
// based on their frequency
struct Compare {
	// Compares the frequency of two nodes and returns 'true' if 
	//the frequency of the left node is greater than the frequency of the right node
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Function to build the Huffman tree
Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    // Create a priority queue to store the nodes
    // sorted in descending order based on their frequency [https://en.cppreference.com/w/cpp/container/priority_queue]
    // This priority_queue automatically maintains the elements in a sorted order.
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Iterate over the frequency map and create the nodes
    for (auto pair : freq) {
        Node* node = new Node; 							//creates a new Node object named node
        node->c = pair.first; 							//assigns the character to the 'c' field of the Node object [pair.first refers to the key (i.e., the first element) of the current element]
        node->freq = pair.second; 						// assigns the frequency to the 'freq' field of the Node object. [pair.second refers to the value (i.e., the second element) of the current element]
        node->left = node->right = nullptr; 			//sets the 'left' and 'right' fields of the Node object to 'nullptr', indicating that the node has no children.
        pq.push(node); 									//adds the 'node' object to the priority_queue using the pq.push() function. [Refer: https://cplusplus.com/reference/queue/priority_queue/push/]
    }

    // Build the Huffman tree
    while (pq.size() > 1) {
        // Extract the two nodes with the lowest frequencies       
        Node* left = pq.top(); pq.pop(); 				//pq.pop() removes the element from the 'priority_queue'
        Node* right = pq.top(); pq.pop();

        // Create a new internal node with the sum of the frequencies
        // and the two extracted nodes as children
        Node* internal = new Node; 
        internal->freq = left->freq + right->freq; 		//gabungan antara 2 values
        internal->left = left;
        internal->right = right;
        pq.push(internal);
    }

    // The remaining node in the queue is the root of the Huffman tree
    return pq.top();
}

// Recursive function to assign codes to the tree nodes
void assignCodes(Node* node, string code,
                 unordered_map<char, string>& codes) {
    // If the current node is a leaf node, assign the code
    // and return
    if (!node->left && !node->right) { 					//f both fields are "nullptr",
        codes[node->c] = code;         					//it means that the node has no children and is a leaf node
        return;
    }

    // Recursively call the function on the left and right children
    // with the updated code
    if (node->left) assignCodes(node->left, code + "0", codes);
    if (node->right) assignCodes(node->right, code + "1", codes);
}

void generateOutput(string inputFilename, string outputFilename, int n){
	// Open the input file and output file
    ifstream input(inputFilename);
  	ofstream out(outputFilename);
  	
	// Skip the first line of the input file
	input.ignore(numeric_limits<streamsize>::max(), '\n');
	
    // Read the input file and count the frequency of each character
    unordered_map<char, int> freq; 					//  unordered_map<key, value> name;
    char c;
    int message_length = 0; 						//to calculate the length of the message
    //cout << "Message: ";
    cout << "Output for " << n << " number of words";
    while (input.get(c)) {
    	//cout << c;
        if (c != ' ' && c != '\n') { 				//dont count space as a character
            freq[c]++;
            message_length++;
        }      
    }
    //Display length and size of the original message. -> CBKTG CACGA GCTA
    cout << "\nLength of message: " << message_length << endl;
    cout << "Size of the message: " << message_length * 7; //size of message = length of message * 7 bit

    //build the Huffman tree
    Node* root = buildHuffmanTree(freq);

    // Assign codes to the tree nodes
    unordered_map<char, string> codes;
    assignCodes(root, "", codes);

    // Print the number of unique characters and write into output file
    cout << "\n\nNumber of unique characters: " << freq.size() << endl;
    out << freq.size() << endl;

    // Read the input file again and encode it
    input.clear();
    input.seekg(0, ios::beg);
    
    // Skip the first line of the input file
	input.ignore(numeric_limits<streamsize>::max(), '\n');
	
    string encoded = "";
    while (input.get(c)) {
        // Ignore spaces
        if (c == ' ' || c == '\n') continue;	

        // Encode the character and add it to the encoded string
        encoded += codes[c];
    }
	
	// Print the characters, frequencies, code word, and total bits
    cout << "Character\tFrequency\tCode word\tTotal bit" << endl;
	
	//Loop to get length of code and total size of code for each word
	int total_code_length = 0; 							//sum of length for all code word
	int total_code_size = 0; 							// sum of total bit
	for (auto pair : codes) {
		
	  char character = pair.first; 						//character
	  string code = pair.second;						//code word
	  int code_length = code.length(); 					//length of code word
	  total_code_length += code_length; 				//total for length of code word
	  
	  total_code_size += (freq[pair.first] * code_length); // (freq[pair.first] * code_length) is the total bit for each character
	  
	  //Display to cmd and write to file.txt
	  cout << character << "\t\t"						//Character
	       << freq[pair.first] << "\t\t"				//Frequency
		   << code << "\t\t"							//Code word
		   << (freq[pair.first] * code_length) << endl; //Total bit for each character 
	  out << character << " " 
		  << freq[pair.first] << " " 
		  << code << " " 
		  << (freq[pair.first] * code_length) << endl;
	}
	
	//Display and write
	cout << "----------------------------------------------------------\n";
	cout << freq.size() * 7 << "\t\t" 					//Total size of unique character
		 << message_length << "\t\t" 					//Total of frequency
		 << total_code_length << "\t\t" 				//Total length for of code word
		 << total_code_size << endl;					//Total bit
	cout << "\nTotal size of unique characters (bit): " << freq.size() * 7 << endl;
	cout << "Total frequency: " << message_length << endl;
	cout << "Code length (bit): " << total_code_length << endl;
	cout << "Total size of code (bit): " << total_code_size << endl;
	cout << endl;
	cout << "Huffman's algorithm encodes the message into " << total_code_size << "-bit out of " << message_length * 7 << "-bit" << endl;
	out << total_code_size << "-bit out of " << message_length * 7 << "-bit" << endl;
	//cout << "Encoded message: " << encoded << endl;
	out << encoded << endl;
	cout << "Time Complexity: " <<  floor(freq.size() * log(freq.size())) << "s"; // Time complexity O(nlogn)
	out  <<  floor(freq.size() * log(freq.size())) << "s";	
	cout << "\n----------------------------------------------------------\n";
	
	// close the output file
	out.close();
    // close the output file
	input.close();
}

int main() {

	generateOutput("huffmancoding_00000010_input.txt","huffmancoding_00000010_output.txt", 10);
	generateOutput("huffmancoding_00000050_input.txt","huffmancoding_00000050_output.txt", 50);
	generateOutput("huffmancoding_00000100_input.txt","huffmancoding_00000100_output.txt", 100);
	generateOutput("huffmancoding_00001000_input.txt","huffmancoding_00001000_output.txt", 1000);
	generateOutput("huffmancoding_00010000_input.txt","huffmancoding_00010000_output.txt", 10000);

    return 0;
}

