#ifndef __SALES_ITEM_H__
#define __SALES_ITEM_H__

#include <iostream>
#include <string>

class Sales_item 
{
friend std::istream& operator>>(std::istream&, Sales_item&);
friend std::ostream& operator<<(std::ostream&, const Sales_item&);
friend bool operator<(const Sales_item&, const Sales_item&);
friend bool operator==(const Sales_item&, const Sales_item&);

public:
	Sales_item()
		:units_sold(0), revenue(0.0)
	{}

	Sales_item(const std::string &book)
		:bookNo(book), units_sold(0), revenue(0.0)
	{}

	Sales_item(std::istream &is)
	{
		is >> *this;
	}
public:
	Sales_item& operator+=(const Sales_item&);
	std::string isbn() const
	{
		return bookNo;
	}
	double argv_price() const;
private:
	std::string bookNo;
	unsigned units_sold;
	double revenue;
};

inline bool compareIsbn(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs.isbn() == rhs.isbn();
}

Sales_item operator+(const Sales_item&, const Sales_item&);

inline bool operator==(const Sales_item &lhs, const Sales_item &rhs)
{
	return lhs.units_sold == rhs.units_sold 
		&& lhs.revenue == rhs.revenue
		&& lhs.isbn() == rhs.isbn();
}

inline bool operator!=(const Sales_item &lhs, const Slaes_item &rhs)
{
	return !(lhs == rhs);
}

//这个操作必须先确定两个对象的isbn()是一样的相加才有意义
Sales_item& Sales_item::operator+=(const Sales_item &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;
	return *this;
}

//FIXME：用已实现的+=操作函数来实现+操作函数可以优化掉程序生成的临时变量
Sales_item operator+(const Sales_item &lhs, const Sales_item &rhs)
{
	Sales_item ret(lhs);
	ret += rhs;
	return ret;
}

std::istream& operator>>(std::istream &in, Sales_item &s)
{
	double price;
	//输入时流的顺序分别是 ISBN 数量 单价
	in >> s.bookNo >> s.units_sold >> price;
	if (in)  {
		s.revenue = s.units_sold * price;
	} else {
		s = Sales_item();
	}

	return in;
}

std::ostream& operator<<(std::ostream &out, const Sales_item &s)
{
	out << s.isbn() << " " << s.units_sold << " " << s.revenue << s.avg_price();
	return out;
}

double Sales_item::arg_price() const
{
	if (units_sold)  {
		return revenue / units_sold;
	}else {
		return 0;
	}
}
#endif /* end of :__SALES_ITEM_H__ */
