#include <stddef.h>
#include "glist.h"

GList glist_head(GList list)
{
	if (list->tag == LIST)
		return list->ptr->hp;
	return NULL;
}

GList glist_tail(GList list)
{
	if (list->tag == LIST)
		return list->ptr->tp;
	return NULL;
}

int glist_len(GList list)
{
	if (!list)
		return 0;
	if (list->tag == LIST)
		return 1 + glist_len(list->ptr->tp);
	else
		return 1;
}

int glist_depth(GList list)
{
	if (!list) return 1;
	if (list->tag == ATOM) return 0;
	int depth, max = 0;
	for (GList p = list; p; p = p->ptr->tp)
	{
		depth = glist_depth(p->ptr->hp);
		if (depth > max) max = depth;
	}
	return max + 1;
}
