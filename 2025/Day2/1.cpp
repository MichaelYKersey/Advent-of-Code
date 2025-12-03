#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

//returns half mag & -mag if not even (10-99 -> 10, 1000-9999 -> 100)
//mag being 10^n where n is digits/2
//if mag -round up on n
long long get_half_mag(long long val) {
    long long mag = 1;
    while (val >= mag*mag) {
        // printf("\nloop:%lld,%lld",val,mag*mag);
        mag *= 10;
    }
    if (val > mag*mag/10-1) {
        return mag;
    }
    return -mag;
}
long long get_next_half_mag(long long val) {
    long long half_mag = get_half_mag(val);
    if (half_mag < 0) {
        return -half_mag;
    } else {
        return half_mag * 10;
    }
}
long long count_dupe_inrange(long long half_mag, long long start, long long end) {
    long long start_num = start/half_mag;
    long long end_num = end/half_mag;
    //calc for sure inbetween vals (not inclue start & end pairs)
    //end and start are same then it will double count addition for end invalids so it balances out
    long long count = (end_num-1) - start_num;
    //end invalids
    long long start_invalid = start_num*half_mag+start_num;
    if (start <= start_invalid && start_invalid <= end) count++;
    long long end_invalid = end_num*half_mag+end_num;
    if (start <= end_invalid && end_invalid <= end) count++;
    //return min 0
    return max(count,0ll);
}
long long calc_sum_dupe_inrange(long long half_mag, long long start, long long end) {
    //calc range of invalids
    long long start_num = start/half_mag;
    if (start%half_mag > start_num) start_num++; 
    long long end_num = end/half_mag;
    if (end%half_mag < end_num) end_num--;
    //if no invalids then return
    if (end_num < start_num) return 0;
    //calc triangles values to sum
    printf("\ndupes:%lld - %lld",start_num,end_num);
    long long positive_triangle = end_num * (end_num+1)/2;
    long long negative_triangle = (start_num-1) * start_num /2;
    return (positive_triangle-negative_triangle) * (half_mag+1);
}

int main(int argc, char* argv[]) {
    printf("app start\n");
    // get_half_mag(2121212118);
    // for (int i=1; i< argc; i++) {
        // int a = atoi(argv[i]);
        // printf("\n%lld:%lld,%lld",a,get_half_mag(a),get_next_half_mag(a)*get_next_half_mag(a)/10);
        // printf("\n%lld:%lld",a,get_half_mag(a));
    // }
    // for (int i=1; i+1 < argc; i+=2) {
    //     int s = atoi(argv[i]);
    //     int e = atoi(argv[i+1]);
    //     printf("\n%lld - %lld:%lld", s, e, calc_dupe_inrange(get_half_mag(s),s,e));
    // }
    // printf("app end\n");
    // return 0;
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
        printf("\n\nInput Range:%lld - %lld", start, end);
        // printf("\nloop:%d",last);
        //get number of digits
        //if odd skip
        //if even then break into 2
        //the diff in range for first part determins how many matchs there are
        //check if max of doble (9...9...) is in range if not then take mod of upper to get highest posible and also check if that one is in range
        //keep incremnting digits untill all are cleared
        long long half_mag = get_half_mag(start);
        //if not half mag then get next mag
        if (half_mag < 0) {
            half_mag *= -1;
            start = half_mag * half_mag / 10;
        }
        long long invalid_sum = 0;
        while (start <= end) {
            // printf("\nloop");
            long long search_end = min(end, half_mag*half_mag-1);
            if (search_end < 0) break;
            printf("\nsearch range:%lld - %lld", start, search_end);
            invalid_sum += calc_sum_dupe_inrange(half_mag, start, search_end);
            half_mag *= 10;
            start = half_mag * half_mag / 10;
        }
        printf("\ninvalid_sum:%lld",invalid_sum);
        invalid_sum_total += invalid_sum;

        printf("\n");
    }
    printf("\ninvalid_sum_total:%lld",invalid_sum_total);

    input_file.close();
    return 0;
}