//Main for Polynomial Program
//Format and fix the output and validation

#include <iostream>
#include <string>
using namespace std;

const int MAX_POLY = 13;

struct Node
{
	int coEff;
	int exp;
	struct Node* next;
};

Node* createNode(int, int, Node*);
void show(Node*);
string convertToFinal(Node*);
void displayFinal(string);
int getPolyNumber();
string getPolynomials(int);
string validatePolynomials(string);
Node* convertToList(string, int, string&, string&);
Node* add(Node**, int);
Node* multiply(Node**, int);
Node* resetList(Node*);
Node* simplify(Node*);
Node* sort(Node*);
Node* mult(Node*, Node*);
Node* addition(Node*, Node*);

int main()
{
	int x;
	string str;
	string addDisplay;
	string multDisplay;

	do
	{
		x = getPolyNumber();	//validate

		if (x == 0)
		{
			return 0;
		}

		Node* list[MAX_POLY];
		int i = 0;

		while (i < x)
		{
			str = getPolynomials(i);
			list[i] = convertToList(str, i, addDisplay, multDisplay);
			i++;
		}

		for (int i = 1; i <= 2; i++)
		{
			addDisplay.pop_back();
			multDisplay.pop_back();
		}

		Node* temp[MAX_POLY];

		for (int i = 0; i < x; i++)
		{
			temp[i] = resetList(list[i]);
		}

		Node* sum = add(list, x);

		cout << endl;
		cout << "sum = " << addDisplay << endl << "    = ";
		string sumFinal = convertToFinal(sum);
		displayFinal(sumFinal);

		for (int i = 0; i < x; i++)	//resets the list for the multiply function
		{
			list[i] = temp[i];
		}

		Node* product = multiply(list, x);
		cout << endl;
		cout << "product = " << multDisplay << endl << "        = ";

		string productFinal = convertToFinal(product);
		displayFinal(productFinal);

	} while (true);

	return 0;
}



//-------------------------------------------------------------
// Resets the linked list so that we can use the list again.
// 
// @param - Node*
// @return - Node*
//-------------------------------------------------------------

Node* resetList(Node* first)
{
	Node* head;
	Node* temp = new Node;
	temp->coEff = first->coEff;
	temp->exp = first->exp;
	temp->next = nullptr;
	head = temp;

	if (first->next)
	{
		first = first->next;
	}

	while (first)
	{
		if (temp)
		{
			temp->next = new Node;
			temp = temp->next;
			temp->coEff = first->coEff;
			temp->exp = first->exp;
			temp->next = nullptr;
		}
		first = first->next;
	}

	temp = head;

	return head;
}


//-------------------------------------------------------------
// Multiplies the linked list by nodes and returns an address 
// to the node
// 
// @param - Node*, Node*
// @return - Node*
//-------------------------------------------------------------

Node* mult(Node* p1, Node* p2)
{
	Node* temp = new Node;

	temp->coEff = p1->coEff * p2->coEff;
	temp->exp = p1->exp + p2->exp;
	temp->next = nullptr;

	return temp;
}


//-------------------------------------------------------------
// sums the linked list node by node, then returns the address 
// to the node.
// 
// @param - Node*, Node*
// @return - Node*
//-------------------------------------------------------------

Node* addition(Node* p1)	//has p2 head, add and simplify the list
{
	Node* head = p1;
	Node* ptr = p1->next;

	while (p1)
	{
		while (ptr)
		{
			if (p1->exp == ptr->exp)
			{
				p1->coEff += ptr->coEff;
				ptr->coEff = 0;
				ptr->exp = 0;
			}
			ptr = ptr->next;
		}

		p1 = p1->next; 
		ptr = p1->next;
		if (!p1->next)	
		{
			break;
		}
	}

	p1 = head;
	ptr = head;

	if (ptr)
	{
		ptr = ptr->next;
	}

	while (ptr)		//loop back through list and delete nodes that are 0
	{
		if (ptr->coEff == 0 && ptr->exp == 0)
		{
			p1->next = ptr->next;
			ptr = ptr->next;
		}
		else
		{
			if (p1)
			{
				p1 = p1->next;
			}
			ptr = ptr->next;
		}
	}

	return head;
}


//-------------------------------------------------------------
// Multiplies the linked list into one list.
// 
// @param - Node**, int
// @return - void
//-------------------------------------------------------------

