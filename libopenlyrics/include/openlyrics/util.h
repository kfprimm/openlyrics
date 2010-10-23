
#ifndef OPENLYRICS_UTIL_H
#define OPENLYRICS_UTIL_H

#include <string.h>

#define OL_DEBUG

#ifdef OL_DEBUG
  #define OL_DEBUG_LOG(message) printf("DEBUG: %s\n",message)
#else
  #define OL_DEBUG_LOG
#endif

typedef void** OLArray;

typedef void  (*ol_free_func)(void*);
typedef void* (*ol_copy_func)(void*);

void  ol_string_set(char **stringptr, const char *newstring);
void *ol_object_new(int size);

OLArray ol_array_new      (int count);
void    ol_array_free     (OLArray  array, int  size, ol_free_func  func);
OLArray ol_array_copy     (OLArray  array, int  size, ol_copy_func  func);
void    ol_array_extend   (OLArray *array, int *size, int           add);
void    ol_array_add_elem (OLArray *array, int *size, void         *elem);

const char *ol_lang_get_lc(const char *lang);
const char *ol_lang_get_cc(const char *lang); 

const char *ol_lang_set_lc(char *lang, const char *lc);
const char *ol_lang_set_cc(char *lang, const char *cc);

#endif
