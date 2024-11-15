# **Minishell**
**Minishell** est un projet d'initiation au développement d'un interpréteur de commandes en C. Ce projet vise à reproduire certaines fonctionnalités de base du shell Bash.

## **Sommaire**
- [Description](#description)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Détails Techniques](#détails-techniques)
- [Limites](#limites)
- [Contributeurs](#contributeurs)

---

## **Description**
Minishell est un shell minimaliste développé dans le cadre d'un projet éducatif. Il permet d'exécuter des commandes simples en reproduisant des comportements du shell standard. Ce projet met l'accent sur la gestion des processus, la manipulation de fichiers, et l'interaction utilisateur.

---

## **Fonctionnalités**
- Exécution des commandes simples (par exemple, `ls`, `echo`, `pwd`).
- Gestion des redirections (`>`, `<`, `>>`).
- Gestion des pipes (`|`).
- Gestion des signaux (CTRL-C, CTRL-\).
- Implémentation des built-ins : 
  - `cd`
  - `echo`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`.

---

## **Installation**
1. Clonez le dépôt depuis GitHub :
   ```bash
   git clone https://github.com/votre_nom_utilisateur/minishell.git
   ```
2. Rendez-vous dans le répertoire du projet :
   ```bash
   cd minishell
   ```
3. Compilez le projet :
   ```bash
   make
   ```

---

## **Utilisation**
1. Lancez Minishell :
   ```bash
   ./minishell
   ```
2. Entrez vos commandes comme dans un shell classique.

---

## **Détails Techniques**
- **Langage** : C
- **Fonctions autorisées** : 
  - `readline`, `execve`, `pipe`, `fork`, etc. (voir la liste complète dans le sujet).
- **Norme** : Respect de la norme 42 (Norminette).
- **Limites techniques** :
  - Pas de gestion des jokers (`*`, `?`).
  - Pas de support des fonctionnalités avancées comme les sous-shells ou les opérateurs logiques (`&&`, `||`).

---

## **Limites**
- Ce projet ne gère pas toutes les subtilités d’un shell complet (par exemple, les expansions complexes comme `$((expression))` ou `${}`).
- La gestion des erreurs est limitée à des cas courants.

---
