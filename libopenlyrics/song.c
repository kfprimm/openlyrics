
#include <libxml/tree.h>
#include <openlyrics/song.h>
#include <openlyrics/util.h>

#include <stdio.h>

const char *ol_error_str(OL_ERROR error)
{
	switch (error)
	{
	case OL_ERROR_NONE: return "No error.";
	case OL_ERROR_INPUT: return "Input error.";
	case OL_ERROR_XML: return "XML Parsing error.";
	case OL_ERROR_ROOT: return "XML root is not \"song.\"";
	case OL_ERROR_VERSION: return "Invalid version.";
	}
	return "Invalid error code.";
}

OLSong *ol_new_song() { return ol_new_object(sizeof(OLSong)); }

const char *ol_song_get_createdin	(OLSong *song) { return song->createdIn; }
void ol_song_set_createdin			(OLSong *song, const char *createdin) { ol_set_string(&song->createdIn,createdin); }

const char *ol_song_get_modifiedin	(OLSong *song) { return song->modifiedIn; }
void ol_song_set_modifiedin			(OLSong *song, const char *modifiedin) { ol_set_string(&song->modifiedIn,modifiedin); }

const char *ol_song_get_modifieddate	(OLSong *song) { return song->modifiedDate; }
void ol_song_set_modifieddate			(OLSong *song, const char *modifieddate) { ol_set_string(&song->modifiedDate,modifieddate); }

OLTitle *ol_new_title() { return ol_new_object(sizeof(OLTitle)); }
int ol_song_num_titles	(OLSong *song) { return song->num_titles; }
void ol_song_get_title	(OLSong *song, int index, char **title, char **lang)
{
	(*title) = song->titles[index]->title;
	(*lang) = song->titles[index]->lang;
}
void ol_song_add_title	(OLSong *song, const char *title, const char *lang)
{	
	OLTitle *newtitle=ol_new_title();
	ol_set_string(&newtitle->title,title);
	ol_set_string(&newtitle->lang,lang);
	
	ol_extend_ptr_array((void**)&song->titles,&song->num_titles,1);
	song->titles[song->num_titles-1]=newtitle;
}

OLAuthor *ol_new_author() { return ol_new_object(sizeof(OLAuthor)); }
int ol_song_num_authors	(OLSong *song) { return song->num_authors; }
void ol_song_get_author	(OLSong *song, int index, char **name, OL_AUTHOR_TYPE *type, char **lang)
{
	(*name) = song->authors[index]->name;
	(*type) = song->authors[index]->type;
	(*lang) = song->authors[index]->lang;
}
void ol_song_add_author	(OLSong *song, const char *author,OL_AUTHOR_TYPE type, const char *lang)
{
	OLAuthor *newauthor=ol_new_author();	
	ol_set_string(&newauthor->name,author);
	newauthor->type=type;
	ol_set_string(&newauthor->lang,lang);
	
	ol_extend_ptr_array((void**)&song->authors,&song->num_authors,1);
	song->authors[song->num_authors-1]=newauthor;
}

const char *ol_song_get_copyright	(OLSong *song) { return song->copyright;}
void ol_song_set_copyright			(OLSong *song, const char *copyright) { ol_set_string(&song->copyright,copyright); }

int ol_song_get_ccli_num	(OLSong *song) { return song->ccliNo; }
void ol_song_set_ccli_num	(OLSong *song, int num) { song->ccliNo = num; }

const char *ol_song_get_release_date	(OLSong *song) { return song->releaseDate; }
void ol_song_set_release_date			(OLSong *song, const char *date) { ol_set_string(&song->releaseDate,date); }

int ol_song_get_transposition	(OLSong *song) { return song->transposition; }
void ol_song_set_transposition	(OLSong *song, int transposition) { song->transposition = transposition; }

