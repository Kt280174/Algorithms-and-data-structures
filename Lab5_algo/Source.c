#pragma warning (disable: 4996)
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#define M 10
struct tree {
	int data;
	struct tree* left;
	struct tree* right;
};
struct table {
	char* str1;
	char* str2;
};
char* toStr(int num) {
	int len = 0;
	int n = num;
	while (n != 0) {
		n = n / 10;
		len++;
	}
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
int A[100][100];
int x = 1;
void InitMatrix(struct tree* t, int y) {
	if (t != NULL)
	{
		InitMatrix(t->left, y + 1);
		A[x][y] = t->data;
		x++;
		InitMatrix(t->right, y + 1);
	}
}
int maxDepth(struct tree* t) {
	if (t == NULL) {
		return 0;
	}
	else {
		int lDepth = maxDepth(t->left);
		int rDepth = maxDepth(t->right);
		if (lDepth > rDepth) {
			return (lDepth + 1);
		}
		else return (rDepth + 1);
	};
}
void Print_tree(int A[100][100], struct tree* t) {
	printf("Binary tree:\n");
	for (int i = 0; i < maxDepth(t); i++) {
		for (int j = 0; j < x; j++) {
			if (A[j][i] == NULL) {
				printf("  ");
			}
			else printf(" %d", A[j][i]);
		}
		printf("\n");
	}
}
struct tree* Add(struct tree* t, int x)
{
	if (t == NULL)
	{
		t = (struct tree*)malloc(sizeof(struct tree));
		t->data = x;
		t->left = t->right = NULL;
	}
	else
	{
		if (x < t->data)
			t->left = Add(t->left, x);
		else
		{
			if (x > t->data)
				t->right = Add(t->right, x);
		}
	}
	return t;
}
struct tree* Search(struct tree* root, int key) {
	struct tree* current = root;
	while (current != NULL && current->data != key) {
		if (key < current->data) current = current->left;
		else current = current->right;
	}
	return current;
}
char* InitTableLeaf(struct tree* t) {
	if (t == NULL) {
		return "-";
	}
	char* line = "";
	line = connect(line, toStr(t->data), "");
	if (t->left != NULL) {
		line = connect(line, "(", InitTableLeaf(t->left));
		line = connect(line, ")", "");
	}
	if (t->right != NULL) {
		line = connect(line, "(", InitTableLeaf(t->right));
		line = connect(line, ")", "");
	}
	return line;
}
void InitTable(int n, struct table A[M + 1], struct tree *t) {
	if (t == NULL) {
		return;
	}
	for (int i = 1; i <= n; i++) {
		A[i].str1 = InitTableLeaf(Search(t, i)->left);
		A[i].str2 = InitTableLeaf(Search(t, i)->right);
	}
}
void printTable(struct table A[M + 1], int n) {
	int maxLen_key = 0;
	int maxLen_str1 = 0;
	int maxLen_str2 = 0;
	for (int i = 1; i <= n; i++) {
		if (strlen(toStr(i)) > maxLen_key) {
			maxLen_key = strlen(toStr(i));
		}
		if (strlen(A[i].str1) > maxLen_str1) {
			maxLen_str1 = strlen(A[i].str1);
		}
		if (strlen(A[i].str2) > maxLen_str2) {
			maxLen_str2 = strlen(A[i].str2);
		}
	}
	printf("Link Table: \n");
	printf("| Key");
	for (int i = 0; i < maxLen_key - 3; i++) {
		printf(" ");
	}
	printf("| left leaf");
	for (int i = 0; i < maxLen_str1 - 6; i++) {
		printf(" ");
	}
	printf("| right leaf");
	for (int i = 0; i < maxLen_str2 - 9; i++) {
		printf(" ");
	}
	printf("|\n");
	for (int i = 1; i <= n; i++) {
		printf("| %d", i);
		for (int j = 0; j < maxLen_key - strlen(toStr(i)); j++) {
			printf(" ");
		}

		printf(" | %s", A[i].str1);
		for (int j = 0; j < maxLen_str1 - strlen(A[i].str1); j++)
			printf(" ");

		printf(" | %s", A[i].str2);
		for (int j = 0; j < maxLen_str2 - strlen(A[i].str2); j++)
			printf(" ");
		printf(" |\n");
	}
}

int main() {
	struct tree* t = NULL;
	struct table B[M + 1];
	for (int i = 1; i <= 10; i++) {
		int num;
		num = rand() % 10 + 1;
		while (Search(t, num) != NULL) {
			num = rand() % 10 + 1;
		}
		t = Add(t, num);
	}
	InitMatrix(t, 0);
	Print_tree(A, t);
	InitTable(10, B, t);
	printTable(B, 10);


}
