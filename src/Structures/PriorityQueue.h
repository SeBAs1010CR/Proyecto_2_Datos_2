#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "Node.h"

using namespace std;

template <typename T>

class PriorityQueue {

private:


    // NODO INTERNO


    class PQNode {

    public:

        T data;
        int priority;

        PQNode* next;

        PQNode(T data, int priority) {

            this->data = data;
            this->priority = priority;

            next = nullptr;
        }
    };

    PQNode* head;
    int size;

public:


    // CONSTRUCTOR


    PriorityQueue() {

        head = nullptr;
        size = 0;
    }

  
    // INSERTAR
    // Menor prioridad = sale primero
   

    void enqueue(T data, int priority) {

        PQNode* newNode =
            new PQNode(data, priority);

        // Lista vacía
        if (head == nullptr) {

            head = newNode;
        }

        // Insertar al inicio
        else if (priority < head->priority) {

            newNode->next = head;

            head = newNode;
        }

        // Insertar ordenado
        else {

            PQNode* temp = head;

            while (temp->next != nullptr &&
                   temp->next->priority <= priority) {

                temp = temp->next;
            }

            newNode->next = temp->next;

            temp->next = newNode;
        }

        size++;
    }

   
    // ELIMINAR PRIMERO


    void dequeue() {

        if (head == nullptr) {

            return;
        }

        PQNode* temp = head;

        head = head->next;

        delete temp;

        size--;
    }

    
    // OBTENER PRIMERO


    T front() {

        if (head == nullptr) {

            throw runtime_error(
                "Priority Queue vacia"
            );
        }

        return head->data;
    }

  
    // OBTENER PRIORIDAD
   

    int frontPriority() {

        if (head == nullptr) {

            throw runtime_error(
                "Priority Queue vacia"
            );
        }

        return head->priority;
    }

  
    // VERIFICAR VACÍA


    bool isEmpty() {

        return head == nullptr;
    }

   
    // TAMAÑO
  

    int getSize() {

        return size;
    }


    // IMPRIMIR
   

    void print() {

        PQNode* temp = head;

        while (temp != nullptr) {

            cout << "["
                 << temp->data
                 << " | P:"
                 << temp->priority
                 << "] -> ";

            temp = temp->next;
        }

        cout << "NULL" << endl;
    }

  
    // DESTRUCTOR


    ~PriorityQueue() {

        while (head != nullptr) {

            PQNode* temp = head;

            head = head->next;

            delete temp;
        }
    }
};

#endif