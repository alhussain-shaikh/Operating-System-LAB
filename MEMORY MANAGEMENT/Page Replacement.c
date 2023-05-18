
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <limits.h>

#define MAX_SIZE 100

struct Node {
    int pageNumber;
    struct Node* next;
};

struct Queue {
    struct Node* front, * rear;
};

struct Node* createNode(int pageNumber) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->pageNumber = pageNumber;
    node->next = NULL;
    return node;
}

struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

bool isQueueEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

void enqueue(struct Queue* queue, int pageNumber) {
    struct Node* newNode = createNode(pageNumber);
    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }
    queue->rear->next = newNode;
    queue->rear = newNode;
}

void dequeue(struct Queue* queue) {
    if (isQueueEmpty(queue))
        return;
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
}

bool search(struct Queue* queue, int pageNumber) {
    struct Node* current = queue->front;
    while (current != NULL) {
        if (current->pageNumber == pageNumber)
            return true;
        current = current->next;
    }
    return false;
}


int fifo(int pages[], int n, int capacity) {
    printf("* ---------- First In First Out Page Replacement Algorithm ---------- *\n\n");
    struct Queue* queue = createQueue();

    int pageFaults = 0;
    for (int i = 0; i < n; i++) {
        if (!search(queue, pages[i])) {
            if (queue->rear == NULL || capacity > 0) {
                enqueue(queue, pages[i]);
                capacity--;
                pageFaults++;
            }
            else {
                dequeue(queue);
                enqueue(queue, pages[i]);
                pageFaults++;
            }
        }

        printf("Iteration %d: ", i + 1);
        struct Node* current = queue->front;
        while (current != NULL) {
            if (current->pageNumber != pages[i]) {
                printf("%d ", current->pageNumber);
            }
            else {
                printf("[%d] ", current->pageNumber);
            }
            current = current->next;
        }
        printf("\n");
    }

    return pageFaults;
}

typedef struct {
    int key;
    int value;
} KeyValuePair;

typedef struct {
    KeyValuePair* elements;
    int capacity;
    int size;
} LinkedHashMap;

LinkedHashMap* createLinkedHashMap(int capacity) {
    LinkedHashMap* map = (LinkedHashMap*)malloc(sizeof(LinkedHashMap));
    map->elements = (KeyValuePair*)malloc(capacity * sizeof(KeyValuePair));
    map->capacity = capacity;
    map->size = 0;
    return map;
}

bool containsKey(LinkedHashMap* map, int key) {
    for (int i = 0; i < map->size; i++) {
        if (map->elements[i].key == key) {
            return true;
        }
    }
    return false;
}

void put(LinkedHashMap* map, int key, int value) {
    if (containsKey(map, key)) {
        for (int i = 0; i < map->size; i++) {
            if (map->elements[i].key == key) {
                map->elements[i].value = value;
                break;
            }
        }
    } else {
        if (map->size < map->capacity) {
            map->elements[map->size].key = key;
            map->elements[map->size].value = value;
            map->size++;
        } else {
            int lru = INT_MAX;
            int val = -1;
            for (int i = 0; i < map->size; i++) {
                if (map->elements[i].value < lru) {
                    lru = map->elements[i].value;
                    val = i;
                }
            }
            map->elements[val].key = key;
            map->elements[val].value = value;
        }
    }
}

void removeKey(LinkedHashMap* map, int key) {
    for (int i = 0; i < map->size; i++) {
        if (map->elements[i].key == key) {
            for (int j = i; j < map->size - 1; j++) {
                map->elements[j] = map->elements[j + 1];
            }
            map->size--;
            break;
        }
    }
}



int lru(int pages[], int n, int capacity) {
    printf("* ---------- Last Recently Used Replacement Algorithm ---------- *\n\n");
    LinkedHashMap* map = createLinkedHashMap(capacity);

    int page_faults = 0;
    for (int i = 0; i < n; i++) {
        if (map->size < capacity) {
            if (!containsKey(map, pages[i])) {
                put(map, pages[i], i);
                page_faults++;
            }
        } else {
            if (!containsKey(map, pages[i])) {
                int lru = INT_MAX;
                int val = -1;
                for (int j = 0; j < map->size; j++) {
                    if (map->elements[j].value < lru) {
                        lru = map->elements[j].value;
                        val = map->elements[j].key;
                    }
                }
                removeKey(map, val);
                
                put(map, pages[i], i);
                page_faults++;
            } else {
                put(map, pages[i], i);
            }
        }
        printf("Iteration %d: ", i + 1);
        for (int i = 0; i < map->size; i++) {
            printf("%d ", map->elements[i].key);
        }printf("\n");
        
    }
    
    free(map->elements);
    free(map);
    
    return page_faults;
    
}

int optimal(int pages[], int n, int capacity) {
    printf("* ---------- Optimal Replacement Algorithm ---------- *\n");
    int page_faults = 0;
    int frame[MAX_SIZE];
    int mapKeys[MAX_SIZE];
    int mapValues[MAX_SIZE];
    int mapSize = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];

        // If the page is already present in the frame, no page fault occurs
        bool contains = false;
        for (int j = 0; j < mapSize; j++) {
            if (mapKeys[j] == page) {
                contains = true;
                break;
            }
        }
        if (contains) {
            continue;
        }

        // If there is an empty space in the frame, insert the page
        bool inserted = false;
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1) {
                frame[j] = page;
                mapKeys[mapSize] = page;
                mapValues[mapSize] = i;
                mapSize++;
                page_faults++;
                inserted = true;
                break;
            }
        }

        if (!inserted) {
            int idx = 0, farthest = i;
            for (int j = 0; j < capacity; j++) {
                if (mapKeys[j] == frame[j]) {
                    int next = mapValues[j];
                    if (next > farthest) {
                        farthest = next;
                        idx = j;
                    }
                } else {
                    idx = j;
                    break;
                }
            }

            mapKeys[idx] = page;
            mapValues[idx] = i;
            frame[idx] = page;
            page_faults++;
        }

        printf("Iteration %d: ", i + 1);
        for (int j = 0; j < capacity; j++) {
            if (frame[j] != -1) {
                printf("%d ", frame[j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }

    return page_faults;
}

int main() {
    printf("---------- Welcome to page replacement algorithm ----------\n");
    int n;
    printf("Enter the number of reference strings: ");
    scanf("%d", &n);
    int* pages = (int*)malloc(n * sizeof(int));
    printf("Enter the reference strings: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Reference strings elements are: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");
    int capacity;
    printf("Enter page frame size: ");
    scanf("%d", &capacity);
    while (true) {
        printf("\n");
        printf("* ---------- Page Replacement Menu ---------- *\n");
        printf("1. FIFO page replacement algorithm\n");
        printf("2. LRU page replacement algorithm\n");
        printf("3. Optimal page replacement algorithm\n");
        printf("4. Exit\n");
        printf("\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
    
        switch (choice) {
            case 1:
                printf("\nTotal page faults for FIFO page replacement algorithm: %d\n", fifo(pages, n, capacity));
                break;
            case 2:
                printf("\nTotal page faults for LRU page replacement algorithm: %d\n", lru(pages, n, capacity));
                break;
            case 3:
                printf("\nTotal page faults for optimal page replacement algorithm: %d\n", optimal(pages, n, capacity));
                break;
            case 4:
                printf("----------- Thank You ----------\n");
                free(pages);
                return 0;
            default:
                printf("Invalid choice\n");
        }
        
    }
    
}    

