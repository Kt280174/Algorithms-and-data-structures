#pragma warning (disable:4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node {
	char family[20];
	char number[15];
	struct node* next;

};
struct character
{
	char a;
	struct node* head;
};
// Function to create a new contact node
struct node* createNode(char family[], char number[]) {
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	strcpy(newNode->family, family);
	strcpy(newNode->number, number);
	newNode->next = NULL;
	return newNode;
}
void display(struct node* head) {
	struct node* temp;
	temp = head;
	while (temp != NULL) {
		printf("%s: %s\n", temp->family, temp->number);
		temp = temp->next;
	}
}
void print_list(struct character* A[]) {
	printf("Here is your phone book:\n");
	for (int i = 0; i < 26; i++) {
		printf("%c\n", A[i]->a);
		display(A[i]->head);
	}
}
void save_in_file(struct character* A[]) {
	FILE* fpt;
	fpt = fopen("telephone_book.txt", "w");
	if (fpt == NULL) {
		printf("Error");
		exit(1);
	}
	for (int i = 0; i < 26; i++) {

		fprintf(fpt, "%c:\n", A[i]->a);
		struct node* temp;
		temp = A[i]->head;
		while (temp != NULL) {
			fprintf(fpt, "%s: %s\n", temp->family, temp->number);
			temp = temp->next;
		}
	}
	fclose(fpt);
}
void push_in_list(struct character* A[]) {
	char input[50];
	char familier[20];
	char numberer[15];
	printf("Enter the family and phone number, which need to insert:");
	//fgets(input, sizeof(input), stdin);
	//sscanf(input, "%s %s", familier, numberer);
	scanf("%s %s", familier, numberer);

	struct node* newnode = createNode(familier, numberer);

	for (int i = 0; i < 26; i++) {
		if (newnode->family[0] == A[i]->a) {
			struct node* old_node = A[i]->head;
			newnode->next = old_node;
			A[i]->head = newnode;
		}
	}
}

void searchNode(struct node* head, char fm[]) {
	struct node* temp = head;
	while (temp != NULL) {
		if (strcmp(temp->family, fm) == 0) {
			printf("number telephone :\n");
			printf("%s\n", temp->number);
			return 0;
		}
		temp = temp->next;
	}
	printf("Cannot find this number of family!\n");
}
void search_in_list(struct character* A[]) {
	char family[20];
	printf("Enter the family you want to look:");
	scanf("%s", family);
	for (int i = 0; i < 26; i++) {
		if (family[0] == A[i]->a) {
			searchNode(A[i]->head, family);
			return 0;
		}
	}
	printf("Cannot find this family in phone book\n");
}

void delListNode(struct character* A[]) {
	// Can safely assume vector is NULL or fully built.
	char family[20];
	printf("Enter family, you want to remove:\n");
	scanf("%s", family);
	for (int i = 0; i < 26; i++) {
		if (family[0] == A[i]->a) {
			struct node* temp = A[i]->head, * prev;
			if (temp != NULL && strcmp(temp->family, family) == 0) {
				A[i]->head = temp->next;
				free(temp);
				print_list(A);
				return 0;
			}
			while (temp != NULL && strcmp(temp->family, family) == 0) {
				prev = temp;
				temp = temp->next;
			}
			if (temp == NULL) {
				return 0;
			}
		}
	}
	printf("Cannot find this family in phone book");

}
void sort(struct character* A[]) {
	for (int i = 0; i < 26; i++) {
		for (struct node* pTmp = A[i]->head; pTmp != NULL; pTmp = pTmp->next) {
			for (struct node* pTmp2 = pTmp->next; pTmp2 != NULL; pTmp2 = pTmp2->next) {
				if (strcmp(pTmp->family, pTmp2->family) > 0) {
					char temp[20];
					strcpy(temp, pTmp->family);
					strcpy(pTmp, pTmp2);
					strcpy(pTmp2, temp);
				}
			}
		}

	}
}
struct character* createHeaderList(char x) {
	struct character* newHeader = (struct character*)malloc(sizeof(struct character));
	newHeader->a = x;
	newHeader->head = NULL;
	return newHeader;
}
int main() {
	struct character* A[26];
	for (int i = 0; i < 26; i++) {
		struct character* newHeader = createHeaderList((char)(i + 65));
		A[i] = newHeader;
	}
	int ch;
	do {
		printf("------------Welcome-----------\n");
		printf("Choose one of these option:\n");
		printf("1.Insert\n2. Search\n3. Delete\n4. Sort\n5. Display\n");
		printf("If you want to exit, enter 0\n");
		scanf("%d", &ch);
		switch (ch) {
		case 1: push_in_list(A);
			break;
		case 2: search_in_list(A);
			break;
		case 3: delListNode(A);
			break;
		case 4: sort(A);
			break;
		case 5: print_list(A);
			break;
		}
		save_in_file(A);

	} while (ch != 0);
	return 0;

}