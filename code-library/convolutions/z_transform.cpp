#pragma once
#include <vector>

namespace convolution {

    void z_transform(int a[], int z[], int N, bool inv=0) {
        for (int i=0; i<N; ++i) z[i]=a[i];
        for (int i=0; i<N; ++i)
            for (int s = 0; s < 1<<N; ++s) if(s & (1 << i)) 
                z[s] += (inv==0 ? z[s ^ (1 << i)] : -z[s ^ (1 << i)]);
    }

    int fh[20][1<<20], gh[20][1<<20], h[20][1<<20];
    void subset(int a[], int b[], int c[], int N) {
        for (int i=0; i<(1<<N); ++i) {
            fh[__builtin_popcount(i)][i] = a[i];
            gh[__builtin_popcount(i)][i] = b[i];
        }
        for (int x=0; x<N; ++x) {
            z_transform(fh[x], fh[x], N);
            z_transform(gh[x], gh[x], N);
        }
        for (int i=0; i<(1<<N); ++i)
            for (int x=0; x<N; ++x) {
                h[x][i] = 0;
                for (int y=0; y<=x; ++y)
                    h[x][i] += fh[y][i] * gh[x-y][i];
            }
        for (int x=0; x<N; ++x)
            z_transform(h[x], h[x], N, true);
        for(int i=0; i<(1<<N); ++i)
            c[i] = h[__builtin_popcount(i)][i];
    }

};
