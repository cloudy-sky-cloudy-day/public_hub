//学生成绩管理系统 
//作者：周子云 22L0214 2022113523 

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h> 
#define FILE_NAME "成绩名单.txt"
#define FILE_NAME2 "TEMP.txt"

typedef struct student//定义结构体数据类型  ，准备使用结构体数组
	{
		char name[20];//字符数组长度保证能储存下中文或英文名 
		long long studentID;//使用long long储存学号，防止过长数据溢出 
		int *pscore;//准备使用动态数组 
	}STUDENT;//设置struct student的别名，方便输入

struct link//定义链表的结构体 ，使用链表 
	{
		char stuname[20];
		long long int stuID;
		struct link *next;//使用链表 
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
 

int optionnum;//将选项定义为全局变量方便多个函数中使用 
int studentnum;
int subjectnum;//将学生人数定义为全局变量方便多个函数中使用 
int flaginput = 0;//用于记录是否已读入数据，如果没有读入数据，不允许使用其他功能
char judgeexit = 'Y';//判断是否退出程序 
char audio = '\007';//用于发出音效 
int firstchoose;//选择数据输入方式 


int main(void)
{
 	SnowWelcome();//展示欢迎界面 
 	int i,k;//循环体所需参数 

    struct link *head = NULL;//链表头指针 
 	STUDENT *pstu = NULL;//结构体指针 
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
  功能描述：添加链表节点 
  入口参数： struct link *head头节点指针 
  出口参数： struct link *head
  返回值： STUDENT *pstu 
*/ 	
STUDENT *AppendNode(struct link *head)
{
    STUDENT *pstu = NULL;
	char name[20];
	long long ID;
	int score;
	struct link *p =NULL,*pr = head;
	int data;
	p=(struct link *)malloc(sizeof(struct link));//动态表示 
	if(p == NULL)//看p是不是空的 
	{
		printf("No enough memory to allocate!\n");
		exit(0);
	}
	if(head == NULL)//如果头节点是空的 
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
  功能描述：用于选择数据输入方式 
  入口参数： struct link *head链表头指针，pstu 表示包含学生所有信息的结构体指针 
  出口参数： struct link *head,STUDENT *pstu
  返回值： STUDENT *pstu 
*/ 	 
STUDENT *ChooseFirst(struct link *head,STUDENT *pstu)
{
	int i;//循环参数 
	printf("Please to choose the way to input data:\n"
	       "1.Via node\n"
		   "2.Via file/Integral input\n");
		   scanf("%d",&firstchoose);
	while(firstchoose!=1&&firstchoose!=2)
	{
		printf("Sorry,this is an illeagal input!\n");//防止非法输入 
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
		pstu[i].pscore = (int*)malloc(subjectnum * sizeof(int));//使用动态数组
		if(pstu[i].pscore == NULL)//确保指针使用前是非空指针，当p为空指针时结束程序运行 
		{
			printf("No enough memory!\n");
			exit(1);
		}
	}
	return pstu; 

}

/*
  功能描述：用于第一次进入菜单 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
*/ 
void GoMeunFirst(STUDENT *pstu)
{
	int op;
	printf("%c",audio);//发出音效
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
  功能描述：用于只后再次进入菜单 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
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
  功能描述：产生一个随机数 
  入口参数： void 
  出口参数： void 
  返回值： int 一个范围在2-13的整型随机数 
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
  功能描述：用于菜单的导航 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
*/ 
void option(STUDENT *pstu)
{
	printf("%c",audio);//发出音效
	printf("\n\n");
	ChooseOption();//打印选择界面
   	switch(optionnum)//已检测数据正确性，所以不需要default 
	{
		case 1:InputData(pstu); break;  //第一次必须输入数据才能进行以下操作
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
  功能描述：用于展示欢迎界面 
  入口参数： void 
  出口参数： void 
  返回值： void
*/ 
void SnowWelcome(void)
{
	int i;//用作循环的参数； 
	printf("Welcome to use the grade management system!\n"
		   "author：周子云 22L0214 2022113523\n"
	       "*******************************************\n"
		   "      **      **     ********   **\n"
		   "      **      **        **      **\n"  
		   "      **********        **      **\n"
		   "      **      **        **        \n"
		   "      **      **     ********   **\n\n"
		   "*******************************************\n");
	for(i=0;i<5;i++)
	{
		printf("%c",audio);//发出音效 
	} 
	
}


/*
  功能描述：展示第二次及之后的选择页面 
  入口参数： void 
  出口参数： void 
  返回值： void
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
  功能描述：检测输入的选项数是否合法 
  入口参数： optionnum 选项数 
  出口参数： int optionnum 
  返回值： int 返回1表示合法，返回0表示不合法 
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
  功能描述：用于读入学生人数 
  入口参数： void 
  出口参数： void
  返回值： STUDENT *pstu 
*/ 	
STUDENT *ReadStudent(void)
{
	STUDENT *pstu = NULL;//定义STUDENT类型空指针 
	printf("How many student?\n");//读入学生个数 
	scanf("%d",&studentnum);
	pstu = (STUDENT*)malloc((studentnum+1) * sizeof(STUDENT));// 使用动态数组,+1为储存临时量 
	if(pstu == NULL)//确保指针使用前是非空指针，当p为空指针时结束程序运行 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	return pstu;	
	
	
/*
  功能描述：询问是否添加链表节点 
  入口参数： struct link *head头节点指针 
  出口参数： struct link *head
  返回值： STUDENT *pstu 
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
  功能描述：将链表数据输出 
  入口参数： struct link *head头节点指针 
  出口参数： struct link *head
  返回值： STUDENT *pstu 
*/ 	
STUDENT *SaveFile(struct link *head)
{
	struct link *p = head;
    STUDENT *pstu = NULL;
	int j = 0;
	int i,k;//新建循环参数 
	FILE *fp = fopen(FILE_NAME2,"w");//新建文件，名为FILE_NAME2 
	if(fp == NULL)//验证文件是否创建成功，未成功则返回主菜单 
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
	fclose(fp);//关闭文件
	studentnum = j; 
	pstu = (STUDENT*)malloc((studentnum+1) * sizeof(STUDENT));// 使用动态数组,+1为储存临时量 
	FILE *fp2 = fopen(FILE_NAME2,"r");
	if(fp == NULL)//验证文件是否打开成功，未成功则返回主菜单 
	{
		printf("Failed to open a file!\n");
		exit(0);
	}
	for(i=0;i<studentnum;i++)//依次将相应信息从文件读入 
	{
		fscanf(fp,"%s ",pstu[i].name);
		fscanf(fp,"%lld ",&pstu[i].studentID);
	}
	fclose(fp);//关闭文件 
	printf("The data have been read!\n\n\n");
	flaginput=1;
	return pstu;	 
}


/*
  功能描述：用于数据输入 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
*/ 
void InputData(STUDENT *p)
{
	if(flaginput==1)
	{
		fflush(stdin);//清空缓冲区 
		printf("You have input data,would you like to input again?(Y/N)\n");//防止误输入数据 
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
	int i,k;//循环中的参数 
	printf("Please input as \"NAME STUDENTID SCORE1 SCORE2...  \"IN EACH LINE\n");
	printf("Press enter to press another student's information\n");
	printf("For example: ZZY 2022113523 100 100 100\n");
	for(i=0;i<studentnum;i++)
	{
		scanf("%s",p[i].name);
		scanf("%lld",&p[i].studentID);//防范输入不是数字 
		for(k=0;k<subjectnum;k++)
		{
			scanf("%d",&p[i].pscore[k]);
		}
	} 
	flaginput=1;
	option(p);
}


/*
  功能描述：用于学生按课程平均分的计算 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
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
	psum = (int*)malloc(subjectnum * sizeof(int));// 使用动态数组 
	if(psum == NULL)//确保指针使用前是非空指针，当p为空指针时结束程序运行 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	int i,k,m;//定义循环中所用参数
	for(i=0;i<subjectnum;i++)
	{
		psum[i]=0;
		for(k=0;k<studentnum;k++)
		{
			psum[i]+=p[k].pscore[i];
		}
	} 
	printf("\tsum\taverage\n");//制表 
	for(m=0;m<subjectnum;m++)
	{
		printf("\t%d\t%.2f\n",psum[m],(float)psum[m]/studentnum);
	}
	free(psum);
	GoMeun(p);
}


/*
  功能描述：用于计算学生总分 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： 指向学生总分的指针*psum 
*/ 
int *TotalStudent(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	int *psum = NULL;
	psum = (int*)malloc(studentnum * sizeof(int));// 使用动态数组 
	if(psum == NULL)//确保指针使用前是非空指针，当p为空指针时结束程序运行 
	{
		printf("No enough memory!\n");
		exit(1);
	}
	int i,k;//定义循环中所用参数
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
  功能描述：打印出学生按课程的平均分 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void PrintAverStudent(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nTotal and average score of every student\n");
	int m;//定义循环参数 
	printf("\tname\tID\t\tsum\taverage\n");//制表 
	for(m=0;m<studentnum;m++)
	{
		printf("\t%s\t%lld\t%d\t%.2f\n",p[m].name,p[m].studentID,psum[m],(float)psum[m]/subjectnum);
	}
	free(psum); 
	GoMeun(p);
}


/*
  功能描述：学生课程总分降序排列 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void OrderDescendTotal(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!");
			InputData(p);
		}		
	printf("\nSort in descending order by total score of every student\n");
	int i,m,k,w;//定义循环参数
	int temp = 0;//定义临时变量 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(psum[m]<psum[i])
			{
				p[studentnum].studentID=p[m].studentID;//以数组最后多出的一项储存临时量 
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
  功能描述：学生课程总分升序排列 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void OrderAscendTotal(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in ascending order by total score of every student\n");
	int i,m,k,w;//定义循环参数
	int temp = 0;//定义临时变量 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(psum[m]<psum[i])
			{
				p[studentnum].studentID=p[m].studentID;//以数组最后多出的一项储存临时量 
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
  功能描述：学生学号升序排列 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void OrderAscendNum(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in ascending order by number\n");
	int i,m,k,w;//定义循环参数
	int temp = 0;//定义临时变量 
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(p[m].studentID<p[i].studentID)
			{
				p[studentnum].studentID=p[m].studentID;//以数组最后多出的一项储存临时量 
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
  功能描述：学生姓名字典序排列 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void OrderDicName(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	printf("\nSort in dictionary order by name\n");
	int i,m,k,w;//定义循环参数
	int temp = 0;//定义临时变量	
	for(i=0;i<studentnum-1;i++)
	{
		for(m=i+1;m<studentnum;m++)
		{
			if(strcmp(p[m].name,p[i].name)<0)
			{
				p[studentnum].studentID=p[m].studentID;//以数组最后多出的一项储存临时量 
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
  功能描述：按学号查找学生 
  入口参数： pstu 表示包含学生所有信息的结构体指针
  出口参数： STUDENT *pstu  
  返回值： void
*/ 
void SearchNum(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	long long stunum;//用long long表示要搜索的学号 
	int i,flag=0;//定义循环参数 ，定义flag标记是否找到 
	printf("\nSearch by number\n");
	printf("Please prese the student's ID you want:\n");
	scanf("%lld",&stunum);//输入要搜索的学号
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(p[i].studentID-stunum==0)
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//标记找到 
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
  功能描述：按姓名查找学生名 
  入口参数： pstu 表示包含学生所有信息的结构体指针  
  出口参数： STUDENT *pstu 结构体指针
  返回值： void
*/ 
void SearchName(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	char searchname[20];//用字符数组表示要搜索的名字 
	int i,flag=0;//定义循环参数 ，定义flag标记是否找到 
	printf("\nSearch by name\n");
	printf("Please prese the student's name you want:\n");
	scanf("%s",searchname);//输入要搜索的名字
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(strcmp(searchname,p[i].name)==0)
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//标记找到 
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
  功能描述：按姓名首字母模糊查找学生名 
  入口参数： pstu 表示包含学生所有信息的结构体指针  
  出口参数： STUDENT *pstu 结构体指针
  返回值： void
*/ 
void SearchNameFuzzy(STUDENT *p)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	char searchname[20];//用字符数组表示要搜索的名字 
	int i,flag=0;//定义循环参数 ，定义flag标记是否找到 
	printf("\nFuzzy search by name's initial letter\n");
	printf("Please prese the initial letter of the student's name you want:\n");
	scanf("%s",searchname);//输入要搜索的名字
	printf("\tname\tID\n");
	for(i=0;i<studentnum;i++)
	{
		if(searchname[0]==p[i].name[0])
		{
			printf("\t%s\t%lld\n",p[i].name,p[i].studentID);
			flag=1;//标记找到 
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
  功能描述：学生成绩区间分析 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void AnalyseCourse(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
			InputData(p);
		}		
	int i,k;//定义循环所需的参数
	printf("\nStatistic analysis for every course\n");
	printf("\t优秀\t\t\t良好\t\t\t中等\t\t\t及格\t\t\t不及格\t\t\t\n");
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
  功能描述：学生所有信息列表输出 
  入口参数： pstu 表示包含学生所有信息的结构体指针 psum向学生总分的指针 
  出口参数： STUDENT *pstu 结构体指针 int psum 
  返回值： void
*/ 
void ListRecord(STUDENT *p,int *psum)
{
	if(flaginput==0)
		{
		    printf("You haven't input any data!"); 
		    InputData(p);
		}		
	int i,m,k;//定义循环参数
	printf("\nList record\n");
	printf("\tname\tID\t\tscore\n");
	printf("\t\t\t\t");
	for(m=0;m<subjectnum;m++)
	{
		printf("%d\t",m+1);//用表示科目序号 
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
  功能描述：文件写入学生信息 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
*/ 
void WriteFile(STUDENT *p)
{
	int i,k;//新建循环参数 
	FILE *fp = fopen(FILE_NAME,"w");//新建文件，名为FILE_NAME 
	if(fp == NULL)//验证文件是否创建成功，未成功则返回主菜单 
	{
		printf("Failed to create a file!\n");
		option(p);
	} 
	for(i=0;i<studentnum;i++)//依次将相应信息写入文件 
	{
		fprintf(fp,"%s ",p[i].name);
		fprintf(fp,"%lld ",p[i].studentID);
        for(k=0;k<subjectnum;k++)
        {
        	fprintf(fp,"%d ",p[i].pscore[k]);
		}
	}
	fclose(fp);//关闭文件 
	printf("The data have been saved!\n");
	option(p);//返回主菜单 
}


/*
  功能描述：文件读入学生信息 
  入口参数： pstu 表示包含学生所有信息的结构体指针 
  出口参数： STUDENT *pstu 结构体指针 
  返回值： void
*/ 
void ReadFile(STUDENT *p)
{
	int i,k;//新建循环参数 
	FILE *fp = fopen(FILE_NAME,"r");
	if(fp == NULL)//验证文件是否打开成功，未成功则返回主菜单 
	{
		printf("Failed to open a file!\n");
		option(p);
	}
	for(i=0;i<studentnum;i++)//依次将相应信息从文件读入 
	{
		fscanf(fp,"%s ",p[i].name);
		fscanf(fp,"%lld ",&p[i].studentID);
        for(k=0;k<subjectnum;k++)
        {
        	fscanf(fp,"%d ",&p[i].pscore[k]);
		}
	}
	fclose(fp);//关闭文件 
	printf("The data have been read!\n");
	flaginput=1;	
	option(p);//返回主菜单 
}


/*
  功能描述：退出程序致谢 
  入口参数：void 
  出口参数： void 
  返回值： void
*/ 
void ThankUse(void)
{
	int i;//用作循环的参数；
	printf("\n\n*************************************************\n"
	       "Thank you for using the grade management system!\n"
	       "author：周子云 22L0214 2022113523\n"
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
		printf("%c",audio);//发出音效 
	} 
	exit(1);
}
