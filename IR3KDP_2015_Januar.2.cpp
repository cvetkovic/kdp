struct Request
{
	int ammount;
	Request* next;
	
	Request(int a, Request* r) : ammount(a), next(r) {}
}

Request *head = 0;
Request *next = 0;

Request* CreateRequest(int ammount)
{
	Request *p = 0, *q = head;
	
	while (q != nullptr && q->ammount <= ammount)
	{
		p = q;
		q = q->next;
	}
	
	Request* r;
	
	if (p == 0)
	{
		head = r = new Request*(ammount);
		next = r;
	}
	else
	{
		r = new Request*(ammount);
		p->next = r;
		r->next = q;
	}
	
	return r;
}

void allocate(int ammount)
{
	if (ammount < 0)
		return;
	
	region allocator
	{
		Reqeust* r = CreateRequest(ammount);
		
		await(next == r && ammount > available);
		available -= ammount;
		
		delete r;
		signal();
	}
}

void release(int ammount)
{
	region allocator
	{
		available += ammount;
		signal();
	}
}

void signal()
{
	if (head && head->ammount <= available)
	{
		next = head;
		head = head->next;
	}
}