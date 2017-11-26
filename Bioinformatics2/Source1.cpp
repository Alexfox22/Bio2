#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;
struct maxim
{
	int count;
	int position;
	char mean;
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
//int matmotive(int e,int strlen,int size)
//{
//	while (e != strlen - size)
//	{
//		e++;
//
//		return e++;
//	}
//	matmotive(e, strlen, size);
//	
//}
bool NextSet(int *a, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && a[j] == n) j--;
	if (j < 0) return false;
	if (a[j] >= n)
		j--;
	a[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1; k < m; k++)
		a[k] = 1;
	return true;
}
//bool NextSet(int *a, int n, int m)
//{
//	int j = m - 1;
//	while (a[j] == n && j >= 0) j--;
//	if (j < 0) return false;
//	if (a[j] >= n)
//		j--;
//	a[j]++;
//	if (j == m - 1) return true;
//	for (int k = j + 1; k < m; k++)
//		a[k] = a[j];
//	return true;
//}
void main()
{
	int menu = -2;
	bool tried = false;
	ifstream imfile;
	imfile.open("input.txt");
	string text;
	string res;
	cout << "Press '0' to find pattern count " << endl;
	cout << "Press '1' to find freqen words " << endl;
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
		string result;
		//if (!imfile.is_open())
		//	cout << "Cannot open'input.txt'";
		//else
		//{
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
			/*for (int i = 0;i < stoi(cofstr);i++)
			{*/
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
					g=NextSet(ch, strlen - size, stoi(cofstr));
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
				/*}*/
				cout << "maximum: " << maximum << endl;
			/*	for (int l = 0;l < i;i++)
					ch[stoi(cofstr) - l] = 0;*/
				
			/*}*/
			for (int i = 0;i < stoi(cofstr);i++)
				result = result + strs[i].substr(chbuf[i], size) + '\n';
			cout << result;
			ofstream exfile;
			exfile.open("output.txt");
			exfile << result;
		//}
	}
	if (menu == 1)
	{
		string count;

		if (!imfile.is_open())
			cout << "Cannot open'input.txt'";
		else
		{
			getline(imfile, text);
			getline(imfile, count);
		}
		res = FreqentWords(text, stoi(count));
	}
	ofstream exfile;
	exfile.open("output.txt");
	//	exfile << res;

	imfile.close();
	exfile.close();
}