# Mise en place d'une architecture de communication pour un robot mobile explorateur

## Description du projet

Ce projet a pour objectif de concevoir et simuler une architecture de communication robuste pour un robot mobile explorateur, destiné à évoluer dans des environnements contraints comme les tunnels.  
L'approche repose sur la création d'un réseau mobile ad hoc (MANET) utilisant le protocole de routage OLSR et des technologies modernes de communication sans fil.

---

## Pourquoi ce projet ?

- Répondre aux défis de communication dans des environnements sans infrastructure (tunnels, mines, zones sinistrées).
- Proposer une solution basée sur les réseaux MANET pour garantir une communication stable et fiable entre robots mobiles.
- Exploiter les dernières avancées technologiques pour simuler des scénarios réalistes.

---

## Table des matières

- [Technologies utilisées](#technologies-utilisées)
- [Processus de réalisation](#processus-de-réalisation)
- [Optimisation du script ns-3](#optimisation-du-script-ns-3)
- [Résultats obtenus](#résultats-obtenus)
- [Motivations et contexte](#motivations-et-contexte)
- [Limitations et défis](#limitations-et-défis)
- [Utilisation prévue](#utilisation-prévue)

---

## Technologies utilisées

- **ns-3** : simulateur pour modéliser et analyser les réseaux MANETs.
- **Wireshark + Pcap** : outils de capture et d'analyse des paquets réseau.
- **Wi-Fi (802.11n)** : technologie sans fil à haut débit et meilleure portée, idéale pour les environnements souterrains.

### Modèles de propagation :
- **Friis** (espace libre)
- **LogDistance** (perte de signal avec obstacles)

### Modèle de mobilité :
- **RandomWaypointMobilityModel** pour simuler des déplacements réalistes.

### Protocole de routage :
- **OLSR (Optimized Link State Routing)**, adapté aux réseaux mobiles ad hoc.

---

## Processus de réalisation

1. Étude préalable des architectures de communication en robotique.
2. Choix technologiques :
   - Architecture Ad Hoc (MANET) avec Wi-Fi 802.11n.
   - Protocole de routage OLSR.
3. Implémentation sur ns-3 :
   - Configuration du Wi-Fi, mobilité, propagation et routage.
4. Simulation et tests :
   - Captures réseau via Wireshark.
   - Analyse des performances (débit, latence, pertes de paquets).
5. Analyse critique :
   - Évaluation de la robustesse du réseau selon différents scénarios.

---

## Optimisation du script ns-3

Pour améliorer la simulation et refléter les contraintes réelles des environnements souterrains :

- **Wi-Fi (WIFI_STANDARD_80211n)** :
  - Meilleure portée et débits plus élevés, adaptés aux tunnels avec forte atténuation de signal.

- **Propagation Loss Models** :
  - **Friis** pour l'espace libre.
  - **LogDistance** pour simuler les pertes dans des environnements avec obstacles.

- **RandomWaypointMobilityModel** :
  - Déplacement réaliste des robots dans le tunnel, avec pauses et variations de vitesse.

- **Protocole OLSR** :
  - Découverte rapide et efficace des routes dans un réseau mobile.
  - Réduction de la latence et amélioration de la résilience du réseau face à la mobilité.

---

## Résultats obtenus

- Réseau MANET opérationnel dans un environnement simulé.
- Démonstration de la capacité du Wi-Fi 802.11n à maintenir la communication dans des tunnels.
- Bonne résilience du protocole OLSR malgré une forte mobilité.
- Optimisation des paramètres réseau pour minimiser la perte de paquets et la latence.

---

## Motivations et contexte

Le projet a été inspiré par le besoin croissant de communications robustes pour les robots autonomes en exploration souterraine.  
Dans les contextes où les infrastructures classiques sont absentes ou détruites, un réseau MANET offre une solution souple, adaptable et fiable.

---

## Limitations et défis

### Limitations :
- La mobilité aléatoire ne capture pas toutes les contraintes physiques des tunnels (virages serrés, dénivelés, obstacles imprévus).
- La simulation ne prend pas en compte les interférences multi-chemin complexes.

### Défis :
- Ajustement précis des paramètres de mobilité pour éviter des artefacts de simulation (regroupements non réalistes).
- Gestion de la consommation d'énergie liée à l'émission fréquente de messages OLSR.

---

## Utilisation prévue

- Exploration robotique dans des environnements souterrains (mines, tunnels, grottes).
- Déploiement rapide de réseaux d'urgence en l'absence d'infrastructures de communication.
- Simulations avancées pour l'étude de protocoles de routage dans des environnements dynamiques et contraints.

---
