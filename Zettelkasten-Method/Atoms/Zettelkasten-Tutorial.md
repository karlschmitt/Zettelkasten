---
id: 20260626131504
title: Zettelkasten Tutorial
author: Karl Schmitt
date: 2026-06-26
keywords: [ Zettelkasten, tutorial, git, typescript, deno, Angular ]
---

![Das Zettelkasten-Prinzip zur Wissensvernetzung](../Images/Das_Zettelkasten-Prinzip_zur_Wissensvernetzung.png)

# Zettelkasten-Tutorial – Wissen aufbauen statt nur Notizen sammeln

![Niklas Luhmann](../Images/Niklas_Luhmann.jpg)

Das **Zettelkasten-System** wurde von dem deutschen Soziologen Niklas Luhmann entwickelt. Mit dieser Methode kannst Du Wissen langfristig organisieren, Zusammenhänge erkennen und neue Ideen entwickeln.

![Analog Zettelkasten](../Images/analog-zettelkasten.png)

## 1. Was ist ein Zettelkasten?

Ein Zettelkasten besteht aus vielen kleinen, miteinander verknüpften Notizen ("Zettel").

![Atom](../Images/Atom.png)

[Attomic Notes](./atomic-notes.md) ➡️ Jeder Zettel enthält:

* **genau eine Idee oder einen Gedanken** 💡

* eine **eindeutige Kennung** 🎯

* **Verweise auf andere Zettel** 🔗

* eigene Formulierungen statt bloßer Kopien ✍️

Der Schwerpunkt liegt nicht auf dem Sammeln von Informationen, sondern auf dem **Verknüpfen von Wissen**.

> [!Note]
> Bei der Zettelkasten-Methode kommt das  **Prinzip der Atomarität** zur Anwendung , bei dem jede Notiz ausschließlich **einen einzelnen Gedanken** behandeln sollte.

![Lego Brick](../Images/lego-brick.png)

Durch diese strikte Trennung von Informationen fungieren Notizen als **unkomplizierte Bausteine**, die sich flexibel zu neuen Projekten oder Argumentationsketten zusammenfügen lassen. Das **präzise Verlinkungen** ist nur dann möglich sind, wenn der Fokus einer Notiz scharf definiert ist und keine thematischen Vermischungen vorliegen. Kurze, eigenständige Einheiten senken zudem die **Hemmschwelle beim Schreiben** und verhindern unnötige Wiederholungen innerhalb der Wissensdatenbank. Letztlich ermöglicht dieser Ansatz eine **hohe Wiederverwendbarkeit** von Wissen, da Informationen wie Lego-Steine immer wieder neu kombiniert werden können. Eine Notiz gilt dann als atomar, wenn sie eine **eindeutige Aussage** trifft und auch ohne weiteren Kontext vollkommen verständlich bleibt.

***

## 2. Die drei wichtigsten Notiztypen

### A. Flüchtige Notizen ([Fleeting Notes](./fleeting-nodes.md))

Kurze Gedanken, die spontan entstehen. 💭

![Note-Book](../Images/Note-Book.png)

Das Konzept der **flüchtigen Notizen** innerhalb der Zettelkasten-Methode unterstützt bei der ersten Stufe der Ideenerfassung. Diese Notizen dienen als **temporäre Gedankenstützen**, die dazu gedacht sind, spontane Einfälle ohne Rücksicht auf Struktur oder Grammatik schnell festzuhalten. Da das menschliche Gedächtnis begrenzt ist, fungieren sie als **Zwischenspeicher**, damit der Fokus auf der aktuellen Tätigkeit bleiben kann. Ein entscheidender Aspekt ist ihre **begrenzte Haltbarkeit**, weshalb sie innerhalb weniger Tage gesichtet und entweder gelöscht oder in dauerhafte Wissenselemente umgewandelt werden müssen. Letztlich fungieren diese Skizzen nur als **vorübergehendes Gerüst**, das nach der Integration der Inhalte in das Langzeitarchiv vollständig entfernt wird. Somit wird sichergestellt, dass nur **relevante und ausgearbeitete Informationen** dauerhaft im System verbleiben.


Beispiele:

