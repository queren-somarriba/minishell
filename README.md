# Minishell

## Introduction

Minishell est un projet de shell simplifié développé en C, permettant d'exécuter des commandes systèmes, gérer les redirections, les pipes, ainsi que des fonctionnalités avancées comme les built-ins et le Heredoc.

## Fonctionnalités

- Exécution de commandes systèmes
- Gestion des redirections (`<`, `>`, `<<` et `>>`)
- Gestion des pipes
- Support de variables d'environnement
- Gestion des erreurs et des signaux
- Built-ins (`cd`, `echo`, `env`, `exit`, , `export`, `pwd`, `unset`)

## Installation

### Cloner le projet

Clonez le dépôt Git sur votre machine locale :

```sh
git clone https://github.com/votre-repo/minishell.git
cd minishell
```

### Compiler le projet

Utilisez `make` pour compiler le projet. Cela génère l'exécutable `minishell` dans le répertoire courant.

```sh
make
```

### Lancer le shell

Une fois compilé, lancez le shell en exécutant l'exécutable `minishell` :

```sh
./minishell
```

## Utilisation

Une fois le shell lancé, vous pouvez entrer des commandes comme dans un terminal classique. Exemple :

```sh
minishell-$ ls
```

### Built-ins

Minishell prend en charge plusieurs built-ins essentiels permettant de gérer certaines commandes directement sans passer par des processus externes.

#### `cd`

Permet de changer le répertoire de travail courant.

```sh
minishell$ cd /path/to/directory
```

#### `echo`

Affiche une chaîne de texte à la sortie standard. Supporte `-n` pour ne pas ajouter de nouvelle ligne à la fin.

```sh
minishell$ echo "Hello, world!"
```

#### `env`

Affiche les variables d'environnement actuelles.

```sh
minishell$ env
```

#### `exit`

Permet de quitter le minishell. Vous pouvez aussi spécifier un code de sortie.

```sh
minishell$ exit
minishell$ exit 42
```

## Redirections

Le Minishell prend en charge les redirections suivantes :

### Redirection de sortie (`>` ou `>>`)

```sh
echo "Hello World" > file.txt
```

Ajout au fichier existant :

```sh
echo "New Line" >> file.txt
```

### Redirection d'entrée (`<`)

```sh
cat < file.txt
```

## Pipes

Vous pouvez chaîner des commandes avec des pipes (`|`) pour rediriger la sortie d'une commande vers l'entrée d'une autre :

```sh
minishell$ ls | grep "test"
```

## Heredoc

Le Heredoc permet de passer plusieurs lignes d'entrée à une commande sans avoir à utiliser un fichier.

Exemple d’utilisation avec `cat` :

```sh
minishell$ cat << EOF
Ceci est un test
Multiples lignes
EOF
```

## Variables d'environnement

Minishell permet d'utiliser et de manipuler les variables d'environnement, comme `$PATH`, `$HOME`, etc.

```sh
minishell$ echo $HOME
```

