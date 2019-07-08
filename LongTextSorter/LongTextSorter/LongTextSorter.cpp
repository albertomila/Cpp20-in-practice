#include "stdafx.h"
#include "LongTextSorter.h"
#include <vector>
#include "Debug.h"
#include <thread>
#include <queue>

void split(const string& s, char c, std::vector<string>& vector_out) 
{
	string::size_type i = 0;
	string::size_type j = s.find(c);

	while (j != string::npos)
	{
		vector_out.push_back(s.substr(i, j - i));
		i = ++j;
		j = s.find(c, j);

		if (j == string::npos)
		{
			vector_out.push_back(s.substr(i, s.length()));
		}
	}
}

bool SortTwoWordsPredicate(const std::string& word1, const std::string& word2)
{
	int comparison = word1.compare(word2);
	if (comparison < 0)
	{
		return true;
	}
	else if (comparison == 0)
	{
		return false;
	}
	else
	{
		return false;
	}
}

bool RemoveCharacter(const char& value)
{
	return value == '.'
		|| value == ','
		|| value == '\n'
		|| value == '\t'
		|| value == '\0';
}

int FindLastIndexLastWord(char* buffer)
{
	int index = LongTextSorter::BUFFER_LENGTH - 2;
	char currentChar = '\n';

	while (currentChar != '\0'
		&& currentChar != ' '
		&& index > 0)
	{
		currentChar = buffer[index];
		--index;
	}

	return index;
}

void Trim(string& s)
{
	size_t p = s.find_first_not_of(" \t");
	s.erase(0, p);

	p = s.find_last_not_of(" \t");
	if (string::npos != p)
	{
		s.erase(p + 1);
	}
}


LongTextSorter::LongTextSorter(const char* fileName, const char* filenameOut)
	:_filename(fileName)
	,_filenameOut(filenameOut)
	,_filenameTemp1("Temp1.txt")
	,_filenameTemp2("Temp2.txt")
	, _currentPass(1)
{
	assert(fileName != NULL);
}

LongTextSorter::~LongTextSorter()
{

}

void LongTextSorter::Sort()
{
	FirstPassSortBuffers();
}

void LongTextSorter::FirstPassSortBuffers()
{
	ifstream inputFile;
	inputFile.open(_filename, ios::in | ios::ate);
	const int fileSizeBytes = static_cast<int>(inputFile.tellg());

	ofstream outputFile;
	outputFile.open(_filenameTemp1, ios::out | ios::trunc);

	//one thread to read the chunks
	//another thread to write the data

	int nextIndex = 0;
	while (nextIndex <= fileSizeBytes)
	{
		char buffer[BUFFER_LENGTH] = { '\0' };

		int readBufferSize = BUFFER_LENGTH;
		if (readBufferSize > fileSizeBytes - nextIndex)
		{
			readBufferSize = fileSizeBytes - nextIndex;
			if (readBufferSize < 0)
			{
				readBufferSize = 0;
			}
		}

		inputFile.seekg(nextIndex, ios::beg);
		inputFile.read(buffer, readBufferSize);

		int bufferLastWordIndex = FindLastIndexLastWord(buffer);
		nextIndex += bufferLastWordIndex;

		buffer[bufferLastWordIndex+1] = '\0';

		std::string bufferSorted;
		FirstPassSortBuffer(buffer, bufferSorted);
		outputFile.write(bufferSorted.c_str(), bufferSorted.length());
	}

	inputFile.close();
	outputFile.close();

	IterativePassSortBuffers();

	FinalizeFiles();
}

void LongTextSorter::FinalizeFiles()
{
	bool leftToRight = _currentPass % 2 != 0;
	const char* fileNameSource = leftToRight ? _filenameTemp1 : _filenameTemp2;
	const char* fileNameTarget = !leftToRight ? _filenameTemp1 : _filenameTemp2;
	
	int result = 0;

	ifstream fileSorted(fileNameTarget);
	if(fileSorted.good() )
	{
		fileSorted.close();
		result = remove(fileNameTarget);
	}
	result = rename(fileNameSource, _filenameOut);
	result = remove(fileNameTarget);
}

