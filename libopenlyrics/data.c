
#include <openlyrics/data.h>
#include <openlyrics/util.h>
#include <stdlib.h>

#define OL_DATA_FREE(obj) free((obj)->name);free((obj)->lang)

void ol_data_get (OLData *data, char **name, char **lang)
{
  (*name) = data->name;
  (*lang) = data->lang;
}
void ol_data_set (OLData *data, const char *name, const char *lang)
{
  ol_set_string(&data->name, name);
  ol_set_string(&data->lang, lang);
}

OLTitle *ol_title_new(const char *name, const char *lang) 
{ 
  OLTitle *title = ol_new_object(sizeof(OLTitle));
  ol_title_set(title, name, lang);
  return title;
}
void ol_title_free(OLTitle *title) { OL_DATA_FREE(title);free(title); }
void ol_title_get(OLTitle *title, char **name, char **lang) { ol_data_get((OLData*)title,name,lang); }
void ol_title_set(OLTitle *title, const char *name, const char *lang) { ol_data_set((OLData*)title, name, lang); }
OLTitle *ol_title_copy(OLTitle *title) { return ol_title_new(title->name,title->lang); }

OLAuthor *ol_author_new(const char *name, OL_AUTHOR_TYPE type, const char *lang)
{
  OLAuthor *author = ol_new_object(sizeof(OLAuthor));
  ol_author_set(author, name, type, lang);
  return author;
}
void ol_author_free(OLAuthor *author) { OL_DATA_FREE(author);free(author); }
void ol_author_get(OLAuthor *author, char **name, char **lang, OL_AUTHOR_TYPE *type)
{
  ol_data_get((OLData*)author, name, lang);
  (*type) = author->type;
}
void ol_author_set(OLAuthor *author, const char *name, OL_AUTHOR_TYPE type, const char *lang)
{
  ol_data_set((OLData*)author, name, lang);
  author->type = type;
}
OLAuthor *ol_author_copy(OLAuthor *author) { return ol_author_new(author->name, author->type, author->lang); }

OL_AUTHOR_TYPE ol_author_get_type(OLAuthor *author) { return author->type; }
void ol_author_set_type(OLAuthor *author, OL_AUTHOR_TYPE type) { author->type = type; }

OLSongbook *ol_songbook_new(const char *name, const char *entry, const char *lang)
{
  OLSongbook *songbook = ol_new_object(sizeof(OLSongbook));
  ol_songbook_set(songbook, name, entry, lang);
  return songbook;
}
void        ol_songbook_free (OLSongbook *songbook) { OL_DATA_FREE(songbook);free(songbook->entry);free(songbook); }
OLSongbook *ol_songbook_copy (OLSongbook *songbook) { return ol_songbook_new(songbook->name, songbook->entry, songbook->lang); }
void        ol_songbook_get  (OLSongbook *songbook, char **name, char **entry, char **lang)
{
  ol_data_get((OLData*)songbook, name, lang);
  (*lang) = songbook->lang;
}
void        ol_songbook_set  (OLSongbook *songbook, const char *name, const char *entry, const char *lang)
{
  ol_data_set((OLData*)songbook, name, lang);
  ol_set_string(&songbook->entry, entry);
}

OLTheme *ol_theme_new(const char *name, int id, const char *lang)
{
  OLTheme *theme = ol_new_object(sizeof(OLTheme));
  ol_theme_set(theme, name, id, lang);
  return theme;
}
void ol_theme_free(OLTheme *theme) { OL_DATA_FREE(theme);free(theme); }
OLTheme *ol_theme_copy (OLTheme *theme) { return ol_theme_new(theme->name, theme->id, theme->lang); }
void     ol_theme_get  (OLTheme *theme, char **name, int *id, char **lang)
{
  ol_data_get((OLData*)theme, name, lang);
  (*id) = theme->id;
}
void     ol_theme_set  (OLTheme *theme, const char *name, int id, const char *lang)
{
  ol_data_set((OLData*)theme, name, lang);
  theme->id = id;
}


