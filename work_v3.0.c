//ѧ���ɼ�����ϵͳ 
//���ߣ������� 22L0214 2022113523 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 
#define FILE_NAME "�ɼ�����.txt"
#define FILE_NAME2 "TEMP.txt"

typedef struct student//����ṹ����������  ��׼��ʹ�ýṹ������
	{
		char name[20];//�ַ����鳤�ȱ�֤�ܴ��������Ļ�Ӣ���� 
		long long studentID;//ʹ��long long����ѧ�ţ���ֹ����������� 
		int *pscore;//׼��ʹ�ö�̬���� 
	}STUDENT;//����struct student�ı�������������

struct link//��������Ľṹ�� ��ʹ������ 
	{
		char stuname[20];
		long long int stuID;
		struct link *next;//ʹ������ 
	};

void SnowWelcome(void);
STUDENT *ReadStudent(void);
STUDENT *AddNode(struct link *head);
STUDENT *SaveFile(struct link *head);
STUDENT *AppendNode(struct link *head);
STUDENT *ChooseFirst(struct link *head,STUDENT *pstu); 
void ChooseOption(void);
void GoMeunFirst(STUDENT *pstu);
void GoMeun(STUDENT *pstu);
void option(STUDENT *pstu);
void InputData(STUDENT *p);
void AverCourse(STUDENT *p);
int CheckInput(int optionnum);
int *TotalStudent(STUDENT *p); 
void PrintAverStudent(STUDENT *p,int *psum);
void OrderDescendTotal(STUDENT *p,int *psum);
void OrderAscendTotal(STUDENT *p,int *psum);
void OrderAscendNum(STUDENT *p,int *psum);
void OrderDicName(STUDENT *p,int *psum);
void SearchNum(STUDENT *p);
void SearchName(STUDENT *p); 
void SearchNameFuzzy(STUDENT *p); 
void AnalyseCourse(STUDENT *p,int *psum);
void ListRecord(STUDENT *p,int *psum);
void WriteFile(STUDENT *p);
void ReadFile(STUDENT *p);
void Random(STUDENT *pstu);
void ThankUse(void); 
 

int optionnum;//��ѡ���Ϊȫ�ֱ���������������ʹ�� 
int studentnum;
int subjectnum;//��ѧ����������Ϊȫ�ֱ���������������ʹ�� 
int flaginput = 0;//���ڼ�¼�Ƿ��Ѷ������ݣ����û�ж������ݣ�������ʹ����������
char judgeexit = 'Y';//�ж��Ƿ��˳����� 
char audio = '\007';//���ڷ�����Ч 
int firstchoose;//ѡ���������뷽ʽ 


int main(void)
{
 	SnowWelcome();//չʾ��ӭ���� 
 	int i,k;//ѭ����������� 

    struct link *head = NULL;//����ͷָ�� 
 	STUDENT *pstu = NULL;//�ṹ��ָ�� 
 	pstu = ChooseFirst(head,pstu);
	printf("The number of students is %d\n",studentnum); 
	printf("The number of subjects is %d\n",subjectnum);
	if(firstchoose==1)
	{
		for(i=0;i<studentnum;i++)
		{
		    printf("Please input the score of the %d student\n",i+1);
			for(k=0;k<subjectnum;k++)
			{
				scanf("%d",&pstu[i].pscore[k]);
			}
		}
		option(pstu);
	}
	else if(firstchoose==2)
	{
		printf("Please input data according to the numbers you give\n");
        GoMeunFirst(pstu);
	}
}

