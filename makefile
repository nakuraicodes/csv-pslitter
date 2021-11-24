CC = g++ -std=c++17
CFLAGS = -Wall -MD
INCLUDES = 
LIBS = 

# INCLUDES = -I./src/headers -I./lib/iup/include
# LIBS =  -liup -lgdi32 -lcomdlg32 -lcomctl32 -luuid -loleaut32 -lole32 -L./lib/iup
# PROG = csv-splitter.exe
# $(PROG):
# 	$(CC) $(PROG).cpp -o $(PROG).exe $(GTK_4_INCLUDES)


OBJS = main.o
# link
csv-splitter: $(OBJS)
	$(CC) $(INCLUDES) $(CFLAGS) $(OBJS) $(LIBS) -o $@.exe 

# compile
%.o: ./src/%.cpp
	$(CC) $(INCLUDES) $(CFLAGS) -c ./src/$*.cpp $(LIBS) -o $@


install:
	@echo This is not implemented yet.

clean:
	-del *.o *.d *.exe

-include $(OBJS:.o=.d)