#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
typedef int ElemType;
typedef struct person {
	char num[10];//��� 
	char name[10];//���� 
	char sex[10];//�Ա� 
	char phone[10];//�绰 
}personal;/*={};����*/
typedef struct node
{
	person data;//������ 
	struct node* next;//ָ���� 
}ListNode, * LinkList;
LinkList InitList();
LinkList Create(LinkList head);
void List(LinkList head);//��ʾ���м�¼ 
void save(LinkList head);//���浽�ļ� 
void Find(LinkList head);//��Ҫ����� 
int GetLength(LinkList head);//�ܼ�¼���� 
void Add(LinkList head);//�����µļ�¼ 
void Alter(LinkList head);//�޸� 
void Delete(LinkList head); //ɾ�� 
void Statis_sex(LinkList head);//�Ա���� 
void Quit();//�˳�ѡ�� 
void Menu(LinkList head);//ѡ��
//Creatģ����ͨ����ȡ�ļ���Ϣʵ�� 
LinkList InitList()
{
	LinkList head = (LinkList)malloc(sizeof(ListNode));//����ͷ���
	if (head == NULL)
	{
		printf("�ռ������Ч!");
		exit(-1);//�˳�����
	}
	head->next = NULL;
	return head;
}
LinkList Create(LinkList head)
{
	person LM;//�����ļ����� 
	LinkList rear;
	rear = head;
	FILE* fp = fopen("file.txt", "r");
	if (fp == NULL)
	{
		printf("���ļ�ʧ��!");
		return NULL;
	}

	while (fscanf(fp, "%s%s%s%s", LM.num, LM.name, LM.sex, LM.phone) != EOF)//�������ļ�β 
	{
		LinkList s = (LinkList)malloc(sizeof(ListNode));
		s->data = LM;
		s->next = NULL;
		rear->next = s;
		rear = s;
	}
	fclose(fp);
	return head;
}
void List(LinkList head) {
	LinkList p;
	p = head->next;
	if (!p) //���headָ��Ϊ��˵������Ϊ��
	{
		printf("\n����Ϊ�գ�\n\n");
	}
	else
	{
		printf("\nͨ��¼��\n\n");
		printf("���	����	�Ա�	�绰 \n");
		while (p)  //ѭ���������ڵ�ֵ���
		{
			printf("%s\t%s\t%s\t%s\n", p->data.num, p->data.name, p->data.sex, p->data.phone);//��ӡ
			p = p->next;//�˾���ڴ�ӡ���棬��ֹ����Ұָ�� 
		}
		Statis_sex(head);
		printf("\n�������˵�\n");
		system("pause");//ҳ��ͣ��
		Menu(head);
	}
}
void save(LinkList head)
{
	LinkList rear;
	person LM;
	rear = head->next;//����ͷ�ڵ� 
	FILE* fp;
	int i;
	if ((fp = fopen("file.txt", "wb")) == NULL)/*ֻ�򿪻���һ���������ļ���ֻ����д����*/
	{
		printf("\n�ļ�������!\n");
	}
	while (rear)//�������ļ�β 
	{
		LM = rear->data;
		fprintf(fp, "%s\t%s\t%s\t%s\n", LM.num, LM.name, LM.sex, LM.phone);
		rear = rear->next;
	}
	fclose(fp);
}
void Find(LinkList head)
{
	int Loop = 0;
	char name[10];
	printf("������Ҫ��ѯ��ϵ�˵�����[     ]\b\b\b\b\b\b");
	scanf("%s", name);
	LinkList rear = head->next;
	while (rear)
	{
		if (strcmp(rear->data.name, name) == 0)
		{
			printf("���	����	�Ա�	�绰 \n");
			printf("%s\t%s\t%s\t%s\n", rear->data.num, rear->data.name, rear->data.sex, rear->data.phone);
			Loop = 1;
		}
		rear = rear->next;
	}
	if (Loop == 1)
	{
		printf("\n��ѯ��ϵ�˳ɹ�!���ز˵�\n");
		system("pause");
		Menu(head);
	}
	else
	{
		int n;
		printf("�޴���ϵ��!!!\n\n���ز˵�(1) or ��������(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Find(head); break;
		}
	}
}
int GetLength(LinkList head)
{
	LinkList p = head->next;
	int i = 0;
	while (p)
	{
		i++;
		p = p->next;

	}
	return i;
}//��ȡ�������� 
void Add(LinkList head)
{
	char c;
	person LM;
	LinkList p = head;
	printf("�������½���ϵ�˵���Ϣ\n\n���	/����	/�Ա�	/�绰���룺\n");
	do
	{
		scanf("%s", LM.num);
		scanf("%s", LM.name);
		scanf("%s", LM.sex);
		scanf("%s", LM.phone);
		LinkList s = (LinkList)malloc(sizeof(ListNode));
		s->data = LM;
		s->next = NULL;
		while (p->next)
		{
			p = p->next;
		}
		p->next = s;
		save(head);
		printf("�Ƿ�������� y/n\n");
		scanf(" %c", &c);
	} while (c == 'y' || c == 'Y');
	printf("\n�������˵�\n");
	system("pause");
	Menu(head);
}
void Alter(LinkList head)
{
	int loop = 0;
	int n;
	char name[10];
	printf("������Ҫ��ѯ��ϵ�˵����� [     ]\b\b\b\b\b\b");
	scanf("%s", name);
	printf("\n");
	LinkList rear = head->next;
	while (rear)
	{
		if (strcmp(rear->data.name, name) == 0)
		{
			printf("������Ҫ�޸ĵ�����:(1)��� (2)���� (3)�Ա� (4)�绰���� (5)ȫ����Ϣ [ ]\b\b");//printf("%s\t%s\t%s\t%s\n",rear->data.num,rear->data.name,rear->data.sex,rear->data.phone);
			scanf("%d", &n);
			printf("\n");
			switch (n)
			{
			case 1: printf("�������޸ĺ�ı�ţ�"); scanf("%s", rear->data.num); break;
			case 2: printf("�������޸ĺ��������"); scanf("%s", rear->data.name); break;
			case 3: printf("�������޸ĺ���Ա�"); scanf("%s", rear->data.sex); break;
			case 4: printf("�������޸ĺ�ĵ绰����"); scanf("%s", rear->data.phone); break;
			case 5: printf("������Ҫ�޸���ϵ�˵���Ϣ: \n\n���	����	�Ա�	�绰���룺\n");
				scanf("%s", rear->data.num);
				scanf("%s", rear->data.name);
				scanf("%s", rear->data.sex);
				scanf("%s", rear->data.phone); break;
			}
			system("cls");
			loop = 1;
		}
		rear = rear->next;
	}
	if (loop == 0)
	{
		printf("�޴���ϵ��!!!\n\n���ز˵�(1) or ��������(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Alter(head); break;
		}
	}
	save(head);
	printf("\n�޸ĳɹ�!���ز˵�\n");
	system("pause");
	Menu(head);
}
void Delete(LinkList head)
{
	LinkList rear = head;//������Ҫɾ���ڵ��ǰһ�ڵ� 
	LinkList p = rear->next;//������Ҫɾ���ڵ�
	char name[10];
	int Loop = 0, n;
	printf("������Ҫɾ����ϵ�˵�����:[    ]\b\b\b\b\b");
	scanf("%s", name);
	printf("\n");
	while (p)
	{
		if (strcmp(p->data.name, name) == 0)
		{
			rear->next = p->next;
			free(p);
			save(head);
			Loop = 1;
		}
		rear = p;
		p = p->next;
	}
	if (Loop == 1)
	{
		printf("\nɾ����ϵ�˳ɹ�!���ز˵�\n");
		system("pause");
		Menu(head);
	}
	else
	{
		printf("�޴���ϵ��!!!\n\n���ز˵�(1) or ��������(2)[  ]\b\b\b");
		scanf("%d", &n);
		printf("\n");
		switch (n)
		{
		case 1:system("cls"); Menu(head); break;
		case 2:system("cls"); Delete(head); break;
		}
	}
}
void Statis_sex(LinkList head)
{
	int i = 0;//��¼������Ŀ 
	int j = GetLength(head);//��ȡ�ܼ�¼�� 
	LinkList rear = head->next;
	char sex[10] = "man";
	while (rear)
	{
		if (strcmp(rear->data.sex, sex) == 0)
			i++;
		rear = rear->next;
	}
	printf("\nͨ��¼�������� %d �ˣ���Ů�� %d �ˡ�\n", i, j - i);
}
void Quit()
{
	printf("\n\t                         �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� �� ��\n\n");
	puts("\n");
	puts("\t                             ��                                               ��");
	puts("\t                             ��                                               ��");
	puts("\t                             ��     ��л����ͨ��¼����ϵͳ!��ӭ�´�����!      ��");
	puts("\t                             ��                                               ��");
	puts("\t                             ��                                               ��");
	puts("\t                             ��                  �����ˣ�׷���λ�                ��");
	puts("\t                             ��                          2020.7.3             �� ");
	puts("\n ");

}
void Menu(LinkList head)
{
	int n;
	int choice = 0;
	do
	{
		system("cls");
		printf("\n");
		printf("                                              ---ͨѶ¼����ϵͳ---\n");
		puts("\n");
		printf("                                             1/��������ѯ��ϵ����Ϣ\n");
		puts("\n");
		printf("                                             2/  �½���ϵ��\n");
		puts("\n");
		printf("                                             3/�޸���ϵ����Ϣ\n");
		puts("\n");
		printf("                                             4/ ɾ����ϵ����Ϣ\n");
		puts("\n");
		printf("                                             5/��ʾ������ϵ����Ϣ\n");
		puts("\n");
		printf("                                             6/     �˳�\n");
		puts("\n");
		printf("                                          ��ѡ���������(1-6) : [ ]\b\b");
		scanf("%d", &n);
		if (n < 1 || n>6)
		{
			system("cls");
			printf("ѡ�����!  ������ѡ��!\n");
			system("pause");
			choice = 1;
		}
		else
		{
			break;
		}
	} while (choice == 1);

	switch (n)
	{
	case 1:system("cls"); Find(head); break;//Find������ѯ 
	case 2:system("cls"); Add(head); break;//Add�����½���ϵ�� 
	case 3:system("cls"); Alter(head); break;//Alter�޸���ϵ����Ϣ 
	case 4:system("cls"); Delete(head); break;//Deleteɾ����ϵ����Ϣ 
	case 5:system("cls"); List(head); break;//List��ʾ������Ϣ 
	case 6:system("cls"); Quit(); break;//�˳� 
	}
}
int main()
{
	LinkList head = InitList();
	head = Create(head);
	printf("\n��Ϣ¼��ɹ���");
	system("pause");
	Menu(head);
}
