#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>//美化控制台程序
#include<stdio.h>
#include<stdlib.h>//主要用于调用system函数
#include<string.h>
#include<conio.h>//主要用于调用getch函数

//人员信息结构体
struct tex1         //字符串数组初始化一个0可以防止空输入时的内存泄露甚至程序崩溃
{
	char name[250] = { 0 };//人名       
	char office[250] = { 0 };//单位
	char telephone[250] = { 0 };//固定电话 
	char smartphone[250] = { 0 };//移动电话 
	char type[250] = { 0 };//分类
	char email[250] = { 0 };//电子邮件 
	char qq[250] = { 0 };//QQ
	char mark[20] = { 0 };//常用联系人的标志
};

//用于创建链表的结构体
struct tex
{
	struct tex1 tex1;//联系人信息结构体 
	struct tex* next;//后趋指针
};

//用于创建页面信息的结构体
struct page
{
	struct page* previous = NULL;//上一页位置

	struct tex* stu[9];//用数组每9个存储每个成员的指针，并从通讯录列表获取成员信息

	struct page* next = NULL;//下一页位置
};

//以下相似部分为函数声明

int maincai();//主菜单显示函数

int filetest();//通讯录文件判空函数

void create();//初始联系人录入函数

void adding();//增加联系人母函数

void add2();//增加联系人子函数

void finding();//查找联系人函数

struct page* search_v3(struct tex* head, char search_name[250]);//模糊搜索模块

int del(struct tex* p, struct tex* head_member);//删除联系人模块

void changing(struct tex* q,struct tex* head_member);//修改联系人模块

struct page* addpage();//页面创建函数

int culpage();//页码计算函数

struct tex* show(char search_name[250], struct page* head_page);//分页显示函数

void inizaize();// 初始化通讯录函数
 
struct tex* reading();//文件传入链表函数

void writing(struct tex* head);//链表写入文件函数

void display(struct tex* gp,int i);//显示单独联系人函数

void destroy(struct tex* head);//链表销毁函数

void often();//常用联系人函数

void often_out(struct tex* q, struct tex* head_member);//常用联系人移出模块

void often_in(struct tex* q, struct tex* head_member);//常用联系人移入模块

struct page* often_distinguish(struct tex* head, char mark[20]);//常用联系人判定模块

int exiting();    //用户退出确认函数

int people;//全局变量，用于记录录入人数

//主函数
//当程序被第一次打开时创建储存文件并在未退出的情况下循环所有功能选择
int main() {
	system("color F1");          //调整控制台背景色与文字颜色

	FILE* fpq, * fpz, * file;    //从这里开始的部分用于检测用户是否为第一次打开程序，ifer.dat仅用于做标记
	file = fopen("ifer.dat", "r");
	if (file == NULL) {
		fpz = fopen("tencures.txt", "w+"); fclose(fpz);
	}
	fpq = fopen("ifer.dat", "w+");
	fclose(fpq);                 //接上一注释所表示的范围
	                  
	int menu,pan=0;             //menu用于调用显示主菜单函数,pan用于判断用户的退出意愿
	char ch,s[]="/e";          //记录用户的功能选择，/e是常用联系人的副标记
	menu = maincai();         //显示主菜单
	printf("\t\t\t\t请用数字选择您需要的功能：");
	do {
		ch = _getch();
		switch (ch)
		{
		case '1': system("cls"); adding(); system("cls"); menu = maincai(); //新增联系人
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		case '2': system("cls"); finding(); system("cls"); menu = maincai(); //查找联系人
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		case '3': system("cls"); often(); system("cls"); menu = maincai(); //常用联系人
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		case '4':system("cls"); show(s, NULL); system("cls"); menu = maincai(); //查看所有联系人
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		case '5':system("cls"); inizaize(); system("cls"); menu = maincai(); //初始化联系人
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		case '6': system("cls"); pan = exiting();  if (pan == 1) { break; }system("cls"); menu = maincai(); //退出系统
			printf("\t\t\t\t请用数字选择你需要的功能："); break;

		default: system("cls");  menu = maincai(); 
			printf("\t\t\t\t请输入正常的功能数字：\a"); break; //防止用户输入异常的功能数字
		}
	} while (pan != 1 );
            printf("\n\n\n\n\n\n\n\t\t\t\t您已成功退出系统！\n\n\n\n\n\n\n\n\t\t\t\t");
	return 0;
}

//检测通讯录文件是否为空的函数
//用于阻止通讯录为空时用户使用查找，查看等功能从而造成潜在的崩溃
int filetest()
{
	FILE* fp;
	fp = fopen("tencures.txt", "r");
	getc(fp);//feof函数生效的前提是至少读取文件中的一个字符
	if (feof(fp))
	{
		printf("\n\n\n\n\n\n\n\t\t\t\t当前通讯录为空，请先录入联系人\n\n\t\t\t\t");
		system("pause");
		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return 0;
	}
}

//退出确认模块
 int exiting() {
	int pan=0;
	char ch;
	printf("\n\n\n\n\n\n\n\t\t\t\t您确认要退出程序吗？\n");
	printf("\t\t\t\t----------------------------------\n");
	printf("\t\t\t\t1.是\n\t\t\t\t2.否\n");
	do {
        ch = _getch();
		switch (ch) {
		case '1': system("cls"); pan = 1; goto ending;
		case '2':system("cls"); pan = 2; goto ending;
		default:system("cls"); 
			printf("\n\n\n\n\n\n\n\t\t\t\t您确认要退出程序吗？\n\t\t\t\t----------------------------------\n\t\t\t\t1.是\n\t\t\t\t2.否\n\n"); 
			printf("\n\n\n\n\n\n\n\t\t\t\t请输入正确的选项\n"); break;
		}
	} while (1);
	ending:
	return pan;
}

//主菜单显示
int maincai() { 
	printf("\n\n\n\n\n\n\n");
	printf("\t\t\t\t欢迎使用本通讯录！\n");
	printf("\t\t\t\t--------------------------------------------------------------\n");
	printf("\t\t\t\t|                 1.新增联系人                               |\n");
	printf("\t\t\t\t|                 2.查找联系人                               |\n");
	printf("\t\t\t\t|                 3.常用联系人                               |\n");
	printf("\t\t\t\t|                 4.查看联系人                               |\n");
	printf("\t\t\t\t|                 5.初始化通讯录                             |\n");
	printf("\t\t\t\t|                 6.退出系统                                 |\n");
	printf("\t\t\t\t--------------------------------------------------------------\n");
	return 0;
}

