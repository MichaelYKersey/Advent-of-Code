#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input_file(argv[1]);
    int sum = 0;
    while(input_file.peek() != EOF) {
        string line;
        getline(input_file,line);
        if (line.size() < 2) {
            throw std::invalid_argument(nullptr);
        }
        //first
        int c1 = line.size()-2;
        for (int i=c1-1; i>=0; i--) {
            if (line[i] >= line[c1]) {
                c1 = i;
            }
        }
        int c2 = line.size()-1;
        for (int i=c2-1; i>c1; i--) {
            if (line[i] >= line[c2]) {
                c2 = i;
            }
        }
        sum += (int)(line[c1]-'0')*10+(int)(line[c2]-'0');
    }
    printf("%d",sum);
}