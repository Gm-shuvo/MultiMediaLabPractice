#include<bits/stdc++.h>
using namespace std;

vector<int> lzw_encoding(){
  string str;
  ifstream encode_in;
  encode_in.open("lzw_in.txt");
  ofstream encode_out;
  encode_out.open("lzw_encode.txt");

  //Read string from file
  encode_in>>str;
  cout << str << endl;

  //Encoding...
  unordered_map<string, int>table;
  //intialize code for every character
  for (int i = 0; i < 256; i++){
    string ch = "";
    ch += char(i);
    table[ch] = i;
  }
  string p = "", c = "";
  int code = 256;
  vector<int> output_encode;
  // take p to first char
  p += str[0];
  for (int i = 0; i < str.length(); i++){
    if(i != str.length() - 1){
      c += str[i + 1];
    }
    if(table.find(p+c) != table.end()){
      p = p + c;
    }
    else{
      table[p + c] = code++;
      output_encode.push_back(table[p]);
      p = c;
    }
    c = "";
  }
  output_encode.push_back(table[p]);
  //write output on file
  string encode;
  for (auto &out : output_encode)
  {
    encode += to_string(out) + " ";
  }

  encode_out << encode << endl;
  cout << encode << endl;

  return output_encode;
}

//Decoding 
void lzw_decoding(){

}

int main(){
  vector<int>output = lzw_encoding();
  lzw_decoding();
  return 0;
}