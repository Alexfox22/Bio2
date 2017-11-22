#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
struct max
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
void bubblesort(max *x,int len)
{
	max temp;
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = i + 1; j < len; j++)
		{
			if (x[i].count < x[j].count)
			{
				temp = x[i];
				x[i] = x[j];
				x[j] = temp;
			}

		}
	}
}

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

		string size;
		string cofstr;
		if (!imfile.is_open())
			cout << "Cannot open'input.txt'";
		else
		{
			getline(imfile, size);
			getline(imfile, cofstr);
			string buf;
			for (int i = 0;i < stoi(cofstr);i++)
			{
				getline(imfile, buf);
				text = text + buf + '\n';
			}
		}
		cout << size << endl;
		cout << cofstr << endl;
		cout << text << endl;
		int strlen = text.size() / stoi(cofstr) -1;
		int **mas = new int*[4];

		string out = " ";

		for (int i = 0;i < 4;i++)
		{
			mas[i] = new int[strlen];
		}
		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < (strlen);j++)
			{
				mas[i][j] = 0;
			}
		}
		for (int i = 0;i < (strlen);i++)
		{
			for (int j = 0;j < stoi(cofstr);j++)
			{
				if ((text.substr(j*(strlen+1)+i, 1) == "A"))   mas[0][i]++;
				if ((text.substr(j*(strlen+1)+i, 1) == "C"))   mas[1][i]++;
				if ((text.substr(j*(strlen+1)+i, 1) == "G"))   mas[2][i]++;
				if ((text.substr(j*(strlen+1)+i, 1) == "T"))   mas[3][i]++;
			}

		}


		for (int i = 0;i < 4;i++)
		{
			for (int j = 0;j < (strlen);j++)
			{
				cout << mas[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		max *popopo = new max[strlen];
		cout << "maximum: ";
		for (int i = 0;i < strlen;i++)
		{
			int maximus = -10000000;
			for (int j = 0;j < (4);j++)
			{
				if (mas[j][i] > maximus)
				{
					maximus = mas[j][i];
					if (j == 0) popopo[i].mean = 'A';
					if (j == 1) popopo[i].mean = 'C';
					if (j == 2) popopo[i].mean = 'G';
					if (j == 3) popopo[i].mean = 'T';

				}
			}
			popopo[i].count = maximus;
			popopo[i].position = i;
			cout << popopo[i].count << ' ';
		}
		cout << endl;
		cout << " consen: ";
		for (int i = 0;i < strlen;i++)
		{
			cout << popopo[i].mean << ' ';
		}
		cout << endl;
		bubblesort(popopo, strlen);
		
		for (int i = 0;i < strlen;i++)
			cout << popopo[i].count << ' ';
		cout << endl;
		for (int i = 0;i < strlen;i++)
			cout << popopo[i].mean << ' ';
		cout << endl;
		bool e = false;
		for (int s = 0;s < stoi(cofstr);s++)
		{
			
			for (int i = 0;i < strlen-3;i++)
			{
				string sbuf;
				sbuf = popopo[i].mean;

				for (int j = i + 1;j < strlen-2;j++)
				{
					sbuf = sbuf+popopo[j].mean;
					for (int k = j + 1;k < strlen-1;k++)
					{
						sbuf = sbuf+popopo[k].mean;
						cout << sbuf << endl;
						if (PatternCount((text.substr(s*(strlen + 1), strlen)), sbuf) != 0) 
						{
							out = out + sbuf + ' ';
							e = true;
							break;
						}
						sbuf=sbuf.substr(0,2);
						if (e == true) break;
					}
					sbuf = sbuf.substr(0, 1);
					if (e == true) break;
				}
				if (e == true) continue;
			}
			
		}
		cout << out;
	
		//ofstream exfile;
		//exfile.open("file2.txt");
		//exfile << out;
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
	exfile << res;

	imfile.close();
	exfile.close();
}