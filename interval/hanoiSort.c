#include <stdio.h>
/*
 * 汉诺塔思路：想象一个数组从0-n下标，数组元素大小表示塔的大小，每次只能拿出需要的塔位置及以上全部的塔
 * 拿出后只能做翻转后全部放回或者不操作全部放回
 * 需要使得该塔从下标开始从大到小排序
 */

//拿出后翻转
void turn(int *array, int n)
{
	int *p1 = array;
	int *p2 = array + n-1;
	while (p1 < p2) {
		int temp = *p1;
		*p1 = *p2;
		*p2 = temp;
		p1++;
		p2--;
	}
}

//找出塔的最长大小的下标
int searchMax(int *array, int n)
{
	int index = 0;
	int temp = array[0];
	for (int i = 0; i < n; i++) {
		if (temp < array[i])  {
			temp = array[i];
			index = i;
		}
	}
	return index;
}

void showArray(int *array, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

}

void hanoi(int *array, int n)
{
	//翻转次数
	int index;
	for (int i = 0; i < n; i++) {
		index = searchMax(&array[i], n-i);
		turn(&array[index+i], n-index-i);
		turn(&array[i], n-i);
		showArray(array, 10);
//		printf("%d %d\n", i, index);
	}
}
int main(int argc, const char *argv[])
{
	
	int array[10] = {1, 8, 6, 5, 2, 10, 7, 3, 4, 9};
	showArray(array, 10);

	hanoi(array, 10);

	showArray(array, 10);

	return 0;
}
