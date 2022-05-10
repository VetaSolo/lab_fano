#pragma once
#include <iostream>
#include <iomanip>


using namespace std;

template <typename first_typename>

class stack
{
private:
	// class Node for stack element storage
	class Node
	{
	public:
		first_typename value;
		Node* prev;
		Node(const int element) :value(element), prev(0) {}
	};
	Node* current;
	size_t size_stack;
public:
	// Consrtructor of stack
	stack() :current(0), size_stack(0) {}

	// Desrtructor of stack
	~stack()
	{
		while (current)
			pop();
	}

	// add element to the stack
	void push(const first_typename element)
	{
		Node* temp = current;
		current = new Node(element);
		current->prev = temp;
		size_stack++;
	}

	// remove top element from the stack
	void pop()
	{
		if (size_stack) {
			Node* temp = current->prev;
			delete current;
			current = temp;
			size_stack--;
		}
		else {
			throw out_of_range("stack is empty");
		}
	}

	// get the element on the top of the stack
	first_typename top()
	{
		return current->value;
	}

	// check the stack's empty
	bool empty()
	{
		return !size_stack;
	}

	// get the size of the stack
	size_t size()
	{
		return size_stack;
	}
};

template <typename first_typename>

class Linked_list {

	// class Node for Linked_list element storage
	class Node {
	public:
		first_typename data;
		Node* next;
	};

	// delete the head
	void delete_head() {
		if (head != NULL)
		{
			list_size--;
			Node* to_delete = head;
			to_delete = head;
			head = head->next;
			delete to_delete;
		}
		else
			throw out_of_range("List is empty");
	}

public:

	Node* head; // pointer to the Linked_list head
	int list_size;

	// Constructor
	Linked_list() {
		head = NULL;
		list_size = 0;
	}

	// Destructor
	~Linked_list() {
		list_size = 0;
	}

	// insert the element to the end of list
	void insert_node(first_typename data) {
		// Create the new Node.
		Node* new_node = new Node;
		new_node->data = data;
		new_node->next = NULL;
		list_size++;

		// if it is first element
		if (head == NULL) {
			head = new_node;
			return;
		}

		// else go to the end of list
		Node* current_last = head;
		while (current_last->next != NULL) {
			current_last = current_last->next;
		}
		// insert at the last
		current_last->next = new_node;
	}

	// get the head value
	first_typename get_head() {
		if (list_size != 0)
			return head->data;
		else
			throw out_of_range("List is empty");
	}

	// go to the next element of the list
	void set_next() {
		if (head != NULL)
			head = head->next;
		else
			throw out_of_range("There is not next element");
	}

	// get the list size
	int size() {
		return list_size;
	}

};

template <typename first_typename, typename second_typename>

class MyMap {
private:

	// class Node for RBTree element storage
	class Node {
	public:
		first_typename key; // holds the key
		second_typename value; // holds the value
		Node* parent; // pointer to the parent
		Node* left; // pointer to left child
		Node* right; // pointer to right child
		int color; // 0 is Black, 1 is Red

		Node() {
			color = 0;
			left = nullptr;
			right = nullptr;
		}

		Node(first_typename outside_key, second_typename outside_value) {
			parent = nullptr;
			key = outside_key;
			value = outside_value;
			color = 1; // inserting node must be red
		}
	};

	Node* root;  // pointer to the root of RBTree
	Node* Nil; // pointer to the NULL

	// move moving_node to the host_node place
	void moving(Node* host_node, Node* moving_node) {
		if (host_node->parent == nullptr) {
			root = moving_node;
		}
		else if (host_node == host_node->parent->left) {
			host_node->parent->left = moving_node;
		}
		else {
			host_node->parent->right = moving_node;
		}
		moving_node->parent = host_node->parent;
	}

