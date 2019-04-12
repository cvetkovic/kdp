/*wait(goingEast);
id (direction == WEST)
{
	wait(change);
	direction = EAST;
}
vine++;
signal(goingEast);

cross();

wait(goingEast);
vine--;
if (vine == 0)
	signal(change);
signal(goingEast);*/

messagebox mbox_west, mbox_east, mbox_dir, mbox_vine, mbox_dir_wait;
message msg = blankMessage();

void eastboundMonkey()
{
	message dir, vine;
	
	mbx_get(mbox_east, msg, INF, status);
	mbx_get(mbox_dir, dir, INF, status);
	mbx_put(mbox_dir, dir);
	if (dir.content == WEST)
	{
		mbx_get(mbox_dir_wait, msg, INF status);
		
		mbx_get(mbox_dir, dir, INF, status);
		dir.content = EAST;
		mbx_put(mbox_dir, dir);
	}

	mbx_get(mbox_vine, vine, INF, status);
	vine.content++;
	mbx_put(mbox_vine, vine);
	
	mbx_put(mbox_east, msg);
	
	///////////////
	ride();
	///////////////
	
	mbx_get(mbox_east, msg, INF, status);
	mbx_get(mbox_vine, vine, INF, status);
	vine.content--;
	mbx_put(mbox_vine, vine);
	if (vine.content == 0)
		mbx_put(mbox_dir_wait, msg);
	
	mbx_put(mbox_east, msg);
}

// analogno ide za zapadne majmune