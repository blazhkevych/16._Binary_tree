#pragma once

struct Elem
{
	char eng[15]; // Ключ.
	char rus[15]; // Значение.
	Elem* left/*левый потомок*/, * right/*правый потомок*/, * parent/*родитель*/;
};

class Tree
{
	// Корень.
	Elem* root;
	// Количество узлов.
	int count;
public:
	Tree();
	~Tree();
	// Печать от указанного узла.
	void Print(Elem* Node);
	// Поиск от указанного узла.
	Elem* Search(Elem* Node, char* key);
	// min от указанного узла.
	Elem* Min(Elem* Node);
	// max от указанного узла.
	Elem* Max(Elem* Node);
	// Следующий для указанного узла.
	Elem* Next(Elem* Node);
	// Предыдущий для указанного узла.
	Elem* Previous(Elem* Node);
	// Вставка узла.
	void Insert(Elem* z);
	// Удаление ветки для указанного узла.
	void Del(Elem* z);
	// Количество узлов дерева.
	int GetCount() { return count; }
	// Получить корень.
	Elem* GetRoot();

	// Сохранение данных дерева в файл.
	void Save(Elem* Node, FILE* f);
	// Загрузка данных из файла.
	void Load(Elem* Node, FILE* f);
	// Балансировка бинарного дерева.
	void Вalancing();
};