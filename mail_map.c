#include "mail.h"



int get_mailbox_GID(tw_lpid lpid)
{
     return lpid;
}

int get_post_office_GID(tw_lpid lpid)
{
     return total_mailboxes + lpid;
}

int get_assigned_post_office_LID(tw_lpid lpid)
{
     return lpid % total_post_offices
}


//Given an LP's GID (global ID)
//return the PE (aka node, MPI Rank)
tw_peid mail_map(tw_lpid gid)
{
     return (tw_peid) gid / g_tw_nlp;
}
