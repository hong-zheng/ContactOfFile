#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
//// ������Ϣ��һ���ṹ�����洢
//typedef struct People{
//	char name[1024];
//	char sex[1024];
//	int age;
//	char phone[1024];
//	char addr[1024];
//}People;
//typedef struct Contact{
//	People* people;
//	int size;
//	int capacity;
//}Contact;
//
//// �뿪����ʱ����ҪSave
//void Save(Contact* contact){
//	// ��ͨѶ¼�����е����ݶ����浽�ļ�����
//	FILE* fp = fopen("G:\ContactOfFile/contact.txt","w");
//	if (NULL == fp){
//		perror("�ļ���ʧ��\n");
//		return;
//	}
//	for (int i = 0; i < contact->size;i++){
//		fwrite(&contact->people[i],sizeof(People),1,fp);
//	}
//	fclose(fp);
//	printf("����ɹ�\n");
//}
//
//// ��ʼ��ʱ����ҪLoad
//void Load(Contact* contact){
//	// 1�����ļ�
//	FILE* fp = fopen("G:\ContactOfFile/contact.txt", "r");
//	if (NULL == fp){
//		perror("��ʧ��\n");
//		return;
//	}
//	// 2��ѭ����ȡ�ļ��е����ݣ��������ݼ��ص�ͨѶ¼�ṹ����
//	People tmp = { 0 };
//	while (1){
//		int n = fread(&tmp,sizeof(People),1,fp);
//		if (n < 1){
//			break;
//		}
//		//if (contact->size >= contact->capacity){
//		//	ReallocPeople(contact);
//		//}
//		contact->people[contact->size] = tmp;
//		contact->size++;
//	}
//}

#define NUM 4
typedef struct PersonInfo{
		char name[1024];
		char sex[1024];
		int age;
		char phone[1024];
		char addr[1024];
}PersonInfo;
typedef struct Contact{
	PersonInfo* persons;
	int size;
	int capacity;
}Contact;
int menu(){
	printf("*******************************\n");
	printf("******** 0��exit       ********\n");
	printf("******** 1��Add        ********\n");
	printf("******** 2��Del        ********\n");
	printf("******** 3��Modify     ********\n");
	printf("******** 4��Find       ********\n");
	printf("******** 5��Display    ********\n");
	printf("******** 6��Clear      ********\n");
	printf("******** 7��SortOfName ********\n");
	printf("*******************************\n");
	printf("���ݲ˵��������ѡ��:>\n");
	int choice = 0;
	scanf("%d",&choice);
	return choice;
}
void InitContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	contact->capacity = NUM;
	contact->size = 0;
	contact->persons = (PersonInfo*)malloc(sizeof(PersonInfo)*contact->capacity);
	printf("��ʼ�����!\n");
}
void AddContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	char name[1024];
	char sex[1024];
	int age;
	char phone[1024];
	char addr[1024];
	printf("��������:>\n");
	scanf("%s",name);
	strcpy(contact->persons[contact->size].name,name);
	printf("�����Ա�:>\n");
	scanf("%s", sex);
	strcpy(contact->persons[contact->size].sex, sex);
	printf("��������:>\n");
	scanf("%d", &age);
	contact->persons[contact->size].age = age;
	printf("����绰:>\n");
	scanf("%s", phone);
	strcpy(contact->persons[contact->size].phone, phone);
	printf("�����ַ:>\n");
	scanf("%s", addr);
	strcpy(contact->persons[contact->size].addr,addr);
	contact->size++;
	printf("��ӳɹ�!\n");
}
void Move_pos(Contact* contact,int pos){
	if (NULL == contact){
		perror("�õ�ַΪ��\n");
		return;
	}
	contact->persons[pos] = contact->persons[contact->size-1];
	contact->size--;
}
void DelContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	int id = 0;
	while (1){
		printf("������Ҫɾ���Ķ���:>\n");
		scanf("%d", &id);
		if (id >= contact->size || id < 0){
			continue;
		}
		break;
	}
	Move_pos(contact,id);
	printf("ɾ���ɹ�\n");
}
// ��������޸ľ�������
void ModifyContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	printf("������Ҫ�޸���ϵ�˵����:>\n");
	int id = 0;
	scanf("%d", &id);
	void Print_person(PersonInfo* person, int i);
	Print_person(&contact->persons[id],0);
	char name[1024];
	char sex[1024];
	int age;
	char phone[1024];
	char addr[1024];
	printf("�����޸�����:>\n");
	scanf("%s", name);
	strcpy(contact->persons[id].name, name);
	printf("�����޸��Ա�:>\n");
	scanf("%s", sex);
	strcpy(contact->persons[id].sex, sex);
	printf("�����޸�����:>\n");
	scanf("%d", &age);
	contact->persons[id].age = age;
	printf("�����޸ĵ绰:>\n");
	scanf("%s", phone);
	strcpy(contact->persons[id].phone, phone);
	printf("�����޸ĵ�ַ:>\n");
	scanf("%s", addr);
	strcpy(contact->persons[id].addr, addr);
	contact->size++;
	printf("�޸ĳɹ�!\n");
}
void Print_person(PersonInfo* person,int i){
	if (NULL == person){
		perror("�޸���ϵ��\n");
		return;
	}
	printf("[%d]\t%s\t%s\t%d\t%s\t\t%s\n"
		, i
		, person->name
		, person->sex
		, person->age
		, person->phone
		, person->addr);
}
void FindContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	printf("������ҪѰ�ҵ�����:>\n");
	char name[1024] = { 0 };
	scanf("%s",name);
	int count = 0;
	printf("���ҽ������:>\n");
	for (int i = 0; i < contact->size;i++){
		if (0 == strcmp(contact->persons[i].name,name)){
			Print_person(&contact->persons[i],count++);
		}
	}
	printf("Ѱ�����\n");
}
void DisplayContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	if (0 == contact->size){
		printf("ͨѶ¼Ϊ��\n");
		return;
	}
	void printContact(Contact* contact);
	printContact(contact);
}
void ClearContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	contact->size = 0;
	free(contact->persons);
	printf("���е���ϵ����ɾ��!\n");
}
void Swap_person(PersonInfo* person1, PersonInfo* person2){
	PersonInfo tmp = *person1;
	*person1 = *person2;
	*person2 = tmp;
}
void Bubble_person(Contact* contact){
	if (NULL ==  contact){
		perror("�޸�ͨѶ¼\n");
		return;
	}
	for (int i = 0; i < contact->size - 1;i++){
		for (int j = 0; j < contact->size - i - 1;j++){
			if (strcmp(&contact->persons[j + 1], &contact->persons[j]) < 0){
				Swap_person(&contact->persons[j + 1], &contact->persons[j]);
			}
		}
	}
}
void SortOfNameContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	Bubble_person(contact);
}

