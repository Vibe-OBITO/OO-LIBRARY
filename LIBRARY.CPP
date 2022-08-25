#ifndef _LIBRARYCPP
#define _LIBRARYCPP
#include "LIBRARY.H"
#include <string.h>
#include <stdio.h>
#include <conio.h>
LIBRARY::LIBRARY()//конструктор root=NULL;
{
	root=NULL;
}
LIBRARY::~LIBRARY()//деструктор
{
	BOOKLISTITEM *bli=root;
	if (bli) bli=bli->Next;
	while (bli)
	{
		delete bli->Previous;
		bli=bli->Next;
	}
	if (bli) delete bli;
}
//		BOOL AddBook(char *Author,char *Title,char *Manufactor,UINT Pages,UNIT Year);
BOOL LIBRARY::AddBook(BOOK &Book)
{
	BOOKLISTITEM * bli=new BOOKLISTITEM;
	if (!bli) return FALSE;
	bli->Author=strdup(Book.Author);
	bli->Title=strdup(Book.Title);
	bli->Manufactor=strdup(Book.Manufactor);
	bli->Pages=Book.Pages;
	bli->Year=Book.Year;
	//Переставляем указатели
	if (root) root->Previous=bli;
	bli->Next=root;
	bli->Previous=NULL;
	root=bli;
	return TRUE;
}
//		BOOL DeleteBook(char *Author,char *Title,char *Manufactor,UINT Pages,UNIT Year);
BOOL LIBRARY::DeleteBook(BOOKLISTITEM *bli)
{
	//Исправление указателей
	if (bli->Previous) bli->Previous->Next=bli->Next;
	if (bli->Next) bli->Next->Previous=bli->Previous;
	if (root==bli) root=NULL;
	//Удаление книги
	delete bli;
	return TRUE;
}
 
BOOKLISTITEM* LIBRARY::FindBook(BOOK &Book,BOOKLISTITEM *Start)
{
	if (!root) return NULL;
	BOOKLISTITEM *bli=Start;
	BOOL Find=TRUE;
	while (bli)
	{
		if (Book.Author)
		{
			if (strcmpi(Book.Author,bli->Author)!=0) Find=FALSE;
		}
		if (Book.Title)
		{
			if (strcmpi(Book.Title,bli->Title)!=0)  Find=FALSE;
		}
		if (Book.Manufactor)
		{
			if (strcmpi(Book.Manufactor,bli->Manufactor)!=0) Find=FALSE;
		}
		if (Book.Pages)
		{
			if (Book.Pages!=bli->Pages) Find=FALSE;
		}
		if (Book.Year)
		{
			if ((Book.Year)!=bli->Year) Find=FALSE;
		}
		if (Find) return bli;
		bli=bli->Next;
	}
	return NULL;
}
 
BOOL LIBRARY::Sort(UINT Field)
{
	LIBRARY Library;
	BOOK Book;
	if (!root) return TRUE;
	while (root)
	{
		BOOKLISTITEM * max=root;
		BOOKLISTITEM * bli=root;
		while (bli)
		{
			switch (Field)
			{
			case S_AUTHOR:
				if (strcmpi(max->Author,bli->Author)<0) max=bli;
				break;
			case S_TITLE:
				if (strcmpi(max->Title,bli->Title)<0) max=bli;
				break;
			case S_MANUFACTOR:
				if (strcmpi(max->Manufactor,bli->Manufactor)<0) max=bli;
				break;
			case S_PAGES:
				if (max->Pages<bli->Pages) max=bli;
			break;
			case S_YEAR:
				if (max->Year<bli->Year) max=bli;
				break;
			}
			bli=bli->Next;
		}
		if (max->Previous) max->Previous->Next=max->Next;
		if (max->Next) max->Next->Previous=max->Previous;
		if (root==max) root=max->Next;
		memcpy((char*)&Book,(char*)max,sizeof(Book));
		Library.AddBook(Book);
		delete max;
	}
	this->root=Library.root;
	return TRUE;
}
 
void LIBRARY::Print()
{
	BOOKLISTITEM *bli=this->root;
	while (bli)
	{
		PrintBook(bli);
		printf("Нажмите любую кнопку для продолжения...\n");getch();
		bli=bli->Next;
	}
  printf("Вывод завершён. "); getch();
 
}
 
template <class T>BOOL PrintBook(T *Book)
{
	printf("\nАвтор: ");
	if (Book->Author) printf("%s",Book->Author);
	printf("\nКнига: ");
	if (Book->Title) printf("%s",Book->Title);
	printf("\nИздательство: ");
	if (Book->Manufactor) printf("%s",Book->Manufactor);
	printf("\nСтраниц: ");
	if (Book->Pages)	printf("%u",Book->Pages);
	printf("\nГод: ");
	if (Book->Year) printf("%u",Book->Year);
	printf("\n");
	return TRUE;
}
 
template <class T>BOOL InputBook(T *Book)
{
	const MAX=256;
	char *str1=new char[MAX];
	char *f="%256s";
	if (!str1) return FALSE;
	printf("\nАвтор: ");fflush(stdin);
	scanf(f,str1);
	Book->Author=strdup(str1);
	printf("Книга: ");fflush(stdin);
	scanf(f,str1);
	Book->Title=strdup(str1);
	printf("Издательство: ");fflush(stdin);
	scanf(f,str1);
	Book->Manufactor=strdup(str1);
	printf("Страниц: ");// fflush(stdin);
	scanf("%u",&Book->Pages);
	printf("Год: ");  //fflush(stdin);
	scanf("%u",&Book->Year);
	delete str1;
	return TRUE;
}
 
#endif
