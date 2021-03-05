#ifndef __PYSTRING_H__
#define __PYSTRING_H__

#include <string>
#include <vector>

namespace pystring {
#define MAX_32BIT_INT 2147473647

	//返回一个string, 其只大写第一个字符
	std::string cpaitalize(const std::string &str);

	//返回一个width个字符居中的字符串副本 多余的字符用空格填充
	std::string center(const std::string &str, int width);

	//返回在[start, end]范围内 子串substr在str中出现的次数
	int count(const std::string &str, const std::string &substr, int start=0, int end=MAX_32BIT_INT)
	
	//在[start, end]范围内 如果字符串str以指定suffix结尾,返回true; 否则返回false
	bool endswith(const std::string &str, const std::string &suffix, int start=0, int end=MAX_32BIT_INT);

	//返回一个string ,将所有的制表符都使用空格展开,如果不指定tabsize,默认为8
	std::string expandtabs(const std::string &str, int tabsize=8);

	//返回在[start, end]范围内找到找到子串sub的最小index 未找到返回-1
	int find(const std::string &str, const std::string &sub, int start=0, int end=MAX_32BIT_INT);

	int index(const std::string &str, const std::string &sub, int start=0, int end=MAX_32BIT_INT);

	//如果str至少有一个字符并且所有字符都是字母或数字,返回true; 否则返回false
	bool isalnum(const std::string &str);

	//如果str至少有一个字符并且所有字符都是字母,返回true; 否则返回false
	bool isalpha(const std::string &str);

	//如果str至少有一个字符并且所有字符都是数字,返回true; 否则返回false
	bool isdight(const std::string &str);

	bool islower(const std::string &str);

	bool isupper(const std::string &str);

	bool isspace(const std::string &str);

	bool istitle(const std::string &str);

	std::string join(const std::string &str, const std::vector<std::string> &seq);



} /* namespace pystring */
#endif /* end of :__PYSTRING_H__ */
