#include <stdio.h>

int findJudge(int n, int trustSize, int** trust) {
    
    int trust_count[n + 1]; 
    int is_trusted[n + 1];  

    for (int i = 0; i <= n; i++) {
        trust_count[i] = 0;
        is_trusted[i] = 0;
    }
    for (int i = 0; i < trustSize; i++) {
        int a = trust[i][0];
        int b = trust[i][1];
        trust_count[b]++;
        is_trusted[a]++;
    }

    for (int i = 1; i <= n; i++) {
        if (trust_count[i] == n - 1 && is_trusted[i] == 0) {
            return i;  
        }
    }

    return -1; 
}
int main() {
    int n = 4;
    int trustSize = 5;
    int trust[5][2] = {{1,3},{1,4},{2,3},{2,4},{4,3}};
    printf("%d\n", findJudge(n, trustSize, trust));
    return 0;
}
