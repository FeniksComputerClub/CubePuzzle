HEADERS = Direction.h Piece.h PiecePosition.h PositionSet.h MultiLoop.h matrix.h
SOURCES = Direction.cxx PositionSet.cxx Piece.cxx main.cxx matrix.cxx

cube: $(HEADERS) $(SOURCES)
	g++ -std=c++11 -O2 $(SOURCES) -o cube

clean:
	rm cube

tags ctags:
	ctags $(HEADERS) $(SOURCES)
