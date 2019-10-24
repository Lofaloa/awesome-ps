# Notes pour les auteurs
## Sélection des processus
À investiguer.

## Recherche des informations liées à un processeur
### Fichier virtuel /proc/[pid]/stat
#### Description
Le fichier contient les informations liées au statut d'un processus. Si l'on essaye de consulter son contenu via ```cat```, on obtient une suite de données peu lisible.

Pour comprendre le contenu du fichier, les pages de manuel ```man 5 proc``` nous explique que les données y sont rangées dans l'ordre séparées par un espace. Pour extraire ses données, la documentation nous recommande d'utiliser la fonction ```scanf (3)``` de la librairie standard.

#### Le device (tty_nr)
tty_nr est un numéro de device. Sur Linux, il se compose d'un id *major* et d'un id *mineur*. Le majeur représente une classe de device et le minor représente une instance de device.

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

## Affichage et sélection des informations liées à un processeur