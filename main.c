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
void strToArr(char* S, int* arr)
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

#pragma region Реализация очереди и работа с ней
//Структура очереди
typedef struct Queue {
    Node *frnt,*rear;
}Queue;
//Инициализация очереди
Queue *init() {
    Queue *q = (Queue*)malloc(sizeof(Queue*));
    q->frnt = NULL;
    q->rear = NULL;
    return q;
}
//Проверка пуста ли очередь
int isEmpty(Queue *q) {
    if(q->frnt != NULL) {
        return 0;
    }
    else {
        return 1;
    }
}
//Удаление всей очереди
void delete(Queue *q)
{
    Node *temp;
    if(isEmpty(q)==1) {
        printf("Очередь пуста!\n");
        return;
    }
    temp = q->frnt;
    q->frnt = q->frnt->next;
    free(temp);
    if (q->frnt!= NULL) {
        delete(q);
    }
}
//Удаление элемента очереди
void deleteNthElmQueue(Queue *q,int value)
{
    Node *curr,*prev;
    if(isEmpty(q)==1) {
        printf("Queue is NULL!\n");
        return;
    }
    for(curr = q->frnt; curr!= NULL; curr=curr->next) {

        if (curr->value != value) {
            prev = curr;
        }else {
            if (curr == q->frnt) {
                prev = curr;
                (*curr) = (*prev->next);return;
            }else {
                if (curr->next != NULL) {
                    prev->next = curr->next;
                    return;
                }else {
                    prev->next = NULL;
                    (*curr) = (*prev);
                    return;
                }
            }

        }

    }
}
//Посмотреть и удалить
int popQueue(Queue *q) {
    Node*temp;
    int x;
    if(isEmpty(q)==1) {
        printf("Queue is NULL!\n");
        return 0;
    }
    x = q->frnt->value;
    temp = q->frnt;
    q->frnt = q->frnt->next;
    free(temp);
    return x;
}
//Посмотреть и удалить элемент
int popQueueNth(Queue *q, int value) {
    Node *curr,*prev;
    int x;
    if(isEmpty(q)==1) {
        printf("Queue is NULL!\n");
        return 0;
    }
    for(curr = q->frnt; curr!= NULL; curr=curr->next) {

        if (curr->value != value) {
            prev = curr;
        }else {
            if (curr == q->frnt) {
                prev = curr;
                (*curr) = (*prev->next);return curr->value;
            }else {
                if (curr->next != NULL) {
                    prev->next = curr->next;
                    return curr->value;
                }else {
                    prev->next = NULL;
                    (*curr) = (*prev);
                    return curr->value;
                }
            }

        }

    }
}
//Функция добавления элемента в очередь
void insertToQueue(Queue *q, int elm)
{
    Node *tmp;
    tmp = (Node*)malloc(sizeof(Node*));
    tmp->next = NULL;
    tmp->value = elm;
    if(q->rear != NULL)
        q->rear->next = tmp;
    else {
        q->frnt = tmp;
    }
q->rear = tmp;
}
//Сформировать очередь
void createQueue(Queue *q,int* elms, int len) {
    for (size_t i = 0; i < len;i++) {
        insertToQueue(q,elms[i]);
    }
}
//Вывод всех элементов очереди
void printQueue(Queue* q) {
    Node *h;
    if(isEmpty(q)==1) {
        printf("Queue is Null!\n");
        return;
    }
    for(h = q->frnt; h!= NULL; h=h->next)
        printf("%d ",h->value);
}
//Поиск элемента очереди
void searchElmInQueue(Queue *q,int val) {
    if (q->frnt == 0) {
        printf("Queue is NULL");
    }else {
        Node *h;
        for(h = q->frnt; h!= NULL; h=h->next){
            if (h->value == val) {
                printf("This element is present in queue");
                return;
            }
        }

    }
}
//Количество элементов с одинаковыми соседями
int countElementsWithSameNeighbours(Queue* queue) {
    int count = 0;
    Node* current = queue->frnt;
    Node* previous = NULL;
    Node* next = NULL;

    while (current != NULL) {
        next = current->next;

            if (previous != NULL && next != NULL && current->value == previous->value && current->value == next->value)
            count++;

        previous = current;
        current = next;
    }

    return count;
}
#pragma endregion

