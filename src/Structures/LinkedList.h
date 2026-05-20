#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Node.h"

using namespace std;

template <typename T>

class LinkedList {

private:

    Node<T>* head;
    int size;

public:


    // CONSTRUCTOR


    LinkedList() {

        head = nullptr;
        size = 0;
    }


    // CONSTRUCTOR DE COPIA
    LinkedList(const LinkedList& other) {
        head = nullptr;
        size = other.size;
        Node<T>* curr = other.head;
        Node<T>* tail = nullptr;
        while (curr != nullptr) {
            Node<T>* newNode = new Node<T>(curr->data);
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            curr = curr->next;
        }
    }


    // OPERADOR DE ASIGNACIÓN
    LinkedList& operator=(const LinkedList& other) {
        if (this == &other) return *this;

        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }

        head = nullptr;
        size = other.size;
        Node<T>* curr = other.head;
        Node<T>* tail = nullptr;
        while (curr != nullptr) {
            Node<T>* newNode = new Node<T>(curr->data);
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
            curr = curr->next;
        }
        return *this;
    }


    // INSERTAR AL FINAL


    void insert(T data) {

        Node<T>* newNode = new Node<T>(data);

        // Si la lista está vacía
        if (head == nullptr) {

            head = newNode;
        }

        else {

            Node<T>* temp = head;

            while (temp->next != nullptr) {

                temp = temp->next;
            }

            temp->next = newNode;
        }

        size++;
    }


    // INSERTAR AL INICIO

    void insertFirst(T data) {

        Node<T>* newNode = new Node<T>(data);

        newNode->next = head;

        head = newNode;

        size++;
    }


    // ELIMINAR


    void remove(T data) {

        if (head == nullptr) {

            return;
        }

        // Si el head es el que se elimina
        if (head->data == data) {

            Node<T>* temp = head;

            head = head->next;

            delete temp;

            size--;

            return;
        }

        Node<T>* current = head;

        while (current->next != nullptr &&
            current->next->data != data) {

            current = current->next;
        }

        // Si encontró el dato
        if (current->next != nullptr) {

            Node<T>* temp = current->next;

            current->next = temp->next;

            delete temp;

            size--;
        }
    }


    // BUSCAR


    bool contains(T data) {

        Node<T>* temp = head;

        while (temp != nullptr) {

            if (temp->data == data) {

                return true;
            }

            temp = temp->next;
        }

        return false;
    }


    // OBTENER TAMAÑO


    int getSize() {

        return size;
    }


    // VERIFICAR SI ESTÁ VACÍA


    bool isEmpty() {

        return head == nullptr;
    }


    // OBTENER HEAD


    Node<T>* getHead() {

        return head;
    }


    // IMPRIMIR LISTA


    void print() {

        Node<T>* temp = head;

        while (temp != nullptr) {

            cout << temp->data << " -> ";

            temp = temp->next;
        }

        cout << "NULL" << endl;
    }


    // DESTRUCTOR


    ~LinkedList() {

        Node<T>* current = head;

        while (current != nullptr) {

            Node<T>* next = current->next;

            delete current;

            current = next;
        }
    }
};

#endif