
#include <iostream>
#include <cstdlib>
#include <Windows.h>
using namespace std;

void slt()
{
	Sleep(700);
}

struct Node {
	int data;
	Node* next;
};
struct QueueL {
	Node* head;
	Node* tail;
};
bool QueueEmpty(QueueL a) {
	return a.head == nullptr;
}
void push(QueueL& a, int value) {
	bool empty = a.head == nullptr;

	Node* temp = new Node;
	temp->data = value;
	temp->next = nullptr;
	if (!empty) a.tail->next = temp;
	a.tail = temp;
	if (empty) a.head = temp;
	return;
}
int pop(QueueL& a) {
	int result = 0;
	if (!QueueEmpty(a))
	{
		Node* temp = a.head;
		result = a.head->data;
		a.head = a.head->next;
		delete temp;
	}
	else {
		cout << " Очередь пуста извлечение невозможно"; exit(1);
	}
	return result;
}
void ShowHead(QueueL& a) {
	cout << a.head->data << "\n";
}
void ShowTail(QueueL& a)
{
	cout << a.tail->data << "\n";
}
void Init_Queue(QueueL& a)
{
	a.head = nullptr;
	a.tail = nullptr;
}

struct QueueA {
	int arr[100];
	int start = 0;
	int end = 0;
};
bool QueueA_empty(QueueA* q)
{
	if (q->start == q->end)
		return true;
	else
		return false;
}
bool QueueA_full(QueueA* q)
{
	if (q->end == 100)
		return true;
	else 
		return false;
}
void QueueA_add(QueueA* q, int a)
{
	if (!QueueA_full(q))
	{
		q->arr[q->end] = a;
		q->end++;
	}
}
void QueueA_take(QueueA* q, int* a)
{
	if (!QueueA_empty(q))
	{
		*a = q->arr[q->start];
		q->start++;
	}
}
void QueueA_clear(QueueA* q)
{
	for (int i = 0; i < 100; i++)
	{
		q->arr[i] = NULL;
	}
	q->start = 0;
	q->end = 0;
}
void QueueA_out(QueueA* q)
{
	for (int i = q->start; i < q->end; i++)
	{
		if (i != q->start)
			cout << ", " << q->arr[i];
		else
			cout << q->arr[i];
	}
}

void arrqueue()
{
	int ch;
	int a;
	bool quit = false;
	QueueA q;
	do
	{
		system("cls");
		QueueA_out(&q);
		cout << "\n1. Добавить элемент\n";
		cout << "2. Вывести элемент\n";
		cout << "3. Очистить очередь\n";
		cout << "0. Назад\n";
		cout << "Действие: "; cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			QueueA_out(&q); cout << "\n";
			if (QueueA_full(&q))
			{
				cout << "Очередь заполнена";
				slt();
			}
			else
			{
				cout << "Введите элемент:"; cin >> a;
				QueueA_add(&q, a);
			}
			break;
		case 2:
			system("cls");
			QueueA_out(&q); cout << "\n";
			if (QueueA_empty(&q))
			{
				cout << "Очередь пуста";
				slt();
			}
			else
			{
				QueueA_take(&q, &a);
				cout << "Выведенный элемент: " << a;
				slt(); slt();
			}
			break;
		case 3:
			QueueA_clear(&q);
			break;
		case 0:
			quit = true;
			break;
		default:
			cout << "Ошибка";
			slt();
		}
	} while (!quit);
}

struct intST {
	int arr[100];
	int top = 0;
	int MAXsize = 100;
	int fill = 0;
};

struct QueueS {
	intST in;
	intST out;
};