#pragma region Реализация стека и работа с ним
//Структура стека
typedef struct Stack
{
    int size;
    Node *top;
}Stack;
//Инициализация стека
void stack_Init(Stack **stack) {
    Stack *new_stack = NULL;
    if((new_stack = (Stack*)malloc(sizeof(Stack))) == NULL)
    {
        return;
    }
    new_stack->top = NULL;
    new_stack->size = 0;
    (*stack) = new_stack;
}
//Вывести из стека
int stack_Pop(Stack* stack,int* value) {
    if(stack->top == NULL)
    {
        return -1;
    }
    if (stack->size != 0) {
        stack->size--;
        *value = stack->top->value;
        stack->top = stack->top->next;
        return *value;
    }else {
        printf("Stack UNDERFLOW");
        return -1;
    }
}
//Внести в стек
void stack_Push(Stack* stack,int value) {
    Node *newElmt = NULL;
    if(stack == NULL || (newElmt = (Node*)malloc(sizeof(Node))) == NULL)
    {
        return;
    }
    if (stack->size != 20) {
        newElmt->value = value;
        newElmt->next = stack->top;
        stack->size++;
        stack->top = newElmt;
    }else {
        printf("Stack OVERFLOW\n");
    }

}
//Уничтожить стек
int stack_Destory(Stack **stack) {
    int count = 0;
    int value;
    if(*stack == NULL)
    {
        return -1;
    }
    count = (*stack)->size;
    while((*stack)->size > 0)
    {
        stack_Pop(*stack,&value);
    }
    free(*stack);
    *stack = NULL;
    return count;
}
//Проверка стека на пустоту
void isEmptyStack(Stack* stack) {
    if (stack->top == NULL) {
        printf("Stack is NULL");
    }else {
        printf("Stack is not NULL");
    }
}
//Формирование стека
void createStack(Stack* stack,int value) {
    stack_Push(stack,value);
}
//Поиск элемента в стеке
void searchElmStack(Stack* stack,int value) {
    Node* tmp = NULL; ;
    for (tmp = stack->top;tmp != NULL;tmp = tmp->next) {
        if (tmp->value == value) {
            printf("This element is present in stack");
            return;
        }
        if (tmp == NULL) {
            printf("This element is not present in stack");
        }
    }

}
//Посмотреть и удалить элемент
int PopElmStack(Stack *stack,int value) {
    Node *curr,*prev;
    int x;
    if(stack->top == NULL) {
        printf("Stack is NULL!\n");
        return 0;
    }
    for(curr = stack->top; curr!= NULL; curr=curr->next) {

        if (curr->value != value) {
            prev = curr;
        }else {
            if (curr == stack->top) {
                prev = curr;
                (*curr) = (*prev->next);return curr->value;
            }else {
                if (curr->next != NULL) {
                    prev->next = curr->next;
                    return curr->value;
                }else {
                    prev->next = NULL;
                    (*curr) = (*prev);
                    return curr->value;
                }
            }

        }

    }
}
//Посмотреть и удалить элемент
void PopAllStack(Stack *stack) {
    int value = 0;
    while (stack_Pop(stack,&value) != -1)
    printf("%d ",value);
}
//Удалить элемент
void deleteElmStack(Stack* stack,int value) {
    Node *curr,*prev;
    if(stack->top == NULL) {
        printf("Stack is NULL!\n");
        return;
    }
    for(curr = stack->top; curr!= NULL; curr=curr->next) {

        if (curr->value != value) {
            prev = curr;
        }else {
            if (curr == stack->top) {
                prev = curr;
                (*curr) = (*prev->next);return;
            }else {
                if (curr->next != NULL) {
                    prev->next = curr->next;
                    return;
                }else {
                    prev->next = NULL;
                    (*curr) = (*prev);
                    return;
                }
            }

        }

    }
}
//Вывети вершину стека
void printTopStack(Stack* stack) {
    printf("%d ",stack->top->value);
}
//Вывети вершину стека
void printAllStack(Stack* stack) {
    Node* tmp = NULL; ;
    for (tmp = stack->top;tmp != NULL;tmp = tmp->next) {
        printf("%d " , tmp->value);
    }
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
                   "\t\t  6  Take a list item"
                   "\n"
                   "\t\t  7  Viewing list items"
                   "\n"
                   "\t\t  8  Reverse list on first E to last E"
                   "\n"
                   "\t\t  9  Exit in grand menu"
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
                            strToArr(&str,&array);
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
                            strToArr(&str,&array);
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
        case 9: {
            free(head);
            return;
        }
        default: {
            exit(-1);
        }
            }
    val = 0;
    menuList(head,val);
    }