/*
  �����������������ڵ� 
  ��ڲ����� struct link *headͷ�ڵ�ָ�� 
  ���ڲ����� struct link *head
  ����ֵ�� STUDENT *pstu 
*/ 	
STUDENT *AppendNode(struct link *head)
{
    STUDENT *pstu = NULL;
	char name[20];
	long long ID;
	int score;
	struct link *p =NULL,*pr = head;
	int data;
	p=(struct link *)malloc(sizeof(struct link));//��̬��ʾ 
	if(p == NULL)//��p�ǲ��ǿյ� 
	{
		printf("No enough memory to allocate!\n");
		exit(0);
	}
	if(head == NULL)//���ͷ�ڵ��ǿյ� 
	{
		head = p;
	}
	else
	{
		while(pr->next!=NULL)
		{
			pr = pr->next;
		}
		pr->next=p;
	}
	printf("Input student name:\n");
	scanf("%s",name);
	printf("Input student ID:\n");
	scanf("%lld",&ID);
	p->stuID = ID;
    strcpy(p->stuname,name);
	p->next = NULL;
	printf("\nSuccessfully added\n\n");
	pstu = AddNode(head);
	return pstu;
}	

 
/*
  ��������������ѡ���������뷽ʽ 
  ��ڲ����� struct link *head����ͷָ�룬pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� struct link *head,STUDENT *pstu
  ����ֵ�� STUDENT *pstu 
*/ 	 
STUDENT *ChooseFirst(struct link *head,STUDENT *pstu)
{
	int i;//ѭ������ 
	printf("Please to choose the way to input data:\n"
	       "1.Via node\n"
		   "2.Via file/Integral input\n");
		   scanf("%d",&firstchoose);
	while(firstchoose!=1&&firstchoose!=2)
	{
		printf("Sorry,this is an illeagal input!\n");//��ֹ�Ƿ����� 
		printf("please try again\n");
		scanf("%d",&firstchoose);
		fflush(stdin);
	}
	if(firstchoose==1)
	{
		pstu = AppendNode(head);
	}
    else if(firstchoose==2)
    {
    	pstu = ReadStudent();
	} 
	printf("How many subject?\n");
	scanf("%d",&subjectnum);
	for(i=0;i<studentnum;i++)
	{
		pstu[i].pscore = NULL;
		pstu[i].pscore = (int*)malloc(subjectnum * sizeof(int));//ʹ�ö�̬����
		if(pstu[i].pscore == NULL)//ȷ��ָ��ʹ��ǰ�Ƿǿ�ָ�룬��pΪ��ָ��ʱ������������ 
		{
			printf("No enough memory!\n");
			exit(1);
		}
	}
	return pstu; 

}

/*
  �������������ڵ�һ�ν���˵� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void GoMeunFirst(STUDENT *pstu)
{
	int op;
	printf("%c",audio);//������Ч
	printf( "\nPlease press a number to choose functions to get data\n"
	      "Functions:\n"
	      "1.Input record\n"
	      "2.Read from a file\n");
	scanf("%d",&op);
    switch(op)
    {
    	case 1:InputData(pstu); break;
    	case 2:ReadFile(pstu); break;
    	default:printf("Your input is not correct,please try aggin!\n"); GoMeunFirst(pstu);
	}
}


/*
  ��������������ֻ���ٴν���˵� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void GoMeun(STUDENT *pstu)
{
	fflush(stdin);
    printf("GO TO THE FUNCTION MEUN?(Y/N)\n");
	scanf("%c",&judgeexit);
	if(judgeexit=='Y'||judgeexit=='y')
	{
		option(pstu);
	}
	else if(judgeexit=='N'||judgeexit=='n')
	{
		ThankUse();
	}
	else
	{
		printf("Your input is not correct,please try aggin!\n");
		GoMeun(pstu);
	}
}


/*
  ��������������һ������� 
  ��ڲ����� void 
  ���ڲ����� void 
  ����ֵ�� int һ����Χ��2-13����������� 
*/ 
void Random(STUDENT *pstu)
{
	int a;
	printf("^_^  Choose a function randomly!  ^_^\n");
	srand(time(NULL));
	a=rand()%12+2;
	switch(a)
	{
		case 2:AverCourse(pstu); break;
		case 3:PrintAverStudent(pstu,TotalStudent(pstu)); break;
		case 4:OrderDescendTotal(pstu,TotalStudent(pstu)); break;
		case 5:OrderAscendTotal(pstu,TotalStudent(pstu)); break;
		case 6:OrderAscendNum(pstu,TotalStudent(pstu)); break;
		case 7:OrderDicName(pstu,TotalStudent(pstu)); break;
		case 8:SearchNum(pstu); break;
		case 9:SearchName(pstu); break;
		case 10:SearchNameFuzzy(pstu); break;
		case 11:AnalyseCourse(pstu,TotalStudent(pstu)); break;
		case 12:ListRecord(pstu,TotalStudent(pstu)); break;
		case 13:WriteFile(pstu); break;
		case 14:ReadFile(pstu); break;
		}
}


