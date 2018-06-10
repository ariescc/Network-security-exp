#include <iostream>
#include <deque>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <string.h>
#include <cmath>

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
    deque<char> que;

    string plaintext;
    getline(cin, plaintext);

    string key;
    cin >> key;

    // 处理字符串
    for(int i = 0; i < plaintext.length(); i++) {
        if(plaintext[i] == ' ') continue;
        if(!i) que.push_back(plaintext[i]);
        else {
            char ch = que.back();
            if(plaintext[i] == ch) que.push_back('X');
            que.push_back(plaintext[i]);
        }
    }

    /*while(!que.empty()) {
        cout << que.front();
        que.pop_front();
    }*/

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

    //cout << k << " " << r << endl;
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

    deque<char> result; // 存储解密结果

    while(!que.empty()) {
        char ch1 = que.front(); que.pop_front();
        char ch2 = que.front(); que.pop_front();
        // calutate cooderative
        grid(mp, ch1, x, y);
        int first_x = x, first_y = y;
        grid(mp, ch2, x, y);
        int second_x = x, second_y = y;

        // same row
        if(first_x == second_x) {
            result.push_back(mp[first_x][(first_y+4)%5]);
            result.push_back(mp[second_x][(second_y+4)%5]);
        } // same col
        else if(first_y == second_y) {
            result.push_back(mp[(first_x+4)%5][first_y]);
            result.push_back(mp[(second_x+4)%5][second_y]);
        } // others
        else {
            if(abs(second_x-first_x) < abs(second_y-first_y)) {
                result.push_back(mp[second_x][first_y]);
                result.push_back(mp[first_x][second_y]);
            }
            else {
                result.push_back(mp[first_x][second_y]);
                result.push_back(mp[second_x][first_y]);
            }
        }
    }

    // 将X处理掉
    for(int i = 0; i < result.size(); i++) {
        if(result.at(i) != 'X') cout << result.at(i);
        else {
            // 判断前后是否相同
            if(result.at(i-1) != result.at(i+1)) cout << 'X';
        }
    }
    cout << endl;
    return 0;
}