//初始联系人录入 
//第一次录入使用边输入信息边储存的方式，避免空文件与空链表所带来的麻烦
void create()
{
	FILE* fp;
	char n1,n2,oi;            //n1用于判断用户是否需要继续录入联系人，n2用于判断用户是否需要直接退出，oi用于判断是否输入空名字
	struct tex1 tex1;        //创建结构体以储存联系人信息
	struct tex *p2;         //p2用于为单独显示函数传递实时的数据指针，以通过单独显示函数实现良好的界面输出效果
	int i=0, mem = 1;      //i用于显示已录入联系人个数，mem用于移动写入文件的光标

	fp = fopen("tencures.txt", "w"); //此部分为打开文件
	if (!fp)
	{
		printf("cannot open file\n");
		exit(0);
	}                               //接上一注释

	printf("\n\n\n\n\n\t\t\t\t按1新建联系人，按e退出");  //此部分为判断用户是否需要直接退出，使用goto语句来进行跳转
	while (1) {
        n2 = _getch();
		switch (n2) {
		case 'e':system("cls"); goto end;
		case '1':system("cls"); goto begin;
		default: system("cls"); printf("\n\n\n\n\n\t\t\t\t请输入正确的选项！\n\n\t\t\t\t"); system("pause");
			system("cls"); printf("\n\n\n\n\n\t\t\t\t按1新建联系人，按e退出"); break;
		}
	}                                  //接上一注释

begin:               // 录入的起始跳转节点
	p2 = (struct tex*)malloc(sizeof(struct tex));
	
	    tex1.name[0] = '\0';//防止空输入时造成乱码
	    tex1.office[0] = '\0';
	    tex1.telephone[0] = '\0';
	    tex1.smartphone[0] = '\0';
	    tex1.type[0] = '\0';
	    tex1.email[0] = '\0';
        tex1.qq[0] = '\0';
		tex1.mark[0] = '\0';
		

	   //此部分一步步录入数据并写入文件，使用[^\n]来保证可以输入空格
		i++;                           
	name:                //重新输入名字的跳转节点
		p2->tex1 = tex1;//更新显示信息
		display(p2, i);

		printf("请输入姓名：");
		scanf("%[^\n]", tex1.name);
		getchar();                    //getchar用于吸收缓冲区中的回车
		if (!strcmp(tex1.name, "\0"))//对输入名字为空选择，如果命名为空会影响分页显示函数的运行
		{
			system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入姓名为空，是否确认输入?\n"); 
			printf("\n\t\t\t\t----------------------------------\n"); 
			printf("\t\t\t\t确认（y）  重新输入（其他键）\n"); 
			oi = _getch(); system("cls"); if (oi != 'y') goto name;
			else
			{
				strcpy(tex1.name, "未命名");
			}
		}

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入单位：");
		scanf("%[^\n]", tex1.office);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入固定电话：");
		scanf("%[^\n]", tex1.telephone);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入移动电话：");
		scanf("%[^\n]", tex1.smartphone);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入分类：");
		scanf("%[^\n]", tex1.type);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入电子邮件：");
		scanf("%[^\n]", tex1.email);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		printf("请输入QQ：");
		scanf("%[^\n]", tex1.qq);
		getchar();

		p2->tex1 = tex1;
		display(p2, i);
		fprintf(fp, "%d.", mem);
		fprintf(fp, "%s\n\n单位：%s\n固定电话：%s\n移动电话：%s\n分类：%s\n电子邮件：%s\nQQ：%s\n标志：%s\n\n",
			tex1.name, tex1.office, tex1.telephone, tex1.smartphone, tex1.type, tex1.email, tex1.qq,tex1.mark);
		mem++;      //接上一注释
		
		system("pause");
		system("cls");
		while (1) {   
			printf("\n\n\n\n\n\n\n\t\t\t\t您还需要继续添加吗？");          //此部分判断用户是否需要继续录入，使用goto语句来进行跳转
			printf("\n\t\t\t\t----------------------------------\n");
			printf("\t\t\t\t1.是\n\t\t\t\t2.否\n");         
			n1 = _getch();
			switch (n1) {
			case '1':system("cls"); goto begin;
			case '2':system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t联系人添加成功.\n\n\n\n\n\n\n\n\t\t\t\t"); system("pause"); system("cls"); goto end;
			default:system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t请输入正确的选项\n\n\n\n\n\n\n\t\t\t\t"); system("pause"); system("cls"); break;
			}
		}                                              //接上一注释

    end:              //所有录入都已结束的跳转节点
	fclose(fp);
}

//增加联系人母函数 	
//通过判断通讯录文件是否为空来决定是调用初始录入函数还是增加函数
//将两种输入情况进行区分主要是为了避免空文件和空链表所带来的不必要的麻烦
void adding() {         
	char ch;           
	FILE* fp;
	fp = fopen("tencures.txt", "r");
	ch = fgetc(fp);
	if (ch == EOF){
		create();
	}
	else{
		add2();
	}
	fclose(fp);
}

