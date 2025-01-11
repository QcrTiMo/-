#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


/*PIMS=Personal Information Managerment System(个人信息管理体系)*/


typedef struct PIMS      /*定义了PIMS结构体用来保存联系人基本信息*/
{
    char name[50];
    char sex[10];
    char address[100];
    char phone[20];
    struct PIMS *next;
}PIMS;


typedef struct login      /*定义了login结构体用来保存用户的账号信息*/
{
	char zhanghao[50];
	char mima[50];
	struct login *next;
}login;


PIMS *head = NULL;        /*定义链表头节点，为后面的文件操作做准备*/
login *headpro = NULL;


void login1();
void addPIMS();
void deletePIMS();
void modifyPIMS();
void findPIMS();           /*主函数、功能函数定义*/
void displayPIMS();
void savePIMS();
void loadPIMS();
void freePIMS();
void savelogin();
void loadlogin();
void freelogin();

/*主函数*/
int main() 
{
    loadPIMS();       /*在开始程序开头重新加载并读取文件内容*/
    loadlogin();
    login1();         /*在进入菜单前让用户进行注册账号、登录操作，具有一定安全性*/
    int choice;
    do 
	{
        printf("———————— 通讯录管理系统 ————————\n");
        printf("——             1. 添加联系人              —— \n");
        printf("——             2. 删除联系人              —— \n");
        printf("——             3. 修改联系人              —— \n");    /*菜单样式*/
        printf("——             4. 查找联系人              —— \n");
        printf("——             5. 显示所有联系人          —— \n");
        printf("——             0. 退出系统                —— \n");
        printf("————————————————————————\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        switch (choice)        /*菜单功能选择，输入不同数字，前往运行不同的功能函数*/
		{
            case 1:
                addPIMS();       
                break;
            case 2:
                deletePIMS();
                break;
            case 3:
                modifyPIMS();
                break;
            case 4:
                findPIMS();
                break;
            case 5:
                displayPIMS();
                break;
            case 0:
                savePIMS();       /*结束程序前对文件进行保存并释放无用内存，保证文件和程序的正常运行*/
                freePIMS();
                savelogin();
                freelogin();
                printf("感谢使用！\n");
                Sleep(3000);
                break;
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }while (choice != 0);
    return 0;
}

/*登录函数模块*/
void login1()
{
	char search_zh[50];    /*定义了账号密码等数组，用来储存账号等数据*/
	char search_mm[50];
	char zhanghao[50];
	char mima[50];
    login *newlogin = (login *)malloc(sizeof(login));   /*为接下来的数据存储分配内存*/
    if(newlogin==NULL)
    {
		printf("内存分配失败!\n");
		return;
	}
	if(headpro==NULL)    /*如果文件是空的或者没有文件，则会提示创建账号密码*/
	{
		printf("欢迎使用由QcrTiMo开发的通讯录管理系统！\n");
		printf("\n");
		Sleep(1000);
		printf("检测到你还未拥有账号,请注册后再使用管理系统\n");
		printf("\n");
		Sleep(1000);
		printf("注册你的账号:\n");
	reloginzczh:scanf("%s",newlogin->zhanghao);     /*将账号数据存储到数组中*/
		login *current = headpro;	
		while(current!=NULL)
		{
			if(strcmp(current->zhanghao,zhanghao)==0)
			{
				printf("账号已存在！请重新输入注册你的账号:\n");
				goto reloginzczh;
			}
			current = current->next;
		}
		printf("注册输入你的密码:\n");
	reloginzcmm:scanf("%s",newlogin->mima);
		while(current!=NULL)
		{
			if(strcmp(current->mima,mima)==0)
			{
				printf("密码已存在！请重新注册输入你的密码:\n");
				goto reloginzcmm;
			}
			current = current->next;
		}		
		newlogin->next = NULL;           /*将newlogin指针定义到下一个节点，为接下来的读取做准备*/
		if(headpro==NULL)
		{
			headpro=newlogin;
		}
		else
		{
			login *temp = headpro;
			while(temp->next != NULL)      /*定义临时指针，更新指针状态，将数组的数据写入到文件中*/
			{
				temp = temp->next;
			}
			temp->next = newlogin;
		}
		savelogin();            /*实时保存更新文件，避免用户直接叉掉程序而没有保存数据*/
		printf("账号添加成功！欢迎使用通讯录管理系统！\n");
		printf("\n");
		Sleep(1000);
	}
	else              /*如果文件不为空，也就是用户之前已经注册了有账号，则进入登录阶段*/
	{
		printf("欢迎使用由QcrTiMo开发的通讯录管理系统！\n");
		printf("\n");
		Sleep(1000);
		printf("检测到你拥有账号，请使用账号密码登录管理系统\n");
		printf("\n");
		Sleep(1000);
		printf("输入你的账号:\n");
	reloginzh:scanf("%s",search_zh);
		login *current = headpro;
		int found = 0;
		while(current != NULL)
		{
			if(strcmp(current->zhanghao,search_zh)==0)        /*遍历文件，查找与用户输入相同的数据，如果没有则返回错误*/
			{
				printf("输入你的密码:\n");
			reloginmm:scanf("%s",search_mm);
				login *current = headpro;
				int foundmm = 0;
				while(current != NULL)
				{
					if(strcmp(current->mima,search_mm)==0)
					{
						printf("登录成功！欢迎使用通讯录管理系统！\n");
						printf("\n");
						Sleep(1000);
						return;
					}
					current = current->next;
				}
				if(!foundmm)
				{
					printf("密码错误！请重新输入!\n");
					printf("输入你的密码:\n");
					goto reloginmm;
				}
			}
			current = current->next;
		}
		if(!found)
		{
			printf("账号输入错误或没有此账号！请重试!\n");
			printf("输入你的账号:\n");
			goto reloginzh;                     /*使用goto，虽然跳来跳去很烦，但是至少能避免if循环过多，能起到基本的作用*/
		}
	}

}

/*添加联系人模块*/
void addPIMS() 
{
    PIMS *newPIMS = (PIMS *)malloc(sizeof(PIMS));
    if (newPIMS == NULL) 
	{
        printf("内存分配失败！\n");
        return;
    }
    printf("请输入姓名: ");
    scanf("%s", newPIMS->name);     /*将用户输入的字符串通过指针保存到结构体当中储存*/
    printf("请输入性别: ");
    scanf("%s", newPIMS->sex);
    printf("请输入地址: ");
    scanf("%s", newPIMS->address);
    printf("请输入电话: ");
    scanf("%s", newPIMS->phone);
    newPIMS->next = NULL;
    if (head == NULL) 
	{
        head = newPIMS;
    } 
	else 
	{
        PIMS *temp = head;
        while (temp->next != NULL) 
		{
            temp = temp->next;
        }
        temp->next = newPIMS;
    }
    savePIMS();
    printf("联系人添加成功！\n");
}

/*删除联系人模块*/
void deletePIMS() 
{
    char name[50];
    printf("请输入要删除的联系人姓名: ");
    scanf("%s", name);
    if (head == NULL) 
	{
        printf("通讯录为空！\n");
        return;
    }
    PIMS *current = head;     /*定义current指针用来遍历文件*/
    PIMS *previous = NULL;    /*定义previous指针用来后续删除工作*/
    while (current != NULL) 
	{
        if (strcmp(current->name, name) == 0) 
		{
            if (previous == NULL) 
			{
                head = current->next;     /*两种删除情况，将指针更新到要删除节点的下一个节点，跳过该节点*/
            } 
			else 
			{
                previous->next = current->next;
            }
            free(current);
            printf("联系人删除成功！\n");
            return;
        }
        previous = current;
        current = current->next;    /*定义current指针到下一个节点，为下次工作做准备*/
    }
    printf("未找到该联系人！\n");
}

/*修改联系人模块*/
void modifyPIMS() 
{
    char name[50];
    printf("请输入要修改的联系人姓名: ");
    scanf("%s", name);

    PIMS *current = head;
    while (current != NULL) 
	{
        if (strcmp(current->name, name) == 0)   /*遍历文件，搜索与用户输入的name相同的数据，此时搜到的就是用户要修改的联系人数据*/
		{
            printf("请输入新的姓名: ");    /*捕捉用户输入的数据，然后存放到current指针指向的结构体中*/
            scanf("%s", current->name);
            printf("请输入新的性别: ");
            scanf("%s", current->sex);
            printf("请输入新的地址: ");
            scanf("%s", current->address);
            printf("请输入新的电话: ");
            scanf("%s", current->phone);
            printf("联系人修改成功！\n");
            return;
        }
        current = current->next;
    }
    printf("未找到该联系人！\n");
}

/*查找联系人模块*/
void findPIMS() 
{
    int choice;
    char search_key[50];
    printf("1. 按姓名查找\n");
    printf("2. 按电话查找\n");
    printf("请选择查找方式: ");
    scanf("%d", &choice);
    if (choice == 1)
	{
        printf("请输入要查找的姓名: ");
        scanf("%s", search_key);
    } 
	else if (choice == 2)
	{
        printf("请输入要查找的电话: ");
        scanf("%s", search_key);
    } 
	else 
	{
        printf("无效的选择，请重新输入！\n");
        return;
    }
    PIMS *current = head;
    int found = 0;

    while (current != NULL) 
	{
           if (choice == 1)
		   {
                if (strcmp(current->name, search_key) == 0) 
				{
                    printf("姓名: %s, 性别: %s, 地址: %s, 电话: %s\n",current->name, current->sex, current->address, current->phone);
                    found = 1;
                   }
            } 
			else if (choice == 2) 
			{
                if (strcmp(current->phone, search_key) == 0) 
				{
                    printf("姓名: %s, 性别: %s, 地址: %s, 电话: %s\n",current->name, current->sex, current->address, current->phone);
                    found = 1;
                }
            }
        current = current->next;
    }
    if (!found) 
	{
        printf("未找到该联系人！\n");
    }
}


void displayPIMS() 
{
    if (head == NULL) 
	{
        printf("通讯录为空！\n");
        return;
    }
    PIMS *current = head;
    while (current != NULL) 
	{
        printf("姓名: %s, 性别: %s, 地址: %s, 电话: %s\n",current->name, current->sex, current->address, current->phone);
        current = current->next;
    }
}


void savePIMS() 
{
    FILE *fp = fopen("PIMS.txt", "w");
    if (fp == NULL) 
	{
        printf("无法打开文件！\n");
        return;
    }

    PIMS *current = head;
    while (current != NULL) 
	{
        fprintf(fp, "%s %s %s %s\n",current->name, current->sex, current->address, current->phone);
        current = current->next;
    }
    fclose(fp);
    printf("\n");
}


void savelogin() 
{
    FILE *fp = fopen("login.txt", "w");
    if (fp == NULL) 
	{
        printf("无法打开文件！\n");
        return;
    }

    login *current = headpro;
    while (current != NULL) 
	{
        fprintf(fp, "%s %s\n",current->zhanghao, current->mima);
        current = current->next;
    }
    fclose(fp);
    printf("\n");
}


void loadPIMS() 
{
    FILE *fp = fopen("PIMS.txt", "r");
    if (fp == NULL) 
	{
        return;
    }

    PIMS *newPIMS;
    while (1) 
	{
       newPIMS = (PIMS *)malloc(sizeof(PIMS));
        if (newPIMS == NULL)
		{
            printf("内存分配失败！\n");
            fclose(fp);
            return;
        }
        if(fscanf(fp, "%s %s %s %s", newPIMS->name, newPIMS->sex, newPIMS->address, newPIMS->phone) == EOF){
            free(newPIMS);
            break;
        }

        newPIMS->next = NULL;
        if (head == NULL) 
		{
            head = newPIMS;
        } else {
            PIMS *temp = head;
            while (temp->next != NULL) 
			{
                temp = temp->next;
            }
            temp->next = newPIMS;
        }
        
    }
    fclose(fp);
    printf("\n");
}


void freePIMS() 
{
    PIMS *current = head;
    PIMS *temp;
    while (current != NULL) 
	{
        temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}


void loadlogin() 
{
    FILE *fp = fopen("login.txt", "r");
    if (fp == NULL) 
	{
        return;
    }

    login *newlogin;
    while (1) 
	{
       newlogin = (login *)malloc(sizeof(login));
        if (newlogin == NULL)
		{
            printf("内存分配失败！\n");
            fclose(fp);
            return;
        }
        if(fscanf(fp, "%s %s", newlogin->zhanghao, newlogin->mima) == EOF)
		{
            free(newlogin);
            break;
        }

        newlogin->next = NULL;
        if (headpro == NULL) 
		{
            headpro = newlogin;
        } 
		else 
		{
            login *temp = headpro;
            while (temp->next != NULL) 
			{
                temp = temp->next;
            }
            temp->next = newlogin;
        }
        
    }
    fclose(fp);
    printf("\n");
}


void freelogin() 
{
    login *current = headpro;
    login *temp;
    while (current != NULL) 
	{
        temp = current;
        current = current->next;
        free(temp);
    }
    headpro = NULL;
}
