#include <algorithm>
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
    sort(fresh_set.begin(),fresh_set.end());
    long long range_end = LONG_LONG_MIN;
    long long total_fresh = 0;
    for (auto p : fresh_set) {
        printf("(%lld,%lld),",p.first,p.second);
        if (range_end >= p.second) {
            continue;
        } else if (range_end >= p.first) {
            total_fresh += p.second-range_end;
        } else {
            total_fresh += p.second-p.first+1;
        }
        range_end = p.second;
    }
    printf("\ntotal_fresh:%lld",total_fresh);
    input_file.close();
    return 0;
}