//增加联系人子函数
//先读取文件并创建链表，用户更改链表，最后覆盖写入文件
void add2()
{
	int i=0;              //i用于显示已录入联系人个数
	char n1,n2,oi;          //n1用于判断用户是否需要继续录入联系人，n2用于判断用户是否需要直接退出,oi用于判断是否输入空名字
	struct tex* p1 = NULL, * head = NULL, * p2;   //分别为跳转指针，头指针和尾指针
	system("cls");
	head = reading();   //从文件读取数据 

	printf("\n\n\n\n\n\t\t\t\t按1新建联系人，按e退出");        //此部分为判断用户是否需要直接退出，使用goto语句来进行跳转	
	while (1) {
        n2 = _getch();
		switch (n2) {
		case 'e':system("cls");  goto end1;
		case '1':system("cls"); goto begin;
		default:system("cls"); printf("\n\n\n\n\n\t\t\t\t请输入正确的选项！\n\n\t\t\t\t"); system("pause"); 
			system("cls"); printf("\n\n\n\n\n\t\t\t\t按1新建联系人，按e退出"); 
		}
	}                                        //接上一注释

	    begin:       // 输入的起始跳转节点
	               
		p2 = (struct tex*)malloc(sizeof(struct tex));//此部分一步步录入数据并写入文件，使用[^\n]来保证可以输入空格
		
		p2->tex1.name[0] = '\0'; //此处防止空输入时造成乱码
		p2->tex1.office[0] = '\0';
		p2->tex1.telephone[0] = '\0';
		p2->tex1.smartphone[0] = '\0';
		p2->tex1.type[0] = '\0';
		p2->tex1.email[0] = '\0';
		p2->tex1.qq[0] = '\0';
		p2->tex1.mark[0] = '\0';

		i++;
	name:              //重新输入名字的跳转节点
		display(p2,i);//更新显示信息
		printf("请输入姓名：");
		scanf("%[^\n]", p2->tex1.name);
		getchar();    //getchar用于吸收缓冲区中的回车
		if (!strcmp(p2->tex1.name, "\0"))//对输入名字为空选择，如果命名为空会影响分页函数的运行
		{
			system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入姓名为空，是否确认输入?\n"); 
			printf("\n\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认（y）  重新输入（其他键）\n"); 
			oi = _getch(); system("cls"); if (oi != 'y') goto name;
			else
			{
				strcpy(p2->tex1.name, "未命名");
			}
		}

		display(p2, i);
		printf("请输入单位：");
		scanf("%[^\n]", p2->tex1.office);
		getchar();

		display(p2, i);
		printf("请输入固定电话：");
		scanf("%[^\n]", p2->tex1.telephone);
		getchar();

		display(p2, i);
		printf("请输入移动电话：");
		scanf("%[^\n]", p2->tex1.smartphone);
		getchar();

		display(p2, i);
		printf("请输入分类：");
		scanf("%[^\n]", p2->tex1.type);
		getchar();

		display(p2, i);
		printf("请输入电子邮件：");
		scanf("%[^\n]", p2->tex1.email);
		getchar();

		display(p2, i);
		printf("请输入QQ：");
		scanf("%[^\n]", p2->tex1.qq);
		getchar();

		display(p2, i);
											 
		p1 = head;                    //此部分为链表尾插添加数据
		while (p1->next != NULL)
			p1 = p1->next;
		p1->next = p2;
		p2->next = NULL;             //接上一注释
        writing(head);	//将数据写入文件

		system("pause");
		system("cls");
	while (1) {
		printf("\n\n\n\n\n\n\n\t\t\t\t您还需要继续添加吗？");          //此部分判断用户是否需要继续录入，使用goto语句来进行跳转
		printf("\n\t\t\t\t----------------------------------\n");
		printf("\t\t\t\t1.是\n\t\t\t\t2.否\n");
		n1 = _getch();
		switch (n1) {
		case '1':system("cls"); goto begin;
		case '2':system("cls");  goto end2;
		default:system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t请输入正确的选项\n\n\n\n\n\n\n\t\t\t\t"); system("pause"); system("cls"); break;
		}
	}                      //接上一注释
 
 end2://结束所有输入的跳转节点
	
	printf("\n\n\n\n\n\n\n\t\t\t\t联系人添加成功.\n\n\n\n\n\n\n\n\t\t\t\t");
	system("pause");
 end1:               //直接退出的跳转节点
	destroy(head);    //销毁链表，释放内存
}

//查找联系人母函数
//其核心为模糊搜索模块
void finding()
{
	struct tex* head = NULL;  //头指针
	struct page* p;          //为模糊搜索模块传递搜索关键字
	
	if (filetest())//检测文件是否为空
	{
		goto end;
	}
	head = reading();      //读取文件数据并创建链表 

	while (1) {
	begin:  //输入为空时的跳转节点
		printf("\n\n\n\n\n\n\n");
		printf("\t\t\t\t请输入查找的关键字,输入/e以退出\n");
		printf("\t\t\t\t-------------------------------\n\t\t\t\t");
		char  searches[250] = { '\0' };
		fflush(stdin);     //清空输入缓冲区，防止上一个关键字干扰当前的关键字
		scanf("%[^\n]", searches);
		getchar();

		if (!strcmp(searches, "/e"))   //判断用户是否输入/e以退出
			goto end;
		else if (!strcmp(searches, "")) //关键字判空
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t\t\t\t所输入内容为空，请重新输入!\n\n\t\t\t\t");
			system("pause");
			system("cls");
			goto begin;
		}

		p = search_v3(head, searches);  //调用模糊搜索模块，无结果则返回空
		if (p == NULL)
		{
			system("cls");
			printf("未找到相关联系人，请确认所输信息是否正确!\n\n");
			system("pause");
			system("cls");
		}
		else 
		{
			show(searches,p);  //以分页形式展示搜索结果
		}
	}

end:   //结束所有查找的跳转节点
	destroy(head);  //销毁链表，释放内存
}

//模糊搜索模块，使用strstr函数来实现模糊搜索
struct page* search_v3(struct tex*head,char search_name[250])
{
	struct tex* p1 = NULL, * p2 = NULL;            //p1，p2用于定位成员
	struct page* head_page=NULL,*aim_page=NULL,*previous_page=NULL;//head_page用于定位首页，aim_page用于定位页码
	p1 = p2 = head;                              //将p1、p2定位到第一个成员
	int i = 0, stui_last_member;                //i用于定位当前页成员位置，stui_last_member用于定位最后一个搜索到的成员
	
	while (p1 != NULL)
	{
		if (strstr(p1->tex1.name, search_name) || strstr(p1->tex1.office, search_name) || strstr(p1->tex1.telephone, search_name) || strstr(p1->tex1.smartphone, search_name)
			|| strstr(p1->tex1.type, search_name) || strstr(p1->tex1.email, search_name) || strstr(p1->tex1.qq, search_name))//搜索条件，如果符合条件则录入成员
		{

			//搜索刚开始进行时，需要开辟新页以及用head_page定位第一页，自此以下内容主要用于构造显示页面
			if (head_page == NULL)
			{
				head_page = aim_page = (struct page*)malloc(sizeof(struct page));
				aim_page->next = NULL;
			}

			//如果当前页录入的成员已满，开辟新页
			else if (i >= 9)
			{
				i = 0;
				previous_page=aim_page;//记录上一页
				aim_page->next= (struct page*)malloc(sizeof(struct page));
				aim_page = aim_page->next;
				aim_page->next = NULL;
				aim_page->previous = previous_page;
				previous_page = NULL;
			}

			//录入搜索到的成员所在内存位置（录入指针）
			if(aim_page!=NULL)
				aim_page->stu[i] = p1;
			stui_last_member = i;
			i++;
		}

		//定位到下一个成员
		p2 = p1;
		p1 = p1->next;
		
	}
	//对搜索到的成员的最后一页做处理
	if (aim_page != NULL)
	{
		aim_page->next = NULL;
		for (i = 8; i > stui_last_member; i--)//最后一页的处理
		{
			aim_page->stu[i] = (struct tex*)malloc(sizeof(struct tex));
			if(aim_page->stu[i]!=NULL)
				strcpy(aim_page->stu[i]->tex1.name, "");
		}
	}                  //接上一指针

