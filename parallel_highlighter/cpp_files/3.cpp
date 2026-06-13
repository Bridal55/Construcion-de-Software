#include<iostream>
using namespace std;

class Node {
public:
	int value;
	Node* next;

	Node() {
		value = 0;
		next = nullptr;
	}
	Node(int v) {
		value = v;
		next = nullptr;
	}

};

class Linkedlist {
private:
	Node* head;
public:
	Linkedlist() {
		head = nullptr;
	}
	
	void push_front(int value) {
		Node* new_node = new Node(value);
		if (head == NULL) {
			head = new_node;
			return;
		}
		else {
			new_node->next = head;
			head = new_node;
			return;
		}
	}

	void push_back(int value) {
		Node* new_node = new Node(value);
		Node* temporary = head;
		if (head == NULL)
			push_front(value);
		else {
			while (temporary->next != NULL) 
				temporary = temporary->next;
			temporary->next = new_node;
		}
	}

	void read() { //print
		Node* temporary = head; 
		cout << "Head --> ";
		while (temporary != NULL) {
			cout << temporary->value << " --> ";
			temporary = temporary->next;
		}
		cout << "NULL\n" << endl;
	}

	int list_size() {
		Node* temporary = head;
		int count = 0;
		while (temporary != NULL) {
			temporary = temporary->next;
			count++;
		}
		return count;
	}

	void insert(int value, int index) {
		int size = list_size();
		if (size < index)
			cout << "The Index is to big for the size of the list\n" << endl;
		else if (index == size+1) {
			push_back(value);
		}
		else if (index == 0 || index == 1)
			push_front(value);
		else {
			Node* new_node = new Node(value);
			Node* temporary = head;
			for (int i = 0; i < index-2; i++) 
				temporary = temporary->next;
			new_node->next = temporary->next;
			temporary->next = new_node;
		}
	}

	void update(int value, int index) {
		int size = list_size();
		if (size < index)
			cout << "The Index is to big for the size of the list\n" << endl;
		else if (head == NULL) {
			cout << "The list is empty\n" << endl;
		}
		else {
			Node* new_node = new Node(value);
			Node* temporary = head;
			for (int i = 0; i < index - 1; i++)
				temporary = temporary->next;
				//new_node->next = temporary->next; 
			temporary->value = new_node->value;
		}
	}

	void pop_front() {
		if (head == NULL)
			cout << "The list is empty\n" << endl;
		else
		head = head->next;
	}

	void pop_back() {
		Node* temporary = head;
		if (head == NULL)
			cout << "The list is empty\n" << endl;
		else {
			while (temporary->next->next != NULL)
				temporary = temporary->next;
			temporary->next = NULL;
		}
	}

	void delete_element(int index) {
		int size = list_size();
		if (size < index)
			cout << "The Index is to big for the size of the list\n" << endl;
		else if (head == NULL)
			cout << "The list is empty\n" << endl;
		else if (size == index)
			pop_back();
		else if (index == 1)
			pop_front();
		else if (index == 0)
			cout << "There is no element 0 in this list\n" << endl;
		else {
			Node* temporary = head;
			for (int i = 0; i < index - 2; i++)
				temporary = temporary->next;
			temporary->next = temporary->next->next;
		}
	}

	void index_search(int index) {
		int size = list_size();
		if (size < index)
			cout << "The Index is to big for the size of the list\n" << endl;
		else if (head == NULL)
			cout << "The list is empty\n" << endl;
		else if (index == 0) 
			cout << "There is no element 0 in this list\n" << endl;
		else {
			Node* temporary = head;
			for (int i = 0; i < index - 1; i++)
				temporary = temporary->next;
			cout << "The Value found in the Index you inputed is: " << temporary->value << "\n" << endl;
		}
	}

	void value_search (int value) {
		if (head == NULL)
			cout << "The list is empty\n" << endl;
		else {
			Node* temporary = head;
			int i = 0;
			while (temporary != NULL) {
				i++;
				if (temporary->value == value){
					cout << "The value you are looking for is in the index number: " << i << "\n" << endl;
				return;
			}
			temporary = temporary->next;
			}
			cout << "The number you are looking for does not exist in this list\n" << endl;
		}
	}
};

int main() {
	Linkedlist d;
	d.push_back(10);
	d.push_back(20);
	d.push_back(30);
	d.push_back(40);
	d.push_back(50);
	d.push_back(60);
	d.push_back(70);
	d.push_back(80);
	d.push_back(90);
	d.push_back(100);

	while (true) {
		int choice;
		int value;
		int index;
		cout << "Select which of the following you want to do: " << endl;
		cout << "1. Create a Node at the begining of the list\n2. Create a Node at the end\n3. Create a node in a position determined by the index you provide\n4. Read the entire list\n5. Update the node found in the index you provide\n6. Delete the first node\n7. Delete the last node\n8. Delete the node found in the index you will provide\n9. Search for the index of a specific value\n10. Search for the value found in a specific index\n11. Exit Program\n" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "\nWhat value would you like to asign to the node: " << endl;
			cin >> value;
			d.push_front(value);
			break;
		case 2:
			cout << "\nWhat value would you like to asign to the node: " << endl;
			cin >> value;
			d.push_back(value);
			break;
		case 3:
			cout << "\nWhat value would you like to asign to the node: " << endl;
			cin >> value;
			cout << "In which position (index) would you like to place it: " << endl;
			cin >> index;
			d.insert(value, index);
			break;
		case 4:
			cout << "\n" << endl;
			d.read();
			break;
		case 5:
			cout << "\nWhat value would you like to asign to the node: " << endl;
			cin >> value;
			cout << "In which position (index) would you like to make the change: " << endl;
			cin >> index;
			d.update(value, index);
			break;
		case 6:
			d.pop_front();
			cout << "\nFirst Node was Successfully eliminated" << endl;
			break;
		case 7:
			d.pop_back();
			cout << "\nLast Node was Successfully eliminated" << endl;
			break;
		case 8:
			cout << "\nWhich position (index) would you like to delete: " << endl;
			cin >> index;
			d.delete_element(index);
			break;
		case 9:
			cout << "\nWhat value would you like to search for: " << endl;
			cin >> value;
			d.value_search(value);
			break;
		case 10:
			cout << "\nWhat index would you like to look into: " << endl;
			cin >> index;
			d.index_search(index);
			break;
		case 11:
			cout << "\nProgram ended" << endl;
			exit(0);
		}
	}
	return 0;
}
