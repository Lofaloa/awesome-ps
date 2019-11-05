# Gestion des options
## Sélection des données à afficher (Alexandre)
Critères de sélection:
- Sélection sur base de l'utilisateur.
- Sélection sur base du terminal courant et utilisateur courant. (option de base)
- Sélection sur base du statut d'un processus.

**Remarque:** travailler sur base de flags passés en paramètre de la fonction process_selector.searchProcesses.

## Sélection des données à afficher
Chaque option permet à l'utilisateur de sélectionner les données à afficher pour les processus sélectionnés.

### Option générale
Ici on afficherait les informations générales d'un process (nom de la commande, exécutable, utilisateur...)

### Option relative aux page faults
À voir.

### Option relative à la gestion des enfants (vie d'un processus)
Par exemple, pour la démonstration, générer des zombie, créer des process et faire appel à notre commande.

Dans le fichier /proc/[pid]/stat
- cutime : Amount of time that this process's waited-for children have been  scheduled in  user  mode,  measured  in clock ticks (divide by sysconf(_SC_CLK_TCK)). (See also times(2).)  This includes guest  time,  cguest_time  (time  spent running a virtual CPU, see below).
- cstime : Amount  of time that this process's waited-for children have been scheduled in kernel mode, measured in clock ticks (divide by sysconf(_SC_CLK_TCK)).
- À voir

### Option relative à la gestion des fichiers
À voir.

### Option relative aux utilisateurs
À voir.

### Option relative à l'ordonencement

# Rédaction du rapport
Le rapport se trouve sur la branche documentation. Pour y ajouter notre travail, créer une nouvelle branche et merge à documentation. On merge le rapport quand il est finit.