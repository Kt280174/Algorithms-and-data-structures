#pragma warning (disable: 4996)
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct tree {
	int numLeaves;
	int data;
	struct tree* left;
	struct tree* right;
};		
int countLeaf(struct tree* t) {
	if (t == NULL) {
		return 0;
	}
	if (t->left == NULL && t->right == NULL) {
		return 1;
	}
	return countLeaf(t->left) + countLeaf(t->right);
}
void updatenumLeaves(struct tree* t) {
	if (t == NULL) {
		return;
	}
	t->numLeaves = countLeaf(t);
	updatenumLeaves(t->left);
	updatenumLeaves(t->right);
}

int A[100][100];
int x = 1;
void PrintTree(struct tree* t, int y) {
	if (t != NULL)
	{
		PrintTree(t->left, y + 1);
		A[x][y] = t->numLeaves;
		x++;
		PrintTree(t->right, y + 1);
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


int main() {
	struct tree* root = NULL;;
	root = Add(root, 50);
	root = Add(root, 20);
	Add(root, 30);
	Add(root, 40);
	Add(root, 70);
	Add(root, 60);
	Add(root, 80);
	Add(root, 10);
	Add(root, 90);
	Add(root, 12);
	updatenumLeaves(root);
	PrintTree(root, 0);
	for (int i = 0; i < maxDepth(root); i++) {
		for (int j = 0; j < x; j++) {
			if (A[j][i] == NULL) {
				printf("  ");
			}
			else printf(" %d", A[j][i]);
		}
		printf("\n");
	}

}