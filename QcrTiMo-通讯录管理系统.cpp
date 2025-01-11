#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


/*PIMS=Personal Information Managerment System(������Ϣ������ϵ)*/


typedef struct PIMS      /*������PIMS�ṹ������������ϵ�˻�����Ϣ*/
{
    char name[50];
    char sex[10];
    char address[100];
    char phone[20];
    struct PIMS *next;
}PIMS;


typedef struct login      /*������login�ṹ�����������û����˺���Ϣ*/
{
	char zhanghao[50];
	char mima[50];
	struct login *next;
}login;


PIMS *head = NULL;        /*��������ͷ�ڵ㣬Ϊ������ļ�������׼��*/
login *headpro = NULL;


void login1();
void addPIMS();
void deletePIMS();
void modifyPIMS();
void findPIMS();           /*�����������ܺ�������*/
void displayPIMS();
void savePIMS();
void loadPIMS();
void freePIMS();
void savelogin();
void loadlogin();
void freelogin();

/*������*/
int main() 
{
    loadPIMS();       /*�ڿ�ʼ����ͷ���¼��ز���ȡ�ļ�����*/
    loadlogin();
    login1();         /*�ڽ���˵�ǰ���û�����ע���˺š���¼����������һ����ȫ��*/
    int choice;
    do 
	{
        printf("���������������� ͨѶ¼����ϵͳ ����������������\n");
        printf("����             1. �����ϵ��              ���� \n");
        printf("����             2. ɾ����ϵ��              ���� \n");
        printf("����             3. �޸���ϵ��              ���� \n");    /*�˵���ʽ*/
        printf("����             4. ������ϵ��              ���� \n");
        printf("����             5. ��ʾ������ϵ��          ���� \n");
        printf("����             0. �˳�ϵͳ                ���� \n");
        printf("������������������������������������������������\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);
        switch (choice)        /*�˵�����ѡ�����벻ͬ���֣�ǰ�����в�ͬ�Ĺ��ܺ���*/
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
                savePIMS();       /*��������ǰ���ļ����б��沢�ͷ������ڴ棬��֤�ļ��ͳ������������*/
                freePIMS();
                savelogin();
                freelogin();
                printf("��лʹ�ã�\n");
                Sleep(3000);
                break;
            default:
                printf("��Ч��ѡ�����������룡\n");
        }
    }while (choice != 0);
    return 0;
}

/*��¼����ģ��*/
void login1()
{
	char search_zh[50];    /*�������˺���������飬���������˺ŵ�����*/
	char search_mm[50];
	char zhanghao[50];
	char mima[50];
    login *newlogin = (login *)malloc(sizeof(login));   /*Ϊ�����������ݴ洢�����ڴ�*/
    if(newlogin==NULL)
    {
		printf("�ڴ����ʧ��!\n");
		return;
	}
	if(headpro==NULL)    /*����ļ��ǿյĻ���û���ļ��������ʾ�����˺�����*/
	{
		printf("��ӭʹ����QcrTiMo������ͨѶ¼����ϵͳ��\n");
		printf("\n");
		Sleep(1000);
		printf("��⵽�㻹δӵ���˺�,��ע�����ʹ�ù���ϵͳ\n");
		printf("\n");
		Sleep(1000);
		printf("ע������˺�:\n");
	reloginzczh:scanf("%s",newlogin->zhanghao);     /*���˺����ݴ洢��������*/
		login *current = headpro;	
		while(current!=NULL)
		{
			if(strcmp(current->zhanghao,zhanghao)==0)
			{
				printf("�˺��Ѵ��ڣ�����������ע������˺�:\n");
				goto reloginzczh;
			}
			current = current->next;
		}
		printf("ע�������������:\n");
	reloginzcmm:scanf("%s",newlogin->mima);
		while(current!=NULL)
		{
			if(strcmp(current->mima,mima)==0)
			{
				printf("�����Ѵ��ڣ�������ע�������������:\n");
				goto reloginzcmm;
			}
			current = current->next;
		}		
		newlogin->next = NULL;           /*��newloginָ�붨�嵽��һ���ڵ㣬Ϊ�������Ķ�ȡ��׼��*/
		if(headpro==NULL)
		{
			headpro=newlogin;
		}
		else
		{
			login *temp = headpro;
			while(temp->next != NULL)      /*������ʱָ�룬����ָ��״̬�������������д�뵽�ļ���*/
			{
				temp = temp->next;
			}
			temp->next = newlogin;
		}
		savelogin();            /*ʵʱ��������ļ��������û�ֱ�Ӳ�������û�б�������*/
		printf("�˺���ӳɹ�����ӭʹ��ͨѶ¼����ϵͳ��\n");
		printf("\n");
		Sleep(1000);
	}
	else              /*����ļ���Ϊ�գ�Ҳ�����û�֮ǰ�Ѿ�ע�������˺ţ�������¼�׶�*/
	{
		printf("��ӭʹ����QcrTiMo������ͨѶ¼����ϵͳ��\n");
		printf("\n");
		Sleep(1000);
		printf("��⵽��ӵ���˺ţ���ʹ���˺������¼����ϵͳ\n");
		printf("\n");
		Sleep(1000);
		printf("��������˺�:\n");
	reloginzh:scanf("%s",search_zh);
		login *current = headpro;
		int found = 0;
		while(current != NULL)
		{
			if(strcmp(current->zhanghao,search_zh)==0)        /*�����ļ����������û�������ͬ�����ݣ����û���򷵻ش���*/
			{
				printf("�����������:\n");
			reloginmm:scanf("%s",search_mm);
				login *current = headpro;
				int foundmm = 0;
				while(current != NULL)
				{
					if(strcmp(current->mima,search_mm)==0)
					{
						printf("��¼�ɹ�����ӭʹ��ͨѶ¼����ϵͳ��\n");
						printf("\n");
						Sleep(1000);
						return;
					}
					current = current->next;
				}
				if(!foundmm)
				{
					printf("�����������������!\n");
					printf("�����������:\n");
					goto reloginmm;
				}
			}
			current = current->next;
		}
		if(!found)
		{
			printf("�˺���������û�д��˺ţ�������!\n");
			printf("��������˺�:\n");
			goto reloginzh;                     /*ʹ��goto����Ȼ������ȥ�ܷ������������ܱ���ifѭ�����࣬���𵽻���������*/
		}
	}

}

