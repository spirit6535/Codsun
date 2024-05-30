#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->prev = nullptr;
    newNode->next = nullptr;
    return newNode;
}

void insertNode(Node*& head, int value) {
    if (head == nullptr) {
        head = createNode(value);
        return;
    }

    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    Node* new_node = createNode(value);
    new_node->prev = temp;
    temp->next = new_node;
}

int countDivisors(int n) {
    int divisorsCount = 0;

    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            divisorsCount++;
    }

    return divisorsCount;
}

void removeMaxDivisorNodes(Node*& head) {
    // 1. Найти максимальное количество делителей
    int maxDivisors = -1;
    Node* current = head;
    while (current != nullptr) {
        int div = countDivisors(current->data);
        if (div > maxDivisors) {
            maxDivisors = div;
        }
        current = current->next;
    }

    // 2. Удалить узлы с максимальным количеством делителей
    current = head;
    while (current != nullptr) {
        int div = countDivisors(current->data);
        if (div == maxDivisors) {
            if (current == head) { // Удаление головы списка
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
                delete current;
                current = head; 
            } else { // Удаление не-головового узла
                current->prev->next = current->next;
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                Node* temp = current->next; // Сохраняем ссылку на следующий узел
                delete current; 
                current = temp;  // Переходим к следующему узлу
            }
        } else {
            current = current->next;
        }
    }
}

int main() {
    Node* listHead = nullptr;

    insertNode(listHead, 10);
    insertNode(listHead, 15);
    insertNode(listHead, 7);
    insertNode(listHead, 12); 
    insertNode(listHead, 16);

    cout << "Список до удаления:" << endl;
    Node* current = listHead;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    removeMaxDivisorNodes(listHead);

    cout << "Список после удаления:" << endl;
    current = listHead;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;

    return 0;
}