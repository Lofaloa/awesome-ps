
Affichage commande PS de base :

Affiche les process dont l'euid correspond � l'euid de l'utilisateur ainsi que le m�me terminal que le terminal appelant (TTY)

PID 		TTY 		TIME		CMD

ID = Id du process 			| Trouvable dans /proc/"pid"/stat/pid	
TTY = Terminal qui a ex�cut�		| Trouvable dans /proc/"pid"/stat/tty_nr
TIME = Temps noyau accord� au process	| Trouvable dans /proc/"pid"/stat/stime
CMD = Commande qui a lanc� le process	| Trouvable dans /proc/"pid"/stat/comm



Objectifs: 

- refaire ps 
- coder les options de ps
	Trouver des infos dans /proc/"pid"/stat
	
- ps plus clair/userfriendly




