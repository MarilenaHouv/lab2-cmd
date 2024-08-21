#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cmdmodel.h"
#include "effects.h"
#include "statemodel.h"

/* Initialize FSM to contain pointers to transition table, effect table,
   and entry actions. Also set the live, runtime, and state values to
   defaults. Return true if successful. Return false if anything fails
   or cannot be set successfully. */
fsm_t *
cmdline_init (void)
{
  return NULL;
}

event_t
lookup (char *token)
{
  if (!strcmp (token, "|"))
    return PIPE;

  if (!strcmp (token, "NL"))
    return NEWLINE;

  return TOKEN;
}

// TODO: Complete this table mapping state/events to the target state
static state_t const _transitions[NUM_STATES][NUM_EVENTS] = {
};

// TODO: Create a table mapping states/events to the effect functions


const char *
event_name (event_t evt)
{
  assert (evt <= NIL);

  // Event names for printing out
  const char *names[] = { "TOKEN", "PIPE", "NEWLINE", "NIL" };
  return names[evt];
}

const char *
state_name (state_t st)
{
  assert (st <= NST);

  // State names for printing out
  const char *names[]
      = { "Init", "Command", "Arguments", "Make_Pipe", "Term", "NST" };
  return names[st];
}