	//返回首页指针
	return head_page;
}

//删除联系人模块
//主要通过定向覆写来实现删除
int del(struct tex* p, struct tex* head_member)
{
	char ch;    //ch用于确认删除的选择
	struct tex* aim_member=head_member;//aim_page用于定位第一个成员
retype:   //重载用户选择的跳转节点

	system("cls");
	
	display(p,-1);  //展示要删除的联系人并提供删除确认选项
	printf("确定删除该联系人?");
	printf("\n\t\t\t\t确定（y）  取消（n）\n");
	ch = _getch();
	if (ch == 'y')
		goto deling;
	else if (ch == 'n')
	{
		return 0;
	}
	else
	{
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t输入选项有误，请重新输入！\n");
		system("pause");
		system("cls");
		goto retype;
	}



deling:   //执行删除操作的跳转节点
	FILE* fp;
	int mem = 1;  //mem为文件中每个联系人前面的数字标号，与用户无关，主要用于程序检查

	if (!(fp = fopen("tencures.txt", "w")))  //打开文件
	{
		printf("cannot open file\n");
		exit(0);
	}

	//将被删除成员以外的成员信息覆盖写入文件，以实现删除的目的
	while (aim_member != NULL)
	{
		if (p != aim_member)
			if (strcmp(aim_member->tex1.name, ""))//写入文件条件：不是要删除的成员也不是名字为空的成员
			{
				//写入到文件
				fprintf(fp, "%d.", mem);
				fprintf(fp, "%s\n\n单位：%s\n固定电话：%s\n移动电话：%s\n分类：%s\n电子邮件：%s\nQQ：%s\n标志：%s\n\n",
					aim_member->tex1.name, aim_member->tex1.office, aim_member->tex1.telephone,
					aim_member->tex1.smartphone, aim_member->tex1.type, aim_member->tex1.email,
					aim_member->tex1.qq, aim_member->tex1.mark);
				mem++;
			}
		aim_member = aim_member->next;  //数据块跳转
	}
		fclose(fp);
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t删除成功！\n");
		printf("\n\t\t\t\t");
		system("pause");
		return 1;
		               //接上一注释
}

//修改联系人模块
void changing(struct tex* q,struct tex* head_member)
{
	char ch, oi;   //用于对修改项的选择

	while (1) {
		char  name[250] = { '\0' }, smartphone[250] = { '\0' }, office[250] = { '\0' }, type[250] = { '\0' };  //此处数组用于保存用户的修改信息
		char qq[250] = { '\0' }, telephone[250] = { '\0' }, email[250] = { '\0' };
	retype:              //重新输入的跳转节点
		system("cls");  //接上一注释
		display(q,-1); //显示修改前的信息

		printf("请选择您要修改的信息,退出修改请按0\n");
		printf("\t\t\t\t*------------------------------------------------*\n");
		printf("\t\t\t\t*1.修改联系人姓名          2.修改联系人单位      *\n");
		printf("\t\t\t\t*3.修改联系人固定电话      4.修改联系人移动电话  *\n");
		printf("\t\t\t\t*5.修改联系人分类          6.修改联系人电子邮箱  *\n");
		printf("\t\t\t\t*7.修改联系人QQ                                  *\n");
		printf("\t\t\t\t*------------------------------------------------*\n");
		ch = _getch();

		switch (ch)   //输入修改信息部分
		{
		case '1':printf("\t\t\t\t输入新的联系人姓名：");  scanf("%[^\n]", name); getchar();
			if (!strcmp(name, "\0"))      //对输入名字为空选择，如果命名为空会影响分页函数的运行
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入姓名为空，是否确认更改?\n");
				printf("\t\t\t\t----------------------------------\n");
				printf("\t\t\t\t确认 1  取消按其他键\n"); oi = _getch(); 
				system("cls"); if (oi != '1') goto retype;
				else
				{
					strcpy(q->tex1.name, "未命名");
					break;
				}
			}
			strcpy(q->tex1.name, name); break;

		case '2':printf("\t\t\t\t输入新的联系人单位：");  scanf("%[^\n]", office); getchar();
			if (!strcmp(office, "\0"))//对输入单位为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入单位为空，是否确认更改?\n"); 
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n");
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.office, office); break;

		case '3':printf("\t\t\t\t输入新的联系人固定电话："); scanf("%[^\n]", telephone); getchar();
			if (!strcmp(telephone, "\0"))//对输入固定电话为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入固定电话为空，是否确认更改?\n");
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n"); 
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.telephone, telephone); break;

		case '4':printf("\t\t\t\t输入新的联系人移动电话：");      scanf("%[^\n]", smartphone); getchar();
			if (!strcmp(smartphone, "\0"))//对输入移动电话为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入移动电话为空，是否确认更改?\n"); 
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n"); 
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.smartphone, smartphone); break;

		case '5':printf("\t\t\t\t输入新的联系人分类：");      scanf("%[^\n]", type); getchar();
			if (!strcmp(type, "\0"))//对输入分类为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入联系人分类为空，是否确认更改?\n"); 
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n"); 
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.type, type); break;

		case '6':printf("\t\t\t\t输入新的联系人电子邮箱：");      scanf("%[^\n]", email); getchar();
			if (!strcmp(email, "\0"))//对输入邮箱为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入电子邮箱为空，是否确认更改?\n");
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n");
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.email, email); break;

		case '7': printf("\t\t\t\t输入新的联系人QQ：");    scanf("%[^\n]", qq); getchar();
			if (!strcmp(qq, "\0"))//对输入QQ为空选择
			{
				system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t所输入QQ为空，是否确认更改?\n"); 
				printf("\t\t\t\t----------------------------------\n"); printf("\t\t\t\t确认 1  取消按其他键\n");
				oi = _getch(); system("cls"); if (oi != '1') goto retype;
			}
			strcpy(q->tex1.qq, qq); break;

		case '0':system("cls"); goto end;
		default:system("cls"); printf("\n\n\n\n\n\n\n\t\t\t\t输入错误，请重新输入!\n\t\t\t\t"); system("pause"); goto retype;
		}         //接上一注释

		writing(head_member);			//将修改后的信息存入文件
		system("cls");
		printf("\n\n\n\n\n\n\n\t\t\t\t修改成功!\n\n\t\t\t\t");
		system("pause");
	}
