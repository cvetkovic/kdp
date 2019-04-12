channel in(unsigned);
channel out(unsigned);

void filter_process()
{
	unsigned recorded_min;
	unsigned v;
	
	receive in(recorded_min);
	if (recorded_min == EOS)
	{
		send out(EOS);
		return;
	}
	
	receive in(v);
	while (v != EOS)
	{
		if (v > recorded_min)
		{
			send out(v);
			receive in(v);
		}
		else // v <= recorded_min
		{
			send out(recorded_min);
			recorded_min = v;
			receive in(v);
		}
	}
	
	send_out(recorded_min);
	send out(EOS);
}