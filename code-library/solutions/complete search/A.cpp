#include <bits/stdc++.h>
using namespace std;

int main() {
    char c;
    bool open = 0;
    while ((c = getchar()) != EOF) {
        if (c == '<') open = 1;
        else if (c == '>') open = 0;
        else if (!open) {
            putchar(c);
            if (c == ';') cout << '\n';
        }
    }
    return 0;
}