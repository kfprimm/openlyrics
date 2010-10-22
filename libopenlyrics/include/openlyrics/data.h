
#ifndef OPENLYRICS_DATA_H
#define OPENLYRICS_DATA_H

typedef enum tagOL_AUTHOR_TYPE
{
  OL_AUTHOR_INVALID,
  OL_AUTHOR_WORDS,
  OL_AUTHOR_MUSIC,
  OL_AUTHOR_TRANSLATION
} OL_AUTHOR_TYPE;

typedef enum tagOL_TEMPO_TYPE
{
  OL_TEMPO_INVALID,
  OL_TEMPO_BPM,
  OL_TEMPO_TEXT
} OL_TEMPO_TYPE;

typedef struct tagOLData
{
  char *name, *lang;
} OLData;

typedef struct tagOLTitle 
{
  char *name, *lang;
} OLTitle; 

typedef struct tagOLAuthor
{
  char *name, *lang;
  OL_AUTHOR_TYPE type;
  
} OLAuthor;

typedef struct tagOLSongbook
{
  char *name, *lang;
  char *entry;
} OLSongbook;

typedef struct tagOLTheme
{
  char *name, *lang;
  int id;  
} OLTheme;

typedef struct tagOLLine
{
  char *name, *lang;
  char *part;
} OLLine;

typedef struct tagOLVerse
{
  char *name, *lang;
  OLLine **lines;
  int num_lines;
} OLVerse;

void ol_data_get (OLData *data, char **name, char **lang);
void ol_data_set (OLData *data, const char *name, const char *lang);

OLTitle *ol_title_new  (const char *name, const char *lang);
void     ol_title_free (OLTitle *title);
OLTitle *ol_title_copy (OLTitle *title);
void     ol_title_set  (OLTitle *title, const char *name, const char *lang);

OLAuthor       *ol_author_new      (const char *name, OL_AUTHOR_TYPE type, const char *lang);
void            ol_author_free     (OLAuthor *author);
OLAuthor       *ol_author_copy     (OLAuthor *author);
void            ol_author_set      (OLAuthor *author, const char *name, OL_AUTHOR_TYPE type, const char *lang);
OL_AUTHOR_TYPE  ol_author_get_type (OLAuthor *author);
void            ol_author_set_type (OLAuthor *author, OL_AUTHOR_TYPE type);

OLSongbook *ol_songbook_new  (const char *name, const char *entry, const char *lang);
void        ol_songbook_free (OLSongbook *songbook);
OLSongbook *ol_songbook_copy (OLSongbook *songbook);
void        ol_songbook_get  (OLSongbook *songbook, char **name, char **entry, char **lang);
void        ol_songbook_set  (OLSongbook *songbook, const char *name, const char *entry, const char *lang);

OLTheme *ol_theme_new  (const char *name, int id, const char *lang);
void     ol_theme_free (OLTheme *theme);
OLTheme *ol_theme_copy (OLTheme *theme);
void     ol_theme_get  (OLTheme *theme, char **name, int *id, char **lang);
void     ol_theme_set  (OLTheme *theme, const char *name, int id, const char *lang);

OLLine *ol_line_new  (const char *name, const char *part, const char *lang);
void    ol_line_free (OLLine *line);
OLLine *ol_line_copy (OLLine *line);
void    ol_line_get  (OLLine *line, char **name, char **part, char **lang);
void    ol_line_set  (OLLine *line, const char *name, const char *part, const char *lang);

OLVerse *ol_verse_new  (const char *name, const char *lang);
void     ol_verse_free (OLVerse *verse);
OLVerse *ol_verse_copy (OLVerse *verse);
int      ol_verse_num_lines (OLVerse *verse);
OLLine **ol_verse_get_lines (OLVerse *verse);
void ol_verse_get_line(OLVerse *verse, int index, char **name, char **part, char **lang);
void ol_verse_add_line (OLVerse *verse, int index, const char *name, const char *part, const char *lang);

#endif
