#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <ratio>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

bool roll_at(vector<string>& grid, int row, int col) {
    if (row < 0 || row >= grid.size()) return false;
    if (col < 0 || col >= grid[row].size()) return false;
    return grid[row][col] == '@';
}

bool accessible(vector<string>& grid, int row, int col) {
    int count = (roll_at(grid,row,col) ? -1:0);
    for (int i=-1; i<=1; i++) {
        for (int j=-1; j<=1; j++) {
            if (roll_at(grid,row+i,col+j)) count++;
        }
    }
    // printf("%d",count);
    return count < 4;
}

int main(int argc, char* argv[]) {
    ifstream input_file(argv[1]);
    vector<string> grid;
    while(input_file.peek() != EOF) {
        grid.push_back("");
        getline(input_file,grid.back());
    }
    int count = 0;
    for (int i=0; i<grid.size(); i++) {
        for (int j=0; j<grid[i].size(); j++) {
            bool a = accessible(grid, i, j);
            bool r = roll_at(grid, i, j);
            if (r) {
                if (a) {
                    printf("X");
                    count++;
                    // grid[i][j] = '.';
                } else {
                    printf("@");
                }
            } else {
                printf(".");
            }

        }
        printf("\n");
    }
    printf("removable:%d", count);
}
