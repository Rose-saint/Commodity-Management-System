//操作函数
#include "CMS.h"


//商品信息录入函数
void ProductEntry() {
	int n;
	do {
		printf("  输入商品数:");
		if (scanf_s("%ld", &(n)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}
		clearInputBuffer();
		if (!num(n)) {
			printf("商品数过大，请重新输入。\n");
		}
	} while (!num(n));

	for (int i = 0; i < n; i++) {
		product pro;    // 创建新商品

		// 输入商品代码
		do {
			printf(" 输入商品代码（不超过5位数）:");
			if (scanf_s("%ld", &(pro.productID)) != 1) {
				printf("无效的输入，请重新输入。\n");
				clearInputBuffer();
				continue;
			}
			clearInputBuffer();
			if (!isValidProductID(pro.productID)) {
				printf("商品代码无效，请重新输入。\n");
			}
			else if (isDuplicateProductID(pro.productID, count + 1)) {
				printf("商品代码重复，请重新输入。\n");
				continue;
			}
		} while (!isValidProductID(pro.productID) || isDuplicateProductID(pro.productID, count + 1));

		// 输入商品名称
		do {
			printf("输入商品名称（不超过15个字符）:");
			scanf_s("%100s", pro.produtName, sizeof(pro.produtName));
			clearInputBuffer();
			if (strlen(pro.produtName) > 15) {
				printf("商品名称无效，请重新输入。\n");
			}
			else if (!isValidProductName(pro.produtName)) {
				printf("商品名称无效，请重新输入。\n");
			}
		} while (strlen(pro.produtName) > 15 || !isValidProductName(pro.produtName));

		// 输入商品单价
		do {
			printf(" 输入商品单价（不超过5位数）:");
			if (scanf_s("%lf", &(pro.price)) != 1) {
				printf("无效的输入，请重新输入。\n");
				clearInputBuffer();
				continue;
			}
			clearInputBuffer();
			if (!isValidPrice(pro.price)) {
				printf("商品单价无效，请重新输入。\n");
			}
		} while (!isValidPrice(pro.price));

		// 输入总量
		do {
			printf("     输入总量（不超过5位数）:");
			if (scanf_s("%d", &(pro.total)) != 1) {
				printf("无效的输入，请重新输入。\n");
				clearInputBuffer();
				continue;
			}
			clearInputBuffer();
			if (!isValidQuantity(pro.total)) {
				printf("商品总量无效，请重新输入。\n");
			}
		} while (!isValidQuantity(pro.total));

		// 输入销售量
		do {
			printf("   输入销售量（不超过5位数）:");
			if (scanf_s("%d", &(pro.sales)) != 1) {
				printf("无效的输入，请重新输入。\n");
				clearInputBuffer();
				continue;
			}

			if (!isValidQuantity(pro.sales)) {
				printf("商品销售量无效，请重新输入。\n");
				clearInputBuffer();
			}
		} while (!isValidQuantity(pro.sales));

		pro.inventory = pro.total - pro.sales;
		pro.revenue = pro.sales * pro.price;
		products[count] = pro;
		count++;
		//----将该循环的product信息写入"D:\test.txt"----
		SaveProductToFile(pro);
		//-------------------------------------------------------------
	}
	std::cout << "信息录入完成!" << std::endl;
	// 
}
int num(long n) {
	return (n > 0 && n < 1000);
}
//检测输入的商品代码是否重复
int isDuplicateProductID(long productID, int index) {
	for (int i = 0; i < index; i++) {
		if (products[i].productID == productID) {
			return 1; // 商品代码已存在
		}
	}
	return 0; // 商品代码不重复
}
// 验证商品代码是否有效
int isValidProductID(long productID) {
	return (productID > 0 && productID < 100000);
}
// 验证商品单价是否有效
int isValidPrice(double price) {
	return (price > 0 && price < 100000);
}
// 验证商品数量是否有效
int isValidQuantity(int quantity) {
	return (quantity >= 0 && quantity < 100000);
}
// 清除输入缓冲区
void clearInputBuffer() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}
// 验证商品名称是否有效
int isValidProductName(const char* productName) {
	// 商品名称不能为空且不能包含空格
	if (productName[0] == '\0' || strchr(productName, ' ') != NULL) {
		return 0;
	}
	return 1;
}
//商品显示函数
void ProductBrowsing() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");
		return;
	}
	printRepeatedChar('-', 82);
	printf("| %-8s | %-15s | %-5s | %-8s | %-6s | %-6s | %-14s |\n",
		"商品代码", "商品名称", "总量", "单价", "销售量", "库存量", "销售额");

	// products数已经填充了商品信息
	for (int i = 0; i < count; i++) {
		// products[i]是结构体类型，包含商品信息
		printRepeatedChar('-', 82);

		printf("| %-8d | %-15s | %-5d | %-8.2lf | %-6d | %-6d | %-14.2lf |\n",
			products[i].productID,
			products[i].produtName,
			products[i].total,
			products[i].price,
			products[i].sales,
			products[i].inventory,
			products[i].revenue);
	}

	printRepeatedChar('-', 82);

}
//格式对应函数
void printRepeatedChar(char c, int num) {
	for (int i = 0; i < num; i++) {
		printf("%c", c);
	}
	printf("\n");
}
//删除数据函数
void ProductDeletion() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");

		return;
	}
	ProductBrowsing();
	long ID;
	do {
		printf(" 请输入要删除的商品代码(输入-1返回菜单)");
		if (scanf_s("%ld", &(ID)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}
		if (ID == -1) {
			return;
		}
		if (!isValidProductID(ID)) {
			printf("商品代码无效，请重新输入。\n");
			clearInputBuffer();
		}
	} while (!isValidProductID(ID));
	int a = -1;
	for (int i = 0; i < count; i++) {
		if (products[i].productID == ID) {
			a = i;
			products[a] = products[count - 1];
			count--;
			printf("商品已成功删除。\n");
			break;
		}
	}
	if (a == -1) {
		printf("未找到指定的商品。\n");
	}
	char choice;
	do {
		printf("是否要继续删除商品？ (按'y'继续，按'n'退出):\n ");
		scanf_s(" %c", &choice);
		clearInputBuffer();

		if (choice == 'y' || choice == 'Y') {
			ProductDeletion(); // 递归调用继续删除商品
			return; // 返回上级函数后结束当前函数的执行
		}
		else if (choice == 'n' || choice == 'N') {
			FILE* tempFile = NULL;
			errno_t err = fopen_s(&tempFile, "D:\\temp.txt", "w");
			if (err != 0 || tempFile == NULL) {
				printf("临时文件打开失败。\n");

				return;
			}
			for (int i = 0; i < count; i++) {
				fprintf(tempFile, "%ld %s %.2lf %d %d %d %.2lf\n",
					products[i].productID, products[i].produtName, products[i].price, products[i].total, products[i].sales, products[i].inventory, products[i].revenue);
			}
			fclose(tempFile);

			remove("D:\\test.txt");
			rename("D:\\temp.txt", "D:\\test.txt");
			return; // 退出删除商品功能
		}
		else {
			printf("无效的输入，请重新输入。\n");
		}
	} while (1);
	//----------------删除商品操作-----------------------
	//原理是用新文件覆盖原文件，将剩余商品信息重新写入

	//---------------------------------------------------

}
//商品信息修改函数
void ProductModification() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");

		return;
	}
	ProductBrowsing();
	long ID;
	do {
		printf(" 请输入要修改商品的代码(输入-1返回菜单)");
		if (scanf_s("%ld", &(ID)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}
		if (ID == -1) {
			return;
		}
		if (!isValidProductID(ID)) {
			printf("商品代码无效，请重新输入。\n");
		}
	} while (!isValidProductID(ID));
	int a = -1;
	for (int i = 0; i < count; i++) {
		if (products[i].productID == ID) {
			a = i;
			printf("查询到该商品\n");
			break;
		}
	}
	if (a == -1) {
		printf("未找到指定的商品。\n");
		return;
	}
	//输入名称
	do {
		printf("      输入修改后商品名称:");
		scanf_s("%100s", products[a].produtName, sizeof(products[a].produtName));
		clearInputBuffer();
		if (strlen(products[a].produtName) > 15) {
			printf("商品名称无效，请重新输入。\n");
		}
		else if (!isValidProductName(products[a].produtName)) {
			printf("商品名称无效，请重新输入。\n");
		}
	} while (strlen(products[a].produtName) > 15 || !isValidProductName(products[a].produtName));
	//输入总量
	do {
		printf("  请输入修改后的商品总量:");
		if (scanf_s("%d", &(products[a].total)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}
		clearInputBuffer();
		if (!isValidQuantity(products[a].total)) {
			printf("商品总量无效，请重新输入。\n");
		}
	} while (!isValidQuantity(products[a].total));
	// 输入商品单价
	do {
		printf("  请输入修改后的商品单价:");
		if (scanf_s("%lf", &(products[a].price)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}
		clearInputBuffer();
		if (!isValidPrice(products[a].price)) {
			printf("商品单价无效，请重新输入。\n");
		}
	} while (!isValidPrice(products[a].price));

	// 输入销售量
	do {
		printf("请输入修改后的商品销售量:");
		if (scanf_s("%d", &(products[a].sales)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}

		if (!isValidQuantity(products[a].sales)) {
			printf("商品销售量无效，请重新输入。\n");
			clearInputBuffer();
		}
	} while (!isValidQuantity(products[a].sales));


	products[a].inventory = products[a].total - products[a].sales;
	products[a].revenue = products[a].sales * products[a].price;
	printf("商品信息修改成功。\n");
	//----------------执行修改操作-----------------------
	SaveAllProductsToFile();
	//---------------------------------------------------

}
//计算各类商品的库存量及销售额
void InventoryAndSales() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");

		return;
	}
	for (int i = 0; i < count; i++) {
		printf("商品库存量：%-d ", products[i].inventory);
		printf("商品销售额：%-.2lf\n", products[i].revenue);
	}
}
//排序函数
void Sort() {
	if (count == 0) {
		printf("目前没有任何商品信息。\n");

		return;
	}
	for (int i = 0; i < count - 1; i++) {
		for (int j = 0; j < count - i - 1; j++) {
			if (products[j].inventory > products[j + 1].inventory) {
				product temp = products[j];
				products[j] = products[j + 1];
				products[j + 1] = temp;
			}
			else if (products[j].inventory == products[j + 1].inventory) {
				if (products[j].sales > products[j + 1].sales) {
					product temp1 = products[j];
					products[j] = products[j + 1];
					products[j + 1] = temp1;
				}
			}
		}
	}

	//--------排序后更新文件----------
	SaveSortedProductsToFile();
	//---------------------------------------
	std::cout << "已排序完成" << std::endl;
	ProductBrowsing();

}
//查找函数
void lookup() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");

		return;
	}
	long ID;
	do {
		printf("请输入要查找的商品代码：");
		if (scanf_s("%ld", &(ID)) != 1) {
			printf("无效的输入，请重新输入。\n");
			clearInputBuffer();
			continue;
		}

		if (!isValidProductID(ID)) {
			printf("商品代码无效，请重新输入。\n");
			clearInputBuffer();
		}
	} while (!isValidProductID(ID));
	int a = -1;
	for (int i = 0; i < count; i++) {
		if (products[i].productID == ID) {
			a = i;
			printf("查询到该商品\n");
			printRepeatedChar('-', 82);

			printf("| %-8s | %-15s | %-5s | %-8s | %-6s | %-6s | %-14s |\n",
				"商品代码", "商品名称", "总量", "单价", "销售量", "库存量", "销售额");
			printRepeatedChar('-', 82);

			printf("| %-8d | %-15s | %-5d | %-8.2lf | %-6d | %-6d | %-14.2lf |\n",
				products[i].productID,
				products[i].produtName,
				products[i].total,
				products[i].price,
				products[i].sales,
				products[i].inventory,
				products[i].revenue);
			printRepeatedChar('-', 82);

			break;
		}
	}
	if (a == -1) {
		printf("未找到指定的商品。\n");

		return;
	}
}

