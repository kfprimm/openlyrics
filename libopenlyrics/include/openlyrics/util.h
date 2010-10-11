
#ifndef OPENLYRICS_UTIL_H
#define OPENLYRICS_UTIL_H

#include <string.h>

void ol_set_string(char **stringptr, const char *newstring);
void *ol_new_object(int size);
void ol_extend_ptr_array(void **array,int *size,int add);

const char *ol_lang_get_lc(const char *lang);
const char *ol_lang_get_cc(const char *lang); 

const char *ol_lang_set_lc(char *lang, const char *lc);
const char *ol_lang_set_cc(char *lang, const char *cc);

#endif
