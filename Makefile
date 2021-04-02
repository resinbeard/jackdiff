all:
	gcc -o jackdiff jackdiff.c rtqueue.c osc.c osc_handlers.c -ljack -lpthread -lm -llo