	// left-rotation at node current_node
	void left_rotate(Node* current_node) {
		Node* right_child = current_node->right;
		current_node->right = right_child->left;
		if (right_child->left != Nil) {
			right_child->left->parent = current_node;
		}
		right_child->parent = current_node->parent;
		if (current_node->parent == nullptr) {
			root = right_child;
		}
		else if (current_node == current_node->parent->left) {
			current_node->parent->left = right_child;
		}
		else {
			current_node->parent->right = right_child;
		}
		right_child->left = current_node;
		current_node->parent = right_child;
	}

	// right-rotation at node current_node
	void right_rotate(Node* current_node) {
		Node* left_child = current_node->left;
		current_node->left = left_child->right;
		if (left_child->right != Nil) {
			left_child->right->parent = current_node;
		}
		left_child->parent = current_node->parent;
		if (current_node->parent == nullptr) {
			root = left_child;
		}
		else if (current_node == current_node->parent->right) {
			current_node->parent->right = left_child;
		}
		else {
			current_node->parent->left = left_child;
		}
		left_child->right = current_node;
		current_node->parent = left_child;
	}

	// fix the RBTree modified by the insert operation
	void fix_after_insert(Node* x) {
		Node* uncle;
		while (x->parent->color == 1) {
			if (x->parent == x->parent->parent->right) {
				uncle = x->parent->parent->left;
				if (uncle->color == 1) {
					// parent becomes black, uncle becomes black, grandparent becomes red
					uncle->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left) {
						// do the right-rotation at parent of current_node
						x = x->parent;
						right_rotate(x);
					}
					x->parent->color = 0; // parent becomes black
					x->parent->parent->color = 1; // grandparent becomes red
					left_rotate(x->parent->parent); // do the left-rotation at grandparent, grandparent becomes brother of current_node
				}
			}
			else {
				uncle = x->parent->parent->right;

				if (uncle->color == 1) {
					// parent becomes black, uncle becomes black, grandparent becomes red
					uncle->color = 0;
					x->parent->color = 0;
					x->parent->parent->color = 1;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->right) {
						// do the left-rotation at parent of current_node
						x = x->parent;
						left_rotate(x);
					}

					x->parent->color = 0; // parent becomes black
					x->parent->parent->color = 1; // grandparent becomes red
					right_rotate(x->parent->parent); // do the right-rotation at grandparent, grandparent becomes brother of current_node
				}
			}
			if (x == root) {
				break;
			}
		}
		root->color = 0; // root must be black
	}

	// fix the RBTree modified by the remove operation
	void fix_after_remove(Node* x) {
		Node* brother;
		while (x != root && x->color == 0) {
			// if brother is right brother of x
			if (x == x->parent->left) {
				brother = x->parent->right; // brother is right brother of x
				if (brother->color == 1) {
					// if x's brother color is red
					brother->color = 0;
					x->parent->color = 1;
					left_rotate(x->parent);
					brother = x->parent->right;
				}

				if (brother->left->color == 0 && brother->right->color == 0) {
					// if x's brother color is red, and both of x’s brother's children are black
					brother->color = 1;
					x = x->parent;
				}
				else {
					if (brother->right->color == 0) {
						// if x's brother color is red, x’s brother's right child is black, x’s brother's left child is red
						brother->left->color = 0;
						brother->color = 1;
						right_rotate(brother);
						brother = x->parent->right;
					}

					// if x's brother color is black, x’s brother's right child is red
					brother->color = x->parent->color;
					x->parent->color = 0;
					brother->right->color = 0;
					left_rotate(x->parent);
					x = root;
				}
			}
			// if brother is left brother of x = mirror of brother is right brother of x
			else {
				brother = x->parent->left; // brother is left brother of x
				if (brother->color == 1) {
					// if x's brother color is red
					brother->color = 0;
					x->parent->color = 1;
					right_rotate(x->parent);
					brother = x->parent->left;
				}

				if (brother->right->color == 0 && brother->left->color == 0) {
					// if x's brother color is red, and both of x’s brother's children are black
					brother->color = 1;
					x = x->parent;
				}
				else {
					if (brother->left->color == 0) {
						// if x's brother color is red, x’s brother's right child is red, x’s brother's left child is black
						brother->right->color = 0;
						brother->color = 1;
						left_rotate(brother);
						brother = x->parent->left;
					}

					// if x's brother color is black, x’s brother's left child is red
					brother->color = x->parent->color;
					x->parent->color = 0;
					brother->left->color = 0;
					right_rotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0; // root must be black
	}

	//algorithm part of find operation
	Node* find_algorithm(Node* current_node, first_typename key) {
		if (key == current_node->key) {
			return current_node;
		}

		// check that tree contains the node with looking for key
		if (current_node == Nil) {
			throw out_of_range("Couldn't find key in the RBTree");
		}

		if (key < current_node->key) {
			return find_algorithm(current_node->left, key);
		}
		return find_algorithm(current_node->right, key);
	}

	//algorithm part of contains operation
	bool contains_algorithm(Node* current_node, first_typename key) {
		if (key == current_node->key) {
			return true;
		}

		if (current_node == Nil) {
			return false;
		}

		if (key < current_node->key) {
			return contains_algorithm(current_node->left, key);
		}
		return contains_algorithm(current_node->right, key);
	}

	// record RBTree keys in stack to clear the RBTree
	void RBTree_to_stack(Node* node, stack<first_typename>& MyStack) {
		if (node != Nil) {
			MyStack.push(node->key);
			RBTree_to_stack(node->left, MyStack);
			RBTree_to_stack(node->right, MyStack);
		}
	}

	//algorithm part of get keys operation
	void get_keys_algorithm(Node* node, Linked_list<first_typename>& MyLinked_list) {
		if (node != Nil) {
			MyLinked_list.insert_node(node->key);
			get_keys_algorithm(node->left, MyLinked_list);
			get_keys_algorithm(node->right, MyLinked_list);
		}
	}

	//algorithm part of get values operation
	void get_values_algorithm(Node* node, Linked_list<second_typename>& MyLinked_list) {
		if (node != Nil) {
			MyLinked_list.insert_node(node->value);
			get_values_algorithm(node->left, MyLinked_list);
			get_values_algorithm(node->right, MyLinked_list);
		}
	}

	// helper method to print the RBTree
	void print_with_indent(Node* node, int level = 0)
	{
		if (node != Nil)
		{
			print_with_indent(node->left, level + 1);
			for (int i = 0; i < level; i++) cout << "   ";
			cout << setw(3) << node->key;
			if (node->color == 0) { cout << " (Black)" << '\n'; }
			else { cout << " (Red)" << '\n'; }
			print_with_indent(node->right, level + 1);
		}
	}

public:
	// CustomMap class Constructor 
	MyMap() {
		Nil = new Node;
		/*Nil->color = 0;
		Nil->left = nullptr;
		Nil->right = nullptr;*/
		root = Nil;
	}

	// CustomMap class Destructor 
	~MyMap() {
		clear();
	}

	// insert the node with user's key and value to the RBTree in its appropriate position and fix the RBTree after insertion
	void insert(first_typename key, second_typename value) {

		Node* inserting_node = new Node(key, value);
		inserting_node->left = Nil;
		inserting_node->right = Nil;

		Node* y = nullptr;
		Node* x = root;

		while (x != Nil) {
			y = x;
			if (inserting_node->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		// if y is parent of x
		inserting_node->parent = y;
		if (y == nullptr) {
			root = inserting_node;
		}
		else if (inserting_node->key < y->key) {
			y->left = inserting_node;
		}
		else {
			y->right = inserting_node;
		}

		// if inserting_node is a root node
		if (inserting_node->parent == nullptr) {
			inserting_node->color = 0;
			return;
		}

		// if the grandparent is null
		if (inserting_node->parent->parent == nullptr) {
			return;
		}

		// fix the tree
		fix_after_insert(inserting_node);
	}

	// remove the node with user's key from the RBTree and fix the RBTree after deletion
	void remove(first_typename key) {
		Node* node_to_be_deleted = Nil;
		Node* x;
		Node* y;

		// finding the node with looking for key
		node_to_be_deleted = find(key);

		y = node_to_be_deleted;
		int y_original_color = y->color; // save the node_to_be_deleted color
		if (node_to_be_deleted->left == Nil) {
			x = node_to_be_deleted->right;
			moving(node_to_be_deleted, node_to_be_deleted->right); // move x to the node_to_be_deleted place
		}
		else if (node_to_be_deleted->right == Nil) {
			x = node_to_be_deleted->left;
			moving(node_to_be_deleted, node_to_be_deleted->left); // move x to the node_to_be_deleted place
		}
		else {
			// y becomes the minimum key in node_to_be_deleted right subtree
			y = node_to_be_deleted->right;
			while (y->left != Nil) {
				y = y->left;
			}
			// save the y color
			y_original_color = y->color;
			x = y->right;
			if (y->parent == node_to_be_deleted) {
				x->parent = y;
			}
			else {
				moving(y, y->right); // move y right child to the y place
				y->right = node_to_be_deleted->right;
				y->right->parent = y;
			}

			moving(node_to_be_deleted, y); // move y to the node_to_be_deleted place
			y->left = node_to_be_deleted->left;
			y->left->parent = y;
			y->color = node_to_be_deleted->color;
		}
		delete node_to_be_deleted;

		// if y_original_color is black
		if (y_original_color == 0) {
			fix_after_remove(x);
		}
	}

	// search the node with user's key
	Node* find(first_typename key) {
		return find_algorithm(root, key);
	}

	// clear the RBTree by remove nodes step be step
	void clear() {
		stack<first_typename> MyStack;
		RBTree_to_stack(root, MyStack);
		while (MyStack.size()) {
			remove(MyStack.top());
			MyStack.pop();
		}
	}

	// return the list of RBTree keys
	Linked_list<first_typename> get_keys() {
		Linked_list<first_typename> MyLinked_list;
		get_keys_algorithm(root, MyLinked_list);
		return MyLinked_list;
	}

	// return the list of RBTree values
	Linked_list<second_typename> get_values() {
		Linked_list<second_typename> MyLinked_list;
		get_values_algorithm(root, MyLinked_list);
		return MyLinked_list;
	}

	// print the RBTree on the screen
	void print() {
		return print_with_indent(root);
	}

	bool contains(first_typename key) {
		return contains_algorithm(root, key);
	}
};

// class ShannonFano_Coder for encode and decode text
class Fano_Coder {
private:
	char* char_array; // dynamic array for different text characters storage
	int* frequency; // dynamic array for text characters frequency storage
	string* code; // dynamic array for text characters codes storage
	string original_text;
	int alphabet_size; // number of different text characters

	// BubbleSort algorithm for arrays sorting in descending order
	void BubbleSort() {
		for (int i = 0; i < alphabet_size; i++) {
			for (int j = 0; j < alphabet_size - 1; j++) {
				if (frequency[j] < frequency[j + 1]) {
					int int_temporary = frequency[j];
					char char_temporary = char_array[j];
					frequency[j] = frequency[j + 1];
					char_array[j] = char_array[j + 1];
					frequency[j + 1] = int_temporary;
					char_array[j + 1] = char_temporary;
				}
			}
		}
	}

	// return the index of character
	int get_index(char letter) {
		for (int i = 0; i < alphabet_size; i++) {
			if (char_array[i] == letter) return i;
		}
	}

	// return the index of character
	int get_index(string substring) {
		for (int i = 0; i < alphabet_size; i++) {
			if (code[i] == substring) return i;
		}
	}

	// return the minimum of two value
	int min(int first, int second) {
		return !(second < first) ? first : second;
	}

	// check that substring is a code of some character
	bool contains(string substring) {
		for (int i = 0; i < alphabet_size; i++) {
			if (code[i] == substring) return true;
		}
		return false;
	}

public:
	// ShannonFano_Coder class Constructor
	Fano_Coder(MyMap<char, int>& MyCustomMap, const int different_letter, string text_to_encode) {
		char_array = new char[different_letter];
		frequency = new int[different_letter];
		code = new string[different_letter];
		alphabet_size = different_letter;
		original_text = text_to_encode;

		Linked_list<char> map_keys = MyCustomMap.get_keys();
		Linked_list<int> map_values = MyCustomMap.get_values();

		for (int i = 0; i < alphabet_size; i++)
		{
			char_array[i] = map_keys.get_head();
			frequency[i] = map_values.get_head();
			code[i] = "";
			map_keys.set_next();
			map_values.set_next();
		}

		BubbleSort();

	}

	// ShannonFano_Coder class Destructor
	~Fano_Coder() {
		delete[] char_array;
		delete[] frequency;
		delete[] code;
	}

	// print text characters frequency table on the screen
	void print_frequency_table() {
		for (int i = 0; i < alphabet_size; i++)
		{
			cout << char_array[i] << " : " << frequency[i] << '\n';
		}
	}

	// ShannonFano encode algorithm
	void ShannonFano_encoding(int begin, int end) {
		if (begin == end)
			return;
		int left = begin;
		int right = end;
		int sum_left = 0;
		int sum_right = 0;
		// find index to split array in half by frequency
		while (left <= right) {
			if (sum_left <= sum_right) {
				sum_left += frequency[left];
				left++;
			}
			else {
				sum_right += frequency[right];
				right--;
			}
		}
		// insert '0' to the end of left-subarray characters
		for (int i = begin; i < left; i++) {
			code[i] += "0";
		}
		// insert '1' to the end of right-subarray characters
		for (int i = left; i <= end; i++) {
			code[i] += "1";
		}
		// run the recursive algorithm to left and right subarrays
		ShannonFano_encoding(begin, left - 1);
		ShannonFano_encoding(left, end);
	}

	// print text characters code table on the screen
	void print_code_table() {
		for (int i = 0; i < alphabet_size; i++)
		{
			cout << char_array[i] << " : " << code[i] << '\n';
		}
	}

	// calculate original text size
	int original_text_size() {
		int sum_size = 0;
		for (int i = 0; i < alphabet_size; i++)
		{
			sum_size += 8 * frequency[i];
		}
		return sum_size;
	}

	// calculate encoded text size
	int encoded_text_size() {
		int sum_size = 0;
		for (int i = 0; i < alphabet_size; i++)
		{
			sum_size += code[i].size() * frequency[i];
		}
		return sum_size;
	}

	// calculate ShannonFano encode algorithm compression ratio
	float compression_ratio() {
		int original_size = original_text_size();
		float divided = original_size / 1.0f;
		int encoded_size = encoded_text_size();
		float divisor = encoded_size / 1.0f;
		float quotient = divided / divisor;
		return quotient;
	}

	// return string of encoded text
	string encoded_text() {
		string encoded_text = "";
		for (int i = 0; i < original_text.size(); i++) {
			encoded_text += code[get_index(original_text.at(i))];
		}
		return encoded_text;
	}

	// return string of decoded text
	string decoded_text() {
		string decoded_text = "";
		string text_to_decode = encoded_text();
		int max_code_lenght = 0;
		for (int i = 0; i < alphabet_size; i++) {
			if (code[i].size() > max_code_lenght) max_code_lenght = code[i].size();
		}
		while (text_to_decode.size() > 0) {
			for (int i = 0; i <= min(max_code_lenght, text_to_decode.size()); i++) {
				string substring = text_to_decode.substr(0, i);
				if (contains(substring)) {
					decoded_text += char_array[get_index(substring)];
					text_to_decode.erase(0, i);
					break;
				}
			}
		}
		return decoded_text;
	}

	// print encoded text on the screen
	void print_encoded_text() {
		cout << encoded_text();
	}

	// print decoded text on the screen
	void print_decoded_text() {
		cout << decoded_text();
	}

};
