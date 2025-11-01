
#pragma once
#include <iostream>
#include <string>
#include <cstring> 
#include <cstddef>
#include <cstdio>
#include <conio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define N 999

typedef struct Product {
	long productID;			//商品代码
	char produtName[100];	//名称
	double price;			//单价
	int total;				//总量
	int sales;				//销售量
	int inventory;			//库存量
	double revenue;			//销售额
}product;

void ProductEntry();					//商品信息录入					操作1函数
void ProductBrowsing();					//商品信息浏览					操作2函数
void ProductDeletion();					//商品信息删除					操作3函数
void ProductModification();				//商品信息修改					操作4函数
void InventoryAndSales();				//计算各类商品的库存量及销售额	操作5函数
void Sort();							//排序							操作6函数
void lookup();							//查找							操作7函数
void calculate();						//计算并返回销售总额			操作8函数
int isValidProductID(long productID);	// 验证商品代码是否有效
int isValidPrice(double price);			// 验证商品单价是否有效
int isValidQuantity(int quantity);		// 验证商品数量是否有效
int isValidProductName(const char* productName);;// 验证商品名称是否有效
int num(long n);
void clearInputBuffer();// 清除输入缓冲区
void SaveAllProductsToFile();//将所有商品保存至文件
void ReadProduct();//读取商品文件
void SaveSortedProductsToFile();//将排序后的商品保存至文件
void SaveProductToFile(product pro);//将该商品保存至文件
void filebuild();//创建文件
void clearScreen();//清屏
void ShowMenu(int selected);//显示菜单
void printRepeatedChar(char c, int num);//将格式长度与字符长度相对应
int isDuplicateProductID(long productID, int index);
product products[N];					// 商品数组
int count = 0;						    // 商品数量
int choice = 0;                         //目录选项

