package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle_de extends ListResourceBundle
	{
		public Object[][] getContents()
			{
				return contents;
			}

		private Object[][] contents =
			{
				{ "menuFichier", new String("Datei") },
				{ "menuAbout", new String("über") },
				{ "menuFichierOpen", new String("öffnen") },
				{ "menuFichierSave", new String("speichern") },
				{ "menuFichierExit", new String("abmelden") },
				{ "menuAboutApropos", new String("uns") },
				{ "menuComm", new String("Verbindung") },
				{ "menuCommSel", new String("Anschluss wählen") },
				{ "menuCommConnect", new String("Verbinden") }, 
				
				{ "paramTel1", new String("Tel. Nummer 1") },
				{ "paramTel2", new String("Tel. Nummer 2") },
				{ "paramMode", new String("Modus") },
				{ "paramInter", new String("Interval") },
				{ "paramDispo", new String("Verfügbarkeit") },
				{ "paramMdpU", new String("Benutzer Passwort") },
				{ "paramMdpA", new String("Administrator Passwort") },
				{ "paramOffsetTemp", new String("Temp. Offset") },
				{ "paramCompt1", new String("Zähler 1") },
				{ "paramCompt2", new String("Zähler 2") },
				{ "paramUnitName", new String("Einheit Name") },
				{ "paramMonthLim", new String("Monatlich Limit") },
				{ "paramMeasureStat", new String("Mess Status") },
				
				// Boutons
				{ "buttonRead", new String("Lesen") },
				{ "buttonSave", new String("Speichern") },};

	}
