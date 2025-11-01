#include<iostream>
#include<vector>
#include<stdio.h> 
using namespace std;

template<class T>
class dlist;
template<class T>

class dnode     // class of node
{
	T data;
	dnode<T> * next;
	dnode<T> * prev;
public:
	dnode() { next = prev = nullptr; }   // default constructor of dnode

	dnode(T d, dnode* n = nullptr)      // constructor with parimeters of dnode
	{
		data = d;
		next = n;
		prev = nullptr;
	}
	friend class dlist<T>;
};

// class of list
template <class T>
class dlist
{
	dnode<T> head;												// dummy head
																// class of iterator
	class dlistiterator
	{
		dnode<T> * curr;
	public:
		friend class dlist;
		dlistiterator(dnode<T>* n = nullptr)                      // constructor of list iterator
		{
			curr = n;
		}

		dlistiterator operator++()         // increment operator of list iterator
		{
			if (curr != nullptr)
				curr = curr->next;
			return *this;
		}
		bool operator==(dlistiterator iter)
		{
			return curr == iter.curr;
		}
		dlistiterator operator--()         // decrement operator of list iterator
		{
			if (curr != nullptr && curr->prev != nullptr)
				curr = curr->prev;
			return *this;
		}

		bool operator!=(const dlistiterator &it) const   // not equal operator of list iterator
		{
			return(curr != it.curr);
		}

		T& operator*()                     // * operator of list iterator (gives value )
		{
			return curr->data;
		}


		dnode<T> *getCurr()	   // gives pointer to which iterator is pointing
		{
			return curr;
		}

	};

public:
	typedef dlistiterator diterator;
	dlist()										 // constructor of list
	{
		head.next = nullptr;
	}

	~dlist()								// destructor of list
	{
		if (head.next != nullptr) {
			dnode<T> *t = head.next;
			while (t != nullptr) {
				t = head.next->next;
				delete head.next;
				head.next = t;
			}
		}
	}

	void insertatstart(T d)				 // inserts data at start of list
	{
		dnode<T> * temp = new dnode<T>(d);
		temp->next = head.next;
		temp->prev = nullptr;
		if (head.next != nullptr)
			head.next->prev = temp;
		head.next = temp;
	}

	dlistiterator begin()				// points iterator at start of list
	{
		dlistiterator it(head.next);
		return it;
	}

	dlistiterator end()					// points iterator at end of list (nullptr)
	{
		dlistiterator it;
		return it;
	}

	bool isEmpty()   // returns true if list is empty
	{
		return head.next == nullptr;
	}
	bool search(T d)   // search given data from list
	{
		dnode<T> *curr = head.next;
		while (curr != nullptr)
		{
			if (curr->data == d)
				return true;
			else
				curr = curr->next;
		}
		return false;
	}
	void printList()   // prints data of list
	{
		dnode<T> *curr = head.next;
		while (curr != nullptr)
		{
			cout << curr->data << " ";
			curr = curr->next;
		}
		cout << endl;
	}

	dnode<T>* getHead()     // return pointer of first element
	{
		return head.next;
	}

};

struct key_val              // key_val struct for storing char and its frequency
{
	char character;
	int freq;
};

struct key_code                // key_code struct for storing char and its code
{
	char character;
	vector<int> code;
};

int hash_function(key_val obj)             // hash function for key_val pair
{
	int temp = obj.character;  // ascii 
	return temp % 95;      // 95 for no collision;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
}

int hash_function_code(key_code obj)       // hash function for key_code pair
{
	int temp = obj.character;  // ascii 
	return temp % 95;    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
}

template <class T>
class hash_table_input                    // hash table class for storing frequency and char
{
public:
	vector <dlist<T>> h_table;

