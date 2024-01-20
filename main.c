#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
//Удалить и вывести последний элемент
int popEnd(Node **head) {
    int val = 0;
    Node *pFwd = NULL;  //текущий узел
    Node *pBwd = NULL;  //предыдущий узел
    //Получили NULL
    if (!head) {
        exit(-1);
    }
    //Список пуст
    if (!(*head)) {
        exit(-1);
    }

    pFwd = *head;
    while (pFwd->next) {
        pBwd = pFwd;
        pFwd = pFwd->next;
    }

    if (pBwd == NULL) {
        free(*head);
        *head = NULL;
    } else {
        val = pFwd->value;
        free(pFwd->next);
        pBwd->next = NULL;
    }
    return val;
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
void deleteEnd(Node **head) {
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
//Функция удаление первого элемента
void deleteStart(Node **head) {
    //Локальная переменная с адресом первого элемента
    Node* prev = NULL;
    //Проверка head на NULL
    if (head == NULL) exit(-1);
    //Указатель на первый элемент в списке
    prev = (*head);
    //перенос указателя head на след.элемент
    (*head) = (*head) -> next;
    //Удаление первого элемента списка
    free(prev);
}
//Функция удаления n-ного элемента списка
void deleteNth(Node **head, unsigned n) {
    if (n == 0) {
         pop(head);
    } else {
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        prev->next = elm->next;
        free(elm);
    }
}
//Возврат и  удаления n-ного элемента списка
int popNth(Node **head, unsigned n) {
    int val = 0;
    if (n == 0) {
        val = (*head)->value;
        pop(head);
        return val;
    } else {
        Node *prev = getNth(*head, n-1);
        Node *elm  = prev->next;
        prev->next = elm->next;
        val = elm->value;
        free(elm);
        return val;
    }
}
//Удаление всего списка
void deleteList(Node **head) {
    while ((*head)->next) {
        pop(head);
        *head = (*head)->next;
    }

    pop(head);
}
//Проверка на пустоту
void isNull(Node* head) {
    //Проверка head на NULL
    if (head == 0) {
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
void printLinkedList(Node *head) {
    while (head != 0) {
        printf("%d ",head->value);
        head=head->next;
    }
    printf("\n");
}
//Вывод первого элемента списка
void printFromHead(Node *head) {
    if (head) {
        printf("%d ", head->value);
    }
    printf("\n");
}
//Вывод последнего элемента списка
void printFromEnd(Node *head) {
    if (head->next != NULL) {
        head = head->next;
        printFromEnd(head);
    }else {
        printf("%d ",head->value);
        printf("\n");
    }
}
//Поиск заданного элемента
void search(Node* head, int val) {

    if(head == 0 || (head->value == 0 && head->next == 0)) {
        printf("This value is no in the list");
        printf("\n");
        return;
    }
    if(head->value == val) {
        printf("This value is present in the list");
        printf("\n");
        return;
    }else {head= head->next; search(head,val);
    }
}
//Пузырьковая сортировка
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

//Реверс элементов между первым и последним вхождение элемента E
Node* reverseBetweenFirstAndLast(Node* head, int e) {
    if (!head)return;;
    Node* curr = head;
    Node* first = NULL;
    Node* last = NULL;
    Node* reverst = NULL;
    Node* answ = NULL;

    int i = 0;

    while (curr) {
        if (curr->value == e) {
            i++;
        }
        curr = curr->next;
    }
    curr = head;
    if (i<2){printf("Count e in list < 2"); return -1;}

    // Находим первое и последнее вхождение элемента E
    while (curr) {
        if (curr->value == e) {
            if (first == NULL){first = curr;}
            last = curr;
        }
        curr = curr->next;
    }
    Node* tmpLast = last;
    //Реверс конца списка
    while (last) {
        Node* tmp = last->next;
        last->next = reverst;
        reverst = last;
        last = tmp;
    }
    last = tmpLast;
    //Внесение элементов от последнего вхождения Е
    while (reverst) {
        Node* tmp = reverst->next;
        reverst->next = answ;
        answ = reverst;
        reverst = tmp;
    }
    Node* tmpFirst = first;
    first = first->next;
    //Внесение реверсированных элементов между первым и последними вхождение Е
    while (first != last) {
        Node* tmp = first->next;
        first->next = answ;
        answ = first;
        first = tmp;
    }
    first = tmpFirst->next;
    //Реверс элементов до первого вхождения Е
    while(head != first) {
        Node* tmp = head->next;
        head->next = reverst;
        reverst = head;
        head = tmp;
    }
    while (reverst) {
        Node* tmp = reverst->next;
        reverst->next = answ;
        answ = reverst;
        reverst = tmp;
    }





    return answ;


}




#pragma endregion
#pragma region Меню


void menuList(Node *head,int val){
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
                   "\t\t  8 Reverse list on first E to last E"
                   "\n"
           "_______________________________________________________"
                   "\n"
                );
    scanf("%d", &val);
    switch (val) {
        case 1: {
            isNull(head);
            break;
        }
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
                            Node *tmp = head;
                            printLinkedList(head);
                            head = tmp;
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
                }
        case 3: {
                    char s[10];
                    int a = 0;
                    printf("\t\t  input elements\n");
                    getchar();
                    fgets(s,10,stdin);
                    a = strtol(s,NULL,10);
                    search(head,a);
                    break;
                }
        case 4: {
                    char value[10];
                    printf("Which element is being inserted?\n");
                    getchar();
                    fgets(value,10,stdin);
                    printf(
                "\n "
                   "_______________________________________________________"
                   "\n"
                   "\t\t  1  Add element before n-th element"
                   "\n"
                   "\t\t  2  Add element after n-th element"
                   "\n"
                   "\t\t  3  Add element to start"
                   "\n"
                   "\t\t  4  Add element to end"
                   "\n"

           "_______________________________________________________"
                   "\n"
                );
                    scanf("%d", &val);
                    getchar();
                    switch (val) {
                        case 1:{
                            int valueNth;
                            printf("Before which element?\n");
                            scanf("%d", &valueNth);
                            int n = 0;
                            Node* tmp = head;
                            while (head != 0 && head->value != valueNth) {
                                    n++;
                                head = head->next;
                            }
                            head = tmp;



                            insertBefore(head,n,strtol(value,NULL,10));
                            printLinkedList(head);
                            break;
                        }
                        case 2: {
                            int valueNth;
                            printf("After which element?\n");
                            scanf("%d", &valueNth);
                            int n = 0;
                            Node* tmp = head;
                            while (head != 0 && head->value != valueNth) {
                                n++;
                                head = head->next;
                            }
                            head = tmp;



                            insertAfter(head,n,strtol(value,NULL,10));
                            printLinkedList(head);
                            break;
                        }
                        case 3: {
                            push(head,strtol(value,NULL,10));
                            printLinkedList(head);
                            break;
                        }
                        case 4: {
                            pushEnd(head,value);
                            printLinkedList(head);
                            break;
                        }
                    }
                    break;
                }
        case 5: {
                    printf(
                "\n "
                   "_______________________________________________________"
                   "\n"
                   "\t\t  1  Delete start element"
                   "\n"
                   "\t\t  2  Delete end element"
                   "\n"
                   "\t\t  3  Delete N-th element"
                   "\n"
                   "\t\t  4  Delete all list"
                   "\n"
           "_______________________________________________________"
                   "\n"
                );
                    scanf("%d", &val);
                    switch (val) {
                        case 1: {
                            deleteStart(&head);
                            printLinkedList(head);
                            break;
                        }
                        case 2: {
                            deleteEnd(&head);
                            printLinkedList(head);
                            break;
                        }
                        case 3: {
                            int valueNth;
                            printf("Which element delete?\n");
                            scanf("%d", &valueNth);
                            getchar();
                            int n = 0;
                            Node* tmp = head;
                            while (head != 0 && head->value != valueNth) {
                                n++;
                                head = head->next;
                            }
                            head = tmp;
                            deleteNth(&head,n);
                            printLinkedList(head);
                            break;
                        }
                        case 4: {
                            deleteList(&head);
                            printLinkedList(head);
                            break;
                        }
                    }
                    break;
                }
        case 6: {
                    printf(
            "\n "
               "_______________________________________________________"
               "\n"
               "\t\t  1  Output first element"
               "\n"
               "\t\t  2  Output last element"
               "\n"
               "\t\t  3  Output N-th element"
               "\n"
       "_______________________________________________________"
               "\n"
            );
                    scanf("%d", &val);
                    switch (val) {
                        case 1: {
                            printf("%d", pop(&head));
                            break;
                        }
                        case 2: {
                            printf("%d",popEnd(&head));
                            break;
                        }
                        case 3: {
                            int valueNth;
                            printf("Which element output?\n");
                            scanf("%d", &valueNth);
                            getchar();
                            int n = 0;
                            Node* tmp = head;
                            while (head != 0 && head->value != valueNth) {
                                n++;
                                head = head->next;
                            }
                            head = tmp;
                            printf("%d",popNth(&head,n));
                            break;
                        }
                    }
                    break;
                }
        case 7: {
                    printf(
   "\n "
      "_______________________________________________________"
      "\n"
      "\t\t  1  Print first"
      "\n"
      "\t\t  2  Print last"
      "\n"
      "\t\t  3  Print all"
      "\n"
"_______________________________________________________"
      "\n"
   );
                    scanf("%d", &val);
                    switch (val) {
                        case 1:{Node *tmp = head;printFromHead(head);head=tmp;;break;}
                        case 2:{Node *tmp = head;printFromEnd(head);head=tmp;;break;}
                        case 3:{Node *tmp = head;printLinkedList(head);head=tmp;;break;}
                    }
                    break;
                }
        case 8: {
                    int value;
                    printf("Insert E\n");
                    scanf("%d", &value);
                    getchar();
                    head = reverseBetweenFirstAndLast(head,value);
                    break;
        }
        default:break;
            }
    val = 0;
    menuList(head,val);
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
            menuList(head,val);
            }
        case 2: printf("stack");break;
        case 3: printf("queue");break;
    }
}





