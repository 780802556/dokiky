#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<windows.h>
#include<setjmp.h> 
#define menu_num 30

int k;//k代表菜单有多少菜品 
int num=0;//取餐码  

jmp_buf start1;
jmp_buf start2;
 
struct menu//菜品信息的结构体
{
	int num;//编号 
	char name[50];//菜品名
	int price;//菜品单价
	int purchase;//菜品销售情况
}menu[menu_num],menu_t;//t用来替代 

struct site//外卖地址信息结构体
{
	char name[10];//外卖地址
	int price;//销售额
	int num;//记录点单次数 
}site[4];

struct user_information//订单信息结构体
{
	int num[menu_num];//订单中每个菜名的编号 
	char name[menu_num][100];//菜名 
	int price[menu_num];//菜的单价 
	int count[menu_num];//每种菜点几份 
	int size;//用来记录点了几种套餐 
	char site[50];//每个订单的地址 
	char state[100];//每个订单的状态 1为已完成 0为备餐中 
	int l;//记录订单号 
	int total;//每个订单的总金额 
}information[2000];

void manage_pattern();//管理者模式
void order_pattern();//点菜模式 
void code_verify();//密码验证
void revise_password();//修改密码
void revise_menu();//修改菜单
void get_menu();//获取菜单数据信息
void print_menu();//打印菜单数据信息
void sort_menu();//按价格从小到大顺序排列菜单
void revise_dish();//修改单个菜品信息
void add_dish();//增加菜品
void delete_dish();//删除菜品
void save_menu();//保存菜品信息
void profit();//打印各个外卖地址销售额
void free_profit();//清空各个外卖地址销售额
void dish_purchase();//打印菜品销售情况并且屏幕暂停
void delete_dish_purchase();//清空各个菜品销售情况
void get_dish_purchase();//获取各个菜品销售情况
void put_dish_purchase();//保存各个菜品销售情况
void print_dish_purchase();//打印各个菜品销售情况
void get_site();//获取各个外卖地址信息
void save_site();//保存各个外卖地址信息
void delete_site();//删除各个外卖地址信息
void get_information();//获取订单信息
void save_information();//保存订单信息
int print_information();//打印订单信息
void delete_information();//删除订单信息
void find_information(); //管理者看订单信息并修改其状态
void backup();//备份
void delete_all();//清空所有
void research_information();//用户查询订单信息

int main()
{   
 
    get_menu();//给k、结构体site赋值
	get_information();  
	get_dish_purchase();
	get_site();//给结构体site赋值
	for(;;)
	{   
	    system("cls"); 
		printf("\t|-----------------------------------------------|\n");
		printf("\t|\t********欢迎使用本程序********\t\t|\n");
        printf("\t|\t\t1.管理者模式\t\t\t|\n");
        printf("\t|\t\t2.点菜模式\t\t\t|\n");
        printf("\t|\t\t3.查看订单信息\t\t\t|\n");
        printf("\t|\t\t0.退出\t\t\t\t|\n");
        printf("\t|-----------------------------------------------|\n");
        int n;
	    for(;;)
	        {
	  	      printf("请输入你的指令:");
	  	      scanf("%d",&n);
	  	      if(n>=0 && n<=3)
	  	         break;
	  	      else
	  	         printf("请重新输入正确选项!\n");
	        }
	    switch(n)
	     {
	   	  case 0:exit(0);
	   	  case 1:manage_pattern();break;
	   	  case 2:order_pattern();break;
	   	  case 3:research_information();break; 
		} 
	}
}

