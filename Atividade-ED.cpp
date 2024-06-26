#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void displayList(Node*);

// Exercícios
void insertBefore(Node*, int);
Node* searchNodebyValue(Node*, int);
void deleteNodebyValue(Node**, int);

int main()
{
    Node* head = nullptr;
    displayList(head);
    cout << "==============" << endl;

    // Inserção no fim da lista
    insertEnd(&head, 20);
    insertEnd(&head, 30);
    displayList(head);
    cout << "==============" << endl;

    // Inserção no início da lista
    insertFront(&head, 10);
    insertFront(&head, 5);
    displayList(head);
    cout << "==============" << endl;

    // Inserção após um nó específico
    Node* nodeToInsertAfter = searchNodebyValue(head, 20);
    insertAfter(nodeToInsertAfter, 25);
    displayList(head);
    cout << "==============" << endl;
    
    // Inserção antes de um nó específico
    Node* nodeToInsertBefore = searchNodebyValue(head, 30);
    insertBefore(nodeToInsertBefore, 27);
    displayList(head);
    cout << "==============" << endl;
    
    // Exclusão de um nó por valor
    deleteNodebyValue(&head, 10);
    displayList(head);
    cout << "==============" << endl;
    
    return 0;
}


Node* createNode(int iPayload)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->iPayload = iPayload;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}


void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: Não é possível realizar displayList" << endl;
        return; // Usa return pra sair da função, o resto do código não será executado
    }
    
    if  (node -> ptrPrev != nullptr)
    {
        cout << "Meio ou Fim da Lista: Não é possível realizar displayList" << endl;
        return;
       
    }
    
    Node* temp = node;
     
    cout << "Payload: ";
    
    while(temp != nullptr)
    {
        cout << temp->iPayload<< " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}

void insertFront(Node** head, int iPayload)
{
    Node* newNode = createNode(iPayload);
    // newNode->ptrNext = nullptr;
    
    if (*head != nullptr)
    {
        (*head)->ptrPrev = newNode;
        newNode->ptrNext = (*head);
        (*head) = newNode;
        
        return;
    }
}

void insertEnd(Node** head, int iPayload)
{
  Node* newNode = createNode(iPayload);
  // newNode -> ptrNext = nullptr;
  
  if (*head == nullptr)
  {
      // newNode -> ptrNext = nullptr;
      (*head) = newNode;
      return;
      
  }
  
  Node* temp = (*head);
  
  // Percorremos a lista até seu fim(ptrNext do ultimo nó é NULL)
  while(temp->ptrNext != nullptr) temp = temp->ptrNext;
  
  newNode->ptrPrev = temp; // newNode aponta para o fim da lista
  temp->ptrNext = newNode; // Antigo último elemento aponta para o novo nó
}

void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl;
        return;
    }
    
    Node* newNode = createNode(iPayload);
    
    // Corrigir nó a ser inserido
    newNode->ptrNext = ptrLocation->ptrNext;
    newNode->ptrPrev = ptrLocation;
    
    // Corrigir o ponto de inserção
    ptrLocation->ptrNext = newNode;
    
    if (newNode->ptrNext != nullptr) newNode->ptrNext->ptrPrev = newNode;
}

void deleteNode(Node** head, Node* ptrDelete)
{
    if (*head == nullptr || ptrDelete == nullptr)
    {
        cout << "Não foi posível remover." << endl;
        return;
    }
    
    // Caso o ptrDelete seja o primero elemento da lista
    if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;
    
    // Se o ptrDelete não é o último nó
    if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;
    
    // Se o ptrDelete não é o primeiro nó
    if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

    free(ptrDelete);
}

// Exercício 1. Elaborar a função void insertBefore(Node*, int);
void insertBefore(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "Location é NULL." << endl;
        return;
    }

    Node* newNode = createNode(iPayload);

    newNode->ptrNext = ptrLocation;
    newNode->ptrPrev = ptrLocation->ptrPrev;

    ptrLocation->ptrPrev = newNode;
    
    if (newNode->ptrPrev != nullptr) newNode->ptrPrev->ptrNext = newNode;
}

// Exercício 3. Elaborar a função Node* searchNodebyValue(node*, int);
Node* searchNodebyValue(Node* head, int iValue)
{
    if (head == nullptr)
    {
        cout << "Lista vazia." << endl;
        return nullptr;
    }

    Node* temp = head;

    while (temp != nullptr)
    {
        if (temp->iPayload == iValue) return temp;
        temp = temp->ptrNext;
    }

    cout << "Valor não encontrado na lista." << endl;
    return nullptr;
}

// Exercício 2. Elaborar a função void deleteNodebyValue(Node**, int); 
// Se tiver duas ocorrências, apaga a primeira
void deleteNodebyValue(Node** head, int iValue)
{
    if (*head == nullptr)
    {
        cout << "Lista vazia." << endl;
        return;
    }

    Node* toRemove = searchNodebyValue(*head, iValue);
    if (toRemove != nullptr) deleteNode(head, toRemove);
}