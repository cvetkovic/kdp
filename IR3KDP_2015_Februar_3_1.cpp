
// fine-grained atomic action   = action that is implemented directly by the hardware on which a concurrent program executes
// coarse-grained atomic action = sequence of fine-grained AA that appears to be indivisible

// coarse grain ticket algorithm using C-Linda

void process(int i)
{
	int myturn, next;
	
	// request ticket
	in("ticket_request", ?myturn);
	out("ticket_request", myturn + 1);
	
	// waiting for my turn
	do
	{
		rd("next", ?next);
	} while (next != myturn);
	
	// CRITICAL SECTION
	
	// signal finished and permit next
	in("next", ?next);
	out("next", next + 1);
}

void init()
{
	out("ticket_request", 0);
	out("next", 0);
	
	for (int i = 0; i < n; i++)
		eval(process(i));
}