void manage_pattern()//*****管理者模式 
{ 
    code_verify(); 
	printf("欢迎进入管理者模式！\n");
	for(int i=0;i<=2;i++)
	  {
	  	printf("\t\t%d秒后即将跳转......\n",3-i);
	    Sleep(1000);
	  }
	for(;;)//每完成一个管理者系统中的子程序就返回管理者系统主页面从而一直操作 
	{
		system("cls"); 
	printf("\t|-----------------------------------------------|\n");
    printf("\t|\t\t*****管理者模式*****\t\t|\n");
    printf("\t|\t\t1.修改密码\t\t\t|\n");
    printf("\t|\t\t2.修改菜单\t\t\t|\n");
    printf("\t|\t\t3.查看营收\t\t\t|\n");
    printf("\t|\t\t4.查看每个菜品销售情况\t\t|\n");
    printf("\t|\t\t5.查看目前所有订单信息\t\t|\n");
    printf("\t|\t\t6.备份\t\t\t\t|\n");
    printf("\t|\t\t7.清空\t\t\t\t|\n");
    printf("\t|\t\t0.退出\t\t\t\t|\n");
    printf("\t|-----------------------------------------------|\n");
    int n;
    scanf("%d",&n);
    if(n==0)
      break;
	switch(n)
       {
       	case 1:revise_password();break; 
       	case 2:revise_menu();break;
       	case 3:profit();break;
		case 4:dish_purchase();break;
		case 5:find_information();break;
		case 6:backup();break;
		case 7:delete_all(); break;
	   }
	}	
}

void code_verify()
{
	char a[15];//Q1 初始化数组a防止给如垃圾数据 
	FILE *password=fopen("./password","r");
	if(password==NULL)
	   {
	   	  printf("读取数据失败！\n");
	      return;
       }
    fscanf(password,"%s",a);
    fclose(password);
	for(int i=1;i<=3;i++)
	   {  
	      printf("请输入管理者密码:");
	      char b[15];
	      scanf("%s",b);
	      if(strcmp(a,b)==0)
	        break;
	      if(i==3)
	        {
	        	printf("你的次数已用光，本程序以锁定!"); 
	        	for(;;)
	            {
				}
			}
	        
		  else
	        printf("你还有%d次输入正确密码的机会！\n",3-i);
	   }
}

void revise_password()
{
    char b[13];//b用来保存原密码，然后进行与新密码比较 
    FILE *r;
    if((r=fopen("./password","r"))==NULL)
      printf("无法读取密码！");
    fgets(b,sizeof(b),r);//Q3 为什么是sizeof而不是strlen，这个函数不是要求取字符串长度吗 
	fclose(r);
	char a[100000];//Q5 a用来保存新密码，万一用户输入数字大缓冲区会崩溃所以a的大小要弄很大，之前的a【13】明显是这个问题 
	printf("请输入新密码:(符号、数字、字母都可以包含且密码不超过12位)\n");
	for(;;)
	  {  	 
	  	scanf("%s",a);
		if(strcmp(a,b)==0)
		   	printf("请勿输入原密码:");
		else if(strlen(a)<=12)
		   break;
		else
		   printf("请按规定要求修改新密码:"); 
		  }
	printf("密码修改成功!当前密码为:%s\n",a);
	printf("1.保存 0.取消\n");
	printf("请选择你的操作:");
	int n;
	scanf("%d",&n);
	if(n==1)
	{
		FILE *fp;
	    if((fp=fopen("./password","w"))==NULL)//Q4 前面已经启动写入模式，那个fp里面不是什么都没有吗，那么这个循环条件不是一直成立吗 
	       {
	  	      printf("无法读取密码！");
	        	return; 
		   }
		fputs(a,fp);
	    printf("你已修改成功！\n");
	    fclose(fp);
	    for(int i=0;i<=2;i++)
	     {
	  	    printf("\t\t%d秒后即将返回管理者程序......\n",3-i);
	        Sleep(1000);
	     }
	}
	else
	;
	 return; 	
 } 
 
