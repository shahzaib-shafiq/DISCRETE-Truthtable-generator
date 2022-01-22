#include<iostream>
#include<fstream>
#include<string.h>
#include<string>
using namespace std;

struct Relation
{
	int element1, element2;
	Relation* next2;
	Relation()
	{
		element1 = element2 = 0;
		next2 = NULL;
	}
};
Relation* head2, * tail2;
class KLASS
{
protected:
	struct Set
	{
		int element;
		Set* next1, * back1;
		Set()
		{
			element = 0;
			next1 = NULL;
			back1 = NULL;
		}
	};
	Set* head1, * tail1;
	int length;
	int NoOfRelation, CountSymmetric, CountAntiSymmetric, CountBoth;
public:
	KLASS()
	{
		length = 0;
		head1 = tail1 = NULL;
		head2 = tail2 = NULL;
		NoOfRelation = CountSymmetric = CountAntiSymmetric = CountBoth = 0;
	}
	void SetInsertion(int data)
	{
		Set* ptr = new Set;
		ptr->element = data;
		if (head1 == NULL)
		{
			head1 = ptr;
			tail1 = ptr;
		}
		else
		{
			ptr->back1 = tail1;
			tail1->next1 = ptr;
			tail1 = ptr;
		}
		length++;
	}
	void RelationInsertion(KLASS* obj1, KLASS* obj2)
	{
		Set* ptr1 = obj1->head1;
		while (ptr1 != NULL)
		{
			Set* ptr2 = obj2->head1;
			while (ptr2 != NULL)
			{
				Relation* ptr3 = new Relation;
				ptr3->element1 = ptr1->element;
				ptr3->element2 = ptr2->element;
				if (head2 == NULL)
				{
					head2 = ptr3;
					tail2 = ptr3;
				}
				else
				{
					tail2->next2 = ptr3;
					tail2 = ptr3;
				}
				ptr2 = ptr2->next1;
				NoOfRelation++;
			}
			ptr1 = ptr1->next1;
		}
	}
	void display(KLASS* obj1, KLASS* obj2)
	{
		Set* ptr1 = obj1->head1;
		cout << "SET A = { ";
		while (ptr1 != NULL)
		{
			cout << ptr1->element << " ";
			ptr1 = ptr1->next1;
		}
		cout << "}" << endl;
		ptr1 = obj2->head1;
		cout << "SET B = { ";
		while (ptr1 != NULL)
		{
			cout << ptr1->element << " ";
			ptr1 = ptr1->next1;
		}
		cout << "}" << endl;
		Relation* ptr2 = head2;
		cout << "A x B = { ";
		while (ptr2 != NULL)
		{
			cout << "( " << ptr2->element1 << ", " << ptr2->element2 << " ) ";
			ptr2 = ptr2->next2;
		}
		cout << " }" << endl;
	}
	bool equivalanceSet(KLASS* obj1, KLASS* obj2)
	{
		bool check = false;
		if (obj1->length == obj2->length)
		{
			Set* ptr1 = obj1->head1;
			Set* ptr2 = obj2->head1;
			while (ptr1 != NULL)
			{
				if (ptr1->element == ptr2->element)
				{
					ptr1 = ptr1->next1;
					ptr2 = obj2->head1;
					check = true;
				}
				else
				{
					check = false;
					ptr2 = ptr2->next1;
					if (ptr2 == NULL)
					{
						break;
					}
				}
			}
			if (check == true)
			{
				return check;
			}
			else
			{
				check = false;
				return check;
			}
		}
		else
		{
			check = false;
			return check;
		}
	}
	int getNoOfRelations()
	{
		return NoOfRelation;
	}
	void NoOfReflexiveRelation(KLASS* obj1, KLASS* obj2)
	{
		if (obj1->length == obj2->length || obj1->length < obj2->length)
		{
			bool check = false;
			Set* ptr1 = obj1->head1;
			Set* ptr2 = obj2->head1;
			while (ptr1 != NULL)
			{
				if (ptr1->element == ptr2->element)
				{
					ptr1 = ptr1->next1;
					ptr2 = obj2->head1;
					check = true;
				}
				else
				{
					check = false;
					ptr2 = ptr2->next1;
					if (ptr2 == NULL)
					{
						break;
					}
				}
			}
			if (check)
			{
				cout << "NUMBER OF REFLEXIVE REALTIONS = " << obj1->length << endl;
			}
			else
			{
				cout << "SET A AND B ARE NOT REFLEXIVE.\n";
			}
		}

		else
		{
			bool check = false;
			Set* ptr1 = obj1->head1;
			Set* ptr2 = obj2->head1;
			while (ptr2 != NULL)
			{
				if (ptr1->element == ptr2->element)
				{
					ptr2 = ptr2->next1;
					ptr1 = obj1->head1;
					check = true;
				}
				else
				{
					check = false;
					ptr1 = ptr1->next1;
					if (ptr1 == NULL)
					{
						break;
					}
				}
			}
			if (check)
			{
				cout << "NUMBER OF REFLEXIVE REALTIONS = " << obj2->length << endl;
			}
			else
			{
				cout << "SET A AND B ARE NOT REFLEXIVE.\n";
			}
		}
	}
	void NoOfSymmetricRelation(KLASS* obj1, KLASS* obj2)
	{
		CountSymmetric = 0;
		if (equivalanceSet(obj1, obj2))
		{
			cout << "NUMBER OF SYMMETRIC RELATIONS IN SET A AND B = " << (obj1->length) * 2 << endl;
		}
		else
		{
			Relation* dummyhead = MakeDummyRelations();
			Relation* ptr = dummyhead;
			while (ptr != NULL)
			{
				if (ptr->element1 != ptr->element2)
				{
					if (IsSymmetric(ptr->element1, ptr->element2, dummyhead))
					{
						CountSymmetric++;
						ptr->element1 = ptr->element2;
					}
				}
				ptr = ptr->next2;
			}
			cout << "NUMBER OF SYMMETRIC RELATIONS IN SET A AND B = " << CountSymmetric << endl;
		}
	}
	void NoOfAntiSymmetricRelation(KLASS* obj1, KLASS* obj2)
	{
		CountAntiSymmetric = 0;
		if (equivalanceSet(obj1, obj2))
		{
			cout << "NUMBER OF ANTYSYMMETRIC RELATIONS = " << obj1->length * obj2->length << endl;
		}
		else
		{
			Relation* dummyhead = MakeDummyRelations();
			Relation* ptr = dummyhead;
			while (ptr != NULL)
			{
				if (ptr->element1 != ptr->element2)
				{
					if (IsSymmetric(ptr->element1, ptr->element2, dummyhead))
					{
						bool check1 = IsReflexive(ptr->element1);
						bool check2 = IsReflexive(ptr->element2);
						if (check1 && check2)
							CountAntiSymmetric += 2;
						else
							CountAntiSymmetric++;
						ptr->element1 = ptr->element2;
					}
				}
				ptr = ptr->next2;
			}
			cout << "NUMBER OF ANTYSYMMETRIC RELATIONS = " << CountAntiSymmetric << endl;
		}
	}
	void BothSymmetricAndReflexive(KLASS* obj1, KLASS* obj2)
	{
		if (equivalanceSet(obj1, obj2))
		{
			cout << "NUMBER OF BOTH SYMMETRIC AND REFLEXIVE RELATIONS = " << (obj1->length) << endl;
		}
		else
		{
			cout << "THERE IS NO BOTH SYMMETRIC AND REFLEXIVE RELATIONS. " << endl;
		}
	}
	void BothSymmetricAndAntiSymmetric(KLASS* obj1, KLASS* obj2)
	{
		CountBoth = 0;
		if (equivalanceSet(obj1, obj2))
		{
			cout << "NUMBER OF ANTYSYMMETRIC RELATIONS = " << obj1->length * obj2->length << endl;
		}
		else
		{
			Relation* dummyhead = MakeDummyRelations();
			Relation* ptr = dummyhead;
			while (ptr != NULL)
			{
				if (ptr->element1 != ptr->element2)
				{
					if (IsSymmetric(ptr->element1, ptr->element2, dummyhead))
					{
						bool check1 = IsReflexive(ptr->element1);
						bool check2 = IsReflexive(ptr->element2);
						if (check1 && check2)
							CountBoth++;

						ptr->element1 = ptr->element2;
					}
				}
				ptr = ptr->next2;
			}
			cout << "NUMBER OF BOTH SYMMETRIC AND ANTYSYMMETRIC RELATIONS = " << CountBoth << endl;
		}
	}
	Relation* MakeDummyRelations()
	{
		Relation* dummyhead, * dummytail;
		dummyhead = dummytail = NULL;
		Relation* ptr = head2;
		while (ptr != NULL)
		{
			Relation* newptr = new Relation;
			newptr->element1 = ptr->element1;
			newptr->element2 = ptr->element2;
			if (dummyhead == NULL)
			{
				dummyhead = newptr;
				dummytail = newptr;
			}
			else
			{
				dummytail->next2 = newptr;
				dummytail = newptr;
			}
			ptr = ptr->next2;
		}
		return dummyhead;
	}
	bool IsSymmetric(int value1, int value2, Relation* dummyhead)
	{
		Relation* temp = dummyhead;
		while (temp != NULL)
		{
			if (temp->element1 == value2 && temp->element2 == value1)
			{
				return true;
			}
			temp = temp->next2;
		}
		return false;
	}
	bool IsReflexive(int value)
	{
		Relation* temp = head2;
		while (temp != NULL)
		{
			if (temp->element1 == value && temp->element2 == value)
			{
				return true;
			}
			temp = temp->next2;
		}
		return false;
	}
	Set* getHead()
	{
		return head1;
	}
};
class Stack
{
	struct Node
	{
		int data;
		Node* bottom;
		Node()
		{
			data = 0;
			bottom = NULL;
		}
	};
	int count;
	Node* top;
public:
	Stack()
	{
		count = 0;
		top = NULL;
	}
	void Push(int value)
	{
		Node* ptr = new Node();
		ptr->data = value;
		if (top == NULL)
		{
			top = ptr;
		}
		else
		{
			ptr->bottom = top;
			top = ptr;
		}
		count++;
	}
	int Pop()
	{
		if (IsEmpty())
		{
			return -1;
		}
		else
		{
			int val = top->data;
			Node* temp = top;
			top = top->bottom;
			temp->bottom = NULL;
			free(temp);
			count--;
			return val;
		}
	}
	bool IsEmpty()
	{
		if (top == NULL)
			return true;
		return false;
	}
};
class List
{
protected:
	struct Node
	{
		Node* next;
		int data, weight;
		Node() {
			data = weight = 0;
			next = NULL;
		}
	};
	Node* head = NULL;
	Node* tail = NULL;
public:
	List()
	{
		head = tail = NULL;
	}
	void Insert(int value, int weight = 0)
	{
		Node* newNode = new Node;
		newNode->data = value;
		newNode->weight = weight;
		if (head == NULL)
		{
			head = tail = newNode;
		}
		else
		{
			tail->next = newNode;
			tail = newNode;
		}
	}
	void Display()
	{
		Node* temp = head;
		while (temp != NULL)
		{
			if (temp->next == NULL)
				cout << temp->data << " " << temp->weight;
			else
				cout << temp->data << " " << temp->weight << "->";

			temp = temp->next;
		}
		cout << endl;
	}
	Node* getHead()
	{
		return head;
	}
};
//class Adj_PrimsList:public List
//{
//	List *obj;
//	Stack *S;
//	int V;
//public:
//	Adj_PrimsList()
//	{
//		ifstream Myfile;
//		int v = 0;
//		Myfile.open("PrimsFile.txt");
//		Myfile >> v;
//		V = v;
//		obj = new List[V];
//		S = new Stack();
//		Myfile.close();
//	}
//	void InsertInAdjacencyList()
//	{
//		int line1, line2, weight;
//		ifstream myFile;
//		myFile.open("PrimsFile.txt");
//		myFile >> line1;
//		while (myFile >> line1 >> line2 >> weight)
//		{
//			obj[line1].Insert(line2, weight);
//			obj[line2].Insert(line1, weight);
//		}
//		myFile.close();
//	}
//	
//	
//};
//class Adj_KruskalMatrix
//{
//	int **arr;
//	int V, E;
//public:
//	Adj_KruskalMatrix()
//	{
//		ifstream Myfile;
//		int v = 0, e = 0;
//		Myfile.open("KruskalFile.txt");
//		Myfile >> v >> e;
//		V = v;
//		E = e;
//		Myfile.close();
//		arr = new int*[V];
//		for (int i = 0; i < V; i++)
//		{
//			arr[i] = new int[E];
//			for (int j = 0; j < E; j++)
//				arr[i][j] = 0;
//		}
//	}
//	void InsertInAdjacencyMatrix()
//	{
//		int line1, line2, weight;
//		ifstream myFile;
//		myFile.open("KruskalFile.txt");
//		myFile >> line1 >> line2;
//		while (myFile >> line1 >> line2 >> weight)
//		{
//			arr[line1][line2] = weight;
//			arr[line2][line1] = weight;
//		}
//		myFile.close();
//	}
//};
//class Adj_EulerList : public List
//{
//	List *obj;
//	Stack *S;
//	int V, edgeCount;
//public:
//	Adj_EulerList(int check)
//	{
//		ifstream Myfile;
//		int v = 0;
//		if (check == 1)
//		{
//			Myfile.open("eulerCircuitFile.txt");
//		}
//		else
//		{
//			Myfile.open("eulerPathFile.txt");
//		}
//		Myfile >> v;
//		V = v;
//		edgeCount = 0;
//		obj = new List[V];
//		S = new Stack();
//		Myfile.close();
//	}
//	void InsertInAdjacencyList(int check)
//	{
//		int line1, line2, weight = 0;
//		ifstream myFile;
//		if (check == 1)
//		{
//			myFile.open("eulerCircuitFile.txt");
//		}
//		else
//		{
//			myFile.open("eulerPathFile.txt");
//		}
//		myFile >> line1;
//		while (myFile >> line1 >> line2)
//		{
//			obj[line1].Insert(line2, weight);
//			obj[line2].Insert(line1, weight);
//			weight++;
//		}
//		myFile.close();
//		edgeCount = weight;
//	}
//	
//	
//};
//class Adj_Bipartite:public KLASS,List
//{
//	KLASS *obj1, *obj2;
//	int V, maxRelation, relationFound;
//	List *bipartite;
//	Stack *S;
//public:
//	Adj_Bipartite()
//	{
//		ifstream Myfile;
//		Myfile.open("bipartiteFile.txt");
//		Myfile >> V;
//		Myfile >> maxRelation;
//		obj1 = new KLASS();
//		obj2 = new KLASS();
//		bipartite = new List[V];
//		S = new Stack();
//		Myfile.close();
//		relationFound = 0;
//	}
//	void InsertInBipartite()
//	{
//		int line1, line2, weight, count = 0;
//		char ch;
//		ifstream myFile;
//		myFile.open("bipartiteFile.txt");
//		myFile >> line1;
//		myFile >> line1;
//		while (myFile >> line1)
//		{
//			if (count == 0)
//				obj1->SetInsertion(line1);
//			else
//				obj2->SetInsertion(line1);
//
//			myFile.get(ch);
//			if (ch == '\n')
//			{
//				count++;
//			}
//			if (count >= 2)
//				break;
//		}
//		while (myFile >> line1>>line2)
//		{
//			bipartite[line1].Insert(line2);
//			bipartite[line2].Insert(line1);
//			relationFound++;
//		}
//		myFile.close();
//	}
//	void display()
//	{
//		Set *ptr1 = obj1->getHead();
//		cout << "SET A = { ";
//		while (ptr1 != NULL)
//		{
//			cout << ptr1->element << " ";
//			ptr1 = ptr1->next1;
//		}
//		cout << "}" << endl;
//		ptr1 = obj2->getHead();
//		cout << "SET B = { ";
//		while (ptr1 != NULL)
//		{
//			cout << ptr1->element << " ";
//			ptr1 = ptr1->next1;
//		}
//		cout << "}" << endl;
//	}


