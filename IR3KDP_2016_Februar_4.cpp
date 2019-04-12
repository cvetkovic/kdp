PARENT(id:integer, num:integer) ::
*[
	ROOM!BringChildren(num);
	ROOM?BringOk(val);
	[ val = true -> go_somewhere;
					...
					ROOM!TakeChildrenHome(num);		 		 
]

////////////////////////////

NANN(id:integer, num:integer) ::
*[
	ROOM!ComeToWork();
	[ val = true -> do_something;
					...
					ROOM!WantToLeave();		
					ROOM?Leave(); 		
					ROOM!Sync(); 
]

////////////////////////////

ROOM ::
	numChildren, numNann, numWaiting : integer all initialized to 0;

	*[
		val:boolean; val = false;
		
		PARENT(i)?BringChildren(num) -> [numChildren + num <= 3 * numNann -> numChildren += num; val = true;] 
										ROOM?BringOk(val);
		[]
		PARENT(i)?TakeChildrenHome(num) -> numChildren -= num;
										   out:integer;
										   out = numNann - (numChildren + 2) / 3;
										   [out > numWaiting -> numWaiting = out;]
										   i:integer; i = 0; // RED CEKANJE IMPLEMENTIRANJE
										   *[i < out -> x:integer; 
														QUEUE?dequeue(x);
														NANN(x)!Leave(); 
														numNann--; 
														NANN(x)?Sync()
											];
		[]
		NANN(i)?ComeToWork() -> numNann++; 
								[numWaiting > 0 -> x:integer; 
														QUEUE?dequeue(x);
														NANN(x)!Leave(); 
														numNann--; 
														NANN(x)?Sync()
											];
		[]
		NANN(i)?WantToLeave() -> [numC <= 3 * (numN - 1) -> x:integer; 
														QUEUE?dequeue(x);
														NANN(x)!Leave(); 
														numNann--; 
														NANN(x)?Sync();
								  []
								  numC > 3 * (numN - 1) -> numWaiting++; QUEUE!enqueue(i);
								 ]
	]

////////////////////////////

QUEUE ::
	front, rear, cnt : integer; front = 0; rear = 0; cnt = 0;
	buffer : integer[N];
	
	*[
		QUEUE?enqueue(t) -> buffer[rear] = t; rear = (rear + 1) % n; cnt++;
		[]
		cnt != 0; QUEUE?dequeue() -> CALLER!buffer[front]; front = (front + 1) % n;
		[]
		else -> wait;
	]