#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
} node;
struct BigInteger
{
    node *head;
    int length;
};
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger sub(struct BigInteger a, struct BigInteger b);
struct BigInteger mul(struct BigInteger a, struct BigInteger b);
struct BigInteger div1(struct BigInteger a, struct BigInteger b);
struct BigInteger mod(struct BigInteger a, struct BigInteger b);
void insertend(node **, int);
void display(struct BigInteger a);
int count(struct BigInteger a);
int compare(struct BigInteger a, struct BigInteger b);
struct BigInteger copy(struct BigInteger a);
// int main()
// {
//     char str1[100];
//     char str2[100];
//     printf("Enter 1st number\n");
//     gets(str1);
//     printf("Enter 2nd number\n");
//     gets(str2);
//     struct BigInteger a = initialize(str1);
//     struct BigInteger b = initialize(str2);
//     printf("1st number is:");
//     display(a);
//     printf("2nd number is:");
//     display(b);
//     printf("sum is:");
//     struct BigInteger sum = add(a, b);
//     display(sum);
//     printf("diffrence is:");
//     struct BigInteger dif = sub(a, b);
//     display(dif);
//     printf("quotient is:");
//     struct BigInteger div = div1(a, b);
//     display(div);
//     printf("remainder is:");
//     struct BigInteger rem = mod(a, b);
//     display(rem);
//     printf("product is:");
//     struct BigInteger pro = mul(a, b);
//     display(pro);
// }
struct BigInteger initialize(char *a)
{
    struct BigInteger b;
    struct node *temp = NULL;
    int i, l, x = 0;
    for (i = 0; *(a + i) != '\0'; i++)
        x++;
    b.length = x;
    for (i = 0; i < b.length; i++)
    {
        int f = *(a + i) - '0';
        insertend(&temp, f);
    }
    b.head = temp;
    while (b.head->data == 0 && b.head->next != NULL)
    {
        b.head = b.head->next;
        b.head->prev = NULL;
    }
    return b;
}
void insertend(node **head, int a)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = a;
    temp->next = NULL;
    temp->prev = NULL;
    if (*head == NULL)
    {
        *head = temp;
        return;
    }
    node *itr = *head;
    while (itr->next != NULL)
        itr = itr->next;
    itr->next = temp;
    temp->prev = itr;
}
void display(struct BigInteger a)
{
    node *itr = a.head;
    while (itr != NULL)
    {
        printf("%d", itr->data);
        itr = itr->next;
    }
    printf("\n");
}
int count(struct BigInteger a)
{
    node *itr = a.head;
    int c = 0;
    while (itr != NULL)
    {
        c++;
        itr = itr->next;
    }
    return c;
}
struct BigInteger copy(struct BigInteger a)
{
    node *itr = a.head;
    struct BigInteger x;
    x.head = NULL;
    node *itr1 = NULL;
    while (itr != NULL)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->next = NULL;
        temp->prev = NULL;
        temp->data = itr->data;
        if (x.head == NULL)
        {
            x.head = temp;
            itr1 = temp;
        }
        else
        {
            itr1->next = temp;
            temp->prev = itr1;
            itr1 = temp;
        }
        itr = itr->next;
    }
    return x;
}
struct BigInteger add(struct BigInteger a, struct BigInteger b)
{

