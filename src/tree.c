#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "stack.h"
#include "queue.h"

ComBiTree* comtree_init(TreeType* array, int len) {
    ComBiTree* tree = (ComBiTree*)malloc(sizeof(ComBiTree));
    tree->length = len;
    tree->data = (TreeType*)malloc(len * sizeof(TreeType));
    for (int i = 0; i < len; i++)
        tree->data[i] = array[i];
    return tree;
}

void comtree_destroy(ComBiTree** tree) {
    free((*tree)->data);
    free(*tree);
    *tree = NULL;
}

void comtree_visit(ComBiTree* tree, int position) {
    printf("%d ", tree->data[position]);
}

void comtree_pre_traverse(ComBiTree* tree, int position) {
    if (position >= tree->length) return;
    comtree_visit(tree, position);
    comtree_pre_traverse(tree, 2 * position + 1);
    comtree_pre_traverse(tree, 2 * position + 2);
}

void comtree_in_traverse(ComBiTree* tree, int position) {
    if (position >= tree->length) return;
    comtree_in_traverse(tree, 2 * position + 1);
    comtree_visit(tree, position);
    comtree_in_traverse(tree, 2 * position + 2);
}

void comtree_post_traverse(ComBiTree* tree, int position) {
    if (position >= tree->length) return;
    comtree_post_traverse(tree, 2 * position + 1);
    comtree_post_traverse(tree, 2 * position + 2);
    comtree_visit(tree, position);
}

void comtree_level_traverse(ComBiTree* tree, int position) {
    for (; position < tree->length; position++)
        comtree_visit(tree, position);
}

int comtree_depth(ComBiTree* tree) {
    return (int)(log(tree->length) / log(2)) + 1;
}

int comtree_nnode(ComBiTree* tree) {
    return tree->length;
}

int comtree_nleaf(ComBiTree* tree) {
    return (tree->length + 1) / 2;
}

int comtree_find(ComBiTree* tree, TreeType data) {
    for (int i = 0; i < tree->length; i++)
        if (data == tree->data[i])
            return i;
    return -1;
}

int comtree_ancestor(int ind1, int ind2) {
    while (ind1 != ind2) {
        if (ind1 < ind2)
            ind2 = comtree_parent(ind2);
        else
            ind1 = comtree_parent(ind1);
    }
    return ind1;
}

int comtree_parent(int ind) {
    return (ind + 1) / 2 - 1;
}

int comtree_lchild(int ind) {
    return 2 * ind + 1;
}

int comtree_rchild(int ind) {
    return 2 * ind + 2;
}

int comtree_index(int level, int order) {
    if (level < 1 || order < 1 || order >(int)pow(2, level - 1))
        return -1;
    return (int)pow(2, level - 1) + order - 2;
}

TreeType comtree_get(ComBiTree* tree, int ind) {
    if (ind >= tree->length)
        return 0;
    return tree->data[ind];
}

int comtree_set(ComBiTree* tree, int ind, TreeType data) {
    if (ind >= tree->length)
        return 0;
    tree->data[ind] = data;
    return 1;
}

void bitree_visit(BiTree tree) {
    printf("%d ", tree->data);
}

void bitree_pre_traverse(BiTree tree) {
    if (tree == NULL) return;
    bitree_visit(tree);
    bitree_pre_traverse(tree->lchild);
    bitree_pre_traverse(tree->rchild);
}

void bitree_in_traverse(BiTree tree) {
    if (tree == NULL) return;
    bitree_in_traverse(tree->lchild);
    bitree_visit(tree);
    bitree_in_traverse(tree->rchild);
}

void bitree_post_traverse(BiTree tree) {
    if (tree == NULL) return;
    bitree_post_traverse(tree->lchild);
    bitree_post_traverse(tree->rchild);
    bitree_visit(tree);
}

void bitree_dbl_traverse(BiTree tree) {
    if (tree == NULL) return;
    bitree_visit(tree);
    bitree_dbl_traverse(tree->lchild);
    bitree_visit(tree);
    bitree_dbl_traverse(tree->rchild);
}

