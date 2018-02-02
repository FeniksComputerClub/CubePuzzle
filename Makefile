HEADERS = PositionSet.h Piece.h
SOURCES = PositionSet.cxx Piece.cxx main.cxx

cube: $(HEADERS) $(SOURCES)
	g++ -std=c++11 -g $(SOURCES) -o cube
