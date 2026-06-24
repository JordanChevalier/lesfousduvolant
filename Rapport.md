#  Rapport – Projet amazinggame
Jordan Chevalier
Thomas Albouy

---

## 1. Installation des dépendances et lancement

### 🔧 Dépendances nécessaires
Le projet repose sur un environnement C standard avec :

- GCC (ou Clang)
- Bibliothèques sockets TCP (POSIX / Windows Winsock)
- MinUnit pour les tests unitaires

---

###  Compilation

#### Compiler le client
```bash
gcc -Wall -o client sample_player_client.c strategie.c
```

#### Compiler les tests
```bash
gcc -Wall -o test test.c strategie.c
```

---

###  Exécuter les tests
```bash
./runtest.sh
```

---

###  Lancer le client en local
```bash
./competition.sh
```

---

## 2. Démarche étape par étape

### Étape 1 : Compréhension du protocole serveur
Le serveur envoie les capteurs sous forme d’une ligne unique :

```
time exploration x y orientation speed front right rear left
```

---

### Étape 2 : Parsing des capteurs
La fonction `analyse_sensors()` permet de :

- Lire la ligne reçue
- Convertir les valeurs en float
- Stocker les données dans des variables globales
- Multiplier par 100 pour éviter les problèmes de précision

---

### Étape 3 : Moteur de décision
La fonction principale :

```c
const char *calcul_prochaine_action();
```

Elle permet de :

- Analyser les capteurs
- Appliquer une logique de sécurité
- Choisir une action :
  - ACCELERATE
  - DECELERATE
  - TURN_LEFT
  - TURN_RIGHT

---

### Étape 4 : Séparation réseau / logique

Le projet est structuré en deux parties :

- sample_player_client.c → communication réseau
- strategie.c → intelligence artificielle

---

### Étape 5 : Tests unitaires

Les tests permettent de vérifier :

- Parsing des capteurs
- Initialisation de la stratégie
- Cohérence des variables globales

Exemple :

```c
mu_assert_int_eq(sensor_x, 200);
```

---

## 3. Trois grandes difficultés rencontrées

###  1. Attente infinie / blocage

**Problème :**
Le programme pouvait se bloquer dans la boucle réseau.

**Cause :**
Mauvaise synchronisation send / receive.

**Solution :**
Respect strict du cycle :

```
send → receive → analyse
```

---

###  2. Parsing instable

**Problème :**
Certaines lignes capteurs étaient mal interprétées.

**Cause :**
Format serveur parfois incomplet.

**Solution :**
Vérification de sscanf :

```c
if (n != 10) continue;
```

---

###  3. Couplage logique / réseau

**Problème :**
Difficile de tester l’IA indépendamment.

**Solution :**
Séparation claire :

- stratégie = logique pure
- client = réseau uniquement

---

## 4. Notions apprises / retour d’expérience

###  Architecture logicielle
- séparation des responsabilités
- modularisation du code
- IA indépendante du réseau

###  Réseaux TCP
- sockets client TCP
- gestion des échanges texte
- gestion des erreurs de connexion

###  Tests unitaires
- validation de fonctions isolées
- tests sans serveur
- utilisation de MinUnit

###  IA réactive
- prise de décision basée capteurs
- logique simple d’évitement
- gestion d’état interne

---

##  Conclusion

Ce projet m’a permis de :

- comprendre un client réseau en C
- structurer une IA simple basée sur capteurs
- séparer logique et communication
- mettre en place des tests unitaires
- Cela m’a également permis de comprendre la notion de temps réel entre un client et un serveur, car de nombreux problèmes sont apparus à cause de la synchronisation et des délais de communication.
```