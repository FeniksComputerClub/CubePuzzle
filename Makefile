HEADERS = Direction.h Piece.h PiecePosition.h PositionSet.h MultiLoop.h matrix.h ComboPositions.h RotPos.h Combinations.h
SOURCES = Direction.cxx PositionSet.cxx Piece.cxx main.cxx ComboPositions.cxx RotPos.cxx Combinations.cxx

all: cube rotations

cube: $(HEADERS) $(SOURCES)
	g++ -std=c++11 -O2 $(SOURCES) -o cube

rotations: rotations.cxx
	g++ -std=c++11 -O2 rotations.cxx -o rotations

clean:
	rm cube rotations

tags ctags:
	ctags $(HEADERS) $(SOURCES)
