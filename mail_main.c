/*
     mail_main.c
     Mail System Simulator
     7-15-2016
     Neil McGlohon
*/


//The C main file for a ROSS model
//This file includes:
// - definition of the LP types
// - command line argument setup
// - a main function

//includes
#include "mail.h"

// #define MB_LP 1
// #define PO_LP 2

// Define LP types
tw_lptype model_lps[] = {
  {
    (init_f) mailbox_init,
    (pre_run_f) NULL,
    (event_f) mailbox_event_handler,
    (revent_f) mailbox_RC_event_handler,
    (commit_f) mailbox_commit,
    (final_f) mailbox_final,
    (map_f) mail_map,
    sizeof(state)
  },
  // {
  //   PO_LP, sizeof(post_office_state),
  //   (init_f) post_office_init,
  //   (pre_run_f) NULL,
  //   (event_f) post_office_event_handler,
  //   (revent_f) post_office_RC_event_handler,
  //   (final_f) post_office_final,
  //   (statecp_f) NULL
  // },
  { 0 },
};


//Define command line arguments default values
unsigned int setting_1 = 0;

//add your command line opts
const tw_optdef model_opts[] = {
	TWOPT_GROUP("Mail Model"),
	TWOPT_UINT("nlp", nlp_per_pe, "number of LPs per processor"),
	// TWOPT_STIME("mean", mean, "exponential distribution mean for timestamps"),
	// TWOPT_STIME("mult", mult, "multiplier for event memory allocation"),
	// TWOPT_STIME("lookahead", lookahead, "lookahead for events"),
	// TWOPT_UINT("start-events", g_phold_start_events, "number of initial messages per LP"),
	// TWOPT_UINT("stagger", stagger, "Set to 1 to stagger event uniformly across 0 to end time."),
	// TWOPT_UINT("memory", optimistic_memory, "additional memory buffers"),
	// TWOPT_CHAR("run", run_id, "user supplied run name"),
	TWOPT_END()
};

//for doxygen
#define mail_main main
int mail_main(int argc, char** argv, char **env)
{
     // int i;

	// get rid of error if compiled w/ MEMORY queues
	// g_tw_memory_nqueues=1;
	// set a min lookahead of 1.0
	// lookahead = 1.0;

	tw_opt_add(model_opts);
	tw_init(&argc, &argv);

	// if( lookahead > 1.0 )
	//   tw_error(TW_LOC, "Lookahead > 1.0 .. needs to be less\n");

	// mean = mean - lookahead;

	// g_tw_memory_nqueues = 16; // give at least 16 memory queue event


	// offset_lpid = g_tw_mynode * nlp_per_pe;
	// ttl_lps = tw_nnodes() * g_tw_npe * nlp_per_pe;
	// g_tw_events_per_pe = (mult * nlp_per_pe * g_phold_start_events) +
	// 			optimistic_memory;
	// //g_tw_rng_default = TW_FALSE;
	// g_tw_lookahead = lookahead;

	//set up LPs within ROSS
	tw_define_lps(nlp_per_pe, sizeof(letter));

     g_tw_lp_types = model_lps;
     tw_lp_setup_types();


	tw_run();
	tw_end();

	return 0;
}
