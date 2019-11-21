#!/bin/bash

################################### PURPOSE ###################################
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
DEMO_SCRIPT="./demonstration/start.sh"
REPORT_FILE="$TARGET_DIRECTORY/report.pdf"
REQUIRED_OPTIONS=1

################################## CONSTANTS ##################################
DEMONSTRATION_OPTION="demo"
REPORT_OPTION="report"
INSTALL_OPTION="install"
HELP_OPTION="help"

############################ FUNCTION DECLARATIONS ############################

function startDemonstration {
    bash $DEMO_SCRIPT
}

function showReport {
    if [ ! -f $REPORT_FILE ]; then
        make
    fi
    evince ./target/report.pdf || echo "Failed to open $REPORT_FILE!"
}

function installAwesomePS {
    if [ -d "$TARGET_DIRECTORY" ]; then
        echo "The project is already built in the ${TARGET_DIRECTORY} directory."
    else
        echo "Building the project in ${TARGET_DIRECTORY}..."
        make
    fi
}

function printOption {
    printf "   %-15s %s\n" "$1" "$2"
}

function showHelp {
    echo "Available options:"
    printOption $DEMONSTRATION_OPTION "Starts a project demonstration"
    printOption $REPORT_OPTION "Opens the project report in PDF reader"
    printOption $INSTALL_OPTION "Installs the project on the user machine"
    printOption $HELP_OPTION "Prints the list of available options"
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
if [ $# -eq 0 ]; then
    printf "AWESOME PS's guide script\n\n"
    printf "Welcome to our guide, here is the list of available options!\n\n"
    showHelp
elif [ $# -eq $REQUIRED_OPTIONS ]; then
    handle_option "$1"
else
    echo "usage: $0 <option> (enter \"$0 help\" to print available options)"
    exit 1
fi