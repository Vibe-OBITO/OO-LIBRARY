//Класс библиотека
#ifndef _LIBRARYH
#define _LIBRARYH
typedef unsigned int UINT;
typedef unsigned short int BOOL;
struct BOOK{
	char * Author;
	char * Title;
	char * Manufactor;
	UINT Pages;
	UINT Year;
};
 
struct BOOKLISTITEM{
	char * Author;
	char * Title;
	char * Manufactor;
	UINT Pages;
	UINT Year;
	BOOKLISTITEM *Next;
	BOOKLISTITEM *Previous;
};
 
//////////////////////////////////////////////
//Определение констант
const TRUE=1,FALSE=0;
const S_AUTHOR=0,S_TITLE=1,S_MANUFACTOR=2,S_PAGES=3,S_YEAR=4;
 
class LIBRARY
{
	private:
	protected:
	public:
		BOOKLISTITEM * root;
		LIBRARY();//конструктор root=NULL;
		~LIBRARY();//деструктор
//		BOOL AddBook(char *Author,char *Title,char *Manufactor,UINT Pages,UNIT Year);
		BOOL AddBook(BOOK &Book);
//		BOOL DeleteBook(char *Author,char *Title,char *Manufactor,UINT Pages,UNIT Year);
		BOOL DeleteBook(BOOKLISTITEM *bli);
		BOOKLISTITEM* FindBook(BOOK &Book,BOOKLISTITEM *Start);
		BOOL Sort(UINT Field);
		void Print();
};
 
template <class T>BOOL PrintBook(T *Book);
template <class T>BOOL InputBook(T *Book);
#include "LIBRARY.CPP"
#endif
