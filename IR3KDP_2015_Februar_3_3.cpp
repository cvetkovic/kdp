/*

	<turn[i] = ticket; ticket++;>
	<await(turni[i] == current)>;
	
	<current++;>
	
*/

// ticket
process p[i]()
{
	int turn;
	
	in("ticket", ?turn);
	out("ticket", turn + 1);
	
	in("current", turn);
	
	// CRITICAL SECTION
	
	out("current", t + 1);
}

void initialize()
{
	out("ticket", 0);
	out("current", 0);
	
	for (int i = 0; i < n; i++)
		eval(p(i));
}