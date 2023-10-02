CFLAGS = -Wall -Werror -Wextra
ARCH = $(shell arch)
ifeq "$(ARCH)" "i386"
MYFLAGS = -lm --coverage -lgtest
endif
ifeq "$(ARCH)" "x86_64"
MYFLAGS =-L/usr/lib -lm --coverage -lgtest
endif

all: clean test gcov_report

test:
	g++ -std=c++17 $(CFLAGS) model/*.cc model/tests/test.cc $(MYFLAGS) -o  test
	./test
	

gcov_report: test
	./test
	gcovr --html-details rep.html
	open rep.html


clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css
	rm -f test
	rm -rf *.gcno *.gcov *.gcda *.info ../*.h.gch

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -n *.cpp
	clang-format -n *.h
	
git:
	git add *.cpp *.h *.cc model/*.cc model/*.h view/*.cc view/*.h ExtLib/ model/tests/*.h
	git add Makefile
	
