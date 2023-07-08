#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

int findMax(vector<int> &v, int size) {
    int max = v[0];
    for (int i = 0; i < size; i++) {
        if (v[i] > max) max = v[i];
    }
    return max;
}

int n, k, l, r, candidateMedian, result, maxSum, minSum;
int *c, *ones, *sums;
bool isMedian = false;
vector<int> medians;


int main () {
    // input
    cin >> n >> k;
    c = new int [n];
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    //-------------------------------------------------------------------------//
    ones = new int [n];
    sums = new int [n];
    l = 1;
    r = n;
    while(l <= r) {
        isMedian = false;
        candidateMedian = (l + r) / 2;
        for (int i = 0; i < n; i++) {
            if (c[i] < candidateMedian)
                ones[i] = -1;
            else
                ones[i] = 1;
        }
        sums[0] = ones[0];
        for (int i = 1; i < n; i++) {
            sums[i] = sums[i - 1] + ones[i];
        }

        maxSum = sums[k - 1];
        minSum = 0;
        for (int i = k; i < n; i++) {
            if (sums[i - k] < minSum)
                minSum = sums[i - k];
            if (sums[i] - minSum > maxSum)
                maxSum = sums[i] - minSum;
        }
        if (maxSum > 0) {
            medians.push_back(candidateMedian);
            isMedian = true;
        }
        if (isMedian) l = candidateMedian + 1;
        else r = candidateMedian - 1;
    }

    result = findMax(medians, medians.size());
    cout << result << endl;
    return 0;
}