void intST_push(intST& stack, int n)
{
	if (stack.top < stack.MAXsize)
	{
		stack.arr[stack.top] = n;
		stack.top++;
		if (stack.top == stack.MAXsize)
			stack.fill = 2;
		else
			stack.fill = 1;
	}
	else
	{
		cout << "Стек переполнен\n";
		slt();
	}
	return;
}
void intST_pop(intST& stack)
{
	if (stack.top > 0)
	{
		stack.top--;
		stack.arr[stack.top] = NULL;
		if (stack.top == 0)
			stack.fill = 0;
		else
			stack.fill = 1;
	}
	else
	{
		cout << "Стек уже пуст\n";
		slt();
	}
	return;
}
int intST_top(intST stack)
{
	return stack.arr[stack.top - 1];
}
void stacks_replace(intST& s1, intST& s2)
{
	if (s1.fill != 0 && s2.fill != 2)
	{
		int n = intST_top(s1);
		intST_push(s2, n);
		intST_pop(s1);
	}
	else if (s1.fill == 0)
	{
		cout << "\nПередающий стек пуст";
		slt();
	}
	else if (s2.fill == 2)
	{
		cout << "\nПолучающий стек уже полон";
		slt();
	}

}
bool QueueS_empty(QueueS* q) {
	return (q->in.top == 0 && q->out.top == 0);
}
bool QueueS_full(QueueS* q) {
	return (q->in.top == q->in.MAXsize);
}
void QueueS_add(QueueS* q, int value) {
	intST_push(q->in, value);
}
void QueueS_take(QueueS* q, int* out_value) {
	
	if (q->out.top == 0) {
		while (q->in.top > 0) {
			int val = intST_top(q->in);
			intST_pop(q->in);
			intST_push(q->out, val);
		}
	}
	
	*out_value = intST_top(q->out);
	intST_pop(q->out);
}
void QueueS_clear(QueueS* q) {
	q->in.top = 0;
	q->in.fill = 0;
	q->out.top = 0;
	q->out.fill = 0;
}
void QueueS_out(QueueS* q) {
	// Вывод стека out (от вершины к дну) – это начало очереди
	for (int i = q->out.top - 1; i >= 0; --i) {
		cout << q->out.arr[i] << " ";
	}
	// Вывод стека in (от дна к вершине) – продолжение очереди
	for (int i = 0; i < q->in.top; ++i) {
		cout << q->in.arr[i] << " ";
	}
}
void stackqueue()
{

	int ch;
	int a;
	bool quit = false;
	QueueS q;
	do
	{
		system("cls");
		QueueS_out(&q);
		cout << "\n1. Добавить элемент\n";
		cout << "2. Вывести элемент\n";
		cout << "3. Очистить очередь\n";
		cout << "0. Назад\n";
		cout << "Действие: "; cin >> ch;
		switch (ch)
		{
		case 1:
			system("cls");
			QueueS_out(&q); cout << "\n";
			if (QueueS_full(&q))
			{
				cout << "Очередь заполнена";
				slt();
			}
			else
			{
				cout << "Введите элемент:"; cin >> a;
				QueueS_add(&q, a);
			}
			break;
		case 2:
			system("cls");
			QueueS_out(&q); cout << "\n";
			if (QueueS_empty(&q))
			{
				cout << "Очередь пуста";
				slt();
			}
			else
			{
				QueueS_take(&q, &a);
				cout << "Выведенный элемент: " << a;
				slt(); slt();
			}
			break;
		case 3:
			QueueS_clear(&q);
			break;
		case 0:
			quit = true;
			break;
		default:
			cout << "Ошибка";
			slt();
		}
	} while (!quit);
}



int main()
{
	system("chcp 1251");
	int ch;
	bool quit = false;
	do
	{
		system("cls");
		cout << "** Меню **";
		cout << "\n1. Очередь через массив\n";
		cout << "2. Очередь через стеки\n";
		cout << "0. Выход\n";
		cout << "Действие: "; cin >> ch;
		switch (ch)
		{
		case 1:
			arrqueue();
			break;
		case 2:
			stackqueue();
			break;
		case 0:
			quit = true;
			break;
		default:
			cout << "Ошибка";
			slt();
		}
	} while (!quit);
	return 0;
}
