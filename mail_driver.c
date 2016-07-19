/*
     mail_driver.c
     Mail System Simulator
     7-15-2016
     Neil McGlohon
*/


//The C driver file for a ROSS model
//This file includes:
// - an initialization function for each LP type
// - a forward event function for each LP type
// - a reverse event function for each LP type
// - a finalization function for each LP type

//Includes
#include "mail.h"


//--------------Mail box stuff-------------

void mailbox_init (state *s, tw_lp *lp)
{
  int self = lp->gid;

  // init state data
  s->num_letters_recvd = 0;

  int i;
  for(i = 0; i < LET_PER_MAILBOX; i++)
  {
    // tw_event *e = tw_event_new(self,tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT),lp);
    // tw_stime ts = 1;
    tw_stime ts = tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT) + lookahead;
    tw_event *e = tw_event_new(self,ts,lp);
    letter *let = tw_event_data(e);
    let->sender = self;
    let->recipient = self;
    tw_event_send(e);
  }
}


void mailbox_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{
  int self = lp->gid;
  // tw_lpid dest = self;
  tw_lpid dest;

  unsigned int ttl_lps = tw_nnodes() * g_tw_npe * nlp_per_pe;
  dest = tw_rand_integer(lp->rng, 0, ttl_lps - 1);

     if(dest >= (g_tw_nlp * tw_nnodes()))
     {
          printf("Attempted Destination: %llu\n", dest);
          tw_error(TW_LOC, "bad dest");
     }

  // // initialize the bit field
  // *(int *) bf = (int) 0;

  s->num_letters_recvd++;

  //schedule a new letter
  // tw_event *e = tw_event_new(self,tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT),lp);
  // tw_stime ts = 1;
  // tw_stime ts = tw_rand_exponential(lp->rng, mean) + lookahead + (tw_stime)(lp->gid % (unsigned int)g_tw_ts_end);
  tw_stime ts = tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT) + lookahead;
  tw_event *e = tw_event_new(dest,ts,lp);
  letter *let = tw_event_data(e);
  let->sender = self;
  let->recipient = dest;
  tw_event_send(e);
}

void mailbox_RC_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{
     tw_rand_reverse_unif(lp->rng);
}

void mailbox_final(state *s, tw_lp *lp)
{
  int self = lp->gid;
  printf("%d received %d messages\n", self, s->num_letters_recvd);
}

// void mailbox_commit(state * s, tw_bf * bf, letter * m, tw_lp * lp)
// {
// }

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
