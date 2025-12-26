#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_set>

using namespace std;

struct range_set{
    //key is lower bound value is lower
    map<long long, long long> set_ranges;
    void insert(long long start, long long end) {
        //if start is not in set make new key starting at start
        bool not_in_set;
        auto start_it = set_ranges.upper_bound(start);
        if (start_it == set_ranges.begin()) {
            not_in_set = true;
        } else {
            start_it--;
            not_in_set = start_it->second < start;
        }
        if (not_in_set) {
            set_ranges.insert(pair(start,end));
            start_it = set_ranges.find(start);
        } else {
            start_it->second = max(start_it->second,end);
        }
        //merge the iterator that contains start with ranges that overlap
        long long range_start= start_it->first; 
        long long range_end = start_it->second;
        
        bool fin = false;
        while (!fin) {
            start_it++;
            if (start_it != set_ranges.end() && start_it->first <= range_end) {
                range_end = start_it->second;
                set_ranges.erase(start_it);
                start_it = set_ranges.find(range_start);
                start_it->second = range_end;
            } else {
                fin = true;
            }
        } 
    }
    bool contains(long long val) {
        auto it = set_ranges.upper_bound(val);
        if (it == set_ranges.begin()) {
            return false;
        } else {
            it--;
            return it->second >= val;
        }
    }
    void print() {
        for (auto it = set_ranges.begin(); it != set_ranges.end(); it++) {
            printf("\n(%lld,%lld)", it->first,it->second);
        }
    }
};

int main(int argc, char* argv[]) {
    printf("app start\n");
    ifstream input_file(argv[1]);
    range_set fresh_set;
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
            fresh_set.insert(start,end);
            // printf("\nInput Range:%lld - %lld", start, end);
        }
    }

    //check struct validity
    long long last_range_end = LONG_LONG_MIN;
    for (auto it = fresh_set.set_ranges.begin(); it != fresh_set.set_ranges.end(); it++) {
        if (last_range_end >= it->first) {
            printf("\ninvalid:%d,%d", last_range_end,it->first);
        }
        last_range_end = it->second;
    }
    // printf("\nset ranges:");
    // fresh_set.print();
    // printf("\ncontains 3:%d",fresh_set.contains(10));
    
    printf("\ncheking");
    //check if in set
    long long queried_and_fresh = 0;
    while (input_file.peek() != EOF) {
        //get range
        string line;
        getline(input_file,line);
        long long query = stoll(line);
        // printf("\nquery:%lld",query);
        if (fresh_set.contains(query)) queried_and_fresh++;
    }
    printf("\nqueried_and_fresh:%lld",queried_and_fresh);
    input_file.close();
    return 0;
}