Node* multiply(Node* list[MAX_POLY], int polyNum)
{
	Node* product = list[0];
	Node* p1 = nullptr;
	Node* p1Head = nullptr;
	Node* p2 = nullptr;
	Node* p2Head = nullptr;
	bool firstTime = true;

	for (int i = 1; i < polyNum; i++)
	{
		p1 = list[i];
		p1Head = p1;
		firstTime = true;

		while (product)
		{
			while (p1)
			{
				if (firstTime)
				{
					p2 = mult(product, p1);
					p2Head = p2;
					firstTime = false;
					p1 = p1->next;
				}
				else
				{
					p2->next = mult(product, p1);
					p2 = p2->next;
					p2->next = nullptr;
					p1 = p1->next;
				}
			}
			p1 = p1Head;
			product = product->next;
		}

		product = addition(p2Head); //simplifies p2 and returns head ptr
		p2 = new Node;
		p2Head = p2;
	}

	return product;


}


//-------------------------------------------------------------
// Adds the linked list into one list
// 
// @param - Node**, int
// @return - void
//-------------------------------------------------------------

Node* add(Node* list[MAX_POLY], int polyNum)
{
	Node* sum = new Node;
	Node* sumHead = sum;
	Node* head = sum;
	Node* temp;
	bool firstNode = false;

	for (int i = 0; i < polyNum; i++)
	{
		while (list[i])
		{
			if (i == 0 && !firstNode)
			{
				sum->coEff = list[i]->coEff;
				sum->exp = list[i]->exp;
				sum->next = nullptr;
				list[i] = list[i]->next;
				firstNode = true;
			}
			else
			{
				if (list[i])
				{
					temp = new Node;
					temp->coEff = 0;
					temp->exp = 0;
					temp->coEff += list[i]->coEff;
					temp->exp += list[i]->exp;
					sum->next = temp;
					sum = sum->next;
					list[i] = list[i]->next;
				}
			}
		}
	}
	sum->next = nullptr;	//needs to set the pointers to null
	sum = sumHead;
	sum = simplify(sumHead);
	sum = sumHead;

	return sum;

}


//-------------------------------------------------------------
// Simplifies the linked list
// 
// @param - Node*
// @return - Node*
//-------------------------------------------------------------

Node* simplify(Node* head)
{
	Node* sum = head;
	Node* nodePtr = sum->next;

	while (sum)
	{
		while (nodePtr)
		{
			if ((sum->exp == nodePtr->exp) && nodePtr->coEff != 0)
			{
				sum->coEff += nodePtr->coEff;
				nodePtr->coEff = 0;
				nodePtr->exp = 0;
			}
			nodePtr = nodePtr->next;
		}
		if (sum->next)
		{
			sum = sum->next;
			nodePtr = sum->next;
		}
		else
			break;
	}
	sum = head;
	Node* previousPtr = head;

	if (sum)
	{
		sum = sum->next;
	}

	//loop back through list and delete nodes that are 0
	while (sum)
	{
		if (sum->coEff == 0 && sum->exp == 0)
		{
			previousPtr->next = sum->next;
			sum = sum->next;
		}
		else
		{
			if (previousPtr)
			{
				previousPtr = previousPtr->next;
			}
			sum = sum->next;
		}
	}

	sum = head;
	return head;
}


//-------------------------------------------------------------
// Sorts the linked list into ascending order
// 
// @param - Node*
// @return - Node*
//-------------------------------------------------------------

Node* sort(Node* sum)
{
	Node* head = sum;
	Node* highestPtr = head;
	Node* ptr = head;
	Node* newListNode = new Node;
	Node* newHead = newListNode;
	Node* newPtr = newHead;
	bool newHeadFlag = false;

	while (head)
	{
		highestPtr = head;
		ptr = head;
		newPtr = newHead;

		while (ptr)
		{
			if (ptr->exp > highestPtr->exp)
			{
				highestPtr = ptr;
			}
			ptr = ptr->next;
		}

		if (highestPtr->coEff == 0 && highestPtr->exp == 0) //terminating case
		{
			break;
		}

		if (!newHeadFlag)
		{
			newListNode->coEff = highestPtr->coEff;
			newListNode->exp = highestPtr->exp;
			highestPtr->coEff = 0;
			highestPtr->exp = 0;
			newHeadFlag = true;
		}
		else
		{
			newListNode = new Node;

			while (newPtr->next)	//traverses the new list
			{
				newPtr = newPtr->next;
			}

			newPtr->next = newListNode;
			newListNode->coEff = highestPtr->coEff;
			newListNode->exp = highestPtr->exp;
			highestPtr->coEff = 0;
			highestPtr->exp = 0;
		}
	}
	return head;
}


//-------------------------------------------------------------
// Creates a node with the coefficient and exponent values
// 
// @param - int, int, int
// @return - Node*
//-------------------------------------------------------------

Node* createNode(int coeff, int exp, Node* temp)
{
	Node* first;
	Node* nodePtr;
	Node* head = temp;
	if (head == nullptr)
	{
		first = new Node;
		first->coEff = coeff;
		first->exp = exp;
		first->next = nullptr;
		head = first;
	}
	else
	{
		nodePtr = head;
		while (nodePtr->next)
		{
			nodePtr = nodePtr->next;
		}

		first = new Node;
		first->coEff = coeff;
		first->exp = exp;
		first->next = nullptr;
		nodePtr->next = first;
	}

	return head;
}


