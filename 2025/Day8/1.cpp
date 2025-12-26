#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits.h>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_set>
#include <vector>

using namespace std;

string to_string(tuple<int,int,int> pos) {
    return "(" + std::to_string(std::get<0>(pos)) + "," + std::to_string(std::get<1>(pos)) + "," + std::to_string(std::get<2>(pos)) + ")";
}
long long calc_dist_sqrd(tuple<int,int,int> pos1, tuple<int,int,int> pos2) {
    int d0 = std::get<0>(pos1) - std::get<0>(pos2);
    int d1 = std::get<1>(pos1) - std::get<1>(pos2);
    int d2 = std::get<2>(pos1) - std::get<2>(pos2);
    return (((long long)d0)*d0)+(((long long)d1)*d1)+(((long long)d2)*d2);
}

struct disjoint_set {
    vector<int> parent;
    vector<int> set_size;
    disjoint_set(int size) {
        parent = vector<int>(size,-1);
        set_size = vector<int>(size,1);
    }
    int get_set(int element) {
        if (parent[element] == -1) {
            return element;
        } else {
            parent[element] = get_set(parent[element]);
            return parent[element];
        }
    }
    int get_set_size(int element) {
        return set_size[get_set(element)];
    }
    bool merge(int e1, int e2) {
        e1 = get_set(e1);
        e2 = get_set(e2);
        if (e1 == e2) return false;
        if (set_size[e1] > set_size[e2]) {
            parent[e2] = e1;
            set_size[e1] += set_size[e2];
        } else {
            parent[e1] = e2;
            set_size[e2] += set_size[e1];
        }
        return true;
    }
};

int main(int argc, char* argv[]) {
    printf("app start\n");
    ifstream input_file(argv[1]);
    
    vector<tuple<int,int,int>> poses;
    printf("\nposes:");
    while (input_file.peek() != EOF) {
        string line;
        getline(input_file,line);
        int coma_index_1 = 0;
        while (line[coma_index_1] != ',') coma_index_1++;
        int coma_index_2 = coma_index_1+1;
        while (line[coma_index_2] != ',') coma_index_2++;
        poses.push_back({
            stoi(line.substr(0,coma_index_1)),
            stoi(line.substr(coma_index_1+1,coma_index_2-coma_index_1-1)),
            stoi(line.substr(coma_index_2+1,line.size()-coma_index_2-1))
        });
        printf("\n%s",to_string(poses.back()).c_str());
    }

    //calc distances for pairs
    printf("\npairs:");
    vector<pair<pair<int,int>,long long>> pairs(poses.size()*(poses.size()-1)/2);
    int pair_index = 0;
    for (int i=0; i<poses.size(); i++) {
        for(int j=i+1; j<poses.size(); j++) {
            pairs[pair_index] = pair(pair(i,j),calc_dist_sqrd(poses[i], poses[j]));
            pair_index++;
            // printf("\n(%d,%d):%lld",i,j,calc_dist_sqrd(poses[i], poses[j]));
        }
    }
    
    //use heap to get shortest distances
    auto compare_func = [&](pair<pair<int,int>,long long>& e1, pair<pair<int,int>,long long>& e2){
        return e1.second > e2.second;
    };
    make_heap(pairs.begin(),pairs.end(),compare_func);
    printf("\ndist_heap:");
    // for (auto const& p : pairs) {
    //     printf("%d,",p.second);
    // }
    // auto heap_back_print = pairs.end();
    // while (heap_back_print != pairs.begin()) {
    //     printf("%lld,",pairs.front().second);
    //     pop_heap(pairs.begin(),heap_back_print,compare_func);
    //     heap_back_print--;
    // }
    // return 0;
    //use a disjoint set to keep track of connected nodes
    //pick merges
    printf("\nmergeing");
    disjoint_set ds(poses.size());
    int merges = 1000;
    auto heap_back = pairs.end();
    while (merges > 0) {
        // if (pairs.begin() == heap_back) {
        //     printf("AHHHHHHHH");
        // }
        int e1 = pairs.front().first.first;
        int e2 = pairs.front().first.second;
        // printf("\ntrying to merge:%d,%d",e1,e2);
        if (ds.merge(e1,e2)) {
            // printf("\nmerged:%d,%d,%lld",e1,e2,pairs.front().second);
        }
        merges--;
        pop_heap(pairs.begin(),heap_back,compare_func);
        heap_back--;
    }
    //make heap of largest sets
    printf("\ngeting_largets_sets");
    vector<int> largest_circuits (3,-1);
    for (int i=0; i<poses.size(); i++) {
        // if (ds.get_set(i) == i) {
        //     printf("\nset_parent:%d",i);
        // }
        if (ds.get_set(i) == i && ds.get_set_size(i) > largest_circuits.front()) {
            pop_heap(largest_circuits.begin(),largest_circuits.end(),greater<int>());
            largest_circuits.back() = ds.get_set_size(i);
            push_heap(largest_circuits.begin(),largest_circuits.end(),greater<int>());
        }
    }
    //calc product
    printf("\n");
    long long product = 1;
    for (int n : largest_circuits) {
        product *= n;
        printf("%d,",n);
    }
    printf("\nproduct:%lld",product);


    input_file.close();
    return 0;
}