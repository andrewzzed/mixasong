/* RTcmix  - Copyright (C) 2004  The RTcmix Development Team
   See ``AUTHORS'' for a list of contributors. See ``LICENSE'' for
   the license to this software and for a DISCLAIMER OF ALL WARRANTIES.
*/

/* symbol table management routines */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <vector>
#include "minc_internal.h"
#include "handle.h"

#define NO_EMALLOC_DEBUG
#define SYMBOL_DEBUG


static struct str {             /* string table */
   char *str;                   /* string */
   struct str *next;            /* next entry */
} *stab[HASHSIZE] = {
   0
};

static struct symbol *freelist = NULL;  /* free list of unused entries */

/* prototypes for local functions */
static struct symbol *symalloc(const char *name);
static void free_symbol(struct symbol *p);
#ifdef NOTYET
static void free_node(struct symbol *p);
static void kill_scope(ScopeType scope);
#endif
#ifdef NOMORE
static char *dname(int x);
static void dump(struct symbol *p, FILE * fp);
#endif
static int hash(const char *s);

// New Scope Code

class Scope {
public:
	Scope(int inDepth) : _depth(inDepth) { htab[0] = 0; }
	~Scope();
	Symbol *install(const char *name);
	Symbol *lookup(const char *name);
	int		depth() const { return _depth; }
private:
	int		_depth;			  /* for debugging */
	Symbol *htab[HASHSIZE];   /* hash table */
};

Scope::~Scope()
{
	for (int s = 0; s < HASHSIZE; ++s) {
		for (Symbol *p = htab[s]; p != NULL; ) {
			Symbol *next = p->next;
			free_symbol(p);
			p = next;
		}
		htab[s] = NULL;
	}
}

Symbol *
Scope::install(const char *name)
{
	Symbol *p = symalloc(name);
	int h = hash(name);
	p->next = htab[h];
	p->scope = depth();	/* XXX */
	p->type = MincVoidType;
	htab[h] = p;
	p->v.number = 0.0;
	
#ifdef SYMBOL_DEBUG
	DPRINT3("Scope::install ('%s') => %p [scope %d]\n", name, p, p->scope);
#endif
	return p;
}

Symbol *
Scope::lookup(const char *name)
{
	Symbol *p = NULL;
	
	for (p = htab[hash(name)]; p != NULL; p = p->next)
		if (name == p->name)
			break;
	
	DPRINT3("Scope::lookup ('%s') [scope %d] => %p\n", name, depth(), p);
	return p;
}

static std::vector<Scope *> sScopeStack;
static int sStackDepth = -1;	// hack till I figure out initialization

void check_scope() {
	if (sStackDepth == -1) {
		push_scope();
	}
}

void push_scope()
{
	++sStackDepth;
	sScopeStack.push_back(new Scope(sStackDepth));
	DPRINT1("push_scope() => %d\n", sStackDepth);
}

void pop_scope() {
	assert(sStackDepth >= 0);
	Scope *top = sScopeStack.back();
	sScopeStack.pop_back();
	delete top;
	--sStackDepth;
	DPRINT1("pop_scope() => %d\n", sStackDepth);
}

int current_scope()
{
	check_scope();		// XXX HACK
	DPRINT1("current_scope() == %d\n", sStackDepth);
	return sStackDepth;
}

/* Allocate and initialize and new symbol table entry for <name>. */
static struct symbol *
symalloc(const char *name)
{
   struct symbol *p;

   p = freelist;
   if (p)
      freelist = p->next;
   else {
      p = (struct symbol *) emalloc(sizeof(struct symbol));
      if (p == NULL)
         return NULL;
   }
   p->name = name;
   p->tree = NULL;
   p->sibling = NULL;
#ifdef NOTYET
   p->defined = p->offset = 0;
   p->list = NULL;
#endif
   return p;
}

static void free_symbol(struct symbol *p)
{
#ifdef SYMBOL_DEBUG
	rtcmix_print("\tfreeing symbol \"%s\" for scope %d (%p)\n", p->name, p->scope, p);
#endif
	if (p->type == MincHandleType)
		unref_handle(p->v.handle);
	else if (p->type == MincListType) {
		unref_value_list(&p->v);
	}
	free(p);
}

void
free_symbols()
{
#ifdef SYMBOL_DEBUG
	rtcmix_print("freeing symbol and string tables...\n");
#endif
	// Start at deepest scope (end) and work back to global (begin)
	while (!sScopeStack.empty()) {
		Scope *s = sScopeStack.back();
		sScopeStack.pop_back();
		delete s;
	}
	for (int s = 0; s < HASHSIZE; ++s)
	{
#if 1
		struct str *str;
		for (str = stab[s]; str != NULL; ) {
			struct str *next = str->next;
			free(str->str);
			free(str);
			str = next;
		}
		stab[s] = NULL;
#endif
	}
#ifdef SYMBOL_DEBUG
	rtcmix_print("done\n");
#endif
}

#ifdef NOTYET
/* Free storage for reuse.  Very closely connected to symalloc.
   TBD:  only allow a maximum freelist length
*/
static void
free_node(struct symbol *p)
{
   if (p == NULL) {
      minc_warn("free_node was called with NULL ptr ");
      return;
   }

   if (freelist == NULL)
      freelist = p;
   else {
      p->next = freelist;
      freelist = p;
   }
}
#endif


