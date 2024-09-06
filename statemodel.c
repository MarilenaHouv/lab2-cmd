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
  assert (fsm != NULL);
  // assert (fsm->state < NST);

  // lookup curr state/event in transition table
  action_t effect = NULL;
  state_t next = fsm->transition (fsm, event, &effect);

  // if invalid/ range of valid values from 0
  if (next == NST || next < 0)
    {
      return false;
    }

  printf ("[%s.%s -> %s]\n", state_name (fsm->state), event_name (event),
          state_name (next));
  // if effect found
  if (effect != NULL)
    {
      effect (fsm);
    }
  // set state to next
  fsm->state = next;

  return true;
}
