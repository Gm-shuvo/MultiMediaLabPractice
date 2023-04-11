#include<bits/stdc++.h>
using namespace std;

//make a node struct...
struct HuffmanNode{
  char symbol;
  int frequency;
  HuffmanNode *left, *right;

  HuffmanNode(char symbol, int freq){
    this->symbol = symbol;
    this->frequency = freq;
    left = nullptr;
    right = nullptr;
  }
};

struct CompareNodes
{
  bool operator()(HuffmanNode *lhs, HuffmanNode *rhs) const
  {
    return lhs->frequency > rhs->frequency;
  }
};

void generateCode(HuffmanNode* node, string s, unordered_map<char, string>& codes){
  if(!node)
    return;
  if(node->symbol != '\0'){
    codes[node->symbol] = s;
  }
  generateCode(node->left, s + "0", codes);
  generateCode(node->right, s + "1", codes);
}

//Encoding..
void Encoding(){
  ifstream encode_in("huffman_in.txt", ios::in);
  ofstream encode_out("huffman_encode.txt", ios::out);

  char ch;
  unordered_map<char, int> frq;
  unordered_map<char, string> codes;
  string str;
    
  while (encode_in.get(ch) && !encode_in.eof())
  {
    //cout << ch << endl;
    frq[ch] = frq[ch] + 1;
    str += ch;
  }

  priority_queue<HuffmanNode *, vector<HuffmanNode *>, CompareNodes> pq;

  for(auto& fr: frq){
    // cout << fr.first << " " << fr.second << endl;
    pq.push(new HuffmanNode(fr.first, fr.second));
  }
  
  while(pq.size() > 1){
    HuffmanNode *left = pq.top();
    pq.pop();
    HuffmanNode *right = pq.top();
    pq.pop();
    HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
    newNode->left = left;
    newNode->right = right;
    pq.push(newNode);
  }

  //Genetare code
  generateCode(pq.top(), "", codes);

  for(auto& it: str){
    encode_out << codes[it] ;
  }
  encode_out << endl;
  for(auto& it: codes){
    encode_out<<it.first<< " "<<it.second<<endl;
  }
  encode_in.close();
  encode_out.close();
}

void Decoding(){
  ifstream decode_in("huffman_encode.txt", ios::in);
  ofstream decode_out("huffman_decode.txt", ios::out);

  vector<char>ch;
  string codeWord, line;
  unordered_map<string, char> codes;
  getline(decode_in, codeWord);

  while(getline(decode_in, line)){
    char key = line[0];
    string code = line.substr(2);
    codes[code] = key;
  }

  // cout<<codeWord<<endl;

  // for(auto& c: codes){
  //   cout << c.first << " " << c.second << endl;
  // }

  string c;
  for (int i = 0; i < codeWord.size(); i++){
    c += codeWord[i];
    while(codes.find(c) == codes.end()){
      c += codeWord[++i];
    }
    decode_out << codes[c];
    cout << codes[c] << endl;
    c = "";
  }
  decode_out << endl;
}

int main()
{
  Encoding();
  Decoding();
  return 0;
}