CC = g++

EXE = runner

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
TEST_SRC_DIR = tests
TEST_OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC = $(wildcard $(TEST_SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ = $(TEST_SRC:$(TEST_SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
F_OBJ = $(filter-out obj/main.o,$(OBJ))
DEPS = $(wildcard $(INC_DIR)/*.h*)

CCFLAGS = -std=c++11 -O3 -pthread

.PHONY: clean
.PHONY: directories

$(EXE): directories $(OBJ)
	$(CC) -o $@ $(OBJ) $(CCFLAGS)
	#
	#	OK! now try the dataset by typing:
	#		./runner < init
	#	or automate it
	#		time ./runner < init | ./check.sh ./workloads/small/small.result
	#

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(EXE) $(OBJ) $(TEST_OBJ) test_*

directories:
	mkdir -p obj

#compile for gdb
d: CCFLAGS += -g3

d: $(EXE)

############## tests

test_result: CCFLAGS += -D TEST_RESULT
test_result: ./obj/result.o
	$(CC) -o $@ $^ $(CCFLAGS)

test_utils: ./obj/utils.o ./obj/testUtils.o
	$(CC) -o $@ $^ $(CCFLAGS)
	#
	# OK! now try ./test_utils
	#

test_parsing: $(F_OBJ) ./obj/testParsing.o
	$(CC) -o $@ $^ $(CCFLAGS)
	#
	# OK! now try echo -e '\n' | cat ./workloads/small/small.init - ./workloads/small/small.work | ./test_parsing
	#

test_relation: $(F_OBJ) ./obj/testRelation.o
	$(CC) -o $@ $^ $(CCFLAGS)
	@echo '#!/bin/bash\nDIFF=$$(diff <(cat $$(cat ./workloads/small/small.init | sed "s/.*/\.\/workloads\/small\/&\.tbl/")) <(./test_relation < ./workloads/small/small.init))\nif [ "$$DIFF" == "" ]\nthen\necho PASSED\nelse\necho FAILED\nfi' > test_relation.sh
	@chmod +x ./test_relation.sh
	#
	# OK! now try ./test_relation.sh
	# (disable LOG for test to work)
	#

test_threads: ./obj/testThreads.o ./obj/jobScheduler.o
	$(CC) -o $@ $^ $(CCFLAGS)
	#
	# OK! now try ./test_threads [Threads] [Jobs]

test_stats: $(F_OBJ) ./obj/testStats.o
	$(CC) -o $@ $^ $(CCFLAGS)
	#
	# OK! now try echo -e '\n' | cat ./workloads/small/small.init - ./workloads/small/small.work | ./test_parsing
	#
