#include "library.h"
#include <stdlib.h>
char ch=' ';
LIBRARY Library;
BOOK Book;
BOOKLISTITEM *bli;
void main()
{
	while (ch!=27)
	{
		clrscr();
		printf("1-Добавить книгу\n2-Удалить книгу\n3-Вывод списка книг\n4-Поиск книги\n5-Сортировка\n");
		ch=getch();
		clrscr();
		switch(ch)
		{
		case '1':
			printf("Добавление книги:\n");
			InputBook(&Book);
			if (!Library.AddBook(Book)) printf("Не удалось добавить книгу.\n");
			break;
		case '2':
			printf("Удаление книги:\n");
			InputBook(&Book);
			bli=Library.FindBook(Book,Library.root);
			if (bli) Library.DeleteBook(bli);
			else {printf("Ошибка. Возможно такой книги нет.\n");getch();}
			break;
		case '3':
			Library.Print();
			break;
		case '4':
			printf("Введите данные о книге, которую хотите найти:\n");
			ch=' ';
			const MAX=256;
			char *str1 =new char[MAX];
			char *f="%256s";
			if (Book.Author) free(Book.Author);
			if (Book.Title)free(Book.Title);
			if (Book.Manufactor)free(Book.Manufactor);
			Book.Author=NULL;
			Book.Title=NULL;
			Book.Manufactor=NULL;
			Book.Pages=0;
      Book.Year=0;
			fflush (stdin);
 
			while (ch!='0')
			{
				printf("Текущие параметры поиска:\n");
				PrintBook(&Book);
				printf("\nВведите параметры поиска\n");
				printf("1-Автор\n2-Название\n3-Издательство\n4-Страниц\n5-Год\n0-Начать поиск\n");
				ch=getch();
				switch (ch)
				{
				case '1':
					printf("Введите автора: "); fflush(stdin);
					scanf(f,str1);
					if (Book.Author) free(Book.Author);
					Book.Author=strdup(str1);
					break;
				case '2':
					printf("Введите название: "); fflush(stdin);
					scanf(f,str1);
					if (Book.Title) free(Book.Title);
					Book.Title=strdup(str1);
					break;
				case '3':
					printf("Введите издательство: "); fflush(stdin);
					scanf(f,str1);
					if (Book.Manufactor) free(Book.Manufactor);
					Book.Manufactor=strdup(str1);
					break;
				case '4':
					printf("Введите количество страниц: ");fflush(stdin);
					scanf("%u",Book.Pages);
					break;
				case '5':
					printf("Введите год: ");fflush(stdin);
					scanf("%u",Book.Year);
					break;
				}
			}
			delete str1;
			bli=Library.root;
			printf("Результаты:\n");
			while (bli)
			{
				bli=Library.FindBook(Book,bli);
				if (bli)
				{
					PrintBook(bli);
					getch();
					bli=bli->Next;
				}
			}
			printf("Вывод закончен.");
			getch();
			break;
		case '5':
			printf("Выберите параметры сортировки: \n");
			printf("1-по автору\n2-по названию\n3-по издательству\n4-по количеству страниц\n5-по году\n");
			ch=getch();
			UINT Field;
			Field=ch-'1';
			if (!Library.Sort(Field)) printf("Произошла ошибка при сортировке.\n");
			else  printf("Сортировка прошла успешно.\n");
			getch();
			break;
		case '6':
		case '7':
		break;
		}
	}
}
