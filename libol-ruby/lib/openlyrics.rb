
require File.dirname(__FILE__) + '/../ext/openlyrics'

module OL
	class Song	
		def initialize(file = "")
			parse(file) if file != ""
		end
	end
end
