# Awesome PS
## Utilisation du projet
### Utilisation du guide
Le guide est un script bash qui a pour but de rendre plus facile l'utilisation de ce répertoire. Il permet à l'utilisateur de compiler, de visualiser le rapport et de lancer une démonstration.
```
$ > bash guide.sh
AWESOME PS's guide script

Welcome to our guide, here is the list of available options!

Available options:
   demo            Starts a project demonstration
   report          Opens the project report in PDF reader
   install         Installs the project on the user machine
   help            Prints the list of available options
$ >
```
### Utilisation de AwesomePs
*AwesomePs* permet à l'utilisateur de spécifier une série d'options à l'exécution du programme. Ces paramètres passés en ligne de commande fonctionne en suivant un modèle de clé et de valeur. Vous trouverez ici, une description détaillée de ces options.

#### La clé ```user```
Cette clé permet à l'utilisateur de sélectionner les processus à afficher sur base de l'utilisateur.
```
$ ./awesomeps user=doe
```
#### La clé ```status```
Cette clé permet à l'utilisateur de sélectionner les processus à afficher sur base de leur état.
```
$ ./awesomeps status=running
$ ./awesomeps status=sleeping
$ ./awesomeps status=zombie
```
#### La clé ```topic```
Cette clé permet à l'utilisateur de sélectionner les données à afficher pour les processus sélectionnés.
```
$ ./awesomeps topic=general
$ ./awesomeps topic=runtime
$ ./awesomeps topic=paging
```
#### Exemples d'exécution

## Structure du projet
- **sources** : le dossier contient toutes les sources du programme. 
- **target** : est le dossier qui contient l'exécutable et le rapport au format pdf après la compilation. Il est créé à la compilation du projet.
- **report** : est le dossier qui contient les fichiers LaTeX écrits durant la rédaction de notre rapport de laboratoire.

