/* osc_handlers.h
This file is a part of 'cyperus'
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

'cyperus' is a JACK client for learning about software synthesis

Copyright 2015 murray foster */

#include <lo/lo.h>

#include "global_t.h"

#ifndef OSC_HANDLERS_H
#define OSC_HANDLERS_H

void osc_error(int num, const char *msg, const char *path);

int osc_address_handler(const char *path, const char *types, lo_arg ** argv,
			int argc, void *data, void *user_data);
 
int osc_is_ready_handler(const char *path, const char *types, lo_arg ** argv,
                         int argc, void *data, void *user_data);
int
osc_start_handler(const char *path, const char *types, lo_arg ** argv,
                  int argc, void *data, void *user_data);

#endif
