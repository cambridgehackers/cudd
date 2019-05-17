#
CUDDINC = -I../cudd -I.. -I../st -I../mtr -I../epd
CPPFLAGS := -std=c++11 $(CUDDINC)
all:
	g++ $(CPPFLAGS) jca.cpp ../cudd/.libs/libcudd.a
	./a.out
