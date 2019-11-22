# Awesome PS
## Installation
### Compilation

Pour compiler le projet soit vous pouvez utiliser notre guide. Comme suit.
```
bash guide.sh install
```
Ou vous pouvez directement utiliser le Makefile.
```
# Pour obtenir le rapport et l'exécutable
make

# Pour obtenir l'exécutable
make awesomeps
```

Après la compilation, vous retrouverez l'exécutable et le rapport au format pdf dans le dossier ```target```.

***Note :*** ```make report``` cause une erreur.

### Visualiser le rapport
```
bash guide.sh report
```
## Utilisation du projet
### Utilisation du guide
Le guide est un script bash qui a pour but de rendre plus facile l'utilisation de ce répertoire. Il permet à l'utilisateur de compiler, de visualiser le rapport et de lancer une démonstration.

Il peut être utilisé à la place du Makefile, son avantage est de guidé l'utilisateur. Il gère les cas d'erreur ou informe l'utilisateur en cas de problème.

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

#### Sélection sur base de l'état d'un processus
Ce type de sélection est spécifié par la clé ```state```. Cette clé permet à l'utilisateur de sélectionner les processus à afficher sur base de leur état. Par exemple, s'il l'on afficher les données générales pour les processus en cours d'exécution, on écrira :
```
$ ./awesomeps status=running topic=general
```

#### Sélection d'un sujet
Le choix du sujet se fait en utilisant la clé ```state```. Cette clé permet à l'utilisateur de sélectionner les données à afficher pour les processus sélectionnés. Pour afficher les données relatives à la pagination pour tout les processus, nous aurions l'appel suivant :
```
$ ./awesomeps topic=paging
```


#### Sélection d'un processus sur base d'un pid
Il est possible de sélectionner un processus unique en spécifiant son identifiant. Cela est possible en utilisant la clé ```pid```. Pour sélectionner le processus de pid 237, l'appel se fait comme suit :
```
$ ./awesomeps pid=237
```

***Note :*** il est impératif de spécifier le sujet choisi.

#### Sélection sur base de l'utilisateur
Ce type de sélection est spécifié par la clé ```user```. Elle permet à l'utilisateur de sélectionner les processus à afficher sur base de l'utilisateur. Par exemple, si l'on veut sélectionner les processus appartenant à l'utilisateur "*doe*", nous l'appel se fait de cette manière.
```
$ ./awesomeps user=doe
```

## Structure du projet
- **sources** : le dossier contient toutes les sources du programme.
   - **processes_filter** : contient le code utiliser pour rechercher et filtrer les processus.
   - **procfs_reader** : contient le code utiliser pour lire le contenu du système de ficihers ```/proc```.
   - **user_interaction** : contient le code utiliser pour gérer les entrées et les sorties du programme.
- **target** : est le dossier qui contient l'exécutable et le rapport au format pdf après la compilation. Il est créé à la compilation du projet.
- **report** : est le dossier qui contient les fichiers LaTeX écrits durant la rédaction de notre rapport de laboratoire.