//计算销售总额函数
void calculate() {
	if (count == 0) {
		printf("当前没有任何商品信息\n");

		return;
	}
	double sum = 0;
	for (int i = 0; i < count; i++) {
		sum = sum + products[i].revenue;
	}
	printf("销售总额为:%.2lf\n", sum);

}

//----------将修改后的商品写入"D:\test.txt"----------
void SaveAllProductsToFile() {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, "D:\\test.txt", "w"); //打开文件
	if (err != 0 || file == NULL) {
		printf("文件打开失败。\n");
		return;
	}
	for (int i = 0; i < count; i++) {
		fprintf(file, "%ld %s %.2lf %d %d %d %.2lf\n",
			products[i].productID, products[i].produtName, products[i].price, products[i].total, products[i].sales, products[i].inventory, products[i].revenue);
	}			//写入
	fclose(file); // 关闭文件
	printf("所有商品信息已更新到文件。\n");
}
//---------------------------------------------------

//-------------读取文件里的商品------------------
void ReadProduct() {
	FILE* file = NULL;
	errno_t err = fopen_s(&file, "D:\\test.txt", "r");
	if (err != 0 || file == NULL) {
		printf("文件打开失败。\n");
		return;
	}
	product tempProduct;
	int i = 0;
	while (fscanf_s(file, "%ld %99s %lf %d %d %d %lf\n",
		&tempProduct.productID, tempProduct.produtName, (unsigned)_countof(tempProduct.produtName), &tempProduct.price, &tempProduct.total, &tempProduct.sales, &tempProduct.inventory, &tempProduct.revenue) != EOF) {
		products[i] = tempProduct;
		i++;
	}
	count = i;
	fclose(file);
	printf("商品信息读取完成。\n");
}