/*
  �������������ڲ˵��ĵ��� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void option(STUDENT *pstu)
{
	printf("%c",audio);//������Ч
	printf("\n\n");
	ChooseOption();//��ӡѡ�����
   	switch(optionnum)//�Ѽ��������ȷ�ԣ����Բ���Ҫdefault 
	{
		case 1:InputData(pstu); break;  //��һ�α����������ݲ��ܽ������²���
		case 2:AverCourse(pstu); break;
		case 3:PrintAverStudent(pstu,TotalStudent(pstu)); break;
		case 4:OrderDescendTotal(pstu,TotalStudent(pstu)); break;
		case 5:OrderAscendTotal(pstu,TotalStudent(pstu)); break;
		case 6:OrderAscendNum(pstu,TotalStudent(pstu)); break;
		case 7:OrderDicName(pstu,TotalStudent(pstu)); break;
		case 8:SearchNum(pstu); break;
		case 9:SearchName(pstu); break;
		case 10:SearchNameFuzzy(pstu); break;
		case 11:AnalyseCourse(pstu,TotalStudent(pstu)); break;
		case 12:ListRecord(pstu,TotalStudent(pstu)); break;
		case 13:WriteFile(pstu); break;
		case 14:ReadFile(pstu); break;
		case 15:Random(pstu); break; 
		case 0:ThankUse(); break;
		}	
}


/*
  ��������������չʾ��ӭ���� 
  ��ڲ����� void 
  ���ڲ����� void 
  ����ֵ�� void
*/ 
void SnowWelcome(void)
{
	int i;//����ѭ���Ĳ����� 
	printf("Welcome to use the grade management system!\n"
		   "author�������� 22L0214 2022113523\n"
	       "*******************************************\n"
		   "      **      **     ********   **\n"
		   "      **      **        **      **\n"  
		   "      **********        **      **\n"
		   "      **      **        **        \n"
		   "      **      **     ********   **\n\n"
		   "*******************************************\n");
	for(i=0;i<5;i++)
	{
		printf("%c",audio);//������Ч 
	} 
	
}


/*
  ����������չʾ�ڶ��μ�֮���ѡ��ҳ�� 
  ��ڲ����� void 
  ���ڲ����� void 
  ����ֵ�� void
*/ 
void ChooseOption(void)
{
	printf( "Please press a number to choose functions\n"
	       "Functions:\n"
	       "1.Input record\n"
	       "2.Calculate total and average score of every course\n"
	       "3.Calculate total and average score of every student\n"
	       "4.Sort in descending order by total score of every student\n"
	       "5.Sort in ascending order by total score of every student\n"
	       "6.Sort in ascending order by number\n"
	       "7.Sort in dictionary order by name\n"
	       "8.Search by number\n"
	       "9.Search by name\n"
	       "10.Fuzzy search by name's initial letter\n"
	       "11.Statistic analysis for every course\n"
	       "12.List record\n"
	       "13.Write to a file\n"
	       "14.Read from a file\n"
	       "15.Choose a function randomly!  ^_^\n"
	       "0.Exit\n");
	scanf("%d",&optionnum);
	while(CheckInput(optionnum)==0)
	{
		printf("Sorry,this is an illeagal input!\n");
		printf("please try again\n");
		scanf("%d",&optionnum);
		fflush(stdin);
	}
}


