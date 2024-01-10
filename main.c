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
//Функция вставки нового значения на  место предыдущее n-ному значению
void insertBefore(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    while (i < n-1 && head ->next) {
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
//Функция вставки нового значения на  место следующее за n-ным значением
void insertAfter(Node *head, unsigned n, int val) {
    unsigned i = 0;
    Node *tmp = NULL;
    while (i < n-1 && head ->next) {
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
        printf("List null\n");
    }else printf("List not null\n");
}
//Создание списка из массива
void fromArray(Node **head,int *arr, int N) {
    int i= N;
    if (arr == NULL) {
        return;
    }
    do {
        push(head,arr[i]);
    }while (i--!=0);
}
//Возвращение массива элементов,хранящихся в строке
int toArray(const Node *head) {
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
    while (head->next != NULL) {
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
//Поиск заданного элемента
void search(const Node* head, int val) {
    if(head->value == val) {
        printf("This value is present in the list");
        printf("%d\n");
        return;
    }
    if(head->next == NULL) {
        printf("This value is no in the list");
        printf("%d\n");
    }else {head= head->next; search(head,val);
    }}
//Функция слияния списков
void merge(Node *a, Node *b, Node **c) {
    Node tmp;
    *c = NULL;
    if (a == NULL) {
        *c = b;
        return;
    }
    if (b == NULL) {
        *c = a;
        return;
    }
    if (a->value < b->value) {
        *c = a;
        a = a->next;
    } else {
        *c = b;
        b = b->next;
    }
    tmp.next = *c;
    while (a && b) {
        if (a->value < b->value) {
            (*c)->next = a;
            a = a->next;
        } else {
            (*c)->next = b;
            b = b->next;
        }
        (*c) = (*c)->next;
    }
    if (a) {
        while (a) {
            (*c)->next = a;
            (*c) = (*c)->next;
            a = a->next;
        }
    }
    if (b) {
        while (b) {
            (*c)->next = b;
            (*c) = (*c)->next;
            b = b->next;
        }
    }
    *c = tmp.next;
}
//Функция разделения списка пополам
void split(Node *src, Node **low, Node **high) {
    Node *fast = NULL;
    Node *slow = NULL;

    if (src == NULL || src->next == NULL) {
        (*low) = src;
        (*high) = NULL;
        return;
    }

    slow = src;
    fast = src->next;

    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            fast = fast->next;
            slow = slow->next;
        }
    }

    (*low) = src;
    (*high) = slow->next;
    slow->next = NULL;
}

//Функция сортировки методом разделения и слияния списка
void mergeSort(Node **head) {
    Node *low  = NULL;
    Node *high = NULL;
    if ((*head == NULL) || ((*head)->next == NULL)) {
        return;
    }
    split(*head, &low, &high);
    mergeSort(&low);
    mergeSort(&high);
    merge(low, high, head);
}
#pragma endregion


int main() {
    //Опусташаем список
    Node *head = NULL;
    //Вызываем меню
    int val = 0;
    printf(
        "\n"
           "_______________________________________________________"
           "\n** "
           "Select one of the options for the program to work **"
           "\n"
           "_______________________________________________________"
           "\n"
           "\t\t  1   Work with list"
           "\n"
           "\t\t  2   Work with stack"
           "\n"
           "\t\t  3   Work with queue"
           "\n"
           "_______________________________________________________"
           "\n"
           );
    scanf("%d",&val);
    switch (val) {
        case 1: {
            printf(
                "\n "
                   "_______________________________________________________"
                   "\n"
                   "\t\t  1  Check if the list is empty"
                   "\n"
                   "\t\t  2  Creating a list"
                   "\n"
                   "\t\t  3  Searching for a list item"
                   "\n"
                   "\t\t  4  Adding a list item"
                   "\n"
                   "\t\t  5  Removal"
                   "\n"
                   "\t\t  6 Take a list item"
                   "\n"
                   "\t\t  7 Viewing list items"
                   "\n"
           "_______________________________________________________"
                   "\n"
                );
            scanf("%d", &val);
            switch (val) {
                case 1: isNull(head); break;;
                case 2: {
                    printf(
               "\n""_______________________________________________________"
               "\n\t\t  1  Create with sort"
               "\n\t\t  2  Create not sort"
               "\n""_______________________________________________________\n");
                    scanf("%d",&val);
                    switch (val) {
                        case 1: {
                            unsigned i;
                            unsigned N;
                            printf("\t\t  How many elements?\n");
                            scanf("%d",&N);
                            int array[N];
                            printf("\t\t  input elements\n");
                            for(i = 0; i < N; i++ )// заполняем массив
                            {
                                printf("[%u]=",i+1);
                                scanf("%d", array+i);
                            }

                            fromArray(&head,array,N);
                            mergeSort(&head);
                            printLinkedList(head);
                        }
                        case 2: {
                            unsigned i;
                            unsigned N;
                            printf("\t\t  How many elements?\n");
                            scanf("%d",&N);
                            int array[N];
                            printf("\t\t  input elements\n");
                            for(i = 0; i < N; i++ )// заполняем массив
                            {
                                printf("[%u]=",i+1);
                                scanf("%d", array+i);
                            }

                            fromArray(&head,array,N);
                            printLinkedList(head);
                            break;
                        }
                    }
                    break;
                };
                case 3: {
                    int s;
                    printf("\t\t  input elements\n");
                    scanf("%d", s);
                    search(head,s);
                    break;
                }
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
            }
            break;
        }
        case 2: printf("stack");break;
        case 3: printf("queue");break;
    }
}





