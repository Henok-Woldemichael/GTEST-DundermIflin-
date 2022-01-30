PROGRAM_TEST = testPaper
PROGRAM_TEST_CLEAN = $(PROGRAM_TEST)-clean
PROGRAM_TEST_BUGS = $(PROGRAM_TEST)-bugs

# Compilation command and flags
CXX=g++
CXXVERSION= -std=c++11
CXXFLAGS= $(CXXVERSION)
LINKFLAGS= -lgtest
LIB_CLEAN = -Llibs -lpaper-clean
LIB_BUGS = -Llibs -lpaper-bugs

# Directories
GTEST_DIR = test
SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

# Tool varialbes
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint.py

DOXY_DIR = docs/code

# Default goal, used by Atom for local compilation
.DEFAULT_GOAL := test_buggy

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# clean up all files that should NOT be submitted
.PHONY: clean
clean:
	rm -rf *~ $(SRC)/*.o *.o $(GTEST_DIR)/output/*.dat \
	*.gcov *.gcda *.gcno *.orig ???*/*.orig \
	$(PROJECT) $(COVERAGE_RESULTS) \
	$(GTEST) $(MEMCHECK_RESULTS) $(COVERAGE_DIR)  \
	$(DOXY_DIR)/html obj bin $(PROGRAM_TEST_CLEAN).exe
	$(PROGRAM_TEST_BUGS).exe

$(PROGRAM_TEST_CLEAN): $(TEST_DIR)
		$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST_CLEAN) $(INCLUDE) \
		$(GTEST_DIR)/*.cpp $(LINKFLAGS) $(LIB_CLEAN)

$(PROGRAM_TEST_BUGS): $(TEST_DIR)
		$(CXX) $(CXXFLAGS) -o $(PROGRAM_TEST_BUGS) $(INCLUDE) \
		$(GTEST_DIR)/*.cpp $(LINKFLAGS) $(LIB_BUGS)

# To perform unit tests
tests: $(PROGRAM_TEST_CLEAN) #$(PROGRAM_TEST_BUGS)
	$(PROGRAM_TEST_CLEAN)

# To perform all tests
.PHONY: allTests
allTests: $(PROGRAM_TEST_CLEAN) $(PROGRAM_TEST_BUGS) \
		memcheck docs static style

memcheck: $(GTEST)
	valgrind --tool=memcheck --leak-check=yes $(PROGRAM_TEST_CLEAN)

fullmemcheck: $(GTEST)
	valgrind --tool=memcheck --leak-check=full $(PROGRAM_TEST_CLEAN)

static: ${GTEST_DIR}
	${STATIC_ANALYSIS} --verbose --enable=all ${GTEST_DIR} --suppress=missingInclude

style: ${SRC_DIR} ${GTEST_DIR}
	${STYLE_CHECK} ${GTEST_DIR}/*

docs: ${SRC_INCLUDE}
	doxygen $(DOXY_DIR)/doxyfile
