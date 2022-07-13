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

// ����������� ����� ������
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
	// ���� ���� ���� � ����� �� ���������
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
	// ����� ������ "������" ����
	if (Node != nullptr)
		while (Node->left != nullptr)
			Node = Node->left;

	return Node;
}

Elem* Tree::Max(Elem* Node)
{
	// ����� ������ "�������" ����
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
		// ���� ���� ������ �������
		if (Node->right != nullptr)
			// ��������� ���� - ����� "����� ����" � ������ ��������� 
			return Min(Node->right);

		// �������� ����
		y = Node->parent;
		// ���� Node �� ������ � Node ������
		while (y != 0 && Node == y->right)
		{
			// �������� �����
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
		// ���� ���� ����� �������
		if (Node->left != nullptr)
			// ���������� ���� - ����� "������" ���� � ����� ��������� 
			return Max(Node->left);

		// �������� ����
		y = Node->parent;
		// ���� Node �� ������ � Node �����
		while (y != nullptr && Node == y->left)
		{
			// �������� �����
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

// ���������� ������ ������ � ����.
void Tree::Save(Elem* Node, FILE* f)
{

}

// �������� ������ �� �����.
void Tree::Load(Elem* Node, FILE* f)
{

}

// ������������ ��������� ������.
void Tree::�alancing()
{

}

void Tree::Insert(Elem* z)
{
	// �������� ���
	z->left = nullptr;
	z->right = nullptr;

	Elem* y = nullptr; // �������� ������������ ��������
	Elem* Node = root;

	// ����� �����
	while (Node != nullptr)
	{
		// ������� ��������
		y = Node;
		if (strcmp(z->eng, Node->eng) < 0)
			Node = Node->left;
		else
			Node = Node->right;
	}
	// ��������� ��������
	z->parent = y;

	if (y == nullptr) // ������� ������ (������������)
		root = z;
	// ��� ���� ������?
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
		Elem* Node = nullptr; // �������� ���� ��� ���������� ����
		Elem* y = nullptr; // ��������� ����
		// �� 2 �������
		if (z->left == nullptr || z->right == nullptr)
			y = z;
		else
			y = Next(z);

		if (y->left != nullptr)
			Node = y->left;
		else
			Node = y->right;
		// ���� ��������� �� ����
		if (Node != nullptr)
			Node->parent = y->parent;
		// ��������� �������� ����?
		if (y->parent == nullptr)
			root = Node;
		else if (y == y->parent->left) // ����� �� ��������?
			y->parent->left = Node;
		else
			y->parent->right = Node;  // ������ �� ��������?

		if (y != z)
		{
			// ����������� ������ ����
			strcpy_s(z->eng, y->eng);
			strcpy_s(z->rus, y->rus);
		}
		delete y;
		count--;
	}
}