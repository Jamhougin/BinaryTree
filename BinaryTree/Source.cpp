#include <iostream>
//James Hall
//Dec 2019

typedef struct node {
	int data;
	node* left;
	node* right;
	node* parent;
}*nodeptr;


nodeptr root = NULL;


nodeptr getnode(nodeptr prnt, int data) {
	nodeptr newnode = new node;
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	newnode->parent = prnt;
	return newnode;
}

nodeptr search(nodeptr root, int data) {
	if (root == NULL) {
		return NULL;
	}
	else if (root->data == data) {
		return root;
	}
	else if (root->data > data) {
		return search(root->left, data);
	}
	else {
		return search(root->right, data);
	}
}

nodeptr insert(nodeptr prnt, nodeptr root, int data) {
	if (root == NULL)
	{
		root = getnode(prnt, data);
	}
	else if (root->data > data)
	{
		prnt = root;
		root->left = insert(prnt, root->left, data);
	}
	else if (root->data < data)
	{
		prnt = root;
		root->right = insert(prnt, root->right, data);
	}
	return root;
}

nodeptr smallest(nodeptr root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

nodeptr largest(nodeptr root) {
	while (root->right != NULL) {
		root = root->right;
	}
	return root;
}

int nextLowest(nodeptr root, int toFind) {
	nodeptr predecessor = NULL;
	nodeptr current = root;

	if (!root)
		return NULL;

	while (current && current->data != toFind) {
		if (current->data > toFind) {
			current = current->left;
		}
		else {
			predecessor = current;
			current = current->right;
		}
	}
	if (current && current->left) {
		predecessor = largest(current->left);
	}
	return predecessor->data;
}

int nextHighest(nodeptr root, int toFind) {
	nodeptr current = root;

	if (!root)
		return NULL;
	//while finds address of value toFind
	while (current && current->data != toFind) {
		if (current->data > toFind) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	if (current->right != NULL) {
		return smallest(current->right)->data;
	}
	else {
		struct node* successor = current->parent;
		while (successor != NULL && current == successor->right)
		{
			current = successor;
			successor = successor->parent;
		}
		return successor->data;
	}
}

bool hasLeft(nodeptr root) {
	if (root != NULL && root->left != NULL) {
		return true;
	}
	return false;
}

bool hasRight(nodeptr root) {
	if (root != NULL && root->right != NULL) {
		return true;
	}
	return false;
}

int left(nodeptr root) {
	if (hasLeft(root)) {
		return root->left->data;
	}
}

int right(nodeptr root) {
	if (hasRight(root)) {
		return root->right->data;
	}
}

bool isLeaf(nodeptr root) {
	if (root != NULL && root->right == NULL && root->left == NULL) {
		return true;
	}
	return false;
}

void display(nodeptr root) {
	if (root) {
		display(root->left);
		std::cout << root->data << " ";
		display(root->right);
	}
}

int height(node* root)
{
	if (root == NULL)
		return 0;
	else {
		int lHeight = height(root->left);
		int rHeight = height(root->right);

		if (lHeight > rHeight) {
			return(lHeight + 1);
		}
		else return(rHeight + 1);
	}
}

bool deleteNode(nodeptr root, int val) {
	nodeptr toDel = search(root, val);
	if (toDel == NULL) {
		return false;
	}
	else {
		if (isLeaf(toDel)) {
			if (toDel->data == toDel->parent->right->data) {
				toDel->parent->right = NULL;
				delete toDel;
			}
			else {
				toDel->parent->left = NULL;
				delete toDel;
			}
			return true;
		}
		//If node has 2 children
		else if (hasLeft(toDel) && hasRight(toDel)) {
			nodeptr toSwap = search(root, nextHighest(root, toDel->data));
			toDel->data = toSwap->data;
			if (toDel->data == toDel->right->data) {
				toDel->right = toDel->right->right;
				delete toSwap;
			}
			else {
				//delete swapped in node
				deleteNode(toSwap, toSwap->data);
			}
		}
		//If node has one child
		else if (!hasLeft(toDel) && hasRight(toDel)) {
			toDel->parent->right = toDel->right;
			delete toDel;
		}
		else if (hasLeft(toDel) && !hasRight(toDel)) {
			toDel->parent->left = toDel->left;
			delete toDel;
		}
	}
}

void deleteAll(node* &root) {
	if (!root) {
		return;
	}

	deleteAll(root->left);
	deleteAll(root->right);
	delete root;
	root = NULL;

}

int main() {
	root = insert(root, root, 12);
	root = insert(root, root, 20);
	root = insert(root, root, 5);
	root = insert(root, root, 18);
	root = insert(root, root, 3);
	root = insert(root, root, 4);
	root = insert(root, root, 45);
	root = insert(root, root, 59);
	display(root);
	std::cout << "\n";
	std::cout << height(root) << "\n";
	//*******************************************
	//Check has Left
	if (hasLeft(search(root, 20))) {
		std::cout << "Has Left\n";
	}
	else std::cout << "Has no Left\n";

	if (hasLeft(search(root, 45))) {
		std::cout << "Has Left\n";
	}
	else std::cout << "Has no Left\n";
	//*******************************************
	//Check has Right
	if (hasRight(search(root, 45))) {
		std::cout << "Has Right\n";
	}
	else std::cout << "Has no Right\n";

	if (hasRight(search(root, 18))) {
		std::cout << "Has Right\n";
	}
	else std::cout << "Has no Right\n";
	//*******************************************
	//Check is Leaf
	if (isLeaf(search(root, 20))) {
		std::cout << "Is Leaf\n";
	}
	else std::cout << "Is not Leaf\n";

	if (isLeaf(search(root, 45))) {
		std::cout << "Is Leaf\n";
	}
	else std::cout << "Is not Leaf\n";

	if (isLeaf(search(root, 18))) {
		std::cout << "Is Leaf\n";
	}
	else std::cout << "Is not Leaf\n";
	//*******************************************
	nodeptr twenty = search(root, 20);
	std::cout << "20's parent is: " << twenty->parent->data << "\n";
	nodeptr eighteen = search(root, 18);
	std::cout << "18's parent is: " << eighteen->parent->data << "\n";

	std::cout << "The smallest value is: " << smallest(root)->data << "\n";
	std::cout << "The largest value is: " << largest(root)->data << "\n";
	std::cout << "5's nextLowest value is: " << nextLowest(root, 5) << "\n";
	std::cout << "18's nextLowest value is: " << nextLowest(root, 18) << "\n";
	std::cout << "45's nextLowest value is: " << nextLowest(root, 45) << "\n";
	std::cout << "The nextHighest value is: " << nextHighest(root, 5) << "\n";
	std::cout << "The nextHighest value is: " << nextHighest(root, 18) << "\n";
	std::cout << "The nextHighest value is: " << nextHighest(root, 45) << "\n";
	//********************************************
	//Delete Element Tests
	deleteNode(root, 12);
	deleteNode(root, 5);
	deleteNode(root, 20);
	display(root);
	std::cout << "\n";
	root = insert(root, root, 30);
	root = insert(root, root, 44);
	root = insert(root, root, 25);
	display(root);
	std::cout << "\n";
	deleteNode(root, 45);
	deleteNode(root, 15);
	display(root);
	std::cout << "\n";
	deleteAll(root);
	root = NULL;
	display(root);
	return 0;
}