void bitree_pre_traverse2(BiTree tree) {
    Stack* stack = stack_init(10);
    while (tree || !stack_empty(stack)) {
        if (tree) {
            stack_push(stack, tree);
            bitree_visit(tree);
            tree = tree->lchild;
        } else {
            tree = stack_pop(stack);
            tree = tree->rchild;
        }
    }
    putchar('\n');
    stack_destroy(&stack);
}

void bitree_in_traverse2(BiTree tree) {
    Stack* stack = stack_init(10);
    while (tree || !stack_empty(stack)) {
        if (tree) {
            stack_push(stack, tree);
            tree = tree->lchild;
        } else {
            tree = stack_pop(stack);
            bitree_visit(tree);
            tree = tree->rchild;
        }
    }
    putchar('\n');
    stack_destroy(&stack);
}

void bitree_level_traverse(BiTree tree) {
    LinkQueue* queue = lqueue_init();
    lqueue_offer(queue, tree);
    BiTree node = NULL;
    while (!lqueue_empty(queue)) {
        lqueue_poll(queue, (void**)(&node));
        bitree_visit(node);
        if (node->lchild)
            lqueue_offer(queue, node->lchild);
        if (node->rchild)
            lqueue_offer(queue, node->rchild);
    }
    lqueue_destroy(&queue);
}

static int current_position = 0;

BiTree bitree_create(TreeType* array, int len, TreeType token) {
    if (array[current_position] == token) {
        if (++current_position == len)
            current_position = 0;
        return NULL;
    } else {
        BiTree tree = (BiTree)malloc(sizeof(BiNode));
        tree->data = array[current_position];
        current_position++;
        tree->lchild = bitree_create(array, len, token);
        tree->rchild = bitree_create(array, len, token);
        return tree;
    }
}

BiTree bitree_from_in_post_traverse(TreeType* post, TreeType* in, int len) {
    if (len < 1) return NULL;
    BiTree tree = (BiTree)malloc(sizeof(BiNode));
    tree->data = post[len - 1];
    int ind = -1;
    for (int i = 0; i < len; i++)
        if (in[i] == post[len - 1]) {
            ind = i;
            break;
        }
    tree->lchild = bitree_from_in_post_traverse(post, in, ind);
    tree->rchild = bitree_from_in_post_traverse(post + ind, in + ind + 1, len - ind - 1);
    return tree;
}

BiTree bitree_copy(BiTree tree) {
    if (!tree) return NULL;
    else {
        BiTree newtree = (BiTree)malloc(sizeof(BiNode));
        newtree->data = tree->data;
        newtree->lchild = bitree_copy(tree->lchild);
        newtree->rchild = bitree_copy(tree->rchild);
        return newtree;
    }
}

int bitree_depth(BiTree tree) {
    if (!tree) return 0;
    int len1 = bitree_depth(tree->lchild);
    int len2 = bitree_depth(tree->rchild);
    return 1 + (len1 > len2 ? len1 : len2);
}

int bitree_nnode(BiTree tree) {
    if (!tree) return 0;
    int count1 = bitree_nnode(tree->lchild);
    int count2 = bitree_nnode(tree->rchild);
    return 1 + count1 + count2;
}

int bitree_nleaf(BiTree tree) {
    if (!tree)
        return 0;
    if (!tree->lchild && !tree->rchild)
        return 1;
    int count1 = bitree_nleaf(tree->lchild);
    int count2 = bitree_nleaf(tree->rchild);
    return count1 + count2;
}

void bitree_switch_lr(BiTree tree) {
    if (!tree) return;
    BiTree temp = tree->lchild;
    tree->lchild = tree->rchild;
    tree->rchild = temp;
    bitree_switch_lr(tree->lchild);
    bitree_switch_lr(tree->rchild);
}

int bitree_insert_lchild(BiTree tree, BiTree left) {
    if (!tree || !left) return 0;
    left->lchild = tree->lchild;
    tree->lchild = left;
    return 1;
}

