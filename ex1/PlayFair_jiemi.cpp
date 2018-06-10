#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include<vector>


using namespace std;

int main()
{

    string key;
    cin >> key;

    string plaintext;
    cin.get();
    getline(cin,plaintext);


    char a[5][5];
    string upper_list = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int flag, cnt;
    vector<char> str;

    for(int i = 0; i < key.length(); i++){
        flag = 0;
        for(int j = 0; j < str.size(); j++){
            if(key[i] == str[j]){
                flag = 1;
                continue;
            }
        }
        if(flag == 0){
            if(key[i] == 'J'){
                int cnt = 0;
                for(int t = 0; t < str.size(); t++){
                    if(str[t] == 'I'){
                        cnt = 1;
                        continue;
                    }
                }
                if(cnt == 0) str.push_back('I');
            }
            else str.push_back(key[i]);
        }
    }

    while(str.size() < 25){
        for(int i = 0; i < upper_list.length(); i++){
            int flag = 0;
            for(int j = 0; j < str.size(); j++){
                if(upper_list[i] == str[j]){
                    flag = 1;
                    continue;
                }
            }
            if(flag == 0) {
                if(upper_list[i] == 'J'){
                    cnt = 0;
                    for(int t = 0; t < str.size(); t++){
                        if(str[t] == 'I'){
                            cnt = 1;
                            continue;
                        }
                    }
                    if(cnt == 0) str.push_back('I');
                }
                else str.push_back(upper_list[i]);
            }

        }
    }

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            a[i][j] = str[5*i + j];
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }

    vector<string> last;
    string res = "";
    for(int i = 0; i < plaintext.size(); i++){
        if(plaintext[i] == 'J') plaintext[i] == 'I';
    }

    for(int i = 0; i < plaintext.size(); i++){
       if(plaintext[i] != ' '){
          res += plaintext[i];
       }
       else{
        if(res.size()%2 == 0){
            last.push_back(res);
            res = "";
        }
        else{
            string res1 = "";
            for(int j = 0; j < res.size()-1; j++){
                res1 += res[j];
            }
            res1 = res1 + res[res.size() - 1] + 'X';
            last.push_back(res1);
            res = "";
        }
       }
       if(i == plaintext.size()-1){
        if(res.size()%2 == 0){
            last.push_back(res);
            res = "";
        }
        else{
            string res1 = "";
            for(int j = 0; j < res.size()-1; j++){
                res1 += res[j];
            }
            res1 = res1 +'X' + res[res.size() - 1];
            last.push_back(res1);
            res = "";
        }
       }
   }

   int m1,n1,m2,n2;
   for(int i = 0; i < last.size(); i++){
    for(int j = 0; j < last[i].length()/2; j++){
        for(int m = 0; m <5; m++){
            for(int n = 0; n < 5; n++){
                if(a[m][n] == last[i][j*2]){
                    m1 = m;
                    n1 = n;
                }
                if(a[m][n] == last[i][j*2 + 1]){
                    m2 = m;
                    n2 = n;
                }

            }
        }
        if(m1 == m2 && n1 != n2){
            cout<<a[m1][(n1+1)%5 ]<<a[m2][(n2+1)%5]<<" ";
        }
        if(n1 == n2&& m1 != m2){
            cout<<a[(m1+1)%5][n1]<<a[(m2+1)%5][n2]<<" ";
        }
        if(n1 != n2 && m1!= m2){
            if(m1 < m2){
                cout<<a[m1][n2]<<a[m2][n1]<<" ";
            }
            else cout<<a[m2][n1]<<a[m1][n2]<<" ";
        }

    }
   }
   cout<<endl;

    return 0;



}
