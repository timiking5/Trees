#pragma once

struct Node {
	int value;
	Node* left;
	Node* right;
	Node* parent;
	Node(int val) {  // for initializing root node;
		value = val;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
	}
	Node(Node* parent_, int val) {  // for initializing child nodes; 
		parent = parent_;
		left = nullptr;
		right = nullptr;
		value = val;
	}
	Node(Node* parent_, Node* left_, Node* right_, int val) {  // just in case;
		parent = parent_;
		left = left_;
		right = right_;
		value = val;
	}
};

struct NodeRB {
	int value;
	NodeRB* left;
	NodeRB* right;
	NodeRB* parent;
	char color;
	NodeRB(int val) {
		value = val;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		color = 'B';
	}  // for initializing root node;
	NodeRB(NodeRB* parent_, int val, char col) {
		parent = parent_;
		left = nullptr;
		right = nullptr;
		value = val;
		color = col;
	}  // for initializing child nodes; 
	NodeRB(NodeRB* parent_, NodeRB* left_, NodeRB* right_, int val, char col) {
		parent = parent_;
		left = left_;
		right = right_;
		value = val;
		color = col;
	}  // just in case;
};

class BinaryTree {
private:
	Node* root;
public:
	BinaryTree(int val) {
		root = new Node(val);
	}

	void Insert(int val) {
		Node* x = this->root;
		Node* y = nullptr;
		while (x != nullptr) {
			y = x;
			if (x->value > val) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		Node* node = new Node(y, val);
		if (y == nullptr) root = node;
		else if (y->value > val) y->left = node;
		else y->right = node;
	}

	Node* TreeMinimum(Node* x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}

	Node* TreeMaximum(Node* x) {
		while (x->right != nullptr) {
			x = x->right;
		}
		return x;
	}

	Node* TreeSearch(Node* x, int k) {
		if (x == nullptr || x->value == k) return x;
		if (k < x->value) return TreeSearch(x->left, k);
		else return TreeSearch(x->right, k);
	}

	void Transplant(BinaryTree T, Node* u, Node* v) {
		if (u->parent == nullptr)
			T.root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != nullptr)
			v->parent = u->parent;
	}

	void TreeDelete(BinaryTree T, Node* z) {
		if (z->left == nullptr) {
			Transplant(T, z, z->right);
		}
		else if (z->right == nullptr) {
			Transplant(T, z, z->left);
		}
		else {
			Node* y = TreeMinimum(z->right);
			if (y->parent != z) {
				Transplant(T, y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(T, z, y);
			y->left = z->left;
			y->left->parent = y;
		}
	}

	void TreeWalkLVR(BinaryTree T) {
		LVR(T.root);
	}

	void LVR(Node* x) {
		if (x != nullptr) {
			LVR(x->left);
			std::cout << x->value << std::endl;
			LVR(x->right);
		}
	}
};

class BinaryTreeRB {
private:
	NodeRB* root;
	NodeRB* Nil;
public:
	BinaryTreeRB(int val) {
		root = new NodeRB(val); // цвет уже инициализирован
		Nil = new NodeRB(nullptr, root, root, NULL, 'B');
		root->parent = Nil;
		root->left = Nil;
		root->right = Nil;
	}
	NodeRB* TreeMinimum(NodeRB* x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}
	void LeftRotate(NodeRB* x) {
		NodeRB* y = x->right;
		x->right = y->left;
		if (y->left != Nil)
			y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == Nil)
			root = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
	}
	void RightRotate(NodeRB* y) {
		NodeRB* x = y->left;
		x->left = y->right;
		if (x->right != Nil)
			x->right->parent = y;
		x->parent = y->parent;
		if (y->parent == Nil)
			root = x;
		else if (y == y->parent->left)
			y->parent->left = x;
		else y->parent->right = x;
		x->right = y;
		y->parent = x;
	}
	void InsertFixup(NodeRB* z) {
		while (z->parent->color == 'R') {
			NodeRB* y;
			if (z->parent == z->parent->parent->left) {
				y = z->parent->parent->right;
				if (y->color == 'R') {
					z->parent->color = 'B';
					y->color = 'B';
					z->parent->parent->color = 'R';
					z = z->parent->parent;
				}
				else if (z == z->parent->right) {
					z = z->parent;
					LeftRotate(z);
					z->parent->color = 'B';
					z->parent->parent->color = 'R';
					RightRotate(z->parent->parent);
				}
			}
			else {
				y = z->parent->parent->left;
				if (y->color == 'R') {
					z->parent->color = 'B';
					y->color = 'B';
					z->parent->parent->color = 'R';
					z = z->parent->parent;
				}
				else if (z == z->parent->left) {
					z = z->parent;
					RightRotate(z);
					z->parent->color = 'B';
					z->parent->parent->color = 'R';
					LeftRotate(z->parent->parent);
				}
			}
		}
		root->color = 'B';
	}
	void Insert(int val) {
		NodeRB* y = Nil;
		NodeRB* x = root;
		while (x != Nil) {
			y = x;
			if (val < x->value) x = x->left;
			else x = x->right;
		}
		NodeRB* z = new NodeRB(y, val, 'R');
		if (y == Nil)
			root = z;
		else if (val < y->value)
			y->left = z;
		else y->right = z;
		z->left = Nil;
		z->right = Nil;
		InsertFixup(z);
	}
	void Transplant(NodeRB* u, NodeRB* v) {
		if (u->parent == Nil)
			root = v;
		else if (u = u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}
	void DeleteFixup(NodeRB* x) {
		while (x != root && x->color == 'B') {
			NodeRB* w;
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->color == 'R') {
					w->color = 'B';
					x->parent->color = 'R';
					LeftRotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == 'B' && w->right->color == 'B') {
					w->color = 'R';
					x = x->parent;
				}
				else if (w->right->color == 'B') {
					w->left->color = 'B';
					w->color = 'R';
					RightRotate(w);
					w = x->parent->right;
					w->color = x->parent->color;
					x->parent->color = 'B';
					w->right->color = 'B';
					LeftRotate(x->parent);
					x = root;
				}
			}
			else {
				w = x->parent->left;
				if (w->color == 'R') {
					w->color = 'B';
					x->parent->color = 'R';
					RightRotate(x->parent);
					w = x->parent->left;
				}
				if (w->left->color == 'B' && w->right->color == 'B') {
					w->color = 'R';
					x = x->parent;
				}
				else if (w->left->color == 'B') {
					w->right->color = 'B';
					w->color = 'R';
					LeftRotate(w);
					w = x->parent->left;
					w->color = x->parent->color;
					x->parent->color = 'B';
					w->left->color = 'B';
					RightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 'B';
	}
	void Delete(NodeRB* z) {
		NodeRB* x;
		NodeRB* y = z;
		char y_originial_color = y->color;
		if (z->left == Nil) {
			x = z->right;
			Transplant(z, z->right);
		}
		else if (z->right = Nil) {
			x = z->left;
			Transplant(z, z->left);
		}
		else {
			y = TreeMinimum(z->right);
			y_originial_color = y->color;
			x = y->right;
			if (y->parent = z) {
				x->parent = y;
			}
			else {
				Transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			Transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_originial_color == 'B')
			DeleteFixup(x);
	}
	void TreeWalkLVR(BinaryTreeRB T) {
		LVR(T.root);
	}

	void LVR(NodeRB* x) {
		if (x != Nil) {
			LVR(x->left);
			std::cout << x->value << " " << x->color << std::endl;
			LVR(x->right);
		}
	}
};