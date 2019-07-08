#pragma once
#include <vector>
#include <string>
#include <array>
#include <iostream>
#include <vector>
using namespace std;

class PictureComposition
{
	using TTypeList = std::vector<int>;
	using TConstIterator = TTypeList::const_iterator;
public:
	static const int INVALID_PICTURE_ID = -1;

	void AttachPictureFromLeft(int pictureId)
	{
		_pictures.insert(std::begin(_pictures), pictureId);
	}

	void AttachPictureFromRight(int pictureId)
	{
		_pictures.emplace_back(pictureId);
	}

	int DetachPictureFromLeft()
	{
		return DetachByIndex(0);
	}

	int DetachPictureFromRight()
	{
		return DetachByIndex(_pictures.size() - 1);
	}

private:
	int DetachByIndex(std::size_t index)
	{
		if (	_pictures.empty() 
			|| index > (_pictures.size() - 1)) {
			//Throw an error
			return INVALID_PICTURE_ID;
		}

		TConstIterator it = std::begin(_pictures) + index;
		const int pictureId = *it;
		_pictures.erase(it);
		return pictureId;
	}


	TTypeList _pictures;
};
/*
#ifndef OMNIDRONE_TEST // Please don't remove
int main()
{
	PictureComposition pc;
	pc.AttachPictureFromLeft(1);
	pc.AttachPictureFromLeft(2);
	pc.AttachPictureFromRight(3);
	cout << pc.DetachPictureFromLeft(); // 2
	cout << pc.DetachPictureFromLeft(); // 1
	cout << pc.DetachPictureFromLeft(); // 3
}
#endif
*/