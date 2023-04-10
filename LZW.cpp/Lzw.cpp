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
void lzw_decoding(vector<int>& output){
  //writable output file
  ofstream decode_out;
  decode_out.open("lwz_decode.txt");

  //decoding...
  unordered_map<int, string>table;
  for (int i = 0; i < 256; i++){
    string ch = "";
    ch += char(i);
    table[i] = ch;
  }

  string decode = "";
  int old = output[0], n;
  string s = table[old];
  // cout<<s<<endl;
  decode += s;
  string c = "";
  c += s[0];
  int code = 256;

  //string decode

  for (int i = 0; i < output.size() - 1; i++)
  {
    n = output[i + 1];
    if(table.find(n) == table.end()){
      s = table[old];
      s = s + c;
    }
    else{
      s = table[n];
    }
    decode += s;
    c = "";
    c += s[0];
    table[code++] = table[old] + c;
    old = n;
  }
  decode_out << decode << endl;
  cout << decode << endl;
}

int main(){
  vector<int>output = lzw_encoding();
  lzw_decoding(output);
  return 0;
}