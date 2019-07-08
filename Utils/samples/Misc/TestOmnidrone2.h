#pragma once
#include "stdafx.h"
#include <typeinfo>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <unordered_map>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <assert.h>

using namespace std;
/*
class GridBlocks
{
public:

	GridBlocks(vector<string> rows)
		:_rows(rows)
	{
		Fall();
	}

	vector<string> GetStateAfterFall()
	{
		return _rows;
	}

private:
	void Fall() {
		bool stopped = false;
		int currentIndex = 0;
		while (!stopped) {
			int nextIndex = currentIndex + 1;

			char type = GetTypeByPos(0, currentIndex);
			if (type == '#') {
				type = GetTypeByPos(0, nextIndex);
				if (type == '\0') {
					stopped = true;
					break;
				}

				if (type == '.') {
					char SetTypeByPos(0, currentIndex, '.');
					char SetTypeByPos(0, nextIndex, '#');
				}
			}


		}


	}

	char GetTypeByPos(std::size_t x, std::size_t y) {
		if (y > _rows.size()) {
			return '\0';
		}

		const std::string row = _rows[y];
		if (x > row.size()) {
			return '\0';
		}

		return row[x];
	}

	char SetTypeByPos(std::size_t x, std::size_t y, char value) {
		if (y > _rows.size()) {
			assert(false);
		}

		std::string row = _rows[y];
		if (x > row.size()) {
			assert(false);
		}

		row[x] = value;
	}


	vector<string> _rows;
};
*/
class TestOmnidrone2
{
public:
	static void Run() {
		/*
		GridBlocks grid(vector<string>{"#", ".", "."});
		for (string s : grid.GetStateAfterFall())
		{
			cout << s; // {".", ".", "#"} The only block falls.
		}

		grid = GridBlocks(vector<string>{"##", "#.", ".."});
		for (string s : grid.GetStateAfterFall())
		{
			cout << s; // {"..", "#.", "##"} The 2 blocks on the left pile up.
		}*/
	}
};