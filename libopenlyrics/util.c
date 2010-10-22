
#include <openlyrics/util.h>
#include <stdlib.h>

void ol_string_set(char **stringptr, const char *newstring)
{
  if ((*stringptr))
    free((*stringptr));
  (*stringptr)=NULL;
  if (newstring)  
    if (strlen(newstring)>0)
    {
      (*stringptr)=malloc(strlen(newstring)+1);
      memset((*stringptr),0,strlen(newstring)+1);
      strcpy((*stringptr),newstring);
    }    
}

void *ol_object_new(int size)
{
  void *obj=malloc(size);
  memset(obj,0,size);
  return obj;
}

OLArray ol_array_new (int count) { return ol_object_new(sizeof(void*)*count); }

void ol_array_free(OLArray array, int size, ol_free_func func)
{
  int i;
  for (i=0;i<size;i=i+1)
    func(array[i]);
  free(array);
}

OLArray ol_array_copy(OLArray array, int size, ol_copy_func func)
{
  OLArray new_array = ol_array_new(size);
  int i;
  for (i=0;i<size;i=i+1)
    new_array[i] = func(array[i]);
  return new_array;
}

void ol_array_extend(OLArray *array,int *size,int add)
{
  void *newptrs=ol_array_new(*size+add);
  memcpy(newptrs,(*array),(*size)*4);
  (*size) = (*size) + 1;
  free((*array));
  (*array) = newptrs;
}

void ol_array_add_elem(OLArray *array,int *size, void *elem)
{
  ol_array_extend(array,&size,1);
  array[*size-1]=elem;
}

const char *ol_lang_get_c(const char *lang, int offset)
{
  char lc[3] = {0, 0, 0};
  if (strlen(lang)>offset+1)
  {
    lc[0]=lang[offset+0];
    lc[1]=lang[offset+1];
  }
  return &lc[0];
}

const char *ol_lang_get_lc(const char *lang) { return ol_lang_get_c(lang,0); }
const char *ol_lang_get_cc(const char *lang) { return ol_lang_get_c(lang,3); }

const char *ol_lang_set_lc(char *lang, const char *lc);
const char *ol_lang_set_cc(char *lang, const char *cc);
