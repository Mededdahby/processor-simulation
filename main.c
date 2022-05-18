#include <stdio.h>
#include <stdlib.h>
typedef struct
{
	int id;
	int ex_time;
	int a_time;
	int priority;
} element;
typedef struct process
{
	element pro;
	struct process *next;
} process;

typedef struct File
{
	process *head;
	process *tail;
	int size;
} File;
typedef struct File *file;
file ini_file()
{
	file temp;
	temp = (File *)malloc(sizeof(File));
	temp->head = NULL;
	temp->tail = NULL;
	temp->size = 0;
	return temp;
}

process *create_process(int id, int ex_time, int a_time, int prio)
{
	process *temp;
	temp = (process *)malloc(sizeof(process));
	temp->pro.id = id;
	temp->pro.ex_time = ex_time;
	temp->pro.a_time = a_time;
	temp->pro.priority = prio;
	//	scanf("%d %d %d %d",&temp->pro.id,&temp->pro.ex_time,&temp->pro.a_time,&temp->pro.priority);
	temp->next = NULL;
	return temp;
}
file push_file(process *pro, file head1)
{
	process *temp;
	if (head1->head == NULL)
	{
		head1->head = pro;
		head1->tail = pro;
		return head1;
	}
	else
	{
		temp = head1->head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = pro;
		head1->tail = pro;
	}
	return head1;
}
void affiche(file head1);
file SJF(file f)
{
	process *temp;
	element aux1;
	int n, i;
	n = f->size;
	if (f->size == 1)
	{
		printf("impossible trie\n");
	}

	while (n > 1)
	{
		temp = f->head;
		for (i = 0; i < n - 1; i++)
		{
			if (temp->pro.a_time >= temp->next->pro.a_time && temp->pro.ex_time > temp->next->pro.ex_time)
			{
				aux1 = temp->pro;
				temp->pro = temp->next->pro;
				temp->next->pro = aux1;
			}
			temp = temp->next;
		}
		n--;
	}

	return f;
}
file FIFO(file f)
{
	process *temp;
	element aux1;
	int n, i;
	n = f->size;
	if (f->size == 1)
	{
		printf("impossible trie\n");
	}

	while (n > 1)
	{
		temp = f->head;
		for (i = 0; i < n - 1; i++)
		{
			if (temp->pro.a_time > temp->next->pro.a_time)
			{
				aux1 = temp->pro;
				temp->pro = temp->next->pro;
				temp->next->pro = aux1;
			}
			temp = temp->next;
		}
		n--;
	}

	return f;
}
int total_execute_time(File f)
{
	File temp;
	int som = 0;
	temp = f;
	while (temp.head != NULL)
	{
		som += temp.head->pro.ex_time;
		temp.head = temp.head->next;
	}
	return som;
}

file SRTF(file f)
{
	int t, min, i, j;
	process *pro;
	process *k = NULL;
	file head;
	head = ini_file();
	process *temp;
	t = total_execute_time(*f);
	printf("t=%d", t);
	for (i = 0; i < t; i++)
	{
		min = 1000;
		temp = f->head;
		printf("\nthis is i : %d\n", i);
		for (j = 0; j < f->size; j++)
		{
			if ((temp->pro.a_time <= i) && (temp->pro.ex_time >= 0) && (temp->pro.ex_time < min))
			{
				min = temp->pro.ex_time;
				k = temp;
			}
			temp = temp->next;
		}
		if (k != NULL)
		{
			pro = NULL;
			pro = create_process(k->pro.id, k->pro.ex_time, k->pro.a_time, k->pro.priority);
			head = push_file(pro, head);
			k->pro.ex_time--;
		}
	}
	return head;
}
process *pop_file(file f)
{
	process *temp;
	if (f->head == NULL)
		exit(-1);
	temp = f->head;
	f->head = f->head->next;
	return temp;
}

void affiche(file head1)
{
	process *temp;
	temp = head1->head;
	while (temp != NULL)
	{
		printf("--id : %d\t---arrive_time : %d\t--execute_time : %d\t--priority : %d\n", temp->pro.id, temp->pro.a_time, temp->pro.ex_time, temp->pro.priority);
		temp = temp->next;
	}
}
void affiche_SRTF(file head1)
{
	process *temp;
	int i = 0;
	temp = head1->head;
	while (temp != NULL)
	{
		if (i == 0)
		{
			printf("instant T = %d\n", i);
			printf("id : %d\tarrive_time : %d\nexecute_time : %d\npriority : %d\n", temp->pro.id, temp->pro.a_time, temp->pro.ex_time, temp->pro.priority);
			temp = temp->next;
			i++;
		}
		else
		{
			printf("\tinstant T = %d\n", i);
			printf("\tid : %d\tarrive_time : %d\nexecute_time : %d\npriority : %d\n", temp->pro.id, temp->pro.a_time, temp->pro.ex_time, temp->pro.priority);
			temp = temp->next;
			i++;
		}
	}
}
int main()
{
	file temp;
	file head1 = NULL;
	process *pro;
	int n, i, a, b, c, d, e;
	head1 = ini_file();
	printf("donner votre methode que vous preferer : taper [1 : FIFO] / [2 : SJF] / [3 : SRTF]\n ");
	scanf("%d", &e);
	printf("\n---------votre donne est sous forme : [id - execute time - arrive time- priority]--------------------\n");
	printf("donner le nombre des processus : \t");
	scanf("%d", &head1->size);
	for (i = 0; i < head1->size; i++)
	{
		printf("donner id : ");
		scanf("%d", &a);
		printf("donner le temps d'execution :\t ");
		scanf("%d", &b);
		printf("donner le temps d'arrive: \t");
		scanf("%d", &c);
		printf("donner la priority : \t ");
		scanf("%d", &d);
		pro = create_process(a, b, c, d);
		head1 = push_file(pro, head1);
	}
	switch (e)
	{
	case 1:
		head1 = FIFO(head1);
		affiche(head1);
		break;
	case 2:
		head1 = SJF(head1);
		affiche(head1);
		break;
	case 3:
		head1 = SRTF(head1);
		affiche_SRTF(head1);
		break;
	}
}
