
#include <stdio.h>
#include <string.h>
#include <openlyrics/parse.h>
#include <openlyrics/song.h>

#define seql(s0,s1) (!strcmp((s0),(s1)))

typedef void (*list_func)(OLSong*,int,int);

void print_whitespace(int size)
{
  int j;
  for (j=0;j<size;j=j+1)
    printf(" ");
}

void list_items(OLSong *song,const char *heading,int count,list_func func)
{
  printf(heading);
  int heading_size = strlen(heading);
  int i;
  for (i=0;i<count;i=i+1)
  {
    if (i>0)
      print_whitespace(heading_size);
    func(song,i,heading_size);
    printf("\n");
  }
  if (count==0)
    printf("\n");
}

void list_titles(OLSong *song,int index, int heading)
{
  char *title, *lang;
  ol_song_get_title(song,index,&title,&lang);
  printf(title);
}

void list_authors(OLSong *song,int index, int heading)
{
  char *name, *lang;
  OL_AUTHOR_TYPE type;
  ol_song_get_author(song,index,&name,&type,&lang);
  printf(name);
}

void list_songbooks(OLSong *song,int index, int heading)
{
  char *name, *entry, *lang;
  ol_song_get_songbook(song,index,&name,&entry,&lang);
  if (entry)
    printf("%s (%s)",name,entry);
  else
    printf(name);
}

void list_themes(OLSong *song,int index, int heading)
{
  char *name, *lang;
  int id;
  ol_song_get_theme(song,index,&name,&id,&lang);
  printf("%s (%i)",name,id);
}

void list_keywords(OLSong *song,int index, int heading)
{
  printf(ol_song_get_keyword(song,index));
}

void list_verses(OLSong *song,int index, int heading)
{
  char *name, *lang;
  OLVerse *verse = ol_song_get_verse_at(song,index);
  ol_verse_get(verse,&name,&lang);
  
  printf("%s",name);
  int i;
  for (i=0;i<ol_verse_num_lines(verse);i+=1)
  {
    char *line, *part;
    ol_verse_get_line(verse,i,&line,&part,&lang);

    if (part==NULL)
      part = "NON";
    else if (seql(part,"men"))
      part = "MEN";
    else if (seql(part,"women"))
      part = "WMN";
    else
      part = "NON";
    
    printf("\n");
    print_whitespace(heading);
    printf("  (%s) %s",part,line); 
  }  
}

int main(int argc, char *argv[])
{
  const char *filename = argv[1];//"./tests/songs/Amazing Grace.xml";
  //const char *filename = "./example_complex.xml";
  OLSong *song = ol_song_new();
  
  OL_ERROR err;
  if (!(err=ol_song_parse_from_file(song,filename)))
  {
    printf("Source:           %s\n",filename);
    printf("Created in:       %s\n",ol_song_get_createdin(song));
    printf("Modified in:      %s\n",ol_song_get_modifiedin(song));
    printf("Last modified on: %s\n",ol_song_get_modifieddate(song));
  
    list_items(song,"Title(s):         ",ol_song_num_titles(song),list_titles);
    list_items(song,"Author(s):        ",ol_song_num_authors(song),list_authors);
  
    printf("Copyright:        %s\n",ol_song_get_copyright(song));
    printf("CCLI number:      %i\n",ol_song_get_ccli_num(song));
    printf("Release date:     %s\n",ol_song_get_release_date(song));
    printf("Transposition:    %i\n",ol_song_get_transposition(song));
    printf("Tempo:            %s\n",ol_song_get_tempo_text(song));
    printf("Key:              %s\n",ol_song_get_key(song));
    printf("Variant:          %s\n",ol_song_get_variant(song));
    printf("Custom Version:   %s\n",ol_song_get_custom_version(song));
  
    list_items(song,"Keywords(s):      ",ol_song_num_keywords(song),list_keywords);
  
    list_items(song,"Songbook(s):      ",ol_song_num_songbooks(song),list_songbooks);
    list_items(song,"Themes(s):        ",ol_song_num_themes(song),list_themes);
    
    list_items(song,"Verse(s):        ",ol_song_num_verses(song),list_verses);
  }
  else
    printf("ERROR: %s\n",ol_error_str(err));
    
  return 0;
}
