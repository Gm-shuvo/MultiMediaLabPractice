#include <bits/stdc++.h>
using namespace std;

char str[1000];
string en = "";

int main()
{
  ifstream run_in, encode_in;
  ofstream decode, encode;

  run_in.open("run_in.txt");
  encode.open("encode.txt");
  
  run_in >> str;

  cout<< str <<endl;
  int i, j;
  for( i = 0; str[i]; i++){
    int cnt = 0;
    for( j = i; str[j] && str[i] == str[j]; j++){
      cnt++;
    }
    i = j - 1;
    en += str[i];
    en += '(' + to_string(cnt) + ')';
    
  }

  encode << en <<endl;
  cout<< "puting encod.txt" <<endl;

  //Decoding

  encode_in.open("encode.txt");
  decode.open("decode.txt");

  encode_in >> str ;

  cout << str << endl;
  string dcode;
  for( i = 0; str[i]; i++){
    if(str[i] == '('){
      int num = 0;
      for( j = i + 1; str[j] && str[j] != ')'; j++){
        num = num * 10 + (int) (str[j] - '0'); 
      }
      while(num--){
        dcode += str[i-1];
      }
      i = j + 1;
    }
  }

  decode << dcode << endl;
  cout<<"Puting decode.txt"<<endl;

  run_in.close();
  encode.close();
  decode.close();

  return 0;
}