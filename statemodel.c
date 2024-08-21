#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "cmdmodel.h"
#include "effects.h"
#include "statemodel.h"

/* Generic front-end for handling events. Should do nothing more
   than calling the appropriate *_event function based on the type. */
bool
handle_event (fsm_t *fsm, event_t event)
{
  // TODO: Look up the current state/event combination in the
  // transition table. Print the following line for debugging
  // purposes:
  //   printf ("[%s.%s -> %s]\n", ...);
  // BOILERPLATE:
  // TODO: If the state/event combination is valid, execute
  // the transition and return true. If invalid, call the
  // error function and return false.

  return true;
}
