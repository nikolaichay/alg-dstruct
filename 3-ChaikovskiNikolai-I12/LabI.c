#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#define BUF_SIZE 16
#define INVALID_IDX -1
#define BTREE_PARAM 3

typedef struct Node {
    bool isLeaf;
    int count;
    int* keys;
    struct Node** children;
} Node;

typedef struct {
    int t;
    Node* root;
} BTree;

Node* NodeCreate(const int t);
void NodeDestroy(Node* node);
int FindKeyInArr(const int* arr, const int size, const int key);
bool InsertNonfull(Node* node, const int key, const int t);
bool SplitChild(Node* node, const int t, const int i);
Node* FindNodeContainsKey(const BTree* tree, const int key, int* idx);
int GetPredecessor(Node* node, const int idx);
int GetSuccessor(Node* node, const int idx);
void RemoveFromArrI(int* arr, const int size, const int idx);
void RemoveFromArrNP(Node** arr, const int size, const int idx);
void LeftRotate(Node* node, const int keyIdx);
void RightRotate(Node* node, const int keyIdx);
void MergeChild(Node* node, const int keyIdx);
void RemoveFromLeaf(Node* node, const int t, const int key);
void Remove(Node* node, Node* nodeContainsKey, const int idx, const int t, const int key);
void Destroy(Node* node, const int t);

bool BTreeInit(BTree* tree);
bool BTreeFind(const BTree* tree, const int key);
bool BTreeInsert(BTree* tree, const int key);
void BTreeRemove(BTree* tree, const int key);
void BTreeDestroy(BTree* tree);

int Test(FILE* in, FILE* out);

int main() {
    return Test(stdin, stdout);
}

Node* NodeCreate(const int t) {
    Node* res = (Node*)malloc(sizeof(Node));
    if (!res) {
        return NULL;
    }
    res->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    if (!res->keys) {
        free(res);
        return NULL;
    }
    res->children = (Node**)malloc(2 * t * sizeof(Node*));
    if (!res->children) {
        free(res->keys);
        free(res);
        return NULL;
    }
    res->count = 0;
    res->isLeaf = false;
    for (int i = 0; i < 2 * t; ++i) {
        res->children[i] = NULL;
    }
    return res;
}

void NodeDestroy(Node* node) {
    free(node->children);
    free(node->keys);
    free(node);
}

int FindKeyInArr(const int* arr, const int size, const int key) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == key) {
            return i;
        }
    }
    return INVALID_IDX;
}

bool BTreeInit(BTree* tree) {
    Node* root = NodeCreate(tree->t);
    if (!root) {
        return false;
    }
    root->count = 0;
    root->isLeaf = true;
    tree->root = root;
    return true;
}

bool BTreeFind(const BTree* tree, const int key) {
    int idx = INVALID_IDX;
    Node* found = FindNodeContainsKey(tree, key, &idx);
    return found;
}

bool BTreeInsert(BTree* tree, const int key) {
    if (BTreeFind(tree, key)) {
        return false;
    }
    Node* oldRoot = tree->root;
    if (oldRoot->count == 2 * tree->t - 1) {
        Node* newRoot = NodeCreate(tree->t);
        if (!newRoot) {
            return false;
        }
        tree->root = newRoot;
        newRoot->isLeaf = false;
        newRoot->count = 0;
        newRoot->children[0] = oldRoot;
        if (!SplitChild(newRoot, tree->t, 0)) {
            NodeDestroy(newRoot);
            return false;
        }
        return InsertNonfull(newRoot, key, tree->t);
    }
    return InsertNonfull(oldRoot, key, tree->t);
}

bool InsertNonfull(Node* node, const int key, const int t) {
    assert(node->count < 2 * t - 1);

    int i = node->count - 1;
    if (node->isLeaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        node->keys[i + 1] = key;
        ++node->count;
        return true;
    }
    else {
        while (i >= 0 && key < node->keys[i]) {
            --i;
        }
        ++i;
        if (node->children[i]->count == 2 * t - 1) {
            if (!SplitChild(node, t, i)) {
                return false;
            }
            if (key > node->keys[i]) {
                ++i;
            }
        }
        return InsertNonfull(node->children[i], key, t);
    }
}

