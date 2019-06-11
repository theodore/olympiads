/*
PROB:theme
LANG:C++
*/
/*
For:
   Test 1: TEST OK [0.000 secs, 2816 KB]
   Test 2: TEST OK [0.011 secs, 2816 KB]
   Test 3: TEST OK [0.011 secs, 2816 KB]
   Test 4: TEST OK [0.000 secs, 2816 KB]
   Test 5: TEST OK [0.000 secs, 2816 KB]
   Test 6: TEST OK [0.011 secs, 2816 KB]
   Test 7: TEST OK [0.000 secs, 2816 KB]
   Test 8: TEST OK [0.000 secs, 2816 KB]
   Test 9: TEST OK [0.000 secs, 2816 KB]
   Test 10: TEST OK [0.011 secs, 2816 KB]
   Test 11: TEST OK [0.119 secs, 2816 KB]
   Test 12: TEST OK [0.140 secs, 2816 KB]
   Test 13: TEST OK [0.032 secs, 2816 KB]
   Test 14: TEST OK [0.918 secs, 2816 KB]
   Test 15: TEST OK [0.022 secs, 2816 KB]
*/
#include <iostream>

using namespace std;

int n, note[5003];

int main()
{
	freopen("theme.in", "r", stdin);
	freopen("theme.out", "w", stdout);
	scanf("%d", &n);
	int b4;
	scanf("%d", &b4);
	for (int i=0; i<n-1; ++i){
		int now;
		scanf("%d", &now);
		note[i] = now - b4;
		b4 = now;
	}

//	for (int i=0; i<n-1; ++i)
//		printf("%d ", note[i]);

	int ans = 0;//*
	for (int i=1; i<n-1; ++i){
		for (int j=i-ans-2; j>=ans; --j)
			if (note[i] == note[j] && note[i-ans] == note[j-ans]){
				int now = 1;
				for (int ip=i-1, jp=j-1; ip>j && jp>=0; --ip, --jp)
					if (note[ip] == note[jp])
						++now;
					else
						break;
				if (now > ans)
					ans = now;
			}
	}//*/
//now new solution
	printf("%d\n", ans>=4 ? ans+1 : 0);
	return 0;
}
