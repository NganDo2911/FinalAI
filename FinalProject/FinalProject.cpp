// Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include<stdio.h>
#include<malloc.h>
#include<string.h>

enum class Actions { left, right, up, down };
std::string action_names[] = { "left","right","up","down" };
#define SIDE 3 // Length of the board 
typedef struct Node_array
{
    int state[SIDE][SIDE];
    Actions action;
    struct Node_array* parent; // tree search

    int path_cost;
    int depth;
    struct Node_array* nextNode; // list


} Node;



typedef struct NodeList {
    unsigned int nodeCount;    //the number of nodes in the list
    Node* head;            //pointer to the first node in the list
    Node* tail;            //pointer to the last node in the list
};



void set_zero(int a[][SIDE])
{
    int i, j;
    for (i = 0; i < SIDE; i++)
        for (j = 0; j < SIDE; j++)
            a[i][j] = 0;
}

void copy_array(int a[][SIDE], int b[][SIDE])//copy b to a
{
    int i, j;
    for (i = 0; i < SIDE; i++)
        for (j = 0; j < SIDE; j++)
            a[i][j] = b[i][j];
}

int is_equal(int a[][SIDE], int b[][SIDE])
{
    int i, j, flag = 1;
    for (i = 0; i < SIDE; i++)
        for (j = 0; j < SIDE; j++)
            if (a[i][j] != b[i][j])
                flag = 0;
    return flag;
}

void swap(int& a, int& b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}

void print_array(int a[][SIDE])
{
    int i, j;
    for (i = 0; i < SIDE; i++)
    {
        for (j = 0; j < SIDE; j++)
            printf("%d  | ", a[i][j]);
        printf("\n");
        for (j = 0; j < SIDE; j++)
            printf("---|-");

        printf("\n");
    }
}

bool isLegalAction(Node* node, Actions action) {
    int index_i, index_j;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (node->state[i][j] == 0) {
                index_i = i;
                index_j = j;
                i = SIDE;
                break;
            }
        }
    }
    if (action == Actions::left && index_j == 0)  return false;
    if (action == Actions::right && index_j == 2)  return false;

    switch (index_i)
    {
    case 0:
        if (action == Actions::up) return false;
        return true;
    case 2:
        if (action == Actions::down) return false;
        return true;
    default:
        return true;
    }
    return true;
}

Node* Child_node(Node* node, Actions action) {
    Node* child = (Node*)malloc(sizeof(Node));
    int index_i, index_j;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (node->state[i][j] == 0) {
                index_i = i;
                index_j = j;
                i = SIDE;
                break;
            }
        }
    }
    copy_array(child->state, node->state);
    child->action = action;
    child->parent = node;
    child->path_cost = node->path_cost + 1;
    if (action == Actions::left) {
        swap(child->state[index_i][index_j - 1], child->state[index_i][index_j]);
    }
    else if (action == Actions::right) {
        swap(child->state[index_i][index_j + 1], child->state[index_i][index_j]);
    }
    else if (action == Actions::up) {
        swap(child->state[index_i - 1][index_j], child->state[index_i][index_j]);
    }
    else if (action == Actions::down) {
        swap(child->state[index_i + 1][index_j], child->state[index_i][index_j]);
    }
    return child;
}

NodeList* FIFO_initial() {
    NodeList* list;
    list = (NodeList*)malloc(sizeof(NodeList));
    list->nodeCount = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}
void FIFO_add(NodeList* list, Node* node) {
    if (list->nodeCount <= 0) {
        list->head = node;
        list->tail = node;
        list->nodeCount += 1;
        return;
    }

    list->tail->nextNode = node;


    list->tail = node;
    list->nodeCount += 1;
}

Node* FIFO_pop(NodeList* list) {
    if (list->nodeCount <= 0) {
        return NULL;
    }
    Node* temp = list->head;
    list->nodeCount -= 1;
    if (list->nodeCount <= 0) {
        list->head = NULL;
        list->tail = NULL;
    }
    else {
        list->head = temp->nextNode;
    }
    return temp;
}
void LIFO_push(NodeList* list, Node* node) {
    Node* temp = (Node*)malloc(sizeof(Node));
    if (list->nodeCount <= 0) {
        list->head = node;
        list->tail = node;
        list->nodeCount += 1;
        return;
    }
    temp = node;
    temp->nextNode = list->head;
    list->head = temp;
    list->nodeCount += 1;
}

bool Max_pathcost(NodeList* list, Node* node) {
    if (node->path_cost == list->tail->path_cost)
        return true;
    return false;
}
int Max_depth(NodeList* list) {
    int max = 0;
    while (list->head != NULL) {
        if (list->head->depth > max) {
            max = list->head->depth;
        }
        list->head = list->head->nextNode;
    }
    return max;
}
bool Goal_test(Node* node, Node* goal)
{
    return is_equal(node->state, goal->state);
}

