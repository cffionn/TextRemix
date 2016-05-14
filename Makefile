CXX = g++
CXXFLAGS = -Wall -O2 -Werror -Wextra
GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

all: createNewIdioms.exe createSyllableSorted.exe sortDatabaseStrings.exe expandRhymeDatabase.exe testFunctions/testReturnFileList.exe testFunctions/testGetRhyme.exe testFunctions/testGetSyllable.exe

createNewIdioms.exe: createNewIdioms.C
	$(CXX) $(CXXFLAGS) -o createNewIdioms.exe createNewIdioms.C 

createSyllableSorted.exe: createSyllableSorted.C 
	$(CXX) $(CXXFLAGS) -o createSyllableSorted.exe createSyllableSorted.C 

sortDatabaseStrings.exe: sortDatabaseStrings.C 
	$(CXX) $(CXXFLAGS) -o sortDatabaseStrings.exe sortDatabaseStrings.C 

expandRhymeDatabase.exe: expandRhymeDatabase.C 
	$(CXX) $(CXXFLAGS) -o expandRhymeDatabase.exe expandRhymeDatabase.C 

testFunctions/testReturnFileList.exe: testFunctions/testReturnFileList.C 
	$(CXX) $(CXXFLAGS) -o testFunctions/testReturnFileList.exe testFunctions/testReturnFileList.C 

testFunctions/testGetRhyme.exe: testFunctions/testGetRhyme.C 
	$(CXX) $(CXXFLAGS) -o testFunctions/testGetRhyme.exe testFunctions/testGetRhyme.C 

testFunctions/testGetSyllable.exe: testFunctions/testGetSyllable.C 
	$(CXX) $(CXXFLAGS) -o testFunctions/testGetSyllable.exe testFunctions/testGetSyllable.C 

clean:
	sh cleanup/cleanAll.sh || true