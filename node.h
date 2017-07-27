#pragma once



////////////////////////////   CLASSE NODE: ÁRVORES BINÁRIAS   ////////////////////////////
template <class type>
class node_BT {
public:

	type data;
	node_BT * right;
	node_BT * left;
	node_BT * father;
	node_BT () {
		right = NULL;
		left = NULL;
		father = NULL;
	}
};

///////////////////////////////////   CLASSE ÁRVORE   ///////////////////////////////////
template <class type>
class BinaryTree {
private:
	int nNodes = 0;
	int max_p;

	node_BT <type> * head;
	
	//Definindo tipos...
	template <class T>
	class Foo {
	public:
		typedef  void (BinaryTree<type>::*ptFp)(void(BinaryTree<type>::*)(node_BT<type>*), T); 
		typedef void (BinaryTree<type>::*Fc) ( T *); 
	};

	template <typename T> using ptFp = typename Foo<T>::ptFp; // tipo: &function (&função, var)
	template <typename T> using Fc = typename Foo<T>::Fc; // tipo: &funtion (var)
	

	//Funções de percurso em árvore...
	
	void lrr ( Fc<node_BT<type>> Op, bool inverso = false ) ; // Percurso in-order left->root->right
	void bfs ( Fc<node_BT<type>> Op, bool inverso = false ) ; // Percurso em largura root->left->right
	
public:
	//Endereços de funções...
	ptFp<bool> LRR = &BinaryTree<type>::lrr; // endereço da função lrr
	ptFp<bool> BFS = &BinaryTree<type>::bfs; // endereço da função bfs
	
	//Funções da arvore...
	node_BT <type> * new_node ( type data , node_BT <type> * dad); // gerar novo node

	int insert ( type data); // inserir node gerado na head
	
	void print (ptFp<bool> ptF, bool inverso = false) ; // imprimir (endereço da função de percurso, inverso ou não)

	void search_f(Fc<node_BT<type>> Op, type key, int limit = 1, bool return_at_find = true); // achar key e executar função Op(var)
	void search_p(type key, int limit = 1); // imprimir a busca

	node_BT<type> * search_first_maior(node_BT<type> *temp);

	void delete_n(node_BT<type>*delNode);
	void del(type key, int limit = 1);

	void pp(node_BT <type> *a); // imprimir node
	void p(node_BT <type> *a); // somar node+1 -> teste.



	//void del() {};
	BinaryTree () {};
	~BinaryTree() {};
};



////////////////////////    FUNÇÕES DA ÁRVORE    ////////////////////////


//////// Função: Gerar novo Node ////////

template < class type >
node_BT < type > * BinaryTree < type > :: new_node ( type data , node_BT <type> * dad) {
	node_BT < type > * nNew = new node_BT < type > ();
	nNew->data = data;
	nNew->father = dad;
	nNew->left = NULL;
	nNew->right = NULL;

	return nNew;
};

//////// Função: Inserir o node gerado na posição adequada ////////

template < class type >
int BinaryTree < type > :: insert ( type data ) {
	if ( nNodes == 0 ) {
		head = new_node( data , NULL );
		nNodes++;
		return 1;
	}
	node_BT < type > * temp = this->head;

	while (true) {
		if (temp->data <= data) {
			if (temp->right == NULL) {
				temp->right = new_node ( data , temp ) ;
				nNodes++;
				return 1;
			}
			else {
				temp = temp->right;
			}
		}
		else {
			if (temp->left == NULL) {
				temp->left = new_node ( data , temp );
				nNodes++;
				return 1;
			}
			else {
				temp = temp->left;
			}
		}
	}
	return 0;
};

//  Função: Buscar o node com uma key n vezes e realizar a função Fc(var) em cada node encontrado 
template <class type>
void BinaryTree<type>::search_f(Fc<node_BT<type>> Op, type key, int limit = 1, bool return_at_find = true) {
	node_BT<type> *temp = this->head;
	for (int i = 0; i < limit && temp != NULL; i=i) {
		
		if (key == temp->data) {
			(this->*Op)(temp);
			//cout << temp->father->data;
			temp = temp->right;
			++i;
			//if (return_at_find) temp = this->head;
			continue;
		}
		else if (key > temp->data) {
			temp = temp->right;
		}
		else {
			temp = temp->left;
		}
	}
}

template <class type>
node_BT<type> * BinaryTree<type>::search_first_maior(node_BT<type> * temp) {
	if (temp == NULL) return temp;
	if (temp->right == NULL) return temp;
	node_BT<type> * tt = temp->right;
	while (tt->left != NULL) tt = tt->left;
	return tt;
}

