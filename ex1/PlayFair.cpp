#define LOCAL
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

char mp[5][5]; // matrix
int _exist[26];

int x, y;

// get cooderation from mp
void grid(char mmp[5][5], char c, int &x, int &y)
{
    int flag = 0;
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            if(mmp[i][j] == c) {x = i; y = j; flag = 1; break;}
        }
        if(flag) break;
    }
}


int main()
{
    #ifdef LOCAL
    freopen("email.txt", "r", stdin);
    //freopen("ciphertext.txt", "w", stdout);
    #endif // LOCAL

    string plaintext;
    cin >> plaintext;

    string key;
    cin >> key;

    // init matrix
    int k = 0;
    int r = 0;
    for(int i = 0; i < key.length(); i++) {
        _exist[key[i]-'A'] = 1;
        if(key[i] == 'I' || key[i] == 'J') {_exist[8] = 1; _exist[9] = 1;}

        if(i > 4 && i % 5 == 0) {
            k++;
        }
        r = i % 5;
        mp[k][r] = key[i];
    }

    cout << k << " " << r << endl;
    r++;
    for(int i = 0; i < 26; i++) {
        if(i == 9) continue;
        if(!_exist[i]) {
            if(r % 5 == 0) {
                k++;
                r = 0;
            }
            mp[k][r] = 'A' + i;
            r++;
        }
    }

    // print mp
    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            cout << mp[i][j] << " ";
        }
        cout << endl;
    }


    string res = plaintext;

    if(plaintext.length() % 2) plaintext += "X";
    for(int i = 0; i < plaintext.length(); i+=2) {
        grid(mp, plaintext[i], x, y);
        int first_x = x, first_y = y;
        grid(mp, plaintext[i+1], x, y);
        int second_x = x, second_y = y;

        // same row
        if(first_x == second_x) {
            res[i] = mp[first_x][(first_y+1)%5];
            res[i+1] = mp[second_x][(second_y+1)%5];
        } // same col
        else if(first_y == second_y) {
            res[i] = mp[(first_x+1)%5][first_y];
            res[i+1] = mp[(second_x+1)%5][second_y];
        } // others
        else {
            res[i] = mp[first_x][second_y];
            res[i+1] = mp[second_x][first_y];
        }
    }

    // print result
    for(int i = 0; i < res.length(); i++) {
        cout << res[i];
    }

    return 0;
}
