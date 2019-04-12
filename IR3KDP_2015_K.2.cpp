// shared
	int cnt[N]; // for signalling
	int write = 0; // write at
	int readAt[N];
	int freeSpace;
	int numberOfReadsPerItem[N];

// producer
while (true)
{
	region fs
		await(freeSpace != 0);
			
	buffer[write] = item();
	write = (write + 1) % n;
	
	for(int i = 0; i < K; i++)
		cnt[i]++;
}

// consumer[i]
while (true)
{
	region cnt[i]
	{
		await(cnt[i] != 0);
		
		item = buffer[readAt[i]];
		
		region read
		{
			numberOfReadsPerItem[readAt[i]]++;
			if (numberOfReadsPerItem[readAt[i]] == N)
			{
				numberOfReadsPerItem[readAt[i]] = 0;
				region fs
					freeSpace++;
			}
		}
		
		cnt[i]--;
		readAt[i] = (readAt[i] + 1) % n;
	}

	consume(item);
}