#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int data;
	struct Node* next;
} Node;

Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node*));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// them 1 phan tu vao dau list
Node* addToHead(Node* head, int data) {
	Node* newHead = createNode(data);
	newHead->next = head;
	
	return newHead;
}

// them 1 phan tu vao cuoi list
Node* addToTail(Node* head, int data) {
	if (head == NULL) {
        return createNode(data);
    }
    
	Node* currentNode = head;
	
	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}
	
	currentNode->next = createNode(data);
	
	return head;
}

// chen so x vao vi tri thu k
Node* insertNode(Node* head, int x, int k) {
	if (k == 1) {
		return addToHead(head, x);
	}
	
	
	Node* currentNode = head;
	Node* newNode = createNode(x);
	
	while (currentNode->next != NULL && k > 2) {
		currentNode = currentNode->next;
		k--;
	}
	
	newNode->next = currentNode->next;
	currentNode->next = newNode;
	
	return head;
}

// xoa phan tu o vi tri pos
Node* deleteNode(Node* head, int pos) {
	if (head == NULL) {
		return NULL;
	}
	
	if (pos == 1) {
        head = head->next;
        return head;
    }
	
	Node* currentNode = head;
	while (currentNode != NULL && pos > 2) {
		currentNode = currentNode->next;
		pos--;
	}
	
	// Trường hợp vị trí cần xoá không tồn tại
    if (currentNode == NULL || currentNode->next == NULL) {
        return head;
    }
	
	currentNode->next = currentNode->next->next;
	
	return head;
}

// in ra day so vua nhap
void printList(Node* head) {
	Node* currentNode = head;
	while (currentNode != NULL) {
		printf("%d ", currentNode->data);
		currentNode = currentNode->next; 
	}
	printf("\n\n");
}

int main() {
	int n, k, x, choice;
	
	printf("Nhap so luong phan tu: ");
	scanf("%d", &n);
	
	Node* head = NULL;
	
	for (int i = 0; i < n; i++) {
		int data;
		printf("Nhap phan tu thu %d: ", i + 1);
		scanf("%d", &data);
		head = addToTail(head, data);
	}	
					
	while (1) {
        printf("\n\nChon mot hanh dong:\n");
		printf("1. Them phan tu vao dau\n");
		printf("2. Them phan tu vao cuoi\n");
		printf("3. Chen phan tu vao vi tri\n");
		printf("4. Xoa phan tu o vi tri\n");
		printf("5. Thoat\n");
		scanf("%d", &choice);
        
        switch (choice) {
			case 1:
				printf("Nhap so ban can them vao dau day so: ");
				scanf("%d", &x);
				head = addToHead(head, x);
			
				printf("\nDay so moi cua ban la: ");
				printList(head);
				break; 	 	
			case 2:
				printf("Nhap so ban can them vao cuoi day so: ");
				scanf("%d", &x);
				head = addToTail(head, x);
			
				printf("\nDay so moi cua ban la: ");
				printList(head);
				break;
			case 3:
				printf("Nhap so ban can chen: ");
				scanf("%d", &x);
				printf("Nhap vi tri ban can chen: ");
				scanf("%d", &k);
				if (1 <= k && k <= n) {
					head = insertNode(head, x, k);
		
					printf("\nDay so moi cua ban la: ");
					printList(head);
				} else {
					printf("Gia tri cua k khong hop le!");
				}
				break;
			case 4:
				printf("Nhap vi tri ban can xoa: ");
				scanf("%d", &k);
				head = deleteNode(head, k);
		
				printf("\nDay so moi cua ban la: ");
				printList(head);
				break;
			case 5:
                printf("Thoat chuong trinh...\n");
                return 0;
            default:
                printf("Lua chon khong hop le!\n");
		}
	}

	return 0;
}