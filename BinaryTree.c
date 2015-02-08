/* Binary Tree Implementation */

#include <stdlib.h>
#include <stdio.h>

/* Tree Node */
typedef struct Node {
   int data;
   struct Node *left;
   struct Node *right;
}Node;

/* Queue Node Struct */
typedef struct QueueNode {
   Node *node;
   struct QueueNode *next;
   struct QueueNode *prev;
}QueueNode;

/* Queue Struct */
typedef struct Queue {
   QueueNode *head;
   QueueNode *tail;
}Queue;

/* Add to Tail of Queue */
void enqueue(Queue *queue, Node *node) {
   QueueNode *new = calloc(1, sizeof(struct QueueNode));

   new->node = node;

   if ((*queue).head) {
      new->prev = (*queue).tail;
      (*queue).tail->next = new;
      (*queue).tail = new;
   }
   else {
      (*queue).head = new;
      (*queue).tail = (*queue).head;
   }
}

/* Remove from Head of Queue */
Node *dequeue(Queue *queue) {
   Node *node;
   QueueNode *temp = (*queue).head;

   if ((*queue).head) {
      node = (*queue).head->node;
      (*queue).head = (*queue).head->next;
      free(temp);

      return node;
   }

   return NULL;
}

Node *recurInsert(Node *node, int elem) {
   if (!node) {
      node = calloc(1, sizeof(Node));
      node->data = elem;
   }
   else {
      if (elem < node->data) {
         node->left = recurInsert(node->left, elem);
      }
      else {
         node->right = recurInsert(node->right, elem);
      }
   }
   return node;
}

void insert(Node **root, int elem) {
   *root = recurInsert(*root, elem);
}

/* Return Number of Nodes in Tree */
int size(Node *node) {
   if (!node) {
      return 0;
   }

   return size(node->left) + 1 + size(node->right);
}

Node *findMin(Node *node) {
   if (!node) {
      return NULL;
   }

   if (node->left) {
      return findMin(node->left);
   }
   else {
      return node;
   }
}

Node *findMax(Node *node) {
   if (!node) {
      return NULL;
   }

   if (node->right) {
      return findMin(node->right);
   }
   else {
      return node;
   }
}

/* Return Node Containing Element */
Node *find(Node *node, int elem) {
   if (!node) {
      return NULL;
   }

   if (elem > node->data) {
      return find(node->right, elem);
   }
   else if (elem < node->data) {
      return find(node->left, elem);
   }
   else {
      return node;
   }
}

Node *deleteNode(Node *node, int elem) {
   Node *temp;

   if (!node) {
      return node;
   }

   if (elem < node->data) {
      node->left = deleteNode(node->left, elem);
   }
   else if (elem > node->data) {
      node->right = deleteNode(node->right, elem);
   }
   else {
      /* One or No Child */
      if (!node->left) {
         temp = node->right;
         free(node);
         return temp;
      }
      else if (!node->right) {
         temp = node->left;
         free(node);
         return temp;
      }

      /* Two Children */
      temp = findMin(node->right);
      node->data = temp->data;
      node->right = deleteNode(node->right, temp->data);
   }
   return node;
}

void deleteItem(Node **root, int elem) {
   if (*root) {
      *root = deleteNode(*root, elem);
   }
}

/* Print Breadth First */
void printLevelOrder(Node *root) {
   Queue queue;
   Node *temp = root;
   int data;

   queue.head = NULL;
   queue.tail = NULL;

   while (temp) {
      printf("%d ", temp->data);

      if (temp->left) {
         enqueue(&queue, temp->left);
      }

      if (temp->right) {
         enqueue(&queue, temp->right);
      }

      temp = dequeue(&queue);
   }
}

/* Print Depth First Algorithms */
void printInOrder(Node *node) {
   if (node) {
      printInOrder(node->left);
      printf("%d ", node->data);
      printInOrder(node->right);
   }
}

void printPreOrder(Node *node) {
   if (node) {
      printf("%d ", node->data);
      printPreOrder(node->left);
      printPreOrder(node->right);
   }
}

void printPostOrder(Node *node) {
   if (node) {
      printPostOrder(node->left);
      printPostOrder(node->right);
      printf("%d ", node->data);
   }
}

int maxDepth(Node *node) {
   int leftDepth, rightDepth;

   if (!node) {
      return 0;
   }

   leftDepth = maxDepth(node->left);
   rightDepth = maxDepth(node->right);

   if (leftDepth > rightDepth) {
      return leftDepth + 1;
   }
   else {
      return rightDepth + 1;
   }
}

int getLevel(Node *node, int data, int level) {
   int height;

   /* Return 0 If Not Found */
   if (!node) {
      return 0;
   }

   /* If Found, Return Level */
   if (node->data == data) {
      return level;
   }

   /* Search Left Subtree */
   if ((height = getLevel(node->left, data, level + 1))) {
      return height;
   }

   /* Search Right Subtree */
   return getLevel(node->right, data, level + 1);
}

int nodeLevel(Node* node, int data) {
   return getLevel(node, data, 1);
}

/* Testing */
int main() {
   Node *root = NULL;
   int arr[10] = {5, 3, 7, 2, 4, 6, 8, 9, 1, 10};
   int i;

   for(i = 0; i < 10; i++) {
      insert(&root, arr[i]);
   }

   printLevelOrder(root);
   printf("\n");

   deleteItem(&root, 5);

   printLevelOrder(root);
   printf("\n");

   printf("Max Depth: %d\n", maxDepth(root));
   printf("Level of 8: %d\n", nodeLevel(root, 8));

   return 0;
}