void LongTextSorter::FirstPassSortBuffer(const char* buffer, std::string& bufferSorted)
{
	std::string bufferString(buffer);
	std::remove_if(bufferString.begin(), bufferString.end(), RemoveCharacter);

	std::vector<std::string> words;
	split(bufferString, ' ', words);

	std::sort(words.begin(), words.end(), SortTwoWordsPredicate);

	for (unsigned int i = 0; i < words.size(); ++i)
	{
		const std::string& word = words[i];
		bufferSorted.append(word);

		if (i < words.size() - 1)
		{
			bufferSorted.append(" ");
		}
	}

	//fill the rest of the chunk with empty spaces (bytes)
	int previousSize = bufferSorted.size();
	if (bufferSorted.size() < BUFFER_LENGTH)
	{
		bufferSorted.resize(BUFFER_LENGTH);
		for (int i = previousSize; i < BUFFER_LENGTH; ++i)
		{
			bufferSorted[i] = ' ';
		}
	}
}

void LongTextSorter::IterativePassSortBuffers()
{
	bool finished = false;
	while (!finished)
	{
		finished = IterativePassSortBuffer();
	}
}

class ThreadSortPairChunks
{
public:
	ThreadSortPairChunks(int pairIndex, int fileSizeBytes, int chunkSize, ifstream& ifStream, ofstream& outStream, OutputData& debug)
		: _pairIndex(pairIndex)
		, _chunkSize(chunkSize)
		, _fileSizeBytes(fileSizeBytes)
		, _ifStream(ifStream)
		, _outStream(outStream)
		, _debug(debug)
	{
	}

	void operator()()
	{
		int mainIndex = _pairIndex*(_chunkSize * 2);
		int writerIndex = mainIndex;

		int nextIndexBufferLeft = mainIndex;
		int nextIndexBufferRight = nextIndexBufferLeft + _chunkSize;
		int boundaryLeft = nextIndexBufferLeft + _chunkSize;
		int boundaryRight = nextIndexBufferRight + _chunkSize;
		if (boundaryRight > _fileSizeBytes)
		{
			boundaryRight = _fileSizeBytes;
		}

		std::vector<std::string> wordsLeft;
		std::vector<std::string> wordsRight;

		//Advance chunks and merge
		int charsWritten = 0;
		while (nextIndexBufferLeft < boundaryLeft
			|| nextIndexBufferRight < boundaryRight)
		{
			if (wordsLeft.empty())
			{
				int readSize = LongTextSorter::BUFFER_LENGTH;
				if (readSize >(boundaryLeft - nextIndexBufferLeft))
				{
					readSize = boundaryLeft - nextIndexBufferLeft;
					if (readSize < 0)
					{
						readSize = 0;
					}
				}

				if (readSize > 0)
				{
					RetrieveWordsFromCurrentBuffer(_ifStream, nextIndexBufferLeft, readSize, wordsLeft);
				}
			}

			if (wordsRight.empty())
			{
				int readSize = LongTextSorter::BUFFER_LENGTH;
				if (readSize > (boundaryRight - nextIndexBufferRight))
				{
					readSize = boundaryRight - nextIndexBufferRight;
					if (readSize < 0)
					{
						readSize = 0;
					}
				}

				if (readSize > 0)
				{
					RetrieveWordsFromCurrentBuffer(_ifStream, nextIndexBufferRight, readSize, wordsRight);
				}
			}

			if (wordsLeft.empty() && wordsRight.empty())
			{
				break;
			}

			std::string outString = "";

			if (!wordsLeft.empty() && !wordsRight.empty())
			{
				while (!wordsLeft.empty() && !wordsRight.empty())
				{
					std::string& wordLeft = wordsLeft.front();
					std::string& wordRight = wordsRight.front();
					int comparison = wordLeft.compare(wordRight);
					if (comparison <= 0)
					{
						outString += wordLeft + " ";
						wordsLeft.erase(wordsLeft.begin());
					}
					else
					{
						outString += wordRight + " ";
						wordsRight.erase(wordsRight.begin());
					}
				}
			}
			else if (wordsRight.empty())
			{
				for (std::string& word : wordsLeft)
				{
					outString += word + " ";
				}
				wordsLeft.clear();
			}
			else if (wordsLeft.empty())
			{
				for (std::string& word : wordsRight)
				{
					outString += word + " ";
				}
				wordsRight.clear();
			}


			charsWritten += outString.length();
			_outStream.seekp(writerIndex);
			_outStream.write(outString.c_str(), outString.length());
			writerIndex += outString.length();

			//_debug.UpdateData(_pairIndex, nextIndexBufferLeft, nextIndexBufferRight);
			//_debug.PrintStatus();
		}

		std::string outString = "";
		if (!wordsRight.empty())
		{
			assert(wordsLeft.empty());
			for (std::string& word : wordsRight)
			{
				outString += word + " ";
			}
			wordsRight.clear();
		}
		else if (!wordsLeft.empty())
		{
			assert(wordsRight.empty());
			for (std::string& word : wordsLeft)
			{
				outString += word + " ";
			}
			wordsLeft.clear();
		}
		charsWritten += outString.length();
		_outStream.seekp(writerIndex);
		_outStream.write(outString.c_str(), outString.length());
		writerIndex += outString.length();

		assert(wordsLeft.empty() && wordsRight.empty());
		if (!wordsLeft.empty() || !wordsRight.empty())
		{
			int x = 0;
			x++;
		}


		string extraString = "";
		for (int i = charsWritten; i < (_chunkSize * 2); ++i)
		{
			extraString += " ";
		}

		_outStream.seekp(writerIndex);
		_outStream.write(extraString.c_str(), extraString.length());
	}

