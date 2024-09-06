#define _POSIX_C_SOURCE 200809L // needed for strdup extension

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdmodel.h"
#include "effects.h"

void
start_command (fsm_t *cmdmodel)
{

  // copy token to command field of fsm_t
  cmdmodel->command = cmdmodel->current_token;
  // setup args and nargs = 1 (for arg dynamically allocate array)
  cmdmodel->args = calloc (MAX_ARGUMENTS, sizeof (char *));
  cmdmodel->args[0] = cmdmodel->current_token;
  cmdmodel->nargs = 1;
  printf ("Starting new command: %s\n", cmdmodel->current_token);
}

void
append (fsm_t *cmdmodel)
{
  assert (cmdmodel->args != NULL);

  if (cmdmodel->nargs >= MAX_ARGUMENTS)
    {
      return;
    }

  // store token and increment nargs
  cmdmodel->args[cmdmodel->nargs] = cmdmodel->current_token;
  cmdmodel->nargs++;
  printf ("Appending %s to the argument list\n", cmdmodel->current_token);
}

void
execute (fsm_t *cmdmodel)
{

  // Start with printing the command
  printf ("Execute %s with arguments { ", cmdmodel->command);

  // print all args
  for (int i = 0; i < cmdmodel->nargs; i++)
    {
      if (cmdmodel->args[i] != NULL)
        { // check arg is not null
          printf ("%s", cmdmodel->args[i]);
          if (i < cmdmodel->nargs - 1)
            {
              printf (", ");
            }
        }
    }

  // add null entry to list
  printf (", (null) }\n");

  free (cmdmodel->args);
  cmdmodel->args = NULL;
}

void
link_commands (fsm_t *cmdmodel)
{
  printf ("Set up pipe\n");
  execute (cmdmodel);
}

void
error_pipe (fsm_t *cmdmodel)
{
  printf ("ERROR: Received token %s while in state %s\n",
          cmdmodel->current_token, state_name (cmdmodel->state));
}

void
error_newline (fsm_t *cmdmodel)
{
  printf ("ERROR: Received token %s while in state %s\n",
          cmdmodel->current_token, state_name (cmdmodel->state));
}