bool SplitChild(Node* node, const int t, const int i) {
    assert(node->children[i]->count == 2 * t - 1);

    Node* newNode = NodeCreate(t);
    if (!newNode) {
        return false;
    }

    Node* child = node->children[i];
    newNode->isLeaf = child->isLeaf;
    newNode->count = t - 1;
    for (int j = 0; j < t - 1; ++j) {
        newNode->keys[j] = child->keys[j + t];
    }
    if (!child->isLeaf) {
        for (int j = 0; j < t; ++j) {
            newNode->children[j] = child->children[j + t];
        }
    }
    child->count = t - 1;
    for (int j = node->count + 1; j > i + 1; --j) {
        node->children[j] = node->children[j - 1];
    }
    node->children[i + 1] = newNode;
    for (int j = node->count; j > i; --j) {
        node->keys[j] = node->keys[j - 1];
    }
    node->keys[i] = child->keys[t - 1];
    ++node->count;
    node->isLeaf = false;
    return true;
}

Node* FindNodeContainsKey(const BTree* tree, const int key, int* idx) {
    Node* iter = tree->root;
    while (!iter->isLeaf) {
        *idx = FindKeyInArr(iter->keys, iter->count, key);
        if (*idx != INVALID_IDX) {
            return iter;
        }
        if (key >= iter->keys[iter->count - 1]) {
            iter = iter->children[iter->count];
            continue;
        }
        for (int i = 0; i < iter->count; ++i) {
            if (key < iter->keys[i]) {
                iter = iter->children[i];
                break;
            }
        }
    }
    *idx = FindKeyInArr(iter->keys, iter->count, key);
    return *idx != INVALID_IDX ? iter : NULL;
}

int GetPredecessor(Node* node, const int idx) {
    node = node->children[idx];
    while (!node->isLeaf) {
        node = node->children[node->count];
    }
    return node->keys[node->count - 1];
}

