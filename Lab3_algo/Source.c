#pragma warning(disable : 4996)
#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int check = 0;
char* toStr(int num, int len) {
	char* str = (char*)malloc((len + 1) * sizeof(char));
	str[len] = NULL;
	if (num == 0) {
		str[0] = num + '0';
		return str;
	}
	while (num != 0) {
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	} 
	return str;
}
char* connect(char* str1, char* str2, char* str3) {
	int n1 = strlen(str1);
	int n2 = strlen(str2);
	int n3 = strlen(str3);
	char* str = (char*)malloc(sizeof(char) * (n1 + n2 + n3));
	sprintf(str, "%s%s%s\0", str1, str2, str3);
	return str;
}
void generate_expressions_helper(char* arr, int target, char* expression, int index, int current_value, int prev_num, FILE*fpt) {

	if (index == strlen(arr)) {
		if (current_value == target) {
			fprintf(fpt,"%s\n", expression);
			check = 1;
		}
		return 0;
	}
	for (int i = index; i < strlen(arr); i++) {
		int num = 0;
		for (int j = index; j < i + 1; j++) {
			num = num * 10 + ((int)arr[j] - 48);
		}
		if (num == 0 && i + 1 - index != 1) {
			break;
		}
		if (index == 0) {
			generate_expressions_helper(arr, target, toStr(num, i + 1 - index), i + 1, num, num,fpt);
		}
		else {
			generate_expressions_helper(arr, target, connect(expression, "+", toStr(num, i + 1 - index)), i + 1, current_value + num, num,fpt);
			generate_expressions_helper(arr, target, connect(expression, "-", toStr(num, i + 1 - index)), i + 1, current_value - num, -num,fpt);
			generate_expressions_helper(arr, target, connect(expression, "*", toStr(num, i + 1 - index)), i + 1, current_value - prev_num + prev_num * num, prev_num * num, fpt);
			if (num == 0) {
				break;
			}
			if (prev_num % num == 0) {
				generate_expressions_helper(arr, target, connect(expression, "/", toStr(num, i + 1 - index)), i + 1, current_value - prev_num + prev_num / num, prev_num / num, fpt);
			}
		}
	}
}
void generate_expressions(char* arr, int target) {
	FILE* fpt = fopen("output.txt", "w+");
	if (fpt == NULL) {
		printf("Error!");
		exit(1);
	}
	generate_expressions_helper(arr, target, "", 0, 0, 0, fpt);
	fclose(fpt);
	
}
int main() {
	char str[30];
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("Error!");
		exit(1);
	}
	char c;
	int i = 0;
	while ((c = fgetc(fp))!= '\n') {
		str[i] = c;
		i++;
	} 
	int number;
	str[i] = NULL;
	fscanf(fp, "%d", &number);
	generate_expressions(str, number);
	if (check == 0) {
		FILE* fpt = fopen("output.txt", "w+");
		if (fpt == NULL) {
			printf("Error");
			exit(1);
		}
		fprintf(fpt, "%d", 0);
		fclose(fpt);
	}
	fclose(fp);
}
