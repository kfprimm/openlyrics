
#ifndef OPENLYRICS_SONG_H
#define OPENLYRICS_SONG_H

#include <openlyrics/data.h>

#ifndef NULL
	#define NULL 0
#endif

typedef enum tagOL_ERROR
{
	OL_ERROR_NONE,
	OL_ERROR_INPUT,
	OL_ERROR_XML,
	OL_ERROR_ROOT,
	OL_ERROR_VERSION
} OL_ERROR;

typedef struct tagOLSong
{
	char *createdIn;
	char *modifiedIn;
	char *modifiedDate;
	
	OLTitle **titles;
	OLAuthor **authors;
	int num_titles, num_authors;
	
	char *copyright;
	int ccliNo;
	char *releaseDate;	
	int transposition;
	
	char *tempo;
	OL_TEMPO_TYPE tempo_type;
	
	char *key;
	char *variant;
	char *publisher;
	char *customVersion;
	
	char **keywords;
	int num_keywords;
	
	int *verseOrder;
	int num_verse_order;
	
	OLSongbook **songbooks;
	int num_songbooks;
	
	OLTheme **themes;
	int num_themes;
	
	OLVerse **verses;
	int num_verses;
} OLSong;

const char *ol_error_str(OL_ERROR error);

OLSong *ol_song_new();
void ol_song_free(OLSong *song);

const char *ol_song_get_createdin	(OLSong *song);
void ol_song_set_createdin			(OLSong *song, const char *createdin);

const char *ol_song_get_modifiedin	(OLSong *song);
void ol_song_set_modifiedin			(OLSong *song, const char *modifiedin);

const char *ol_song_get_modifieddate	(OLSong *song);
void ol_song_set_modifieddate			(OLSong *song, const char *modifieddate);

int ol_song_num_titles	     (OLSong *song);
OLTitle **ol_song_get_titles (OLSong *song);
void ol_song_get_title	     (OLSong *song, int index, char **title, char **lang);
void ol_song_add_title	     (OLSong *song, const char *title, const char *lang);

int ol_song_num_authors	       (OLSong *song);
OLAuthor **ol_song_get_authors (OLSong *song);
void ol_song_get_author	       (OLSong *song, int index, char **name, OL_AUTHOR_TYPE *type, char **lang);
void ol_song_add_author	       (OLSong *song, const char *author,OL_AUTHOR_TYPE type, const char *lang);

const char *ol_song_get_copyright	(OLSong *song);
void ol_song_set_copyright			(OLSong *song, const char *copyright);

int ol_song_get_ccli_num	(OLSong *song);
void ol_song_set_ccli_num	(OLSong *song, int num);

const char *ol_song_get_release_date	(OLSong *song);
void ol_song_set_release_date			(OLSong *song, const char *date);

int ol_song_get_transposition	(OLSong *song);
void ol_song_set_transposition	(OLSong *song, int transposition);

int ol_song_get_tempo_bpm				(OLSong *song);
const char *ol_song_get_tempo_text		(OLSong *song);
void ol_song_set_tempo_bpm				(OLSong *song, int bpm);
void ol_song_set_tempo_text				(OLSong *song, const char *text);
OL_TEMPO_TYPE ol_song_get_tempo_type	(OLSong *song);

const char *ol_song_get_key	(OLSong *song);
void ol_song_set_key		(OLSong *song, const char *key);

const char *ol_song_get_variant	(OLSong *song);
void ol_song_set_variant		(OLSong *song, const char *variant);

const char *ol_song_get_publisher	(OLSong *song);
void ol_song_set_publisher			(OLSong *song, const char *publisher);

const char *ol_song_get_custom_version	(OLSong *song);
void ol_song_set_custom_version			(OLSong *song, const char *version);

int ol_song_get_num_keywords	(OLSong *song);
const char **ol_song_get_keywords(OLSong *song);
const char *ol_song_get_keyword	(OLSong *song, int index);
void ol_song_add_keyword		(OLSong *song, const char *keyword);

int ol_song_get_num_verse_order		(OLSong *song);
const int *ol_song_get_verse_order	(OLSong *song);
const int *ol_song_set_verse_order	(OLSong *song, const int *order);

int ol_song_num_songbooks	(OLSong *song);
OLSongbook **ol_song_get_songbooks (OLSong *song);
void ol_song_get_songbook	(OLSong *song, int index, char **name, char **entry, char **lang);
void ol_song_add_songbook	(OLSong *song, const char *name, const char *entry, const char *lang);

int ol_song_num_themes	(OLSong *song);
OLTheme **ol_song_get_themes (OLSong *song);
void ol_song_get_theme	(OLSong *song, int index, char **name, int *id, char **lang);
void ol_song_add_theme	(OLSong *song, const char *name, int id, const char *lang);

#endif
