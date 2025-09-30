# Informatik 3

Begleitprojekt für Informatik 3 im Kurs tfe24-2 an der DHBW Ravensburg Campus Friedrichshafen

**WICHTIG** Bitte verwenden sie zur Entwicklung die vorgefertigten Umgebungen.

## Prepared Environments

[![Open in GitHub Codespaces](https://github.com/codespaces/badge.svg)](https://codespaces.new/graugans/tfe24-2?quickstart=1)

## Synchronisation des eignen Forks

Es wird davon ausgegangen, dass Sie einen [Fork](https://docs.github.com/de/pull-requests/collaborating-with-pull-requests/working-with-forks/fork-a-repo) angelegt haben und von diesen geklont haben. Damit entspricht Ihr Fork der Bezeichnung ``origin``.

Um die aktuellen Änderungen in die lokale Kopie des ``tfe24-2`` Repository zu übertragen sollten Sie zunächst ein ``git fetch`` durchführen.

**WICHTIG** Allgemeine Hinweise zu Forks finden sie in der [GitLab Doku](https://docs.github.com/de/pull-requests/collaborating-with-pull-requests/working-with-forks/about-forks)

```sh
git fetch upstream
```

Nun checken wir die lokale Kopie des zu synchronisierenden Branches aus, in unserem Fall der ``main`` Branch. Dieser Schritt kann entfallen falls wir bereits schon auf dem ``main`` Branch sind. Das können Sie mit ``git branch -a`` prüfen.

```sh
git checkout main
```

## Stellen Sie Ihren Fork auf privat

**WICHTIG** Bitte stellen Sie Ihren Fork auf privat damit die Kommilitonen nicht bei Ihnen die Lösungen kopieren können.

Damit Sie sie die Aufgaben später abgeben können fügen Sie mich bitte zu Ihrem Repository hinzu. Der Benutzername lautet: `graugans`

## Übungsaufgaben

- [Übungsaufgabe Nr. 1](exercise-001/README.md)

## Abgabe der Übungsaufgaben

Die Übungsaufgaben können jeweils in Gruppen bis zu 3 Personen durchgeführt werden. Die Übungsaufgaben sind als [Pull-Request](https://docs.github.com/de/pull-requests/collaborating-with-pull-requests/proposing-changes-to-your-work-with-pull-requests/creating-a-pull-request) abzugeben. Als Reviewer fügen Sie bitte meinen Benutzernamen hinzu: `graugans`.

Neben dem Code erstellen Sie bitte zusätzlich eine kleine Dokumentation in Markdown.

## Hilfreiche Links

- [Markdown Cheat Sheet](https://guides.github.com/pdfs/markdown-cheatsheet-online.pdf)
- [Git Cheat Sheet](https://about.gitlab.com/images/press/git-cheat-sheet.pdf)
