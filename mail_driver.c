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

void mailbox_init (mailbox_state *s, tw_lp *lp)
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
          let->final_dest = self;
          tw_event_send(e);
     }
}


void mailbox_event_handler(mailbox_state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{
     int self = lp->gid;
     tw_lpid final_dest;
     tw_lpid next_dest;

     // unsigned int ttl_lps = tw_nnodes() * g_tw_npe * nlp_per_pe;
     // dest = tw_rand_integer(lp->rng, 0, ttl_lps - 1);
     final_dest = tw_rand_integer(lp->rng, 0, total_mailboxes - 1);

     //Next destination from a mailbox is its assigned post office
     tw_lpid assigned_post_office = get_assigned_post_office_LID(lp->id);
     next_dest = get_post_office_GID(assigned_post_office);

     // // initialize the bit field
     // *(int *) bf = (int) 0;

     s->num_letters_recvd++;

     //schedule a new letter
     // tw_event *e = tw_event_new(self,tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT),lp);
     // tw_stime ts = 1;
     // tw_stime ts = tw_rand_exponential(lp->rng, mean) + lookahead + (tw_stime)(lp->gid % (unsigned int)g_tw_ts_end);
     tw_stime ts = tw_rand_exponential(lp->rng, MEAN_MAILBOX_WAIT) + lookahead;
     tw_event *e = tw_event_new(next_dest,ts,lp);
     letter *let = tw_event_data(e);
     let->sender = self;
     let->final_dest = final_dest;
     let->next_dest = next_dest;
     tw_event_send(e);
}

void mailbox_RC_event_handler(mailbox_state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{
     tw_rand_reverse_unif(lp->rng);
}

void mailbox_final(mailbox_state *s, tw_lp *lp)
{
     int self = lp->gid
     printf("%d received %d messages\n", self, s->num_letters_recvd);
}

// void mailbox_commit(state * s, tw_bf * bf, letter * m, tw_lp * lp)
// {
// }

//-------------Post office stuff-------------

void post_office_init (post_office_state *s, tw_lp *lp)
{

}

void post_office_event_handler(post_office_state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{

}

void post_office_RC_event_handler(post_office_state *s, tw_bf *bf, letter *in_msg, tw_lp *lp)
{

}

void post_office_final(post_office_state *s, tw_lp *lp)
{

}
