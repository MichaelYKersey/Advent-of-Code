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
    string line;
    getline(input_file,line);
    vector<long long> beams(line.size(),0);
    for (int i=0; i<line.size(); i++) {
        if (line[i] == 'S') beams[i] = 1;
    }
    long long splits = 0;
    while (input_file.peek() != EOF) {
        vector<long long> new_beams(beams.size(),0);
        long long add_to_next = 0;
        getline(input_file,line);
        // printf("%s\n",line.c_str());
        for (int i=0; i<line.size(); i++) {    
            if (line[i] == '.') {
                new_beams[i] += beams[i];
            } else if (line[i] == '^') {
                new_beams[i-1] += beams[i];
                new_beams[i+1] += beams[i];
                if (beams[i] > 0) splits++;
            } else {
                throw invalid_argument(nullptr);
            }
        }
        for (int i=0; i<line.size(); i++) {
            if (new_beams[i]) line[i] = '|';
        }
        printf("%s\t%lld\n",line.c_str(),splits);
        beams = std::move(new_beams);
    }
    printf("\nsplits:%lld",splits);
    long long total_beams = 0;
    for (long long b : beams) {
        total_beams += b;
    }
    printf("total_beams:%lld",total_beams);

    input_file.close();
    return 0;
}