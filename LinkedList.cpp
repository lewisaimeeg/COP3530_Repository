#include <iostream>
#include <string>
using namespace std;

class LinkedList {
public:

	// Nested Node Class
	class Node {
	public:
		Node();

		//Node variables
		string data;
		int index;
		Node * next;
		Node * prev;

	};

	//Linked List variables
	Node * headNode;
	Node * tailNode;
	int nodeCount;

	LinkedList();

	// -------------- Accessors --------------------
	void print() const;
	void printAt(int index) const;

	void search(const string &data);

	// -------------- Insertion ---------------

	void insertEnd(const string &data);
	void insert(unsigned int index, const string &data);

	// -------------- Removal ----------------

	bool remove(int index);

	// -------------- Edit ------------

	void edit(unsigned int index, const string &data);
	void updateIndex();


	// Trilogy of Evil
	LinkedList(const LinkedList &d);
	LinkedList &operator=(const LinkedList &d);
	~LinkedList();
};

//							----------------------------- Definitions ------------------------------

//Default Constructor for a linked list
LinkedList::LinkedList() {
	headNode = nullptr;
	tailNode = nullptr;
	nodeCount = 0;
}

//Default constructor for a node
LinkedList::Node::Node() {
	data = "";
	index = 0;
	next = nullptr;
	prev = nullptr;
}

//							------------------------------ Accessors --------------------------------

//Iterate through all of the nodes and print their values
void LinkedList::print() const {
	Node * currentNode = headNode;

	while (currentNode != nullptr) {
		cout << currentNode->index << " " << currentNode->data << endl;
		currentNode = currentNode->next;
	}
}

//Iterate through the list until it reaches the index, then print one line
void LinkedList::printAt(int index) const {
	Node * currNode = headNode;
	for (int i = 1; i < index; i++) {
		currNode = currNode->next;
	}
	cout << currNode->index << " " << currNode->data << endl;

}

//Find the first node with a data value matching the passed in parameter, returning a pointer to that node. Returns null if no
//matching node found
void LinkedList::search(const string &data) {
	bool found = false;
	Node * curNode = headNode;
	//search for the phrase by iterating through the linked list and comparing phrases
	while (curNode != nullptr) {
		if (curNode->data.find(data) != std::string::npos) {
			found = true;
			printAt(curNode->index);
		}
		curNode = curNode->next;
	}
	if (!found) {
		cout << "not found" << endl;
	}
}

//							--------------------- Insertion --------------------

//Create a new node to store the passed in data
void LinkedList::insertEnd(const string &data) {
	//create a new Node
	Node * nodeptr = new Node();
	nodeptr->data = data;

	//update new node's pointers
	nodeptr->prev = tailNode;
	nodeptr->next = nullptr;

	if (nodeCount == 0) {
		tailNode = nodeptr;
		headNode = nodeptr;
	}
	else {
		tailNode->next = nodeptr;
		//make Tail point to this new node
		tailNode = nodeptr;
	}
	nodeCount++;
	updateIndex();
}

//Inserts a node into the list at the specified index
void LinkedList::insert(unsigned int index, const string &data) {
	if (index <= nodeCount) {
		//create a new Node
		Node * nodeptr = new Node();
		nodeptr->data = data;

		//insert at 1
		if (index == 1) {
			nodeptr->next = headNode;
			headNode->prev = nodeptr;
			headNode = nodeptr;

		}
		//insert in middle
		else {
			//iterate a tmpNext pointer to the node at the specified index (index)
			Node * tmpNext = headNode;
			Node * tmpPrev = headNode;

			for (int i = 1; i < index; i++) {
				tmpNext = tmpNext->next;
			}
			//iterate a tmpPrev pointer to the node before the specified index (index - 1)
			for (int i = 1; i < index - 1; i++) {
				tmpPrev = tmpPrev->next;
			}

			//update prev and next node's pointers
			tmpNext->prev = nodeptr;
			tmpPrev->next = nodeptr;

			//update the new node's pointers
			nodeptr->prev = tmpPrev;
			nodeptr->next = tmpNext;
		}
		nodeCount++;
		updateIndex();
	}
	else if (index == nodeCount + 1) {
		insertEnd(data);
	}
}

//					---------------------- Removal ------------------------

