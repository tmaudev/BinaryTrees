/* Binary Tree Implementation */

#include <stdlib.h>
#include <stdio.h>

/* Tree Node */
typedef struct Node {
   int data;
   struct Node *left;
   struct Node *right;
}Node;

typedef struct QueueNode {
   Node *node;
   struct QueueNode *next;
   struct QueueNode *prev;
}QueueNode;

typedef struct Queue {
   QueueNode *head;
   QueueNode *tail;
}Queue;

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
      print("%d ", node->data);
      printPreOrder(node->left);
      printPreOrder(node->right);
   }
}

void printPostOrder(Node *node) {
   if (node) {
      printPostOrder(node->left);
      printPostOrder(node->right);
      print("%d ", node->data);
   }
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

   return 0;
}