/*
  ������������������ѡ�����Ƿ�Ϸ� 
  ��ڲ����� optionnum ѡ���� 
  ���ڲ����� int optionnum 
  ����ֵ�� int ����1��ʾ�Ϸ�������0��ʾ���Ϸ� 
*/ 
int CheckInput (int optionnum)
{
	if(optionnum>=0&&optionnum<=15)
	{
		return 1;
	}
	else return 0;
}

/*
  �������������ڶ���ѧ������ 
  ��ڲ����� void 
  ���ڲ����� void
  ����ֵ�� STUDENT *pstu 
*/ 	
STUDENT *ReadStudent(void)
{
	STUDENT *pstu = NULL;//����STUDENT���Ϳ�ָ�� 
	printf("How many student?\n");//����ѧ������ 
	scanf("%d",&studentnum);
	pstu = (STUDENT*)malloc((studentnum+1) * sizeof(STUDENT));// ʹ�ö�̬����,+1Ϊ������ʱ�� 
	if(pstu == NULL)//ȷ��ָ��ʹ��ǰ�Ƿǿ�ָ�룬��pΪ��ָ��ʱ������������ 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	return pstu;	
	
	
/*
  ����������ѯ���Ƿ��������ڵ� 
  ��ڲ����� struct link *headͷ�ڵ�ָ�� 
  ���ڲ����� struct link *head
  ����ֵ�� STUDENT *pstu 
*/ 	
}
STUDENT *AddNode(struct link *head)
{
	STUDENT *pstu = NULL;
	printf("Add node?(Y/N)\n");
	fflush(stdin);
	scanf("%c",&judgeexit);
	if(judgeexit=='Y'||judgeexit=='y')
	{
		AppendNode(head);
	}
	else if(judgeexit=='N'||judgeexit=='n')
	{
		pstu = SaveFile(head);
		return pstu;
	}
	else
	{
		printf("Your input is not correct,please try aggin!\n");
		AddNode(head);
	}
}


/*
  ����������������������� 
  ��ڲ����� struct link *headͷ�ڵ�ָ�� 
  ���ڲ����� struct link *head
  ����ֵ�� STUDENT *pstu 
*/ 	
STUDENT *SaveFile(struct link *head)
{
	struct link *p = head;
    STUDENT *pstu = NULL;
	int j = 0;
	int i,k;//�½�ѭ������ 
	FILE *fp = fopen(FILE_NAME2,"w");//�½��ļ�����ΪFILE_NAME2 
	if(fp == NULL)//��֤�ļ��Ƿ񴴽��ɹ���δ�ɹ��򷵻����˵� 
	{
		printf("Failed to create a file!\n");
		exit(1);
	} 
	while(p!=NULL)
	{
		fprintf(fp,"%s ",p->stuname);
		fprintf(fp,"%lld ",p->stuID);
		p=p->next;
		j++;
	}
	fclose(fp);//�ر��ļ�
	studentnum = j; 
	pstu = (STUDENT*)malloc((studentnum+1) * sizeof(STUDENT));// ʹ�ö�̬����,+1Ϊ������ʱ�� 
	FILE *fp2 = fopen(FILE_NAME2,"r");
	if(fp == NULL)//��֤�ļ��Ƿ�򿪳ɹ���δ�ɹ��򷵻����˵� 
	{
		printf("Failed to open a file!\n");
		exit(0);
	}
	for(i=0;i<studentnum;i++)//���ν���Ӧ��Ϣ���ļ����� 
	{
		fscanf(fp,"%s ",pstu[i].name);
		fscanf(fp,"%lld ",&pstu[i].studentID);
	}
	fclose(fp);//�ر��ļ� 
	printf("The data have been read!\n\n\n");
	flaginput=1;
	return pstu;	 
}


