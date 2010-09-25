
PROGRAM = applauncher

OBJS    = gui_gtk.o listcmd.o options.o main.o
SRCS    = gui_gtk.c listcmd.c options.c main.c

CC      = gcc #C compiler
FLAGS   = -O3 -std=c99 `pkg-config --cflags gtk+-2.0`
LIBS    = -lgtk-x11-2.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0
DESTDIR = 
BIN     = $(DESTDIR)/usr/bin

all:      $(PROGRAM)

.c.o:	$(SRCS)
	$(CC) $(FLAGS) -c $*.c -o $@ 

applauncher:	$(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

release:	$(PROGRAM)
	strip $(PROGRAM)

clean:
	rm -f $(OBJS)  $(PROGRAM) 

install: release
	cp $(PROGRAM) $(BIN)/

uninstall:
	rm -f $(INST_DIR)/$(PROGRAM)

run: $(PROGRAM)
	./applauncher --config applauncher.list

