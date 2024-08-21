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
  printf ("Starting new command: %s\n", cmdmodel->current_token);
}

void
append (fsm_t *cmdmodel)
{
  if (cmdmodel->nargs >= MAX_ARGUMENTS)
    return;

  printf ("Appending %s to the argument list\n", cmdmodel->current_token);
  assert (cmdmodel->args != NULL);

}

void
execute (fsm_t *cmdmodel)
{
  assert (cmdmodel->args != NULL);

  printf ("Execute %s with arguments { %s, %s }", "ls", "ls", NULL);
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