/* Allocate a new entry for name and install it. */
struct symbol *
install(const char *name)
{
	check_scope();		// XXX HACK
	return sScopeStack.back()->install(name);
}

/* Lookup <name> at a given scope; return pointer to entry.
   Will match for smallest scope that is >= than that requested.
   So, looking for GLOBAL will not find LOCAL or PARAM.
   If scope is OR'd with S_ANY, lookup will return the first symbol
   matching the name, regardless of scope.
 */
/* WARNING: it can only find symbol if name is a ptr returned by strsave */
Symbol *
lookup(const char *name, Bool anyLevel)
{
	Symbol *p = NULL;
	int foundLevel = -1;
	check_scope();		// XXX HACK
	if (anyLevel == YES) {
		// Start at deepest scope and work back to global
		for (std::vector<Scope *>::reverse_iterator it = sScopeStack.rbegin(); it != sScopeStack.rend(); ++it) {
			Scope *s = *it;
			if ((p = s->lookup(name)) != NULL) {
				foundLevel = s->depth();
				break;
			}
		}
	}
	else {
		// Current scope only
		if ((p = sScopeStack.back()->lookup(name)) != NULL) {
			foundLevel = sScopeStack.back()->depth();
		}
	}
#ifdef SYMBOL_DEBUG
	if (p) {
		DPRINT4("lookup ('%s', %s) => %p (scope %d)\n", name, anyLevel ? "any" : "current", p, foundLevel);
	}
	else {
		DPRINT3("lookup ('%s', %s) => %p\n", name, anyLevel ? "any" : "current", p);
	}
#endif
   return p;
}

Symbol * lookupOrAutodeclare(const char *name)
{
	DPRINT1("lookupOrAutodeclare('%s')\n", name);
	Symbol *sym = lookup(name, NO);	// Check at current scope *only*
	if (sym != NULL) {
		return sym;
	}
	else {
		sym = lookup(name, YES);		// check at all levels
		return (sym) ? sym : install(name);		// XXX DOES THIS MATCH OLD BEHAVIOR?
	}
}

/* Lookup <str> and install if necessary; return pointer. */
char *
strsave(char *str)
{
   int h;
   struct str *p;

   h = hash(str);
   for (p = stab[h]; p != NULL; p = p->next)
      if (strcmp(str, p->str) == 0)
         return (p->str);
   p = (struct str *) emalloc(sizeof(struct str));
   if (p == NULL)
      return NULL;
   p->str = (char *) emalloc(strlen(str) + 1);
	if (p->str == NULL) {
		efree(p);
      return NULL;
	}
   strcpy(p->str, str);
   p->next = stab[h];
   stab[h] = p;

#ifdef SYMBOL_DEBUG
   DPRINT2("strsave ('%s') => %p\n", str, p);
#endif
   return p->str;
}


#ifdef NOTYET
/* remove all entries of the scope from the symbol table */
static void
kill_scope(ScopeType scope)
{
   register int i;
   register struct symbol *p, **q, *r;

   for (i = 0; i < HASHSIZE; i++) {
      q = &htab[i];
      for (p = htab[i]; p; p = r) {
         r = p->next;
         if (p->scope == scope) {
            *q = p->next;
            free_node(p);
         }
         else
            q = &p->next;
      }
   }
}
#endif


#ifdef NOMORE
/* Return string representation of type or scope. */
static char *
dname(int x)
{
   static struct tname {
      int val;
      char *name;
   } tnames[] = {
      { T_INT, "int" },
      { T_FLOAT, "float" },
      { T_COND, "conditional" },
      { T_SCALAR, "scalar" },
      { T_FUNC, "()" },
      { T_ARRAY, "[]" },
      { S_GLOBAL, "global" },
      { S_PARAM, "parameter" },
      { S_LOCAL, "local" },
      { 0, 0 }
   };
   static char buf[30];
   int i;

   for (i = 0; tnames[i].name; i++)
      if (tnames[i].val == x)
         return (tnames[i].name);
   sprintf(buf, "<%d>", x);
   return buf;
}


/* Print entire symbol table or one entry. */
static void
dump(struct symbol *p, FILE * fp)
{
   int i;

   if (fp == NULL)
      fp = stderr;
   if (p == NULL)
      for (i = 0; i < HASHSIZE; i++)
         for (p = htab[i]; p; p = p->next)
            dump(p, fp);
   else {
      fprintf(fp, "%s ", dname(p->type));
/*
   fprintf(fp, "%s%s, %sscope=%s, offset=%d\n", p->name,
   dname(xshape(p->type)), p->defined?"defined, ":"",
   dname(p->scope), p->offset);
*/
   }
}
#endif /* NOMORE */


/* Has error-checking for malloc built in. */
char *
emalloc(long nbytes)
{
   char *s;

   s = (char *) malloc(nbytes);
   if (s == NULL)
      sys_error("system out of memory");

#ifndef NO_EMALLOC_DEBUG
   DPRINT2("emalloc: nbytes=%d, ptr=%p\n", nbytes, s);
#endif
   return s;
}

void efree(void *mem)
{
#ifndef NO_EMALLOC_DEBUG
   DPRINT1("efree: ptr=%p\n", mem);
#endif
   free(mem);
}

/* Returns an index to a hash bucket. */
static int
hash(const char *s)
{
   int i = 0;

   while (*s) {
      i = (((unsigned int) *s + i) % HASHSIZE);
      s++;
   }
   return i;
}