    node *tail1 = a.head;
    node *tail2 = b.head;
    struct BigInteger sum;
    sum.head = NULL;
    int car = 0;
    while (tail1->next != NULL)
        tail1 = tail1->next;
    while (tail2->next != NULL)
        tail2 = tail2->next;
    while (tail1 != NULL || tail2 != NULL)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->next = NULL;
        temp->prev = NULL;
        if (tail1 == NULL)
        {
            temp->data = tail2->data + car;
            tail2 = tail2->prev;
        }
        else if (tail2 == NULL)
        {
            temp->data = tail1->data + car;
            tail1 = tail1->prev;
        }
        else
        {
            temp->data = tail2->data + tail1->data + car;
            tail1 = tail1->prev;
            tail2 = tail2->prev;
        }
        if (temp->data > 9)
        {
            car = temp->data / 10;
            temp->data %= 10;
        }
        else
        {
            car = 0;
        }
        if (sum.head == NULL)
        {
            sum.head = temp;
        }
        else
        {
            (sum.head)->prev = temp;
            temp->next = sum.head;
            sum.head = temp;
        }
    }
    if (car != 0)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->next = NULL;
        temp->prev = NULL;
        temp->data = car;
        (sum.head)->prev = temp;
        temp->next = sum.head;
        sum.head = temp;
    }
    return sum;
}
struct BigInteger sub(struct BigInteger a, struct BigInteger b)
{
    int c1 = count(a);
    int c2 = count(b);
    int k = 0;
    struct BigInteger x = copy(a);
    struct BigInteger y = copy(b);
    node *head1 = x.head;
    node *head2 = y.head;
    node *tail1;
    node *tail2;
    struct BigInteger dif;
    dif.head = NULL;
    int bor = 0;
    if (c1 > c2)
    {
        tail1 = x.head;
        tail2 = y.head;
    }
    else if (c1 == 1 && c2 == 1)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->data = head1->data - head2->data;
        temp->next = NULL;
        temp->prev = NULL;
        dif.head = temp;
        return dif;
    }
    else if (c1 == c2)
    {
        node *itr1 = x.head;
        node *itr2 = y.head;
        while (itr1->next != NULL || itr2->next != NULL)
        {
            if (itr1->data > itr2->data)
            {
                tail1 = x.head;
                tail2 = y.head;
                break;
            }
            else if (itr1->data < itr2->data)
            {
                tail1 = y.head;
                tail2 = x.head;
                k++;
                break;
            }
            itr1 = itr1->next;
            itr2 = itr2->next;
        }
        if (itr1->next == NULL || itr2->next == NULL)
        {
            node *temp = (node *)malloc(sizeof(node));
            temp->data = 0;
            temp->next = temp->prev = NULL;
            dif.head = temp;
            return dif;
        }
    }
    else
    {
        tail1 = y.head;
        tail2 = x.head;
        k++;
    }
    while (tail1->next != NULL)
        tail1 = tail1->next;
    while (tail2->next != NULL)
        tail2 = tail2->next;
    while (tail1 != NULL)
    {
        node *temp = (node *)malloc(sizeof(node));
        temp->next = NULL;
        temp->prev = NULL;
        if (tail1->data >= tail2->data)
        {
            temp->data = tail1->data - tail2->data;
        }
        else
        {
            temp->data = (tail1->data + 10) - tail2->data;
            bor = 1;
        }
        tail1 = tail1->prev;
        if (tail2->prev != NULL)
            tail2 = tail2->prev;
        else
            tail2->data = 0;
        if (bor == 1)
        {
            if (tail1->data == 0 && tail1->prev != NULL)
            {
                tail1->data = 9;
                bor = 1;
            }
            else
            {
                tail1->data -= 1;
                bor = 0;
            }
        }
        if (dif.head == NULL)
        {
            dif.head = temp;
        }
        else
        {
            (dif.head)->prev = temp;
            temp->next = dif.head;
            dif.head = temp;
        }
    }
    while (dif.head->data == 0)
        dif.head = dif.head->next;
    if (k != 0)
        dif.head->data = -1 * dif.head->data;
    return dif;
}
int compare(struct BigInteger a, struct BigInteger b)
{
    int c1 = 0, c2 = 0;
    node *itr = a.head;
    while (itr != NULL)
    {
        itr = itr->next;
        c1++;
    }
    node *itr2 = b.head;
    while (itr2 != NULL)
    {
        itr2 = itr2->next;
        c2++;
    }
    if (c1 > c2)
        return 1;
    itr = a.head;
    itr2 = b.head;
    if (c1 == c2)
    {
        while (itr != NULL && itr2 != NULL)
        {
            if (itr->data == itr2->data)
            {
                if (itr->next == 0)
                {
                    return 0;
                }
                itr = itr->next;
                itr2 = itr2->next;
            }
            else if (itr->data > itr2->data)
                return 1;
            else
                return 0;
        }
    }
    else
        return 0;
}
struct BigInteger div1(struct BigInteger a, struct BigInteger b)
{
    int q = 0;
    struct BigInteger divident;
    struct BigInteger divisor;
    struct BigInteger subt;
    struct BigInteger d;
    struct BigInteger q1;
    divident.head = a.head;
    divisor.head = b.head;
    if (divident.head->data == 0 && divisor.head->data == 0)
    {
        printf("not defined");
        divident.head = NULL;
        return divident;
    }
    else if (divisor.head->data == 0)
    {
        printf("infinite");
        divident.head = NULL;
        return divident;
    }
    subt.head = NULL;
    node *temp = (node *)malloc(sizeof(node));
    node *temp1 = (node *)malloc(sizeof(node));
    temp->next = temp->prev = temp1->prev = temp1->next = d.head = q1.head = NULL;
    temp->data = 1;
    d.head = temp;
    temp1->data = 0;
    q1.head = temp1;
    while (compare(divident, divisor))
    {
        subt = sub(divident, divisor);
        divident.head = subt.head;
        q1 = add(q1, d);
    }
    return q1;
}
struct BigInteger mod(struct BigInteger a, struct BigInteger b)
{
    int q = 0;
    struct BigInteger divident;
    struct BigInteger divisor;
    struct BigInteger subt;
    struct BigInteger d;
    struct BigInteger q1;
    divident.head = a.head;
    divisor.head = b.head;
    if (divident.head->data == 0 && divisor.head->data == 0)
    {
        printf("not defined");
        divident.head = NULL;
        return divident;
    }
    else if (divisor.head->data == 0)
    {
        printf("no remainder");
        divident.head = NULL;
        return divident;
    }
    subt.head = NULL;
    node *temp = (node *)malloc(sizeof(node));
    node *temp1 = (node *)malloc(sizeof(node));
    temp->next = temp->prev = temp1->prev = temp1->next = d.head = q1.head = NULL;
    temp->data = 1;
    d.head = temp;
    temp1->data = 0;
    q1.head = temp1;
    while (compare(divident, divisor))
    {
        subt = sub(divident, divisor);
        divident.head = subt.head;
        q1 = add(q1, d);
    }
    if (compare(divident, divisor) == 0)
        return divident;
    return subt;
}
struct BigInteger mul(struct BigInteger a, struct BigInteger b)
{
    int c1 = count(a);
    int c2 = count(b);
    struct BigInteger pro;
    struct BigInteger upper;
    struct BigInteger lower;
    struct BigInteger q1;
    struct BigInteger d;
    node *temp = (node *)malloc(sizeof(node));
    node *temp1 = (node *)malloc(sizeof(node));
    temp->next = temp->prev = temp1->prev = temp1->next = d.head = q1.head = pro.head = NULL;
    upper.head = NULL;
    lower.head = NULL;
    temp1->data = 1;
    q1.head = temp1;
    temp->data = 0;
    d.head = temp;
    pro.head = temp;
    if (c1 > c2)
    {
        upper.head = a.head;
        lower.head = b.head;
    }
    else
    {
        upper.head = b.head;
        lower.head = a.head;
    }
    while (compare(lower, d))
    {
        pro = add(pro, upper);
        d = add(d, q1);
    }
    return pro;
}