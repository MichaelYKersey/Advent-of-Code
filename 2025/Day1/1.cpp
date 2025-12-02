#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input_file(argv[1]);
    int zero_count = 0;
    int pos = 50;
    int mod = 100;
    
    while( input_file.peek() != EOF )
    {
        string line;
        getline(input_file,line);
        char comand = line[0];
        printf("\n%s",line.c_str());
        printf(", char:%c",line[0]);
        int val = std::stoi(line.substr(1,line.size()-1));
        printf(", val:%d",val);
        if (line[0] == 'R') {
            pos += val;
        } else {
            pos -= val;
        }
        pos = (pos+mod)%mod;
        printf(", pos:%d",pos);
        if (pos == 0) {
            printf("=======");
            zero_count++;
        }
    }
    printf("\ncount:%d",zero_count);
    input_file.close();
}