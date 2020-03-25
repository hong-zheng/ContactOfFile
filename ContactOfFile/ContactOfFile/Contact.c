#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
//// 个人信息用一个结构体来存储
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
//// 离开程序时就需要Save
//void Save(Contact* contact){
//	// 把通讯录中所有的数据都保存到文件当中
//	FILE* fp = fopen("G:\ContactOfFile/contact.txt","w");
//	if (NULL == fp){
//		perror("文件打开失败\n");
//		return;
//	}
//	for (int i = 0; i < contact->size;i++){
//		fwrite(&contact->people[i],sizeof(People),1,fp);
//	}
//	fclose(fp);
//	printf("保存成功\n");
//}
//
//// 初始化时就需要Load
//void Load(Contact* contact){
//	// 1、打开文件
//	FILE* fp = fopen("G:\ContactOfFile/contact.txt", "r");
//	if (NULL == fp){
//		perror("打开失败\n");
//		return;
//	}
//	// 2、循环读取文件中的内容，并把数据加载到通讯录结构体中
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
	printf("******** 0、exit       ********\n");
	printf("******** 1、Add        ********\n");
	printf("******** 2、Del        ********\n");
	printf("******** 3、Modify     ********\n");
	printf("******** 4、Find       ********\n");
	printf("******** 5、Display    ********\n");
	printf("******** 6、Clear      ********\n");
	printf("******** 7、SortOfName ********\n");
	printf("*******************************\n");
	printf("根据菜单做出你的选择:>\n");
	int choice = 0;
	scanf("%d",&choice);
	return choice;
}
void InitContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	contact->capacity = NUM;
	contact->size = 0;
	contact->persons = (PersonInfo*)malloc(sizeof(PersonInfo)*contact->capacity);
	printf("初始化完成!\n");
}
void AddContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	char name[1024];
	char sex[1024];
	int age;
	char phone[1024];
	char addr[1024];
	printf("输入姓名:>\n");
	scanf("%s",name);
	strcpy(contact->persons[contact->size].name,name);
	printf("输入性别:>\n");
	scanf("%s", sex);
	strcpy(contact->persons[contact->size].sex, sex);
	printf("输入年龄:>\n");
	scanf("%d", &age);
	contact->persons[contact->size].age = age;
	printf("输入电话:>\n");
	scanf("%s", phone);
	strcpy(contact->persons[contact->size].phone, phone);
	printf("输入地址:>\n");
	scanf("%s", addr);
	strcpy(contact->persons[contact->size].addr,addr);
	contact->size++;
	printf("添加成功!\n");
}
void Move_pos(Contact* contact,int pos){
	if (NULL == contact){
		perror("该地址为空\n");
		return;
	}
	contact->persons[pos] = contact->persons[contact->size-1];
	contact->size--;
}
void DelContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	int id = 0;
	while (1){
		printf("输入需要删除的对象:>\n");
		scanf("%d", &id);
		if (id >= contact->size || id < 0){
			continue;
		}
		break;
	}
	Move_pos(contact,id);
	printf("删除成功\n");
}
// 根据序号修改具体内容
void ModifyContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	printf("输入需要修改联系人的序号:>\n");
	int id = 0;
	scanf("%d", &id);
	void Print_person(PersonInfo* person, int i);
	Print_person(&contact->persons[id],0);
	char name[1024];
	char sex[1024];
	int age;
	char phone[1024];
	char addr[1024];
	printf("输入修改姓名:>\n");
	scanf("%s", name);
	strcpy(contact->persons[id].name, name);
	printf("输入修改性别:>\n");
	scanf("%s", sex);
	strcpy(contact->persons[id].sex, sex);
	printf("输入修改年龄:>\n");
	scanf("%d", &age);
	contact->persons[id].age = age;
	printf("输入修改电话:>\n");
	scanf("%s", phone);
	strcpy(contact->persons[id].phone, phone);
	printf("输入修改地址:>\n");
	scanf("%s", addr);
	strcpy(contact->persons[id].addr, addr);
	contact->size++;
	printf("修改成功!\n");
}
void Print_person(PersonInfo* person,int i){
	if (NULL == person){
		perror("无该联系人\n");
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
		perror("未找到该通讯录！\n");
		return;
	}
	printf("输入需要寻找的姓名:>\n");
	char name[1024] = { 0 };
	scanf("%s",name);
	int count = 0;
	printf("查找结果如下:>\n");
	for (int i = 0; i < contact->size;i++){
		if (0 == strcmp(contact->persons[i].name,name)){
			Print_person(&contact->persons[i],count++);
		}
	}
	printf("寻找完毕\n");
}
void DisplayContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	if (0 == contact->size){
		printf("通讯录为空\n");
		return;
	}
	void printContact(Contact* contact);
	printContact(contact);
}
void ClearContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	contact->size = 0;
	free(contact->persons);
	printf("所有的联系人已删除!\n");
}
void Swap_person(PersonInfo* person1, PersonInfo* person2){
	PersonInfo tmp = *person1;
	*person1 = *person2;
	*person2 = tmp;
}
void Bubble_person(Contact* contact){
	if (NULL ==  contact){
		perror("无该通讯录\n");
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
		perror("未找到该通讯录！\n");
		return;
	}
	Bubble_person(contact);
}

// 将文件中的数据加载到通讯录中
void LoadContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
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
		// 如果容量不够就扩容
		if (contact->size >= contact->capacity){
			ReallocContact(contact);
		}
		contact->persons[contact->size++] = person;
	}
	fclose(fp);
	printf("加载到通讯录完毕\n");
}
// 保存至文件中将通讯录数据
void SaveContact(Contact* contact){
	if (NULL == contact){
		perror("未找到该通讯录！\n");
		return;
	}
	FILE* fp = fopen("G:\\ContactOfFile/contact.txt", "w");
	for (int i = 0; i < contact->size;i++){
		fwrite(&contact->persons[i],sizeof(PersonInfo),1,fp);
	}
	fclose(fp);
	printf("保存完毕\n");
}
// 扩容
void ReallocContact(Contact* contact){
	if (NULL == contact){
		perror("无该通讯录\n");
		return;
	}
	contact->capacity += NUM;
	PersonInfo*  curPeople=(PersonInfo*)malloc(sizeof(PersonInfo)*contact->capacity);
	if (NULL == curPeople){
		perror("申请空间失败\n");
		return;
	}
	memcpy(curPeople,contact->persons,sizeof(PersonInfo)*contact->size);
	contact->persons = curPeople;
}
void printContact(Contact* contact){
	if (NULL == contact){
		perror("地址无\n");
		return;
	}
	printf("编号\t姓名\t性别\t年龄\t电话\t\t地址\n");
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
			printf("通讯录中的所有联系人已保存!\n");
			printf("退出\n");
			break;
		}else{
			printf("输入有误，请重新输入\n");
			continue;
		}
	}
	system("pause");
	return 0;
}