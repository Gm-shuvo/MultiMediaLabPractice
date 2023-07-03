#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

char str[1000000];

string en = "", en1 = "", decn = "";
int main()
{
  ifstream run_in, encode_in; // input object
  ofstream decode, encode;    // output object

  run_in.open("run_in.txt");
  encode.open("run_encode.txt");
  decode.open("run_decode.txt");

  run_in >> str;
  cout << str << endl;

  // Encode....
  int i = 0, j = 0;
  for (i = 0; i < str[i]; i++)
  {

    int cnt = 0;
    for (j = i; j < str[i] && str[i] == str[j]; j++)
    {
      cnt++;
    }
    i = j - 1;
    en += str[i];
    en += '(' + to_string(cnt) + ')';
  }
  encode << en << endl;
  cout << "put in Encode.txt :" + en << endl;

  // decode

  encode_in.open("run_encode.txt");
  encode_in >> en1;

  for (int i = 0; i < en1.size(); i++)
  {
    if (en1[i] == '(')
    {
      int cnt = 0;
      for (j = i + 1; j < en1.size() && en1[j] != ')'; j++)
      {
        cnt = cnt * 10 + (int)(en1[j] - '0');
      }
      while(cnt--){
        decn += en1[i - 1];
      }
    }
  }
  decode << decn << endl;
  cout << decn << endl;
  run_in.close();
  decode.close();
  encode.close();

  return 0;
}