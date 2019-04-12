enum op
{
	PARENT_COME,
	PARENT_GO,
	NANN_COME,
	NANN_GO
}

union par
{
	int integer;
}

union res
{
	bool boolean;
}

/* GLOBAL */

const int M = ...; // number of parents
const int N = ...; // number of nanns

channel request(int id, op operation, par params);
channel response_parent[M](res result);
channel response_nann[N](res result);

/* COORDINATOR */
Queue<int> wantToLeave;

void releaseNann()
{
	int id = wantToLeave.dequeue();
	res result;
	result.boolean = true;
	numNann--;
	response response_nann[id](result)
}

process Coordinator()
{
	while (1)
	{
		// communication variables
		int id;
		op operation;
		par params;
		
		receive request(id, operation, params);
		
		// variables
		int numNann;
		int numChildren;
		
		// active monitor
		if (op == PARENT_COME)
		{
			int children = params.integer;
			res result;
			result.boolean = false;
			
			if (children > 0 && numChildren + children <= 3 * numNann)
			{
				numChildren += children;
				result.boolean = true;
			}
			
			send response_parent[id](result);
		}
		else if (op == PARENT_GO)
		{
			int children = params.integer;
			res result;
			result.boolean = false;
			
			if (children > 0)
			{
				numChildren -= children;
				
				int canLeave = numNann - (numChildren + 2) / 3;
				if (canLeave > wantToLeave.count())
					canLeave = wantToLeave.count();
				
				for (int i = 0; i < canLeave; i++)
					releaseNann();
				
				result.boolean = true;
			}
			
			send response_parent[id](result);
		}
		else if (op == NANN_COME)
		{
			res result;
			result.boolean = true;
			
			numNann++;
			if (wantToLeave.count() > 0)
				releaseNann();
			
			send response_nann[id](result);
		}
		else if (op == NANN_GO)
		{
			res result;
			result.boolean = true;
			
			if (numChildren <= 3 * (numNann - 1))
			{
				numNann--;
				send response_nann[id](result);
			}
			else
			{
				wantToLeave.enqueue(id);
			}
		}
	}
}

/* USERS */
///////////////////////
/* PARENT PROCEDURES */
bool parent_come(int id, int n)
{
	par p, r;
	p.integer = n;
	
	send request(id, op.PARENT_COME, p);
	receive response_parent[id](r);
	
	return r.logicResult;
}

bool takeChildren(int id, int n)
{
	par p, r;
	p.integer = n;
	
	send request(id, op.PARENT_GO, p);
	receive response_parent[id](r);
	
	return r.logicResult;
}

///////////////////////
/* NANN PROCEDURES */
void comeNann()
{
	send request(id, op.NANN_COME, 0);
	receive response_nann[id]();
}

void goHomeNann(int id)
{
	send request(id, op.NANN_GO, 0);
	receive response_nann[id]();
}