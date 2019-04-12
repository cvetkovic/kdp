channel in1(int);
channel in2(int);
channel in3(int);
channel out(int);

void sorting_network()
{
	int v1, v2, v3;
	
	receive in1(v1);
	receive in2(v2);
	receive in3(v3);
	
	while (v1 != EOS && v2 != EOS && v3 != EOS)
	{
		if (v1 < v2 && v1 < v3)
		{
			send out(v1);
			receive in1(v1);
		}
		else if (v1 > v2 && v2 < v3)
		{
			send out(v2);
			receive in1(v2);
		}
		else
		{
			send out(v3);
			receive in1(v3);
		}
	}
	
	if (v1 == EOS)
	{
		while (v2 != EOS && v3 != EOS)
		{
			if (v2 < v3)
			{
				send out(v2);
				receive in1(v2);
			}
			else
			{
				send out(v3);
				receive in1(v3);
			}
		}
		
		if (v2 == EOS)
		{
			while (v3 != EOS)
			{
				send out(v3);
				receive in1(v3);
			}
		}
		else if (v3 == EOS)
		{
			while (v2 != EOS)
			{
				send out(v2);
				receive in1(v2);
			}
		}
	}
	else if (v2 == EOS)
	{
		while (v1 != EOS && v3 != EOS)
		{
			if (v1 < v3)
			{
				send out(v1);
				receive in1(v1);
			}
			else
			{
				send out(v3);
				receive in1(v3);
			}
		}
		
		if (v1 == EOS)
		{
			while (v3 != EOS)
			{
				send out(v3);
				receive in1(v3);
			}
		}
		else if (v3 == EOS)
		{
			while (v1 != EOS)
			{
				send out(v1);
				receive in1(v1);
			}
		}
	}
	else if (v3 == EOS)
	{
		while (v1 != EOS && v2 != EOS)
		{
			if (v1 < v2)
			{
				send out(v1);
				receive in1(v1);
			}
			else
			{
				send out(v2);
				receive in1(v2);
			}
		}
		
		if (v1 == EOS)
		{
			while (v2 != EOS)
			{
				send out(v2);
				receive in1(v2);
			}
		}
		else if (v2 == EOS)
		{
			while (v1 != EOS)
			{
				send out(v1);
				receive in1(v1);
			}
		}
	}
	
	send out(EOS);
}

// filterska mreža za najbrže sortiranje 11 elemenata
/*
    1     2     3          4     5     6          7     8     9
	|     |     |	       |     |     |          |     |     |
|-------------------|  |-------------------|  |-------------------|
|					|  |				   |  |	                  |
|-------------------|  |-------------------|  |-------------------|
          |                      |                      |
		  |                      |                      |
		  |------------------|   |   |------------------|
		                     |   |   |
					   |-------------------|
					   |                   |
   					   |-------------------|
								 |
								 |----------------|   10  11
												  |   |   |
										          |   |   |
					                        |-------------------|
											|					|
											|-------------------|
*/