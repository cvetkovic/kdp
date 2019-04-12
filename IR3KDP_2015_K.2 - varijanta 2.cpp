void producer()
{
	region cnt[indexW]
	{
		await(cnt[indexW] == N);

		buffer[writeTo] = item;
		cnt[writeTo] = 0;
		writeTo = (writeTo + 1) % n;
		
		indexW++;
	}
}


void consumer()
{
	region cnt[indexR[ID]]
	{
		await(indexR[ID] == indexW);
	}
	
	int item = buffer[readFrom[ID]];
	
	region cnt[readFrom[ID]]
	{
		cnt[readFrom[ID]]++;
	}
	
	readFrom[ID] = (readFrom[ID] + 1) % n;
	indexR[ID]++;
}