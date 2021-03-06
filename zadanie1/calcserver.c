/*
	calcserver.c

	Example calculator service in C

	Compilation in C (see samples/calc/calc.h):
	$ soapcpp2 -c calc.h
	$ cc -o calcserver calcserver.c stdsoap2.c soapC.c soapServer.c
	where stdsoap2.c is in the 'gsoap' directory, or use libgsoap:
	$ cc -o calcserver calcserver.c soapC.c soapServer.c -lgsoap

--------------------------------------------------------------------------------
gSOAP XML Web services tools
Copyright (C) 2001-2008, Robert van Engelen, Genivia, Inc. All Rights Reserved.
This software is released under one of the following two licenses:
GPL or Genivia's license for commercial use.
--------------------------------------------------------------------------------
GPL license.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 59 Temple
Place, Suite 330, Boston, MA 02111-1307 USA

Author contact information:
engelen@genivia.com / engelen@acm.org
--------------------------------------------------------------------------------
A commercial use license is available from Genivia, Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include "soapH.h"
#include "calc.nsmap"

int main(int argc, char **argv)
{ SOAP_SOCKET m, s; /* master and slave sockets */
  struct soap soap;
  soap_init(&soap);
  if (argc < 2)
    soap_serve(&soap);	/* serve as CGI application */
  else
  { m = soap_bind(&soap, NULL, atoi(argv[1]), 100);
    if (!soap_valid_socket(m))
    { soap_print_fault(&soap, stderr);
      exit(-1);
    }
    fprintf(stderr, "Socket connection successful: master socket = %d\n", m);
    for ( ; ; )
    { s = soap_accept(&soap);
      fprintf(stderr, "Socket connection successful: slave socket = %d\n", s);
      if (!soap_valid_socket(s))
      { soap_print_fault(&soap, stderr);
        exit(-1);
      } 
      soap_serve(&soap);
      soap_end(&soap);
    }
  }
  return 0;
} 

int ns__add(struct soap *soap, double a, double b, double *result)
{ *result = a + b;
  return SOAP_OK;
} 


