#pragma once

struct Elem
{
	char m_eng[15]; // Ключ.
	char m_rus[15]; // Значение.
	Elem* m_left/*левый потомок*/, * m_right/*правый потомок*/, * m_parent/*родитель*/;
};

class Tree
{
	// Корень.
	Elem* m_root;
	// Количество узлов.
	int m_count;
public:
	Tree();
	~Tree();
	// Печать от указанного узла.
	void Print(Elem* node);
	// Поиск от указанного узла.
	Elem* Search(Elem* node, char* key);
	// min от указанного узла.
	Elem* Min(Elem* node);
	// max от указанного узла.
	Elem* Max(Elem* node);
	// Следующий для указанного узла.
	Elem* Next(Elem* node);
	// Предыдущий для указанного узла.
	Elem* Previous(Elem* node);
	// Вставка узла.
	void Insert(Elem* z);
	// Удаление ветки для указанного узла.
	void Del(Elem* z);
	// Количество узлов дерева.
	int GetCount() { return m_count; }
	// Получить корень.
	Elem* GetRoot();

	// Сохранение данных дерева в файл.
	void SaveElemIntoFile(Elem* node, FILE* f);
	// Загрузка данных из файла.
	void LoadElemFromFile(Elem* node, FILE* f);
	// Балансировка бинарного дерева.
	void Вalancing(Elem* node, int leftBorder, int rightBorder);
};