#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct search_info {
    int reps;
    long long frac_mag;
    long long full_mag;
    long long start;
    long long end;
    long long div;
    void print() {
        printf("\nstart:%lld,\tend:%lld,\treps:%lld,\tfrac_mag%lld,\tfull_mag:%lld,\tdiv:%lld",
            start,end,reps,frac_mag,full_mag,div);
    }
};

long long clac_expo(long long val, int expo) {
    long long result = 1;
    while (expo > 0) {
        // printf("\nin expo loop");
        result *= val;
        expo--;
        if (result <= 0) throw overflow_error(nullptr);
    }
    return result;
}
long long get_div(long long frac_mag, int reps) {
    long long div = 1;
    reps --;
    while (reps > 0) {
        div = div * frac_mag + 1;
        reps--;
    }
    return div;
}

//returns current frac_mag if valid of neg of next frac_mag if invalid
search_info get_first_search_info(long long start, long long end,int reps) {
    search_info si;
    si.reps = reps;
    si.frac_mag = 1;
    si.full_mag = 1;
    long long expo = clac_expo(10,reps);
    while (start >= si.full_mag) {
        // printf("\nloop:%lld,%lld,%lld",si.frac_mag,si.full_mag,expo);
        si.frac_mag *= 10;
        si.full_mag *= expo;
    }
    si.start = max(start,si.full_mag/10);
    si.end = min(end,si.full_mag-1);
    si.div = get_div(si.frac_mag,si.reps);
    return si;
}
search_info get_next_search(search_info si, long long end) {
    si.frac_mag *= 10;
    si.full_mag *= clac_expo(10,si.reps);
    si.start = si.full_mag/10;
    si.end = min(si.full_mag-1,end);
    si.div = get_div(si.frac_mag,si.reps);
    return si;
}

long long calc_sum_invalid_in_range(search_info si) {
    //calc range of invalids
    long long start_num = (si.start-1)/si.div+1;
    long long end_num = si.end/si.div;
    //if no invalids then return
    //calc triangles values to sum
    if (start_num > end_num) return 0;
    printf("\ninvalids_rep_num:%lld - %lld\t reps:%d",start_num,end_num,si.reps);
    long long positive_triangle = end_num * (end_num+1)/2;
    long long negative_triangle = (start_num-1) * start_num /2;
    return (positive_triangle-negative_triangle) * si.div;
}
vector<int> calc_rep_factor(int reps) {
    vector<int> reps_factor(reps+1,0);
    for (int i=2; i<= reps; i++) {
        for (int j=2; j< i; j++) {
            // printf("\ntesting:%d%%%d=%d",j,i,j%i);
            if (i%j == 0) {
                reps_factor[i] -= reps_factor[j];
                // printf("doubled");
            }
        }
        reps_factor[i]++;
        printf("\n%d:%d",i,reps_factor[i]);
    }
    return reps_factor;
}

int main(int argc, char* argv[]) {
    printf("app start\n");
    constexpr int max_reps = 39;
    vector<int> rep_factor = calc_rep_factor(max_reps);

    ifstream input_file(argv[1]);
    long long invalid_sum_total = 0;
    bool last = false;
    while (not last) {
        //get range
        long long start;
        input_file >> start;
        input_file.get();
        long long end;
        input_file >> end;
        if (input_file.peek() == EOF) {
            last = true;
        } else {
            input_file.get();
        }
        printf("\nInput Range:%lld - %lld", start, end);
        
        // printf("\nloop:%d",last);
        //get number of digits
        //if odd skip
        //if even then break into 2
        //the diff in range for first part determins how many matchs there are
        //check if max of doble (9...9...) is in range if not then take mod of upper to get highest posible and also check if that one is in range
        //keep incremnting digits untill all are cleared

        // TODO: acreps_
        int most_reps = 1;
        long long mag = 10;
        while (mag <= end) {
            // printf("\nfinding most_reps");
            most_reps++;
            mag *= 10;
        }
        // printf("\nmost_reps:%d",most_reps);

        long long invalid_sum = 0;
        for (int reps=2; reps<= most_reps; reps++) {
            search_info si = get_first_search_info(start,end,reps);
            while (si.start <= si.end) {
                // si.print();
                invalid_sum += calc_sum_invalid_in_range(si) * rep_factor[reps];
                si = get_next_search(si, end);
            }
            // si.print();
        }
        if (invalid_sum) {
            printf("\nInput Range:%lld - %lld", start, end);
            printf("\ninvalid_sum:%lld",invalid_sum);
        }
        invalid_sum_total += invalid_sum;
        printf("\n");
    }
    printf("\ninvalid_sum_total:%lld",invalid_sum_total);

    input_file.close();
    return 0;
}