/*
  ���������������������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void InputData(STUDENT *p)
{
	if(flaginput==1)
	{
		fflush(stdin);//��ջ����� 
		printf("You have input data,would you like to input again?(Y/N)\n");//��ֹ���������� 
		scanf("%c",&judgeexit);
		if(judgeexit=='Y'||judgeexit=='y')
		{
			;
		}
		else if(judgeexit=='N'||judgeexit=='n')
		{
			option(p);
		}
		else
		{
			printf("Your input is not correct,please try aggin!\n");
			InputData(p);
		}
	} 
	printf("\nInput Data\n");
	int i,k;//ѭ���еĲ��� 
	printf("Please input as \"NAME STUDENTID SCORE1 SCORE2...  \"IN EACH LINE\n");
	printf("Press enter to press another student's information\n");
	printf("For example: ZZY 2022113523 100 100 100\n");
	for(i=0;i<studentnum;i++)
	{
		scanf("%s",p[i].name);
		scanf("%lld",&p[i].studentID);//�������벻������ 
		for(k=0;k<subjectnum;k++)
		{
			scanf("%d",&p[i].pscore[k]);
		}
	} 
	flaginput=1;
	option(p);
}


/*
  ��������������ѧ�����γ�ƽ���ֵļ��� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void AverCourse(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!");
			InputData(p); 
		}			
	printf("\nTotal and average score of every course\n");
	int *psum = NULL;
	psum = (int*)malloc(subjectnum * sizeof(int));// ʹ�ö�̬���� 
	if(psum == NULL)//ȷ��ָ��ʹ��ǰ�Ƿǿ�ָ�룬��pΪ��ָ��ʱ������������ 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	int i,k,m;//����ѭ�������ò���
	for(i=0;i<subjectnum;i++)
	{
		psum[i]=0;
		for(k=0;k<studentnum;k++)
		{
			psum[i]+=p[k].pscore[i];
		}
	} 
	printf("\tsum\taverage\n");//�Ʊ� 
	for(m=0;m<subjectnum;m++)
	{
		printf("\t%d\t%.2f\n",psum[m],(float)psum[m]/studentnum);
	}
	free(psum);
	GoMeun(p);
}


/*
  �������������ڼ���ѧ���ܷ� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� ָ��ѧ���ֵܷ�ָ��*psum 
*/ 
int *TotalStudent(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	int *psum = NULL;
	psum = (int*)malloc(studentnum * sizeof(int));// ʹ�ö�̬���� 
	if(psum == NULL)//ȷ��ָ��ʹ��ǰ�Ƿǿ�ָ�룬��pΪ��ָ��ʱ������������ 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	int i,k;//����ѭ�������ò���
	for(i=0;i<studentnum;i++)
	{
		psum[i]=0;
		for(k=0;k<subjectnum;k++)
		{
			psum[i]+=p[i].pscore[k];
		}
	}
	return psum;
}


