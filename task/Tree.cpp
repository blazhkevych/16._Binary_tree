#include <iostream>
#include "tree.h"
using std::cout;
using std::endl;

Tree::Tree()
{
	root = nullptr;
	count = 0;
}

Tree::~Tree()
{
	while (root != nullptr)
		Del(root);
}

// Рекурсивный обход дерева
void Tree::Print(Elem* Node)
{
	if (Node != nullptr)
	{
		Print(Node->left);
		cout << Node->eng << " \t\t" << Node->rus << endl;
		Print(Node->right);
	}
}

Elem* Tree::Search(Elem* Node, char* k)
{
	// Пока есть узлы и ключи не совпадают
	while (Node != nullptr && strcmp(k, Node->eng) != 0)
	{
		if (strcmp(k, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	return Node;
}

Elem* Tree::Min(Elem* Node)
{
	// Поиск самого "левого" узла
	if (Node != nullptr)
		while (Node->left != nullptr)
			Node = Node->left;

	return Node;
}

Elem* Tree::Max(Elem* Node)
{
	// Поиск самого "правого" узла
	if (Node != nullptr)
		while (Node->right != nullptr)
			Node = Node->right;

	return Node;
}

Elem* Tree::Next(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		// если есть правый потомок
		if (Node->right != nullptr)
			// Следующий узел - самый "левый узел" в правом поддереве 
			return Min(Node->right);

		// родитель узла
		y = Node->parent;
		// если Node не корень и Node справа
		while (y != 0 && Node == y->right)
		{
			// Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::Previous(Elem* Node)
{
	Elem* y = nullptr;
	if (Node != nullptr)
	{
		// если есть левый потомок
		if (Node->left != nullptr)
			// Предыдущий узел - самый "правый" узел в левом поддереве 
			return Max(Node->left);

		// родитель узла
		y = Node->parent;
		// если Node не корень и Node слева
		while (y != nullptr && Node == y->left)
		{
			// Движемся вверх
			Node = y;
			y = y->parent;
		}
	}
	return y;
}

Elem* Tree::GetRoot()
{
	return root;
}

// Сохранение данных дерева в файл.
void Tree::Save(Elem* Node, FILE* f)
{

}

// Загрузка данных из файла.
void Tree::Load(Elem* Node, FILE* f)
{

}

// Балансировка бинарного дерева.
void Tree::Вalancing()
{

}

void Tree::Insert(Elem* z)
{
	// потомков нет
	z->left = nullptr;
	z->right = nullptr;

	Elem* y = nullptr; // родитель вставляемого элемента
	Elem* Node = root;

	// поиск места
	while (Node != nullptr)
	{
		// будущий родитель
		y = Node;
		if (strcmp(z->eng, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	// заполняем родителя
	z->parent = y;

	if (y == nullptr) // элемент первый (единственный)
		root = z;
	// чей ключ больше?
	else if (strcmp(z->eng, y->eng) < 0)
		y->left = z;
	else
		y->right = z;
	count++;
}

void Tree::Del(Elem* z)
{
	if (z != nullptr)
	{
		Elem* Node = nullptr; // дочерний узел для удаляемого узла
		Elem* y = nullptr; // удаляемый узел
		// не 2 потомка
		if (z->left == nullptr || z->right == nullptr)
			y = z;
		else
			y = Next(z);

		if (y->left != nullptr)
			Node = y->left;
		else
			Node = y->right;
		// Если удаляется не лист
		if (Node != nullptr)
			Node->parent = y->parent;
		// Удаляется корневой узел?
		if (y->parent == nullptr)
			root = Node;
		else if (y == y->parent->left) // слева от родителя?
			y->parent->left = Node;
		else
			y->parent->right = Node;  // справа от родителя?

		if (y != z)
		{
			// Копирование данных узла
			strcpy_s(z->eng, y->eng);
			strcpy_s(z->rus, y->rus);
		}
		delete y;
		count--;
	}
}