void revise_menu()
{
	for(;;)
	{
	system("cls"); 
	printf("本程序菜单:\n");
	printf("编号\t菜名\t\t\t价格\n");
	sort_menu();
	print_menu();
	printf("目前共有%d个菜品\n",k);
	printf("1.新增菜品 2.修改菜品信息 3.删除菜品 4.保存菜单 0.退出\n");
	printf("请输入你的指令:");
	int n;
    scanf("%d",&n); 
	if(n==0)
	  break;
	switch(n)
	{
		case 1:add_dish();break;
		case 2:revise_dish();break;
		case 3:delete_dish();break;
		case 4:save_menu();break; 
	 }
	 } 
	 
}
void get_menu()
{
	FILE *mr=fopen("./menu","r");
	if (mr == NULL) 
	  {
        printf("打开菜单文件失败");
        return;
      }
	k=0;
    while(fscanf(mr,"%d\t%s\t\t%d", &menu[k].num, menu[k].name, &menu[k].price) == 3) 
	{
	    fscanf(mr,"\n");
		k++;
	}//
	fclose(mr);//读取菜单完成
}

void print_menu()
{
	int j=0;
    while(j<k)
	{
		if(strlen(menu[j].name)<8)
  	    {
  	  	printf("%d\t%s\t\t\t%d",menu[j].num,menu[j].name,menu[j].price);
		printf("\n");
	    }
		else
		{
		printf("%d\t%s\t\t%d",menu[j].num,menu[j].name,menu[j].price);
		printf("\n");	
		}	
		j++;
    }
}

void sort_menu()//按价格大小排序 
{
	int min;
    for(int i=0;i<k-1;i++)
	  {
	  	min=menu[i].price;
	  	for(int j=i+1;j<k;j++)
	  	   {
	  	   	if(min>menu[j].price)
	  	   	  {
			  int a,b;
	  	   	  a=menu[i].num;
	  	   	  b=menu[j].num;
			  menu_t=menu[i];
	  	   	  menu[i]=menu[j];
	  	   	  menu[j]=menu_t;
              menu[i].num=a;
              menu[j].num=b;
			  }
		  }
	  }   	
} 

void add_dish()
{
  	printf("%d",++k);
  	menu[k-1].num=k;
  	scanf("\t%s\t%d",menu[k-1].name,&menu[k-1].price);
	printf("你已成功新加菜品！\n");
	print_menu();
	Sleep(2000);
}

void revise_dish()
{
	printf("请输入你要修改菜单编号:");
  	int n;
	scanf("%d",&n);
	printf("%d",n);
	scanf("\t%s\t%d",menu[n-1].name,&menu[n-1].price); 
	printf("你已成功修改菜品信息！\n");
	print_menu();
	Sleep(2000);
}

void delete_dish()
{
	printf("请输入你要删除的菜品编号:");
	int n;
	for(;;)
	{
		scanf("%d",&n);
		if(n<=k)
		  break;
		else
		  printf("请输入菜单现有编号:");
	}
	for(int i=n-1;i<k;i++)
	   {
	   	menu[i]=menu[i+1];
	   }
	k--;
	for(int j=0;j<k;j++)//用来重置编号 
	  {
	  	menu[j].num=j+1;
	   } 
	printf("你已成功删除编号为%d的菜品\n",n);
	print_menu();
	Sleep(2000);
}

void save_menu()
{   
    sort_menu();
	FILE *f=fopen("./menu","w");
	int i,j=0;
	for(i=0;i<k;i++)
	   {
	   	fprintf(f,"%d\t%s\t%d",menu[i].num,menu[i].name,menu[i].price);
	   	fprintf(f,"\n");
	   	j++;
	   }
	fclose(f);	 
	if(j==k)
	  {
	  	printf("保存信息成功！\n");
        Sleep(2000);
	  } 
	else
	  {
	  	printf("保存信息失败！\n");
	    Sleep(2000);
	  }
} 
 
