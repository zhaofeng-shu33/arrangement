#include <bits/stdc++.h>
#include <fstream>

#include "shape_info.h"

int input[1000][10];
int output[10][20];
std::ofstream fout("result.txt");
void initialize_output() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            output[i][j] = 0;
        }
    }
}
void read_to_input() {
    std::ifstream fin("test_case.txt");
    for (int i = 0; i < 1000; i++) {
        for (int j = 0; j < 19; j++) {
            fin >> input[i][j];
        }
    }
    fin.close();
}

bool permissible(int index, int h_p, int v_p) {
    for (int i = 0; i < 13; i++) {
        if (shape_info[index][i] == 0) {
            continue;
        }
        int h_delta = i % 4;
        int v_delta = i / 4;
        int new_h = h_p + h_delta;
        int new_v = v_p + v_delta;
        if (new_h == 12 || new_h > 19)
            return false;
        if (new_v == 5 || new_v > 9)
            return false;
        if (output[new_h][new_v] == 1) {
            return false;
        }
    }
    return true;
}

void put_here(int index, int h_p, int v_p) {
    for (int i = 0; i < 13; i++) {
        if (shape_info[index][i] == 0) {
            continue;
        }
        int h_delta = i % 4;
        int v_delta = i / 4;
        output[h_p + h_delta][v_p + v_delta] = 1;
    }
}
//! return true is no permissible is available
bool get_next_permissible(int index, int& h_p, int& v_p) {
    for (int i = h_p; i < 20; i++) {
        for (int j = v_p; j < 10; j++) {
            // skip the road
            if (i == 11) {
                continue;
            }
            if (j == 4) {
                continue;
            }
            if (permissible(index, h_p, v_p)) {
                h_p = i;
                v_p = j;
                return false;
            }
        }
    }
    return true;
}

void compute_one_round(int index) {
    for (int i = 0; i < 19; i++) {
        int h_p = 0, v_p = 0;
        for (int j = 0; j < input[index][i]; j++) {
            if (permissible(index, h_p, v_p)) {
                put_here(index, h_p, v_p);
            }
            if (get_next_permissible(index, h_p, v_p)) {
                break;
            }
        }
    }
}

void write_to_result_file() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            fout << output[i][j];
        }
    }
}
int main() {
    read_to_input();
    initialize_output();
    for (int i = 0; i < 1000; i++) {
        compute_one_round(i);
        write_to_result_file();
    }
}