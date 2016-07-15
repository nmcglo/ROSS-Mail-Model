
#include <stdio.h>

#include "ross.h"
#include "mail.h"


#define MB_LP 1
// #define PO_LP 2

// Define LP types
tw_lptype model_lps[] = {
  {
    MB_LP, sizeof(mailbox_state),
    (init_f) mailbox_init,
    (pre_run_f) NULL,
    (event_f) mailbox_event_handler,
    (revent_f) mailbox_RC_event_handler,
    (final_f) mailbox_final,
    (statecp_f) NULL
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
  {0},
};


//--------------Mail box stuff-------------

void mailbox_init (state *s, tw_lp *lp)
{
  int self = lp->gid;

  // init state data
  s->num_letters_recvd = 0;
  S->num_letters_have = letters_per_mailbox;

  int i;
  for(i = 0; i < letters_per_mailbox i++)
  {
    tw_event *e = tw_event_new(self,tw_rand_exponential(self, MEAN_MAILBOX_WAIT),lp);
    letter *let = tw_event_data(e);
    let->sender = self;
    let->recipient = self;
    tw_event_send(e);
  }
}


void mailbox_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp)
{
  int self = lp->gid;

  // initialize the bit field //TODO what is this for?
  *(int *) bf = (int) 0;

  s->num_letters_recvd++;

  //schedule a new letter
  tw_event *e = tw_event_new(self,tw_rand_exponential(self, MEAN_MAILBOX_WAIT),lp);
  letter *let = tw_event_data(e);
  let->sender = self;
  let->recipient = self;
  tw_event_send(e);
}

void mailbox_RC_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp)
{

}

void mailbox_final(state *s, tw_lp *lp)
{
  int self = lp->gid;
  printf("%d received %d messages\n", self, s->num_letters_recvd);
}

//-------------Post office stuff-------------
//
// void post_office_init (state *s, tw_lp *lp)
// {
//
// }
//
// void post_office_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp)
// {
//
// }
//
// void post_office_RC_event_handler(state *s, tw_bf *bf, message *in_msg, tw_lp *lp)
// {
//
// }
//
// void post_office_final(state *s, tw_lp *lp)
// {
//
// }


int mail_main(int argc, char* argv[]) {







}
