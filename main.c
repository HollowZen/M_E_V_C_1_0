#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void isNull(Node* head) {
    //Проверка head на NULL
    if (head->value == 0) {
        printf("List null\n");
    }else {printf("List not null\n");}
}
//Создание списка из массива
void fromArray(Node **head,int *arr,size_t size) {
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        push(head, arr[i]);
    } while(i--!=0);
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
//Функция вычисления размера массива чисел
int lenIntMass(char* S) {
    int i,l,k,len = 0;
    char q;
    l=strlen(S);
    for (i=0; i<l; i++){
        q=S[i];
        if (q==','){
            if (k>0) {
                len++;
            }}
        else{k++;}
    }
    return len;
}
//Функция из строки в массив чисел
void strToArr(char* S, int* arr, int len)
{
    int c,i,j,l,k;
    char q;

    l=strlen(S);
    c=0;
    k=0;
    j=0;

    for (i=0; i<l; i++){
        q=S[i];
        if (q==','){
            if (k>0) {
                arr[j]=c;
                c=0; k=0;
                j++;
            }}
        else{k++;c=c*10+(q-'0');}
    }
}
//Вывод содержимого списка
void printLinkedList(const Node* head) {
    while (head != NULL) {
        printf("%d ",head->value);
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

    if(head->value == 0) {
        printf("This value is no in the list");
        printf("%d\n");
        return;
    }
    if(head->value == val) {
        printf("This value is present in the list");
        printf("%d\n");
        return;
    }else {head= head->next; search(head,val);
    }
}

struct Node* swap(struct Node* ptr1, struct Node* ptr2)
{
    struct Node* tmp = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = tmp;
    return ptr2;
}
void bubbleSort(struct Node** head, int count)
{
    if (head == NULL){return;}
    struct Node** h;
    int i, j, swapped;

    for (i = 0; i <= count; i++) {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++) {

            struct Node* p1 = *h;
            struct Node* p2 = p1->next;

            if (p1->value > p2->value) {
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->next;
        }

        if (swapped == 0)
            break;
    }
}



#pragma endregion
#pragma region Меню


void menuList(Node *head,int val){
    }



#pragma endregion

int main() {
    //Опусташаем список
    Node *head = NULL;

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
                case 1: isNull(&head); break;;
                case 2: {
                    printf(
               "\n_______________________________________________________"
               "\n\t\t  1  Create with sort"
               "\n\t\t  2  Create not sort"
               "\n_______________________________________________________\n");
                    scanf("%d",&val);
                    switch (val) {
                        case 1: {
                            char str[1024];

                            printf("\t\t  input elements through (,)\n");
                            getchar();
                            fgets(&str,1024,stdin);
                            head = NULL;
                            int len = lenIntMass(&str);
                            int array[len];
                            strToArr(&str,&array,len);
                            fromArray(&head,array,len);
                            bubbleSort(&head,len);
                            printLinkedList(&head);
                            break;;
                        }
                        case 2: {
                            char str[1024];

                            printf("\t\t  input elements through (,)\n");
                            getchar();
                            fgets(&str,1024,stdin);
                            head = NULL;
                            int len = lenIntMass(&str);
                            int array[len];
                            strToArr(&str,&array,len);
                            fromArray(&head,array,len);
                            printLinkedList(head);
                            break;;
                        }
                    }
                    break;
                };
                case 3: {
                    char s[10];
                    int a = 0;
                    printf("\t\t  input elements\n");
                    getchar();
                    fgets(s,10,stdin);
                    a = strtol(s,NULL,10);
                    search(&head,a);
                }
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
            }}
        case 2: printf("stack");break;
        case 3: printf("queue");break;
    }
}





