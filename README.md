Bien sûr ! Je vais mettre à jour le README.md en ajoutant les fonctionnalités spécifiques comme les built-ins et Heredoc qui sont souvent implémentées dans un projet de type Minishell. Voici la version mise à jour du fichier README.md :

# Minishell

Minishell est un projet de shell simplifié développé en C, permettant d'exécuter des commandes systèmes, gérer les redirections, les pipes, ainsi que des fonctionnalités avancées comme les **built-ins** et le **Heredoc**.

Ce projet a été réalisé dans le cadre de la formation **42**.

## Fonctionnalités

- Exécution de commandes systèmes
- Gestion des redirections (entrées et sorties)
- Gestion des pipes
- Support de variables d'environnement
- Gestion des erreurs et des signaux
- **Built-ins** (cd, echo, env, exit, etc.)
- **Heredoc** pour les entrées multiples
- Gestion de l'historique des commandes (si implémentée)

## Installation

### Prérequis

Avant d'installer et de lancer **Minishell**, assurez-vous que vous avez les outils suivants installés sur votre système :

- Un compilateur C (ex. : `gcc`)
- Make

### Cloner le projet

Clonez le dépôt Git sur votre machine locale :

```bash
git clone https://github.com/username/minishell.git
cd minishell

Compiler le projet

Utilisez make pour compiler le projet. Cela génère l'exécutable minishell dans le répertoire courant.

make

Lancer le shell

Une fois compilé, lancez le shell en exécutant l'exécutable minishell :

./minishell

Utilisation

Une fois le shell lancé, vous pouvez entrer des commandes comme dans un terminal classique. Exemple :

minishell$ ls

Built-ins

Minishell prend en charge plusieurs built-ins essentiels, permettant de gérer certaines commandes directement dans le shell sans avoir recours à des processus externes. Voici les built-ins disponibles :
cd

Permet de changer le répertoire de travail courant.

minishell$ cd /path/to/directory

echo

Affiche une chaîne de texte à la sortie standard. Supporte les options classiques comme -n pour ne pas ajouter de nouvelle ligne à la fin.

minishell$ echo "Hello, world!"

env

Affiche les variables d'environnement actuelles.

minishell$ env

exit

Permet de quitter le minishell. Vous pouvez aussi spécifier un code de sortie.

minishell$ exit
minishell$ exit 42

Redirections

Le minishell prend en charge les redirections suivantes :

    Redirection de sortie (> ou >>) :

echo "Hello World" > file.txt

Redirection d'entrée (<) :

cat < file.txt

Redirection de sortie avec ajout (>>) :

    echo "New Line" >> file.txt

Pipes

Vous pouvez chaîner des commandes avec des pipes (|) pour rediriger la sortie d'une commande vers l'entrée d'une autre :

minishell$ ls | grep "test"

Heredoc

Le Heredoc permet de passer plusieurs lignes d'entrée à une commande sans avoir à utiliser un fichier. Cela peut être utilisé avec des commandes comme cat, ou pour rediriger plusieurs lignes vers une commande.

Exemple d’utilisation avec cat :

minishell$ cat << EOF
Ceci est un test
Multiple lignes
EOF

Variables d'environnement

Minishell permet également d'utiliser et de manipuler les variables d'environnement, comme $PATH, $HOME, etc. Exemple :

minishell$ echo $HOME

