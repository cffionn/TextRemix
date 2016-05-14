CXX = g++
CXXFLAGS = -Wall -O2 -Werror -Wextra
GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

createNewIdioms.exe: createNewIdioms.o 
	$(CXX) $(CXXFLAGS) -o createNewIdioms.exe createNewIdioms.o 

clean:
	rm *.exe || true
	rm *.o || true