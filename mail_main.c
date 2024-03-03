/*
mail_main.c
Mail System Simulator
7-15-2016
Neil McGlohon
*/

//includes
#include "mail.h"


// Define LP types for Mailbox and Post Office
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

//Command line opts
const tw_optdef model_opts[] = {
     TWOPT_GROUP("Mail Model"),
     TWOPT_UINT("mailboxes", total_mailboxes, "Number of mailboxes in simulation"),
     TWOPT_UINT("postoffices", total_post_offices, "Number of post offices in simulation"),
     TWOPT_END()
};


//Displays simple settings of the simulation
void displayModelSettings()
{
     if(g_tw_mynode ==0)
     {
          for (int i = 0; i < 30; i++)
          {
               printf("*");
          }
          printf("\n");
          printf("Mail Model Configuration:\n");
          printf("\t nnodes: %i\n", tw_nnodes());
          printf("\t g_tw_nlp: %llu\n", g_tw_nlp);
          printf("\t custom_LPs_per_pe: %i\n\n", custom_LPs_per_pe);

          printf("\t total_mailboxes: %i\n", total_mailboxes);
          printf("\t total_post_offices: %i\n\n", total_post_offices);

          printf("\tGID:\n");
          for(int i = 0; i < total_mailboxes; i++)
          {
               tw_lpid assigned_post_office = get_assigned_post_office_LID(i);

               printf("\t%i:   Mailbox assigned to PO %llu\n",i,assigned_post_office);
          }

          for(int i = 0; i < total_post_offices; i++)
          {
               int gid = i + total_mailboxes;
               printf("\t%i:   Post Office %i\n",gid,i);
          }



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

     nlp_per_pe = 1;
     custom_LPs_per_pe = 1;


     g_tw_nlp = (total_mailboxes + total_post_offices);
     g_tw_lookahead = 1;
     custom_LPs_per_pe = (g_tw_nlp)/tw_nnodes();


     displayModelSettings();

     g_tw_lp_types = model_lps;
     g_tw_lp_typemap = lpTypeMapper;

     tw_define_lps(custom_LPs_per_pe, sizeof(letter));

     tw_lp_setup_types();


     tw_run();
     tw_end();

     return 0;
}
