/* 线性表的单链表存储结构 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <math.h>
#include <time.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

/* 结点组成 */
/* 1. 存放数据元素的数据域 */
/* 2. 存放后继结点地址的指针域 */
/* 
假设p是指向线性表第i个元素的指针，
    则该结点ai的数据域可以用p->data表示
        p->data的值是第一个数据元素
    结点ai的指针域可以用p->next表示
        p->next的值是一个指针，p->next指向第i+1个元素，及指向a(i+1)的指针
    即：如果p->data=a1，那么p->next->data=a(i+1)
 */
typedef struct Node
{
    ElemType data;
    struct Node *next;
} Node;

typedef struct Node *LinkList; /* 定义LinkList */


/* 初始化链式线性表 */
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */
    if (!(*L))                           /* 存储分配失败 */
        return ERROR;
    (*L)->next = NULL; /* 指针域为空 */

    return OK;
}


/* 初始条件：链式线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */
/* 由于单链表没有定义表长，所以不方便使用for来控制循环，只能通过工作指针后移来查找 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j;
    LinkList p;        /* 声明一结点p */
    p = L->next;       /* 让p指向链表L的第一个结点 */
    j = 1;             /*  j为计数器 */
    while (p && j < i) /* p不为空或者计数器j还没有等于i时，循环继续 */
    {
        p = p->next; /* 让p指向下一个结点 */
        ++j;
    }
    if (!p || j > i)
        return ERROR; /*  第i个元素不存在 */
    *e = p->data;     /*  取第i个元素的数据 */
    return OK;
}


/* 初始条件：链式线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */
Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p, s;
    p = *L;
    j = 1;
    while (p && j < i) /* 寻找第i个结点 */
    {
        p = p->next;
        ++j;
    }
    if (!p || j > i)
        return ERROR;                   /* 第i个元素不存在 */
    s = (LinkList)malloc(sizeof(Node)); /*  生成新结点(C语言标准函数) */
    s->data = e;
    s->next = p->next; /* 将p的后继结点赋值给s的后继  */
    p->next = s;       /* 将s赋值给p的后继 */
    return OK;
}


/* 初始条件：链式线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */
Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p, q;
    p = *L;
    j = 1;
    while (p->next && j < i)  /* 遍历寻找第i个元素 */
    {
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i)
        return ERROR;  /* 第i个元素不存在 */
    q = p->next;
    p->next = q->next; /* 将q的后继赋值给p的后继 */
    *e = q->data;      /* 将q结点中的数据给e */
    free(q);           /* 让系统回收此结点，释放内存 */
    return OK;
}


/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;
    srand(time(0));  /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;  /*  先建立一个带头结点的单链表 */
    for (i = 0; i < n; i++)
    {
        p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
        p->data = rand() % 100 + 1;         /*  随机生成100以内的数字 */
        p->next = (*L)->next;
        (*L)->next = p;  /* 插入到表头 */
    }
}


/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;
    srand(time(0));                       /* 初始化随机数种子 */
    *L = (LinkList)malloc(sizeof(Node));  /* L为整个线性表 */
    r = *L;                               /* r为指向尾部的结点 */
    for (i = 0; i < n; i++)
    {
        p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
        p->data = rand() % 100 + 1;       /*  随机生成100以内的数字 */
        r->next = p;                      /* 将表尾终端结点的指针指向新结点 */
        r = p;                            /* 将当前的新结点定义为表尾终端结点 */
    }
    r->next = NULL; /* 表示当前链表结束 */
}


/* 初始条件：链式线性表L已存在。 */
/* 操作结果：将L重置为空表 */
Status ClearList(LinkList *L)
{
    LinkList p, q;
    p = (*L)->next; /*  p指向第一个结点 */
    while (p)       /*  没到表尾 */
    {
        q = p->next;
        free(p);
        p = q;
    }
    (*L)->next = NULL; /* 头结点指针域为空 */
    return OK;
}


/* 初始条件：链式线性表L已存在。 */
/* 操作结果：若L为空表，则返回TRUE，否则返回FALSE */
Status ListEmpty(LinkList L)
{
    if (L->next)
        return FALSE;
    else
        return TRUE;
}


/* 初始条件：链式线性表L已存在。*/
/* 操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next; /* p指向第一个结点 */
    while (p)
    {
        i++;
        p = p->next;
    }
    return i;
}


