#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <cctype>

using namespace std;

int isKeyword(const char buffer[]) {
    const char* keywords[32] = {
        "auto","break","case","char","const","continue","default",
        "do","double","else","enum","extern","float","for","goto",
        "if","int","long","register","return","short","signed",
        "sizeof","static","struct","switch","typedef","union",
        "unsigned","void","volatile","while"
    };
    for(int i = 0; i < 32; ++i) {
        if(strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    ifstream fin("lexicalinput.txt");
    if (!fin.is_open()) {
        cout << "Error while opening the file\n";
        return 1;
    }

    char ch, buffer[15], b[30];
    int mark[256] = {0}; // To mark used characters
    int j = 0, aaa = 0;

    vector<string> keywords;
    vector<string> identifiers;
    vector<char> logical_ops;
    vector<char> math_ops;
    vector<string> numerics;
    vector<char> others;

    while (fin.get(ch)) {
        // Check for other symbols
        if (strchr(",;(){}[]'", ch)) {
            if (mark[ch] != 1) {
                others.push_back(ch);
                mark[ch] = 1;
            }
        }

        // Check for math operators
        if (strchr("+-*/=", ch)) {
            if (mark[ch] != 1) {
                math_ops.push_back(ch);
                mark[ch] = 1;
            }
        }

        // Check for logical operators
        if (strchr("><", ch)) {
            if (mark[ch] != 1) {
                logical_ops.push_back(ch);
                mark[ch] = 1;
            }
        }

        // Handle numerical values
        if (isdigit(ch) || ch == '.') {
            b[aaa++] = ch;
        } else if ((ch == ' ' || ch == '\n' || ch == ';') && aaa != 0) {
            b[aaa] = '\0';
            aaa = 0;
            numerics.push_back(string(b));
        }

        // Handle keywords and identifiers
        if (isalnum(ch)) {
            buffer[j++] = ch;
        } else if ((ch == ' ' || ch == '\n' || strchr("+-*/=><;,(){}[]'", ch)) && j != 0) {
            buffer[j] = '\0';
            j = 0;

            if (isKeyword(buffer)) {
                keywords.push_back(buffer);
            } else {
                string id(buffer);
                if (find(identifiers.begin(), identifiers.end(), id) == identifiers.end()) {
                    identifiers.push_back(id);
                }
            }
        }
    }

    fin.close();

    cout << "Keywords: ";
    for (size_t i = 0; i < keywords.size(); ++i) {
        if (i == keywords.size() - 1) {
            cout << keywords[i] << "\n";
        } else {
            cout << keywords[i] << ", ";
        }
    }

    cout << "Identifiers: ";
    for (size_t i = 0; i < identifiers.size(); ++i) {
        if (i == identifiers.size() - 1) {
            cout << identifiers[i] << "\n";
        } else {
            cout << identifiers[i] << ", ";
        }
    }

    cout << "Math Operators: ";
    for (size_t i = 0; i < math_ops.size(); ++i) {
        if (i == math_ops.size() - 1) {
            cout << math_ops[i] << "\n";
        } else {
            cout << math_ops[i] << ", ";
        }
    }

    cout << "Logical Operators: ";
    for (size_t i = 0; i < logical_ops.size(); ++i) {
        if (i == logical_ops.size() - 1) {
            cout << logical_ops[i] << "\n";
        } else {
            cout << logical_ops[i] << ", ";
        }
    }

    cout << "Numerical Values: ";
    for (size_t i = 0; i < numerics.size(); ++i) {
        if (i == numerics.size() - 1) {
            cout << numerics[i] << "\n";
        } else {
            cout << numerics[i] << ", ";
        }
    }

    cout << "Others: ";
    for (size_t i = 0; i < others.size(); ++i) {
        if (i == others.size() - 1) {
            cout << others[i] << "\n";
        } else {
            cout << others[i] << " ";
        }
    }

    return 0;
}
