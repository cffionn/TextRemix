CXX = g++
CXXFLAGS = -Wall -O2 -Werror -Wextra
GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

all: createNewIdioms createSyllableSorted sortDatabaseStrings expandRhymeDatabase testReturnFileList testGetRhyme testGetSyllable

createNewIdioms: createNewIdioms.C
	$(CXX) $(CXXFLAGS) -o bin/createNewIdioms.exe createNewIdioms.C 

createSyllableSorted: createSyllableSorted.C 
	$(CXX) $(CXXFLAGS) -o bin/createSyllableSorted.exe createSyllableSorted.C 

sortDatabaseStrings: sortDatabaseStrings.C 
	$(CXX) $(CXXFLAGS) -o bin/sortDatabaseStrings.exe sortDatabaseStrings.C 

expandRhymeDatabase: expandRhymeDatabase.C 
	$(CXX) $(CXXFLAGS) -o bin/expandRhymeDatabase.exe expandRhymeDatabase.C 

testReturnFileList: testFunctions/testReturnFileList.C 
	$(CXX) $(CXXFLAGS) -o bin/testReturnFileList.exe testFunctions/testReturnFileList.C 

testGetRhyme: testFunctions/testGetRhyme.C 
	$(CXX) $(CXXFLAGS) -o bin/testGetRhyme.exe testFunctions/testGetRhyme.C 

testGetSyllable: testFunctions/testGetSyllable.C 
	$(CXX) $(CXXFLAGS) -o bin/testGetSyllable.exe testFunctions/testGetSyllable.C 

clean:
	sh cleanup/cleanAll.sh || true