void menuQueue(Node *head,Queue *q, int val) {
    printf(
    "\n "
           "_______________________________________________________"
           "\n"
           "\t\t  1  Check if the queue is empty"
           "\n"
           "\t\t  2  Creating a queue"
           "\n"
           "\t\t  3  Searching for a queue item"
           "\n"
           "\t\t  4  Adding a queue item"
           "\n"
           "\t\t  5  Deleting"
           "\n"
           "\t\t  6  Take a queue item"
           "\n"
           "\t\t  7  Viewing queue items"
           "\n"
           "\t\t  8  Defines the number of elements that have the same neighbors"
           "\n"
           "\t\t  9  Exit in grand menu"
           "\n"
   "_______________________________________________________"
           "\n"
               );
    scanf("%d",&val);
    switch (val) {
        case 1: {
            if (isEmpty(q) == 1) {
                printf("Queue is NULL\n");
            }else {
                printf("Queue is not NULL\n");
            }
            break;
        }
        case 2: {
            char str[1024];

            printf("\t\t  input elements through (,)\n");
            getchar();
            fgets(&str,1024,stdin);

            int len = lenIntMass(&str);
            int array[len];

            strToArr(&str,&array);
            createQueue(q,array,len);
            printQueue(q);
            break;
        }
        case 3: {
            int value = 0;
            char str[10];
            printf("Insert value is search in queue\n");
            scanf("%s",str);
            value = strtol(str,NULL,10);
            searchElmInQueue(q,value);
            break;
        }
        case 4: {

            char str[10];
            printf("Insert adding value\n");
            int newValue = 0;

            getchar();
            scanf("%s",&str);
            newValue = strtol(str,NULL,10);
            insertToQueue(q,newValue);
            printQueue(q);
            break;
        }
        case 5: {
            printf(
                "\n "
                       "_______________________________________________________"
                       "\n"
                       "\t\t  1  Delete element queue"
                       "\n"
                       "\t\t  2  Delete all queue"
                       "\n"
               "_______________________________________________________"
                       "\n"
                           );
            scanf("%d",&val);
            switch (val) {
                case 1: {
                    int value = 0;
                    char str[10];
                    printf("Insert delete value\n");
                    getchar();
                    scanf("%s",str);
                    value = strtol(str,NULL,10);
                    deleteNthElmQueue(q,value);
                    break;
                }
                case 2:{
                delete(q);
                break;
                }
            }
            break;
        }
        case 6: { printf(
                "\n "
                       "_______________________________________________________"
                       "\n"
                       "\t\t  1  Output element queue"
                       "\n"
                       "\t\t  2  Output all queue"
                       "\n"
               "_______________________________________________________"
                       "\n"
                           );
            scanf("%d",&val);
            switch (val) {
                case 1: {
                    int value = 0;
                    char str[10];
                    printf("Insert value for output\n");
                    getchar();
                    scanf("%s",str);
                    value = strtol(str,NULL,10);
                    printf("%d",popQueueNth(q,value));
                    break;
                }
                case 2: {
                    while (q->frnt != NULL) {
                        printf("%d ",popQueue(q));
                    };break;
                }
            }

        }
        case 7: {printf(
                "\n "
                       "_______________________________________________________"
                       "\n"
                       "\t\t  1  Print First"
                       "\n"
                       "\t\t  2  Print Rear"
                       "\n"
                       "\t\t  3  Print all"
                       "\n"
               "_______________________________________________________"
                       "\n"
                           );
                scanf("%d",&val);
                switch (val) {
                    case 1: {
                        printf("%d \n",q->frnt->value);
                        break;
                    }
                    case 2: {
                        printf("%d \n",q->rear->value);
                        break;
                    }
                    case 3: {
                        printQueue(q);
                        break;;
                    }
                }

            break;
        }
        case 8: {
            printf("%d",countElementsWithSameNeighbours(q));
            break;
        }
        case 9: {
            free(q);
            return;;
        }
        default:{exit(-1);}
    }

    menuQueue(head,q,val);
}

