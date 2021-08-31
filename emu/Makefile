BIN=emu
OBJ=bus.o cpu.o device.o main.o memory.o null_device.o
TEST_BIN=bus_test cpu_test memory_test
TEST_OBJ=$(TEST_BIN:=.o)

CXX=clang++
CXXFLAGS=-Wall -Wextra -Werror -std=c++17

SRCS=$(OBJ:.o=.cc) $(TEST_BIN:=.cc)
DEPS=$(SRCS:.cc=.d)

default: $(BIN)

all: $(BIN) $(TEST_BIN)

clean:
	rm -f $(BIN) $(TEST_BIN) $(OBJ) $(TEST_OBJ)

cleandeps:
	rm -f $(DEPS)

cleanall: clean cleandeps

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ) $(TEST_OBJ): %.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TEST_BIN): %_test: %_test.o $(filter-out main.o,$(OBJ))
	$(CXX) $(CXXFLAGS) -o $@ $^

run_test_targets=$(addprefix run_, $(TEST_BIN))
$(run_test_targets): run_%: %
	./$<

test: $(run_test_targets)

$(DEPS): %.d: %.cc
	$(CXX) $(CXXFLAGS) -MF $@ -MM $<

$(DEPS):

deps: $(DEPS)

include $(DEPS)

.PHONY: all clean cleanall cleandeps default deps test
