#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//change
/*structure for creating 3 Objects containing Name & Key*/
typedef struct item
{
	int key;     // Used for checking is_safe condition
    char name[10];    // contain Item name
}ITEM;
ITEM item_[4];        // created 4 structures for goat, fox, salad & boat

typedef struct que
{
	ITEM dat;
	struct que *next;
}NODE;

typedef struct QUEUE
{
	NODE *Qfront;
	NODE *Qrear;
}QUEUE;


/*Initializing the QUEUE & setting pointers to Null*/
void initQUEUE(QUEUE *s)
{
	s->Qfront = s->Qrear = NULL;
}

/*function for inserting Item at the last in the QUEUE*/
void enqueue(QUEUE *t, ITEM DataIn)
{
	NODE *pNew = (NODE*)malloc(sizeof(NODE)), *pPre;
	pNew->dat = DataIn;
	pNew->next = NULL;
	if(t->Qfront == NULL)
	{
		t->Qfront = t->Qrear = pNew;
	}
	else
	{
		pPre = t->Qrear;
		pNew->next = pPre->next;
        pPre->next = pNew;
		t->Qrear = pNew;
	}
}

//function for removing first Item from the QUEUE & return item
ITEM dequeue(QUEUE *t)
{
	ITEM temp;
	NODE *pDlt;
	pDlt = t->Qfront;
	t->Qfront = pDlt->next;
	temp = pDlt->dat;
	if(t->Qfront == NULL)
	{
		return temp;
	}
	else
	{
		free(pDlt);
		return temp;
	}
}

ITEM queuefront(QUEUE *t)
{
	NODE *a=t->Qfront;
	ITEM temp = a->dat;
	return temp;
}
//function to display contents of QUEUE
void display(QUEUE *t)
{
	NODE *temp = t->Qfront;
	while(temp!=NULL)
	{
		printf("%s\t",temp->dat.name);
		temp=temp->next;
	}
}

int count(QUEUE *t)
{
	NODE *a = t->Qfront;
	int counter = 0;
	while(a!=NULL)
	{
		counter++;
		a=a->next;
	}
	return counter;
}

int issafe(QUEUE *t)
{
	NODE *a = t->Qfront, *b;
	if(count(t)==0 || count(t)==1)
		return 1;
	else
	{
		b=a->next;
		if(a->dat.key == b->dat.key)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

QUEUE *sr, *dest;

void recursive(QUEUE *source, QUEUE *destination, ITEM boat)
{
	int fg = 0;
	if(sr==source&&source->Qfront==NULL)
	{
		enqueue(dest,boat);
		fg = 1;
		goto xy;
		km:
            printf("\n\nAll items are on the Bank B of the river\n\n");
            display(destination);
            display(source);
            return;
	}
	else
	{
		enqueue(destination, boat);
		xy:
		if(dest == destination)
		{
		    printf("\n\nItem moved to Bank B : %s\nSTATUS :\t",boat.name);
		    printf("\nBANK A : \t");
		    display(source);
		    printf("\nBANK B :\t");
		    display(destination);
		}
		else
		{
            printf("\n\nItem moved to Bank A : %s\nSTATUS :\t",boat.name);
		    printf("\nBANK A : \t");
		    display(destination);
		    printf("\nBANK B :\t");
		    display(source);
		}
		if(fg==1)
		{
			goto km;
		}
		if(issafe(destination))
		{
			boat = dequeue(source);
			recursive(source,destination,boat);
		}
		else
		{

			boat = dequeue(destination);

			recursive(destination,source,boat);
		}
	}
}

void crossriv()
{
	QUEUE A, B;
	sr = &A; dest = &B;
	NODE *a = A.Qfront, *b = B.Qfront;
	int i=0;
	initQUEUE(&A);
	initQUEUE(&B);
	printf("All items are on the Bank A of the river\n\n");
	for(;i<3;i++)
	{
		enqueue(&A, item_[i]);
	}
	display(&A);
	printf("\n\n");
	while(1)
	{
		item_[3] = dequeue(&A);
		if(issafe(&A)==1)
		{
			recursive(&A,&B,item_[3]);
			break;
		}
		else
		{
			enqueue(&A,item_[3]);
		}
	}
}
void init()
{
	int i=0;
	item_[0].key = item_[1].key = 1;
	item_[2].key = 0;
	strcpy(item_[0].name, "Wolf");
	strcpy(item_[1].name, "Salad");
	strcpy(item_[2].name, "Goat");
	printf("All of the ITEMS are about to cross the river\n");
	crossriv();
}
void main()
{
	init();
	return;
}



