//============================================================================
// Name        : DES.cpp
// Author      : seif adel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <bits/stdc++.h>
#include <bitset>
using namespace std;
int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                             60, 52, 44, 36, 28, 20, 12, 4,
                             62, 54, 46, 38, 30, 22, 14, 6,
                             64, 56, 48, 40, 32, 24, 16, 8,
                             57, 49, 41, 33, 25, 17, 9, 1,
                             59, 51, 43, 35, 27, 19, 11, 3,
                             61, 53, 45, 37, 29, 21, 13, 5,
                             63, 55, 47, 39, 31, 23, 15, 7 };
int expansion_perm[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
                      6, 7, 8, 9, 8, 9, 10, 11,
                      12, 13, 12, 13, 14, 15, 16, 17,
                      16, 17, 18, 19, 20, 21, 20, 21,
                      22, 23, 24, 25, 24, 25, 26, 27,
                      28, 29, 28, 29, 30, 31, 32, 1 };
int perm[32] = { 16, 7, 20, 21,
                    29, 12, 28, 17,
                    1, 15, 23, 26,
                    5, 18, 31, 10,
                    2, 8, 24, 14,
                    32, 27, 3, 9,
                    19, 13, 30, 6,
                    22, 11, 4, 25 };
int final_perm[64] = { 40, 8, 48, 16, 56, 24, 64, 32,
                          39, 7, 47, 15, 55, 23, 63, 31,
                          38, 6, 46, 14, 54, 22, 62, 30,
                          37, 5, 45, 13, 53, 21, 61, 29,
                          36, 4, 44, 12, 52, 20, 60, 28,
                          35, 3, 43, 11, 51, 19, 59, 27,
                          34, 2, 42, 10, 50, 18, 58, 26,
                          33, 1, 41, 9, 49, 17, 57, 25 };
int perm_choice1[56] = { 57, 49, 41, 33, 25, 17, 9,
                     1, 58, 50, 42, 34, 26, 18,
                     10, 2, 59, 51, 43, 35, 27,
                     19, 11, 3, 60, 52, 44, 36,
                     63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                     14, 6, 61, 53, 45, 37, 29,
                     21, 13, 5, 28, 20, 12, 4 };
int perm_choice2[48] = { 14, 17, 11, 24, 1, 5,
                         3, 28, 15, 6, 21, 10,
                         23, 19, 12, 4, 26, 8,
                         16, 7, 27, 20, 13, 2,
                         41, 52, 31, 37, 47, 55,
                         30, 40, 51, 45, 33, 48,
                         44, 49, 39, 56, 34, 53,
                         46, 42, 50, 36, 29, 32 };


