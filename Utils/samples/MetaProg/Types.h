#include "TraitsUtils.h"

class AucunTypeCorrespondant;

enum size_types { SIZE_8 = 1, SIZE_16 = 2, SIZE_32 = 4, SIZE_64 = 8};

typedef static_if_else <sizeof(short)==SIZE_8,
   short,
   static_if_else <sizeof(int)==SIZE_8,
      int,
      static_if_else <sizeof(long)==SIZE_8,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_8,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type int8;

typedef static_if_else <sizeof(short)==SIZE_16,
   short,
   static_if_else <sizeof(int)==SIZE_16,
      int,
      static_if_else <sizeof(long)==SIZE_16,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_16,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type int16;

typedef static_if_else <sizeof(short)==SIZE_32,
   short,
   static_if_else <sizeof(int)==SIZE_32,
      int,
      static_if_else <sizeof(long)==SIZE_32,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_32,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type int32;

typedef static_if_else <sizeof(short)==SIZE_64,
   short,
   static_if_else <sizeof(int)==SIZE_64,
      int,
      static_if_else <sizeof(long)==SIZE_64,
         long,
		 static_if_else <sizeof(long long)==SIZE_64,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type int64;






typedef static_if_else <sizeof(unsigned short)==SIZE_8,
   short,
   static_if_else <sizeof(unsigned int)==SIZE_8,
      int,
      static_if_else <sizeof(unsigned long)==SIZE_8,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_8,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type uint8;

typedef static_if_else <sizeof(unsigned short)==SIZE_16,
   short,
   static_if_else <sizeof(unsigned int)==SIZE_16,
      int,
      static_if_else <sizeof(unsigned long)==SIZE_16,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_16,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type uint16;

typedef static_if_else <sizeof(unsigned short)==SIZE_32,
   short,
   static_if_else <sizeof(unsigned int)==SIZE_32,
      int,
      static_if_else <sizeof(unsigned long)==SIZE_32,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_32,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type uint32;

typedef static_if_else <sizeof(unsigned short)==SIZE_64,
   short,
   static_if_else <sizeof(unsigned int)==SIZE_64,
      int,
      static_if_else <sizeof(unsigned long)==SIZE_64,
         long,
		 static_if_else <sizeof(unsigned long long)==SIZE_64,
			 long long,
			 AucunTypeCorrespondant
		  >::type
      >::type
   >::type
>::type uint64;
