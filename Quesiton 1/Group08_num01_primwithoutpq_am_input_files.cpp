// *********************************************************
// Program: Group08_num01_primwithoutpq_am_input_files.cpp
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
#include <chrono>
#include <fstream>
#include <string>
#include <vector>
#include <climits> // for INT_MAX
using namespace std;
const int INF = INT_MAX;
const int n=6; // n number of vertices
//vector<vector<Type>> name(num_rows, vector<Type>(num_cols, initial_value)); 2D array
vector < vector < int >> graph(n, vector < int > (n, 0));
auto start = chrono::system_clock::now(); // take start time

void primMSTwoPQ(){
    int edge;  // number of edge
    int x,y;  // row and col
    int visit[n]; // create an array to check visited vertex
    int totalWeight = 0; // initialize variable total weight to 0

    // open output file
    ofstream output("primwithoutpq_am_0000006_output.txt");

    //show and write in file
    cout<<"Number of Vertices: "<<n<< endl;
    output<<n<< endl;
    cout<<"Vertex indexes and Names: "<< endl;
    for (int i =0;i < n; ++i)  //index and name
    {
        cout<<i<<" "<<char('A'+i)<< endl;
        output<<i<<" "<<char('A'+i)<< endl;
    }

    for(int i = 0; i < n; i++){
        visit[i] = false; //initialise the visit array to false
    }

    // set variable
    edge= 0;
    visit[0] = true; // mark the vertex 0 as visited

    cout <<"Edges and Weight:"<< endl;
    // print for edge and weight
    while (edge < n - 1) {

    int min = INF;
    x = 0; //row
    y = 0; // col

    /*to find the minimum weight edge that connects a visited vertex
    to a non-visited vertex in the graph. */
    for (int i = 0; i < n; i++) {
        if (visit[i]) {   //checks if the vertex at index i has been visited.
            for (int j = 0; j < n; j++) {
                if (!visit[j] && graph[i][j]) { //vertices not been visited (visit[j] is false) and have an edge connecting them to the visited vertex
                    if (min >= graph[i][j]){
                        min = graph[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }
    }

    cout <<char('A' + x)<<"-"<<char('A' + y)<<" "<<graph[x][y]<< endl;
    output <<char('A' + x)<<" "<<char('A' + y)<<" "<<graph[x][y]<< endl;
    visit[y] = true;
    edge++;
    totalWeight += graph[x][y];
  }

    auto end = chrono::system_clock::now(); // take end time.
    chrono::duration<double> duration = end - start; // calculate duration.
    cout <<"Total Weight="<<totalWeight<< endl;
    output<<totalWeight<< endl; // total weight
    cout<<"Duration: "<<duration.count()<< "s" << endl;
    output<<duration.count()<<"s"<< endl; // total time taken to run
}

int main(){
    // read input file
    ifstream input("primwithoutpq_am_0000006_input.txt");

    // number of vertices
    int n;
    input >> n;

    // vertex names
    for (int i = 0; i < n; i++) {
        int index;
        char name;
        input>> index >> name;
    }

    // read in the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            string weight;
            input >> weight;
            if (weight == "i") {
                graph[i][j] = INF;  //graph[0][0] = inf
            } else {
                graph[i][j] = stoi(weight);  //int to string| weights[0][1] = 2; weights[0][2]=8
            }
        }
    }

    primMSTwoPQ(); //fx call

    return 0;
 }
