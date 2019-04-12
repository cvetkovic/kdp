
// fine-grained atomic action   = action that is implemented directly by the hardware on which a concurrent program executes
// coarse-grained atomic action = sequence of fine-grained AA that appears to be indivisible

// coarse grain ticket algorithm using C-Linda and process coordinator

void process(int i)
{
	int myturn, next;
	
	// request ticket
	in("ticket_request", ?myturn);
	out("ticket_request", myturn + 1);
	
	// waiting for my turn
	in("permit", myturn);
	
	// CRITICAL SECTION
	
	// signal finished and permit next
	out("finished", myturn);
}

void coordinator()
{
	while (1)
	{	
		in("next_to_execute", ?ex);
		out("next_to_execute", ex + 1);
		out("permit", ex);
		
		in("finished", ex);
	}	
}

void init()
{
	out("next_to_execute", 0);
	out("ticket_request", 0);
	out("next", 0);
	
	eval(coordinator());
	for (int i = 0; i < n; i++)
		eval(process(i));
}