int GetSuccessor(Node* node, const int idx) {
    node = node->children[idx + 1];
    while (!node->isLeaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

void RemoveFromArrI(int* arr, const int size, const int idx) {
    for (int i = idx; i + 1 < size; ++i) {
        arr[i] = arr[i + 1];
    }
}

void RemoveFromArrNP(Node** arr, const int size, const int idx) {
    for (int i = idx; i + 1 < size; ++i) {
        arr[i] = arr[i + 1];
    }
}

void LeftRotate(Node* node, const int keyIdx) {
    Node* lNeighbour = node->children[keyIdx];
    Node* rNeighbour = node->children[keyIdx + 1];
    ++lNeighbour->count;
    lNeighbour->keys[lNeighbour->count - 1] = node->keys[keyIdx];
    lNeighbour->children[lNeighbour->count] = rNeighbour->children[0];
    node->keys[keyIdx] = rNeighbour->keys[0];
    for (int i = 0; i + 1 < rNeighbour->count; ++i) {
        rNeighbour->keys[i] = rNeighbour->keys[i + 1];
    }
    for (int i = 0; i + 1 < rNeighbour->count + 1; ++i) {
        rNeighbour->children[i] = rNeighbour->children[i + 1];
    }
    --rNeighbour->count;
}

void RightRotate(Node* node, const int keyIdx) {
    Node* lNeighbour = node->children[keyIdx];
    Node* rNeighbour = node->children[keyIdx + 1];
    ++rNeighbour->count;
    for (int i = rNeighbour->count - 1; i - 1 >= 0; --i) {
        rNeighbour->keys[i] = rNeighbour->keys[i - 1];
    }
    rNeighbour->keys[0] = node->keys[keyIdx];
    for (int i = rNeighbour->count; i - 1 >= 0; --i) {
        rNeighbour->children[i] = rNeighbour->children[i - 1];
    }
    rNeighbour->children[0] = lNeighbour->children[lNeighbour->count];
    node->keys[keyIdx] = lNeighbour->keys[lNeighbour->count - 1];
    --lNeighbour->count;
}

void MergeChild(Node* node, const int keyIdx) {
    Node* lChild = node->children[keyIdx];
    Node* rChild = node->children[keyIdx + 1];
    lChild->keys[lChild->count] = node->keys[keyIdx];
    for (int i = 0; i < rChild->count; ++i) {
        lChild->keys[lChild->count + 1 + i] = rChild->keys[i];
    }
    for (int i = 0; i < rChild->count + 1; ++i) {
        lChild->children[lChild->count + 1 + i] = rChild->children[i];
    }
    lChild->count += 1 + rChild->count;
    RemoveFromArrI(node->keys, node->count, keyIdx);
    RemoveFromArrNP(node->children, node->count + 1, keyIdx + 1);
    --node->count;
    NodeDestroy(rChild);
}

void RemoveFromLeaf(Node* node, const int t, const int key) {
    int i = node->count - 1;
    while (i >= 0 && key < node->keys[i]) {
        --i;
    }
    ++i;
    Node* child = node->children[i];
    int idx = FindKeyInArr(child->keys, child->count, key);
    if (idx != INVALID_IDX) {
        assert(child->isLeaf);
        RemoveFromArrI(child->keys, child->count, idx);
        --child->count;
    }
    else {
        if (child->isLeaf) {
            return;
        }
        RemoveFromLeaf(child, t, key);
    }
    if (child->count < t - 1) {
        if (i < node->count) {
            Node* rNeighbour = node->children[i + 1];
            if (child->count + rNeighbour->count + 1 <= 2 * t - 1) {
                MergeChild(node, i);
            }
            else {
                LeftRotate(node, i);
            }
        }
        else {
            Node* lNeighbour = node->children[i - 1];
            if (child->count + lNeighbour->count + 1 <= 2 * t - 1) {
                MergeChild(node, i - 1);
            }
            else {
                RightRotate(node, i - 1);
            }
        }
    }
}

void Remove(Node* node, Node* nodeContainsKey, const int idx, const int t, const int key) {
    if (!nodeContainsKey) {
        return;
    }
    if (nodeContainsKey->isLeaf) {
        RemoveFromLeaf(node, t, key);
    }
    else {
        if (nodeContainsKey->children[idx]->count >= t) {
            int pred = GetPredecessor(nodeContainsKey, idx);
            RemoveFromLeaf(node, t, pred);
            nodeContainsKey->keys[idx] = pred;
        }
        else if (nodeContainsKey->children[idx + 1]->count >= t) {
            int succ = GetSuccessor(nodeContainsKey, idx);
            RemoveFromLeaf(node, t, succ);
            nodeContainsKey->keys[idx] = succ;
        }
        else {
            MergeChild(nodeContainsKey, idx);
            Remove(node, nodeContainsKey->children[idx], (2 * t - 1) / 2, t, key);
        }
    }
}

void BTreeRemove(BTree* tree, const int key) {
    if (tree->root->isLeaf) {
        int idx = FindKeyInArr(tree->root->keys, tree->root->count, key);
        if (idx != INVALID_IDX) {
            RemoveFromArrI(tree->root->keys, tree->root->count, idx);
            --tree->root->count;
        }
    }
    else {
        int idx = INVALID_IDX;
        Node* neededNode = FindNodeContainsKey(tree, key, &idx);
        Remove(tree->root, neededNode, idx, tree->t, key);
        if (tree->root->count == 0) {
            Node* root = tree->root;
            tree->root = tree->root->children[0];
            NodeDestroy(root);
        }
    }
}

void Destroy(Node* node, const int t) {
    if (!node->isLeaf) {
        for (int i = 0; i < node->count + 1; ++i) {
            Destroy(node->children[i], t);
        }
        NodeDestroy(node);
    }
}

void BTreeDestroy(BTree* tree) {
    Destroy(tree->root, tree->t);
    tree->root = NULL;
}

int Test(FILE* in, FILE* out) {
    BTree tree = { BTREE_PARAM, NULL };
    BTreeInit(&tree);
    char buf[BUF_SIZE] = { 0 };
    char c = 0;
    int val = 0;
    while (fgets(buf, BUF_SIZE, in)) {
        sscanf(buf, "%c %d", &c, &val);
        switch (c) {
        case 'a':
            BTreeInsert(&tree, val);
            break;
        case 'r':
            BTreeRemove(&tree, val);
            break;
        case 'f':
            fprintf(out, "%s\n", BTreeFind(&tree, val) ? "yes" : "no");
            break;
        default:
            BTreeDestroy(&tree);
            return 0;
        }
    }
    BTreeDestroy(&tree);
    return 0;
}