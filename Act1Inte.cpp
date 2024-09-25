#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string readFile(const string& filename) {
    ifstream file(filename);
    string content, line;
    while (getline(file, line)) {
        content += line;
    }
    return content;
}

pair<bool, int> findSubstring(const string& text, const string& pattern) {
    size_t pos = text.find(pattern);
    if (pos != string::npos) {
        return {true, static_cast<int>(pos + 1)};
    }
    return {false, -1};
}

pair<int, int> longestPalindromicSubstring(const string& s) {
    int n = s.size();
    if (n == 0) return {0, 0};

    vector<vector<bool>> dp(n, vector<bool>(n, false));
    int maxLength = 1;
    int start = 0;

    for (int i = 0; i < n; ++i)
        dp[i][i] = true;

    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    for (int k = 3; k <= n; ++k) {
        for (int i = 0; i < n - k + 1; ++i) {
            int j = i + k - 1;
            if (dp[i + 1][j - 1] && s[i] == s[j]) {
                dp[i][j] = true;
                if (k > maxLength) {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
    return {start + 1, start + maxLength};
}

pair<int, int> longestCommonSubstring(const string& s1, const string& s2) {
    int m = s1.size();
    int n = s2.size();
    vector<vector<int>> LCSuf(m + 1, vector<int>(n + 1, 0));

    int length = 0;
    int row = 0, col = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                LCSuf[i][j] = LCSuf[i - 1][j - 1] + 1;
                if (LCSuf[i][j] > length) {
                    length = LCSuf[i][j];
                    row = i;
                    col = j;
                }
            } else {
                LCSuf[i][j] = 0;
            }
        }
    }

    if (length == 0) return {-1, -1};

    return {row - length + 1, row};
}

int main() {
    string transmission1 = readFile("transmission1.txt");
    string transmission2 = readFile("transmission2.txt");
    string mcode1 = readFile("mcode1.txt");
    string mcode2 = readFile("mcode2.txt");
    string mcode3 = readFile("mcode3.txt");

    // Parte 1: Verificar hay codigos en las transmisiones
    cout << "Parte 1:" << endl;
    vector<string> transmissions = {transmission1, transmission2};
    vector<string> mcodes = {mcode1, mcode2, mcode3};

    for (int i = 0; i < transmissions.size(); ++i) {
        for (int j = 0; j < mcodes.size(); ++j) {
            auto result = findSubstring(transmissions[i], mcodes[j]);
            if (result.first) {
                cout << "true " << result.second << endl;
            } else {
                cout << "false" << endl;
            }
        }
    }

    // Parte 2: Longest Palindromic Substring
    cout << "\nParte 2:" << endl;
    auto palindrome1 = longestPalindromicSubstring(transmission1);
    auto palindrome2 = longestPalindromicSubstring(transmission2);
    cout << palindrome1.first << " " << palindrome1.second << " (transmission1)" << endl;
    cout << palindrome2.first << " " << palindrome2.second << " (transmission2)" << endl;

    // Parte 3: Longest Common Substring
    cout << "\nParte 3:" << endl;
    auto commonSubstring = longestCommonSubstring(transmission1, transmission2);
    cout << commonSubstring.first << " " << commonSubstring.second << " (substring común más largo entre archivos de transmisión)" << endl;

    return 0;
}
