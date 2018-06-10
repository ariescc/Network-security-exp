#define LOCAL
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

string lower_letter = "abcdefghijklmnopqrstuvwxyz";
string upper_letter = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main()
{

    // read the key from the user
    int key;
    bool flag = false; // plaintext
    cin >> key;

    // read the plaintext from the user

    #ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    #endif // LOCAL

    string text;

    while(getline(cin, text)) {
        for(int i = 0; i < text.length(); i++) {
            if(text[i] != '\r' && text[i] != '\n' &&
               text[i] != ' ') {
                if(text[i] > 'a' && text[i] < 'z') {
                    if(key >= 0) {
                        cout << lower_letter[(text[i]-'a'+key)%26];
                    }
                    else {
                        cout << lower_letter[(text[i]-'a'+26+key)%26];
                    }

                }
                else if(text[i] > 'A' && text[i] < 'Z') {
                    if(key >= 0) {
                        cout << upper_letter[(text[i]-'A'+key)%26];
                    }
                    else {
                        cout << upper_letter[(text[i]-'A'+26+key)%26];
                    }
                }
               }
            else {
                cout << text[i];
            }
        }
    }

    return 0;
}
