#ifndef __statemodel_h__
#define __statemodel_h__

#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <unistd.h>

// States and events should just be integers
typedef int state_t;
typedef int event_t;

// Needed for circular typedef. This lets action_t use fsm_t in its parameter
// list, while the struct fsm can use action_t as a field.
typedef struct fsm fsm_t;

// All entry, exit, and effect instances use the action type
typedef void (*action_t) (fsm_t *);

// Each FSM instance contains a current state
struct fsm
{
  state_t state;  // current state
  size_t nevents; // number of events for this FSM

  // pointer to the FSM's transition function
  state_t (*transition) (struct fsm *, event_t, action_t *);

  // Additional data fields specific to this FSM
  char *command; // the name of the command to run
  size_t nargs;  // the number of command-line arguments
  char **args;   // the command-line arguments

  char *current_token; // current token being processed
};

// Generic entry point for handling events
bool handle_event (fsm_t *fsm, event_t event);

#endif
