#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

void printVect(vector<int> v){
	int size = v.size();
	for (int i = 0; i < size; i++){
		cout << v.at(i) << " ";
	}
}

vector<int> MergeAndSort(vector<int> v){
	int size = v.size();
	int half_size = size / 2;
	if (size < 1){
		cout << "Error size is " << size << endl;
		return  v;
	}
	if (size == 1) {
		cout << "out vector " << v[0] << endl;
		return v;
	}

	printVect(v); cout << "--->";
	vector<int> v_out(size);
	vector<int> v_left(v.begin(), v.begin() + size - half_size);
	printVect(v_left); cout << "----";
	vector<int> v_right(v.begin() + size - half_size, v.end());
	printVect(v_right); cout << endl;

	v_left = MergeAndSort(v_left);
	v_right = MergeAndSort(v_right);

	//merge
	int left = 0;
	int right = 0;
	for (int i = 0; i < size; i++){
		if ((left >= size - half_size) || (v_right[right] < v_left[left])){
			v_out[i] = v_right[right];
			right++;
		}
		else{
			if ((right >= half_size) || (v_left[left] < v_right[right])){
				v_out[i] = v_left[left];
				left++;
			}
		}
	}
	cout << "out vector ";
	printVect(v_out); cout << endl;

	return v_out;
}

void MergeAndSortAndTest(){
	vector <int> v = { 38, 27, 43, 3, 9, 82, 10 };
	cout << endl << "un-ordered vector ";
	printVect(v); cout << endl;

	v = MergeAndSort(v);
	cout << endl << "ordered vector ";
	printVect(v); cout << endl;
}

int main(int argc, char* argv[])
{
	MergeAndSortAndTest();
	system("pause");
	return 0;
}

