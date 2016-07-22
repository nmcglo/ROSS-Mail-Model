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
     return lpid % total_post_offices;
}


tw_lpid lpTypeMapper(tw_lpid gid)
{
  id_type local = getLocalFromGID(gid)
}


tw_lpid coreOffset(tw_lpid gid){

	return (getCoreFromGID(gid) * CORE_SIZE);
}


id_type getCoreFromGID(tw_lpid gid){
	return (gid / CORE_SIZE);
}

/**
 * Assumes linear mapping of GIDs.
 *
 */
id_type getLocalFromGID(tw_lpid gid){
	return (gid - coreOffset(gid));

}



//Given an LP's GID (global ID)
//return the PE (aka node, MPI Rank)
tw_peid mail_map(tw_lpid gid)
{
     return (tw_peid) gid / g_tw_nlp;
}
