#pragma once
#include "stdafx.h"

struct BitArrayPrintHelpers;

template<class TContainer>
class BitArrayIterator
{
public:
	BitArrayIterator( TContainer& dataStructure, int position )
		: m_dataStructure( dataStructure )
		, position( position )
	{
	}

	BitArrayIterator& operator * ()
	{
		return *this;
	}

	BitArrayIterator* operator -> ()
	{
		return this;
	}

	bool GetBit() const
	{
		assert( position >= 0 ); //Position can't be negative!
		return m_dataStructure.GetBit( position );
	}

	void SetBit( bool bit )
	{
		m_dataStructure.SetBit( position, bit );
	}

	BitArrayIterator<TContainer>& operator++() // ++A
	{
		++position;
		return *this;
	}

	BitArrayIterator<TContainer>& operator--() // ++A
	{
		--position;
		return *this;
	}

	bool operator == ( BitArrayIterator<TContainer>& other )
	{
		return position == other.position;
	}

	bool operator != ( BitArrayIterator<TContainer>& other )
	{
		return position != other.position;
	}

private:
	TContainer& m_dataStructure;
	int position;
};

template<class TContainer>
class BitArrayReverseIterator : public BitArrayIterator<TContainer>
{
	typedef BitArrayIterator<TContainer> super;

public:
	BitArrayReverseIterator( TContainer& dataStructure, unsigned int position )
		: super( dataStructure, position )
	{
	}

	BitArrayReverseIterator<TContainer>& operator++() // ++A
	{
		super::operator--();
		return *this;
	}

	BitArrayReverseIterator<TContainer>& operator--() // ++A
	{
		super::operator++();
		return *this;
	}
};

template<typename SIZE_TYPE = char>
class BitArray
{
private:
	friend struct BitArrayPrintHelpers;

public:
	typedef SIZE_TYPE TSizeType;
	typedef BitArrayIterator<BitArray> iterator;
	typedef BitArrayIterator<const BitArray> const_iterator;
	typedef BitArrayReverseIterator<BitArray> reverse_iterator;
	typedef BitArrayReverseIterator<const BitArray> const_reverse_iterator;

public:
	
	iterator begin(){ return iterator(*this, 0);}
	iterator end(){	return iterator(*this, m_size*8 ); }

	const_iterator cbegin() const { return const_iterator(*this, 0);}
	const_iterator cend() const { return const_iterator(*this, m_size*8 ); }

	reverse_iterator rbegin(){ return reverse_iterator(*this, (m_size*8) - 1 );}
	reverse_iterator rend(){ return reverse_iterator(*this, -1); }

	const_reverse_iterator crbegin() const { return const_reverse_iterator(*this, (m_size*8) - 1 );}
	const_reverse_iterator crend() const { return const_reverse_iterator(*this, -1); }
	
	BitArray()
		: m_data( new TSizeType[1] )
		, m_size( 1 )
	{
		for( unsigned int i = 0; i<m_size; ++i)
		{
			m_data[i] = 0;
		}
	}

	bool GetBit( unsigned int position )
	{
		unsigned int slotIndex = position / GetBitSize();
		if( slotIndex > m_size-1 )
		{
			Resize( slotIndex+1 );
		}

		TSizeType slotData = m_data[slotIndex];

		unsigned int bitPos = position % GetBitSize();
		slotData >>= bitPos;
		slotData &= 1;
		
		bool bitValue = (slotData == 1);

		return bitValue;
	}

	bool GetBit( unsigned int position ) const
	{
		unsigned int slotIndex = position / GetBitSize();
		if( slotIndex > m_size-1 )
		{
			assert(false); //Cannot resize when const!
		}

		TSizeType slotData = m_data[slotIndex];

		unsigned int bitPos = position % GetBitSize();
		slotData >>= bitPos;
		slotData &= 1;

		bool bitValue = (slotData == 1);

		return bitValue;
	}

	void SetBit( unsigned int position, bool bit )
	{
		unsigned int slotIndex = position / GetBitSize();
		if( slotIndex > m_size-1 )
		{
			Resize( slotIndex+1 );
		}

		TSizeType& slotData = m_data[slotIndex];


		unsigned int bitPos = position % GetBitSize();
		TSizeType mask = (1 << bitPos);

		if( bit )
		{
			slotData |= mask;
		}
		else
		{
			slotData &= ~mask;
		}
	}

	void ResetBit(unsigned int position)
	{
		SetBit( position, 0 );
	}
	unsigned int GetBitSize() const
	{
		return sizeof( TSizeType ) * 8;
	}
	unsigned int GetSize() const
	{
		return m_size;
	}

private:
	void Resize( unsigned int newSize )
	{
		TSizeType* buffer = new TSizeType[m_size];
		for( unsigned int i = 0; i<m_size; ++i)
		{
			buffer[i] = m_data[i];
		}

		delete[] m_data;
		m_data = new TSizeType[newSize];
		for( unsigned int i = 0; i<m_size; ++i)
		{
			m_data[i] = buffer[i];
		}

		for( unsigned int i = m_size; i<newSize; ++i)
		{
			m_data[i] = 0;
		}

		m_size = newSize;
	}

private:
	TSizeType* m_data;
	unsigned int m_size;
};


struct BitArrayPrintHelpers
{
	template< class T >
	static void Print( const T& bitArray)
	{
		for( const T::TSizeType* slotData = bitArray.m_data; slotData != (bitArray.m_data+bitArray.m_size); ++slotData  )
		{
			T::TSizeType slotDataTemp = *slotData;
			for( unsigned int j = 0; j< bitArray.GetBitSize(); ++j)
			{
				bool bit = (slotDataTemp >> j) & 1;
				cout << bit;
			}
			cout << ",";
		}
		cout << " " << endl;
	}

	template< class T >
	static void PrintIterative( const T& bitArray)
	{
		for( T::const_iterator it = bitArray.cbegin(), endit = bitArray.cend(); it != endit; ++it )
		{
			cout << (*it).GetBit();
		}
	}
};
