#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

    void displayRecursive(Node* current) {
        if (current == nullptr) {
            cout << "NULL" << endl;
            return;
        }
        cout << current->data << " -> ";
        displayRecursive(current->next);
    }

    Node* insertAtTailRecursive(Node* current, int data) {
        if (current == nullptr) {
            return new Node(data);
        }
        current->next = insertAtTailRecursive(current->next, data);
        return current;
    }
    
    Node* insertAtPositionRecursive(Node* current, int data, int pos) {
        if (pos == 1) {
            Node* newNode = new Node(data);
            newNode->next = current;
            return newNode;
        }
        if (current == nullptr) {
            cout << "Position out of bounds!" << endl;
            return nullptr;
        }
        current->next = insertAtPositionRecursive(current->next, data, pos - 1);
        return current;
    }

    Node* deleteFromPositionRecursive(Node* current, int pos) {
        if (current == nullptr) {
            cout << "Position out of bounds!" << endl;
            return nullptr;
        }
        if (pos == 1) {
            Node* temp = current->next;
            delete current;
            return temp;
        }
        current->next = deleteFromPositionRecursive(current->next, pos - 1);
        return current;
    }
    
    Node* reverseRecursive(Node* current) {
        if (current == nullptr || current->next == nullptr) {
            return current;
        }
        Node* newHead = reverseRecursive(current->next);
        current->next->next = current;
        current->next = nullptr;
        return newHead;
    }

    int searchRecursive(Node* current, int key, int pos) {
        if (current == nullptr) {
            return -1;
        }
        if (current->data == key) {
            return pos;
        }
        return searchRecursive(current->next, key, pos + 1);
    }
    
    void mergeRecursive(Node* current, Node* otherHead) {
        if (current->next == nullptr) {
            current->next = otherHead;
            return;
        }
        mergeRecursive(current->next, otherHead);
    }

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    
    void display() {
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        displayRecursive(head);
    }

    void insertAtHead(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    void insertAtTail(int data) {
        head = insertAtTailRecursive(head, data);
    }

    void insertAtPosition(int data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        head = insertAtPositionRecursive(head, data, pos);
    }
    
    void deleteFromPosition(int pos) {
         if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        if (head == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        head = deleteFromPositionRecursive(head, pos);
    }

    void reverse() {
        head = reverseRecursive(head);
    }
    
    int search(int key) {
        return searchRecursive(head, key, 1);
    }
    
    void merge(LinkedList& other) {
        if (other.head == nullptr) return;
        if (head == nullptr) {
            head = other.head;
        } else {
            mergeRecursive(head, other.head);
        }
        other.head = nullptr;
    }
};

int main() {
    cout << "## Creating and Populating List 1 ##" << endl;
    LinkedList list1;
    list1.insertAtHead(10);
    list1.insertAtTail(30);
    list1.insertAtHead(5);
    list1.insertAtPosition(20, 3);
    cout << "Initial List 1: ";
    list1.display();
    cout << "------------------------------------" << endl;

    cout << "\n## Searching in List 1 ##" << endl;
    int keyToFind = 20;
    int pos = list1.search(keyToFind);
    if (pos != -1) {
        cout << "Found " << keyToFind << " at position: " << pos << endl;
    } else {
        cout << keyToFind << " not found in the list." << endl;
    }
    cout << "------------------------------------" << endl;

    cout << "\n## Deleting from List 1 ##" << endl;
    list1.deleteFromPosition(3);
    cout << "List 1 after deleting element at position 3: ";
    list1.display();
    cout << "------------------------------------" << endl;

    cout << "\n## Reversing List 1 ##" << endl;
    list1.reverse();
    cout << "Reversed List 1: ";
    list1.display();
    cout << "------------------------------------" << endl;
    
    cout << "\n## Merging two lists ##" << endl;
    LinkedList list2;
    list2.insertAtTail(100);
    list2.insertAtTail(200);
    cout << "List 1 before merge: ";
    list1.display();
    cout << "List 2 before merge: ";
    list2.display();

    list1.merge(list2);
    
    cout << "List 1 after merging List 2: ";
    list1.display();
    cout << "List 2 after being merged: ";
    list2.display();
    cout << "------------------------------------" << endl;

    return 0;
}