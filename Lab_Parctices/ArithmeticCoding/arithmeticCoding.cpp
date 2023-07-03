#include <bits/stdc++.h>
using namespace std;
unordered_map<char, pair<double, double>>Range;


double Encoding()
{
  ifstream en_in("input.txt", ios:: in);
  ofstream en_out("encode.txt", ios::out);

  double low = 0, high = 1.0, range = 1.0;
  char ch;

  while(en_in.get(ch) && !en_in.eof()){
    high = low + range * Range[ch].second;
    low = low + range * Range[ch].first;
    range = high - low;
  }

  double codeword = (high + low) / 2;

  en_out << codeword ;
  

  en_in.close();
  en_out.close();

  cout<<"Done1!";
  return codeword;

}

void Decoding(double codeword)
{
  ofstream dec_out("decode.txt", ios::out);

  double low, high, range;
  char s;

  do{
    for(auto it: Range){
      if(codeword >= it.second.first && codeword < it.second.second)
      {
        s = it.first;
        low = it.second.first;
        high = it.second.second;
        range = high - low;
        codeword = (codeword - low) / range;
        break;
      }
    }
    dec_out.put(s);

  } while(s != '$');

  dec_out.close();

  cout<<"Done2!";


}


int main()
{
  ifstream fin("input.txt", ios::in);

  unordered_map<char, int> freq, mark;
  char ch;
  vector<char>v;

  while (fin.get(ch) && !fin.eof())
  {
    v.push_back(ch);
    freq[ch]++;
    if(ch == '$') break;
  }
  
  double low = 0.0;
  for(auto &it: v)
  {
    double p = (double) freq[it] / (double) v.size();
    
    if(!mark[it])
    {
      Range[it] = {low, low + p};
      low += p;
      mark[it] = 1;
    }
  }

  // for(auto x: Range){
  //   cout<< x.first << "==" << x.second.first << '|' << x.second.second<<endl;
  // }

  // Enncoding.....
  double val = Encoding();

  cout<< val<< endl;

  // Decoding....

  Decoding(val);


  
  return 0;

}