```text
- Angular Signals könnten RxJS in manchen Fällen ersetzen.
- Interessant: Git Rebase erzeugt lineare Historie.
- Idee für Blogartikel über Deno Deploy.
```

Eigenschaften:

* schnell erfassen

* unstrukturiert ⚠️

* später verarbeiten oder löschen

***

### B. Literatur-Notizen ([Literature Notes](./literature-otes.md)) 🖋️

Notizen beim Lesen eines Buches 📖, Artikels oder Tutorials. 📚

![](../Images\book-stack.png)

**Literatur-Notizen** innerhalb der Zettelkasten-Methode sind das essentielle Bindeglied zwischen externen Inhalten und eigenem Wissen. Im Gegensatz zu flüchtigen Gedanken dienen diese Notizen dazu, die **Kernaussagen fremder Autoren** kurz und prägnant in eigenen Worten zusammenzufassen. Ein effektiver Umgang erfordert dabei zwingend die **Angabe der Originalquelle**, um die wissenschaftliche Integrität zu wahren und den Kontext jederzeit nachvollziehbar zu machen. Der Prozess des aktiven Formulierens schützt den Nutzer vor der sogenannten **Sammler-Täuschung**, bei der bloßes Markieren fälschlicherweise mit echtem Lernen verwechselt wird. Letztlich fungieren diese Aufzeichnungen als **temporärer Zwischenschritt**, aus dem später dauerhafte, voll integrierte Erkenntnisse für das eigene Archiv entstehen. Durch diese **Übersetzung in die eigene Sprache** wird sichergestellt, dass komplexe Informationen für die zukünftige Verwendung sofort verständlich und abrufbar bleiben.


Beispiel:

```text
Quelle:
"Learning Git", Kapitel 5

Kernaussage:
Ein Rebase verschiebt Commits auf eine neue Basis.

Eigene Zusammenfassung:
Rebase schreibt die Historie um.
```

Wichtig:

Nicht ganze Textabschnitte kopieren.

Stattdessen:

> "Wie würde ich das einem Kollegen erklären?"

![conference speaker](../Images/conference-speaker.png)

***

### C. Permanente Notizen ([Permanent Notes](./permanent-notes.md)) 📝

Die **Dauernotizen**, sind das zentrale Fundament der **Zettelkasten-Methode** zur Wissensverwaltung dienen. Im Gegensatz zu flüchtigen Gedanken oder reinen Zusammenfassungen fremder Werke stellen diese Notizen **eigenständige, ausformulierte Ideen** dar, die dauerhaft im System verbleiben. Sie folgen strikten Prinzipien wie der **Atomizität**, bei der jeder Eintrag nur einen Gedanken umfasst, und der **Autonomie**, damit der Inhalt auch Jahre später ohne Originalquelle verständlich bleibt. Ein wesentliches Merkmal ist die **Vernetzung**, da neue Erkenntnisse aktiv mit bestehendem Wissen verknüpft werden müssen, um eine wachsende Gedankenstruktur zu bilden. Der beschriebene Prozess wandelt temporäre Eindrücke in **langfristiges intellektuelles Kapital** um, das bei künftigen Projekten das Schreiben aus dem Nichts ersetzt. Letztlich fungiert diese Sammlung als **kognitiver Partner**, der durch stetige Reflexion und Verknüpfung beim Aufbau einer persönlichen Wissensbasis hilft.

Das Herzstück des Zettelkastens. ❤️

Jede permanente Notiz:

* enthält genau eine Idee 💡

* ist in eigenen Worten geschrieben ✍️

* kann allein verstanden werden 🚀

* verweist auf andere Notizen 🔀

Beispiel:

```text
ID: 202606251030

Titel:
Git Rebase erzeugt eine lineare Historie

Inhalt:
Git Rebase verschiebt Commits auf einen neuen
Ausgangspunkt. Dadurch entsteht eine lineare
Commit-Historie ohne Merge-Commits.

Verknüpfungen:
→ 202606251100 Merge vs Rebase
→ 202606251120 Konfliktauflösung
```

***

## 3. Grundprinzipien

![Conceptual Idea](../Images/conceptual-idea.png)

### Prinzip 1: Eine Idee pro Zettel 💡

❌ Schlecht:

```text
Git, Angular, CSS und Deno
```

✅ Gut:

