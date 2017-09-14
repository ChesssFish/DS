#include<stdio.h>
struct Node
{
	char name[20];
	char brand[20];
};
int main()
{
	Node* n = new Node;
	scanf_s("%s", n->name, 20);
	scanf_s("%s", n->brand, 20);
	return 0;
}