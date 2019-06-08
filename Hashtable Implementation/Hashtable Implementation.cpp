#include<iostream>

struct Product {

	int id;
	char* name;
	float price;
};

struct Node {

	Product info;
	Node* next;
};

struct Hashtable {

	Node** table;
	int size;
};

int getKey(int id, Hashtable h) {

	int key = id % h.size;
	return key;
}

Product createProduct(int id, const char* name, float price) {

	Product newProduct;
	newProduct.id = id;
	newProduct.price = price;
	newProduct.name = (char*)malloc(sizeof(char)*strlen(name) + 1);
	strcpy(newProduct.name, name);
	return newProduct;
}

Node* createNode(Product product, Node* next) {

	Node* node = (Node*)malloc(sizeof(Node));
	node->info = product;
	node->next = next;
	return node;
}

Hashtable initHashtable(int size) {

	Hashtable newHashtable;
	newHashtable.table = (Node**)malloc(sizeof(Node*)*size);
	for (int i = 0; i < size; i++)
		newHashtable.table[i] = NULL;
	newHashtable.size = size;
	return newHashtable;
}

Node* insertAtTheEnd(Node* head, Product prod) {

	Node* newNode = createNode(prod, NULL);
	Node* p = head;

	if (head) {
		while (p->next) {
			p = p->next;
		}
		p->next = newNode;
	}
	else {
		head = newNode;
	}

	return head;
}

void insertInHashtable(Hashtable h, Product prod) {

	int hashKey = getKey(prod.id, h);
	Node* position = h.table[hashKey];

	if (h.table[hashKey]) {

		h.table[hashKey] = insertAtTheEnd(h.table[hashKey], prod);
		
	}
	else{
		h.table[hashKey] = createNode(prod, NULL);
	}

}

void displayHashtable(Hashtable h) {

	for (int i = 0; i < h.size; i++) {

		printf("%d: ", i);

		Node* temp = h.table[i];

		while (temp) {
			printf("%d - %s ; ", temp->info.id, temp->info.name, temp->info.price);
			temp = temp->next;
		}

		printf("\n");
	}
}

void findProductById(Hashtable h, int id) {

	int key = getKey(id, h);
	Node* p = h.table[key];
	bool found = false;

	if (key < h.size) {

		while (p) {

			if (p->info.id == id) {
				printf("The product you searched for is %s \n", p->info.name);
				found = true;
			}
			p = p->next;
		}
	}
	else
		printf("Search error!\n");

	if (found == false)
		printf("The product you requested was not found \n");
}

int main() {

	Hashtable h = initHashtable(10);

	insertInHashtable(h, createProduct(1, "Bread", 5));
	insertInHashtable(h, createProduct(4, "Shampoo", 20));
	insertInHashtable(h, createProduct(11, "Pizza", 25));
	insertInHashtable(h, createProduct(21, "Butter", 10));
	insertInHashtable(h, createProduct(44, "Headphones", 45));
	insertInHashtable(h, createProduct(49, "Chips", 5));
	insertInHashtable(h, createProduct(155, "Beer", 7));

	displayHashtable(h);

	findProductById(h, 49);
}