/*
  ������������ӡ��ѧ�����γ̵�ƽ���� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void PrintAverStudent(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nTotal and average score of every student\n");
	int m;//����ѭ������ 
	printf("\tname\tID\t\tsum\taverage\n");//�Ʊ� 
	for(m=0;m<studentnum;m++)
	{
		printf("\t%s\t%lld\t%d\t%.2f\n",p[m].name,p[m].studentID,psum[m],(float)psum[m]/subjectnum);
	}
	free(psum); 
	GoMeun(p);
}


/*
  ����������ѧ���γ��ֽܷ������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void OrderDescendTotal(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!");
			InputData(p);
		}		
	printf("\nSort in descending order by total score of every student\n");
	int i,m,k,w;//����ѭ������
	int temp = 0;//������ʱ���� 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(psum[m]<psum[i])
			{
				p[studentnum].studentID=p[m].studentID;//�������������һ�����ʱ�� 
				p[m].studentID=p[i].studentID;
				p[i].studentID=p[studentnum].studentID;
				strcpy(p[studentnum].name,p[m].name);
				strcpy(p[m].name,p[i].name);
				strcpy(p[i].name,p[studentnum].name);
				for(w=0;w<subjectnum;w++)
				{
					temp=p[m].pscore[w];
					p[m].pscore[w]=p[i].pscore[w];
					p[i].pscore[w]=temp;
				}
				temp=psum[m];
				psum[m]=psum[i];
				psum[i]=temp;
			}
	    }
	} 
	printf("\tname\tID\tsum score\n");
	for(k=studentnum-1;k>=0;k--)
	{
		printf("\t%s\t%lld\t%d\n",p[k].name,p[k].studentID,psum[k]);
	}
	GoMeun(p);
}


/*
  ����������ѧ���γ��ܷ��������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void OrderAscendTotal(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in ascending order by total score of every student\n");
	int i,m,k,w;//����ѭ������
	int temp = 0;//������ʱ���� 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(psum[m]<psum[i])
			{
				p[studentnum].studentID=p[m].studentID;//�������������һ�����ʱ�� 
				p[m].studentID=p[i].studentID;
				p[i].studentID=p[studentnum].studentID;
				strcpy(p[studentnum].name,p[m].name);
				strcpy(p[m].name,p[i].name);
				strcpy(p[i].name,p[studentnum].name);
				for(w=0;w<subjectnum;w++)
				{
					temp=p[m].pscore[w];
					p[m].pscore[w]=p[i].pscore[w];
					p[i].pscore[w]=temp;
				}
				temp=psum[m];
				psum[m]=psum[i];
				psum[i]=temp;				
			}
	    }
	} 
	printf("\tname\tID\tsum score\n");
	for(k=0;k<studentnum;k++)
	{
		printf("\t%s\t%lld\t%d\n",p[k].name,p[k].studentID,psum[k]);
	}
	GoMeun(p);
}


/*
  ����������ѧ��ѧ���������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void OrderAscendNum(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in ascending order by number\n");
	int i,m,k,w;//����ѭ������
	int temp = 0;//������ʱ���� 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(p[m].studentID<p[i].studentID)
			{
				p[studentnum].studentID=p[m].studentID;//�������������һ�����ʱ�� 
				p[m].studentID=p[i].studentID;
				p[i].studentID=p[studentnum].studentID;
				strcpy(p[studentnum].name,p[m].name);
				strcpy(p[m].name,p[i].name);
				strcpy(p[i].name,p[studentnum].name);
				for(w=0;w<subjectnum;w++)
				{
					temp=p[m].pscore[w];
					p[m].pscore[w]=p[i].pscore[w];
					p[i].pscore[w]=temp;
				}
				temp=psum[m];
				psum[m]=psum[i];
				psum[i]=temp;			
			}
	    }
	} 
	printf("\tname\tID\t\tsum score\n");
	for(k=0;k<studentnum;k++)
	{
		printf("\t%s\t%lld\t%d\n",p[k].name,p[k].studentID,psum[k]);
	}
	GoMeun(p);
}


/*
  ����������ѧ�������ֵ������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void OrderDicName(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in dictionary order by name\n");
	int i,m,k,w;//����ѭ������
	int temp = 0;//������ʱ����	
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(strcmp(p[m].name,p[i].name)<0)
			{
				p[studentnum].studentID=p[m].studentID;//�������������һ�����ʱ�� 
				p[m].studentID=p[i].studentID;
				p[i].studentID=p[studentnum].studentID;
				strcpy(p[studentnum].name,p[m].name);
				strcpy(p[m].name,p[i].name);
				strcpy(p[i].name,p[studentnum].name);
				for(w=0;w<subjectnum;w++)
				{
					temp=p[m].pscore[w];
					p[m].pscore[w]=p[i].pscore[w];
					p[i].pscore[w]=temp;
				}
				temp=psum[m];
				psum[m]=psum[i];
				psum[i]=temp;				
			}
	    }
	} 
	printf("\tname\tID\t\tsum score\n");
	for(k=0;k<studentnum;k++)
	{
		printf("\t%s\t%lld\t%d\n",p[k].name,p[k].studentID,psum[k]);
	}
	GoMeun(p);
}


/*
  ������������ѧ�Ų���ѧ�� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ��
  ���ڲ����� STUDENT *pstu  
  ����ֵ�� void
*/ 
void SearchNum(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	long long stunum;//��long long��ʾҪ������ѧ�� 
	int i,flag=0;//����ѭ������ ������flag����Ƿ��ҵ� 
	printf("\nSearch by number\n");
	printf("Please prese the student's ID you want:\n");
	scanf("%lld",&stunum);//����Ҫ������ѧ��
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(p[i].studentID-stunum==0)
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//����ҵ� 
		}
	} 
	if(flag==1)
	{
		printf("Found!\n");
	}
	if(flag==0)
	{
		printf("Not found!\n");
	} 	
	GoMeun(p); 
}