void profit()
{
	system("cls"); 
	int sum=0;
	for(int i=0;i<4;i++)
	  {
	  	sum+=site[i].price;
	   }
	printf("当前总营收为:%d\n",sum);
	printf("地址\t营收\n");
	printf("柏苑\t%d\n",site[0].price);
	printf("松苑\t%d\n",site[1].price);
	printf("菊苑\t%d\n",site[2].price);
	printf("竹苑\t%d\n",site[3].price);
	system("pause"); 
}

void free_profit()
{
	for(int i=0;i<4;i++)
	  {
	  	site[i].price=0;
	  	site[i].num=0;
	  }
	//save_site( ;
 } 

void dish_purchase()
{
	print_dish_purchase();
	system("pause");	
}

void delete_dish_purchase()
{
	for(int j=0;j<k;j++)
	   	menu[j].purchase=0;
	put_dish_purchase(); 
}

void get_dish_purchase()
{
    FILE *fp=fopen("./dish_purchase","r");
	for(int i=0;i<k;i++)
	   {
	   	fscanf(fp,"%s\t%d",menu[i].name,&menu[i].purchase);
	   	fscanf(fp,"\n");
		   }
	fclose(fp);	   	
}

void put_dish_purchase()
{
	FILE *fp=fopen("./dish_purchase","w");
	for(int j=0;j<k;j++)
	 { 
		fprintf(fp,"%s\t%d",menu[j].name,menu[j].purchase);
		fprintf(fp,"\n");
	 }
	
	 fclose(fp);
}

void print_dish_purchase()
{
	system("cls");
    printf("菜名\t\t销售数量\n");
	for(int i=0;i<k;i++)
	   {
	   	if(strlen(menu[i].name)<8)
  	    {
  	  	printf("%s\t\t%d份",menu[i].name,menu[i].purchase);
		printf("\n");
	    }
		else
		{
		printf("%s\t%d份",menu[i].name,menu[i].purchase);
		printf("\n");	
		}
		   }
}

