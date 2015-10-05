#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Point.h>
#include <ctime>

using namespace std;

void printVect(vector<int> v){
	int size = v.size();
	for (int i = 0; i < size; i++){
		cout << v.at(i) << " ";
	}
}

bool isVectInOrder(vector<int>* v){
	bool result = true;
	int size = v->size();
	for (int i = 0; i < size - 1; i++){
		int j = i + 1;
		if ((*v)[i] >(*v)[j])
			return false;
	}
	return result;
}

int MAX_LINE = -1;

int createVectFromFile(string file, vector<int>& t){
	string line;
	
	ifstream arrayFile(file);

	int  count_lines = 0;
	if (arrayFile.is_open())
	{
		while (getline(arrayFile, line) && (count_lines != MAX_LINE ))
		{
			int num = atoi(line.c_str());
			t.push_back(num);
			//cout << num << '\n';
			count_lines++;
		}
		cout << "vect size is " << t.size() << endl;
		arrayFile.close();
		return 0;
	}

	else cout << "Unable to open file";

	return -1;
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
		if (left >= size - half_size) {
			v_out[i] = v_right[right];
			right++;
		}
		else{
			if ((right >= half_size) ){
				v_out[i] = v_left[left];
				left++;
			}
			else{
				if (v_right[right] < v_left[left]){
					v_out[i] = v_right[right];
					right++;
				}
				else {
					if (v_left[left] < v_right[right]){
						v_out[i] = v_left[left];
						left++;
					}
				}
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

	if (isVectInOrder(&v))
		cout << "SUCCESS! IN ORDER" << endl;
	else
		cout << "ERROR! NOT IN ORDER" << endl;

}


vector<int> CountInv(vector<int> v, long long int &num_inv){
	long long int size = v.size();
	long long int half_size = size / 2;
	long long int left_size = size - half_size;
	long long int righ_size = size - left_size;
	if (size < 1){
#if _DEBUG
		cout << "Error size is " << size << endl;
#endif
		return  v;
	}
	if (size == 1) {
#if _DEBUG
		cout << "out vector " << v[0] << endl;
#endif
		return v;
	}

#if _DEBUG
	printVect(v); cout << "--->";
#endif
	vector<int> v_out(size);
	vector<int> v_left(v.begin(), v.begin() + size - half_size);
#if _DEBUG
	printVect(v_left); cout << "----";
#endif
	vector<int> v_right(v.begin() + size - half_size, v.end());
#if _DEBUG
	printVect(v_right); cout << endl;
#endif

	v_left = CountInv(v_left, num_inv);
	v_right = CountInv(v_right, num_inv);

	//merge
	long long int left = 0;
	long long int right = 0;
	for (long long int i = 0; i < size; i++){
		if (left >= left_size) {
			v_out[i] = v_right[right];
			right++;
		}
		else{
			if ((right >= righ_size)){
				v_out[i] = v_left[left];
				left++;
			}
			else{
				if (v_right[right] < v_left[left]){
					v_out[i] = v_right[right];
					right++;
					num_inv += left_size - left ;
				}
				else {
					if (v_left[left] < v_right[right]){
						v_out[i] = v_left[left];
						left++;
					}
				}
			}
		}
	}
#if _DEBUG
	cout << "out vector ";
	printVect(v_out); cout << endl;
#endif

	return v_out;
}

void CountInvAndTest(){
	vector <int> v = { 1, 3, 5, 2, 4, 6 };
	//vector <int> v = { 5,7,3,2,4,1,6}; //-->sol 13
	cout << endl << "un-ordered vector ";
	printVect(v); cout << endl;

	long long int num = 0;
	CountInv(v, num);

	if (num == 3)
		cout << "SUCCESS! INVERSIONS NUM GOOD" << endl;
	else
		cout << "ERROR! INVERSIONS NUM NOT GOOD. Found " << num << endl;
	vector<int> t;
}

void printPoint(Point* p){
	cout << p->name <<"(" << p->x << ", " << p->y << ")" << endl;
}

void printVectorPoint(vector <Point*> vectPoint){
	int size = vectPoint.size();
	for (int i = 0; i < size; i++){
		printPoint(vectPoint.at(i));
	}
}

float brutForceMinDistSearch(vector <Point*> vectPoint, int nbPoints){
	if (nbPoints > 2){

	float minDist = Point::distanceBetweenPoints(vectPoint.at(0), vectPoint.at(1));
	int indexPoint1 = 0;
	int indexPoint2 = 1;

	for (int i = 0; i < nbPoints - 1; i++){
		for (int j = i + 1; j < nbPoints; j++){
			float tempDist = Point::distanceBetweenPoints(vectPoint.at(i), vectPoint.at(j));
			if (minDist > tempDist){
				minDist = tempDist;
				indexPoint1 = i;
				indexPoint2 = j;
			}
		}
	}

	//cout << "Min dist is " << minDist << " between : " << vectPoint.at(indexPoint1)->name << " and " << vectPoint.at(indexPoint2)->name << endl;
	return minDist;
	}
	else{
		if (nbPoints == 2){
			float result = Point::distanceBetweenPoints(vectPoint.at(0), vectPoint.at(1));
			cout << "Min dist is " << result << endl;
			return result;
		}
		else{
			cout << "Not enought elements in the vector" << endl;
			return -1;
		}
	}
}

pair<Point*, Point*> brutForceClosestPair(vector <Point*> vectPoint){
	pair<Point*, Point*> closestPair (NULL, NULL);
	int nbPoints = vectPoint.size();
	if (nbPoints > 2){

		float minDist = Point::distanceBetweenPoints(vectPoint.at(0), vectPoint.at(1));
		int indexPoint1 = 0;
		int indexPoint2 = 1;

		for (int i = 0; i < nbPoints - 1; i++){
			for (int j = i + 1; j < nbPoints; j++){
				//we don't want to compare a point with itself
				if (vectPoint.at(i)->name != vectPoint.at(j)->name){
					float tempDist = Point::distanceBetweenPoints(vectPoint.at(i), vectPoint.at(j));
					if (minDist > tempDist){
						minDist = tempDist;
						indexPoint1 = i;
						indexPoint2 = j;
					}
				}
			}
		}
		cout << "Min dist is " << minDist << " between : " << vectPoint.at(indexPoint1)->name << " and " << vectPoint.at(indexPoint2)->name << endl;
		closestPair = make_pair(vectPoint.at(indexPoint1), vectPoint.at(indexPoint2));
		return closestPair;
	}
	else{
		if (nbPoints == 2){
			closestPair = make_pair( vectPoint.at(0), vectPoint.at(1) );
			return closestPair;
		}
		else{
			cout << "Not enought elements in the vector" << endl;
			return closestPair;
		}
	}
}



void subVectorPointHalfSize(vector <Point*> vectPoint, vector<Point*>* vectLeft, vector<Point*>* vectRight){
	int size = vectPoint.size();

	int leftSize = size / 2;
	int rightSize = size - leftSize;

	vectLeft->resize(leftSize);
	vectRight->resize(rightSize);

	for (int i = 0; i < size; i++){
		if (i < leftSize){
			vectLeft->at(i) = vectPoint.at(i);
		}
		else{
			vectRight->at(i - leftSize) = vectPoint.at(i);
		}
	}
}

vector<Point*> mergeAndSortVectorPointOnX(vector<Point*> vectPoint){
	int size = vectPoint.size();
	if (size < 2) return vectPoint;

	int leftSize = size / 2;
	int rightSize = size - leftSize;

	vector<Point*> vectLeft;
	vector<Point*> vectRight;

	subVectorPointHalfSize(vectPoint, &vectLeft, &vectRight);
	vectRight = mergeAndSortVectorPointOnX(vectRight);
	vectLeft = mergeAndSortVectorPointOnX(vectLeft);

	vector<Point*> vectOut;
	vectOut.resize(size);

	int runnerLeft = 0;
	int runnerRight = 0;

	for (int i = 0; i < size; i++){
		if (runnerLeft >= leftSize){
			//vectLeft has ALL been copied already into vectOut
			vectOut.at(i) = vectRight.at(runnerRight);
			runnerRight++;
		}
		else{
			if (runnerRight >= rightSize){
				//vectRight has ALL been copied already into vectOut
				vectOut.at(i) = vectLeft.at(runnerLeft);
				runnerLeft++;
			}
			else{
				if (vectLeft.at(runnerLeft)->x <= vectRight.at(runnerRight)->x){
					vectOut.at(i) = vectLeft.at(runnerLeft);
					runnerLeft++;
				}
				else{
					vectOut.at(i) = vectRight.at(runnerRight);
					runnerRight++;
				}
			}
		}
	}

	return vectOut;
}

vector<Point*> mergeAndSortVectorPointOnY(vector<Point*> vectPoint){
	int size = vectPoint.size();
	if (size < 2) return vectPoint;

	int leftSize = size / 2;
	int rightSize = size - leftSize;

	vector<Point*> vectLeft;
	vector<Point*> vectRight;

	subVectorPointHalfSize(vectPoint, &vectLeft, &vectRight);
	vectRight = mergeAndSortVectorPointOnY(vectRight);
	vectLeft = mergeAndSortVectorPointOnY(vectLeft);

	vector<Point*> vectOut;
	vectOut.resize(size);

	int runnerLeft = 0;
	int runnerRight = 0;

	for (int i = 0; i < size; i++){
		if (runnerLeft >= leftSize){
			//vectLeft has ALL been copied already into vectOut
			vectOut.at(i) = vectRight.at(runnerRight);
			runnerRight++;
		}
		else{
			if (runnerRight >= rightSize){
				//vectRight has ALL been copied already into vectOut
				vectOut.at(i) = vectLeft.at(runnerLeft);
				runnerLeft++;
			}
			else{
				if (vectLeft.at(runnerLeft)->y <= vectRight.at(runnerRight)->y){
					vectOut.at(i) = vectLeft.at(runnerLeft);
					runnerLeft++;
				}
				else{
					vectOut.at(i) = vectRight.at(runnerRight);
					runnerRight++;
				}
			}
		}
	}

	return vectOut;
}

float min(float x, float y){
	if (x < y)
		return x;
	else
		return y; 
}

pair<Point*, Point*> closestSplitPair(vector<Point*> Px, vector<Point*> Py, float minP1P2){
	int nbPoints = Px.size();
	pair<Point*, Point*> closestPoints;
	//X is the biggest x-coordinate in the left of P
	float X = Px.at(nbPoints/2 -1)->x;
	vector<Point*> Sy;

	float leftBound = X - minP1P2;
	float rightBound = X + minP1P2;
	if (rightBound < leftBound){
		float temp = leftBound;
		leftBound = rightBound;
		rightBound = temp;
	}
	for (int i = 0; i < nbPoints; i++){
		if ((Py.at(i)->x > leftBound) && (Py.at(i)->x < rightBound)){
			Sy.push_back(Py.at(i));
		}
	}

	int sYSize = Sy.size();
	if (sYSize > 1){
		pair<Point*, Point*> closestPoints(Sy.at(0), Sy.at(1));
		float minDist = Point::distanceBetweenPoints(Sy.at(0), Sy.at(1));

		int maxInnerLoop = min(7, sYSize - 1);
		for (int i = 1; i < sYSize - 1; i++)
			for (int j = 1; j < maxInnerLoop; j++){
				float tempDist = Point::distanceBetweenPoints(Sy.at(i), Sy.at(j));
				if (tempDist < minDist){
					minDist = tempDist;
					closestPoints.first = Sy.at(i);
					closestPoints.second = Sy.at(j);
				}
			}
	}
	else{
		closestPoints.first = NULL;
		closestPoints.second = NULL;
		return closestPoints;
	}
	return closestPoints;
}


pair<Point*, Point*> closestPair(vector<Point*> Px, vector<Point*> Py){
	pair<Point*, Point*> closestPoints(NULL, NULL);
	int nbPoints = Px.size();

	/* 1. Check the stop condition */
	if (nbPoints <= 3){
		vector<Point*> P;

		P.insert(P.begin(), Px.begin(), Px.end());
		P.insert(P.begin() + nbPoints, Py.begin(), Py.end());

		closestPoints = brutForceClosestPair(P);
		return closestPoints;
	}

	/* 2. Create Qx, Qy, and Rx, Ry */
	vector <Point*> Qx;
	vector <Point*> Qy;
	vector <Point*> Rx;
	vector <Point*> Ry;

	int QxSize = nbPoints / 2;
	int QySize = nbPoints - QxSize;
	int RxSize = QxSize;
	int RySize = QySize;

	subVectorPointHalfSize(Px, &Qx, &Rx);
	subVectorPointHalfSize(Py, &Qy, &Ry);
	/*
	cout << endl << "Qx:";
	printVectorPoint(Qx);

	cout << endl << "Qy:";
	printVectorPoint(Qy);

	cout << endl << "Rx:";
	printVectorPoint(Rx);

	cout << endl << "Ry:";
	printVectorPoint(Ry);
	*/

	/* 3. Find closestPair in Qx,Qy and then in Rx,Ry*/

	pair<Point*, Point*> closestPairP1;
	pair<Point*, Point*> closestPairP2;

	closestPairP1 = closestPair(Qx, Qy);
	closestPairP2 = closestPair(Rx, Ry);

	/* 4. Check if splitPair necessary or not*/

	float minDistP1 = Point::distanceBetweenPoints(closestPairP1.first, closestPairP1.second);
	float minDistP2 = Point::distanceBetweenPoints(closestPairP2.first, closestPairP2.second);

	float minP1P2 = minDistP1;
	if (minDistP2 < minDistP1){
		minP1P2 = minDistP2;
		closestPoints = closestPairP2;
	}
	else
		closestPoints = closestPairP1;

	bool splitPoint = true;
	if ((closestPoints.first->y < Px.at(nbPoints / 2 - 1)->y) && (closestPoints.second->y < Px.at(nbPoints / 2 - 1)->y)
		&& (closestPoints.first->y < Py.at(nbPoints / 2 - 1)->y) && (closestPoints.second->y < Py.at(nbPoints / 2 - 1)->y)){
		splitPoint = false;
	}
	else
	{
		if ((closestPoints.first->y > Px.at(nbPoints / 2 - 1)->y) && (closestPoints.second->y > Px.at(nbPoints / 2 - 1)->y)
			&& (closestPoints.first->y > Py.at(nbPoints / 2 - 1)->y) && (closestPoints.second->y > Py.at(nbPoints / 2 - 1)->y)){
			splitPoint = false;
		}
	}
	/* 5. Find ClosestSplitPair if necessary*/
	if (splitPoint){
		pair<Point*, Point*> closestPairP3;
		closestPairP3 = closestSplitPair(Px, Py, minP1P2);
		if (closestPairP3.first != NULL && closestPairP3.second != NULL)
		{
			float minDistP3 = Point::distanceBetweenPoints(closestPairP3.first, closestPairP3.second);
			if (minDistP3 < minP1P2){
				closestPoints = closestPairP3;
			}
		}
	}
		
	return closestPoints;
}

pair<Point*, Point*> findClosestPair(vector<Point*> vectPoint){
	
	int nbPoints = vectPoint.size();

	//brutForceMinDistSearch(vectPoint, nbPoints);

	/* 1. Create Px and Py . Px sorts the points according to their x, Py same with y.*/
	//Create and populate Px and Py
	vector <Point*> Px;
	vector <Point*> Py;

	//Sort Px ad Py
	Px = mergeAndSortVectorPointOnX(vectPoint);
	cout << endl << "merge and sort on X" << endl;
	//printVectorPoint(Px);

	cout << endl << "merge and sort on Y" << endl;
	Py = mergeAndSortVectorPointOnY(vectPoint);
	//printVectorPoint(Py);

	pair<Point*, Point*> closestPoints = closestPair(Px, Py);
	
	cout << "Closest points are " << closestPoints.first->name << " and " << closestPoints.second->name << endl;
	return closestPoints;
}



void findClosestPairAndTest(){
	float max = 1000;
	srand(static_cast <unsigned> (time(0)));
	Point A('a', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point B('b', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point C('c', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point D('d', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point E('e', -static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point F('f', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));
	Point G('g', static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max)));

	vector<Point*> vectPoint = { &A, &B, &C, &D, &E, &F, &G };
	pair<Point*, Point*> algoPoints = findClosestPair(vectPoint);
	pair<Point*, Point*> brutForcePoints = brutForceClosestPair(vectPoint);

	if (algoPoints.first->name == brutForcePoints.first->name){
		if (algoPoints.second->name == brutForcePoints.second->name)
			cout << "CORRECT" << endl;
		else
			cout << "INCORRECT" << endl;
	}
	else{
		if (algoPoints.first->name == brutForcePoints.second->name)
			if (algoPoints.second->name == brutForcePoints.first->name)
			cout << "CORRECT" << endl;
		else
			cout << "INCORRECT" << endl;
	}
}


void subVectorIntHalfSize(vector <int> vect, vector<int>& vectLeft, vector<int>& vectRight){
	int size = vect.size();

	int leftSize = size / 2;
	int rightSize = size - leftSize;

	vectLeft.resize(leftSize);
	vectRight.resize(rightSize);

	for (int i = 0; i < size; i++){
		if (i < leftSize){
			vectLeft[i] = vect[i];
		}
		else{
			vectRight[i - leftSize] = vect[i];
		}
	}
}


void swap(vector<int>* t, int i, int j){
	if (i == j) return;

	int temp = (*t)[i];
	(*t)[i] = (*t)[j];
	(*t)[j] = temp;
}

void QuickSort(vector<int>* t, long long int first, long long int last){
	long long int size = last - first + 1;
	if (size <= 1) 
		return;
	if (size == 2){
		if ((*t)[last] < (*t)[first]){
			swap(t, first, last);
		}
		return;
	}
	
	int pivot = (*t)[first];
	long long int lastPartitionned = first + 1;
	long long int firstPartRight = first + 1;
	
	for (long long int lastPartitionned = first + 1; lastPartitionned <= last; lastPartitionned++){
		if ((*t)[lastPartitionned] < pivot){
			swap(t, lastPartitionned, firstPartRight);
			firstPartRight++;
		}
	}

	//Place pivot at its place
	if (firstPartRight != first){
		swap(t, first, firstPartRight-1);
	}

	long long int firstLeft = first;
	long long int lastLeft = firstPartRight - 2;
	long long int firstRight = firstPartRight ;
	long long int lastRight = last;
	
	QuickSort(t, firstLeft, lastLeft);
	QuickSort(t, firstRight, lastRight);

}

void QuickSortAndTest(vector<int> *t){
	long long int size = t->size();
	QuickSort(t, 0, size-1);
	if (isVectInOrder(t)){
		cout << "QUICKSORT CORRECT" << endl;
	}
	else{
		cout << "QUICKSORT INCORRECT" << endl;
	}
}

int main(int argc, char* argv[])
{
	//MergeAndSortAndTest();
	//CountInvAndTest();
	/*vector<int> t;
	long long int num = 0;
	if (!createVectFromFile("C:/IntegerArray.txt", t)){
		CountInv(t, num);
	}
	cout << "Found " << num << " inversions" << endl;*/

	//findClosestPairAndTest();

	//string file = "C:/IntegerArray10.txt";
	//string file = "C:/IntegerArray9293.txt";
	string file = "C:/IntegerArray.txt";
	vector<int> t;
	if (!createVectFromFile(file, t)){
		QuickSortAndTest(&t);
	}
	
	system("pause");
	return 0;
}

