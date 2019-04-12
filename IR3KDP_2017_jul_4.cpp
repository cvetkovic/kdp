
START::
[
	*[
		USER(i)?delete(val) -> current, previous:integer;
							   previous = 0;
							   break:boolean; break = false;
							   HEAD?getHead(current); // pretrazivanje liste na vrednost val
							   *[break=true or current != 0 -> 
											  Node(current)!getVred();
											  vred:integer;
											  Node(current)?vred;		// vrednost tekuceg element liste
											  [ vred != val -> previous = current;
															   Node(current)!getSled();
															   Node(current)?current;	// current = current->next
											   []
											    vred = val -> [previous = 0 -> // head = head->next
																			   next:integer;
																			   Node(current)!getSled();
																			   Node(current)?next;
																			   HEAD!setHead(next);
																			   // dealokacija prostora
																			   free_current:integer;
																			   FREE!getHead()
																			   FREE?free_current;
																			   Node(current)!setSled(free_current);
																			   FREE!setHead(current);
															  []
															   previous != 0-> // prespajanje pokazivaca prethodnog elementa
																			   next:integer;
																			   Node(current)!getSled();
																			   Node(current)?next;
																			   Node(previous)!setSled(next);
																			   // dealokacija prostora
																			   free_current, free_current_next:integer;
																			   FREE!getHead()
																			   FREE?free_current;
																			   HEAD(free_current)!getSled();
																			   HEAD(free_current)?free_current_next
																			   Node(current)!setSled(free_current_next);
																			   FREE!setHead(current);
															   ];
															   break = true;
											  ]
											  next:integer;
											  Node(current)!getSled();
											  Node(current)?next;
											  current = next;
								]
	]
]

FREE:
[
	free_head:integer;
	*[
		START?setHead(i) -> free_head = i;
		[]
		START?getHead() -> START!free_head;
	]
]

HEAD::
[
	head:integer;
	*[
		START?getHead() -> START!head;
		[]
		START!setHead(h) -> head = h;
	]
]

(i=1..N)NODE(i)::
[
	vred:integer;
	sled:integer;
	
	*[
		START?getVred() -> START!vred;
		[]
		START?getSled() -> START!sled;
		[]
		START?setVred(v) -> vred = v;
		[]
		START?setSled(v) -> sled = v;
	]
]