end:         //结束修改或直接退出的跳转节点
	printf("\n");
	system("cls");
}

//初始化通讯录
//此函数通过创建一个同名字的文件来覆盖原有的文件，由此完成初始化的功能
void inizaize() 
{
	char pan;  //用于读取用户选项
    printf("您确定要初始化通讯录吗，这将清空所有数据\n1.是\n2.取消\n");
	begin:   //起始跳转节点
	pan = _getch();
	switch (pan) {
	case '1': FILE * fp; fp = fopen("tencures.txt", "w+"); fclose(fp); system("cls");printf("初始化成功！\n\n");  system("pause"); break;
	case '2':break;
	default:system("cls"); printf("您确定要初始化通讯录吗，这将清空所有数据\n1.是\n2.取消\n"); printf("\n请输入正确的选项：\n"); goto begin;
	}
	printf("\n");
}

//页面创建函数
/*用文件读取链表函数录入人员信息链表->从人员信息链表当中抽取每九个人开辟一页，一路遍历以创建页面链表，
stu[x]是用于存储每个联系人成员结构体的指针数组，通过对它们的调用可以显示单独的联系人信息->一页用完之后，
记录上一页和下一页的位置（如果存在的话）->判断是否为最后一页，如果是则中断函数执行并返回首页指针，
否则另起一页，继续遍历联系人链表以创建新页*/
struct page* addpage()
{
	struct tex* reading();   //引用“文件数据传入链表”函数，创建联系人信息链表
	struct tex* aim_member; //成员定位指针
	aim_member = reading();//定位第一个成员的内存位置
	struct page* head_page = NULL/*头页码*/, * previous_page = NULL/*上一页页码（对下一页来说）*/, * aim_page = NULL/*页码定位指针*/;
	
	int stui, page, pagei, stui_last_member = -1, i;  
	//stui和i用于每页联系人信息的计数，page和pagei用于页面数量的计数， stui_last_member用于最后一页的联系人信息计数
	
	page = culpage();    //计算总页数
	
	//以下为为页面录入信息
	for (pagei = 0; pagei < page; pagei++)
	{
		aim_page = (struct page*)malloc(sizeof(struct page));//开辟新的页码
		if (aim_page != NULL)
		{
			if (head_page == NULL)
			{
				head_page = aim_page;//定位第一页的位置
			}
			else
			{
				aim_page->previous = previous_page;//记录上一页
				previous_page->next = aim_page;//让上一页“记住”下一页（就是本页）位置
				previous_page = NULL;
			}
			for (stui = 0; stui < 9; stui++)
			{
				aim_page->stu[stui] = aim_member;//录入成员地址
				if (aim_member->next != NULL)//检测是否为最后一个录入的成员
					aim_member = aim_member->next;
				else//如果是则记录最后一页最后一个成员的编号
				{
					stui_last_member = stui;
					for (i = 8; i > stui_last_member; i--)//最后一页的处理
					{
						aim_page->stu[i] = (struct tex*)malloc(sizeof(struct tex));
						if(aim_page->stu[i]->tex1.name)
							strcpy(aim_page->stu[i]->tex1.name, "");
					}
					break;
				}
			}

			previous_page = aim_page;//记录当前页指针，为下一页做准备
		}
	}

	//重置页面指针
	aim_page = NULL;
	previous_page = NULL;
	
	return(head_page);
}

//页码计算函数
//一页九个人
int culpage()  
{
	int page;
	page = people / 9;
	if (page == 0)
	{
		if (people != 0)
			page = 1;
	}
	else if (people % 9)
		page++;
	return page;
}

/*分屏显示函数，它是整个通讯录程序的功能枢纽，它既可以由用户调用修改和删除模块，也可以被查找模块和查看模块所调用
分页显示为用户带来了良好的使用体验
此函数有着几种不同的运行方式，通过特定的信号参数传入来激活特定的运行方式
显示运行方式：用addpage函数创建页码并返回第一页指针->显示所选择的页码->选择要查看的成员或选择页面跳转、退出等
如果分页显示函数用于显示全部成员，函数返回的值为NULL
如果用于选择成员并执行某项功能，则返回被选中成员的指针以驱动对应功能模块的运行，退出返回NULL*/
struct tex* show(char search_name[250], struct page* head_page)
{
    struct page* aim_page;   //aim_page用于定位页码

	struct tex* f_aim_member, * f_head_member=NULL;  //f_head_member用于定位首个联系人的位置， f_aim_member用于定位其它联系人

	char choice, display_choice;                   //choice为当前页的功能选项，display_choice为显示具体某个成员后的功能选项
	char jc[200] = { 0 }, of[] = "*常用联系人*";  //jc是进入页面跳转功能后的功能选项，of用于刷新常用联系人界面

	int pagei, page = 0, i, choice_member = -1; //pagei用于显示第几页，以及防止用户跳转到不存在的页面,i用于定位当前页的9个联系人成员
	int del_choice = 0, page_jump = 0, x = 0;  //del_choice用于帮助确认删除或移除操作，page_jump主要用于调用sscanf函数
	                                          //x用于判断被操作的联系人是否为首页的首成员

