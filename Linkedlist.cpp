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
        head = nullptr;
    }

    /**
     * @brief Inserts a new node at the beginning of the list.
     * @param data The value for the new node.
     */
    void insertAtHead(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    /**
     * @brief Inserts a new node at the end of the list.
     * @param data The value for the new node.
     */
    void insertAtTail(int data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    /**
     * @brief Inserts a new node at a specified position (1-based index).
     * @param data The value for the new node.
     * @param pos The position to insert at.
     */
    void insertAtPosition(int data, int pos) {
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }
        if (pos == 1) {
            insertAtHead(data);
            return;
        }

        Node* newNode = new Node(data);
        Node* temp = head;
        for (int i = 1; i < pos - 1 && temp != nullptr; ++i) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds!" << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    /**
     * @brief Deletes a node from a specified position (1-based index).
     * @param pos The position of the node to delete.
     */
    void deleteFromPosition(int pos) {
        if (head == nullptr) {
            cout << "List is empty. Nothing to delete." << endl;
            return;
        }
        if (pos < 1) {
            cout << "Invalid position!" << endl;
            return;
        }

        Node* temp = head;
        if (pos == 1) {
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = nullptr;
        for (int i = 1; i < pos && temp != nullptr; ++i) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position out of bounds!" << endl;
            return;
        }
        
        prev->next = temp->next;
        delete temp;
    }

    /**
     * @brief Reverses the linked list in-place.
     */
    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next;
            current->next = prev;
            prev = current;
            current = nextNode;
        }
        head = prev;
    }
    
    /**
     * @brief Searches for a value in the list.
     * @param key The value to search for.
     * @return The 1-based position of the key, or -1 if not found.
     */
    int search(int key) {
        Node* current = head;
        int pos = 1;
        while (current != nullptr) {
            if (current->data == key) {
                return pos;
            }
            current = current->next;
            pos++;
        }
        return -1;
    }

    /**
     * @brief Merges another list to the end of the current list.
     * @param other The list to merge. Its nodes are moved, leaving it empty.
     */
    void merge(LinkedList& other) {
        if (other.head == nullptr) {
            return;
        }
        if (head == nullptr) {
            head = other.head;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = other.head;
        }
        other.head = nullptr;
    }
    
    /**
     * @brief Displays the contents of the linked list.
     */
    void display() {
        Node* temp = head;
        if (temp == nullptr) {
            cout << "List is empty." << endl;
            return;
        }
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
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