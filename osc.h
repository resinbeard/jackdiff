/* osc.h
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

'cyperus' is a JACK client for learning about software synthesis

Copyright 2015 murray foster */

#ifndef OSC_H
#define OSC_H

#include <lo/lo.h>

#include "osc_handlers.h"

volatile char *send_host_out;
volatile char *send_port_out;
extern lo_server_thread lo_thread;

int osc_setup(char *osc_port_in, char *osc_port_out);
int osc_change_address(char *new_host_out, char *new_port_out);

#endif
