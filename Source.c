#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct Node {
    int key;
    int degree;
    bool mark;
    struct Node* parent;
    struct Node* child;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct FibonacciHeap {
    Node* min;
    int n;
} FibonacciHeap;

Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->degree = 0;
    node->mark = false;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    return node;
}

FibonacciHeap* make_fibonacci_heap() {
    FibonacciHeap* heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

Node* fibonacci_heap_minimum(FibonacciHeap* heap) {
    return heap->min;
}


void remove_from_root_list(FibonacciHeap* heap, Node* node) {
    node->left->right = node->right;
    node->right->left = node->left;
    if (node == node->right) {
        heap->min = NULL;
    }
    else {
        heap->min = node->right;
    }
}

void add_to_root_list(FibonacciHeap* heap, Node* node) {
    if (heap->min == NULL) {
        heap->min = node;
    }
    else {
        node->left = heap->min;
        node->right = heap->min->right;
        heap->min->right->left = node;
        heap->min->right = node;
    }
}

void fibonacci_heap_link(FibonacciHeap* heap, Node* y, Node* x) {
    remove_from_root_list(heap, y);
    y->left = y->right = y;
    if (x->child == NULL) {
        x->child = y;
    }
    else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right->left = y;
        x->child->right = y;
    }
    y->parent = x;
    x->degree++;
    y->mark = false;
}

void consolidate(FibonacciHeap* heap) {
    int D = (int)log2(heap->n) + 1;
    Node** A = (Node**)malloc(sizeof(Node*) * (D + 1));
    for (int i = 0; i <= D; i++) {
        A[i] = NULL;
    }

    Node* w = heap->min;
    if (w != NULL) {
        Node* x = w;
        do {
            int d = x->degree;
            while (A[d] != NULL) {
                Node* y = A[d];
                if (x->key > y->key) {
                    Node* temp = x;
                    x = y;
                    y = temp;
                }
                fibonacci_heap_link(heap, y, x);
                A[d] = NULL;
                d++;
            }
            A[d] = x;
            x = x->right;
        } while (x != w);
    }

    heap->min = NULL;
    for (int i = 0; i <= D; i++) {
        if (A[i] != NULL) {
            if (heap->min == NULL) {
                A[i]->left = A[i]->right = A[i];
                heap->min = A[i];
            }
            else {
                add_to_root_list(heap, A[i]);
                if (A[i]->key < heap->min->key) {
                    heap->min = A[i];
                }
            }
        }
    }
    free(A);
}

FibonacciHeap* fibonacci_heap_union(FibonacciHeap* H1, FibonacciHeap* H2) {
    FibonacciHeap* H = make_fibonacci_heap();
    H->min = H1->min;
    if (H->min == NULL) {
        H->min = H2->min;
    }
    else if (H2->min != NULL) {
        H1->min->right->left = H2->min->left;
        H2->min->left->right = H1->min->right;
        H1->min->right = H2->min;
        H2->min->left = H1->min;
        if (H2->min->key < H1->min->key) {
            H->min = H2->min;
        }
    }
    H->n = H1->n + H2->n;
    free(H1);
    free(H2);
    return H;
}

void fibonacci_heap_insert(FibonacciHeap* heap, Node* x) {
    /*x->degree = 0;
    x->parent = NULL;
    x->child = NULL;
    x->left = x;
    x->right = x;
    x->mark = false;*/
    if (heap->min == NULL) {
        heap->min = x;
    }
    else {
        add_to_root_list(heap, x);
        if (x->key < heap->min->key) {
            heap->min = x;
        }
    }
    heap->n++;
}

Node* fibonacci_heap_extract_min(FibonacciHeap* heap) {
    Node* z = heap->min;
    if (z != NULL) {
        if (z->child != NULL) {
            Node* x = z->child;
            do {
                Node* next = x->right;
                add_to_root_list(heap, x);
                x->parent = NULL;
                x = next;
            } while (x != z->child);
        }
        remove_from_root_list(heap, z);
        if (z == z->right) {
            heap->min = NULL;
        }
        else {
            heap->min = z->right;
            consolidate(heap);
        }
        heap->n--;
    }
    return z;
}

void DisplayFibNode(Node* node, int depth)
{
    int i;
    for (i = 0; i < depth; i++)
        printf("  ");
    printf("Node %d\n", node->key);

    if (node->child != NULL)
    {
        Node* child = node->child;
        do
        {
            DisplayFibNode(child, depth + 1);
            child = child->right;
        } while (child != node->child);
    }
}

void DisplayFibHeap(FibonacciHeap* H)
{
    Node* current;

    if (H->min == NULL)
    {
        printf("Heap is empty.\n");
        return;
    }

    printf("Fibonacci Heap:\n");
    current = H->min;
    do
    {
        DisplayFibNode(current, 0);
        current = current->right;
    } while (current != H->min);
}
int main() {
    FibonacciHeap* heap = make_fibonacci_heap();

    fibonacci_heap_insert(heap, create_node(3));
    fibonacci_heap_insert(heap, create_node(18));
    fibonacci_heap_insert(heap, create_node(39));
    fibonacci_heap_insert(heap, create_node(10));
    fibonacci_heap_insert(heap, create_node(23));
    fibonacci_heap_insert(heap, create_node(6));

    printf("Initial Heap:\n");
    DisplayFibHeap(heap);
    printf("Deleting minimum: %d\n", fibonacci_heap_extract_min(heap)->key);
    DisplayFibHeap(heap);
    printf("Deleting minimum: %d\n", fibonacci_heap_extract_min(heap)->key);
    DisplayFibHeap(heap);
    FibonacciHeap* heap2 = make_fibonacci_heap();
    fibonacci_heap_insert(heap2, create_node(7));
    fibonacci_heap_insert(heap2, create_node(24));

    printf("Second Heap:\n");
    DisplayFibHeap(heap2);
    FibonacciHeap* union_heap = fibonacci_heap_union(heap, heap2);
    printf("After Union:\n");
    DisplayFibHeap(union_heap);
   
    return 0;
}
