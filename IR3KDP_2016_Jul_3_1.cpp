/*
Najpre se definisu kanali komunikacije i to jedna za zahteve i vise za odgovore, konrektno koliko ima procesa koji mogu da pozivaju aktivni monitor

Vise kanala za odgovor je potrebno da klijent ne bi mogao da cita odgovore koji nisu za njega namenjeni, vec iskljucivo svoje

posto razlicite operacije zahtevaju razlicite parametre zgodno je da type1 i type2 budu C unije
*/

/* medusobno iskljucenje operacija je zagarantovano jer server radi nad jednom niti, dok se uslovna sinhronizacija realizuje na sledeci nacin:
	- wait ne moze da se blokira na semaforu kao kod obicnih monitora vec sam zahtev mora da se sacuva i na njega se ne odgovara dok za to ne dode vreme (ekv. signal nad obicnim semaforom)
	- kada dode vreme da se nesto ispuni, zahtev se vadi iz skupa po odredenom algoritmu i na njega se tek tada salje odgovor. na ovaj nacin klijent je ostao blokiran cekajuci odgovor, dok je sam server nastavio da radi bez blokiranja
*/

/* sledi spisak ekvivalencija:
MONITOR - AKTIVNI MONITOR
trajne promenljive - lokalne serverske promenljive
void funkcija() - request kanal i enum operacija
poziv procedure - send request(), receive response()
monitor ulaz - receive request()
izlaz procedure - send response();
wait() - sacuvaj zahtev
signal() - izvadi i opsluzi sacuvani zahtev
telo procedure - if/then/else statement na serverskoj strani
*/

enum Operation
{
	ACQUIRE,
	RELEASE
}

channel request(int caller, Operation op, type1 param);
channel response[N](type2 result);

// serverski proces ima strukturu
while (1)
{
	int id;
	Operation op;
	type1 param;
	
	int free = 123;
	
	receive request(id, op, param);
	
	if (op == Operation.ACQUIRE)
	{
		if (free > 0)
		{
			free--;
			send response[id](...);
		}
		else
			queue.enqueue(id);
	}
	else if (op == Operation.RELEASE)
	{
		if (queue.empty())
			free++;
		else
			send response[queue.dequeue()](...);
	}
}

// klijentski proces
void client_op1()
{
	send request(id, Operation.op1, param);
	receive response[id](result);
}