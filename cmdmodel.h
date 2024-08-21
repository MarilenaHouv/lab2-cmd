#ifndef __cs361_procmodel_h__
#define __cs361_procmodel_h__

#include "statemodel.h"

#define MAX_ARGUMENTS 10

// Events
typedef enum
{
  TOKEN,   // normal command-line token
  PIPE,    // vertical bar character
  NEWLINE, // newline at the end of the command
  NIL      // invalid non-event
} cmdevt_t;
#define NUM_EVENTS NIL

// Possible states
typedef enum
{
  Init,      // initial state
  Command,   // establishing the command name
  Arguments, // building the argument list
  Make_Pipe, // linking the commands together for a pipe
  Term,      // terminal state (execute program or error)
  NST        // invalid non-state
} cmdst_t;
#define NUM_STATES NST

fsm_t *cmdline_init (void);
event_t lookup (char *);

const char *event_name (event_t);
const char *state_name (state_t);

#endif
