#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "cmdmodel.h"
#include "effects.h"
#include "statemodel.h"

static state_t const _transitions[NUM_STATES][NUM_EVENTS];
static action_t const _effects[NUM_STATES][NUM_EVENTS];
static state_t parse_transition (fsm_t *, event_t, action_t *);
/* Initialize FSM to contain pointers to transition table, effect table,
   and entry actions. Also set the live, runtime, and state values to
   defaults. Return true if successful. Return false if anything fails
   or cannot be set successfully. */
fsm_t *
cmdline_init (void)
{
  // alocate memory
  fsm_t *fsm = calloc (1, sizeof (fsm_t));

  fsm->state = Init; // current state
  fsm->transition
      = parse_transition;    // pointer to the FSM's transition function
  fsm->nevents = NUM_EVENTS; // # of events for this FSM

  // Additional data fields specific to this FSM
  fsm->command = NULL; // the name of the command to run
  fsm->nargs = 0;      // t# of command-line arguments
  fsm->args = NULL;    // the command-line arguments
  fsm->current_token = NULL;

  return fsm;
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
  // each row is transitions from single state
  { Command, Term, NST },         // Init
  { Arguments, Make_Pipe, Term }, // Command
  { Arguments, Make_Pipe, Term }, // Arguments
  { Command, Term, Term },        // Make pipe
  { NST, NST, NST },              // Term
};

// TODO: Create a table mapping states/events to the effect functions
// row=state, column=event
static action_t const _effects[NUM_STATES][NUM_EVENTS] = {
  { start_command, error_pipe, NULL },          // Init
  { append, link_commands, execute },           // Command
  { append, link_commands, execute },           // Arguments
  { start_command, error_pipe, error_newline }, // Make pipe
  { NULL, NULL, NULL },                         // Term
};

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

static state_t
parse_transition (fsm_t *fsm, event_t event, action_t *effect)
{
  *effect = _effects[fsm->state][event];
  state_t next = _transitions[fsm->state][event];
  return next;
}
