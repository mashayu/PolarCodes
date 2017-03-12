#include <iostream>
#include <random>
#include<chrono>
#include<random>
using namespace std;
void noise(long double mean, long double sigma, int n, long double *a) {

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
	normal_distribution<long double> distribution(mean, sigma);
	for (int i = 0; i < n; i++)
		a[i] = distribution(generator);
}

void AWGN(int *original, long double *noisy, long double sigma, int length) {

	long double *gaussianNoise = new long double[length];
	noise(0, sigma, length, gaussianNoise);

	for (int i = 0; i < length; i++) {
		//cout<<"noise "<<gaussianNoise[i]<<" and codeword "<<original[i];
		noisy[i] = original[i] + gaussianNoise[i];
		//cout<<" noise codeword is "<<noisy[i]<<endl;
	}

	delete[] gaussianNoise;
}