int ol_song_get_tempo_bpm				(OLSong *song)
{
	if (song->tempo_type==OL_TEMPO_TEXT)
		return -1;	
	return atoi(song->tempo);
}
const char *ol_song_get_tempo_text		(OLSong *song) { return song->tempo; }
void ol_song_set_tempo_bpm				(OLSong *song, int bpm)
{
	char tmp[(sizeof(int)*8+1)];
	free(song->tempo);
	
	sprintf(&tmp[0],"%d",bpm);
	ol_set_string(&song->tempo,&tmp[0]);
	song->tempo_type=OL_TEMPO_BPM;
}
void ol_song_set_tempo_text				(OLSong *song, const char *text)
{
	ol_set_string(&song->tempo,text);
	song->tempo_type=OL_TEMPO_TEXT;
}
OL_TEMPO_TYPE ol_song_get_tempo_type	(OLSong *song) { return song->tempo_type;}

const char *ol_song_get_key	(OLSong *song) { return song->key; }
void ol_song_set_key		(OLSong *song, const char *key) { ol_set_string(&song->key,key); }

const char *ol_song_get_variant	(OLSong *song) { return song->variant; }
void ol_song_set_variant		(OLSong *song, const char *variant) { ol_set_string(&song->variant,variant); }

const char *ol_song_get_publisher	(OLSong *song) { return song->publisher; }
void ol_song_set_publisher			(OLSong *song, const char *publisher) { ol_set_string(&song->publisher,publisher); }

const char *ol_song_get_custom_version	(OLSong *song) { return song->customVersion; }
void ol_song_set_custom_version			(OLSong *song, const char *version) { ol_set_string(&song->customVersion,version); }

int ol_song_num_keywords	(OLSong *song) { return song->num_keywords; }
const char *ol_song_get_keyword	(OLSong *song, int index) { return song->keywords[index]; }
void ol_song_add_keyword		(OLSong *song, const char *keyword)
{
	ol_extend_ptr_array((void**)&song->keywords,&song->num_keywords,1);
	ol_set_string(&song->keywords[song->num_keywords-1],keyword);
}

int ol_song_get_num_verse_order		(OLSong *song);
const int *ol_song_get_verse_order	(OLSong *song);
const int *ol_song_set_verse_order	(OLSong *song, const int *order);

OLSongbook *ol_new_songbook() { return ol_new_object(sizeof(OLSongbook));}
int ol_song_num_songbooks	(OLSong *song) { return song->num_songbooks; }
void ol_song_get_songbook	(OLSong *song, int index, char **name, char **entry, char **lang)
{
	(*name) = song->songbooks[index]->name;
	(*entry) = song->songbooks[index]->entry;
	(*lang) = song->songbooks[index]->lang;
}
void ol_song_add_songbook	(OLSong *song, const char *name, const char *entry, const char *lang)
{
	OLSongbook *newbook=ol_new_songbook();
	ol_set_string(&newbook->name,name);
	ol_set_string(&newbook->entry,entry);
	ol_set_string(&newbook->lang,lang);
	
	ol_extend_ptr_array((void**)&song->songbooks,&song->num_songbooks,1);
	song->songbooks[song->num_songbooks-1]=newbook;
}

OLTheme *ol_new_theme() { return ol_new_object(sizeof(OLTheme)); }
int ol_song_num_themes	(OLSong *song) { return song->num_themes; }
void ol_song_get_theme	(OLSong *song, int index, char **name, int *id, char **lang)
{
	(*name) = song->themes[index]->name;
	(*id) = song->themes[index]->id;
	(*lang) = song->themes[index]->lang;
}
void ol_song_add_theme	(OLSong *song, const char *name, int id, const char *lang)
{
	OLTheme *theme=ol_new_theme();
	ol_set_string(&theme->name,name);
	theme->id=id;
	ol_set_string(&theme->lang,lang);
	
	ol_extend_ptr_array((void**)&song->themes,&song->num_themes,1);
	song->themes[song->num_themes-1]=theme;
}
