#include <iostream>

struct YearMonthDay
{
	int year;
	int month;
	int day;
};


struct YearMonthDay getYearMonthDay(int julianDayNumber)
{
  int a = julianDayNumber + 32044;
  int b = (4 * a + 3) / 146097;
  int c = a - ((b * 146097) / 4);
  int d = (4 * c + 3) / 1461;
  int e = c - ((1461 * d) / 4);
  int m = (5 * e + 2) / 153;
  struct YearMonthDay ymd;
  ymd.day = e - ((153 * m + 2) / 5) + 1;
  ymd.month = m + 3 - 12 * (m / 10);
  ymd.year = b * 100 + d - 4800 + (m / 10);
  return ymd;
}
int getJulianDayNumber(int year, int month, int day)
{
	int a = (14 - month) / 12;
	int y = year + 4800 - a;
	int m = month + 12 * a - 3;
	return day + (153*m + 2) / 5 + y*365 + y/4 - y/100 + y/400 - 32045;
}

int main(int argc, const char *argv[])
{
	int kJulianDayOf1970_01_01 = getJulianDayNumber(1970, 1, 1);

	std::cout << kJulianDayOf1970_01_01 << std::endl;

	struct YearMonthDay ymd = getYearMonthDay(kJulianDayOf1970_01_01);
	std::cout << ymd.year << " " << ymd.month << " " << ymd.day << std::endl;
	return 0;
}