	if (filetest())        //检测文件是否为空
	{
		goto end;
	}
    
del_begin:
	if (head_page==NULL||del_choice && !strcmp(search_name, "/e"))//如果函数收到的head_page为空,或者删除过成员，需要刷新页码
	{
		head_page = addpage();
		page = culpage();//计算页码
	}
	else
	{
		if ( !strcmp(search_name, ""))//用于刷新页面
		{
			if (!x&& del_choice)
				f_head_member = f_head_member->next;//如果是头成员被删除，则把头成员交给下一个成员
			f_head_member = reading();
			head_page = often_distinguish(f_head_member, of);
		}
		else if (strcmp(search_name, "/e"))//用于刷新页面
		{
			if (!x && del_choice)
				f_head_member = f_head_member->next;//如果是头成员被删除，则把头成员交给下一个成员
			f_head_member = reading();
			head_page = search_v3(f_head_member, search_name);
		}
		aim_page = head_page;
		page = 0;

		while (aim_page != NULL)
		{
			page++;//计算页码
			aim_page = aim_page->next;
		}
	}

	//定位到第一页
	aim_page = head_page;

	del_choice = 0;

	if (aim_page != NULL)
	{
		for (pagei = 0;; pagei++)
		{
		begin:system("cls");     //函数主要功能的起始跳转节点
			//x是一个判断标志，不同的被调用情况下此函数所接收到的x的值不同，由此触发不同的显示类型
			printf("\n\n\n\n");
		    printf("\t\t\t\t请选择要查看的联系人\n\n");
			printf("\t\t\t\t------------------------------------------------\n");
			//此部分为构造显示列表
			for (i = 0; i < 9 && strcmp(aim_page->stu[i]->tex1.name, ""); i++)
			{
				printf("\t\t\t\t%d.%s\n", i + 1, aim_page->stu[i]->tex1.name);
			}
			printf("\t\t\t\t------------------------------------------------\n");
			printf("\n\t\t\t\t上一页（p）  下一页（n） 当前是第%d页,共%d页\n", pagei + 1, page);
			printf("\t\t\t\t输入名字前数字或选择下一页与上一页");
			printf("\n\t\t\t\t输入j进行页面跳转\n\t\t\t\t输入e返回上一级");                         //接上一注释

			choice = _getch();//读取用户选项

			switch (choice)//此部分，页面列表上每一个联系人都配有一个单独的显示调用
			{
			case '1':choice_member = 0; goto play;
			case '2':choice_member = 1; goto play;
			case '3':choice_member = 2; goto play;
			case '4':choice_member = 3; goto play;
			case '5':choice_member = 4; goto play;
			case '6':choice_member = 5; goto play;
			case '7':choice_member = 6; goto play;
			case '8':choice_member = 7; goto play;
			case '9':choice_member = 8; goto play;
			case 'p': //p为上一页
				system("cls");
				if (!pagei || aim_page->previous == NULL)
				{
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t当前是第一页！\n\n\n\n\n\n\n\t\t\t\t");
					system("pause");
					goto begin;
				}
				else
				{
					aim_page = aim_page->previous;
					pagei -= 2;
					goto switch_continue;
				}
			case 'n'://n为下一页
				system("cls");
				if (pagei + 1 == page || aim_page->next == NULL)
				{
					system("cls");
					printf("\n\n\n\n\n\n\n");
					printf("\t\t\t\t当前是最后一页！\n\n\n\n\n\n\n\t\t\t\t");
					system("pause");
					goto begin;
				}
				else
				{
					aim_page = aim_page->next;
					goto switch_continue;
				}
			case 'j':jr://j为页面跳转
				page_jump=0;
				system("cls");
				printf("\n\n\n\n\n\n\n\t\t\t\t请输入要跳转的页码\n\t\t\t\t或快捷跳转：第一页（1） 最后一页（%d）  返回（e）",page);
				printf("\n\t\t\t\t------------------------------------------------\n\t\t\t\t");
				scanf("%s",&jc);
				getchar();
			     if (!strcmp(jc, "e"))
				{
					goto begin;
				}
				else if (strspn(jc, "-0123456789") == strlen(jc))//判断输入的是否为数字
				{
					sscanf(jc, "%d", &page_jump);//取数字到int型的变量
					if (page_jump > page||page_jump<=0)
					{
						system("cls");
						printf("\n\n\n\n\n\n\n\t\t\t\t输入页数无效，请重新输入\n\n\n\n\n\n\n\t\t\t\t");
						system("pause");
						goto jr;
					}
					else if (page_jump > pagei + 1)//输入页码大于当前页码情况
					{
						page_jump -= pagei + 1;//此时page_jump为跳转次数
						for (; page_jump > 0 && aim_page->next != NULL; --page_jump)
						{
							aim_page = aim_page->next;//跳转到要求页
						}
						sscanf(jc, "%d", &pagei);//复制页码到pagei上
						pagei-=2;//修正页码
						goto switch_continue;
					}
					else if (page_jump < pagei + 1)//输入页码小于当前页码情况
					{
						page_jump = pagei + 1- page_jump;
						for (; page_jump > 0 && aim_page->previous != NULL; page_jump--)
						{
							aim_page = aim_page->previous;//跳转到要求页
						}
						sscanf(jc, "%d", &pagei);//复制页码到pagei上
						pagei -= 2;//修正页码
						goto switch_continue;
					}
					else if (page_jump == pagei + 1)//输入页码等于当前页码情况
					{
						goto begin;//直接返回
					}
				}
				else
				{
					system("cls");
					printf("\n\n\n\n\n\n\n\t\t\t\t输入错误，请重新输入！\n\n\n\n\n\n\n\t\t\t\t");
					system("pause");
				}
			case 'e'://e为退出
				goto end;//跳转至函数结束节点
			default:error:  //输入错误时的跳转节点
				system("cls");
				printf("\n\n\n\n\n\n\n\t\t\t\t输入错误!\n\n\n\n\n\n\n\n\t\t\t\t");
				system("pause");
				system("cls");
				goto begin;
			}
			if (0)//在switch中使for语句继续
			{
			switch_continue:
				continue;
			}

			if (0)//查看某个成员时的功能选择
			{
			play:
				if (!strcmp(aim_page->stu[choice_member]->tex1.name, ""))goto error;
				display(aim_page->stu[choice_member], -1);
				printf("请选择所需功能\n\t\t\t\t返回（e） 修改（c） 删除（d）\n\t\t\t\t设为常用联系人（w） 移出常用联系人（r）\n\t\t\t\t");
				display_choice = _getch();
				switch (display_choice)
				{
				case 'e': goto begin;
				case 'c':
					if (f_head_member == NULL)
					{
						changing(aim_page->stu[choice_member], head_page->stu[0]); goto play;
					}
					else
					{
						f_aim_member = f_head_member;
						while (aim_page->stu[choice_member] != f_aim_member)
							f_aim_member = f_aim_member->next;
						changing(f_aim_member, f_head_member); goto play;
					}
				case 'w':
					if (f_head_member == NULL)
					{
						if(!strcmp(aim_page->stu[choice_member]->tex1.mark,"*常用联系人*"))
						{
							system("cls");
							printf("\n\n\n\n\n\n\n\t\t\t\t你已将其设为常用联系人!\n\n\t\t\t\t");
							system("pause");
						}
						else
						  often_in(aim_page->stu[choice_member], head_page->stu[0]); 
						goto play;
					}
					else
					{
						if (!strcmp(aim_page->stu[choice_member]->tex1.mark, "*常用联系人*"))
						{
							system("cls");
							printf("\n\n\n\n\n\n\n\t\t\t\t你已将其设为常用联系人!\n\n\t\t\t\t");
							system("pause");
						}
						else
						{
							f_aim_member = f_head_member;
							while (aim_page->stu[choice_member] != f_aim_member)
							     f_aim_member = f_aim_member->next;
								
							
							often_in(f_aim_member, f_head_member); goto play;
						}
						goto play;
					}
				case 'r':
					if (f_head_member == NULL)
					{
						often_out(aim_page->stu[choice_member], head_page->stu[0]); goto play;
					}
					else
					{
						f_aim_member = f_head_member;
						while (aim_page->stu[choice_member] != f_aim_member)
						{
							f_aim_member = f_aim_member->next;
							x++;//检测被移除的成员是否为头成员
						}
						often_out(f_aim_member, f_head_member); if (!strcmp(search_name, "")) { del_choice = 1; goto del_begin; /*在“常用联系人”功能里，移除联系人后需要刷新页面*/ } else goto play;
					}
				case 'd':
					if (f_head_member == NULL)
					{
						if (del_choice = del(aim_page->stu[choice_member], head_page->stu[0]))goto del_begin; else { system("cls"); goto play; }
					}
					else
					{
						f_aim_member = f_head_member;//确保在搜索和常用联系人函数里能正常将除被删除成员外的成员录入文件
						while (aim_page->stu[choice_member] != f_aim_member)
						{
							f_aim_member = f_aim_member->next;
							x++;//检测被删除的成员是否为头成员
						}
						if (del_choice = del(f_aim_member, f_head_member))
							goto del_begin; else { system("cls"); goto play; }
					}
				default:system("cls"); printf("\n\n\n\n\n\n\n"); printf("\t\t\t\t输入错误！\n\t\t\t\t"); 
					system("pause"); system("cls"); goto play;
				}
				goto begin;
			}
		}

	}
end: 
	system("cls");
	return NULL;  //结束函数运行的跳转节点
}

