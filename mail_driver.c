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
#include <stdio.h>

#include "ross.h"
#include "mail.h"


//--------------Mail box stuff-------------

void mailbox_init (state *s, tw_lp *lp)
{
  int self = lp->gid;

  // init state data
  s->num_letters_recvd = 0;

  int i;
  for(i = 0; i < 1; i++)
  {
    // tw_event *e = tw_event_new(self,tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT),lp);
    tw_event *e = tw_event_new(self,1,lp);
    letter *let = tw_event_data(e);
    let->sender = self;
    let->recipient = self;
    tw_event_send(e);
  }
}


void mailbox_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{
  int self = lp->gid;

  // initialize the bit field
  *(int *) bf = (int) 0;

  s->num_letters_recvd++;

  //schedule a new letter
  // tw_event *e = tw_event_new(self,tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT),lp);
  tw_event *e = tw_event_new(self,1,lp);
  letter *let = tw_event_data(e);
  let->sender = self;
  let->recipient = self;
  tw_event_send(e);
}

void mailbox_RC_event_handler(state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
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