void order_pattern()//*****点菜模式 
{
    int az=99,t=99;
    char xx[10]; 
	for(;;)
	{ 
		setjmp(start1); 
		information[num].total=0;
		information[num].size=0; 
		int m;//m为单个用户点菜总类
		m=0;
		information[num].size=m;
		system("cls"); 
		printf("\t|-----------------------------------------------|\n");
        printf("\t|\t*********点菜模式*********\t\t|\n");
        printf("\t|欢迎使用本程序下单！\t\t\t\t|\n");
        printf("\t|请选择你的外卖地址:\t\t\t\t|\n");
		printf("\t|      1.柏苑 2.松苑 3.菊苑 4.竹苑 0.退出    \t|\n");;
        printf("\t|-----------------------------------------------|\n");
        int n;
		scanf("%d",&n);
		if(n==0)
		  break;
        if(n<0 || n>4)
		  continue; 
		switch(n)
		   {
		   	case 1:strcpy(information[num].site,"(柏苑)");break;
		   	case 2:strcpy(information[num].site,"(松苑)");break;
			case 3:strcpy(information[num].site,"(菊苑)");break; 
		   	case 4:strcpy(information[num].site,"(竹苑)");break;  
		   }
		setjmp(start2);
		system("cls");
        sort_menu();
        printf("编号\t菜名\t\t\t价格\n"); 
		print_menu();
		printf("(输入-1即可重新选择外卖地址)\n");
		printf("(输入0即为查看订单信息,如果想要修改菜品数量重复输入其数量即可)\n");
		for(;;)
		   {
		   	information[num].total=0; 
		   	printf("\t请输入菜品编号:");
		   	int x;
		   	scanf("%d",&x);
		   	if(x<-1 || x>k)
		   	  {
		   	  	printf("请输入正确编号！\n");
		   	  	continue;
				 }
			else if(x==-1)
			       {
			       	break;
				   }
			else if(x==0)
			       {
					for(int z=0;z<m;z++)
			       	   {
			       	   	information[num].total+=information[num].count[z]*information[num].price[z];
						  }
					print_information();
			       	printf("1.提交订单 0.继续点单\n");
			       	printf("请再次确认订单!\n");
					for(;;)
					{
						scanf("%s",xx);
						int aa;
						aa=xx[0]-48;
						if(aa==1 && strlen(xx)==1)
					       {
						system("cls");
			       	    information[num].total=0;
			       	    for(int z=0;z<m;z++)
			       	            {
			       	               information[num].total+=information[num].count[z]*information[num].price[z];
						        }
						information[num].size=m; 
					    print_information();
					    printf("1.确定 0.取消\n");
					    for(;;)
			       	       {
			       	       	  az=99;
					          scanf("%d",&az);
                              switch(az)
			       			                     {
			       				                   case 1:{
								                             if(information[num].total!=0)
									                            {
									                               information[num].size=m;
			       					                               information[num].l=num+1;
			       					                               site[n-1].num++;
			       					                               site[n-1].price+=information[num].total;
			       					                               char x[100]="(备餐中)";
			       					                               strcpy(information[num].state,x);
			       					                               for(int r=0;r<m;r++)
									                                   {
									   	                                  for(int t=0;t<k;t++)
									   	                                      {
									   		                                     if(information[num].num[r]==menu[t].num)
									   		                                        {
									   		   	                                      menu[t].purchase+=information[num].count[r];
												                                    }
										                                      } 	
										                               } 
									                               printf("您的取餐码为%d",num+1);
									                               num++;
									                               save_information();
									                               save_site();
									                               put_dish_purchase();
									                               system("pause"); 
									                               longjmp(start1,1); 
									                            } 
			       					                          else
			       					                            {
			       					  	                           printf("目前显示你的订单信息为零，请重新点单！\n");
			       					  	                           longjmp(start2,1);
										                        }
								                           }
								                   case 0:
								                        {
									                        longjmp(start2,1); 
								                        }
								                   default:{
									                               printf("请输入正确指令！\n");
									                               break;
								                           }   
							                    }                               
					       }
					     
					          }
					     else if(aa==0 && strlen(xx)==1) 
						   break;
						 else
					        {
					        	printf("请输入正确指令！\n");
					        	continue;
							}	 
					}
			      }   
			else
			     {     
						for(int j=0;j<k;j++)
						   {
						   	if(information[num].num[j]==0)//用来看是否之前输入过相同的
							    {
							    	information[num].num[m]=x;
				                    printf("%s你要点几份:",menu[x-1].name);
				                    int t;
				                    scanf("%d",&t);
									if(t!=0)
									  {
									  	strcpy(information[num].name[m],menu[x-1].name);
				                        information[num].count[m]=t;
				                        information[num].price[m]=menu[x-1].price;
				                        m++;
				                        information[num].size=m; 
									    break; 
									   } 
									else
									    break;
								}
							 else if(information[num].num[j]==x)
							    {
							    	printf("%s你要点几份:",menu[x-1].name);
							    	int t;
							    	scanf("%d",&t);
							    	if(t==0)
							    	  {
							    	  	for(int v=j;v<m-1;v++)
										  {
										  	information[num].count[v]=information[num].count[v+1];
									   	information[num].num[v]=information[num].num[v+1];
									   	information[num].price[v]=information[num].price[v+1];
									   	strcpy(information[num].name[v],information[num].name[v+1]);   
										   } 
										information[num].count[m] = 0;
                                        information[num].num[m] = 0;
                                        information[num].price[m] = 0;
                                        char z[100]="\0";
                                        strcpy(information[num].name[m],z);
                                        if(m>0) 
										   m--;
										information[num].size=m;
										break;
									  }
									else
									   {
									   	strcpy(information[num].name[j],menu[x-1].name);
							    	information[num].count[j]=t;
							        break;
									   }
							        
									}
							   else
							      continue; 	
								}
			    }
		  }
		if(az==1 || t==0 || t==1)
		  break;
	}
} 
	 

