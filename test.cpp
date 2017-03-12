#include <map>
#include <iostream>
using namespace std;

int Partition(map <int, int> &vector, int start, int end) {

	int i = start - 1;
	long double elem = vector[end];
	//exchange [start + index] with [end]
	for (int j = start; j <= end - 1; j++) {
		if (vector[j] <= elem) {
			//exchange [j] and [i]
			i++;
			swap(vector[j], vector[i]);
		}
	}
	//exchange [i + 1] and [end] and exchange [ i + 1 + .size()/2] and [end + .size()/2]
	swap(vector[i + 1], vector[end]);
	return i + 1;
}

void Sort(map <int, int> &vector, int start, int end) {
	if (start < end) {
		int q = Partition(vector, start, end);
		Sort(vector, start, q - 1);
		Sort(vector, q + 1, end);
	}
}
void sortTest() {
	map<int, int> mappy;

	for (int i = 0; i < 8; i++) {
		mappy.insert(pair<int, int>(i, i + 10));
	}

	mappy.at(2) = 200;
	mappy.at(5) = 0;
	Sort(mappy, 0, 7);

	for (int i = 0; i < 8; i++)
		cout << mappy.at(i) << "  ";
}