//文件传入链表
/*用fseek函数控制文件指针的位置，用fgets每每定量获取所需信息，然后把fets最后得到的\n改为\0，最后传入链表，该函数会返回第一个成员的指针。
该函数的核心是一个for语句，在for语句中向下扫描联系人的每一个信息并进行读取，读取完成后录入链表
由此便完成一个联系人的读取，后跳到下一个联系人的区块重复操作，最后全部数据读取完毕*/
struct tex* reading()
{
	FILE* fp;
	struct tex1 tex1;
	struct tex* p, * tail = NULL, * head = NULL;  //分别为跳跃指针、尾指针和头指针
	int len, x = 10, y = 4;    //len用于存储联系人某个信息的长度

	fp = fopen("tencures.txt", "r");  //打开文件
	if (!fp)
	{
		printf("cannot open file\n");
		exit(0);
	}                             //接上一注释

	//在文件未遇到结束标志时读取数据,本质上是一个针对单个联系人信息的顺序读取
	people = 0;
	fseek(fp, 2L, 1);//跳过首信息中不应被读取的部分
	for (; fgets(tex1.name, 250, fp) != NULL; fseek(fp, y, 1)/*跳到下一个联系人信息区块*/)
	{
		len = strlen(tex1.name);//去掉fgets中的\n,并且可以防止超量读取
		tex1.name[len - 1] = '\0';//赋结束符
		fseek(fp, 8L, 1);//跳过下一信息中不应被读取的部分

		if (fgets(tex1.office, 250, fp) != NULL)//检测录入的信息是否完全为空
		{
			len = strlen(tex1.office);//去掉fgets中的\n,并且可以防止超量读取
			tex1.office[len - 1] = '\0';//赋结束符
			fseek(fp, 10L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.telephone, 250, fp) != NULL)//检测录入的信息是否完全为空
		{
			len = strlen(tex1.telephone);//去掉fgets中的\n,并且可以防止超量读取
			tex1.telephone[len - 1] = '\0';//赋结束符
			fseek(fp, 10L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.smartphone, 250, fp) != NULL)
		{
			len = strlen(tex1.smartphone);//去掉fgets中的\n,并且可以防止超量读取
			tex1.smartphone[len - 1] = '\0';//赋结束符
			fseek(fp, 6L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.type, 250, fp) != NULL)
		{
			len = strlen(tex1.type);//去掉fgets中的\n,并且可以防止超量读取
			tex1.type[len - 1] = '\0';//赋结束符
			fseek(fp, 10L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.email, 250, fp) != NULL)
		{
			len = strlen(tex1.email);//去掉fgets中的\n,并且可以防止超量读取
			tex1.email[len - 1] = '\0';//赋结束符
			fseek(fp, 4L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.qq, 250, fp) != NULL)
		{
			len = strlen(tex1.qq);//去掉fgets中的\n,并且可以防止超量读取
			tex1.qq[len - 1] = '\0';//赋结束符
			fseek(fp, 6L, 1);//跳过下一信息中不应被读取的部分
		}
		if (fgets(tex1.mark, 20, fp) != NULL)
		{
			len = strlen(tex1.mark);//去掉fgets中的\n,并且可以防止超量读取
			tex1.mark[len - 1] = '\0';//赋结束符
		}
		p = (struct tex*)malloc(sizeof(struct tex));//开辟空间创建链表 
		p->tex1 = tex1;
		if (head == NULL)//对头节点的处理
		{
			head = p;
			people++;
		}
		if (tail != NULL)//对尾节点的处理
		{
			tail->next = p;
			people++;
		}
		tail = p;
		tail->next = NULL;


		//因为文件中的联系人序号会变成两位、三位数，所以要给文件指针做位移补偿
		if (people >= x - 1) { y++; x = x * x; }
	}
	fclose(fp);
	return head;
}