// ���ļ��е����ݼ��ص�ͨѶ¼��
void LoadContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	void ReallocContact(Contact* contact);
	FILE* fp = fopen("G:\\ContactOfFile/contact.txt", "r");
	PersonInfo person = { 0 };
	while (1){
		int n = fread(&person, sizeof(PersonInfo), 1, fp);
		if (n < 1){
			break;
		}
		// �����������������
		if (contact->size >= contact->capacity){
			ReallocContact(contact);
		}
		contact->persons[contact->size++] = person;
	}
	fclose(fp);
	printf("���ص�ͨѶ¼���\n");
}
// �������ļ��н�ͨѶ¼����
void SaveContact(Contact* contact){
	if (NULL == contact){
		perror("δ�ҵ���ͨѶ¼��\n");
		return;
	}
	FILE* fp = fopen("G:\\ContactOfFile/contact.txt", "w");
	for (int i = 0; i < contact->size;i++){
		fwrite(&contact->persons[i],sizeof(PersonInfo),1,fp);
	}
	fclose(fp);
	printf("�������\n");
}
// ����
void ReallocContact(Contact* contact){
	if (NULL == contact){
		perror("�޸�ͨѶ¼\n");
		return;
	}
	contact->capacity += NUM;
	PersonInfo*  curPeople=(PersonInfo*)malloc(sizeof(PersonInfo)*contact->capacity);
	if (NULL == curPeople){
		perror("����ռ�ʧ��\n");
		return;
	}
	memcpy(curPeople,contact->persons,sizeof(PersonInfo)*contact->size);
	contact->persons = curPeople;
}
void printContact(Contact* contact){
	if (NULL == contact){
		perror("��ַ��\n");
		return;
	}
	printf("���\t����\t�Ա�\t����\t�绰\t\t��ַ\n");
	for (int i = 0; i < contact->size;i++){
		Print_person(&contact->persons[i],i);
	}
}
int main(){
	Contact contact;
	InitContact(&contact);
	LoadContact(&contact);
	typedef void(*Func)(Contact* contact);
	Func func[] = {
		NULL,
		AddContact,
		DelContact,
		ModifyContact,
		FindContact,
		DisplayContact,
		ClearContact,
		SortOfNameContact
	};
	while (1){
		int choice = menu();
		if (choice > 0 && choice < 8){
			func[choice](&contact);
		}else if(0 == choice){
			SaveContact(&contact);
			printf("ͨѶ¼�е�������ϵ���ѱ���!\n");
			printf("�˳�\n");
			break;
		}else{
			printf("������������������\n");
			continue;
		}
	}
	system("pause");
	return 0;
}