//////////// FUNÇÕES: Varrer a Árvore ////////////


// Função: Percorrer (com pilha) em left->root->right ou right->root->left 
template <class type>
void BinaryTree <type> :: lrr (Fc<node_BT<type>> Op, bool inverso = false) {
	
	int top = -1; 
	node_BT <type> **item = new node_BT <type> *[ BinaryTree <type> :: nNodes ];
	

	node_BT <type> *temp = this->head;

	while (top != -1 || temp != NULL) {

		while (temp != NULL) {
			item[++top] = temp;
			temp = inverso ? temp->right : temp->left;
		}
		if (top != -1) {
			temp = item[top--];
			(this->*Op)(temp);
			temp = inverso ? temp->left : temp->right;
		}
	}

}
//////// Função: Percorrer (com filas) em largura root->left->right ////////
template <class type>
void BinaryTree <type> ::bfs( Fc<node_BT<type>> Op , bool inverso = false) {
	
	int f1 = -1, f2 = -1; // posição atual  e  posição final da fila
	node_BT <type> **item = new node_BT <type> *[ BinaryTree <type> :: nNodes +1]; // itens da fila
	
	node_BT <type> *temp = this->head;
	item[++f2] = temp;

	do{
		if (inverso) {
			if (temp->right != NULL) item[++f2] = temp->right;
			if (temp->left != NULL) item[++f2] = temp->left;
		}
		else {
			if (temp->left != NULL) item[++f2] = temp->left;
			if (temp->right != NULL) item[++f2] = temp->right;
		}

		if (f1 != f2) (this->*Op)(item[++f1]);
		temp = item[f1+1];
	} while (f1 != f2);


}


//////// Função: imprimir os nodes ////////
template <class type>
void BinaryTree <type> :: print (ptFp<bool> ptF, bool inverso = false) {
	(this->*ptF)(&BinaryTree<type>::pp, inverso);
	cout << endl;
}

template <class type>
void BinaryTree<type>::search_p(type key, int limit = 1) {
	search_f(&BinaryTree<type>::pp, key, limit, false);
}
template<class type>
void BinaryTree<type>::delete_n(node_BT<type>*delNode) {

	node_BT<type> * temp = delNode->father;
	
	if (delNode->left == NULL && delNode->right == NULL) {

		if (delNode != this->head) {
		
			if (temp->left == delNode)  temp->left = NULL;

			else temp->right = NULL;
		
		}
		else {

			this->head = NULL;
		}
	}
	else if (delNode->left == NULL) {

		if (delNode != this->head) {
		
			delNode->right->father = temp;

			if (temp->left == delNode)  temp->left = delNode->right;

			else temp->right = delNode->right;

		}
		else {
			this->head = delNode->right;
			this->head->father = NULL;
		}
	}
	else if (delNode->right == NULL) {

		if (delNode != this->head) {

			delNode->left->father = temp;

			if (temp->left == delNode) temp->left = delNode->left;

			else temp->right = delNode->left;
		
		}
		else {
			
			this->head = delNode->left;
			this->head->father = NULL;
		}	
	}
	else {
		
		node_BT<type> * maior = search_first_maior(delNode);

		if (delNode == this->head) {



			//////////////////////


			maior->left = delNode->left;

			if (maior->right == NULL) {

				maior->father = NULL;

				this->head = maior;

				free(delNode);
			}
			else {

				if (maior != delNode->right) {
					maior->father->left = maior->right;
					maior->right->father = maior->father;
				}

				maior->father = NULL;

				this->head = maior;

				free(delNode);
			}


			///////////////

		}
		else {

			maior->left = delNode->left;

			if (maior->right == NULL) {

				maior->father = delNode->father;

				if (maior == delNode->right)
					maior->right == NULL;
				else 
					maior->right = delNode->right;

				if (delNode->father->left == delNode) 
					delNode->father->left = maior;
				else 
					delNode->father->right = maior;
				
				free(delNode);
			}
			else {

				if (maior != delNode->right) {
					maior->father->left = maior->right;
					maior->right->father = maior->father;
				}

				maior->father = delNode->father;

				if (delNode->father->left == delNode)
					delNode->father->left = maior;
				else 
					delNode->father->right = maior;

				free(delNode);
			}
		}
	}
};

template<class type>
void BinaryTree<type>::del(type key, int limit = 1) {
	search_f(&BinaryTree<type>::delete_n, key, limit, true);

};

template <class type>
void BinaryTree<type>::pp ( node_BT <type> *a ) {
	cout << a->data << " ";
	
}
template <class type>
void BinaryTree<type>::p(node_BT <type> *a) {
	a->data++;	
}