//链表写入文件
void writing(struct tex* head)
{
	FILE* fp;
	struct tex* p = NULL;  //用以读取链表
	int mem = 1;          //用以对联系人计数

	fp = fopen("tencures.txt", "w");  //打开文件部分
	if (!fp)
	{
		printf("cannot open file\n");
		exit(0);
	}                             //接上一注释

	p = head;
	while (p)           //此循环将数据写入文件，直到最后一个（指针为空时）
	{
		fprintf(fp, "%d.", mem);   
		fprintf(fp, "%s\n\n单位：%s\n固定电话：%s\n移动电话：%s\n分类：%s\n电子邮件：%s\nQQ：%s\n标志：%s\n\n", 
		p->tex1.name, p->tex1.office, p->tex1.telephone, p->tex1.smartphone, p->tex1.type, p->tex1.email, p->tex1.qq,p->tex1.mark);
		mem++;
		p = p->next;
	}
	fclose(fp);
}

//显示单独联系人函数
//gp是成员指针，传入对应指针，直接显示。i是信息参数，通常为-1，非-1时则激活被录入联系人函数调用时的功能
void display(struct tex* gp,int i)
{
	system("cls");
	if (i == -1)//其他函数启用
		printf("\n\n\n");
	else//加入联系人函数启用
		printf("\n\t\t\t 第%d个联系人：\n\n", i);

	//显示名字
	printf("\t\t\t\t%s\n", gp->tex1.name);

	printf("\t\t\t\t------------------------------------------------\n\t\t\t\t");

	//显示其他信息
	printf("单位：%s\n\n\t\t\t\t固定电话：%s\n\n\t\t\t\t移动电话：%s\n\n\t\t\t\t分类：%s\n\n\t\t\t\t电子邮箱：%s\n\n\t\t\t\tQQ：%s\n\n\n\t\t\t\t%s\n",
		gp->tex1.office, gp->tex1.telephone, gp->tex1.smartphone,
		gp->tex1.type, gp->tex1.email, gp->tex1.qq,gp->tex1.mark);

	printf("\t\t\t\t------------------------------------------------\n\n\t\t\t\t");
}

//链表销毁函数
//两个指针交叉前进由p进行删除，直到最后一个
void destroy(struct tex* head)
{
	struct tex* p;
	if (head != NULL)
	{
		while (head->next) 
		{
			p = head->next;
			head->next = p->next;
			free(p);
		}
	}
}

//常用联系人函数
void often() {
	struct tex* head = NULL; 
	struct page* p;  //用以读取首页指针

	if (filetest()) //检测文件是否为空
	{
		goto end;
	}

	head = reading();      //读取文件数据并创建链表 

	while (1) {
		char  searches[20] = "*常用联系人*",s[]="\0";
		p = often_distinguish(head, searches);  //调用联系人判别模块，无结果则返回空
		if (p == NULL)
		{
			system("cls");
			printf("\n\n\n\t\t\t当前还没有添加任何常用联系人\n\n");
			system("pause");
			goto end;
			system("cls");
		}
		else
		{
			show(s, p);
			goto end;
		}
	}

end:   //结束功能的跳转节点
	destroy(head);  //销毁链表，释放内存
}

//常用联系人判定模块，是常用联系人函数的核心
//该函数本质上是通过“*常用联系人*”这个特定关键字对所有联系人信息进行自动检索并利用页面创建函数的逻辑来进行分页
struct page* often_distinguish(struct tex* head, char mark[20]) {

	struct tex* p1 = NULL, * p2 = NULL;               //p1，p2用于定位联系人成员
	struct page* head_page = NULL, * aim_page = NULL;//head_page用于定位首页，aim_page用于定位页码
	p1 = p2 = head;                                 //将p1、p2定位到第一个联系人成员
	int i = 0, stui_last_member;                   //i用于定位当前页成员位置，stui_last_member用于定位最后一个检索到的成员
	while (p1 != NULL)
	{
		if (strstr(p1->tex1.mark, mark))//判别条件，如果符合条件则录入常用成员
		{			
			if (head_page == NULL)    //针对首页，需要开辟新页以及用head_page定位第一页
			{
				head_page = aim_page = (struct page*)malloc(sizeof(struct page)); //为检索到的联系人信息开辟内存
				aim_page->next = NULL;
			}		
			else if (i >= 9)     //如果当前页录入的成员已满（9个），开辟新页
			{
				i = 0;
				aim_page->next = (struct page*)malloc(sizeof(struct page));
				aim_page = aim_page->next;
				aim_page->next = NULL;
			}

			//录入检索到的成员所在内存位置（录入指针）
			if (aim_page != NULL)
				aim_page->stu[i] = p1;
			stui_last_member = i;
			i++;
		}

		//定位到下一个联系人成员
		p2 = p1;
		p1 = p1->next;

	}
	//对搜索到的成员最后一页的处理
	if (aim_page != NULL)
	{
		for (i = 8; i > stui_last_member; i--)//最后一页的处理
		{
			aim_page->stu[i] = (struct tex*)malloc(sizeof(struct tex));
			if (aim_page->stu[i] != NULL)
				strcpy(aim_page->stu[i]->tex1.name, "");
		}
	}
	//返回首页指针
	return head_page;
}

//常用联系人移入模块
//本质为将mark数组赋值“*常用联系人*”
void often_in(struct tex* q, struct tex* head_member)
{
		char  in_mark[20] = "*常用联系人*";          
		strcpy(q->tex1.mark, in_mark);         
		writing(head_member);			//将修改后的信息存入文件
		system("cls");
		printf("\n\n\n\n\n\n\n\t\t\t\t已设为常用联系人!\n\n\t\t\t\t");
		system("pause");
		system("cls");
}
  
//常用联系人移出模块
//本质为将mark数组赋值“”
void often_out(struct tex* q, struct tex* head_member)
{
	char  out_mark[20] = "";
	strcpy(q->tex1.mark, out_mark);
	writing(head_member);			//将修改后的信息存入文件
	system("cls");
	printf("\n\n\n\n\n\n\n\t\t\t\t已移出常用联系人\n\n\t\t\t\t");
	system("pause");
	system("cls");
}
