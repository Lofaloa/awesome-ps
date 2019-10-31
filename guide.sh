#!/bin/bash

################################## OBJECTIFS ##################################
# Ce fichier a pour but de gérer la première interaction avec l'utilisateur. On
# pourrait imaginer:
#   - Accepter des paramètres en ligne de commande. Exemples:
#       - "--demo" : pour démarrer une démonstration du projet.
#       - "--report" : pour afficher le rapport au format pdf.
#       - "--install" : pour installer la commande sur la machine de
#         l'utilisateur : (compilation, export de PATH)
#       - "--help" : pour afficher la liste de ces commandes
#
###############################################################################

################################ CONFIGURATION ################################
TARGET_DIRECTORY="./target"

REQUIRED_OPTIONS=1

# Available options for the user
DEMONSTRATION_OPTION="demo"
REPORT_OPTION="report"
INSTALL_OPTION="install"
HELP_OPTION="help"

############################ FUNCTION DECLARATIONS ############################
function startDemonstration {
    echo "[INFO] call to startDemonstration"
}

function showReport {
    echo "[INFO] call to showReport"
}

function installAwesomePS {
    echo "[INFO] call to installAwesomePS"
}

function showHelp {
    echo "[INFO] call to showHelp"
}

function handle_option {
    if [ $# -eq $REQUIRED_OPTIONS ]; then
        case $1 in
            $DEMONSTRATION_OPTION) startDemonstration ;;
            $REPORT_OPTION) showReport ;;
            $INSTALL_OPTION) installAwesomePS ;;
            $HELP_OPTION) showHelp ;;
            *) echo "\"$1\" is an unkown option, please get help." ;;
        esac
    else
        echo "handle_option: invalid number of arguments"
        exit 1
    fi
}

################################# ENTRY POINT #################################
if [ $# -eq $REQUIRED_OPTIONS ]; then
    handle_option "$1"
else
    echo "usage: $0 <option> (enter \"$0 help\" to print available options)"
    exit 1
fi


# if [ -d "$TARGET_DIRECTORY" ]; then
#     echo "The project is already built in the ${TARGET_DIRECTORY} directory."
# else
#     echo "Building the project in ${TARGET_DIRECTORY}."
#     make
# fi