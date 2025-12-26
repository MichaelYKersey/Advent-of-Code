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
    vector<string> problem_input_raw;
    int max_str_len = 0;
    string ops;
    while (true) {
        string line;
        getline(input_file,line);
        // printf("\n%s",line.c_str());
        if ((line[0] > '9' || line[0] < '0') && line[0] != ' ') {
            ops = line + ' ';
            break;
        }
        problem_input_raw.push_back(line);
        max_str_len = max(max_str_len,(int)line.size());
    }
    //parse nums
    vector<long long> nums(max_str_len,0);
    for (int i=0; i<problem_input_raw.size(); i++) {
        for (int j=0; j<problem_input_raw[i].size(); j++) {
            if (problem_input_raw[i][j] != ' ') {
                nums[j] = nums[j]*10 + (int)(problem_input_raw[i][j] - '0');
            }
        }
    }
    printf("\n");
    for (long long n : nums) {
        printf("%lld,",n);
    }
    
    //calc
    long long grand_total = 0;
    int start_index = 0;
    int end_index = 0;
    while (start_index < ops.size()) {
        end_index = start_index+1;
        while (end_index < ops.size() && ops[end_index] == ' ') end_index++;
        if (ops[start_index] == '*') {
            long long problem_sol = 1;
            for (int i=start_index; i<end_index-1; i++) {
                problem_sol *= nums[i];
            }
            grand_total += problem_sol;
        } else if (ops[start_index] == '+') {
            long long problem_sol = 0;
            for (int i=start_index; i<end_index-1; i++) {
                problem_sol += nums[i];
            }
            grand_total += problem_sol;
        }
        start_index = end_index;
    }
    printf("\ngrand_total:%lld",grand_total);

    input_file.close();
    return 0;
}