#include <vector>
#include <iostream>
using namespace std;

void  encode(vector<int> &u) {
	int* temp = new int[u.size()/2];
	int* temp2 = new int[u.size() / 2];
	int m = log2(u.size());
	int N;
	int b;
	int position;
	for (int i = 0; i < m; i++) {
		N = pow(2, m - i);
		b = pow(2, i);
		for (int j = 0; j < b; j++) {
			position = j*N;
			for (int l = 0; l < N / 2; l++) {
				u[2*l+position] = u[2*l+position] ^ u[2*l+1+position];
				//u[position + l] = u[position + l] ^ u[position + N / 2 + l];
				temp[l] = u[2 * l + 1 + position];
				temp2[l] = u[2 * l + position];
			}
			for (int l = 0; l < N / 2; l++) {
				u[position + l] = temp2[l];
				u[position + N / 2 + l] = temp[l];
			}
		}
	}
	delete[] temp;
	delete[] temp2;
}

/*
long double* encode(vector<int> &u) {
	if (u.size() == 1) {
		return 0;
	}
	else {
		vector<int> s1(u.size() / 2);
		vector<int> s2(u.size() / 2);
		for (int i = 0; i < u.size() / 2; i++) {
			s1[i] = u.at(2 * i) ^ u.at(2 * i + 1);
			s2[i] = u.at(2 * i + 1);
		}
		encode(s1);
		encode(s2);
		int i;
		long double* x = new long double[u.size()];
		for (i = 0; i < s1.size(); i++) {
			x[i] = s1[i];
			//}
			//for (i = 0; i < s2.size(); i++) {
			x[s1.size() + i] = s2[i];
		}
		/*if (u.size() == 8) {
		vector<int> res(u.size());
		res[0] = u[0];
		res[4] = u[1];
		res[2] = u[2];
		res[6] = u[3];
		res[1] = u[4];
		res[5] = u[5];
		res[3] = u[6];
		res[7]= u[7];
		cout << "res";
		for (int i = 0; i < u.size(); i++) {
		cout << res.at(i);
		}
		}
		cout << endl;
		return x;
	}
}



int k = 1;
int width = 3;
unsigned int xx = 1;
unsigned y = 0;
unsigned mask = (1 << k) - 1;
for (int i = 0; i<width; ++i)
{
y <<= k;
y |= xx & mask;
xx >>= k;
}

*/