void get_information()
{   
    int i=0; 
	char x;
	FILE *fp=fopen("./information","r");
	while(fscanf(fp,"%c",&x)==1)
	  {
	  	if(x=='A')
		  {
		fscanf(fp,"订单");
		fscanf(fp," ");
        fscanf(fp,"%d%s",&information[i].l,information[i].site); 
		fscanf(fp,"\n");
		int z=0;
	  	while(fscanf(fp,"%c",&x)==1)
	  	   {
	  	   	switch(x)
	  	  {
	  	  	case 'B':{
	  	  		    	fscanf(fp,"%d",&information[i].num[z]);
						fscanf(fp,"\t");
						fscanf(fp,"%s",information[i].name[z]);
						fscanf(fp,"\t");
						fscanf(fp,"%d",&information[i].price[z]);
						fscanf(fp,"\t");
						fscanf(fp,"%d",&information[i].count[z]);
						fscanf(fp,"\t");
	  	  		        fscanf(fp,"\n");
	  	  		        z++;
	  	  		        break;
				}
	  	  	case 'C':{
                    fscanf(fp,"%d",&information[i].size);
                    fscanf(fp,"\n");
					break;				
 				}
	  	  	case 'D':{
	  	  		    fscanf(fp,"%d",&information[i].total);
	  	  		    fscanf(fp,"\n"); 
					break;
				}
	  	  	case 'E':{
				    fscanf(fp,"%s",information[i].state);
				    fscanf(fp,"\n");
			        fscanf(fp,"----------------------------------------------------------");
			        fscanf(fp,"\n"); 
	  	  		    i++;
					num++;
					break; 
				}
			}
			
		 if(x=='E')
		   break;
		   }
		}
	   else
		break;
		  }
	    
	  fclose(fp);
}

void save_information()
{
    FILE *fp=fopen("./information","w");
	for(int i=0;i<num;i++)
	   {
	   	fprintf(fp,"A订单 %d%s\n",i+1,information[i].site);
	   	for(int j=0;j<information[i].size;j++)
	   	{
	   		fprintf(fp,"B%d\t%s\t%d\t%d\n",information[i].num[j],information[i].name[j],information[i].price[j],information[i].count[j]);
		   }
		fprintf(fp,"C%d\n",information[i].size);
		fprintf(fp,"D%d\n",information[i].total);
		fprintf(fp,"E%s\n",information[i].state);
		fprintf(fp,"----------------------------------------------------------\n");
	   }
	fclose(fp);
}

int print_information() 
{
	if(information[num].total==0)
	   {
	   	printf("你目前订单信息为零喔！\n");
	   }
	else
	{
		printf("用户你目前的订单信息为:%s\n",information[num].site);
    printf("编号\t菜名\t\t单价\t份数\n");
    for(int i=0;i<information[num].size;i++)
     {
      	if(strlen(information[num].name[i])<8)
      	  {
      	  	printf("%d\t%s\t\t%d\t%d\n",information[num].num[i],information[num].name[i],information[num].price[i],information[num].count[i]);
			}
		else
		  {
		  	printf("%d\t%s\t%d\t%d\n",information[num].num[i],information[num].name[i],information[num].price[i],information[num].count[i]);
		  }
	  }
	printf("总价格为%d\n",information[num].total);
	printf("----------------------------------------------------------\n");
	}
    
}

void delete_information()
{
    FILE *fp=fopen("./information","w");
	fclose(fp);	
}