	hash_table_input()         // constructor for hash_table_input
	{
		h_table.resize(95);    // 95 for no collision  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	}
	void insert(key_val &obj)         // for inserting data in hash table
	{
		int flag = 0;
		int index = hash_function(obj);
		dlist<key_val>::diterator diter;
		diter = h_table[index].begin();
		for (; diter != h_table[index].end() && flag == 0; ++diter)
		{
			key_val temp = *diter;

			if (temp.character == obj.character)      // if data is already in hash table
			{
				flag = 1;
				temp.freq++;
				*diter = temp;
			}
		}
		if (flag == 0)                    // if data is not in hash table
		{
			h_table[index].insertatstart(obj);
		}
	}

	void print()               // print data in hash table
	{
		for (int i = 0; i < h_table.size(); i++)
		{
			dlist<key_val>::diterator diter;
			diter = h_table[i].begin();
			cout << " Index: " << i << endl << endl;
			for (; diter != h_table[i].end(); ++diter)
			{
				key_val temp = *diter;
				cout << " " << temp.character << "  " << temp.freq << endl;
			}
			cout << endl;
		}
	}
};

template <class T>
class hash_table_code              // class for hash table which stores codes and chars
{
public:
	vector <dlist<key_code>> h_table;

	hash_table_code()             // default constructor 
	{
		h_table.resize(95);  // 95 for no collision  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	}

	void insert(key_code &obj)         // for inserting code and char in hash table
	{
		int index = hash_function_code(obj);

		h_table[index].insertatstart(obj);
	}

	void print()                    // for printing hash table containing code and char
	{
		for (int i = 0; i < h_table.size(); i++)
		{
			cout << " Index: " << i << endl << endl;
			dlist<key_code>::diterator diter;
			diter = h_table[i].begin();
			for (; diter != h_table[i].end(); ++diter)      // print data in list 
			{
				key_code temp = *diter;
				if (temp.code.size() != 0)
				{
					cout << "Character = " << temp.character << endl;
					cout << "Code =  ";
					for (int i = 0; i < temp.code.size(); i++)
						cout << temp.code[i];
					cout << endl <<endl;
				}
			}
		}
	}

	key_code serach(char obj)       // search given char in hash table and return its code
	{
		int temp = obj;
		int index = temp % 95;       // 95 for no collision;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
		dlist<key_code>::diterator diter;

		diter = h_table[index].begin();
		for (; diter != h_table[index].end(); ++diter)   // saerch at index in the list 
		{
			key_code code = *diter;

			if (code.character == obj)     // id it matchs return
			{
				return code;
			}
		}
		key_code empty;
		empty.character = '\0';
		return empty;
	}

	char serach_char(vector<int> v)       // function to search a charcter in table from the array 
	{
		key_code temp;
		dlist<key_code>::diterator diter;
		for (int i = 0; i < h_table.size(); i++)
		{
			diter = h_table[i].begin();
			for (; diter != h_table[i].end(); ++diter)
			{
				temp = *diter;
				if (v == temp.code)
				{
					return temp.character;
				}
			}
		}
		return '\0';
	}
};

template<class T>
class heap;
template<class T>
class binary_tree;

template <class T>
class tnode             // class of tnode
{
public:
	tnode *left;
	tnode *right;
	int height;
	T data;

	friend class heap<T>;
	friend class binary_tree<T>;
	tnode(T d, tnode * l = nullptr, tnode * r = nullptr, int h = 0)    // default constructor of tnode
	{
		left = l;
		right = r;
		height = h;
		data = d;
	}
	void printTnodeData()        // prints data of tnode
	{
		cout << data.character << " " << data.freq << endl;
	}



};

template <class T>
class binary_tree              // class of binary tree
{
public:
	tnode<T> * root;

	friend class heap<T>;
	binary_tree()        // default constructor 
	{
		root = nullptr;
	}

	void insert(T d)                  // wrapper function for insert function
	{
		return insert(root, d);
	}

	void insert(tnode<T> *& r, T d)            // for inserting data in  Binary tree
	{
		//if (r == nullptr)
		{
			r = new tnode<T>(d);
			return;
		}
	}

