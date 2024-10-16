#include <bits/stdc++.h>
using namespace std;

const int N = 8;
bool FOUND;
int rows[8];
int cols[8];
int boxs[2][2];
int S[8][8];

bool verify(int x, int y, int d) {
    if (rows[x] & (1 << d)) return false;
    if (cols[y] & (1 << d)) return false;
    if (boxs[x/4][y/4] & (1<<d)) {
        if (boxs[x/4][y/4] & (1<<(d+8))) return false;
    }
    return true;
}

void put_d(int x, int y, int d) {
    rows[x] |= (1<<d);
    cols[y] |= (1<<d);
    if ((boxs[x/4][y/4] >> d) & 1) boxs[x/4][y/4] |= (1<<(d+8));
    else boxs[x/4][y/4] |= (1<<d); 
    S[x][y] = d;
}

void rem_d(int x, int y, int d) {
    rows[x] &= ~(1<<d);
    cols[y] &= ~(1<<d);
    if ((boxs[x/4][y/4] >> (d+8)) & 1) boxs[x/4][y/4] &= ~(1<<(d+8));
    else boxs[x/4][y/4] &= ~(1<<d);
    S[x][y] = 0; 
}

void dfs(int x, int y) {
    if (FOUND) return;
    if (x == N) {
        FOUND = true;
        cout << "YES" << '\n';
        for (int i=0; i<8; ++i) {
            for (int j=0; j<8; ++j) {
                cout << S[i][j] << " \n"[j+1==8];
            }
        }
        return;
    }
    if (y == N) {
        return dfs(x+1, 0);
    }
    if (S[x][y] != 0) {
        return dfs(x, y + 1);
    } 
    for (int d=1; d<=8; ++d) {
        if (!verify(x, y, d)) continue;       
        put_d(x, y, d);
        dfs(x, y + 1);
        rem_d(x, y, d);
    }
}


void print_sudoku() {
    FOUND = false;
    memset(rows, 0, sizeof rows);
    memset(cols, 0, sizeof cols);
    memset(boxs, 0, sizeof boxs);
    for (int i = 0; i < 8; ++i) {
        for (int j=0; j < 8; ++j) {
            if (S[i][j] != 0) {
                if (!verify(i, j, S[i][j])) {
                    cout << "NO" << '\n';
                    return;
                }
                put_d(i, j, S[i][j]);
            }
        }
    }
    dfs(0, 0);
    if (!FOUND) cout << "NO" << '\n';
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int t, tc=1;
    cin>>t;
    while (t--) {
        for (int i=0; i<8; ++i) {
            for (int j=0; j<8; ++j) {
                cin>>S[i][j];
            }
        }
        cout << "Test case #" << tc++ << ": ";
        print_sudoku();
    }
    return 0;
}