void find_information()
{
	system("cls");
	if(information[0].total!=0)
	{
		int i=0;
	    while(information[i].num[0]!=0)
	          {
	   	       		printf("订单 %d%s\n",information[i].l,information[i].site);
	   	  			printf("编号\t菜名\t\t单价\t份数\n"); 
	   	  			for(int j=0;j<information[i].size;j++)
	   	     			{
	   	     		if(strlen(information[i].name[j])<8)
	   	           		printf("%d\t%s\t\t%d\t%d\n",information[i].num[j],information[i].name[j],information[i].price[j],information[i].count[j]);
	   	        	else
	   	           		printf("%d\t%s\t%d\t%d\n",information[i].num[j],information[i].name[j],information[i].price[j],information[i].count[j]);
						}
	   	  			printf("总金额为:%d\n",information[i].total);
	      			printf("此单状态:%s\n",information[i].state);
		  			printf("----------------------------------------------------------\n");
		  			i++;
				}
		if(i!=0)
			{
			printf("是否想要修改订单状态\n");
			printf("1.修改 0.返回\n");
			int n=99,a=99;
			for(;;)
	  			 {
	   				scanf("%d",&n);
	   				if(n<0 || n>1)
	   	   				{
	   	   					printf("请输入正确指令！\n");
	   	   					continue;
			  			}
					else if(n==0)
		       				break;
					else
		    			{
		    				printf("你将要修改哪个订单状态(0.退出)\n");
		    				for(;;)
		    					{
		    						scanf("%d",&a);
		    						if(a==0)
		    		  				break;
		    						if(information[a-1].total==0)
		    		   					{
		    		   						printf("请输入正确指令！\n");
		    		   						continue;
					   					}
									else
					   					{
					   						printf("订单 %d的状态为:%s\n",information[a-1].l,information[a-1].state);
					   						printf("是否将上述订单状态改为(已完成)\n1.是 0.否\n");
											for(;;)
					   	   						{
					   	   							int c;
					   	   							scanf("%d",&c);
					   	   							if(c==1)
					   	   	  							{
					   	   	  								char p[100]="(已完成)";
					   	        							strcpy(information[a-1].state,p);
					   	        							save_information(); 
					   	        							printf("你已修改成功！\n");
					   	        							system("pause");
					   	        							break; 
														}
													else if(c==0)
							       							break;
													else
							    						{
							    							printf("请输入正确指令!\n");
							    							continue;
														}
							  					}
					   						break;
					   					}
									if(a==1 || a==0)
					  					break;
								}	
						}
		 			if(a==1 || a==0)
					  break;
					} 
	 		} 
	 else
	   {
	   	printf("目前还未有订单信息！\n");
	   	system("pause");
	   }
	}
	else
	   {
	   	printf("当前订单信息为零！\n");
	   	system("pause");
		} 	
}

void research_information()
{
	system("cls");
	printf("你想要查的订单编号多少:(0.返回)\n");
	for(;;)
	   {
	   	  int n;
	   	  scanf("%d",&n);
	   	  if(n>0 && n<num+1)
	   	    {
	   	    	printf("用户你目前的订单信息为:%s\n",information[n-1].site);
                printf("编号\t菜名\t\t单价\t份数\n");
                         for(int i=0;i<information[n-1].size;i++)
                            {
      	                       if(strlen(information[n-1].name[i])<8)
      	                         {
      	  	                       printf("%d\t%s\t\t%d\t%d\n",information[n-1].num[i],information[n-1].name[i],information[n-1].price[i],information[n-1].count[i]);
			                     }
		                       else
		                         {
		  	                       printf("%d\t%s\t%d\t%d\n",information[n-1].num[i],information[n-1].name[i],information[n-1].price[i],information[n-1].count[i]);
		                         }
	                       }
	            printf("总价格为%d\n",information[n-1].total);
	            printf("该订单状态为:%s\n",information[n-1].state);
	            printf("----------------------------------------------------------\n");
	            system("pause");
			   }
		  else if(n==0)
		       break; 
		  else
		    {
		    	printf("无法查询该订单,请输入正确的订单编号！\n");
		    	continue;
			}
		  if(n>0 && n<num+1)
		     break;
	   }
}

