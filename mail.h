#ifndef _mail_h
#define _mail_h

#include <ross.h>

#define MEAN_MAILBOX_WAIT 10.0
// #define MEAN_PO_PROCESS_WAIT 45.0


#define MAX_LETTERS_IN_SYSTEM 1000 //TODO dynamically changing letter storage sizes

static int letters_per_mailbox = 10;

typedef struct letter letter;
typedef struct mailbox_state mailbox_state;
typedef struct post_office_state post_office_state;


struct letter
{
  tw_lpid sender;
  tw_lpid recipient;
}


struct mailbox_state
{
  // struct letter letter_outbox[];
  int num_letters_have;
  int num_letters_recvd;
  //TODO consider an inbox so that there could maybe be ad-hoc p2p messaging, interesting model
}

// struct post_office_state
// {
//   struct letter po_letter_storage[];
//   int num_letters_processed;
// }



extern void mailbox_init(state *s, tw_lp *lp);
extern void mailbox_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void mailbox_RC_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
extern void mailbox_final(state *s, tw_lp *lp);

// extern void post_office_init(state *s, tw_lp *lp);
// extern void post_office_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
// extern void post_office_RC_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp);
// extern void post_office_final(state *s, tw_lp *lp);


#endif
