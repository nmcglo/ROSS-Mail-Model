/*
     mail.h
     Mail System Simulator
     7-15-2016
     Neil McGlohon
*/


#ifndef _mail_h
#define _mail_h

#include "ross.h"

#define MEAN_MAILBOX_WAIT 10.0
// #define MEAN_PO_PROCESS_WAIT 45.0

#define LET_PER_MAILBOX 10
#define MAX_LETTERS_IN_SYSTEM 1000 //TODO dynamically changing letter storage sizes

// static int letters_per_mailbox = 10;

// typedef struct mailbox_state mailbox_state;
// typedef struct post_office_state post_office_state;


typedef struct
{
  tw_lpid sender;
  tw_lpid recipient;
} letter;


typedef struct
{
  int num_letters_recvd;
  //TODO consider an inbox so that there could maybe be ad-hoc p2p messaging, interesting model
} state;

// struct post_office_state
// {
//   struct letter po_letter_storage[];
//   int num_letters_processed;
// }

extern unsigned int setting_1;


extern tw_lptype model_lps[];


extern void mailbox_init(state *s, tw_lp *lp);
extern void mailbox_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp);
extern void mailbox_RC_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp);
extern void mailbox_final(state *s, tw_lp *lp);

extern tw_peid mail_map(tw_lpid gid);


// static tw_stime lookahead = 1.0;
// static unsigned int stagger = 0;
// static unsigned int offset_lpid = 0;
// static tw_stime mult = 1.4;
// static int g_phold_start_events = 1;
// static int optimistic_memory = 100;
// static unsigned int ttl_lps = 0;
static unsigned int nlp_per_pe = 1;

// static tw_stime mean = 1.0;

// static char run_id[1024] = "undefined";



// extern void post_office_init(state *s, tw_lp *lp);
// extern void post_office_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
// extern void post_office_RC_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
// extern void post_office_final(state *s, tw_lp *lp);


#endif
