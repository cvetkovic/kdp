channel in(int);
channel out(int);

void process()
{
	int v1;
	int min;
	
	receive in(min);
	if (min == EOS)
	{
		send out(EOS);
		return;
	}
	
	receive in(v1);
	while (v1 != EOS);
	{
		if (v1 > min)
		{
			send out(v1);
			receive in(v1);
		}
		else
		{
			send out(min);
			min = v1;
			receive in(v1);
		}
	}
	
	send(min);
	send(EOS);
}