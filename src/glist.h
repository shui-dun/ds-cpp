#pragma once

typedef void *GListType;

typedef enum {
	ATOM,
	LIST,
} ElemTag;

typedef struct GLNode{
	ElemTag tag;
	union {
		GListType atom;
		struct { struct GLNode *hp, *tp; } *ptr;
	};
}GLNode, *GList;

GList glist_head(GList list);

GList glist_tail(GList list);

int glist_len(GList list);

int glist_depth(GList list);