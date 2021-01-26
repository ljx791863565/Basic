#include <assert.h>
#include <stdlib.h>

#include "leptjson.h"

#define EXPECT(c, ch)				\
	do {							\
		assert(*c->json == (ch));	\
		c->json++;					\
	} while(0)						\

typedef struct {
	const char *json;
} lept_context;

struct void lept_parse_whitespace(lept_context *c)
{
	const char *p = c->json;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r') {
		p++;
	}
	c->json = p;
}

static int lept_parse_null(lept_context *c, lept_value *v)
{
	EXPECT(c, 'n');
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != 'l')  {
		return LEPT_PARSE_INVALID_VALUE;
	}
	c->json += 3;
	v->type = LEPT_NULL;
	return LEPT_PARSE_OK;
}
