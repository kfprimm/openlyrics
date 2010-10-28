
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

OLSong *ol_song_new() { return ol_object_new(sizeof(OLSong)); }
void ol_song_free(OLSong *song) {}
/*{
  free(song->createdIn);
	free(song->modifiedIn);
	free(song->modifiedDate);
		
	free(song->copyright);
	free(song->releaseDate);		
	free(song->tempo);	
	free(song->key);
	free(song->variant);
	free(song->publisher);
	free(song->customVersion);
	
	int i;
	
	for (i=0;i<song->num_titles;i=i+1)
	  ol_title_free(song->titles[i]);
	free(song->titles);
	
	for (i=0;i<song->num_authors;i=i+1)
	  ol_author_free(song->authors[i]);
	free(song->authors);
	
	for (i=0;i<song->num_keywords;i=i+1)
	  free(song->keywords[i]);
	free(song->keywords);
	
	for (i=0;i<song->num_songbooks;i=i+1)
	  ol_songbook_free(song->songbooks[i]);
	free(song->songbooks);
	
	for (i=0;i<song->num_themes;i=i+1)
	  ol_theme_free(song->themes[i]);
	free(song->themes);	
  

	int *verseOrder;
	int num_verse_order;	
	
	OLVerse **verses;
	int num_verses;
  
  free(song);
}*/

const char *ol_song_get_createdin  (OLSong *song) { return song->createdIn; }
void ol_song_set_createdin      (OLSong *song, const char *createdin) { ol_string_set(&song->createdIn,createdin); }

const char *ol_song_get_modifiedin  (OLSong *song) { return song->modifiedIn; }
void ol_song_set_modifiedin      (OLSong *song, const char *modifiedin) { ol_string_set(&song->modifiedIn,modifiedin); }

const char *ol_song_get_modifieddate  (OLSong *song) { return song->modifiedDate; }
void ol_song_set_modifieddate      (OLSong *song, const char *modifieddate) { ol_string_set(&song->modifiedDate,modifieddate); }

OLTitle **ol_song_get_titles (OLSong *song) { return song->titles; }
int ol_song_num_titles  (OLSong *song) { return song->num_titles; }
void ol_song_get_title  (OLSong *song, int index, char **title, char **lang) { ol_title_get(song->titles[index], title, lang); }
void ol_song_add_title  (OLSong *song, const char *title, const char *lang) { ol_array_add_elem((OLArray*)&song->titles,&song->num_titles,ol_title_new(title, lang)); }

int ol_song_num_authors  (OLSong *song) { return song->num_authors; }
OLAuthor **ol_song_get_authors (OLSong *song) { return song->authors; }
void ol_song_get_author  (OLSong *song, int index, char **name, OL_AUTHOR_TYPE *type, char **lang) { ol_author_get(song->authors[index], name, type, lang); }
void ol_song_add_author  (OLSong *song, const char *author, OL_AUTHOR_TYPE type, const char *lang) { ol_array_add_elem((OLArray*)&song->authors,&song->num_authors,ol_author_new(author,type,lang)); }

const char *ol_song_get_copyright  (OLSong *song) { return song->copyright;}
void ol_song_set_copyright      (OLSong *song, const char *copyright) { ol_string_set(&song->copyright,copyright); }

int ol_song_get_ccli_num  (OLSong *song) { return song->ccliNo; }
void ol_song_set_ccli_num  (OLSong *song, int num) { song->ccliNo = num; }

const char *ol_song_get_release_date  (OLSong *song) { return song->releaseDate; }
void ol_song_set_release_date      (OLSong *song, const char *date) { ol_string_set(&song->releaseDate,date); }

int ol_song_get_transposition  (OLSong *song) { return song->transposition; }
void ol_song_set_transposition  (OLSong *song, int transposition) { song->transposition = transposition; }

