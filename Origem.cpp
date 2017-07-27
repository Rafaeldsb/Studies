#include <iostream>
#include <vector>
#include <stack>
#include <Windows.h>
#include <typeinfo>
#include <string>
#include "Nodes.h"


using namespace std;

/*
#define MAX_STACK 100

struct node {
	int data;
	node *left;
	node *right;
};
int nNode = 0;




void insert(node **head, int data) {
	node *new_node = new node();
	new_node->data = data;
	new_node->left = NULL;
	new_node->right = NULL;

	nNode++;

	if (*head == NULL) {
		*head = new_node;
		return;
	}
	node *temp = *head;

	while (true) {
		if (temp->data <= data) {
			if (temp->right == NULL) {
				temp->right = new_node;
				return;
			}
			else {
				temp = temp->right;
			}
		}
		else {
			if (temp->left == NULL) {
				temp->left = new_node;
				return;
			}
			else {
				temp = temp->left;
			}
		}
	}
}

void erd_rp(node *head) {
	node *temp = head;
	if (temp != NULL) {
		erd_rp(temp->left);
		//cout << temp->data << endl;
		erd_rp(temp->right);
	}
}



void print_srp(node *head) {
	

	struct stack { int top; node *item[MAX_STACK]; } s;
	node *temp = head;
	s.top = -1;
	do {
		while (temp != NULL) {
			s.item[++s.top] = temp;
			temp = temp->right;
		}
		if (s.top != -1) {
			temp = s.item[s.top--];
			cout << "Valor: " << temp->data << endl;
			temp = temp->left;
		}
	} while (!(s.top == -1 && temp == NULL));
	
}

void erd(node *head) {
	struct stack { int top = -1; node *item[MAX_STACK];	} s;
	
	node *temp = head;

	while (s.top != -1 || temp != NULL) {
		
		while (temp != NULL) {
			s.item[++s.top] = temp;
			temp = temp->left;
		}
		if (s.top != -1) {
			temp = s.item[s.top--];
			//cout << "Valor: " << temp->data << endl;
			temp = temp->right;
		}
	}

}

void prints(node *head) {
	stack<node*> pilha;
	pilha.push(head);
	
		while (!pilha.empty()) {
			if (pilha.top()->left != NULL) {
				pilha.push(pilha.top()->left);
				
			}
			else {
				node *n = pilha.top();
				printf("%d ", n->data);
				pilha.pop();
				if (n->right != NULL) {
					pilha.push(n->right);
					
				}
				
			}
		}
}


*/

class teste {
public:
	node_BT<int> *bla = new node_BT<int>;
	void ptf(void (teste::*Op) (node_BT<int>*),
		node_BT<int> *t) { 
		node_BT <int> **item = new node_BT <int>*[5];
		item[0] = t;
		(this->*Op)(item[0]);
	}

	void p() {
		void(teste::*ptF)(node_BT<int>*) = &teste::pt;
		
		ptf(&teste::pt, bla);
	}
	void pt(node_BT<int>* b) {
		b->data = 1; 
	}
};



	int main() {

		teste *ka = new teste;
		ka->bla->data = 5;
		ka->p();
		//cout << ka->bla->data << endl;

	
	
		//node_BT<double> *a = new node_BT<double>() ;
		BinaryTree<int> b;

		int ins[] = { 5,-7,0,5,15,1,9,-3,4,16 };
		int del[] = {5,5};

		for (auto i : ins) {
			b.insert(i);
		}

		b.print(b.BFS);
		cout << "\n";

		for (auto i : del) {
			b.del(i);
			b.print(b.BFS);
			cout << "\n";
		}







		getchar();



	}