/*
  ��������������������ѧ���� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ��  
  ���ڲ����� STUDENT *pstu �ṹ��ָ��
  ����ֵ�� void
*/ 
void SearchName(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	char searchname[20];//���ַ������ʾҪ���������� 
	int i,flag=0;//����ѭ������ ������flag����Ƿ��ҵ� 
	printf("\nSearch by name\n");
	printf("Please prese the student's name you want:\n");
	scanf("%s",searchname);//����Ҫ����������
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(strcmp(searchname,p[i].name)==0)
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//����ҵ� 
		}
	} 
	if(flag==1)
	{
		printf("Found!\n");
	}
	if(flag==0)
	{
		printf("Not found!\n");
	} 
	GoMeun(p);	 
}


/*
  ��������������������ĸģ������ѧ���� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ��  
  ���ڲ����� STUDENT *pstu �ṹ��ָ��
  ����ֵ�� void
*/ 
void SearchNameFuzzy(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	char searchname[20];//���ַ������ʾҪ���������� 
	int i,flag=0;//����ѭ������ ������flag����Ƿ��ҵ� 
	printf("\nFuzzy search by name's initial letter\n");
	printf("Please prese the initial letter of the student's name you want:\n");
	scanf("%s",searchname);//����Ҫ����������
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(searchname[0]==p[i].name[0])
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//����ҵ� 
		}
	} 
	if(flag==1)
	{
		printf("Found!\n");
	}
	if(flag==0)
	{
		printf("Not found!\n");
	} 
	GoMeun(p);	 
}


/*
  ����������ѧ���ɼ�������� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void AnalyseCourse(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	int i,k;//����ѭ������Ĳ���
	printf("\nStatistic analysis for every course\n");
	printf("\t����\t\t\t����\t\t\t�е�\t\t\t����\t\t\t������\t\t\t\n");
	printf("\tnumber\tpercent\t\tnumber\tpercent\t\tnumber\tpercent\t\tnumber\tpercent\t\tnumber\tpercent\n");
	int stupercent[5]={0};
	for(i=0;i<subjectnum;i++)
	{
		printf("%d",i+1);
		for(k=0;k<studentnum;k++)
		{
			if(p[k].pscore[i]<=100&&p[k].pscore[i]>=90)
			{
				stupercent[0]+=1;
			}
			else if(p[k].pscore[i]<90&&p[k].pscore[i]>=80)
			{
				stupercent[1]+=1;
			}
			else if(p[k].pscore[i]<80&&p[k].pscore[i]>=70)
			{
				stupercent[2]+=1;
			}
			else if(p[k].pscore[i]<70&&p[k].pscore[i]>=60)
			{
				stupercent[3]+=1;
			}
			else if(p[k].pscore[i]<60&&p[k].pscore[i]>=0)
			{
				stupercent[4]+=1;
			}
	    }
		printf("\t%d\t%.2f%%",stupercent[0],(float)stupercent[0]/studentnum*100);
		printf("\t\t%d\t%.2f%%",stupercent[1],(float)stupercent[1]/studentnum*100);	
		printf("\t\t%d\t%.2f%%",stupercent[2],(float)stupercent[2]/studentnum*100);
		printf("\t\t%d\t%.2f%%",stupercent[3],(float)stupercent[3]/studentnum*100);		
		printf("\t\t%d\t%.2f%%\n",stupercent[4],(float)stupercent[4]/studentnum*100);									
	
    	for(k=0;k<5;k++)
    	{
    		stupercent[k]=0;
		}
	}
	GoMeun(p);
}


/*
  ����������ѧ��������Ϣ�б���� 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� psum��ѧ���ֵܷ�ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� int psum 
  ����ֵ�� void
*/ 
void ListRecord(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
		    InputData(p);
		}		
	int i,m,k;//����ѭ������
	printf("\nList record\n");
	printf("\tname\tID\t\tscore\n");
	printf("\t\t\t\t");
	for(m=0;m<subjectnum;m++)
	{
		printf("%d\t",m+1);//�ñ�ʾ��Ŀ��� 
	}
	printf("\n");
	for(i=0;i<studentnum;i++)
	{
		printf("\t%s\t%lld",p[i].name,p[i].studentID);
		for(k=0;k<subjectnum;k++)
		{
			printf("\t%d",p[i].pscore[k]);
		}	
		printf("\n");
	}
	GoMeun(p);
}



