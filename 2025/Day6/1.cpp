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
    vector<vector<long long>> problem_input;
    string line;
    while (true) {
        getline(input_file,line);
        printf("\n%s",line.c_str());
        if ((line[0] > '9' || line[0] < '0') && line[0] != ' ') break;
        problem_input.push_back({});
        int start_index = 0;
        int end_index = 0;
        while (start_index < line.size()) {
            while (start_index < line.size() && line[start_index] == ' ') start_index++;
            if (start_index >= line.size()) break;
            end_index = start_index+1;
            while (end_index < line.size() && line[end_index] != ' ') end_index++;
            long long val = stoll(line.substr(start_index,end_index-start_index));
            // printf("\n%d",val);
            start_index = end_index;
            problem_input.back().push_back(val);
        }
    }
    //parse ops
    vector<char> ops;
    int op_index = 0;
    while (op_index < line.size()) {
        ops.push_back(line[op_index]);
        op_index++;
        while (op_index < line.size() && line[op_index] == ' ') op_index++;
    }
    //calc
    long long grand_total = 0;
    for (int i=0; i< ops.size(); i++) {
        if (ops[i] == '*') {
            long long problem_sol = 1;
            for (auto const& row : problem_input) {
                problem_sol *= row[i];
            }
            grand_total += problem_sol;
        } else if (ops[i] == '+') {
            long long problem_sol = 0;
            for (auto const& row : problem_input) {
                problem_sol += row[i];
            }
            grand_total += problem_sol;
        }
    }
    printf("\ngrand_total:%lld",grand_total);

    input_file.close();
    return 0;
}