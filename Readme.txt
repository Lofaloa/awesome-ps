
Affichage commande PS de base :

Affiche les process dont l'euid correspond à l'euid de l'utilisateur ainsi que le même terminal que le terminal appelant (TTY)

PID 		TTY 		TIME		CMD

ID = Id du process 			| Trouvable dans /proc/"pid"/stat/pid	
TTY = Terminal qui a exécuté		| Trouvable dans /proc/"pid"/stat/tty_nr
TIME = Temps noyau accordé au process	| Trouvable dans /proc/"pid"/stat/stime
CMD = Commande qui a lancé le process	| Trouvable dans /proc/"pid"/stat/comm



Objectifs: 

- refaire ps 
- coder les options de ps
	Trouver des infos dans /proc/"pid"/stat
	
- ps plus clair/userfriendly




