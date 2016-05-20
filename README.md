# minishell

Project for Ecole 42 - PARIS.

###EN:  
Minishell's goal is to code a basic shell (Unix command-line interpreter).  
This project is the first of a serie of three projects which goal in the end is to recode a complete shell. The following projects are 21sh, and 42sh.  
  
Functionalities:  
+ A prompt
+ Handling executables stored within PATH variable
+ Error handling without using errno
+ Environment managing (env / setenv / unsetenv / env -u / env -i)
+ Builtins implementation : cd, setenv, unsetenv, env, exit
+ Signals handling (Ctr -C)
+ Splitting commands with ";"
    
###FR:  
Minishell a pour but de nous faire coder un debut de shell (interpreteur de commande Unix).  
Ce projet est le premier d'une serie de trois projets qui nous amenerons a terme a recoder un shell complet. Les projets suivant sont 21sh, puis 42sh.  
  
Fonctionnalites:
+ Affiche d'un prompt
+ Gestion des executables de la variable PATH
+ Gestion des erreurs sans utiliser errno
+ Gestion de l'environnement (env / setenv / unsetenv / env -u / env -i)
+ Implementation manuelle des builtins suivant : cd, setenv, unsetenv, env, exit
+ Gestion des signaux (Ctrl -C)
+ Gestion des droits d’exécution dans le PATH
+ Séparation des commandes avec le ";"