/*
  �����������ļ�д��ѧ����Ϣ 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void WriteFile(STUDENT *p)
{
	int i,k;//�½�ѭ������ 
	FILE *fp = fopen(FILE_NAME,"w");//�½��ļ�����ΪFILE_NAME 
	if(fp == NULL)//��֤�ļ��Ƿ񴴽��ɹ���δ�ɹ��򷵻����˵� 
	{
		printf("Failed to create a file!\n");
		option(p);
	} 
	for(i=0;i<studentnum;i++)//���ν���Ӧ��Ϣд���ļ� 
	{
		fprintf(fp,"%s ",p[i].name);
		fprintf(fp,"%lld ",p[i].studentID);
        for(k=0;k<subjectnum;k++)
        {
        	fprintf(fp,"%d ",p[i].pscore[k]);
		}
	}
	fclose(fp);//�ر��ļ� 
	printf("The data have been saved!\n");
	option(p);//�������˵� 
}


/*
  �����������ļ�����ѧ����Ϣ 
  ��ڲ����� pstu ��ʾ����ѧ��������Ϣ�Ľṹ��ָ�� 
  ���ڲ����� STUDENT *pstu �ṹ��ָ�� 
  ����ֵ�� void
*/ 
void ReadFile(STUDENT *p)
{
	int i,k;//�½�ѭ������ 
	FILE *fp = fopen(FILE_NAME,"r");
	if(fp == NULL)//��֤�ļ��Ƿ�򿪳ɹ���δ�ɹ��򷵻����˵� 
	{
		printf("Failed to open a file!\n");
		option(p);
	}
	for(i=0;i<studentnum;i++)//���ν���Ӧ��Ϣ���ļ����� 
	{
		fscanf(fp,"%s ",p[i].name);
		fscanf(fp,"%lld ",&p[i].studentID);
        for(k=0;k<subjectnum;k++)
        {
        	fscanf(fp,"%d ",&p[i].pscore[k]);
		}
	}
	fclose(fp);//�ر��ļ� 
	printf("The data have been read!\n");
	flaginput=1;	
	option(p);//�������˵� 
}


/*
  �����������˳�������л 
  ��ڲ�����void 
  ���ڲ����� void 
  ����ֵ�� void
*/ 
void ThankUse(void)
{
	int i;//����ѭ���Ĳ�����
	printf("\n\n*************************************************\n"
	       "Thank you for using the grade management system!\n"
	       "author�������� 22L0214 2022113523\n"
	       "BYE-BYE*******BYE-BYE*******BYE-BYE*******BYE-BYE\n"
	       "*************************************************\n\n"
		   "     ********    **    **     ********    **\n"
		   "     *    **      **  **      *    **     **\n"
		   "     ******         **        ******      **\n"
		   "     ******         **        ******      **\n"
		   "     *    **        **        *    **\n"
		   "     ********       **        ********    **\n\n"
		   "*************************************************\n\n");
	for(i=0;i<5;i++)
	{
		printf("%c",audio);//������Ч 
	} 
	exit(1);
}
