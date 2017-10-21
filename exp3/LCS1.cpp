#include <iostream>
#include <string>

using namespace std;

void getLCSLen(string a, string b, int **cnum);
string getLCS(string a, int **cnum, int i, int j);

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
    for (int i = 0; i < m+1; i++) {//������̬��ά����cnum����c[i,j]��ֵ��cnum�������������ַ�����LCS����
        cnum[i] = new int [n+1];
    }
    for (int i = 0; i < m+1 ; i++) {//cnum��ʼ��Ϊ0
        for (int j = 0; j < n+1; j++) {
            cnum[i][j] = 0;
        }
    }
    getLCSLen(str1, str2, cnum);
    string a = getLCS(str1, cnum, str1.size(), str2.size());
    cout << "the LCS of the two strings is:"<<endl;
    cout << a << endl;
    /*for (int i = 0; i < m+1 ; i++) {
        for (int j = 0; j < n+1; j++) {
            cout << cnum[i][j];
        }
        cout <<endl;
    }*/
    for (int i = 0; i < m+1; i++)//�ͷ��ڴ�
    {
        delete [] cnum[i];
    }
    delete [] cnum;
    return 0;
}

void getLCSLen(string a, string b, int **cnum) { // ����c[i][j]��

    unsigned int i = 0, j = 0;
    for (unsigned int i = 0; i < a.size() + 1; i++) {
        cnum[i][0] = 0;
    }
    for (j = 0; j < b.size() + 1; j++) {
        cnum[0][j] = 0;
    }
    for (i = 1; i < a.size() + 1; i++) {
        for (j = 1; j < b.size() + 1; j++) {
            if (a[i-1] == b[j-1]) {
                cnum[i][j] = cnum[i-1][j-1] + 1;
            }
            else if ( cnum[i-1][j] > cnum[i][j-1]) {
                cnum[i][j] = cnum[i-1][j];
            }
            else {
                cnum[i][j] = cnum[i][j-1];
            }
        }
    }
}

string getLCS(string a, int **cnum, int i, int j) { //��ȡ�����������
    if (i == 0 || j == 0) {
        return "";
    }
    if (cnum[i][j] == cnum[i-1][j-1] + 1) {
        return getLCS(a, cnum, i-1, j-1) + a[i-1];
    }
    else if (cnum[i][j] == cnum[i-1][j]) {
        return getLCS(a, cnum, i-1, j);
    }
    else {
        return getLCS(a, cnum, i, j-1);
    }
}

