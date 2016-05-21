CXX = g++
CXXFLAGS = -Wall -O2 -Werror -Wextra
GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

all: createNewIdioms createSyllableSorted sortDatabaseStrings expandRhymeDatabase removeDatabaseDuplicates randomizeTxtFile createSimplePoem createHaiku addToMachineDatabase testReturnFileList testGetRhyme testGetSyllable

createNewIdioms: src/createNewIdioms.C
	$(CXX) $(CXXFLAGS) -o bin/createNewIdioms.exe src/createNewIdioms.C 

createSyllableSorted: src/createSyllableSorted.C 
	$(CXX) $(CXXFLAGS) -o bin/createSyllableSorted.exe src/createSyllableSorted.C 

sortDatabaseStrings: src/sortDatabaseStrings.C 
	$(CXX) $(CXXFLAGS) -o bin/sortDatabaseStrings.exe src/sortDatabaseStrings.C 

expandRhymeDatabase: src/expandRhymeDatabase.C 
	$(CXX) $(CXXFLAGS) -o bin/expandRhymeDatabase.exe src/expandRhymeDatabase.C 

removeDatabaseDuplicates: src/removeDatabaseDuplicates.C 
	$(CXX) $(CXXFLAGS) -o bin/removeDatabaseDuplicates.exe src/removeDatabaseDuplicates.C 

randomizeTxtFile: src/randomizeTxtFile.C
	$(CXX) $(CXXFLAGS) -o bin/randomizeTxtFile.exe src/randomizeTxtFile.C

createSimplePoem: src/createSimplePoem.C
	$(CXX) $(CXXFLAGS) -o bin/createSimplePoem.exe src/createSimplePoem.C

createHaiku: src/createHaiku.C
	$(CXX) $(CXXFLAGS) -o bin/createHaiku.exe src/createHaiku.C

addToMachineDatabase: src/addToMachineDatabase.C
	$(CXX) $(CXXFLAGS) -o bin/addToMachineDatabase.exe src/addToMachineDatabase.C

testReturnFileList: testFunctions/testReturnFileList.C 
	$(CXX) $(CXXFLAGS) -o bin/testReturnFileList.exe testFunctions/testReturnFileList.C 

testGetRhyme: testFunctions/testGetRhyme.C 
	$(CXX) $(CXXFLAGS) -o bin/testGetRhyme.exe testFunctions/testGetRhyme.C 

testGetSyllable: testFunctions/testGetSyllable.C 
	$(CXX) $(CXXFLAGS) -o bin/testGetSyllable.exe testFunctions/testGetSyllable.C 

clean:
	sh cleanup/cleanAll.sh || true