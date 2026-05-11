#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename T>

class Queue {

private:

    Node<T>* frontNode;
    Node<T>* rearNode;

    int size;

public:

    
    // CONSTRUCTOR
  

    Queue() {

        frontNode = nullptr;
        rearNode = nullptr;

        size = 0;
    }

    
    // ENQUEUE
    // INSERTAR AL FINAL


    void enqueue(T data) {

        Node<T>* newNode = new Node<T>(data);

        // Si la cola está vacía
        if (rearNode == nullptr) {

            frontNode = newNode;
            rearNode = newNode;
        }

        else {

            rearNode->next = newNode;

            rearNode = newNode;
        }

        size++;
    }

   
    // DEQUEUE
    // ELIMINAR PRIMERO
  

    void dequeue() {

        if (frontNode == nullptr) {

            return;
        }

        Node<T>* temp = frontNode;

        frontNode = frontNode->next;

        // Si quedó vacía
        if (frontNode == nullptr) {

            rearNode = nullptr;
        }

        delete temp;

        size--;
    }

    // FRONT
    // OBTENER PRIMERO
   

    T front() {

        if (frontNode == nullptr) {

            throw runtime_error("Queue vacia");
        }

        return frontNode->data;
    }

 
    // VERIFICAR VACÍA
 
    bool isEmpty() {

        return frontNode == nullptr;
    }

   
    // TAMAÑO
  

    int getSize() {

        return size;
    }


    // IMPRIMIR


    void print() {

        Node<T>* temp = frontNode;

        while (temp != nullptr) {

            cout << temp->data << " -> ";

            temp = temp->next;
        }

        cout << "NULL" << endl;
    }


    // DESTRUCTOR


    ~Queue() {

        while (frontNode != nullptr) {

            Node<T>* temp = frontNode;

            frontNode = frontNode->next;

            delete temp;
        }
    }
};

#endif