	void print_binary_tree()       // print binary tree data
	{
		if (root != nullptr)
		{
			key_val obj = root->data;
			cout << obj.character << " " << obj.freq << endl;
		}
	}

	~binary_tree()         //wrapper destructor of binary_tree 
	{
		destroy(root);
	}

	void destroy(tnode<T> * r)   // actual destructor of binary_tree
	{
		if (r != nullptr)
		{
			//destroy(r->left);
			//destroy(r->right);
			//delete r;

		}
	}

};

template <class T>
class heap                         //      class of Minheap
{
	binary_tree<key_val> * h;
	int heap_size;
	int max_size;

public:
	heap(int s = 100)            //  constructor of heap
	{
		max_size = s;
		heap_size = 0;
		h = new binary_tree<key_val>[max_size];
	}

	void insert(binary_tree<key_val> d)           // function to insert data in head
	{
		heap_size++;
		h[heap_size] = d;
		int i = heap_size;
		while (i > 1 && h[i].root->data.freq < h[i / 2].root->data.freq)    // check for minheap condition
		{
			if (h[i].root->data.freq < h[i / 2].root->data.freq)
			{
				swap(h[i], h[i / 2]);
				i = i / 2;
			}
			else
				break;
		}
	}

	tnode<key_val> * extract_min()          // function to extract minimum data from heap
	{
		tnode<key_val> *data = h[1].root;
		h[1] = h[heap_size];
		heap_size--;
		min_heapify(1);
		return data;
	}

	void min_heapify(int i)            // function to min heapify the heap
	{
		int left = 2 * i;
		int right = (2 * i) + 1;
		int minimum = i;
		if (left <= heap_size && h[left].root->data.freq < h[i].root->data.freq)
		{
			minimum = left;
		}
		if (right <= heap_size && h[right].root->data.freq < h[i].root->data.freq)
		{
			minimum = right;
		}
		if (i != minimum)
		{
			swap(h[i], h[minimum]);
			min_heapify(minimum);
		}
	}

	tnode<key_val>* huff_man()        // for application of huffman algorithm
	{
		while (heap_size > 1)        // making a tree
		{
			tnode<key_val>* x = extract_min();
			tnode<key_val>* y = extract_min();
			int frq_sum = (x->data.freq) + (y->data.freq);
			binary_tree<key_val> z;
			key_val temp;
			temp.character = '\0';
			temp.freq = frq_sum;
			z.insert(temp);
			z.root->right = y;
			z.root->left =x;
			insert(z);
		}
		return h[1].root;      // return root of tree
	}
	void printheap()			//function to print heap
	{
		for (int i = 1; i < heap_size; i++)	
			cout << h[i].root->data.character << "  " << h[i].root->data.freq << endl;
		cout << endl;
	}

	void print_after_huffman(tnode<key_val> * t)	//function to print heap (tree) after huffman
	{
		tnode<key_val> * curr = t;
		if (curr != nullptr)
		{
			cout << t->data.character << "  " << t->data.freq << endl;
			print_after_huffman(t->left);
			print_after_huffman(t->right);
		}
	}

	void encode(hash_table_code<key_val> &t, vector<int> &v,tnode<key_val> *&h)   // to make codes from tree 
	{
		if (h->right == nullptr && h->left == nullptr)
		{
			char c = h->data.character;
			vector<int> code;
			for (int i = 0; i < v.size(); i++)     // copy generated code in vector
			{
				code.push_back(v[i]);
			}
			key_code encoded;
			encoded.character = c;
			encoded.code = code;
			t.insert(encoded);           // insert in hash table
			return;
		}
		v.push_back(0);
		encode(t,v,h->left);           //  recursive call for left
		v.pop_back();
		v.push_back(1);
		encode(t,v,h->right);         //  recursive call for right
		v.pop_back();
	}

};