void get_site()
{
	FILE *fp=fopen("./site","r");
	for(int i=0;i<4;i++)
	   {
	   	fscanf(fp,"%s\t\t%d\t%d",site[i].name,&site[i].price,&site[i].num);
	   	fscanf(fp,"\n");
	   }
	fclose(fp);
 } 

void save_site()
{
	FILE *fp=fopen("./site","w");
	  for(int i=0;i<4;i++)
	   {
	   	fprintf(fp,"%s\t\t%d\t%d",site[i].name,site[i].price,site[i].num);
	   	fprintf(fp,"\n");
	}
	fclose(fp);
 } 

void delete_site()
{
      FILE *fp=fopen("./site","w");
	  for(int i=0;i<4;i++)
	     {
	     	site[i].num=0;
	     	site[i].price=0;
			 }
	 save_site();
	 fclose(fp);	
}

void backup()
 {
 	char x[100];
 	printf("温馨提示：一经备份将无法修改，请注意！(输入0即返回)\n") ; 
	printf("请输入当日日期(格式为2026/4/4):");
	scanf("%s",x);
	if(strlen(x)==1 && x[0]=='0')
	  	return;
	FILE *fp1=fopen("./backup_site","a");
	fprintf(fp1,"%s\n",x);
	for(int i=0;i<4;i++)
	   {
	   	fprintf(fp1,"%s\t\t%d\t%d",site[i].name,site[i].price,site[i].num);
	   	fprintf(fp1,"\n");
	}
	FILE *fp2=fopen("./backup_purchase","a");
	fprintf(fp2,"%s\n",x);
	for(int j=0;j<k;j++)
	 { 
		fprintf(fp2,"%s\t%d",menu[j].name,menu[j].purchase);
		fprintf(fp2,"\n");
	 }
	FILE *fp3=fopen("./backup_information","a");
	fprintf(fp3,"%s\n",x);
	for(int i=0;i<num;i++)
	   {
	   	fprintf(fp3,"A订单 %d%s\n",i+1,information[i].site);
	   	for(int j=0;j<information[i].size;j++)
	   	{
	   		fprintf(fp3,"B%d\t%s\t%d\t%d\n",information[i].num[j],information[i].name[j],information[i].price[j],information[i].count[j]);
		   }
		fprintf(fp3,"C%d\n",information[i].size);
		fprintf(fp3,"D%d\n",information[i].total);
		fprintf(fp3,"E%s\n",information[i].state);
		fprintf(fp3,"----------------------------------------------------------\n");
	   }
	for(int i=0;i<num;i++)//将information结构体清零
	   {
	   	information[i].size=0;
        information[i].l=0;
        information[i].total=0;
        char z[100]="\0";
        strcpy(information[i].site,z);
        strcpy(information[i].state,z);
	   	for(int j=0;j<information[i].size;j++) 
	        {
		        information[i].count[j] =0;
                information[i].num[j] = 0;
                information[i].price[j] =0;
                strcpy(information[i].name[j],z);
	        } 
	   }
	
	
	fprintf(fp1,"\n");
	fprintf(fp2,"\n"); 
	fprintf(fp3,"\n");
	printf("你已备份成功！\n");
	fclose(fp1);
	fclose(fp2); 
	fclose(fp3);
	system("pause"); 
 }

void delete_all()
{
	printf("你是否将清空当日营收、菜品销售情况、菜单信息？\n");
	printf("1.确定 0.取消\n"); 
	int n;
	printf("请输入你的指令:");
	for(;;)
	   {
	    scanf("%d",&n);
	   	if(n==1)
	   	  {
	   	  	printf("系统将自动跳转进入备份....\n");
	   	  	backup();
	   	  	delete_information();
		    delete_dish_purchase();
		    delete_site();
			free_profit();
			printf("当日营收、菜品销售情况、菜单信息已清空完成！\n");
			break;
			 }
		else if(n==0)
		    break;
		else 
		   {
		   	printf("请输入正确指令！\n");
		   }
		} 
}
