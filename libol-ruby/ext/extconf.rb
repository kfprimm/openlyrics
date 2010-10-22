
require 'mkmf' 

extension_name = 'openlyrics'

cppflags = pkg_config("openlyrics-0.7").join

dir_config(extension_name)
create_makefile(extension_name)

