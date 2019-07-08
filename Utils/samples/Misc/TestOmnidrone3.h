#pragma once
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

class Path
{
public:

	Path(string path)
	{
		string currentPath = "";
		for (char c : path) {
			if (c == '/') {
				if (!currentPath.empty()) {
					_path.push_back(currentPath);
					currentPath.clear();
				}
				continue;
			}

			currentPath += c;
		}

		if (!currentPath.empty()) {
			_path.push_back(currentPath);
		}
	}

	string GetCurrentPath()
	{
		string currentPath = "/";

		for (int i = 0; i < _path.size(); ++i) {
			currentPath += _path[i];
			if (i < _path.size() - 1) {
				currentPath += "/";
			}
		}
		return currentPath;
	}

	void Cd(string newPath)
	{
		Path path(newPath);
		std::vector<string> folders = path._path;

		for (string folder : folders) 
		{
			if (folder == "..") {
				_path.pop_back();
			}
			else if (folder == ".") 
			{
				continue;
			}
			else 
			{
				_path.push_back(folder);
			}
		}
	}

private:
	std::vector<string> _path;
};
/*
#ifndef OMNIDRONE_TEST // Please don't remove
int main()
{
	Path path("/x/y/z");
	path.Cd("../a");
	cout << path.GetCurrentPath(); // "/x/y/a"
}
#endif*/