all:
	gcc -o jackdiff global_t.h rtqueue.c osc_handlers.c osc.c jackdiff.c -ljack -lpthread -lm -llo
