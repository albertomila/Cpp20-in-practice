#pragma once
#include <fstream>
#include <iostream>
#include <assert.h>
#include <vector>
#include <iterator>
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
#include <algorithm>

using namespace std;

struct OutputData;

class LongTextSorter
{
public:
	static const int BUFFER_LENGTH = 512;

public:
	LongTextSorter(const char* fileName, const char* fileNameOut);
	~LongTextSorter();

	void Sort();

private:
	void FirstPassSortBuffers();
	void FirstPassSortBuffer(const char* buffer, std::string& bufferSorted);
	void IterativePassSortBuffers();
	bool IterativePassSortBuffer();
	void FinalizeFiles();

private:
	const char* _filename = nullptr;
	const char* _filenameOut = nullptr;
	const char* _filenameTemp1 = nullptr;
	const char* _filenameTemp2 = nullptr;
	int _currentPass = 0;
};