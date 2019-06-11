#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>

#define GDR 0.381966011F
#define EPS 1e-8
#define SQR(x) ((x) * (x))

struct Pos {

	double x,y;
	Pos() {}
	Pos(double a,double b) {x = a,y = b;}
} A,B,C,D;
// A.x <= B.x

int P,Q,R;

double dist(Pos A,Pos B) {

	return (sqrt(SQR(A.x - B.x) + SQR(A.y - B.y)));
}

double L[3],X[3],Dx1,Dy1,Dx2,Dy2;

double Divide(int Dep) {

	if (Dep > 2)
	{
		Pos P1(X[1] * Dx1 + A.x,	X[1] * Dy1 + A.y);
		Pos P2(X[2] * Dx2 + C.x,	X[2] * Dy2 + C.y);
		return dist(A,P1) / P + dist(P1,P2) / R + dist(P2,D) / Q;
	}

	double x1,x2,f1,f2,l;
	double st = 0,ed = 1;
	X[Dep] = x2 = ed - GDR;
	f2 = Divide(Dep + 1);
	X[Dep] = x1 = st + GDR;
	f1 = Divide(Dep + 1);

	while (fabs(l = ed - st) > EPS)
	{
		if (f1 > f2)
		{
			st = x1;
			l = ed - st;
			x1 = x2; f1 = f2;
			X[Dep] = x2 = ed - l * GDR;
			f2 = Divide(Dep + 1);
		}
		else
		{
			ed = x2;
			l = ed - st;
			x2 = x1; f2 = f1;
			X[Dep] = x1 = st + l * GDR;
			f1 = Divide(Dep + 1);
		}
	}
	return f1;
} 



int main() {

	scanf("%lf %lf %lf %lf\n",&A.x,&A.y,&B.x,&B.y);
	scanf("%lf %lf %lf %lf\n",&C.x,&C.y,&D.x,&D.y);
	scanf("%d %d %d\n",&P,&Q,&R);

	L[1] = dist(A,B);
	L[2] = dist(C,D);
	Dx1 = B.x - A.x,Dy1 = B.y - A.y;
	Dx2 = D.x - C.x,Dy2 = D.y - C.y;

	printf("%.2lf\n",Divide(1));	
	return 0;
}
