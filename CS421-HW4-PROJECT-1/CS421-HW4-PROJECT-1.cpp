// CS 421 HW4: Multithreaded Stastistical Calculator
// Guan Ce Looa

#include <iostream>
#include <thread>
using namespace std;

void average(float *list, int size, float *result);
void minimum(float *list, int size, float *result);
void maximum(float *list, int size, float *result);
void median(float *list, int size, float *result);
void stddev(float *list, int size, float *result);

int main()
{
	// Initialize list dynamically, so that the pointer may be passed to threads
	int size;
	cout << "Enter size of list: ";
	cin >> size;
	float *list = new float[size];

	for (int i = 0; i < size; i++)
	{
		cout << "Enter number " << i + 1 << ": ";
		cin >> list[i];
	}

	// Print list
	cout << "List recieved: ";
	for (int i = 0; i < size; i++)
	{
		cout << list[i] << " ";
	}
	cout << endl;

	// Initialize array to store results of each function
	float result[5] = { 0 };

	// Initialize threads calling each function
	thread threadAvg(average, list, size, result);
	thread threadMin(minimum, list, size, result);
	thread threadMax(maximum, list, size, result);
	thread threadMed(median, list, size, result);
	thread threadSD(stddev, list, size, result);

	// Wait on threads to complete tasks
	threadAvg.join();
	threadMin.join();
	threadMax.join();
	threadMed.join();
	threadSD.join();

	//Print results
	cout << "The average value is: " << result[0] << endl;
	cout << "The minimum value is: " << result[1] << endl;
	cout << "The maximum value is: " << result[2] << endl;
	cout << "The median value is: " << result[3] << endl;
	cout << "The standard deviation is: " << result[4] << endl;

	cout << "Press ENTER to continue..." << endl;
	cin.ignore();
	cin.get();
	return 0;
}

void average(float *list, int size, float *result)
{
	float sum = 0.0;
	for (int i = 0; i < size; i++)
	{
		sum += list[i];
	}
	result[0] = sum / size;
}

void minimum(float *list, int size, float *result)
{
	result[1] = list[0];
	for (int i = 0; i < size; i++)
	{
		if (result[1] > list[i])
		{
			result[1] = list[i];
		}
	}
}

void maximum(float *list, int size, float *result)
{
	result[2] = list[0];
	for (int i = 0; i < size; i++)
	{
		if (result[2] < list[i])
		{
			result[2] = list[i];
		}
	}
}

void median(float *list, int size, float *result)
{
	float *sublist = new float[size];
	for (int i = 0; i < size; i++)
	{
		int t = list[i];
		int j = i;
		while (j > 0 && list[j - 1] > t)
		{
			sublist[j] = list[j - 1];
			j = j - 1;
		}
		sublist[j] = t;
	}
	/* Print sorted list, for debug
	cout << "List sorted: ";
	for (int i = 0; i < size; i++)
	{
		cout << sublist[i] << " ";
	}
	cout << endl;
	*/
	if (size % 2 == 0)
	{
		result[3] = (sublist[(size - 1) / 2] + sublist[size / 2]) / 2.0;
	}
	else
	{
		result[3] = sublist[size / 2];
	}
}

void stddev(float *list, int size, float *result)
{
	float sum = 0.0;
	float avg = 0.0;
	float t = 0.0;
	for (int i = 0; i < size; i++)
	{
		sum += list[i];
	}
	avg = sum / size;
	for (int i = 0; i < size; i++)
	{
		t += pow(list[i] - avg, 2);
	}
	result[4] = sqrt(t / size);
}