//------------------------------------------------------

//-------将排序的商品信息存入文件------------
void SaveSortedProductsToFile() {
	FILE* tempFile = NULL;
	errno_t err = fopen_s(&tempFile, "D:\\temp.txt", "w");
	if (err != 0 || tempFile == NULL) {
		printf("临时文件打开失败。\n");

		return;
	}
	for (int i = 0; i < count; i++) {
		fprintf(tempFile, "%ld %s %.2lf %d %d %d %.2lf\n",
			products[i].productID, products[i].produtName, products[i].price, products[i].total, products[i].sales, products[i].inventory, products[i].revenue);
	}
	fclose(tempFile);

	remove("D:\\test.txt");
	rename("D:\\temp.txt", "D:\\test.txt");
	return; // 退出删除商品功能
}
//-------------------------------------------------------

//将该循环的product信息写入"D:\test.txt"
void SaveProductToFile(product pro) {
	FILE* file = NULL; // 初始化文件指针为NULL
	errno_t err = fopen_s(&file, "D:\\test.txt", "a"); // 使用fopen_s打开文件
	if (err != 0 || file == NULL) { // 检查文件是否成功打开
		printf("文件打开失败。\n");
		return;
	}

	// 写入文件
	fprintf(file, "%ld %s %.2lf %d %d %d %.2lf\n",
		pro.productID, pro.produtName, pro.price, pro.total, pro.sales, pro.inventory, pro.revenue);

	fclose(file); // 关闭文件
	printf("商品信息已保存到文件。\n");
}
//新建文件
void filebuild() {
	const char* filePath = "D:\\test.txt";
	FILE* file = NULL;
	errno_t err;
	err = fopen_s(&file, filePath, "r");
	if (err != 0 || file == NULL) {
		err = fopen_s(&file, filePath, "w");
		if (err == 0 && file != NULL) {
			fclose(file);
		}
		else {
			printf("文件创建失败。检查D:/下是否有test.txt\n");
		}
	}
	else {
		fclose(file);
	}
}
//读取文件

