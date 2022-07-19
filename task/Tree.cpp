#include <iostream>
#include <io.h>
#include "tree.h"
using std::cout;
using std::endl;

Tree::Tree()
{
	m_root = nullptr;
	m_count = 0;
}

Tree::~Tree()
{
	while (m_root != nullptr)
		Del(m_root);
}

// Рекурсивный обход дерева
void Tree::Print(Elem* node)
{
	if (node != nullptr)
	{
		Print(node->m_left);
		cout << node->m_eng << " \t\t" << node->m_rus << endl;
		Print(node->m_right);
	}
}

Elem* Tree::Search(Elem* node, char* k)
{
	// Пока есть узлы и ключи не совпадают
	while (node != nullptr && strcmp(k, node->m_eng) != 0)
	{
		if (strcmp(k, node->m_eng) < 0)
			node = node->m_left;
		else
			node = node->m_right;
	}
	return node;
}

Elem* Tree::Min(Elem* node)
{
	// Поиск самого "левого" узла
	if (node != nullptr)
		while (node->m_left != nullptr)
			node = node->m_left;

	return node;
}

Elem* Tree::Max(Elem* node)
{
	// Поиск самого "правого" узла
	if (node != nullptr)
		while (node->m_right != nullptr)
			node = node->m_right;

	return node;
}

Elem* Tree::Next(Elem* node)
{
	Elem* y = nullptr;
	if (node != nullptr)
	{
		// если есть правый потомок
		if (node->m_right != nullptr)
			// Следующий узел - самый "левый узел" в правом поддереве 
			return Min(node->m_right);

		// родитель узла
		y = node->m_parent;
		// если node не корень и node справа
		while (y != 0 && node == y->m_right)
		{
			// Движемся вверх
			node = y;
			y = y->m_parent;
		}
	}
	return y;
}

Elem* Tree::Previous(Elem* node)
{
	Elem* y = nullptr;
	if (node != nullptr)
	{
		// если есть левый потомок
		if (node->m_left != nullptr)
			// Предыдущий узел - самый "правый" узел в левом поддереве 
			return Max(node->m_left);

		// родитель узла
		y = node->m_parent;
		// если node не корень и node слева
		while (y != nullptr && node == y->m_left)
		{
			// Движемся вверх
			node = y;
			y = y->m_parent;
		}
	}
	return y;
}

Elem* Tree::GetRoot()
{
	return m_root;
}

// Сохранение данных дерева в файл.
void Tree::SaveElemIntoFile(Elem* node, FILE* f_wright) // Размер записанного файла совпадает с размером записываемых массивов.
{
	if (node != nullptr)
	{
		SaveElemIntoFile(node->m_left, f_wright);
		// способ сохранения, скорее бинарный
		fwrite(node->m_eng, sizeof(node->m_eng), 1, f_wright);
		fwrite(node->m_rus, sizeof(node->m_rus), 1, f_wright);
		SaveElemIntoFile(node->m_right, f_wright);
	}
}

// Загрузка данных из файла.
void Tree::LoadElemFromFile(Elem* node, FILE* f_read)
{
	Elem* temp = new Elem;
	const int lenght = _filelength(_fileno(f_read));
	const int numElementsInFile = lenght / (sizeof(temp->m_eng) + sizeof(temp->m_rus));
	Elem* elemArr = new Elem[numElementsInFile];
	for (int i = 0; i < numElementsInFile; i++)
	{
		fread(&temp->m_eng, sizeof(temp->m_eng), 1, f_read);
		fread(&temp->m_rus, sizeof(temp->m_rus), 1, f_read);
		elemArr[i] = *temp;
	}

	Вalancing(elemArr, 0, numElementsInFile - 1);

	delete[]elemArr;
}

// Балансировка бинарного дерева.
void Tree::Вalancing(Elem* node, int leftBorder, int rightBorder)
{
	if (leftBorder <= rightBorder)
	{
		Elem* temp = new Elem; // Выделяем память под новый нод, который отправим в Insert();
		int middle = (leftBorder + rightBorder) / 2;
		temp = node + middle; // след заход идет с новым елементом или начальным ?!?!?!?!?
		Insert(temp);
		rightBorder = middle;
		Вalancing(node, leftBorder, rightBorder);
	}

	/*
	 0 apple
	 1 book		2 итер., (0+1)/2=0  ВСТАВЛЯЕМ, Вalancing(0 apple, 0, 0), потерял cat !
	 2 cat
	 3 dog		1 итер., (0+6)/2=3 ВСТАВЛЯЕМ, Вalancing(0 apple, 0, 3), середина = (0+3)/2 = 1,5 = 1
	 4 girl
	 5 hair
	 6 man

	 apple - man = dog
	 */

}

void Tree::Insert(Elem* z)
{
	// потомков нет
	z->m_left = nullptr;
	z->m_right = nullptr;

	Elem* y = nullptr; // родитель вставляемого элемента
	Elem* node = m_root;

	// поиск места
	while (node != nullptr)
	{
		// будущий родитель
		y = node;
		if (strcmp(z->m_eng, node->m_eng) < 0)
			node = node->m_left;
		else
			node = node->m_right;
	}
	// заполняем родителя
	z->m_parent = y;

	if (y == nullptr) // элемент первый (единственный)
		m_root = z;
	// чей ключ больше?
	else if (strcmp(z->m_eng, y->m_eng) < 0)
		y->m_left = z;
	else
		y->m_right = z;
	m_count++;
}

void Tree::Del(Elem* z)
{
	if (z != nullptr)
	{
		Elem* node = nullptr; // дочерний узел для удаляемого узла
		Elem* y = nullptr; // удаляемый узел
		// не 2 потомка
		if (z->m_left == nullptr || z->m_right == nullptr)
			y = z;
		else
			y = Next(z);

		if (y->m_left != nullptr)
			node = y->m_left;
		else
			node = y->m_right;
		// Если удаляется не лист
		if (node != nullptr)
			node->m_parent = y->m_parent;
		// Удаляется корневой узел?
		if (y->m_parent == nullptr)
			m_root = node;
		else if (y == y->m_parent->m_left) // слева от родителя?
			y->m_parent->m_left = node;
		else
			y->m_parent->m_right = node;  // справа от родителя?

		if (y != z)
		{
			// Копирование данных узла
			strcpy_s(z->m_eng, y->m_eng);
			strcpy_s(z->m_rus, y->m_rus);
		}
		delete y;
		m_count--;
	}
}