void menuStack(Node *head,Stack *stack, int val) {
    printf(
    "\n "
           "_______________________________________________________"
           "\n"
           "\t\t  1  Check if the stack is empty"
           "\n"
           "\t\t  2  Creating a stack"
           "\n"
           "\t\t  3  Searching for a stack item"
           "\n"
           "\t\t  4  Adding a stack item"
           "\n"
           "\t\t  5  Deleting"
           "\n"
           "\t\t  6  Take a stack item"
           "\n"
           "\t\t  7  Viewing stack items"
           "\n"
           "\t\t  9  Exit in grand menu"
           "\n"
   "_______________________________________________________"
           "\n"
               );
    scanf("%d",&val);
    switch (val) {
        case 1: {
            isEmptyStack(stack);
            break;
        }
        case 2: {
            char str[1024];

            printf("\t\t  input elements through (,)\n");
            getchar();
            fgets(&str,1024,stdin);

            int len = lenIntMass(&str);
            int array[len];

            strToArr(&str,&array);
            for (int i = 0;i < len;i++) {
                createStack(stack,array[i]);
                if (i > 20) {
                    printf("Stack OVERFLOW\n");
                    return;
                }
            }
            break;
        }
        case 3: {
            int value = 0;
            char str[10];
            printf("Insert value is search in stack\n");
            scanf("%s",str);
            value = strtol(str,NULL,10);
            searchElmStack(stack,value);
            break;
        }
        case 4: {

            char str[10];
            printf("Insert adding value\n");
            int newValue = 0;

            getchar();
            scanf("%s",&str);
            newValue = strtol(str,NULL,10);
            if (stack->size == 20) {

                printf("Stack OVERFLOW\n");
                break;
            }else {
                stack_Push(stack,newValue);
                printAllStack(stack);
            }
            break;
        }
        case 5: {
            printf(
                "\n "
                       "_______________________________________________________"
                       "\n"
                       "\t\t  1  Delete element stack"
                       "\n"
                       "\t\t  2  Delete all stack"
                       "\n"
               "_______________________________________________________"
                       "\n"
                           );
            scanf("%d",&val);
            switch (val) {
                case 1: {
                    int value = 0;
                    char str[10];
                    printf("Insert delete value\n");
                    getchar();
                    scanf("%s",str);
                    value = strtol(str,NULL,10);
                    deleteElmStack(stack,value);
                    break;
                }
                case 2:{
                    printf("Count delete element: %d\n",stack_Destory(&stack));
                    stack_Init(&stack);
                    break;
                }
            }
            break;
        }
        case 6: { printf(
                "\n "
                       "_______________________________________________________"
                       "\n"
                       "\t\t  1  Output element stack"
                       "\n"
                       "\t\t  2  Output all stack"
                       "\n"
               "_______________________________________________________"
                       "\n"
                           );
            scanf("%d",&val);
            switch (val) {
                case 1: {
                    int value = 0;
                    char str[10];
                    printf("Insert value for output\n");
                    getchar();
                    scanf("%s",str);
                    value = strtol(str,NULL,10);
                    PopElmStack(stack,value);

                    printf("%d",PopElmStack(stack,value));
                    break;
                }
                case 2: {
                    while (stack->top != NULL) {
                        PopAllStack(stack);
                    };break;
                }
            }

        }
        case 7: {
            printf(
           "\n "
                  "_______________________________________________________"
                  "\n"
                  "\t\t  1  Print Top"
                  "\n"
                  "\t\t  2  Print all"
                  "\n"
          "_______________________________________________________"
                  "\n"
                      );
            scanf("%d",&val);
            switch (val) {
                case 1: {
                    printTopStack(stack);
                    break;
                }
                case 2: {
                    printAllStack(stack);
                    break;

                }

                break;
            }
            case 9: {
                free(stack);
                return;;
            }
            default:{exit(-1);}

        }
    } menuStack(head,stack,val);
}

void grandMenu(Node *head,Queue *q,Stack* stack) {
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
           "\t\t  2   Work with queue"
           "\n"
           "\t\t  3   Work with stack"
           "\n"
           "\t\t  0   Exit"
           "\n"
           "_______________________________________________________"
           "\n"
           );
    scanf("%d",&val);
    switch (val) {
        case 1: {menuList(head,val);break;}
        case 2: {menuQueue(head,q,val);break;}
        case 3: {menuStack(head,stack,val);break;};
        case 9: {exit(0);}
        default:{exit(-1);}
    }
    grandMenu(head,q,stack);
}

#pragma endregion

int main() {
    //Опусташаем список
    Node *head = NULL;
    Queue *q = init();
    Stack* stack;
    stack_Init(&stack);
    grandMenu(head,q,stack);
}





