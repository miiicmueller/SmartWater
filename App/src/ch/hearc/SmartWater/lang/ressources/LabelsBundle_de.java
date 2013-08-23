package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle_de extends ListResourceBundle {
	public Object[][] getContents() {
		return contents;
	}

	private Object[][] contents = {
			{"menuFichier", new String("Datei")},
			{"menuAbout", new String("Über")},
			{"menuFichierOpen", new String("Öffnen")},
			{"menuFichierSave", new String("Speichern")},
			{"menuFichierExit", new String("Abmelden")},
			{"menuAboutApropos", new String("Credits")},
			{"menuComm", new String("Verbindung")},
			{"menuCommSel", new String("Anschluss wählen")},
			{"menuCommConnect", new String("Verbinden")},
			{"menuLogin", new String("Login")},
			{"menuLoginLog", new String("einloggen")},

			{"paramTel1", new String("Tel. Nummer 1")},
			{"paramTel2", new String("Tel. Nummer 2")},
			{"paramMode", new String("Modus")},
			{"paramInter", new String("Interval")},
			{"paramDispo", new String("Verfügbarkeit")},
			{"paramMdpU", new String("Benutzer Passwort")},
			{"paramMdpA", new String("Administrator Passwort")},
			{"paramOffsetTemp", new String("Temp. Offset")},
			{"paramCompt1", new String("Zähler 1")},
			{"paramCompt2", new String("Zähler 2")},
			{"paramUnitName", new String("Einheit Name")},
			{"paramMonthLim", new String("Monatlich Limit")},
			{"paramMeasureStat", new String("Mess Status")},

			// Boutons
			{"buttonRead", new String("Lesen")},
			{"buttonSave", new String("Speichern")},
			{"buttonGetConsomm", new String("Lesen")},
			{"buttonWrLimits", new String("Limite speichern")},

			// Graphiques
			{"graphConsTit", new String("Monatlichen Verbrauch")},
			{"graphMois", new String("Monaten")},
			{"graphVol", new String("Volume[m3]")},

			{"graphMoisJanv", new String("Januar")},
			{"graphMoisFev", new String("Februar")},
			{"graphMoisMar", new String("März")},
			{"graphMoisAvr", new String("April")},
			{"graphMoisMai", new String("Mai")},
			{"graphMoisJuin", new String("Juni")},
			{"graphMoisJuil", new String("Juli")},
			{"graphMoisAou", new String("August")},
			{"graphMoisSept", new String("September")},
			{"graphMoisOct", new String("October")},
			{"graphMoisNov", new String("November")},
			{"graphMoisDec", new String("Dezember")},

			{"consomMois", new String("Monatlichen Verbrauch")},
			{"limiteMois", new String("Monatliche Grenzen")},
			{"consomJourn", new String("Tagesverbrauch")},
			

			//Tableau
			{"tabHeaderMois", new String("Monaten")},
			{"tabHeaderLimit", new String("Limite")},

			// Tabs
			{"tabPAram", new String("Einstellung")},
			{"tabSimu", new String("Simulation")},
			{"tabConsoMois", new String("Monatlichen Verbrauch")},
			{"tabConsoJour", new String("Tagesverbrauch")},
			{"tabCompt", new String("Zähler")},

	};

}