Status visit(ElemType c)
{
    printf("%d ", c);
    return OK;
}


/* 初始条件：链式线性表L已存在 */
/* 操作结果：返回L中第1个与e满足关系的数据元素的位序。 */
/* 若这样的数据元素不存在，则返回值为0 */
int LocateElem(LinkList L, ElemType e)
{
    int i = 0;
    LinkList p = L->next;
    while (p)
    {
        i++;
        if (p->data == e) /* 找到这样的数据元素 */
            return i;
        p = p->next;
    }

    return 0;
}


/* 初始条件：链式线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p = L->next;
    while (p)
    {
        visit(p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}


int main()
{
    LinkList L;
    ElemType e;
    Status i;
    int j, k;
    i = InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n", ListLength(L));  /* 初始化L后：ListLength(L)=0 */
    for (j = 1; j <= 5; j++)
        i = ListInsert(&L, 1, j);
    printf("在L的表头依次插入1~5后：L.data=");  /* 在L的表头依次插入1～5后：L.data=5 4 3 2 1  */
    ListTraverse(L);

    printf("ListLength(L)=%d \n", ListLength(L));  /* ListLength(L)=5 */
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n", i);  /* L是否空：i=0(1:是 0:否) */

    i = ClearList(&L);
    printf("清空L后：ListLength(L)=%d\n", ListLength(L));  /* 清空L后：ListLength(L)=0 */
    i = ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n", i);  /* L是否空：i=1(1:是 0:否) */

    for (j = 1; j <= 10; j++)
        ListInsert(&L, j, j);
    printf("在L的表尾依次插入1～10后：L.data=");  /* 在L的表尾依次插入1～10后：L.data=1 2 3 4 5 6 7 8 9 10 */
    ListTraverse(L);

    printf("ListLength(L)=%d \n", ListLength(L));  /* ListLength(L)=10 */

    ListInsert(&L, 1, 0);
    printf("在L的表头插入0后：L.data=");  /* 在L的表头插入0后：L.data=0 1 2 3 4 5 6 7 8 9 10 */
    ListTraverse(L);
    printf("ListLength(L)=%d \n", ListLength(L));  /* ListLength(L)=11 */

    GetElem(L, 5, &e);
    printf("第5个元素的值为：%d\n", e);  /* 第5个元素的值为：4 */
    for (j = 3; j <= 4; j++)
    {
        k = LocateElem(L, j);
        if (k)
            printf("第%d个元素的值为%d\n", k, j);  /* 第4个元素的值为3 第5个元素的值为4*/
        else
            printf("没有值为%d的元素\n", j);
    }

    k = ListLength(L); /* k为表长 */
    for (j = k + 1; j >= k; j--)
    {
        i = ListDelete(&L, j, &e); /* 删除第j个数据 */
        if (i == ERROR)
            printf("删除第%d个数据失败\n", j);  /* 删除第12个数据失败 */
        else
            printf("删除第%d个的元素值为：%d\n", j, e);  /* 删除第11个的元素值为：10 */
    }
    printf("依次输出L的元素：");  /* 依次输出L的元素：0 1 2 3 4 5 6 7 8 9 */
    ListTraverse(L);

    j = 5;
    ListDelete(&L, j, &e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n", j, e);  /* 删除第5个的元素值为：4 */

    printf("依次输出L的元素：");  /* 依次输出L的元素：0 1 2 3 5 6 7 8 9 */
    ListTraverse(L);

    i = ClearList(&L);
    printf("\n清空L后：ListLength(L)=%d\n", ListLength(L));  /* 清空L后：ListLength(L)=0 */
    CreateListHead(&L, 20);
    printf("整体创建L的元素(头插法)：");  /* 整体创建L的元素(头插法)：58 88 37 75 76 58 91 15 28 39 85 49 2 86 90 58 100 25 10 8 */
    ListTraverse(L);

    i = ClearList(&L);
    printf("\n删除L后：ListLength(L)=%d\n", ListLength(L));  /* 删除L后：ListLength(L)=0 */
    CreateListTail(&L, 20);
    printf("整体创建L的元素(尾插法)：");  /* 整体创建L的元素(尾插法)：8 10 25 100 58 90 86 2 49 85 39 28 15 91 58 76 75 37 88 58 */
    ListTraverse(L);

    return 0;
}
