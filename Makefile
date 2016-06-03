TextRemix="TextRemix"
path=$(PWD)

CXX = g++  
CXXFLAGS = -Wall -O2 -Werror -Wextra -Wno-unused-local-typedefs
GCCVERSION := $(shell expr `gcc -dumpversion | cut -f1 -d.` \>= 6)
ifeq "$(GCCVERSION)" "1"
  CXXFLAGS += -Wno-error=misleading-indentation
endif

INCLUDE = -I /opt/local/include -I $(path)

MKDIR_BIN = mkdir -p $(path)/bin

all: mkdirBin createNewIdioms createSyllableSorted sortDatabaseStrings expandRhymeDatabase removeDatabaseDuplicates randomizeTxtFile createSimplePoem createHaiku addToMachineDatabase createRandomStrings createCombinedInput testReturnFileList testGetRhyme testGetSyllable

mkdirBin: 
	$(MKDIR_BIN)

createNewIdioms: src/createNewIdioms.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createNewIdioms.exe src/createNewIdioms.C 

createSyllableSorted: src/createSyllableSorted.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createSyllableSorted.exe src/createSyllableSorted.C 

sortDatabaseStrings: src/sortDatabaseStrings.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/sortDatabaseStrings.exe src/sortDatabaseStrings.C 

expandRhymeDatabase: src/expandRhymeDatabase.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/expandRhymeDatabase.exe src/expandRhymeDatabase.C 

removeDatabaseDuplicates: src/removeDatabaseDuplicates.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/removeDatabaseDuplicates.exe src/removeDatabaseDuplicates.C 

randomizeTxtFile: src/randomizeTxtFile.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/randomizeTxtFile.exe src/randomizeTxtFile.C

createSimplePoem: src/createSimplePoem.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createSimplePoem.exe src/createSimplePoem.C

createHaiku: src/createHaiku.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createHaiku.exe src/createHaiku.C

addToMachineDatabase: src/addToMachineDatabase.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/addToMachineDatabase.exe src/addToMachineDatabase.C

createRandomStrings: src/createRandomStrings.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createRandomStrings.exe src/createRandomStrings.C 

createCombinedInput: src/createCombinedInput.C
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/createCombinedInput.exe src/createCombinedInput.C 

testReturnFileList: testFunctions/testReturnFileList.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/testReturnFileList.exe testFunctions/testReturnFileList.C 

testGetRhyme: testFunctions/testGetRhyme.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/testGetRhyme.exe testFunctions/testGetRhyme.C 

testGetSyllable: testFunctions/testGetSyllable.C 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o bin/testGetSyllable.exe testFunctions/testGetSyllable.C 

clean:
	sh cleanup/cleanAll.sh || true