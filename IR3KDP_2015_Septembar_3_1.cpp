const int N = ...;

channel ch[N](int min, int max);

void initiator()
{
	const int myval = ...;
	int min, max;
	
	send ch[1](myval, myval);
	
	receive ch[0](min, max);
	send ch[1](min, max);
}

void other_nodes(int i)
{
	const int myval = ...;
	int min, max;
	
	receive ch[i](min, max);
	if (myval < min)
		min = myval;
	else if (myval > max)
		max = myval;
	send ch[(i + 1) % n](min, max);
	
	receive ch[i](min, max);
	if (i < n - 1)
		send ch[(i + 1) % n](min, max);
}