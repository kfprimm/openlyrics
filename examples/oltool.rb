#!/usr/bin/ruby -rubygems

require 'openlyrics'

def dump_file(filename)
  song = OL::Song.new(filename)
  
  return if OL::Error.get

  titles    = song.titles
  authors   = song.authors
  keywords  = song.keywords
  songbooks = song.songbooks
  themes    = song.themes

  puts "Source:           " + filename
  puts "Created in:       " + song.createdin
  puts "Modified in:      " + song.modifiedin
  puts "Modified date:    " + song.modifieddate

  print "Title(s):"
  puts if keywords.count==0
  titles.each do |title| 
    print "         " if title!=titles[0]
    print "         " + title.name 
    puts " (" + title.lang + ")"
  end

  print "Author(s):"
  puts if authors.count==0
  authors.each do |author| 
    print "          " if author!=authors[0]
    puts "        " + author.name 
  end

  puts "Copyright:        " + song.copyright

  puts "CCLI number:      " + song.ccli_num.to_s
  puts "Release date:     " + song.release_date
  puts "Transposition:    " + song.transposition.to_s
  puts "Tempo:            " + song.tempo
  puts "Key:              " + song.key
  puts "Variant:          " + song.variant
  puts "Custom Version:   " + song.custom_version

  print "Keyword(s):       "
  puts if keywords.count==0
  keywords.each do |keyword| 
    print "                  " if keyword!=keywords[0]
    puts keyword 
  end 
  
  print "Songbook(s):      "
  puts "none" if songbooks.count==0
  songbooks.each do |songbook| 
    print "                  " if songbook!=songbooks[0]
    puts songbook.name 
  end
 
  print "Theme(s):         "
  puts if themes.count==0
  themes.each do |theme| 
    print "                  " if theme!=themes[0]
    puts theme.name
  end
end

dump_file ARGV.join
