/*
*         OpenPBS (Portable Batch System) v2.3 Software License
*
* Copyright (c) 1999-2000 Veridian Information Solutions, Inc.
* All rights reserved.
*
* ---------------------------------------------------------------------------
* For a license to use or redistribute the OpenPBS software under conditions
* other than those described below, or to purchase support for this software,
* please contact Veridian Systems, PBS Products Department ("Licensor") at:
*
*    www.OpenPBS.org  +1 650 967-4675                  sales@OpenPBS.org
*                        877 902-4PBS (US toll-free)
* ---------------------------------------------------------------------------
*
* This license covers use of the OpenPBS v2.3 software (the "Software") at
* your site or location, and, for certain users, redistribution of the
* Software to other sites and locations.  Use and redistribution of
* OpenPBS v2.3 in source and binary forms, with or without modification,
* are permitted provided that all of the following conditions are met.
* After December 31, 2001, only conditions 3-6 must be met:
*
* 1. Commercial and/or non-commercial use of the Software is permitted
*    provided a current software registration is on file at www.OpenPBS.org.
*    If use of this software contributes to a publication, product, or
*    service, proper attribution must be given; see www.OpenPBS.org/credit.html
*
* 2. Redistribution in any form is only permitted for non-commercial,
*    non-profit purposes.  There can be no charge for the Software or any
*    software incorporating the Software.  Further, there can be no
*    expectation of revenue generated as a consequence of redistributing
*    the Software.
*
* 3. Any Redistribution of source code must retain the above copyright notice
*    and the acknowledgment contained in paragraph 6, this list of conditions
*    and the disclaimer contained in paragraph 7.
*
* 4. Any Redistribution in binary form must reproduce the above copyright
*    notice and the acknowledgment contained in paragraph 6, this list of
*    conditions and the disclaimer contained in paragraph 7 in the
*    documentation and/or other materials provided with the distribution.
*
* 5. Redistributions in any form must be accompanied by information on how to
*    obtain complete source code for the OpenPBS software and any
*    modifications and/or additions to the OpenPBS software.  The source code
*    must either be included in the distribution or be available for no more
*    than the cost of distribution plus a nominal fee, and all modifications
*    and additions to the Software must be freely redistributable by any party
*    (including Licensor) without restriction.
*
* 6. All advertising materials mentioning features or use of the Software must
*    display the following acknowledgment:
*
*     "This product includes software developed by NASA Ames Research Center,
*     Lawrence Livermore National Laboratory, and Veridian Information
*     Solutions, Inc.
*     Visit www.OpenPBS.org for OpenPBS software support,
*     products, and information."
*
* 7. DISCLAIMER OF WARRANTY
*
* THIS SOFTWARE IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND. ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT
* ARE EXPRESSLY DISCLAIMED.
*
* IN NO EVENT SHALL VERIDIAN CORPORATION, ITS AFFILIATED COMPANIES, OR THE
* U.S. GOVERNMENT OR ANY OF ITS AGENCIES BE LIABLE FOR ANY DIRECT OR INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* This license will be governed by the laws of the Commonwealth of Virginia,
* without reference to its choice of law rules.
*/

#include <pbs_config.h>   /* the master config generated by configure */

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pbs_ifl.h"
#ifndef NULL
#define NULL 0
#endif

#define ISNAMECHAR(x) ( (isgraph(x)) && ((x) != '@') && ((x) != ':') )

/*
 *
 * parse_stage_name
 *
 * syntax:
 *
 * locat_file@hostname:remote_file
 *
 * Arguments:
 *
 * pair A staged file name pair.
 * local Local file name.
 * host Remote host.
 * remote Remote file name.
 *
 */

int
parse_stage_name(char *pair, char **local, char **host, char **remote)
  {
  int i;
  char *c;
  static char local_name[MAXPATHLEN+1];
  static int l_pos;
  static char host_name[PBS_MAXSERVERNAME];
  static int h_pos;
  static char remote_name[MAXPATHLEN+1];
  static int r_pos;

  /* initialize static data for this parsing call */

  for (i = 0; i < MAXPATHLEN + 1; i++) local_name[i] = '\0';

  l_pos = 0;

  for (i = 0; i < PBS_MAXSERVERNAME; i++) host_name[i] = '\0';

  h_pos = 0;

  for (i = 0; i < MAXPATHLEN + 1; i++) remote_name[i] = '\0';

  r_pos = 0;

  /* Begin the parse */
  c = pair;

  while (isspace(*c)) c++;

  /* Looking for something before the @ sign */
  while (*c != '\0')
    {
    if (ISNAMECHAR(*c))
      {
      if (l_pos >= MAXPATHLEN) return 1;

      local_name[l_pos++] = *c;
      }
    else
      break;

    c++;
    }

  if (l_pos == 0) return 1;

  /* Looking for something between the @ and the : */
  if (*c == '@')
    {
    c++;

    while (*c != '\0')
      {
      if (ISNAMECHAR(*c))
        {
        if (h_pos >= PBS_MAXSERVERNAME) return 1;

        host_name[h_pos++] = *c;
        }
      else
        break;

      c++;
      }
    }

  if (h_pos == 0) return 1;

  /* Looking for something after the : */
  if (*c == ':')
    {
    c++;

    while (*c != '\0')
      {
      if (ISNAMECHAR(*c))
        {
        if (r_pos >= MAXPATHLEN) return 1;

        remote_name[r_pos++] = *c;
        }
      else
        break;

      c++;
      }
    }

  if (r_pos == 0) return 1;

  if (*c != '\0') return 1;

  /* set char * pointers to static data, to arguments */
  if (local  != NULL) *local = local_name;

  if (host   != NULL) *host = host_name;

  if (remote != NULL) *remote = remote_name;

  return (0);
  }



/*
 *
 * parse_stage_list
 *
 * syntax:
 *
 * local_file@hostname:remote_file [,...]
 *
 * Arguments:
 *
 * list List of staged file name pairs.
 *
 */

int
parse_stage_list(char *list)
  {
  char *b, *c, *s, *l;
  int comma = 0;
  char *local, *host, *remote;

  if (strlen(list) == 0) return (1);

  if ((l = (char *)calloc(1, strlen(list) + 1)) == (char *)0)
    {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
    }

  strcpy(l, list);

  c = l;

  while (*c != '\0')
    {
    /* Drop leading white space */
    while (isspace((int)*c)) c++;

    /* Find the next comma */
    s = c;

    while (*c != '\0' && *c != ',') c++;

    /* Drop any trailing blanks */
    comma = (*c == ',');

    *c = '\0';

    b = c - 1;

    while (isspace((int)*b)) *b-- = '\0';

    /* Parse the individual list item */
    if (parse_stage_name(s, &local, &host, &remote))
      {
      (void)free(l);
      return 1;
      }

    /* Make sure all parts of the item are present */
    if (strlen(local)  == 0)
      {
      (void)free(l);
      return 1;
      }

    if (strlen(host)   == 0)
      {
      (void)free(l);
      return 1;
      }

    if (strlen(remote) == 0)
      {
      (void)free(l);
      return 1;
      }

    if (comma)
      {
      c++;
      }
    }

  if (comma)
    {
    (void)free(l);
    return 1;
    }

  (void)free(l);

  return 0;
  }