/*�����ϵ��ģ��*/
void addPIMS() 
{
    PIMS *newPIMS = (PIMS *)malloc(sizeof(PIMS));
    if (newPIMS == NULL) 
	{
        printf("�ڴ����ʧ�ܣ�\n");
        return;
    }
    printf("����������: ");
    scanf("%s", newPIMS->name);     /*���û�������ַ���ͨ��ָ�뱣�浽�ṹ�嵱�д���*/
    printf("�������Ա�: ");
    scanf("%s", newPIMS->sex);
    printf("�������ַ: ");
    scanf("%s", newPIMS->address);
    printf("������绰: ");
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
    printf("��ϵ����ӳɹ���\n");
}

/*ɾ����ϵ��ģ��*/
void deletePIMS() 
{
    char name[50];
    printf("������Ҫɾ������ϵ������: ");
    scanf("%s", name);
    if (head == NULL) 
	{
        printf("ͨѶ¼Ϊ�գ�\n");
        return;
    }
    PIMS *current = head;     /*����currentָ�����������ļ�*/
    PIMS *previous = NULL;    /*����previousָ����������ɾ������*/
    while (current != NULL) 
	{
        if (strcmp(current->name, name) == 0) 
		{
            if (previous == NULL) 
			{
                head = current->next;     /*����ɾ���������ָ����µ�Ҫɾ���ڵ����һ���ڵ㣬�����ýڵ�*/
            } 
			else 
			{
                previous->next = current->next;
            }
            free(current);
            printf("��ϵ��ɾ���ɹ���\n");
            return;
        }
        previous = current;
        current = current->next;    /*����currentָ�뵽��һ���ڵ㣬Ϊ�´ι�����׼��*/
    }
    printf("δ�ҵ�����ϵ�ˣ�\n");
}

/*�޸���ϵ��ģ��*/
void modifyPIMS() 
{
    char name[50];
    printf("������Ҫ�޸ĵ���ϵ������: ");
    scanf("%s", name);

    PIMS *current = head;
    while (current != NULL) 
	{
        if (strcmp(current->name, name) == 0)   /*�����ļ����������û������name��ͬ�����ݣ���ʱ�ѵ��ľ����û�Ҫ�޸ĵ���ϵ������*/
		{
            printf("�������µ�����: ");    /*��׽�û���������ݣ�Ȼ���ŵ�currentָ��ָ��Ľṹ����*/
            scanf("%s", current->name);
            printf("�������µ��Ա�: ");
            scanf("%s", current->sex);
            printf("�������µĵ�ַ: ");
            scanf("%s", current->address);
            printf("�������µĵ绰: ");
            scanf("%s", current->phone);
            printf("��ϵ���޸ĳɹ���\n");
            return;
        }
        current = current->next;
    }
    printf("δ�ҵ�����ϵ�ˣ�\n");
}

/*������ϵ��ģ��*/
void findPIMS() 
{
    int choice;
    char search_key[50];
    printf("1. ����������\n");
    printf("2. ���绰����\n");
    printf("��ѡ����ҷ�ʽ: ");
    scanf("%d", &choice);
    if (choice == 1)
	{
        printf("������Ҫ���ҵ�����: ");
        scanf("%s", search_key);
    } 
	else if (choice == 2)
	{
        printf("������Ҫ���ҵĵ绰: ");
        scanf("%s", search_key);
    } 
	else 
	{
        printf("��Ч��ѡ�����������룡\n");
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
                    printf("����: %s, �Ա�: %s, ��ַ: %s, �绰: %s\n",current->name, current->sex, current->address, current->phone);
                    found = 1;
                   }
            } 
			else if (choice == 2) 
			{
                if (strcmp(current->phone, search_key) == 0) 
				{
                    printf("����: %s, �Ա�: %s, ��ַ: %s, �绰: %s\n",current->name, current->sex, current->address, current->phone);
                    found = 1;
                }
            }
        current = current->next;
    }
    if (!found) 
	{
        printf("δ�ҵ�����ϵ�ˣ�\n");
    }
}


void displayPIMS() 
{
    if (head == NULL) 
	{
        printf("ͨѶ¼Ϊ�գ�\n");
        return;
    }
    PIMS *current = head;
    while (current != NULL) 
	{
        printf("����: %s, �Ա�: %s, ��ַ: %s, �绰: %s\n",current->name, current->sex, current->address, current->phone);
        current = current->next;
    }
}


void savePIMS() 
{
    FILE *fp = fopen("PIMS.txt", "w");
    if (fp == NULL) 
	{
        printf("�޷����ļ���\n");
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
        printf("�޷����ļ���\n");
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
            printf("�ڴ����ʧ�ܣ�\n");
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
            printf("�ڴ����ʧ�ܣ�\n");
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