int ol_song_get_tempo_bpm        (OLSong *song)
{
  if (song->tempo_type==OL_TEMPO_TEXT)
    return -1;  
  return atoi(song->tempo);
}
const char *ol_song_get_tempo_text    (OLSong *song) { return song->tempo; }
void ol_song_set_tempo_bpm        (OLSong *song, int bpm)
{
  char tmp[(sizeof(int)*8+1)];
  free(song->tempo);
  
  sprintf(&tmp[0],"%d",bpm);
  ol_string_set(&song->tempo,&tmp[0]);
  song->tempo_type=OL_TEMPO_BPM;
}
void ol_song_set_tempo_text          (OLSong *song, const char *text)
{
  ol_string_set(&song->tempo,text);
  song->tempo_type=OL_TEMPO_TEXT;
}
OL_TEMPO_TYPE ol_song_get_tempo_type (OLSong *song) { return song->tempo_type;}

const char *ol_song_get_key  (OLSong *song) { return song->key; }
void ol_song_set_key    (OLSong *song, const char *key) { ol_string_set(&song->key,key); }

const char *ol_song_get_variant  (OLSong *song) { return song->variant; }
void ol_song_set_variant    (OLSong *song, const char *variant) { ol_string_set(&song->variant,variant); }

const char *ol_song_get_publisher  (OLSong *song) { return song->publisher; }
void ol_song_set_publisher      (OLSong *song, const char *publisher) { ol_string_set(&song->publisher,publisher); }

const char *ol_song_get_custom_version  (OLSong *song) { return song->customVersion; }
void ol_song_set_custom_version      (OLSong *song, const char *version) { ol_string_set(&song->customVersion,version); }

int ol_song_num_keywords  (OLSong *song) { return song->num_keywords; }
const char **ol_song_get_keywords(OLSong *song) { return (const char**)song->keywords; }
const char *ol_song_get_keyword  (OLSong *song, int index) { return song->keywords[index]; }
void ol_song_add_keyword    (OLSong *song, const char *keyword) { ol_array_add_elem((OLArray*)&song->keywords,&song->num_keywords,(void*)keyword); }

int ol_song_get_num_verse_order    (OLSong *song);
const int *ol_song_get_verse_order  (OLSong *song);
const int *ol_song_set_verse_order  (OLSong *song, const int *order);

int ol_song_num_songbooks  (OLSong *song) { return song->num_songbooks; }
OLSongbook **ol_song_get_songbooks (OLSong *song) { return song->songbooks; }
void ol_song_get_songbook  (OLSong *song, int index, char **name, char **entry, char **lang) { ol_songbook_get(song->songbooks[index], name, entry, lang); }
void ol_song_add_songbook  (OLSong *song, const char *name, const char *entry, const char *lang) { ol_array_add_elem((OLArray*)&song->songbooks,&song->num_songbooks,ol_songbook_new(name, entry, lang)); }

int ol_song_num_themes  (OLSong *song) { return song->num_themes; }
OLTheme **ol_song_get_themes (OLSong *song) { return song->themes; }
void ol_song_get_theme  (OLSong *song, int index, char **name, int *id, char **lang) { ol_theme_get(song->themes[index], name, id, lang); }
void ol_song_add_theme  (OLSong *song, const char *name, int id, const char *lang) { ol_array_add_elem((OLArray*)&song->themes,&song->num_themes,ol_theme_new(name, id, lang)); }

int ol_song_num_verses (OLSong *song) { return song->num_verses; }
int ol_song_add_verse (OLSong *song, const char *name, const char *lang) { ol_array_add_elem((OLArray*)&song->verses,&song->num_verses,ol_verse_new(name,lang));return song->num_verses-1; }
OLVerse **ol_song_get_verses (OLSong *song) { return song->verses; }
void ol_song_get_verse (OLSong *song, int index, char **name, char **lang) { ol_verse_get(song->verses[index],name,lang); }
OLVerse *ol_song_get_verse_at(OLSong *song, int index) { return song->verses[index]; }
int ol_song_verse_num_lines (OLSong *song, int index) { return ol_verse_num_lines(song->verses[index]); }
void ol_song_verse_add_line (OLSong *song, int index, const char *text, const char *part, const char *lang) { ol_verse_add_line(song->verses[index],text,part,lang); }
void ol_song_verse_get_line (OLSong *song, int verse_index, int index, char **text, char **part, char **lang) { ol_verse_get_line(song->verses[verse_index],index,text,part,lang); }