//Deletes the index-th Node from the list, returning whether or not the operation was successful
bool LinkedList::remove(int index) {
	// compare the index to the index values of each node. When found, delete that node

	if (index != 1 && index != nodeCount) {
		bool found = false;
		Node * tmp = headNode;

		while (!found && tmp != nullptr) {
			if (tmp->index == index) {
				found = true;
			}
			if (!found) {
				tmp = tmp->next;
			}
		}
		if (found) {
			//make the node's prev point to its next and make its next point to its prev
			Node * prevPtr = tmp->prev;
			Node * nextPtr = tmp->next;

			prevPtr->next = nextPtr;
			nextPtr->prev = prevPtr;

			//delete the node
			delete tmp;
			nodeCount--;
		}
	}
	//delete the first node
	else if (index == 1) {
		Node * tmp = headNode;
		headNode = headNode->next;
		headNode->prev = nullptr;
		delete tmp;
		nodeCount--;

	}
	//delete the last node
	else {
		Node * tmp = tailNode;
		tailNode = tailNode->prev;
		tailNode->next = nullptr;
		delete tmp;
		nodeCount--;
	}
	updateIndex();
	return true;
}

//                  --------------------- Edit ---------------------

void LinkedList::edit(unsigned int index, const string &data) {
	// TO DO: iterate through using the index value and then
	// change that node's data value to the passed in data value
	bool found = false;
	Node * tmp = headNode;

	while (!found && tmp != nullptr) {
		if (tmp->index == index) {
			found = true;
		}
		if (!found) {
			tmp = tmp->next;
		}
	}
	if (found) {
		tmp->data = data;
	}
}

//iterate through the list and update each node's index
void LinkedList::updateIndex() {
	Node * tmp = headNode;
	int tmpIndex = 1;
	while (tmp != nullptr) {
		tmp->index = tmpIndex;
		tmp = tmp->next;
		tmpIndex++;
	}
}




//				------------------------ Trilogy of Evil ------------------------------

//copy constructor
LinkedList::LinkedList(const LinkedList &d) {
	nodeCount = d.nodeCount;
	headNode = d.headNode;
	tailNode = d.tailNode;
}

//Assignment operator
LinkedList & LinkedList::operator=(const LinkedList &d) {
	nodeCount = d.nodeCount;
	headNode = d.headNode;
	tailNode = d.tailNode;

	return *this;
}


// LinkedList destructor

LinkedList::~LinkedList() {
	Node * tmpNode = headNode->next;

	while (tmpNode != nullptr) {
		Node * next = tmpNode->next;
		delete tmpNode;
		tmpNode = next;
	}
	headNode = nullptr;
	tailNode = nullptr;

}

int main()
{
	string command;
	string index;
	string phrase;
	string line;
	bool quit = false;

	LinkedList * list = new LinkedList();

	//while loop to read input
	while (!quit) {

		getline(cin, line);
		command = line.substr(0, line.find(" "));

		if (command == "quit") {
			quit = true;
		}
		else if (command == "print") {
			list->print();
		}
		// get the phrase, call insertEnd
		else if (command == "insertEnd") {
			//trim the phrase
			phrase = line.substr(line.find("\"") + 1, 80);
			phrase = phrase.substr(0, phrase.length() - 1);

			list->insertEnd(phrase);
		}
		// get the phrase, call search
		else if (command == "search") {
			//trim the phrase
			phrase = line.substr(line.find("\"") + 1, 80);
			phrase = phrase.substr(0, phrase.length() - 1);

			list->search(phrase);
		}
		// get the index, call delete
		else if (command == "delete") {
			index = line.substr(line.find(" ") + 1, 80);
			index = index.substr(0, phrase.length() - 1);
			int indexInt = stoi(index, nullptr);

			list->remove(indexInt);
		}
		// get the index, get the edited phrase, call edit
		else if (command == "edit") {

			line = line.substr(line.find(" ") + 1, 80);
			index = line.substr(0, line.find(" "));
			phrase = line.substr(line.find("\"") + 1, 80);
			phrase = phrase.substr(0, phrase.length() - 1);
			int indexInt = stoi(index, nullptr);
			list->edit(indexInt, phrase);
		}
		// get the index, get the phrase, call insert
		else if (command == "insert") {
			line = line.substr(line.find(" ") + 1, 80);
			index = line.substr(0, line.find(" "));
			phrase = line.substr(line.find("\"") + 1, 80);
			phrase = phrase.substr(0, phrase.length() - 1);
			int indexInt = stoi(index, nullptr);

			list->insert(indexInt, phrase);
		}
		else {
			quit = true;
		}

	}
}