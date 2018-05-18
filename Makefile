HEADERS = Direction.h Piece.h PiecePosition.h PositionSet.h
SOURCES = Direction.cxx PositionSet.cxx Piece.cxx main.cxx

cube: $(HEADERS) $(SOURCES)
	g++ -std=c++14 -g $(SOURCES) -o cube

tags ctags:
	ctags $(HEADERS) $(SOURCES)