//显示主界面
void ShowMenu(int selected) {
	clearScreen();
	printf("|**********************【商品管理系统】********************|\n");
	printf("|                    %s1.商品信息录入%s                    |\n", selected == 1 ? ">> " : "  ", selected == 1 ? " <<" : "  ");
	printf("|                    %s2.商品信息显示%s                    |\n", selected == 2 ? ">> " : "  ", selected == 2 ? " <<" : "  ");
	printf("|                    %s3.商品信息删除%s                    |\n", selected == 3 ? ">> " : "  ", selected == 3 ? " <<" : "  ");
	printf("|                    %s4.商品信息修改%s                    |\n", selected == 4 ? ">> " : "  ", selected == 4 ? " <<" : "  ");
	printf("|                    %s5.商品信息排序%s                    |\n", selected == 5 ? ">> " : "  ", selected == 5 ? " <<" : "  ");
	printf("|                    %s6.查询指定商品%s                    |\n", selected == 6 ? ">> " : "  ", selected == 6 ? " <<" : "  ");
	printf("|                    %s7.计算营销总额%s                    |\n", selected == 7 ? ">> " : "  ", selected == 7 ? " <<" : "  ");
	printf("|                      %s0.退出系统%s                      |\n", selected == 0 ? ">> " : "  ", selected == 0 ? " <<" : "  ");
	printf("|**********************************************************|\n");
}

