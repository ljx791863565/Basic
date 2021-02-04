#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



struct MonthDay {
	unsigned int month;
	unsigned int day;
};

static int Day_of_the_month[2][13] = {
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

static int Day_Of_the_year[2] = {
	365, 366
};

static const char WeekdayArray[7][10] = {
	{"一"},
	{"二"},
	{"三"},
	{"四"},
	{"五"},
	{"六"},
	{"日"}
};


void main_menu(void)
{
	printf("*****************************************\n");
	printf("*                                       *\n");
	printf("*          万年历			*\n");
	printf("*       1900年-2099年			*\n");
	printf("*                                       *\n");
	printf("*****************************************\n");
	printf("*                                       *\n");
	printf("*                                       *\n");
	printf("*  #1.月历查询                          *\n");
	printf("*  #2.年历查询                          *\n");
	printf("*  #3.星期查询                          *\n");
	printf("*  #4.退出                              *\n");
	printf("*                                       *\n");
	printf("*****************************************\n");
	
	
}



/*
 * 判断年份是否合法 
 * 参数 输入年份
 * 输出 1： 合法 0：非法
 */
int check_year(int year)
{
	return (year >= 1900 && year <= 2099);
}

/*
 * 判断月份是否合法
 * 参数 输入月份
 * 输出 1：合法 0：非法
 */
int check_month(int month)
{
	return (month >0 && month <= 12);
}

/*
 * 判断是否闰年
 * 参数 输入年份
 * 输出 1：闰年 0：平年
 */
int check_LeapYear(int year)
{

	return ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0));
}

int get_day_of_month(int year, int month)
{
	int leap = check_LeapYear(year);
	return Day_of_the_month[leap][month];
}

int get_day_of_year(int year)
{
	int leap = check_LeapYear(year);
	return Day_Of_the_year[leap];
}

/*
 * 判断日期是否合法
 * 参数 输入年份 月份 日期
 * 输出 1：合法 0：非法
 */
int check_day(int year, int month, int day)
{
	return (day <= 	get_day_of_month(year, month) && day > 0);
}


//返回公历某月某日是一年中第几天 默认1月1日是第一天
int get_dayth(int year, int month, int day)
{
	int dayth = 0;
	for (int i=1; i<=month; i++) {
		dayth += get_day_of_month(year, month);
	}
	dayth += day;
	return dayth;
}

//返回某年第某天是该年公历几月几日
struct MonthDay get_Month_Day(int year, int dayth)
{
	struct MonthDay md;
	memset(&md, 0, sizeof(struct MonthDay));
	int month = 0;
	int day = 0;
	while (dayth > 0) {
		dayth -= get_day_of_month(year, month++);
	}
	md.month = month-1;
	md.day = dayth + get_day_of_month(year, month);

	return md;
}

int get_Centunry(int year)
{
	return (year/100)+1;
}

int get_Weekday(int year, int month, int day)
{
	//d+2*m+3*(m+1)/5+y+y/4-y/100+y/400
	if (month == 1)  {
		month = 13;
		year--;
	}else if (month == 2)  {
		month = 14;
		year--;
	}

	return (day + 2*month + 3*(month+1)/5 + year + year/4 - year/100 + year/400) % 7;
}

int get_weekth(int year, int month, int day)
{
	int dayth = get_dayth(year, month, day);

	return (dayth/7)+1; 
}

void check_the_date(int year, int month, int day)
{
	int ret = check_year(year);
	if (ret != 1)  {
		printf("年份输入有误\n");
		return ;
	}

	ret = check_month(month);
	if (ret != 1)  {
		printf("月份输入有误\n");
		return ;
	}

	ret = check_day(year, month, day);
	if (ret != 1)  {
		printf("日期输入有误\n");
		return ;
	}
}

void search_week()
{
	int year, month, day, weekday;
	printf("请输入年月日:\n");
	printf("年：");
	scanf("%d", &year);
	fflush(stdin);
	getchar();
	printf("月：");
	scanf("%d", &month);
	fflush(stdin);
	getchar();
	printf("日：");
	scanf("%d", &day);
	fflush(stdin);
	getchar();

	int ret = check_year(year);
	if (ret != 1)  {
		printf("年份输入有误\n");
		return ;
	}

	ret = check_month(month);
	if (ret != 1)  {
		printf("月份输入有误\n");
		return ;
	}

	ret = check_day(year, month, day);
	if (ret != 1)  {
		printf("日期输入有误\n");
		return ;
	}

	weekday = get_Weekday(year, month, day);
	printf("%d-%d-%d是星期 %s\n", year, month, day, WeekdayArray[weekday]);
}

void Month_head_display(int year, int month)
{
	 printf("%d 年 %d 月\n", year, month);
	 printf("日 一 二 三 四 五 六\n");
}
void month_display(void)
{
	int year, month, weekday;
	printf("请输入年月日:\n");
	printf("年：");
	scanf("%d", &year);
	fflush(stdin);
	getchar();
	printf("月：");
	scanf("%d", &month);
	fflush(stdin);
	getchar();

	Month_head_display(year, month);
	weekday = get_Weekday(year, month, 1);
	int month_day = get_day_of_month(year, month);
	int line = 0;
	int row = 0;
	for (int i = 1; i <= month_day; i++) {
		if (row == 0)  {
			for (int j = 0; j < weekday*4; j++) {
				printf(" ");
			}
			row = 1;
		}
		printf("%3d ", i);
		line++;
		if ((line+weekday) == 7)  {
			printf("\n");
			line = 0;
			weekday = 0;
		}
	}
	printf("\n");
}

void year_display(void)
{
	printf("this is year_display()\n");
	sleep(1);
}

void main_loop(void)
{
	int key = 0;
	for (;;) {
		fflush(stdin);
		main_menu();
		//scanf接收字符会有回车字符 用getchar吸收掉此字符
		scanf("%d", &key);
		getchar();	
	/*	
		switch (key)
		{
			case 1:
				month_display();
				break;
			case 2:
				year_display();
				break;
			case 3:
				search_week();
				break;
			case 4:
				printf("正在退出系统，再见。。。\n");
				sleep(1);
				return;
			default:
				printf("输入有误，请重新输入。。。\n");

		}
	*/
		if (key == 1)  {
			month_display();
		} else if (key == 2)  {
			year_display();
		} else if (key == 3)  {
			search_week();
		} else if (key == 0)  {
			printf("正在退出系统，再见。。。\n");
			sleep(1);
			return;
		}else {
			printf("输入有误，请重新输入。。。\n");
			fflush(stdin);
	
		}
	}
}



int main(int argc, const char *argv[])
{

//	main_menu();
	for (int i = 1; i < 13; i++) {
		printf("%d ", Day_of_the_month[0][i]);
	}
	printf("\n");
	for (int i = 1; i < 13; i++) {
		printf("%d ", Day_of_the_month[1][i]);
	}
	printf("\n");
	main_loop();
	return 0;
}
