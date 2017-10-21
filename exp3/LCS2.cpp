#include <iostream>
#include <string>

using namespace std;

void getLCSLen(string a, string b, int **cnum, int **bnum);
void getLCS(string a, int **bnum, int i, int j, int current_len, int max_len, char *result);

int main()
{
    string str1, str2;
    cout << "Please input the first string:" << endl;
    cin >> str1;
    cout << "Please input the second string:" << endl;
    cin >> str2;
    int m = str1.size();
    int n = str2.size();
    int **cnum = new int *[m+1];
    int **bnum = new int *[m+1];
    for (int i = 0; i < m+1; i++) {//创建动态二维数组cnum保存c[i,j]的值，bnum保存b[i,j]的值
        cnum[i] = new int [n+1];
        bnum[i] = new int [n+1];
    }
    for (int i = 0; i < m+1 ; i++) {//bnum，cnum初始化为0
        for (int j = 0; j < n+1; j++) {
            cnum[i][j] = 0;
            bnum[i][j] = 0;
        }
    }
    getLCSLen(str1, str2, cnum, bnum);
    int k = cnum[m][n];
    char *result = new char [k];
    cout << "the LCS of the two strings is:"<<endl;
    getLCS(str1, bnum, m, n, k, k, result);
    for (int i = 0; i < m+1; i++)//释放内存
    {
        delete [] cnum[i];
        delete [] bnum[i];
    }
    delete [] cnum;
    delete [] bnum;
    return 0;
}

void getLCSLen(string a, string b, int **cnum, int **bnum) { // 计算c[i,j]，b[i,j]表

    unsigned int i = 0, j = 0;
    for (unsigned int i = 0; i <= a.size(); i++) {
        cnum[i][0] = 0;
        bnum[i][0] = 0;
    }
    for (j = 0; j <= b.size(); j++) {
        cnum[0][j] = 0;
        bnum[0][j] = 0;
    }
    for (i = 1; i <= a.size(); i++) {
        for (j = 1; j <= b.size(); j++) {
            if (a[i-1] == b[j-1]) {
                cnum[i][j] = cnum[i-1][j-1] + 1;
                bnum[i][j] = 1;
            }
            else if ( cnum[i-1][j] > cnum[i][j-1]) {
                cnum[i][j] = cnum[i-1][j];
                bnum[i][j] = 2;
            }
            else {
                cnum[i][j] = cnum[i][j-1];
                if (cnum[i-1][j] < cnum[i][j-1]) {
                    bnum[i][j] = 3;
                } else {
                    bnum[i][j] = 4;
                }
            }
        }
    }
}

void getLCS(string a, int **bnum, int i, int j, int current_len, int max_len, char *result) { //获取最长公共子序列
    if (i == 0 || j == 0) {
        for (int k = 0; k < max_len; k++) {
            cout << result[k];
        }
        cout << endl;
        return ;
    }
    if (bnum[i][j] == 1) {
        current_len--;
        result[current_len] = a[i-1];
        getLCS(a, bnum, i-1, j-1, current_len, max_len, result);
    }
    else if (bnum[i][j] == 2) {
        getLCS(a, bnum, i-1, j, current_len, max_len, result);
    }
    else if (bnum[i][j] == 3) {
        getLCS(a, bnum, i, j-1, current_len, max_len, result);
    }
    else {
        getLCS(a,bnum, i, j-1, current_len, max_len, result);
        getLCS(a, bnum, i-1, j, current_len, max_len, result);
    }
}

