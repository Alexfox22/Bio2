#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
struct maxim
{
	int count;
	int position;
	char mean;
};
struct minim
{
	int count;
	int position;
	string mean;
};
int PatternCount(string text, string pattern)
{
	int count = 0;
	int position = 0;

	while (text.find(pattern, position) != string::npos)
	{
		position = text.find(pattern, position) + 1;
		count++;
	}
	return count;
}
string FreqentWords(string text, int count)
{
	string result;
	string pattern;
	int n = text.size();
	int *mas = new int[n];
	int max = -10000;
	for (int i = 0;i < n - count + 1;i++)
	{
		pattern = text.substr(i, count);
		mas[i] = PatternCount(text, pattern);
		if (mas[i] > max)
			max = mas[i];
	}
	for (int i = 0;i < n - count + 1;i++)
	{
		if (mas[i] == max)
		{

			if (PatternCount(result, text.substr(i, count)) == 0)
			{
				result = result + text.substr(i, count) + ' ';
			}

			else
			{
				int r = text.find(text.substr(i, count));
				result.erase(r, count + 1);
				result = result + text.substr(i, count) + ' ';

			}
		}
	}
	return result;
}
void copy(int *fir, int *sec, int len)
{
	for (int i = 0;i < len;i++)
		sec[i] = fir[i];
}
void make_null(int *mas, int len)
{
	for (int j = 0;j < (len);j++)
	{
		mas[j] = 0;
		
	}
}
void make_matrix(int **mas, int strlen, int cofstr, string *str,int *change)
{
	for (int i = 0;i < (cofstr);i++)
	{
		int k = 0;
		for (int j = 0 + change[i];j < strlen + change[i];j++)
		{
			if ((str[i].substr(j, 1) == "A")) { mas[0][k]++; }
			if ((str[i].substr(j, 1) == "C")) { mas[1][k]++; }
			if ((str[i].substr(j, 1) == "G")) { mas[2][k]++; }
			if ((str[i].substr(j, 1) == "T")) { mas[3][k]++; }
			k++;
		}

	}
}
void show_matrix(int **mas, int strlen)
{
	for (int i = 0;i < 4;i++)
	{
		for (int j = 0;j < (strlen);j++)
		{
			cout << mas[i][j] << ' ';
		}
		cout << endl;
	}

}
void consensus(int **mas, int *popopo, int strlen)
{
	cout << "consensus: " << endl;
	for (int i = 0;i < strlen;i++)
	{
		int maximus = -1;
		for (int j = 0;j < (4);j++)
		{
			if (mas[j][i] > maximus)
			{
				maximus = mas[j][i];

			}
		}
		popopo[i] = maximus;
		cout << maximus << ' ';
	}
}
bool combination(int *mas, int tap, int m)
{
	int j = m - 1;
	while (j >= 0 && mas[j] == tap) j--;
	if (j < 0) return false;
	if (mas[j] >= tap)
		j--;
	mas[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		mas[k] = 1;
	return true;
}
int Hamming(string text, string pat)
{
	int count = 0;
	for (int i = 0;i < pat.length();i++)
	{
		if (text.substr(i, 1) != pat.substr(i, 1)) count++;
	}
	return count;
}
minim TotalDistance(string str, string pat,int *mas)
{
	minim min;
	min.count= INT_MAX;
	int k = INT_MAX;
	for (int i = 0;i < str.length() - pat.length()+1;i++)
	{
		mas[i] = Hamming(str.substr(i, pat.length()), pat);
		if (Hamming(str.substr(i, pat.length()), pat) < min.count)
		{
			min.count = Hamming(str.substr(i, pat.length()), pat);
			
			min.position = i;
		}
		
	}
	return min;
}
void main()
{
	int menu = -2;
	bool tried = false;
	ifstream imfile;
	imfile.open("input.txt");
	string text;
	string result;
	cout << "Press '0' to find with max " << endl;
	cout << "Press '1' to find with min " << endl;
	while ((menu != 0) && (menu != 1))
	{
		if (tried == true)
		{
			cout << "Wrong value. Please, press '0' or '1' " << endl;
		}
		cin >> menu;
		tried = true;
	}
	if (menu == 0)
	{

		string sze; 
		string cofstr;
	

			getline(imfile, sze);
			getline(imfile, cofstr);
			string *strs = new string[stoi(cofstr)];
			for (int i = 0;i < stoi(cofstr);i++)
			{
				getline(imfile, strs[i]);
				cout << strs[i] << endl;
			}
			int size = stoi(sze);  //длина мотива
			cout << size << endl;
			cout << cofstr << endl;
			int strlen = strs[0].size();
			int **mas = new int*[4];

			for (int i = 0;i < 4;i++)
			{
				mas[i] = new int[size];
			}
			for (int i = 0;i < 4;i++)
			{
				make_null(mas[i], size);
			}
			int *ch = new int[stoi(cofstr)];//массив смещений
			int *chbuf = new int[stoi(cofstr)];//массив смещений buffer
			make_null(ch, stoi(cofstr));
			make_null(chbuf, stoi(cofstr));
			int maximum = 0;
			int *d = new int[size];

			bool g = true;
				/*for (int j = 0;j < strlen - size;j++)
				{*/while (g)
				{
					make_matrix(mas, size, stoi(cofstr), strs, ch);

					cout << "bar:::::" << endl;
					cout << "chbuf: " << endl;
					for (int e = 0;e < stoi(cofstr);e++)
						cout << ch[e] << ' ';
					cout << endl;
					show_matrix(mas, size);
					consensus(mas, d, size);
					for (int l = 0;l < 4;l++)
						make_null(mas[l], size);
					/*ch[stoi(cofstr)-i-1]++;*/

					g=combination(ch, strlen - size, stoi(cofstr));

					cout << endl;
					int sumum = 0;
					for (int k = 0;k < size;k++)
					{

						sumum = sumum + d[k];

					}
					cout << "sum: " << sumum << endl;
					if (sumum > maximum)
					{
						maximum = sumum;
						copy(ch, chbuf, stoi(cofstr));

					}
				}

				cout << "maximum: " << maximum << endl;

			for (int i = 0;i < stoi(cofstr);i++)
				result = result + strs[i].substr(chbuf[i], size) + '\n';
			cout << result;

	}
	if (menu == 1)
	{
		ifstream imfile2;
		imfile2.open("input.txt");
		string buf;
		int kit = 0;
		while (imfile2)
		{
			getline(imfile2, buf);
			kit++;
		}
		imfile2.close();
		ifstream imfile;
		imfile.open("input.txt");
		string count;
		string DNK;
		string sze;
		int coun;
		minim resic;
		resic.count = INT_MAX;
			getline(imfile, sze);
			cout << sze << endl;
			int sizeofpattern=stoi(sze);
			
		/*	getline(imfile, count);
			cout << count << endl;*/
			coun = kit-2;
			string *strs = new string[coun];
			for (int i = 0;i < coun;i++)
			{
				getline(imfile, strs[i]);
				cout << strs[i] << endl;
			}
			
		int k = 0;
		int len = strs[0].length();
		int **mas = new int*[coun];
		cout << coun << "  <----coun    ";
		cout << len << "  <----len"<<endl;
		for (int i=0;i<coun;i++)
		{
			mas[i] = new int[len];
		}
		for (int i = 0;i < coun;i++)
		{
			for (int j = 0;j < len ;j++)
			{
				mas[i][j]=0;
			}

		}
		string pat;
		char *symb = new char[4];
		symb[0] = 'A';
		symb[1] = 'C';
		symb[2] = 'G';
		symb[3] = 'T';
		bool rere=true;
		string nul;
		int *comb = new int[sizeofpattern];
		for (int i = 0;i < sizeofpattern-1;i++)
			comb[i] = 1;
			comb[sizeofpattern-1] = 0;
		minim *minimus =new minim[coun];
		while (rere) 
		{
			
			rere = combination(comb, 4, sizeofpattern);
			//for (int i = 0;i < sizeofpattern;i++)
				//cout << comb[i] << "  -- ";
			//cout << endl;
			for (int k = 0;k < sizeofpattern;k++)
				pat = pat + symb[comb[k] - 1];
			//cout << "<--" << pat << "-->" << endl;
			for (int i = 0;i < coun;i++)
			{
				minimus[i] = TotalDistance(strs[i], pat, mas[i]);
			}
			int sum = 0;
			for (int i = 0;i < coun;i++)
			{
				sum=sum+minimus[i].count;
			}
			for (int i = 0;i < coun;i++)
			{
				
				for (int j = 0;j < len - sizeofpattern + 1;j++)
				{

					//cout << mas[i][j] << "  ";
				}
				if (sum < resic.count)
				{
					resic.count = sum;
					resic.mean = pat;
				}
				//cout << "| " << minimus[i].count << endl;
				
			}
			pat = nul;

		}
		cout << resic.count << "____" << resic.mean << endl;
		result = resic.mean;

	}

	ofstream exfile;
	exfile.open("output.txt");
	exfile << result;
	exfile.close();
	imfile.close();

}