//清屏
void clearScreen() {
	system("cls");
}

int main()
{
	filebuild();
	ReadProduct();
	int choice = -1;
	int selected = 0;
	int key;

	ShowMenu(selected);

	while (1) {
		key = _getch();
		if (key == 224) {
			key = _getch();
			switch (key) {
			case 72:
				selected = (selected == 0) ? 7 : selected - 1;
				break;
			case 80:
				selected = (selected == 7) ? 0 : selected + 1;
				break;
			}
			ShowMenu(selected);
		}
		else if (key == 13) {
			choice = selected;
			clearScreen();
			switch (choice) {
			case 0:
				printf("\t\t【退出系统】\n");
				return 0;
			case 1:
				printf("\t\t【商品信息录入】\n");
				ProductEntry();
				break;
			case 2:
				printf("\t\t\t\t【商品信息显示】\n");
				ProductBrowsing();
				break;
			case 3:
				printf("\t\t【商品信息删除】\n");
				ProductDeletion();
				break;
			case 4:
				printf("\t\t【商品信息修改】\n");
				ProductModification();
				break;
			case 5:
				printf("\t\t【商品信息排序】\n");
				Sort();
				break;
			case 6:
				printf("\t\t【查询指定商品】\n");
				lookup();
				break;
			case 7:
				printf("\t\t【计算营销总额】\n");
				calculate();
				break;
			default:
				printf("\t\t输入错误，请重新输入代码！\n");
				break;
			}

			printf("按回车键继续...");
			getchar(); // 等待用户按回车键
			getchar(); // 处理多余的换行符
			ShowMenu(selected);
		}
		else if (key >= '0' && key <= '7') { // 数字键
			choice = key - '0';
			clearScreen();
			switch (choice) {
			case 0:
				printf("\t\t【退出系统】\n");
				return 0;
			case 1:
				printf("\t\t【商品信息录入】\n");
				ProductEntry();
				break;
			case 2:
				printf("\t\t\t\t【商品信息显示】\n");
				ProductBrowsing();
				break;
			case 3:
				printf("\t\t【商品信息删除】\n");
				ProductDeletion();
				break;
			case 4:
				printf("\t\t【商品信息修改】\n");
				ProductModification();
				break;
			case 5:
				printf("\t\t【商品信息排序】\n");
				Sort();
				break;
			case 6:
				printf("\t\t【查询指定商品】\n");
				lookup();
				break;
			case 7:
				printf("\t\t【计算营销总额】\n");
				calculate();
				break;
			default:
				printf("\t\t输入错误，请重新输入代码！\n");
				break;
			}

			printf("按回车键继续...");
			getchar(); // 等待用户按回车键
			getchar(); // 处理多余的换行符
			ShowMenu(selected);
		}
	}
}

