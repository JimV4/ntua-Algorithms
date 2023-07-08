#include<iostream>

using namespace std;

int n, k, minLength, currentSum, currentLength;
int p[20000], prefixSum[20000], help[1000000];

int subSum (int start, int finish, int *arr) {
    if (start == 0)
        return arr[finish];
    return arr[finish] - arr[start - 1];
}

int main () {
    cin >> n >> k;
    
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (i == 0) 
            prefixSum[0] = p[0];
        else
            prefixSum[i] = p[i] + prefixSum[i - 1];
    }

    for (int i = 0; i < k; i++) {
        help[i] = n + 1;
    }
    minLength = n + 1;

    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            currentSum = subSum(i, j, prefixSum);
            currentLength = j - i + 1;
            if (currentSum < k + 1) {
                if (currentLength < help[currentSum - 1]) {
                    help[currentSum - 1] = currentLength;
                }
            }
            else 
                break;
        }

        for (int j = i; j >= 0; j--) {
            currentSum = subSum(j, i, prefixSum);
            currentLength = i - j + 1;
            if (currentSum < k + 2) {
                if (currentLength + help[k - currentSum - 1] < minLength && currentSum <= k)
                    minLength = currentLength + help[k - currentSum - 1];
            }
            else if (currentSum >= k + 1) {
                break;
            }  
        }
    }

    if (minLength >= n + 1) {
        minLength = -1;
    }
    
    cout << minLength << endl;
}