bool checkExist(NodeList* list, Node* node) {
    Node* _node;
    int i = 0;
    _node = list->head;
    while (i < list->nodeCount) {
        if (Goal_test(node, _node)) {
            return true;
        }
        _node = _node->nextNode;
        i++;
    }
    return false;
}


void Solution(Node* node) {
    printf("=======================");
    printf("\nSolution\n");
    while (node->parent != NULL) {

        print_array(node->state);
        printf("\n----------^---------\n");
        std::cout << "\naction: " << action_names[int(node->action)] << std::endl;
        printf("----------------------\n");
        node = node->parent;
    }
    print_array(node->state);

}

void breadthFirstSearch(Node* root, Node* goal) {
    Node* node = root;
    int Path_cost = 0;
    if (Goal_test(node, goal)) {
        Solution(node);
        return;
    }
    NodeList* frontier;
    NodeList* explorer;
    frontier = FIFO_initial();
    explorer = FIFO_initial();
    int action;
    FIFO_add(frontier, node);
    do {
        node = (FIFO_pop(frontier));
        FIFO_add(explorer, node);
        //action
        for (action = 0; action < 4; action++) {
            if (isLegalAction(node, (Actions)action)) {
                Node* child = (Child_node(node, (Actions)action));
                if (checkExist(explorer, child) == false || checkExist(frontier, child) == false) {
                    if (Goal_test(child, goal)) {
                        Solution(child);
                        return;
                    }
                    FIFO_add(frontier, child);
                }
            }
        }
    } while (frontier->nodeCount > 0);
}


void depthFirstSearch(Node* root, Node* goal) {
    Node* node = root;
    int Path_cost = 0;
    if (Goal_test(node, goal)) {
        Solution(node);
        return;
    }
    NodeList* frontier;
    NodeList* explorer;
    frontier = FIFO_initial();
    explorer = FIFO_initial();
    int action;
    LIFO_push(frontier, node);

    while (frontier->nodeCount != 0) {
        node = FIFO_pop(frontier);
        LIFO_push(explorer, node);
        for (action = 0; action < 4; action++) {
            if (isLegalAction(node, (Actions)action)) {
                Node* child = (Child_node(node, (Actions)action));
                if (checkExist(explorer, child) == false && checkExist(frontier, child) == false) {
                    if (Goal_test(child, goal)) {
                        Solution(child);
                        return;
                    }
                    LIFO_push(frontier, child);
                }
            }
        }
    }
}

void uniformCostSearch(Node* root, Node* goal) {
    Node* node = root;
    int Path_cost = 0;
    if (Goal_test(node, goal)) {
        Solution(node);
        return;
    }
    NodeList* frontier;
    NodeList* explorer;
    frontier = FIFO_initial();
    explorer = FIFO_initial();
    int action;
    FIFO_add(frontier, node);
    do {
        node = (FIFO_pop(frontier));
        FIFO_add(explorer, node);
        //action
        for (action = 0; action < 4; action++) {
            if (isLegalAction(node, (Actions)action)) {
                Node* child = (Child_node(node, (Actions)action));
                if (checkExist(explorer, child) == false && checkExist(frontier, child) == false) {
                    if (Goal_test(child, goal)) {
                        Solution(child);
                        return;
                    }
                    FIFO_add(frontier, child);
                }
                else if (checkExist(frontier, child) == true && Max_pathcost(frontier, child) == true) {
                    node = child;
                }
            }
        }
    } while (frontier->nodeCount > 0);
}
int heuristic(Node* root, Node* goal) {
    int temp = 0;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (root->state[i][j] != goal->state[i][j] && root->state[i][j] != 0) {
                temp += 1;
            }
        }
    }
    return temp;
}
int manhattan(Node* root, Node* goal) {
    return heuristic(root, goal) + root->path_cost;
}
void aStarSearch(Node* root, Node* goal)
{

}


int main()
{
    Node* Goal, * Start;
    int i, j;
    Goal = (Node*)malloc(sizeof(Node));
    Start = (Node*)malloc(sizeof(Node));
    printf("Enter the goal state\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            std::cin >> Goal->state[i][j];
    printf("Goal state:\n");
    print_array(Goal->state);

    Goal->parent = NULL;
    Goal->depth = 0;



    printf("Enter the current state\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            std::cin >> Start->state[i][j];
    Start->parent = NULL;
    Start->path_cost = 0;
    printf("Start state:\n");
    print_array(Start->state);
    int result = heuristic(Start, Goal);
    std::cout << result << std::endl;
    int result1 = manhattan(Start, Goal);
    std::cout << result1 << std::endl;
    return 0;
}