```text
Eine Notiz über Git Rebase
Eine Notiz über Angular Signals
Eine Notiz über CSS Grid
```

***

### Prinzip 2: In eigenen Worten schreiben ✍️

Nicht:

```text
"Signals are reactive primitives..."
```

Sondern:

```text
Angular Signals speichern Werte und informieren
automatisch alle abhängigen Komponenten über Änderungen.
```

***

### Prinzip 3: Viele Verbindungen erstellen 🔗

Ein Zettel ohne Links ist nur eine isolierte Notiz. 📝

Beispiel:

```text
Git Rebase
    ↕
Merge Strategien
    ↕
Konfliktlösung
    ↕
CI/CD Workflows
```

Je mehr Verbindungen entstehen, desto wertvoller wird der Kasten.

![tressure chest](../Images/tressure-chest.png)
***

## 4. Beispiel eines kleinen Zettelkastens 🗒️

![file cabinet](../Images/file-cabinet.png)

```text
202606251000 Git Merge

Git Merge verbindet zwei Entwicklungszweige
durch einen Merge-Commit.

Links:
→ 202606251010 Rebase
```

```text
202606251010 Git Rebase

Rebase verschiebt Commits und erzeugt
eine lineare Historie.

Links:
→ 202606251000 Merge
→ 202606251020 Konflikte
```

```text
202606251020 Konfliktlösung

Konflikte entstehen, wenn dieselben Dateien
parallel verändert wurden.

Links:
→ 202606251000 Merge
→ 202606251010 Rebase
```

***

## 5. Arbeitsablauf (Workflow) 🚀

### Täglich

### Schritt 1 👣

Etwas lesen:

* Buch 📕

* Artikel

* Tutorial

* Dokumentation

↓

### Schritt 2 👣

Literatur-Notizen erstellen.

↓

### Schritt 3 👣

Die wichtigsten Ideen identifizieren.

↓

### Schritt 4 👣

Für jede Idee eine permanente Notiz anlegen.

↓

### Schritt 5 👣

Verbindungen zu vorhandenen Notizen erstellen.

***

## 6. Digitale Werkzeuge 🔧

![wrench](../Images/wrench.png)

Beliebte Programme:

* [Obsidian](https://obsidian.md/?utm_source=chatgpt.com)

* [Logseq](https://logseq.com/?utm_source=chatgpt.com)

* [Zettlr](https://www.zettlr.com/?utm_source=chatgpt.com) ❤️

* [Joplin](https://joplinapp.org/?utm_source=chatgpt.com)

Für Einsteiger ist **Obsidian** besonders beliebt, da Links zwischen Notizen sehr einfach erstellt werden können.

***

## 7. Beispiel für Softwareentwicklung 👩‍💻

Wenn Du gerade Themen wie **Angular**, **TypeScript**, **Git** und **Deno** lernst, könntest Du Notizen wie diese anlegen:

```text
TypeScript
├── Klassen
├── Interfaces
├── Generics
├── Decorators

Angular
├── Komponenten
├── Dependency Injection
├── Signals
└── RxJS

Git
├── Branches
├── Merge
├── Rebase
└── Konflikte

Deno
├── Berechtigungen
├── Module
├── Testing
└── Deploy
```

Viele Querverbindungen sind möglich:

```text
Angular Dependency Injection
    ↔ TypeScript Decorators

Angular Signals
    ↔ RxJS Observables

Deno Testing
    ↔ CI/CD Pipelines
```

***

## 8. Einfache Regeln für den Anfang 📋

![Wokspace](../Images/workspace.png)

1. Schreibe täglich mindestens einen permanenten Zettel. 📝

2. Verwende eigene Worte. ✍️

3. Eine Idee pro Zettel.💡

4. Erstelle mindestens zwei Links pro Notiz. 🔗

5. Überarbeite und erweitere ältere Notizen regelmäßig. 🗃️

6. Qualität ist wichtiger als Quantität. 💎

Ein Zettelkasten wird mit der Zeit immer wertvoller. Nach einigen Monaten entsteht ein persönliches Wissensnetzwerk, welche Dich beim Lernen, Schreiben und Problemlösen unterstützt.

See also: [Mastering Networked Knowledge](./Mastering_Networked_Knowledge.pdf)
