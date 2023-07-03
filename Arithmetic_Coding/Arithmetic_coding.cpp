#include <bits/stdc++.h>
using namespace std;

unordered_map<char, pair<double, double>> Range;

double generateCodeword(double low, double high)
{
    int k = 1;
    double code = 0.0, x;

    while (code < low)
    {
        x = pow(2.0, -k);

        if (code + x <= high)
            code = code + x;

        k = k + 1;
    }

    return code;
}

double doEncoding()
{

    ifstream enc_in("./input_file.txt", ios::in);
    ofstream enc_out("./encoded_file.txt", ios::out);

    double low = 0.0, high = 1.0, range = 1.0;
    char ch;

    while (enc_in.get(ch) && !enc_in.eof())
    {
        high = low + range * Range[ch].second;
        low = low + range * Range[ch].first;
        range = high - low;
    }

    // double codeword = generateCodeword(low , high);
    double codeword = (low + high) / 2;

    enc_out << codeword;

    enc_in.close();
    enc_out.close();

    return codeword;
}

void doDecoding(double codeword)
{

    // FILE *dec_in = fopen("./encoded_file.txt","r");
    ofstream dec_out("./decoded_file.txt", ios::out);

    double low, high, range;
    char s;

    do
    {
        for (auto &itr : Range)
        {
            if (itr.second.first <= codeword && codeword < itr.second.second)
            {
                s = itr.first;
                low = itr.second.first;
                high = itr.second.second;
                range = high - low;
                codeword = (codeword - low) / range;
                break;
            }
        }
        dec_out.put(s);
    } while (s != '$');

    dec_out.close();
}

int main()
{

    ifstream fin("./input_file.txt", ios::in);
    vector<char> s;
    char ch;

    unordered_map<char, int> freq, mark;
    double low = 0.0;

    while (fin.get(ch) && !fin.eof())
    {
        s.push_back(ch);
        freq[ch] = freq[ch] + 1;
        if (ch == '$')
            break;
    }

    for (auto &itr : s)
    {
        double p = (double)freq[itr] / (double)s.size();
        // cout<<p<<endl;
        if (!mark[itr])
        {
            Range[itr] = {low, low + p};
            low += p;
            mark[itr] = 1;
        }
    }

    // for(auto x: Range){
    // cout<< x.first << "==" << x.second.first << '|' << x.second.second<<endl;
    // }

    double value = doEncoding();
    doDecoding(value);

    fin.close();

    return 0;
}