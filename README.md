nl.sp.drupal-regioconferentie
=============================

Nieuwe module voor de inschrijving voor regioconferenties, congressen en soortgelijke bijeenkomsten van de SP.

Deze module bevat:
- een view met alle evenementen (van het type Regioconferentie) waarvoor de ingelogde bezoeker mensen kan inschrijven
  (als er maar een evenement is wordt de bezoeker automatisch geredirect)
- deelnemersoverzichten voor de betreffende evenementen
- formulieren om deelnemers aan- en af te melden voor de betreffende evenementen

Bij een evenement kan in de backend opgegeven worden:
- wat de ratio afgevaardigden/leden voor een evenement is (1 op 50 is standaard, 0 = onbeperkt)
- voor welke regio's de inschrijving voor dit evenement open staat (op dit moment een option group, zou nog de vorm moeten krijgen van een contact reference field met meerdere opties)
- of een afdeling gasten mag opgeven en zo ja, hoe veel per afdeling
- wanneer de inschrijving voor afdelingen sluit

De hiervoor benodigde velden zijn opgenomen in de nl.sp.generic extensie.

Voor de toekomst:
- toegang tot evenement zelf implementeren in eigen access plugin (ipv via views callback en data filter op overzicht)
- en idem voor deelnemers in eigen filter-plugin
- data over afdeling wellicht toch ophalen obv relaties ipv eigen geostelsel-info (al hebben ACLs ook duidelijke voordelen, zoals niet beperkt zijn tot bepaalde relaties/rollen om het formulier te kunnen gebruiken)