
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
  ol_string_set(&data->name, name);
  ol_string_set(&data->lang, lang);
}

OLTitle *ol_title_new(const char *name, const char *lang) 
{ 
  OLTitle *title = ol_object_new(sizeof(OLTitle));
  ol_title_set(title, name, lang);
  return title;
}
void ol_title_free(OLTitle *title) {}// OL_DATA_FREE(title);free(title); }
void ol_title_get(OLTitle *title, char **name, char **lang) { ol_data_get((OLData*)title,name,lang); }
void ol_title_set(OLTitle *title, const char *name, const char *lang) { ol_data_set((OLData*)title, name, lang); }
OLTitle *ol_title_copy(OLTitle *title) { return ol_title_new(title->name,title->lang); }

OLAuthor *ol_author_new(const char *name, OL_AUTHOR_TYPE type, const char *lang)
{
  OLAuthor *author = ol_object_new(sizeof(OLAuthor));
  ol_author_set(author, name, type, lang);
  return author;
}
void ol_author_free(OLAuthor *author) {}// OL_DATA_FREE(author);free(author); }
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
  OLSongbook *songbook = ol_object_new(sizeof(OLSongbook));
  ol_songbook_set(songbook, name, entry, lang);
  return songbook;
}
void        ol_songbook_free (OLSongbook *songbook) {}// OL_DATA_FREE(songbook);free(songbook->entry);free(songbook); }
OLSongbook *ol_songbook_copy (OLSongbook *songbook) { return ol_songbook_new(songbook->name, songbook->entry, songbook->lang); }
void        ol_songbook_get  (OLSongbook *songbook, char **name, char **entry, char **lang)
{
  ol_data_get((OLData*)songbook, name, lang);
  (*lang) = songbook->lang;
}
void        ol_songbook_set  (OLSongbook *songbook, const char *name, const char *entry, const char *lang)
{
  ol_data_set((OLData*)songbook, name, lang);
  ol_string_set(&songbook->entry, entry);
}

OLTheme *ol_theme_new(const char *name, int id, const char *lang)
{
  OLTheme *theme = ol_object_new(sizeof(OLTheme));
  ol_theme_set(theme, name, id, lang);
  return theme;
}
void ol_theme_free(OLTheme *theme) {}// OL_DATA_FREE(theme);free(theme); }
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

OLLine *ol_line_new  (const char *name, const char *part, const char *lang)
{
  OLLine *line = ol_object_new(sizeof(OLLine));
  ol_line_set(line, name, part, lang);
  return line;
}
void    ol_line_free (OLLine *line) {}// OL_DATA_FREE(line);free(line->part);free(line); }
OLLine *ol_line_copy (OLLine *line) { return ol_line_new(line->name, line->part, line->lang); }
void    ol_line_get  (OLLine *line, char **name, char **part, char **lang)
{
  ol_data_get((OLData*)line, name, lang);
  (*part) = line->part;
}
void    ol_line_set  (OLLine *line, const char *name, const char *part, const char *lang)
{
  ol_data_set((OLData*)line, name, lang);
  ol_string_set(&line->part, part);
}

OLVerse *ol_verse_new  (const char *name, const char *lang)
{
  OLVerse *verse = ol_object_new(sizeof(OLVerse));
  ol_data_set((OLData*)verse, name, lang);
  return verse;
}
void     ol_verse_free      (OLVerse *verse) {}
/*{
  OL_DATA_FREE(verse);
  ol_array_free(verse->lines,ol_verse_num_lines(verse),ol_line_free);
  free(verse);
}*/
OLVerse *ol_verse_copy      (OLVerse *verse)
{
  OLVerse *new_verse = ol_verse_new(verse->name, verse->lang);
  new_verse->lines = ol_array_copy(verse->lines,ol_verse_num_lines(verse),ol_line_copy);
  return new_verse;
}
int      ol_verse_num_lines (OLVerse *verse) { return verse->num_lines; }
OLLine **ol_verse_get_lines (OLVerse *verse) { return verse->lines; }
void ol_verse_get_line      (OLVerse *verse, int index, char **name, char **part, char **lang) { ol_line_get(verse->lines[index], name, part, lang); }
void ol_verse_add_line (OLVerse *verse, int index, const char *name, const char *part, const char *lang)
 { ol_array_add_elem((void**)&verse->lines,&verse->num_lines,ol_line_new(name, part, lang)); }


