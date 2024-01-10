#include <stdio.h>
#include <stdlib.h>

#pragma region Реализация списка и работа с ним
//Структура узла
typedef struct Node {
    // Значение
    int value;
    //Указатель на след.элемент
    struct Node *next;
} Node;
//Функция добавления значения в список
void push(Node **head, int data) {
    //Создание узла
    Node *tmp = (Node*)malloc(sizeof(Node));
    //Присвоение значения
    tmp -> value = data;
    //Присвоение указателю tmp адрес пред.элемента
    tmp -> next = (*head);
    //Присвоение указателю head Адрес нового узла
    (*head) = tmp;
}
//Удаление и возвращение значения элемента на который указывает head
int pop(Node **head) {
    //Локальная переменная с адресом первого элемента
    Node* prev = NULL;
    //Значение первого элемента
    int val;
    //Проверка head на NULL
    if (head == NULL) exit(-1);
    //Указатель на первый элемент в списке
    prev = (*head);
    //Значение удаляемого элемента
    val = prev ->value;
    //перенос указателя head на след.элемент
    (*head) = (*head) -> next;
    //Удаление первого элемента списка
    free(prev);
    return val;
}

//Возврат указателя на n-ный элемент
Node* getNth(Node* head,int n) {
    //Счетчик
    int i = 0;
    //цикл перебора элементов до n-ного элемента
    while (i<n && head) {
        head = head->next;
        i++;
    }
    return head;
}
//Функция возвращение последнего элемента
Node* getLast(Node *head) {
    if (head == NULL) return NULL;
    while (head->next) {
        head = head -> next;
    }
    return head;
}
//Вставка элемента в конец списка
void pushEnd(Node *head, int value) {
    Node *last = getLast(head);
    Node *tmp = (Node*)malloc(sizeof(Node));
    tmp->value=value;
    tmp->next=NULL;
    last->next=tmp;
}
//Возвращение указатель предпоследнего элемента списка
Node* getLastButOne(Node* head) {
    if (head == NULL) exit(-2);
    if (head->next == NULL) {
        return NULL;
    }
    while (head->next->next) {
        head= head->next;
    }
    return head;
}
//Функция удаления последнего элемента списка
void popEnd(Node **head) {
    Node *lastBO = NULL;
    if (!head) exit(-1);
    if (!(*head)) exit(-1);
    lastBO = getLastButOne(*head);
    if (lastBO == NULL) {
        free(*head);
        *head = NULL;
    }else {
        free(lastBO->next);
        lastBO->next = NULL;
    }
}
//Функция вставки нового значения на n-ное место
void insert(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    while (i < n && head ->next) {
        head = head->next;
        i++;
    }
    tmp = (Node*) malloc(sizeof(Node));
    tmp ->value = val;
    if (head->next) {
        tmp-> next = head->next;
    }else {
        tmp ->next = NULL;
    }
    head ->next = tmp;
}
//Функция удаления n-ного элемента списка
int deleteNth(Node **head, unsigned n) {
    if (n==0) {
        return pop(head);
    }else {
        Node *prev = getNth(*head,n-1);
        Node *elm = prev->next;
        int val = elm -> next;
        free(elm);
        return val;
    }
}
//Удаление всего списка
void deleteList(Node **head) {
    Node* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}
//Проверка на пустоту
void isNull(Node **head) {
    //Проверка head на NULL
    if (head == NULL) {
        printf("Список Пуст");
    }else printf("Что-то есть...");
}
//Создание списка из массива
void fromArray(Node **head,int *arr) {
    int i=sizeof(arr)-1;
    if (arr == NULL) {
        return;
    }
    do {
        push(head,arr[i]);
    }while (i--!=0);
}
//Возвращение массива элементов,хранящихся в строке
int* toArray(const Node *head) {
    int len;
    while(head) {
        len++;
        head = head->next;
    }
    int *values = (int*) malloc(len*sizeof(int));
    while (head) {
        values[--len] = head->value;
        head = head->next;
    }
    return values;
}
//Вывод содержимого списка
void printLinkedList(const Node* head) {
    while (head) {
        printf("%d ",head-> value);
        head=head->next;
    }
    printf("\n");
}
//Вывод первого элемента списка
void printFromHead(const Node* head) {
    if (head) {
        printf("%d ", head->value);
    }
    printf("\n");
}
//Вывод последнего элемента списка
void printFromEnd(const Node* head) {
    if (head->next != NULL) {
        head = head->next;
        printFromEnd(head);
    }else {
        printf("%d ",head->value);
        printf("\n");
    }
}

#pragma endregion


int main() {
    //Опусташаем список
    Node *head = NULL;
    int arr[] = {1,2,3,4,5,6,7,8};

    fromArray(&head,arr);

    printFromHead(head);
    printLinkedList(head);
    printFromEnd(head);
}




