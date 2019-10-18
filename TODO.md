# Fonctionnalités

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

Fonctionnalités
- système de sélection de processes: on veut avoir la possibilité de sélectionner une série de pi
d sur base de critères donnés:
        - euid (effective user id)
        - tty (terminal d'invocation)
        - voire autres...
        
- sélection des informations
        - stats 
        - informations sur les fichiers
        - mémoires partagées
        - autres
        
- formatter les donner (moins important)

Parses le fichier status pour retrouver UID: https://stackoverflow.com/questions/18079449/is-there-a-system-call-for-obtaining-the-uid-gid-of-a-running-process
Lister les pids: https://github.com/leo-arch/xps/blob/master/xps.c

Avoir le nombre max de pid : cat /proc/sys/kernel/pid_max