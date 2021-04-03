/* osc_handlers.c
This file is a part of 'cyperus'
This program is free software: you can redistribute it and/or modify
hit under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

'jackdiff' is a JACK client for learning about software synthesis

Copyright 2015 murray foster */

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);

#include "global_t.h"
#include "osc.h"
#include "osc_handlers.h"

void osc_error(int num, const char *msg, const char *path)
{
  printf("liblo server error %d in path %s: %s\n", num, path, msg);
  fflush(stdout);
}

/* for debugging,
 * catch any incoming messages and display them. returning 1 means that the
 * message has not been fully handled and the server should try other methods */
int generic_handler(const char *path, const char *types, lo_arg ** argv,
                    int argc, void *data, void *user_data)
{
  int i;
  
  printf("path: <%s>\n", path);
  for (i = 0; i < argc; i++) {
    printf("arg %d '%c' ", i, types[i]);
    lo_arg_pp((lo_type)types[i], argv[i]);
    printf("\n");
  }
  return 0;
}

int osc_address_handler(const char *path, const char *types, lo_arg **argv,
			int argc, void *data, void *user_data)
{
  char *new_host_out = argv[0];
  char *new_port_out = argv[1];
  printf("hit osc_address_handler\n");
  osc_change_address(new_host_out, new_port_out);

  return 0;
} /* osc_address_handler */

int osc_is_ready_handler(const char *path, const char *types, lo_arg ** argv,
				 int argc, void *data, void *user_data)
{
  printf("osc_is_ready_handler()");
  global_audio_capture_flag = 1;
  printf("done\n");

  return 0;
} /* osc_is_ready_handler */

int osc_start_handler(const char *path, const char *types, lo_arg ** argv,
                      int argc, void *data, void *user_data)
{
  
  /* lo_send(lo_addr_send,"/cyperus/add/module/osc_transmit","ssssi", module_id, host, port, osc_path, samplerate_divisor); */
  /* free(lo_addr_send); */

  printf("done\n");

  return 0;
} /* osc_start_handler */

