#pragma once
#include "queue.h"
#include <math.h>

typedef int TreeType;

typedef struct {
	TreeType *data;
	int length;
}ComBiTree;

ComBiTree *comtree_init(TreeType *array, int len);

void comtree_destroy(ComBiTree **tree);

void comtree_visit(ComBiTree *tree, int position);

void comtree_pre_traverse(ComBiTree *tree, int position);

void comtree_in_traverse(ComBiTree *tree, int position);

void comtree_post_traverse(ComBiTree *tree, int position);

void comtree_level_traverse(ComBiTree *tree, int position);

int comtree_depth(ComBiTree *tree);

int comtree_nnode(ComBiTree *tree);

int comtree_nleaf(ComBiTree *tree);

int comtree_find(ComBiTree *tree, TreeType data);

int comtree_ancestor(int ind1, int ind2);

int comtree_parent(int ind);

int comtree_lchild(int ind);

int comtree_rchild(int ind);

int comtree_index(int level, int order);

TreeType comtree_get(ComBiTree *tree, int ind);

int comtree_set(ComBiTree *tree, int ind, TreeType data);

typedef struct BiNode {
	TreeType data;
	struct BiNode *lchild;
	struct BiNode *rchild;
}BiNode, *BiTree;

void bitree_visit(BiTree tree);

void bitree_pre_traverse(BiTree tree);

void bitree_in_traverse(BiTree tree);

void bitree_post_traverse(BiTree tree);

void bitree_dbl_traverse(BiTree tree);

void bitree_pre_traverse2(BiTree tree);

void bitree_in_traverse2(BiTree tree);

void bitree_level_traverse(BiTree tree);

BiTree bitree_create(TreeType *array, int len, TreeType token);

BiTree bitree_from_in_post_traverse(TreeType *post, TreeType *in, int len);

BiTree bitree_copy(BiTree tree);

int bitree_depth(BiTree tree);

int bitree_nnode(BiTree tree);

int bitree_nleaf(BiTree tree);

void bitree_switch_lr(BiTree tree);

int bitree_insert_lchild(BiTree tree, BiTree left);

int bitree_insert_rchild(BiTree tree, BiTree right);

BiTree bitree_find(BiTree tree, TreeType data);

void bitree_destroy(BiTree *tree);

typedef enum { Link, Thread } ThrPtrTag;

typedef struct BiThrNode {
	TreeType data;
	struct BiThrNode *lchild;
	struct BiThrNode *rchild;
	ThrPtrTag ltag;
	ThrPtrTag rtag;
}BiThrNode, *BiThrTree;

void bithrtree_visit(BiThrNode *node);

void bithrtree_in_traverse(BiThrTree tree);

BiThrTree bithrtree_create(TreeType *array, int len, TreeType token);

BiThrNode *bithrtree_in_next(BiThrNode *tree);

BiThrNode *bithrtree_in_pre(BiThrNode *tree);