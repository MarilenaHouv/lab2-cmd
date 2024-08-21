/*
 * CS 361: Template lab driver
 *
 * Name:
 */

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cmdmodel.h"
#include "statemodel.h"

void
usage (void)
{
  printf ("shell, a command line state model simulator\n\n");
  printf ("usage: shell cmd [arg ...] [ | cmd [arg ...] ... ]\n");
  printf ("Each cmd can contain an argument list of variable length\n");
  printf ("Each cmd after the first must be preceded by a pipe | character\n");
}

int
main (int argc, char **argv)
{
  // With no arguments, show usage and exit
  if (argc != 2)
    {
      usage ();
      return EXIT_FAILURE;
    }

  // Declare and initialize a FSM
  fsm_t *cmdmodel = cmdline_init ();
  if (cmdmodel == NULL)
    return EXIT_FAILURE;

  // TODO: Change this to split the string into tokens, where
  // each token is an event that needs to be handled.
  event_t event = lookup (argv[1]);
  handle_event (cmdmodel, event);

  if (cmdmodel->args != NULL)
    free (cmdmodel->args);

  free (cmdmodel);
  return EXIT_SUCCESS;
}
