# Notes pour les auteurs
## (1) Sélection des processus
À investiguer.

## (2) Recherche des informations liées à un process
Cette section contient toutes les notes relatives à la recherche d'informations dans le système de fichiers vituels ```/proc```.

### Fichier virtuel /proc/[pid]/stat
#### Description
Le fichier contient les informations liées au statut d'un processus. Si l'on essaye de consulter son contenu via ```cat```, on obtient une suite de données peu lisible.

Pour comprendre le contenu du fichier, les pages de manuel ```man 5 proc``` nous explique que les données y sont rangées dans l'ordre séparées par un espace. Pour extraire ses données, la documentation nous recommande d'utiliser la fonction ```scanf (3)``` de la librairie standard.

#### Le device (tty_nr)
tty_nr est un numéro de device. Sur Linux, il se compose d'un id *major* et d'un id *mineur* (voir man major). Le majeur représente une classe de device et le minor représente une instance de device.

Il faudrant indiquer aux utilisateurs de quel type de devices est l'instance du terminal courant. Tout comme le ps de base. Dans le manuel (man 5 proc) on peur lire...
```
/proc/devices
Text listing of major numbers and device groups.  This can be used by MAKEDEV scripts for consistency with the kernel.
```
On peut donc sûrement récupérer des informations sur les devices sur base de l'id récupérer.

*Différence entre tty et pts*
- *Pseudo terminal slave (pts) :* voir ```man pts```
- *Teletype (tty)*

*Remarque :* on obtient le nom du terminal par la commande tty (voir man tty)
man pts nous en dit plus sur la notion de pseudo terminal

On remarque que sur une installation avec une interface graphique, les différentes instances de terminals sont des pts. Or, sur la VM d'environnement SYSG5, les terminaux sont des tty.

#### Les temps d'exécution
- ```starttime``` : le temps passé avant le début de l'exécution depuis le boot
- ```utime``` : le temps passé en mode utilisateur (clock ticks)
- ```stime``` : le temps passé en mode kernel, scheduled, d'où le s (clock ticks)
- **Relatifs aux enfants du process**
    - ```cutime``` : le temps passé en mode utilisateur par l'enfant (clock ticks)
    - ```cstime``` : le temps passé en mode utilisateur par l'enfant (clock ticks)

[How do I get the total CPU usage of an application from /proc/pid/stat?](https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat)

**User mode vs Kernel mode**\
Explication trouvée [ici](https://blog.codinghorror.com/understanding-user-and-kernel-mode/).
- In Kernel mode, the executing code has complete and unrestricted access to the underlying hardware. It can execute any CPU instruction and reference any memory address. Kernel mode is generally reserved for the lowest-level, most trusted functions of the operating system. Crashes in kernel mode are catastrophic; they will halt the entire PC.

- In User mode, the executing code has no ability to directly access hardware or reference memory. Code running in user mode must delegate to system APIs to access hardware or memory. Due to the protection afforded by this sort of isolation, crashes in user mode are always recoverable. Most of the code running on your computer will execute in user mode.


#### Fichier virtuel /proc/[pid]/status
### Description
Fichier contenant un condensé lisible des informations contenues dans les fichiers /proc/[pid]/stat et /proc/[pid]/statm

#### L'user et group id 
Id de l'user ayant lancé la commande du process. Trouvable avec UID dans status l'id de son groupe est à GID  ==> ```le nom de l'user peut être trouvé dans /etc/passwd```


#### Fichier virtuel /proc/[pid]/exe
### Description
Fichier contenant le lien symbolique du fichier du process. Ce lien symbolique peut être déférencé uniquement via la fonction ```readlink(2)```

### Fonction readlink(2)
Fonction dont la signature est : ``` ssize_t readlink(const char *pathname, char *buf, size_t bufsiz); ```

Place le contenu du lien symbolique ```pathname``` dans ```buf``` qui a une taille de ```bufsiz```


## (3) Affichage et sélection des informations liées à un processeur