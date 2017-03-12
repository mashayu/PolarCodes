#include <vector>
#include <iostream>
#include <set>
#include <fstream>
#include <functional>
#include "SeqDecoder.h"
#include "decoder.h"
#include "header_func.h"
#include <chrono>
#include <random>
#include <math.h>
#include <queue> 
using namespace std;
typedef pair<int, int> P;
int main(int argc, char** argv) {
	
	int n = atoi(argv[1]);
	int k = atoi(argv[2]);
	int L = atoi(argv[3]);
	int iteration_count = atoi(argv[4]);
	double SNR =0;//atoi(argv[5]);
	long double epsilon = 0.5;
	long double dispersion;
	long double sigma;
	double E_s = 1;
	set<int> frozen;
//	int* input;
	double h = 0.5;
	int* random_gen = new int[k];					// random vector
	int error_count = 0;
	vector<int> cw_frozen(n);					//word with frozen symbols
	//long double *ccw_frozen = new long double[n];
	//long double *x = new long double[n];					// codeword
	int *x = new int[n];
	long double *x2 = new long double[n];	// noisy codeword;
	int flag = 0;							// for error count
	int index = 0;							// for making symbols frozen
	int* out;								//word from decoder
	int theta = 1024;
	int g;
	double* P_j = new double[n];
	while (SNR <=3) {
		dispersion = E_s * n / (2 * k* pow(10, (SNR / 10)));
		sigma = sqrt(dispersion);
		SNR = SNR + h;
		//cTransform(epsilon, n, n - k, &frozen);		//find frozen symbols
		error_count = 0;
		std::mt19937 generator;
		std::uniform_int_distribution<int> distribution(0, 1);
		meanCount(n, dispersion, P_j, n - k, &frozen);
		//meanCount(n, dispersion, P_j);
		SeqDecoder decoder(L, n, frozen, dispersion, P_j, theta);
		//decoder dec(L, n, frozen, dispersion);
		for (g = 0; g < iteration_count; g++) {
			
			flag = 0;
			if (error_count == 20) {
				cout << SNR - h<<" "<< (double)20/g;
				cout << endl;
				break;
			}
			for (int i = 0; i < k; i++) {
				random_gen[i] = distribution(generator);		//random generator
			}

			
			index = 0;
			for (int i = 0; i < n; i++) {
				if (frozen.find(i) != frozen.end())
					cw_frozen[i] = 0;
				else {
					cw_frozen[i] = random_gen[index];
					index++;
				}
			}

			encode(cw_frozen);

			for (int i = 0; i < n; i++)
			x[i] = -2 * cw_frozen[i] + 1;
			AWGN(x, x2, sigma, n);					//make some noise there
			out = decoder.decode(x2);								// decoded word;
			//out = dec.decode(x2);
			for (int k = 0; k < n; k++) {
				if (out[k] != cw_frozen[k])
					flag = 1;
			}
			if (flag == 1) {
				//cout << "wrong!";
				error_count++;
			}
			//else
			//	cout << "yippie-ki-yay!";
		}
		if (g == iteration_count) {
			cout << SNR - h << " " << "0";
			cout << endl;
		}
		frozen.clear();
	}
	return 0;
}

