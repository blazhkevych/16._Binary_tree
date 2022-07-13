#pragma once

struct Elem
{
	char eng[15]; // ����.
	char rus[15]; // ��������.
	Elem* left/*����� �������*/, * right/*������ �������*/, * parent/*��������*/;
};

class Tree
{
	// ������.
	Elem* root;
	// ���������� �����.
	int count;
public:
	Tree();
	~Tree();
	// ������ �� ���������� ����.
	void Print(Elem* Node);
	// ����� �� ���������� ����.
	Elem* Search(Elem* Node, char* key);
	// min �� ���������� ����.
	Elem* Min(Elem* Node);
	// max �� ���������� ����.
	Elem* Max(Elem* Node);
	// ��������� ��� ���������� ����.
	Elem* Next(Elem* Node);
	// ���������� ��� ���������� ����.
	Elem* Previous(Elem* Node);
	// ������� ����.
	void Insert(Elem* z);
	// �������� ����� ��� ���������� ����.
	void Del(Elem* z);
	// ���������� ����� ������.
	int GetCount() { return count; }
	// �������� ������.
	Elem* GetRoot();

	// ���������� ������ ������ � ����.
	void Save(Elem* Node, FILE* f);
	// �������� ������ �� �����.
	void Load(Elem* Node, FILE* f);
	// ������������ ��������� ������.
	void �alancing();
};