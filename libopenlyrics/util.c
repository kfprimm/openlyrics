
#include <string.h>
#include <stdlib.h>

void ol_set_string(char **stringptr, const char *newstring)
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

void *ol_new_object(int size)
{
	void *obj=malloc(size);
	memset(obj,0,size);
	return obj;
}

void ol_extend_ptr_array(void **array,int *size,int add)
{
	void *newptrs=malloc( ( (*size) + add)*4 );
	memcpy(newptrs,(*array),(*size)*4);
	(*size) = (*size) + 1;
	free((*array));
	(*array) = newptrs;
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
