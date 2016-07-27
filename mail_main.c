/*
mail_main.c
Mail System Simulator
7-15-2016
Neil McGlohon
*/

//includes
#include "mail.h"


// Define LP types
tw_lptype model_lps[] =
{
     {
          (init_f) mailbox_init,
          (pre_run_f) mailbox_prerun,
          (event_f) mailbox_event_handler,
          (revent_f) mailbox_RC_event_handler,
          (commit_f) NULL,
          (final_f) mailbox_final,
          (map_f) mail_map,
          sizeof(mailbox_state)
     },
     {
          (init_f) post_office_init,
          (pre_run_f) post_office_prerun,
          (event_f) post_office_event_handler,
          (revent_f) post_office_RC_event_handler,
          (commit_f) NULL,
          (final_f) post_office_final,
          (map_f) mail_map,
          sizeof(post_office_state)
     },
     { 0 },
};


//Define command line arguments default values
int total_mailboxes= 0;
int total_post_offices = 0;

//add your command line opts
const tw_optdef model_opts[] = {
     TWOPT_GROUP("Mail Model"),
     TWOPT_UINT("mailboxes", total_mailboxes, "Number of mailboxes in simulation"),
     TWOPT_UINT("postoffices", total_post_offices, "Number of post offices in simulation"),
     // TWOPT_UINT("nlp", nlp_per_pe, "number of LPs per processor"),
     // TWOPT_STIME("mean", mean, "exponential distribution mean for timestamps"),
     // TWOPT_STIME("mult", mult, "multiplier for event memory allocation"),
     // TWOPT_STIME("lookahead", lookahead, "lookahead for events"),
     // TWOPT_UINT("start-events", g_phold_start_events, "number of initial messages per LP"),
     // TWOPT_UINT("stagger", stagger, "Set to 1 to stagger event uniformly across 0 to end time."),
     // TWOPT_UINT("memory", optimistic_memory, "additional memory buffers"),
     // TWOPT_CHAR("run", run_id, "user supplied run name"),
     TWOPT_END()
};


void displayModelSettings()
{
     if(g_tw_mynode ==0)
     {
          for (int i = 0; i < 30; i++)
          {
               printf("*");
          }
          printf("\n");
          printf("\t nnodes: %i\n", tw_nnodes());
          printf("\t g_tw_nlp: %llu\n", g_tw_nlp);
          printf("\t custom_LPs_per_pe: %i\n", custom_LPs_per_pe);
          for (int i = 0; i < 30; i++)
          {
               printf("*");
          }
          printf("\n");

     }
}


//for doxygen
#define mail_main main
int mail_main(int argc, char** argv, char **env)
{

     tw_opt_add(model_opts);
     tw_init(&argc, &argv);

     lookahead = 1;
     nlp_per_pe = 1;
     custom_LPs_per_pe = 1;


     g_tw_nlp = (total_mailboxes + total_post_offices);
     g_tw_lookahead = lookahead;
     custom_LPs_per_pe = (g_tw_nlp / g_tw_npe)/tw_nnodes();


     displayModelSettings();

     g_tw_lp_types = model_lps;
     g_tw_lp_typemap = lpTypeMapper;


     tw_define_lps(custom_LPs_per_pe, sizeof(letter));

     tw_lp_setup_types();


     tw_run();
     tw_end();

     return 0;
}
