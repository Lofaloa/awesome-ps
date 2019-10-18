# Notes pour les auteurs
## Sélection des processus
À investiguer.

## Recherche des informations liées à un processeur
### Fichier virtuel /proc/[pid]/stat
#### Description
Le fichier contient les informations liées au statut d'un processus. Si l'on essaye de consulter son contenu via ```cat```, on obtient une suite de données peu lisible.

Pour comprendre le contenu du fichier, les pages de manuel ```man 5 proc``` nous explique que les données y sont rangées dans l'ordre séparées par un espace. Pour extraire ses données, la documentation nous recommande d'utiliser la fonction ```scanf (3)``` de la librairie standard.

#### Données à extraire
- ```comm```: est le nom du fichier exécutable. Il est entouré de parenthèses.
- ```state```: il inqique l'état du processus courant. Il est décrit par un caractère.


## Affichage et sélection des informations liées à un processeur