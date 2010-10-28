
#include <ruby.h>
#include <openlyrics/parse.h>
#include <openlyrics/song.h>
#include <openlyrics/data.h>

#define RB_OL_STR_NEW(str) rb_str_new2((str)==NULL ? "" : (str))

VALUE ol_mod = Qnil, ol_mod_error = Qnil, ol_class_song = Qnil, ol_class_data = Qnil;
VALUE ol_class_author = Qnil, ol_class_title = Qnil, ol_class_songbook = Qnil, ol_class_theme = Qnil;
VALUE ol_class_line, ol_class_verse = Qnil;

OL_ERROR ol_curr_error = OL_ERROR_NONE;

VALUE rb_ol_get_error(VALUE self) { return INT2NUM(ol_curr_error); }
VALUE rb_ol_get_error_str(VALUE self) { return RB_OL_STR_NEW(ol_error_str(ol_curr_error)); }

VALUE rb_ol_data_get_name(VALUE self)
{
  OLData *dataptr;
	Data_Get_Struct(self,OLData,dataptr);
	return RB_OL_STR_NEW(dataptr->name);
}
VALUE rb_ol_data_set_name(VALUE self, VALUE data)
{
  OLData *dataptr;
	Data_Get_Struct(self,OLData,dataptr);
	ol_set_string(&dataptr->name,RSTRING(data)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_data_get_lang(VALUE self)
{
  OLData *dataptr;
	Data_Get_Struct(self,OLData,dataptr);
	return RB_OL_STR_NEW(dataptr->lang);
}
VALUE rb_ol_data_set_lang(VALUE self, VALUE data)
{
  OLData *dataptr;
	Data_Get_Struct(self,OLData,dataptr);
	ol_set_string(&dataptr->lang,RSTRING(data)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_new_song(VALUE self) { return (VALUE)Data_Wrap_Struct(ol_class_song,0,ol_song_free,ol_song_new(NULL,NULL)); }

VALUE rb_ol_make_title(OLTitle *title) { return (VALUE)Data_Wrap_Struct(ol_class_title,0,ol_title_free,title); }
VALUE rb_ol_new_title(VALUE self) { return rb_ol_make_title(ol_title_new(NULL,NULL)); }

VALUE rb_ol_make_author(OLAuthor *author) { return (VALUE)Data_Wrap_Struct(ol_class_author,0,0,author); }
VALUE rb_ol_new_author(VALUE self) { return rb_ol_make_author(ol_author_new(NULL,OL_AUTHOR_INVALID,NULL)); }

VALUE rb_ol_make_theme(OLTheme *theme) { return (VALUE)Data_Wrap_Struct(ol_class_theme,0,0,theme); }
VALUE rb_ol_new_theme(VALUE self) { return rb_ol_make_theme(ol_theme_new(NULL,0,NULL)); }

VALUE rb_ol_make_songbook(OLSongbook *songbook) { return (VALUE)Data_Wrap_Struct(ol_class_songbook,0,0,songbook); }
VALUE rb_ol_new_songbook(VALUE self) { return rb_ol_make_theme(ol_songbook_new(NULL,0,NULL)); }

VALUE rb_ol_make_line(OLLine *line) { return (VALUE)Data_Wrap_Struct(ol_class_line,0,0,line); }
VALUE rb_ol_new_line(VALUE self) { return rb_ol_make_line(ol_line_new(NULL,NULL,NULL)); }

VALUE rb_ol_make_verse(OLVerse *verse) { return (VALUE)Data_Wrap_Struct(ol_class_verse,0,0,verse); }
VALUE rb_ol_new_verse(VALUE self) { return rb_ol_make_verse(ol_verse_new(NULL,NULL)); }

VALUE rb_ol_line_get_part(VALUE self)
{
	OLLine *line;Data_Get_Struct(self,OLLine,line);
	return RB_OL_STR_NEW(ol_line_get_part(line));
}
VALUE rb_ol_line_set_part(VALUE self, VALUE part)
{
	OLLine *line;Data_Get_Struct(self,OLLine,line);
	ol_line_set_part(line,RSTRING(part)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_verse_get_lines(VALUE self)
{
  OLVerse *verse;Data_Get_Struct(self,OLVerse,verse);

	OLLine **lines = ol_verse_get_lines(verse);	
  VALUE array = rb_ary_new2(ol_verse_num_lines(verse));

  int i;
  for (i=0;i<ol_verse_num_lines(verse);i=i+1)
    rb_ary_store(array,i,rb_ol_make_line(ol_line_copy(lines[i])));

  return array;
}

VALUE rb_ol_song_parse_from_file(VALUE self, VALUE uri)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
  ol_curr_error = ol_song_parse_from_file(song, RSTRING(uri)->ptr);
  return INT2NUM(ol_curr_error);
}

VALUE rb_ol_song_get_createdin(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return RB_OL_STR_NEW(ol_song_get_createdin(song));
}
VALUE rb_ol_song_set_createdin(VALUE self, VALUE createdin)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_createdin(song,RSTRING(createdin)->ptr);
	return INT2NUM(0);
}

VALUE rb_ol_song_get_modifiedin(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return RB_OL_STR_NEW(ol_song_get_modifiedin(song));
}
VALUE rb_ol_song_set_modifiedin(VALUE self, VALUE modifiedin)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_modifiedin(song,RSTRING(modifiedin)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_modifieddate(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return RB_OL_STR_NEW(ol_song_get_modifieddate(song));
}
VALUE rb_ol_song_set_modifieddate(VALUE self, VALUE modifieddate)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_modifieddate(song,RSTRING(modifieddate)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_titles(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);
	
	OLTitle **titles = ol_song_get_titles(song);	
  VALUE array = rb_ary_new2(ol_song_num_titles(song));
  
  int i;
  for (i=0;i<ol_song_num_titles(song);i=i+1)
    rb_ary_store(array,i,rb_ol_make_title(ol_title_copy(titles[i])));
  
  return array;
}

VALUE rb_ol_song_get_authors(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);
	
	OLAuthor **authors = ol_song_get_authors(song);	
  VALUE array = rb_ary_new2(ol_song_num_authors(song));
  
  int i;
  for (i=0;i<ol_song_num_authors(song);i=i+1)
    rb_ary_store(array,i,rb_ol_make_author(ol_author_copy(authors[i])));
  
  return array;
}

VALUE rb_ol_author_get_type(VALUE self)
{
	OLAuthor *author;Data_Get_Struct(self,OLAuthor,author);
	return INT2NUM(ol_author_get_type(author));
}
VALUE rb_ol_author_set_type(VALUE self, VALUE type)
{
	OLAuthor *author;Data_Get_Struct(self,OLAuthor,author);
	ol_author_set_type(author,NUM2INT(type));
	return INT2NUM(1);
}

VALUE rb_ol_song_get_copyright(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return RB_OL_STR_NEW(ol_song_get_copyright(song));
}
VALUE rb_ol_song_set_copyright(VALUE self, VALUE copyright)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_copyright(song,RSTRING(copyright)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_ccli_num(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return INT2NUM(ol_song_get_ccli_num(song));
}
VALUE rb_ol_song_set_ccli_num(VALUE self, VALUE ccli_num)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_ccli_num(song,NUM2INT(ccli_num));
	return INT2NUM(1);
}

VALUE rb_ol_song_get_release_date(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return rb_str_new2(ol_song_get_release_date(song));
}
VALUE rb_ol_song_set_release_date(VALUE self, VALUE release_date)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_release_date(song,RSTRING(release_date)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_transposition(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return INT2NUM(ol_song_get_transposition(song));
}
VALUE rb_ol_song_set_transposition(VALUE self, VALUE transposition)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_transposition(song,NUM2INT(transposition));
	return INT2NUM(1);
}

VALUE rb_ol_song_get_tempo(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	if (ol_song_get_tempo_type(song)==OL_TEMPO_BPM)
	  return INT2NUM(ol_song_get_tempo_bpm(song));
	else
	  return rb_str_new2(ol_song_get_tempo_text(song));
}
VALUE rb_ol_song_set_tempo(VALUE self, VALUE tempo)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	if (ol_song_get_tempo_type(song)==OL_TEMPO_BPM)
	  ol_song_set_tempo_bpm(song,NUM2INT(tempo));
	else
	  ol_song_set_tempo_text(song,RSTRING(tempo)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_key(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return rb_str_new2(ol_song_get_key(song));
}
VALUE rb_ol_song_set_key(VALUE self, VALUE key)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_key(song,RSTRING(key)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_variant(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return rb_str_new2(ol_song_get_variant(song));
}
VALUE rb_ol_song_set_variant(VALUE self, VALUE variant)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_variant(song,RSTRING(variant)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_custom_version(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return rb_str_new2(ol_song_get_custom_version(song));
}
VALUE rb_ol_song_set_custom_version(VALUE self, VALUE custom_version)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_custom_version(song,RSTRING(custom_version)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_keywords(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);

  VALUE array = rb_ary_new2(ol_song_num_keywords(song));
    
  int i;
  for (i=0;i<ol_song_num_keywords(song);i=i+1)
    rb_ary_store(array,i,RB_OL_STR_NEW(ol_song_get_keyword(song,i)));
  
  return array;
}

VALUE rb_ol_song_get_songbooks(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);
	
	OLSongbook **songbooks = ol_song_get_songbooks(song);	
  VALUE array = rb_ary_new2(ol_song_num_songbooks(song));
  
  int i;
  for (i=0;i<ol_song_num_songbooks(song);i=i+1)
    rb_ary_store(array,i,rb_ol_make_songbook(ol_songbook_copy(songbooks[i])));
  
  return array;
}

VALUE rb_ol_song_get_themes(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);
	
	OLTheme **themes = ol_song_get_themes(song);	
  VALUE array = rb_ary_new2(ol_song_num_themes(song));
  
  int i;
  for (i=0;i<ol_song_num_themes(song);i=i+1)
    rb_ary_store(array,i,rb_ol_make_theme(ol_theme_copy(themes[i])));
  
  return array;
}

VALUE rb_ol_song_get_verses(VALUE self)
{
  OLSong *song;Data_Get_Struct(self,OLSong,song);
	
	OLVerse **verses = ol_song_get_verses(song);	
  VALUE array = rb_ary_new2(ol_song_num_verses(song));
  
  int i;
  for (i=0;i<ol_song_num_verses(song);i=i+1)
    rb_ary_store(array,i,rb_ol_make_verse(ol_verse_copy(verses[i])));
  
  return array;
}

/*
VALUE rb_ol_song_get_string(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return rb_str_new2(ol_song_get_string(song));
}
VALUE rb_ol_song_set_string(VALUE self, VALUE string)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_string(song,RSTRING(string)->ptr);
	return INT2NUM(1);
}

VALUE rb_ol_song_get_integer(VALUE self)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	return INT2NUM(ol_song_get_integer(song));
}
VALUE rb_ol_song_set_ccli_num(VALUE self, VALUE integer)
{
	OLSong *song;Data_Get_Struct(self,OLSong,song);
	ol_song_set_integer(song,NUM2INT(integer));
	return INT2NUM(1);
}
*/

void Init_openlyrics() {
	ol_mod = rb_define_module("OL");
	
	ol_mod_error = rb_define_module_under(ol_mod,"Error");	
  rb_define_const(ol_mod_error,"None", 		INT2NUM(OL_ERROR_NONE));
  rb_define_const(ol_mod_error,"Input", 	INT2NUM(OL_ERROR_INPUT));
  rb_define_const(ol_mod_error,"XML", 		INT2NUM(OL_ERROR_XML));
  rb_define_const(ol_mod_error,"Root", 		INT2NUM(OL_ERROR_ROOT));
  rb_define_const(ol_mod_error,"Version",	INT2NUM(OL_ERROR_VERSION));
  rb_define_module_function(ol_mod_error,"get",rb_ol_get_error,0);
  rb_define_module_function(ol_mod_error,"get_s",rb_ol_get_error_str,0);
  
  ol_class_data = rb_define_class_under(ol_mod, "Data", rb_cObject);
	rb_define_method(ol_class_data,"name",  rb_ol_data_get_name, 0);
	rb_define_method(ol_class_data,"name=", rb_ol_data_set_name, 1);
	rb_define_method(ol_class_data,"lang",  rb_ol_data_get_lang, 0);
	rb_define_method(ol_class_data,"lang=", rb_ol_data_set_lang, 1);
	
	ol_class_title  = rb_define_class_under(ol_mod, "Title",  ol_class_data);
	rb_define_alloc_func(ol_class_title, rb_ol_new_title);
	
	ol_class_author = rb_define_class_under(ol_mod, "Author", ol_class_data);
	rb_define_alloc_func(ol_class_author, rb_ol_new_author);
	rb_define_const(ol_class_author,"Invalid", 	   INT2NUM(OL_AUTHOR_INVALID));
  rb_define_const(ol_class_author,"Words", 	     INT2NUM(OL_AUTHOR_WORDS));
  rb_define_const(ol_class_author,"Music", 		   INT2NUM(OL_AUTHOR_MUSIC));
  rb_define_const(ol_class_author,"Translation", INT2NUM(OL_AUTHOR_TRANSLATION));
  rb_define_method(ol_class_author,"type",       rb_ol_author_get_type, 0);
	rb_define_method(ol_class_author,"type=",      rb_ol_author_set_type, 1);
	
	ol_class_songbook = rb_define_class_under(ol_mod, "Songbook",  ol_class_data);
	rb_define_alloc_func(ol_class_songbook, rb_ol_new_songbook);
	
	ol_class_theme = rb_define_class_under(ol_mod, "Theme",  ol_class_data);
	rb_define_alloc_func(ol_class_theme, rb_ol_new_theme);
	
	ol_class_line = rb_define_class_under(ol_mod, "Line",  ol_class_data);
	rb_define_alloc_func(ol_class_line, rb_ol_new_line);
  rb_define_method(ol_class_line,"part",  rb_ol_line_get_part, 0);
  rb_define_method(ol_class_line,"part=", rb_ol_line_set_part, 1);
	
	ol_class_verse = rb_define_class_under(ol_mod, "Verse",  ol_class_data);
	rb_define_alloc_func(ol_class_verse, rb_ol_new_verse);
	rb_define_method(ol_class_verse,"lines", rb_ol_verse_get_lines, 0);
	
	ol_class_song = rb_define_class_under(ol_mod, "Song", rb_cObject);
	rb_define_alloc_func(ol_class_song, rb_ol_new_song);
	rb_define_method(ol_class_song,"parse",           rb_ol_song_parse_from_file,    1);
	rb_define_method(ol_class_song,"createdin",       rb_ol_song_get_createdin,      0);
	rb_define_method(ol_class_song,"createdin=",      rb_ol_song_set_createdin,      1);
	rb_define_method(ol_class_song,"modifiedin",      rb_ol_song_get_modifiedin,     0);
	rb_define_method(ol_class_song,"modifiedin=",     rb_ol_song_set_modifiedin,     1);
	rb_define_method(ol_class_song,"modifieddate",    rb_ol_song_get_modifieddate,   0);
	rb_define_method(ol_class_song,"modifieddate=",   rb_ol_song_set_modifieddate,   1);
	rb_define_method(ol_class_song,"titles",          rb_ol_song_get_titles,         0);
	rb_define_method(ol_class_song,"authors",         rb_ol_song_get_authors,        0);
	rb_define_method(ol_class_song,"copyright",       rb_ol_song_get_copyright,      0);
	rb_define_method(ol_class_song,"copyright=",      rb_ol_song_set_copyright,      1);
	rb_define_method(ol_class_song,"ccli_num",        rb_ol_song_get_ccli_num,       0);
	rb_define_method(ol_class_song,"ccli_num=",       rb_ol_song_set_ccli_num,       1);
	rb_define_method(ol_class_song,"release_date",    rb_ol_song_get_release_date,   0);
	rb_define_method(ol_class_song,"release_date=",   rb_ol_song_set_release_date,   1);
	rb_define_method(ol_class_song,"transposition",   rb_ol_song_get_transposition,  0);
	rb_define_method(ol_class_song,"transposition=",  rb_ol_song_set_transposition,  1);
	rb_define_method(ol_class_song,"tempo",           rb_ol_song_get_tempo,          0);
	rb_define_method(ol_class_song,"tempo=",          rb_ol_song_set_tempo,          1);
	rb_define_method(ol_class_song,"key",             rb_ol_song_get_key,            0);
	rb_define_method(ol_class_song,"key=",            rb_ol_song_set_key,            1);
	rb_define_method(ol_class_song,"variant",         rb_ol_song_get_variant,        0);
	rb_define_method(ol_class_song,"variant=",        rb_ol_song_set_variant,        1);
	rb_define_method(ol_class_song,"custom_version",  rb_ol_song_get_custom_version, 0);
	rb_define_method(ol_class_song,"custom_version=", rb_ol_song_set_custom_version, 1);
	rb_define_method(ol_class_song,"keywords",        rb_ol_song_get_keywords,       0);
	rb_define_method(ol_class_song,"songbooks",       rb_ol_song_get_songbooks,      0);
	rb_define_method(ol_class_song,"themes",          rb_ol_song_get_themes,         0);
	rb_define_method(ol_class_song,"verses",          rb_ol_song_get_verses,         0);

	rb_global_variable(ol_mod);
	rb_global_variable(ol_mod_error);
	rb_global_variable(ol_class_song);	
}
