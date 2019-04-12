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

struct Parameter
{
	int caller;
	Operation operation;
}

MessageBox monitor;
MessageBox response[N];

// serverski proces ima strukturu
while (1)
{
	Message<Parameter> param;
	
	mbx_get(monitor, param, INF, status);
	
	if (param.operation == Operation.ACQUIRE)
	{
		if (free > 0)
		{
			free--;
			mbx_put(response[param.caller], msg);
		}
		else
			queue.enqueue(id);
	}
	else if (param.operation == Operation.RELEASE)
	{
		if (queue.empty())
			free++;
		else
			mbx_put(response[queue.dequeue()], msg);
	}
}

// klijentski proces
void client_op1(int id)
{
	Message<Parameter> param;
	param.caller = id;
	
	mbx_put(monitor, param);
	mbx_get(response[id], msg, INF, status);
}