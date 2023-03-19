// *********************************************************
// Program: Group08_num06_primwithpq.cpp
// Course: TCP2101 ALGORITHM DESIGN & ANALYSIS
// Class: TC1V
// Trimester: 2110
// Member_1: 1191201486 | Engku Ammar Muzamil Bin Engku Musa | 1191201486@student.mmu.edu.my | 010-9273985
// Member_2: 1191201228 | Muhammad Amir Naqiuddin Bin Salleh | 1191201228@student.mmu.edu.my | 013-3607188
// Member_3: 1191201485 | Muhammad Fekry Bin Saharudin | 1191201485@student.mmu.edu.m | 019-2717757
// Member_4: 1191201736 | Syed Muhammad Yusri Bin Syed Abd Rahman | 1191201736@student.mmu.edu.my | 019-2930929
// *********************************************************
// Task Distribution
// Member_1:  - Question 1 - Question 5
// Member_2:  - Question 2 - Question 3 - Question 4
// Member_3:  - Question 2 - Question 7 - Documentation
// Member_4:  - Question 6 - Video edit presentation
// *********************************************************

#include <fstream>         //function to read files
#include <iostream>        //function to cin & cout
#include <vector>          //Constructs a container with as many elements as the range [first,last)
#include <queue>           //operates in a first in first out
#include <utility>         //include many other libraries
#include <chrono>          //track time

using namespace std;

const int INF = 1e3;       //one times ten to the 3rd power = 1000 max int
int n;
vector<vector<pair<int, int>>> adj;         //Vector - array
vector<bool> inMST;
vector<int> dist, parent;

void read_adjacency_matrix(ifstream &input)    //ifstream file input stream
{
    input >> n;                                //input shifts to int n vector
    adj.resize(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int w;
            input >> w;
            if (w != 0)
            {
                adj[i].emplace_back(j, w);
            }
        }
    }
}


void prim_with_pq(ofstream &out)          //ofstream file output stream
{
    inMST.assign(n, false);           //To keep track of vertices included in MST
    dist.assign(n, INF);              //Create a vector for keys and initialize all keys as infinite (INF)
    parent.resize(n);

    dist[0] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, 0);
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if (inMST[u])
            continue;
        inMST[u] = true;
        for (auto [v, w] : adj[u])
        {
            if (!inMST[v] && w < dist[v])
            {
                dist[v] = w;
                parent[v] = u;
                pq.emplace(dist[v], v);
            }
        }
    }

    // write output to file
    out << "Prim's algorithm with priority queue:\n";
    for (int i = 1; i < n; i++)
    {
        out << parent[i] << " - " << i << ": " << dist[i] << '\n';
    }
}

void generate_output_files()
{

    vector<string> input_files = {
        "primwithoutpq_primwithpq_am_00000010_input.txt",
        "primwithoutpq_primwithpq_am_00000030_input.txt",
        "primwithoutpq_primwithpq_am_00000050_input.txt",
        "primwithoutpq_primwithpq_am_00000100_input.txt",
        "primwithoutpq_primwithpq_am_00001000_input.txt"};

    for (const string &input_file : input_files)
    {
        ifstream in(input_file);
        string output_file = input_file;
        output_file.replace(output_file.find("primwithoutpq_"), 14, "");
        output_file.replace(output_file.find("input"), 5, "output");
        ofstream out(output_file);
        read_adjacency_matrix(in);

        auto start_time = chrono::system_clock::now();
        prim_with_pq(out);
        auto end_time = chrono::system_clock::now();
        chrono::duration<double> time_with_pq = end_time - start_time;

        out << '\n';
        out << "Duration by Prim's algorithm with pq: " << time_with_pq.count() << "s\n";
    }
}

int main()
{
    generate_output_files();
    return 0;
}
