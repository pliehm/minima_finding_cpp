/*
 * minima_finding.cpp
 *
 *  Created on: Jan 2, 2014
 *      Author: philippliehm
 */

#include <iostream>
#include <vector>
#include <time.h>
#include <stdint.h>
using namespace std;

int intensity [] = {33,32,28,23,19,19,22,27,34,37,37,38,39,43,41,37,34,29,24,23,24,31,39,44,49,51,54,
					53,43,51,45,40,33,28,26,31,37,44,52,58,61,65,65,64,60,61,56,51,44,38,35,36,45,51,62,
					60,65,67,71,71,69,68,67,61,55,49,41,37,41,47,60,69,73,78,83,84,86,85,87,84,82,72,
					65,56,47,41,49,59,70,75,80,87,85,86,89,90,89,86,86,84,75,68,56,49,49,56,65,77,
					87,89,91,91,92,89,86,87,87,84,80,73,67,63,56,46,50,55,69,77,83,88,94,92,95,94,
					92,91,91,87,81,78,77,68,66,58,48,42,48,56,62,73,82,86,90,92,91,91,92,90,94,90,
					89,88,86,79,73,66,60,51,53,56,63,71,74,77,84,83,88,86,86,83,82,80,82,79,81,74,70,
					65,60,56,50,48,42,45,53,58,61,65,66,71,76};

vector<unsigned short int> minima (vector<unsigned short int> intensity, vector<unsigned short int> waves, unsigned short int lookahead, unsigned short int delta )
{
	int mn = 1000;
	int mx = -1000;
	int x,y,mxpos,mnpos;
	vector<unsigned short int> min_peaks;
	unsigned short int length = intensity.size();
	vector<bool> dump;

	for (unsigned short int index=0; index<intensity.size(); ++index) {
		x = waves[index];
		y = intensity[index];
		if (y > mx) {
			mx = y;
			mxpos = x;
		}
		if (y < mn) {
			mn = y;
			mnpos = x;
		}
		// look for max

		if (y < (mx-delta) and (mx != 1000)){
			int biggest = *max_element(intensity.begin() + index,intensity.begin()+index + lookahead);
			if (biggest < mx) {
				mx = 1000;
				mn = 1000;
				dump.push_back(true);
				if (index + lookahead >= length){
					break;
				continue;
				}
			}

		}

		// look for min

		if (y> (mn + delta) and (mn != -1000)) {
			int smallest = *min_element(intensity.begin() + index, intensity.begin() + index + lookahead);
			if (smallest > mn) {
				min_peaks.push_back(mnpos);
				dump.push_back(false);
				mn = -1000;
				mx = -1000;
				if ((index + lookahead) >= length) {
					break;
				}
			}
		}
	}
	// this may not be needed (since "dump" should always be > 0)
	if (dump.size()>0) {
		if (not dump[0]) {
			min_peaks.erase(min_peaks.begin());
		}
	}
	return min_peaks;
}

int main (int argc, char** argv)
{
	clock_t t;

	vector<unsigned short int> vectorOne, vector_waves;

	for (long index=0; index<201; ++index) {
		try {
			vectorOne.push_back(intensity[index]);
			//cout << "Element " << index << ": " << vectorOne[index] << endl;
		}
		catch (exception& e) {
			cout << "Element " << index << ": index exceeds vector dimensions." << endl;
		}
	}
	cout << "size is: " << vectorOne.size() << endl;

	// make a vector with the wavelengths

	for (int index=0; index<201; ++index) {

		vector_waves.push_back(550+index);
	}

	/*for (unsigned int index=0; index<vector_waves.size(); ++index) {
		cout << vector_waves[index] << endl;
	}*/

	// find minima

	vector<unsigned short int > result;
	t = clock();
	result = minima(vectorOne, vector_waves,4,7);
	t = clock() -t;
	cout << "execution time is: " << t << " clicks and that is " << ((float)t)/CLOCKS_PER_SEC*1024*1280 <<" seconds" << endl;
	for (unsigned short int index = 0; index<result.size(); ++index) {
		cout << "The " << index << " minima is at: ";
		cout << result[index] << endl;
	}

	return EXIT_SUCCESS;

}
