package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle_en extends ListResourceBundle
	{
		public Object[][] getContents()
			{
				return contents;
			}

		private Object[][] contents =
			{
				//Menus
				{ "menuFichier", new String("File") },
				{ "menuAbout", new String("About") },
				{ "menuFichierOpen", new String("Open") },
				{ "menuFichierSave", new String("Save") },
				{ "menuFichierExit", new String("Exit") },
				{ "menuAboutApropos", new String("Credits") },
				{ "menuComm", new String("Communication") },
				{ "menuCommSel", new String("Select port") },
				{ "menuCommConnect", new String("Connect") }, 
				
				//Paramètres
				{ "paramTel1", new String("Tel. Number 1") },
				{ "paramTel2", new String("Tel. Number 2") },
				{ "paramMode", new String("Mode") },
				{ "paramInter", new String("Interval") },
				{ "paramDispo", new String("Disponibility") },
				{ "paramMdpU", new String("User Password") },
				{ "paramMdpA", new String("Admin Password") },
				{ "paramOffsetTemp", new String("Temp. Offset") },
				{ "paramCompt1", new String("Counter 1") },
				{ "paramCompt2", new String("Counter 2") },
				{ "paramUnitName", new String("Unit Name") },
				{ "paramMonthLim", new String("Months Limits") },
				{ "paramMeasureStat", new String("Measure Statement") },
				
				// Boutons
				{ "buttonRead", new String("Read") },
				{ "buttonSave", new String("Save") },};
	}
