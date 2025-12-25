#include <cstddef>
#include <cstdio>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    ifstream input_file(argv[1]);
    long long sum = 0;
    while(input_file.peek() != EOF) {
        string line;
        getline(input_file,line);
        constexpr int dc = 12;
        int digits[dc] = {};
        if (line.size() < dc ) {
            throw std::invalid_argument(nullptr);
        }
        for (int i=0; i<dc; i++) {
            int lower_bound = (i==0 ? 0 : digits[i-1]+1);//prev+1 or 0
            digits[i] = line.size()-(dc-i);
            for (int j=digits[i]; j>=lower_bound; j--) {
                if (line[j] >= line[digits[i]]) {
                    digits[i] = j;
                }
            }
            // printf("%c-%d,",line[digits[i]],digits[i]);
        }
        // printf("----\n");
        long long jolts = 0;
        long long power = 1;
        for (int i=dc-1; i>=0; i--) {
            jolts += power * (int)(line[digits[i]] - '0');
            power *= 10;
        }
        sum += jolts;
        printf("jolts:%lld\n",jolts);
    }
    printf("sum:%lld\n",sum);
}