string HexToBinary(string s)
{
	map<char, string> mp;
	mp['0'] = "0000";
	mp['1'] = "0001";
	mp['2'] = "0010";
	mp['3'] = "0011";
	mp['4'] = "0100";
	mp['5'] = "0101";
	mp['6'] = "0110";
	mp['7'] = "0111";
	mp['8'] = "1000";
	mp['9'] = "1001";
	mp['A'] = "1010";
	mp['B'] = "1011";
	mp['C'] = "1100";
	mp['D'] = "1101";
	mp['E'] = "1110";
	mp['F'] = "1111";
	string res="";
	for(int i=0;i<s.length();i++)
	{
		res+=mp[s[i]];
	}
	return res;
}
string BinaryToHex(string s)
{
    map<string, string> mp;
    mp["0000"] = "0";
    mp["0001"] = "1";
    mp["0010"] = "2";
    mp["0011"] = "3";
    mp["0100"] = "4";
    mp["0101"] = "5";
    mp["0110"] = "6";
    mp["0111"] = "7";
    mp["1000"] = "8";
    mp["1001"] = "9";
    mp["1010"] = "A";
    mp["1011"] = "B";
    mp["1100"] = "C";
    mp["1101"] = "D";
    mp["1110"] = "E";
    mp["1111"] = "F";
    string hex = "";
    for (int i = 0; i < s.length(); i += 4) {
        string ch = "";
        ch += s[i];
        ch += s[i + 1];
        ch += s[i + 2];
        ch += s[i + 3];
        hex += mp[ch];
    }
    return hex;
}
string left_shift(string k, int shifts)
{
    string s = "";
    for (int i = 0; i < shifts; i++) {
        for (int j = 1; j < 28; j++) {
            s += k[j];
        }
        s += k[0];
        k = s;
        s = "";
    }
    return k;
}
string XOR(string x,string y)
{
	string res="";
	for(int i=0;i<x.length();i++)
	{
		if(x[i]==y[i])
			res+="0";
		else
			res+="1";
	}
	return res;
}
string permutation(string s,int*arr,int n)
{
	string res="";
	for(int i=0;i<n;i++)
	{
		res+=s[arr[i]-1];
	}
	return res;
}
int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;

        dec_value += last_digit * base;

        base = base * 2;
    }

    return dec_value;
}
int decimalToBinary(int N)
{

    // To store the binary number
	unsigned long long B_Number = 0;
    int cnt = 0;
    while (N != 0) {
        int rem = N % 2;
        unsigned long long c = pow(10, cnt);
        B_Number += rem * c;
        N /= 2;

        // Count used to store exponent value
        cnt++;
    }

    return B_Number;
}
string S_Box(string s)
{
	int sBox[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
	                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
	                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
	                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 },
	                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
	                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
	                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
	                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 },

	                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
	                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
	                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
	                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 },
	                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
	                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
	                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
	                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 },
	                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
	                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
	                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
	                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 },
	                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
	                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
	                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
	                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 },
	                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
	                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
	                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
	                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 },
	                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
	                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
	                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
	                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } };
	string groups[8]={"","","","","","","",""};
	int count=0;
	for(int i=0;i<48;i+=6)
	{
		groups[count]=s.substr(i,6);
		count++;
	}
	string op="";
	for(int i=0;i<8;i++)
	{
		string col=groups[i].substr(1,4);
		string row="";
		row+=groups[i][0];
		row+=groups[i][5];
		int col_int=stoi(col);
		int row_int=stoi(row);
		col_int = binaryToDecimal(col_int);
		row_int = binaryToDecimal(row_int);
		int val=sBox[i][row_int][col_int];
		op += char(val / 8 + '0');
		val = val % 8;
		op += char(val / 4 + '0');
		val = val % 4;
		op += char(val / 2 + '0');
		val = val % 2;
		op += char(val + '0');
	}
	return op;
}

vector<string> generate_keys(string key)
{
	vector<string>left_shift_outputs;
	key = HexToBinary(key);
	key = permutation(key, perm_choice1, 56);
	string combine=key;
	string left = combine.substr(0, 28);
	string right = combine.substr(28, 28);
	for(int i=0;i<16;i++)
	{
		if(i==0 || i==1 || i==8 || i==15)
		{
			// Shifting
			left = left_shift(left, 1);
			right = left_shift(right, 1);
		}
		else
		{
			// Shifting
			left = left_shift(left, 2);
			right = left_shift(right, 2);
		}
		combine =left+right;
		left_shift_outputs.push_back(combine);
	}
	vector<string>result;
	for(int i=0;i<16;i++)
	{
		result.push_back(permutation(left_shift_outputs[i],perm_choice2,48));
	}
	return result;
}
string All_Rounds(string plain_text,vector<string>keys)
{
	plain_text=HexToBinary(plain_text);
	plain_text = permutation(plain_text,initial_perm,64);
	string left = plain_text.substr(0,32);
	string right = plain_text.substr(32,32);
	for(int i=0;i<16;i++)
	{
		string temp_right=right;
		right=permutation(right,expansion_perm,48);
		right=XOR(right,keys[i]);
		right = S_Box(right);
		right = permutation(right,perm,32);
		right = XOR(left,right);
		left = temp_right;
	}
	string temp=left;
	left=right;               // swap phase
	right=temp;
	string result=left+right;
	result = permutation(result,final_perm,64);
	result = BinaryToHex(result);
	return result;
}

int main() {

	string pt, key;
	int choice;
	cout<<"enter 1 to encryption or 2 to decryption";
	cin>>choice;
	vector<string>keys;
	if(choice==1)
	{
		cout<<"Enter key(in hexadecimal): ";
		cin>>key;
		cout<<"Enter plain text(in hexadecimal): ";
		cin>>pt;
		keys=generate_keys(key);
		string cipher=All_Rounds(pt,keys);
		cout<<"the cipher text is : "<<cipher<<endl;
	}
	else if(choice==2)
	{
		cout<<"Enter key(in hexadecimal): ";
		cin>>key;
		cout<<"Enter cipher text(in hexadecimal): ";
		cin>>pt;
		keys=generate_keys(key);
		reverse(keys.begin(), keys.end());
		string message=All_Rounds(pt,keys);
		cout<<"the encrypted data is :"<<message;
	}
	else
	{
		cout<<"wrong choice";
	}
	return 0;
}
