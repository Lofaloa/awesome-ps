#NOM    : Makefile
#CLASSE : ED - LaboED
#OBJET  : Laboratoire E.D Bloc2
#HOWTO	: make; make clean
#AUTEUR	: J.C. Jaumain, 07/2011
#AUTEUR	: MBA, 08/2018

Init:	Affichage
	touch RapportAwesomePs.tex

Affichage: RapportAwesomePs.pdf
	evince -f RapportAwesomePs.pdf&

RapportAwesomePs.pdf: RapportAwesomePs.tex 
	pdflatex RapportAwesomePs.tex
	pdflatex RapportAwesomePs.tex	# 2x pour la T.O.C.
	rm -f *.aux *.dvi *.ps *.log *.toc *~

clean:
	find . -name *~ -exec rm -f '{}' \;