	void RetrieveWordsFromCurrentBuffer(ifstream& inputFile, int& currentIndex_out, int readSize, std::vector<std::string>& wordList_out)
	{
		char buffer[LongTextSorter::BUFFER_LENGTH] = { '\0' };

		std::streampos pos(currentIndex_out);
		//read buffer
		inputFile.seekg(pos, ios::beg);
		inputFile.read(buffer, readSize);

		int bufferLastWordIndex = FindLastIndexLastWord(buffer);

		int bufferIncrement = min(readSize, bufferLastWordIndex + 1);
		currentIndex_out += bufferIncrement;
		buffer[bufferLastWordIndex + 1] = '\0';

		//retrieve words
		std::string bufferString(buffer);
		Trim(bufferString);
		std::remove(bufferString.begin(), bufferString.end(), '\n');
		split(bufferString, ' ', wordList_out);
		bufferString.clear();
	}

private:
	int _pairIndex;
	int _fileSizeBytes;
	int _chunkSize;
	ifstream& _ifStream;
	ofstream& _outStream;
	OutputData& _debug;
};

bool LongTextSorter::IterativePassSortBuffer()
{
	OutputData debug;

	//open files
	bool leftToRight = _currentPass % 2 != 0;
	const char* fileNameSource = leftToRight ? _filenameTemp1 : _filenameTemp2;
	const char* fileNameTarget = !leftToRight ? _filenameTemp1 : _filenameTemp2;

	ifstream inputFile;
	inputFile.open(fileNameSource, ios::in | ios::ate);

	ofstream outputFile;
	outputFile.open(fileNameTarget, ios::out | ios::trunc);

	//Set chunk sizes
	const int fileSizeBytes = static_cast<int>(inputFile.tellg());
	const int chunkSize = BUFFER_LENGTH * static_cast<int>(pow(2, _currentPass - 1));
	const int pairSteps = static_cast<int>(ceil(fileSizeBytes / (chunkSize*2.0f) ));
	
	debug.Init(fileSizeBytes, chunkSize, pairSteps);

	const unsigned int max_threads = pairSteps;
	const unsigned int hardware_threads = std::thread::hardware_concurrency();
	const unsigned int num_threads = min(hardware_threads, max_threads);

	std::queue<std::thread> threadList;

	//iterate through pairs
	for (int pairIndex = 0; pairIndex < pairSteps; ++pairIndex)
	{
		ThreadSortPairChunks threadSortPairChunks(pairIndex, fileSizeBytes, chunkSize, inputFile, outputFile, debug);

		threadList.push(std::thread(threadSortPairChunks));
		if (threadList.size() == num_threads)
		{
			std::thread& frontThread = threadList.front();
			frontThread.join();
			threadList.pop();
		}
	}

	while (!threadList.empty())
	{
		std::thread& frontThread = threadList.front();
		frontThread.join();
		threadList.pop();
	}

	inputFile.close();
	outputFile.close();

	++_currentPass;

	if (pairSteps == 1)
	{
		return true;
	}

	return false;
}