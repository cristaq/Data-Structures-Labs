/*
*	Created by Nan Mihai on 05.05.2021
*	Copyright (c) 2020 Nan Mihai. All rights reserved.
*	Laborator 6 - Structuri de date
*	Grupa 314CD
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Tree parent, Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->parent = parent;
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Tree parent, Item value) {
	// TODO 0
	Tree newnode = malloc(sizeof(TreeNode));
	newnode->parent = parent;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->value = value;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 1
	Tree p = root;
	if(root == NULL)
		return createTree(NULL, value);
	if(value == root->value)
		return root;
	if(value > p->value)
		if(p->right != NULL)
			p->right = insert(p->right, value);
		else {
			p->right = createTree(p, value);
			return root;
		}
	else
		if(p->left != NULL)
			p->left = insert(p->left, value);
		else {
			p->left = createTree(p, value);
			return root;
		}
	return root;
}


/*
*	Funcție care verifică dacă un arbore este vid sau nu
*		- întoarce 1 dacă arborele este vid
*		- întoarce 0 dacă arborele nu este vid
*/
int isEmpty(Tree root) {
	// TODO 2
	return root == NULL ? 1 : 0;
}

/*
*	Funcție care verifică dacă o valoare există sau nu în arbore
*		- 1 dacă value există în arbore
*		- 0 dacă value nu există în arbore
*/
int contains(Tree tree, Item value) {
	// TODO 3
	if(tree != NULL) {
		if(tree->value == value)
			return 1;
		else if(tree->left != NULL && tree->value > value)
			return contains(tree->left, value);
		else if(tree->right != NULL && value > tree->value)
			return contains(tree->right, value);
	}
	return 0;
}

/*
*	Funcție care determină elementul minim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree minimum(Tree tree) {
	// TODO 4.1
	if(tree == NULL)
		return NULL;
	if(tree->left == NULL) {
		return tree;
	}
	else
		return minimum(tree->left);
}

/*
*	Funcție care determină elementul maxim dintr-un arbore binar de căutare
*		- NULL pentru arbore vid
*/
Tree maximum(Tree tree) {
	// TODO 4.2
	if(tree == NULL)
		return NULL;
	if(tree->right == NULL) {
		return tree;
	}
	else
		return maximum(tree->right);
}

/*
*	Funcție care determină succesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree successor(Tree root, Item value) {
	// TODO 5
	if(root == NULL)
		return NULL;
	Tree p = root, succ;
	while(p != NULL && p->value != value) {
		if(value < p->value)
			p = p->left;
		else if(value > p->value)
			p = p->right;
	}
	if(p == NULL)
		return NULL;
	if(p->right != NULL) {
		succ = minimum(p->right);
	}
	else {
		succ = p->parent;
		while(succ != NULL && p != succ->left) {
			p = succ;
			succ = succ->parent;
		}
	}
	return succ;
}

/*
*	Funcție care determină predecesorul în inordine pentru nodul care conține
* valoarea value.
*/
Tree predecessor(Tree root, Item value) {
	// TODO 6
	if(root == NULL)
		return NULL;
	Tree p = root, pred;
	while(p != NULL && p->value != value) {
		if(value < p->value)
			p = p->left;
		else if(value > p->value)
			p = p->right;
	}
	if(p == NULL)
		return NULL;
	if(p->left != NULL) {
		pred = maximum(p->left);
	}
	else {
		pred = p->parent;
		while(pred != NULL && p != pred->right) {
			p = pred;
			pred = pred->parent;
		}
	}
	return pred;
}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void destroyTree(Tree *root) {
	// TODO
	if(*root == NULL)
		return;
	if((*root) != NULL) {
		destroyTree(&((*root)->left));
		destroyTree(&((*root)->right));
		free((*root));
		*root = NULL;
	}
}

/*
*	Funcție care șterge un nod cu o anumită valoare din arbore
*/
Tree delete(Tree root, Item value) {
	// TODO 7
	if(root == NULL)
		return NULL;
	Tree p = root, nod;
	while(p != NULL && p->value != value) {
		if(value < p->value)
			p = p->left;
		else if(value > p->value)
			p = p->right;
	}
	if(p == NULL)
		return root;
	if(p->left == NULL && p->right == NULL) {
		if(p->parent->left == p)
			p->parent->left = NULL;
		else
			p->parent->right = NULL;
		free(p);
	}
	else if(p->left != NULL && p->right != NULL) {
		nod = successor(root, p->value);
		int val = nod->value;
		root = delete(root, nod->value);
		p->value = val;
	}
	else {
		Tree child = (p->left)? p->left : p->right;
		if (p != root) {
            if (p == p->parent->left) {
            	p->parent->left = child;
            }
            else {
                p->parent->right = child;
            }
        }
        else {
            root = child;
        }
		free(p);
	}
	return root;
}

/*
*	Funcție care determină cel mai apropiat strămoș comun pentru
* două noduri având cheile value1 și value2
*/
Tree lowestCommonAncestor(Tree root, Item value1, Item value2) {
	// TODO 8
	if(root == NULL)
		return NULL;
	if(root->value > value1 && root->value > value2)
		return lowestCommonAncestor(root->left, value1, value2);
	if(root->value < value1 && root->value < value2)
		return lowestCommonAncestor(root->right, value1, value2);
	
	return root;
	
}
