#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    printf("app start\n");
    ifstream input_file(argv[1]);
    vector<pair<long long, long long>> fresh_set;
    bool fin = false;
    while (!fin) {
        string line;
        getline(input_file,line);
        // printf("\n\"%s\"",line.c_str());
        if (line  == "") {
            fin = true;
        } else {
            int dash_index = 0;
            while (line[dash_index] != '-') {
                dash_index++;
            }
            long long start = stoll(line.substr(0,dash_index));
            long long end = stoll(line.substr(dash_index+1,line.size()-dash_index-1));
            fresh_set.push_back(pair(start,end));
            // printf("\nInput Range:%lld - %lld", start, end);
        }
    }
    
    printf("\ncheking");
    //check if in set
    long long queried_and_fresh = 0;
    while (input_file.peek() != EOF) {
        //get range
        string line;
        getline(input_file,line);
        long long query = stoll(line);
        // printf("\nquery:%lld",query);
        bool in_set = false;
        for (auto r : fresh_set) {
            if (r.first <= query && r.second >= query) {
                in_set = true;
                break;
            }
        }
        if (in_set) queried_and_fresh++;
    }
    printf("\nqueried_and_fresh:%lld",queried_and_fresh);
    input_file.close();
    return 0;
}