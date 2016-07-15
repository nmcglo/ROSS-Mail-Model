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
#include "ross.h"
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
	TWOPT_GROUP("ROSS Model"),
	TWOPT_UINT("setting_1", setting_1, "first setting for this model"),
	TWOPT_END(),
};

//for doxygen
#define mail_main main
int mail_main(int argc, char* argv[])
{
     // int i;
	int num_lps_per_pe;

	tw_opt_add(model_opts);
	tw_init(&argc, &argv);


     num_lps_per_pe = 1;

	//set up LPs within ROSS
	tw_define_lps(num_lps_per_pe, sizeof(letter));

     g_tw_lp_types = model_lps;
     tw_lp_setup_types();


	tw_run();

	tw_end();

	return 0;
}
