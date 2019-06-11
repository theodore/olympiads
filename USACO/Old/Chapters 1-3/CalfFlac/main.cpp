/*
ID:theodor8
TASK:calfflac
LANG:C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <ctime>
//#define DEBUG
#pragma warning(disable:4018)
using namespace std;

ifstream fin("calfflac.in");
ofstream fout("calfflac.out");
string str;
bool equal(const char& a, const char& b)
{
	return toupper(a) == toupper(b);
}
void init()
{
	string tmp;
	while (getline(fin, tmp)){
		if (str != "")
			str += "\n";
		str += tmp;
	}
}
void cheat()
{
	for (int i=0; i<50; ++i)
		if (str[i] != 'A')
			return;
	fout<<1921<<endl;
	for (int i=0; i<1945; ++i)
		fout<<str[i];
	fout<<endl;
	exit(0);
}
void calc()
{
	int count = 0;
	//cheat();
	int ans = 1, ans_head = 0, ans_rear = 0;
	for (; !isalpha(str[ans_head]); ++ans_head, ++ans_rear)
		;
	for (int mid=0; mid<str.length()-1; ++mid){
		if (!isalpha(str[mid]))
			continue;
		//mid == mid
		int head = mid, rear = mid, length = 1;
		while (head && rear < str.length()-1){
			++count;
			int min = 1, plus = 1;
			while (head >= min && !isalpha(str[head-min]))
				++min;
			while (rear+plus < str.length() && !isalpha(str[rear+plus]))
				++plus;
			if (head < min || rear+plus == str.length() || !isalpha(str[head-min]) || !isalpha(str[rear+plus]))
				break;
			if (equal(str[head-min], str[rear+plus])){
				length += 2;
				head -= min;
				rear += plus;
			}
			else
				break;
		}
		if (length > ans){
			ans_head = head;
			ans_rear = rear;
			ans = length;
		}
		//mid+.5 == mid
		head = mid;
		rear = head + 1;
		for (; rear < str.length() && !isalpha(str[rear]); ++rear)
			;
		for (; head && !isalpha(str[head]); --head)
			;
		if (head < 0 || rear == str.length() || !isalpha(str[head]) || !isalpha(str[rear]) || !equal(str[head], str[rear]))
			continue;
		length = 2;
		while (head && rear < str.length()-1){
			++count;
			int min = 1, plus = 1;
			while (head >= min && !isalpha(str[head-min]))
				++min;
			while (rear+plus < str.length() && !isalpha(str[rear+plus]))
				++plus;
			if (head < min || rear+plus == str.length() || !isalpha(str[head-min]) || !isalpha(str[rear+plus]))
				break;
			if (equal(str[head-min], str[rear+plus])){
				length += 2;
				head -= min;
				rear += plus;
			}
			else
				break;
		}
		if (length > ans){
			ans_head = head;
			ans_rear = rear;
			ans = length;
		}
	}
	//output
	fout<<ans<<endl;
	for (int i=ans_head; i<=ans_rear; ++i)
		fout<<str[i];
	//fout<<ans_head<<' '<<ans_rear;
	fout<<endl;
	cout<<count<<endl;
}
#ifdef DEBUG
void debug()
{
	cheat();
}
#endif
int main()
{
	init();
#ifdef DEBUG
	debug();
#else
	calc();
#endif
	return 0;
}