//-------------------------------------------------------------
// Displays the linked list given
// 
// @param - Node*
// @return - void
//-------------------------------------------------------------

void show(Node* node)
{
	cout << "Displaying Nodes\n";
	while (node)
	{
		cout << node->coEff << " " << node->exp << endl;
		node = node->next;
	}
}


//-------------------------------------------------------------
// Gets the number of polynomials that the user is concerned 
// with. 
// 
// @param - void
// @return - int
//-------------------------------------------------------------

int getPolyNumber()
{
	int x;
	bool flag;
	cout << "\nNumber of polynomials -> ";
	cin >> x; 

	if (x != 0)
	{
		while (x < 2 || x > 13)
		{
			cout << "\nTry again: ";
			cin >> x;
		}
		cout << endl;
	}

	return x;
}


//-------------------------------------------------------------
// Gets the inputted polynomials from the user
// 
// @param - int
// @return - string
//-------------------------------------------------------------

string getPolynomials(int index)
{
	string str;

	cout << "Input polynomial " << (index + 1) << " -> ";
	getline(cin >> ws, str);

	str = validatePolynomials(str);

	return str;
}


//-------------------------------------------------------------
// Converts input to final output's format
// 
// @param - Node*
// @return - string
//-------------------------------------------------------------

string convertToFinal(Node* ptr) 
{
	string str;

	while (ptr)
	{
		str = str + to_string(ptr->coEff);

		if (ptr->exp > 1)
		{
			str += "x^";
			str += to_string(ptr->exp);

		}
		else
		{
			str += "x";
		}

		str += " ";
		ptr = ptr->next;
	}

	return str;
}


//-------------------------------------------------------------
// Displays the final results in foramtted output
// 
// @param - string
// @return - void
//-------------------------------------------------------------

void displayFinal(string str)
{
	cout << str << endl;
}



//-------------------------------------------------------------
// Validates the polynomials inputted by the user
// 
// @param - string
// @return - string
//-------------------------------------------------------------

string validatePolynomials(string str)
{
	string temp;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == ' ')
			continue;
		else
			temp += str[i];
	}

	return temp;
}


//-------------------------------------------------------------
// Converts the inputted polynomials into their 
// corresponding linked lists.
// 
// @param - string, int, string&, string&
// @return - Node*
//-------------------------------------------------------------

Node* convertToList(string str, int index, string& addDisplay, string& multDisplay)
{
	Node* nPtr = nullptr;
	string tempTerm[MAX_POLY];
	string strTerm;
	string strCoeff;
	string strExp;
	int term = 0;
	int coeff = 0;
	int exp = 0;
	int j = 0;
	bool flag;

	for (int i = 0; i < str.length(); i++)	//gets each term into a different index in tempTerm
	{
		if (str[i] == ' ') //gets rid of the whitespace in string
		{
			continue;
		}

		if (i == 0 && str[0] == '-') //maybe change to '-' only
		{
			tempTerm[term] = str[i];	//means there is a negative term
			continue;
		}

		if (i > 0 && (str[i] == '+' || str[i] == '-') && str[i - 1] != '^')	//means we have a new term
		{
			term++;
		}
		tempTerm[term] += str[i];
	}

	for (int i = 0; i <= term; i++)	//works bc im not counting that first term. (term - 1)
	{
		flag = false;
		strTerm = tempTerm[i];
		strCoeff = "";
		strExp = "";
		for (int j = 0; j < tempTerm[i].length(); j++)
		{
			if (strTerm[j] == 'x' && strTerm[j + 1] != '^')
			{
				strExp = '1';
			}

			if (strTerm[j] == 'x' || strTerm[j] == '^')
			{
				flag = true;
				continue;
			}

			if (strTerm[j] == '+')
			{
				continue;
			}

			if (!flag)
			{
				strCoeff += strTerm[j];
			}

			if (flag)
			{
				strExp += strTerm[j];
			}

		}

		coeff = stoi(strCoeff);

		if (!strExp.empty())
		{
			exp = stoi(strExp);
			nPtr = createNode(coeff, exp, nPtr);
		}
		else
		{
			nPtr = createNode(coeff, 0, nPtr);
		}
	}

	addDisplay += "(";
	multDisplay += "(";

	for (int i = 0; i <= term; i++)
	{
		addDisplay += tempTerm[i];
		multDisplay += tempTerm[i];
	}
	addDisplay = addDisplay + ") " + "+ ";
	multDisplay = multDisplay + ") " + "* ";

	return nPtr;
}