int bitree_insert_rchild(BiTree tree, BiTree right) {
    if (!tree || !right) return 0;
    right->rchild = tree->rchild;
    tree->rchild = right;
    return 1;
}

BiTree bitree_find(BiTree tree, TreeType data) {
    LinkQueue* queue = lqueue_init();
    lqueue_offer(queue, tree);
    BiTree node = NULL;
    while (!lqueue_empty(queue)) {
        lqueue_poll(queue, (void**)(&node));
        if (data == node->data) {
            lqueue_destroy(&queue);
            return node;
        }
        if (node->lchild)
            lqueue_offer(queue, node->lchild);
        if (node->rchild)
            lqueue_offer(queue, node->rchild);
    }
    lqueue_destroy(&queue);
    return NULL;
}

void bitree_destroy(BiTree* tree) {
    if (!(*tree)) return;
    bitree_destroy(&((*tree)->lchild));
    bitree_destroy(&((*tree)->rchild));
    free(*tree);
    *tree = NULL;
}

void bithrtree_visit(BiThrNode* node) {
    printf("%d ", (node->data));
}

void bithrtree_in_traverse(BiThrTree tree) {
    BiThrTree node = tree->lchild;
    while (node != tree) {
        while (node->ltag == Link)
            node = node->lchild;
        bithrtree_visit(node);
        while (node->rtag == Thread && node->rchild != tree) {
            node = node->rchild;
            bithrtree_visit(node);
        }
        node = node->rchild;
    }
    putchar('\n');
}

static BiThrTree pre_node_threading = NULL;
static BiThrTree bithrtree_array(TreeType* array, int len, TreeType token);
static void in_threading(BiThrTree node);
static BiThrTree bithrtree_in_threading(BiThrTree tree);

BiThrTree bithrtree_create(TreeType* array, int len, TreeType token) {
    BiThrTree tree = bithrtree_array(array, len, token);
    return bithrtree_in_threading(tree);
}

static BiThrTree bithrtree_array(TreeType* array, int len, TreeType token) {
    if (array[current_position] == token) {
        if (++current_position == len)
            current_position = 0;
        return NULL;
    } else {
        BiThrTree tree = (BiThrTree)malloc(sizeof(BiThrNode));
        tree->data = array[current_position];
        current_position++;
        tree->ltag = Link;
        tree->lchild = bithrtree_array(array, len, token);
        tree->rtag = Link;
        tree->rchild = bithrtree_array(array, len, token);
        return tree;
    }
}

static void in_threading(BiThrTree node) {
    if (!node) return;
    in_threading(node->lchild);
    if (!node->lchild) {
        node->ltag = Thread;
        node->lchild = pre_node_threading;
    }
    if (!pre_node_threading->rchild) {
        pre_node_threading->rtag = Thread;
        pre_node_threading->rchild = node;
    }
    pre_node_threading = node;
    in_threading(node->rchild);
}

static BiThrTree bithrtree_in_threading(BiThrTree tree) {
    BiThrTree head = (BiThrTree)malloc(sizeof(BiThrNode));
    head->ltag = Link;
    head->rtag = Thread;
    head->rchild = head;
    head->lchild = tree;
    pre_node_threading = head;
    in_threading(tree);
    pre_node_threading->rchild = head;
    pre_node_threading->rtag = Thread;
    head->rchild = pre_node_threading;
    return head;
}

BiThrNode* bithrtree_in_next(BiThrNode* tree) {
    if (tree->rtag == Thread)
        return tree->rchild;
    else {
        BiThrNode* node = tree->rchild;
        while (node->ltag == Link)
            node = node->lchild;
        return node;
    }
}

BiThrNode* bithrtree_in_pre(BiThrNode* tree) {
    if (tree->ltag == Thread)
        return tree->lchild;
    else {
        BiThrNode* node = tree->lchild;
        while (node->rtag == Link)
            node = node->rchild;
        return node;
    }
}
