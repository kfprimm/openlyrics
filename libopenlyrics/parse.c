
#include <libxml/tree.h>
#include <openlyrics/parse.h>
#include <openlyrics/util.h>
#include <stdlib.h>

typedef void (*ol_node_parser)(OLSong*,xmlDocPtr,xmlNodePtr);
typedef void (*ol_string_parser)(OLSong*,const char *);
typedef void (*ol_int_parser)(OLSong*,int);
typedef void (*ol_vlist_parser)(OLSong*,const char *);

#define seql(s0,s1) (!xmlStrcmp((s0),(const xmlChar*)(s1)))

void ol_song_parse_node(OLSong *song,xmlDocPtr doc,xmlNodePtr node,const char *name,ol_node_parser func)
{
	node=node->xmlChildrenNode;
	while (node)
	{
		if (seql(node->name,name))
			func(song,doc,node);
		node=node->next;
	}
}

void ol_song_parse_title(OLSong *song,xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *title = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	xmlChar *lang = xmlGetProp(node,"lang");
	
	ol_song_add_title(song,title,lang);
	
	xmlFree(title);xmlFree(lang);
}

void ol_song_parse_author(OLSong *song,xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *name = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	xmlChar *typestr = xmlGetProp(node,"type");
	xmlChar *lang = xmlGetProp(node,"lang");
	
	OL_AUTHOR_TYPE type = OL_AUTHOR_INVALID;
	if (seql(typestr,"words"))
		type=OL_AUTHOR_WORDS;
	if (seql(typestr,"music"))
		type=OL_AUTHOR_MUSIC;
	if (seql(typestr,"translation"))
		type=OL_AUTHOR_TRANSLATION;
		
	ol_song_add_author(song,name,type,lang);
	
	xmlFree(name);xmlFree(typestr);xmlFree(lang);	
}

void ol_song_parse_tempo(OLSong *song,xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *text = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	xmlChar *typestr = xmlGetProp(node,"type");
	
	if (seql(typestr,"bpm"))
		ol_song_set_tempo_bpm(song,atoi(text));
	else
		ol_song_set_tempo_text(song,text);
	
	xmlFree(text);xmlFree(typestr);
}

void ol_song_parse_songbook(OLSong *song,xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *name = xmlGetProp(node,"name");
	xmlChar *entry = xmlGetProp(node,"entry");
	xmlChar *lang = xmlGetProp(node,"lang");
	
	ol_song_add_songbook(song,name,entry,lang);
	
	xmlFree(name);xmlFree(entry);xmlFree(lang);
}

void ol_song_parse_theme(OLSong *song,xmlDocPtr doc,xmlNodePtr node)
{
	xmlChar *name = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	xmlChar *idstr = xmlGetProp(node,"id");
	xmlChar *lang = xmlGetProp(node,"lang");
	
	int id=0;
	if (idstr)
		id=atoi(idstr);
	ol_song_add_theme(song,name,id,lang);
	
	xmlFree(name);xmlFree(idstr);xmlFree(lang);
}

void ol_song_parse_string(OLSong *song,xmlDocPtr doc,xmlNodePtr node,ol_string_parser func)
{
	xmlChar *text = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	func(song,text);
	xmlFree(text);
}

void ol_song_parse_int(OLSong *song,xmlDocPtr doc,xmlNodePtr node,ol_int_parser func)
{
	xmlChar *text = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	func(song,atoi(text));
	xmlFree(text);
}

void ol_song_parse_vlist(OLSong *song,xmlDocPtr doc,xmlNodePtr node,char delim,ol_vlist_parser func)
{
	xmlChar *string = xmlNodeListGetString(doc,node->xmlChildrenNode,1);
	int i,start=0;
	char tmp[1000];

	for (i=0;i<strlen(string);i=i+1)
	{
		if (string[i]==delim)
		{
			memset(&tmp[0],0,sizeof(tmp));
			memcpy(&tmp[0],&string[start],i-start);
			func(song,&tmp[0]);
			start=i+1;
		}			
	}
	if (start<strlen(string)-1)
	{
		memset(&tmp[0],0,sizeof(tmp));
		memcpy(&tmp[0],&string[start],strlen(string)-start);
		ol_song_add_keyword(song,&tmp[0]);
	}
	
	xmlFree(string);
}

void ol_song_parse_keyword(OLSong *song,const char *keyword)
{
	ol_song_add_keyword(song,keyword);
}

OL_ERROR ol_song_parse_from_file(OLSong *song,const char *uri)
{
	if (uri==NULL)
		return OL_ERROR_INPUT;
	xmlDocPtr doc = xmlParseFile(uri);
	if (!doc)
		return OL_ERROR_XML;
	
	memset(song,0,sizeof(OLSong));

	OL_ERROR err = OL_ERROR_NONE;
	xmlNodePtr root=xmlDocGetRootElement(doc);
	if (seql(root->name,"song"))
	{
		char *version=xmlGetProp(root,"version");
		if (seql(version,"0.7"))
		{			
			char *ctdin=xmlGetProp(root,"createdIn"),*modin=xmlGetProp(root,"modifiedIn"),*moddate=xmlGetProp(root,"modifiedDate");
			ol_song_set_createdin(song,ctdin);
			ol_song_set_modifiedin(song,modin);			
			ol_song_set_modifieddate(song,moddate);
			xmlFree(ctdin);xmlFree(modin);xmlFree(moddate);
			
			xmlNodePtr topnode=root->xmlChildrenNode;
			while (topnode)
			{
				if (seql(topnode->name,"properties"))
				{
					xmlNodePtr node=topnode->xmlChildrenNode;
					while (node)
					{
						if (seql(node->name,"titles"))
							ol_song_parse_node(song,doc,node,"title",ol_song_parse_title); 
						else if (seql(node->name,"authors"))
							ol_song_parse_node(song,doc,node,"author",ol_song_parse_author); 
						else if (seql(node->name,"copyright"))
							ol_song_parse_string(song,doc,node,ol_song_set_copyright);		
						else if (seql(node->name,"ccliNo"))
							ol_song_parse_int(song,doc,node,ol_song_set_ccli_num);	
						else if (seql(node->name,"releaseDate"))
							ol_song_parse_string(song,doc,node,ol_song_set_release_date);	
						else if (seql(node->name,"transposition"))
							ol_song_parse_int(song,doc,node,ol_song_set_transposition);	
						else if (seql(node->name,"tempo"))
							ol_song_parse_tempo(song,doc,node);
						else if (seql(node->name,"key"))
							ol_song_parse_string(song,doc,node,ol_song_set_key);	
						else if (seql(node->name,"variant"))
							ol_song_parse_string(song,doc,node,ol_song_set_variant);	
						else if (seql(node->name,"publisher"))
							ol_song_parse_string(song,doc,node,ol_song_set_publisher);	
						else if (seql(node->name,"customVersion"))
							ol_song_parse_string(song,doc,node,ol_song_set_custom_version);
						else if (seql(node->name,"songbooks"))
							ol_song_parse_node(song,doc,node,"songbook",ol_song_parse_songbook); 	
						else if (seql(node->name,"themes"))
							ol_song_parse_node(song,doc,node,"theme",ol_song_parse_theme); 
						else if (seql(node->name,"keywords"))
							ol_song_parse_vlist(song,doc,node,',',ol_song_parse_keyword);	
						node=node->next;
					}
				}
				topnode=topnode->next;
			}		
		}
		else
			err=OL_ERROR_VERSION;
		xmlFree(version);
	}
	else
		err=OL_ERROR_ROOT;
	xmlFreeDoc(doc);
	return err;
}