int main()
{
	int n, val;
	string choice;
	KLASS* obj1 = new KLASS();
	KLASS* obj2 = new KLASS();
	//Adj_KruskalMatrix *obj3 = new Adj_KruskalMatrix();
	//Adj_PrimsList *obj4 = new Adj_PrimsList();
	//Adj_EulerList *obj5 = new Adj_EulerList(1);
	//Adj_EulerList *obj6 = new Adj_EulerList(2);
	//Adj_Bipartite* obj7 = new Adj_Bipartite();
	//obj3->InsertInAdjacencyMatrix(); //for kruskal inserrtion
	//obj4->InsertInAdjacencyList(); //for prims insertion
	//obj5->InsertInAdjacencyList(1); //for euler circuit insertion
	//obj6->InsertInAdjacencyList(2); //for euler path insertion
	//obj7->InsertInBipartite(); // for bipartite insertion
	do
	{
		cout << "ENTER THE NUMBER OF ELEMENTS OF SET 'A' : ";
		cin >> n;
		if (n >= 3)
		{
			for (int i = 0; i < n; i++)
			{
				cout << "ENTER THE ELEMENT " << i + 1 << " OF SET 'A': ";
				cin >> val;
				obj1->SetInsertion(val);
			}
			break;
		}
		else
		{
			continue;
		}
	} while (true);
	do
	{
		cout << "ENTER THE NUMBER OF ELEMENTS OF SET 'B' : ";
		cin >> n;
		if (n >= 3)
		{
			for (int i = 0; i < n; i++)
			{
				cout << "ENTER THE ELEMENT " << i + 1 << " OF SET 'B': ";
				cin >> val;
				obj2->SetInsertion(val);
			}
			break;
		}
		else
		{
			continue;
		}
	} while (true);
	obj1->RelationInsertion(obj1, obj2); //for creating relations
	system("cls");
	do
	{
		cout << "- - - - - - - - - - - - M E N U - - - - - - - - - - - -\n\n";
		cout << "1) NUMBER OF RELATIONS.\n";
		cout << "2) NUMBER OF REFLEXIVE REALTIONS.\n";
		cout << "3) NUMBER OF SYMMETRIC RELATIONS.\n";
		cout << "4) NUMBER OF ANTI-SYMMETRIC RELATIONS.\n";
		cout << "5) NUMBER OF BOTH SYMMETRIC AND REFLEXIVE REALTIONS.\n";
		cout << "6) NUMBER OF BOTH SYMMETRIC AND ANTI-SYMMETRIC REALTIONS.\n";
		cout << "7) EXIT.\n\n";
		cin >> choice;
		if (choice == "1")
		{
			obj1->display(obj1, obj2);
			cout << "NUMBER OF RELATIONS = " << obj1->getNoOfRelations() << endl;
		}
		else if (choice == "2")
		{
			obj1->NoOfReflexiveRelation(obj1, obj2);
		}
		else if (choice == "3")
		{
			obj1->NoOfSymmetricRelation(obj1, obj2);
		}
		else if (choice == "4")
		{
			obj1->NoOfAntiSymmetricRelation(obj1, obj2);
		}
		else if (choice == "5")
		{
			obj1->BothSymmetricAndReflexive(obj1, obj2);
		}
		else if (choice == "6")
		{
			obj1->BothSymmetricAndAntiSymmetric(obj1, obj2);
		}

		system("pause>0");
		system("cls");
	} while (choice != "13");
}