GOAL=./test
TARGET= main.out
OBJECT=./object
SOURCE=$(wildcard ${GOAL}/*.cpp)

CC=g++
CFLAGS = -g
OBJ=$(patsubst %.cpp,${OBJECT}/%.o,$(notdir ${SOURCE}))
$(TARGET):$(OBJ)
	$(CC) $(OBJ) -o  $(TARGET)

$(OBJECT)/%.o:$(GOAL)/%.cpp
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm -rf ./$(OBJECT)/*.o