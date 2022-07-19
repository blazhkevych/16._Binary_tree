/*
############################################ ЗАДАНИЕ ###########################################
				Бинарное дерево
	Добавить в класс "Бинарное дерево" следующие
методы:
	* сохранение данных дерева в файл
void SaveDataOnExit(Elem * Node, FILE*f);
	* загрузка данных из файла
void LoadElemFromFile(Elem * Node, FILE*f);
	* балансировка бинарного дерева
void Вalancing();
################################################################################################
			Бинарное дерево поиска.
			
	* Дерево всегда должно быть упорядочено и для эффективного поиска сбалансированным.
	* Сортировка дерева происходит по ключу.
	* Для каждого узла, в левой ветке содержатся те ключи, которые имеют значение строго меньше чем этот узел.
	* Для каждого узла, в правой ветке содержатся те ключи, которые имеют значение больше либо равно.
	* Минимальный елемент - самый левый узел в левом поддереве.
	* Максимальный елемент - самый правый узел в правом поддереве.
	* Следующий елемент - минимальный елемент в правом поддереве.
	* Предыдущий елемент - максимальный елемент в левом поддереве.
	* Вновь добавляемый елемент всегда лист, у которого пока нету потомков.
	*
################################################################################################
Не закончено.

2,28,30 начало
Слова для тестов:
engl	ru

dog		собака
book	книга
hair	волосы
apple	яблоко
cat		кот
girl	девочка
man		мужчина

					dog
					/  \
                   /    \
               book      hair
              /\            /\
             /  \          /  \
        apple    cat   girl    man
*/

#include <windows.h>
#include <iostream>
#include <conio.h>
#include <io.h>
#include "tree.h"

using namespace std;

void PrintMenu()
{
	char Menu[] = "1.Insert node\n2.Delete node\n3.Print node\n4.Search node\n5.Exit\n";
	system("cls");
	cout << Menu;
}

void Insert(Tree& obj)
{
	system("cls");
	cout << "Enter a quantity of elements to add: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		Elem* temp = new Elem;
		cout << "\nEnter an english word " << i + 1 << endl;
		cin >> temp->m_eng;
		cout << "\nEnter a russian word " << i + 1 << endl;
		cin >> temp->m_rus;
		obj.Insert(temp);
	}
}

void Print(Tree& obj)
{
	system("cls");
	obj.Print(obj.GetRoot());
	_getch();
}

void Search(Tree& obj)
{
	system("cls");
	cout << "Enter an english word for search:\n";
	char buf[15];
	cin >> buf;
	Elem* elem = obj.Search(obj.GetRoot(), buf);
	if (elem)
		cout << elem->m_rus;
	else
		cout << "\nWord not found\n";
	_getch();
}

void Delete(Tree& obj)
{
	system("cls");
	cout << "Enter an english word for delete:\n";
	char buf[15];
	cin >> buf;
	Elem* p = obj.Search(obj.GetRoot(), buf);
	obj.Del(p);
}

void SaveDataOnExit(Tree& obj)
{
	if (obj.GetCount() == 0) // Если в Tree пусто, то ничего не сохраняем в файл и выходим.
		return;
	else
	{
		const char fileNameWrite[20]{ "dictionary.data" };
		FILE* f_wright{ nullptr };
		fopen_s(&f_wright, fileNameWrite, "wb");
		if (f_wright == nullptr)
		{
			perror("Error opening");
			return;
		}

		obj.SaveElemIntoFile(obj.GetRoot(), f_wright);
		fclose(f_wright);
	}
}

void LoadDataOnStart(Tree& obj)
{
	const char fileNameRead[20]{ "dictionary.data" };
	FILE* f_read{ nullptr };
	fopen_s(&f_read, fileNameRead, "rb");
	if (f_read == nullptr)
	{
		perror("Error opening");
		return;
	}




	obj.LoadElemFromFile(obj.GetRoot(), f_read);
	fclose(f_read);
}

int main()
{
	SetConsoleCP(1251);
	/*
	Задает кодовую страницу ввода, используемую консолью, связанной с вызывающим процессом.
	Консоль использует страницу входного кода для преобразования ввода с клавиатуры
	в соответствующее символьное значение.
	*/
	SetConsoleOutputCP(1251);
	/*
	Задает выходную кодовую страницу, используемую консолью, связанной с вызывающим процессом.
	Консоль использует свою кодовую страницу вывода для преобразования символьных значений,
	записанных различными функциями вывода, в изображения, отображаемые в окне консоли.
	*/

	Tree obj;
	LoadDataOnStart(obj);
	while (true)
	{
		PrintMenu();
		char res = _getch();
		switch (res)
		{
		case '1': Insert(obj);
			break;
		case '2': Delete(obj);
			break;
		case '3': Print(obj);
			break;
		case '4': Search(obj);
			break;
		case '5': SaveDataOnExit(obj);  return 0; // Выход.
		}
	}
}