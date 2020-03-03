include ./prefix.sh

CXX_FLAGS= -g
CPP_FILES=$(wildcard *.cpp)
OBJ = $(patsubst %.cpp,%.o,$(CPP_FILES))
AimSvrd = ${Svrd}${Version}
BIN_PATH=./bin/
$(AimSvrd):$(OBJ)
	$(CXX) -o $(AimSvrd) $(OBJ)
	@echo $(AimSvrd)
	install $(AimSvrd) $(BIN_PATH)
clean:
	@rm *.o $(AimSvrd)
