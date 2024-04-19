#include <iostream>
#include <string>

using namespace std;

struct tovar
{
	string name;
	float price;
	int amount;
	tovar* next;
};

tovar* tlist = NULL;

void AddBeginning(string n, float p, int am)
{
	tovar* first = new tovar;
	first->name = n;
	first->price = p;
	first->amount = am;
	first->next = tlist;
	tlist = first;
}

void AddEnd(string n, float p, int am)
{
	if (tlist == NULL)
	{
		AddBeginning(n, p, am);
	}
	else
	{
		tovar* last = new tovar;
		last->name = n;
		last->price = p;
		last->amount = am;
		last->next = NULL;

		tovar* tmp = tlist;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = last;
	}
}

void AddAfter(string n, float p, int am, string nafter)
{
	if (tlist == NULL)
	{
		AddBeginning(n, p, am);
	}
	else
	{
		tovar* tmp = tlist;
		while (tmp->name != nafter && tmp->next != NULL)
		{
			tmp = tmp->next;
		}

		if (tmp->name != nafter)
		{
			cout << "There is no such tovar in the list" << endl;
			return;
		}
		
		tovar* after = new tovar;
		after->name = n;
		after->price = p;
		after->amount = am;
		after->next = tmp->next;
		tmp->next = after;
	}
}

void AddBefore(string n, float p, int am, string nbefore)
{
	if (tlist == NULL || tlist->name == nbefore)
	{
		AddBeginning(n, p, am);
	}
	else
	{
		tovar* tmp = tlist;
		tovar* prev = NULL;
		while (tmp->name != nbefore && tmp != NULL)
		{
			prev = tmp;
			tmp = tmp->next;
		}

		if (tmp->name != nbefore)
		{
			cout << "There is no such tovar in the list" << endl;
			return;
		}

		tovar* before = new tovar;
		before->name = n;
		before->price = p;
		before->amount = am;
		before->next = tmp;
		prev->next = before;
	}
}

void Delete(string n)
{
	if (tlist == NULL)
	{
		cout << "List is empty" << endl;
		return;
	}

	tovar* tmp = tlist;
	tovar* prev = nullptr;
	while (tmp->name != n && tmp != nullptr)
	{
		prev = tmp;
		tmp = tmp->next;
	}

	// Если элемент не найден
	if (tmp->name != n)
	{
		cout << endl << "There is no such tovar in the list" << endl;
		return;
	}
	// Если элемент найден и он первый в списке
	if (prev == NULL)
	{
		tlist = tlist->next;
	}
	// Если элемент найден и он не первый в списке
	else 
	{
		prev->next = tmp->next;
	}

	delete tmp;
}

void PrintList()
{
	if (tlist == NULL)
	{
		cout << "List is empty" << endl;
	}
	else
	{
		tovar* tmp = tlist;
		while (tmp != NULL)
		{
			cout << "Name: " << tmp->name << "; Price: " << tmp->price 
				 << "; Amount: " << tmp->amount << endl;
			tmp = tmp->next;
		}
	}
}


int main()
{
	short action;
	string tovar;
	string name;
	float price;
	int amount;
	while (80085)
	{
		cout << "                                    Choose an action" << endl << endl;
		cout << "1 - Add at the begining; 2 - Add at the end; 3 - Add after element; 4 - Add before element;"
			 << endl << "5 - Delete element; 6 - Print list; 0 - Out" << endl;
		cin >> action;
		if (action == 0)
		{
			break;
		}
		else if (action == 1)
		{
			cout << "Input name: ";
			cin >> name;
			cout << "Input price: ";
			cin >> price;
			cout << "Input amount: ";
			cin >> amount;
			AddBeginning(name, price, amount);
		}
		else if (action == 2)
		{
			cout << "Input name: ";
			cin >> name;
			cout << "Input price: ";
			cin >> price;
			cout << "Input amount: ";
			cin >> amount;
			AddEnd(name, price, amount);
		}
		else if (action == 3)
		{
			cout << "Input name: ";
			cin >> name;
			cout << "Input price: ";
			cin >> price;
			cout << "Input amount: ";
			cin >> amount;
			cout << "Input previous element: ";
			cin >> tovar;
			AddAfter(name, price, amount, tovar);
		}
		else if (action == 4)
		{
			cout << "Input name: ";
			cin >> name;
			cout << "Input price: ";
			cin >> price;
			cout << "Input amount: ";
			cin >> amount;
			cout << "Input next element: ";
			cin >> tovar;
			AddBefore(name, price, amount, tovar);
		}
		else if (action == 5)
		{
			cout << "Input name: ";
			cin >> tovar;
			Delete(tovar);
		}
		else if (action == 6)
		{
			PrintList();
		}
		else
		{
			cout << "Wrong input" << endl;
			continue;
		}
	}

	return 0;
}