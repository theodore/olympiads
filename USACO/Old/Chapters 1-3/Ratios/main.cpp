/*
PROB:ratios
LANG:C++
*/
#include <iostream>
#pragma warning(disable:4996)

using namespace std;

int mix[4][3];
int output_sum, output[4];

int main(){
	freopen("ratios.in" ,"r", stdin);
	freopen("ratios.out", "w", stdout);
	for (int i=0; i<4; ++i)
		for (int j=0; j<3; ++j)
			scanf("%d", &mix[i][j]);
	////////////input above//////////

	bool good = false;
	int f[4];
	for (f[0]=0; f[0]<100; ++f[0])
		for (f[1]=0; f[1]<100; ++f[1])
			for (f[2]=0; f[2]<100; ++f[2]){
				if (!f[0] && !f[1] && !f[2])
					continue;
				int ans[3] = {0};
				for (int i=1; i<4; ++i)
					for (int j=0; j<3; ++j)
						ans[j] += f[i-1] * mix[i][j];
				int sum = 0, div0, div1, div2;
				//check ans
				for (int i=0; i<3; ++i){
					if (mix[0][i] == 0)
						if (ans[i] == 0)
							continue;
						else
							goto next;
					if (ans[i] % mix[0][i])
						goto next;
				}
				div0 = mix[0][0] ? ans[0] / mix[0][0] : ans[0] ? -2 :-1;
				div1 = mix[0][1] ? ans[1] / mix[0][1] : ans[1] ? -2 :-1;
				div2 = mix[0][2] ? ans[2] / mix[0][2] : ans[2] ? -2 :-1;
				if (div0 == -2 || div1 == -2 || div2 == -2)
					continue;
				if ((!(div0 == -1 || div1 == -1) && div0 != div1) || (!(div0 == -1 || div2 == -1) && div0 != div2) || (!(div2 == -1 || div1 == -1) && div1 != div2))
					continue;
				f[3] = div0!=-1 ? div0 : div1!=-1 ? div1 : div2!=-1 ? div2 : 0;
				for (int i=0; i<4; ++i)
					sum += f[i];
				if (!good || sum < output_sum){
					good = true;
					output_sum = sum;
					for (int i=0; i<4; ++i)
						output[i] = f[i];
				}
next:;
			}
	if (good)
		printf("%d %d %d %d\n", output[0], output[1], output[2], output[3]);
	else
		printf("NONE\n");
	return 0;
}
