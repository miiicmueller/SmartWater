package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle extends ListResourceBundle {
	public Object[][] getContents() {
		return contents;
	}

	private Object[][] contents = {
			// Menus
			{"menuFichier", new String("File")},
			{"menuAbout", new String("About")},
			{"menuFichierOpen", new String("Open")},
			{"menuFichierSave", new String("Save")},
			{"menuFichierExit", new String("Exit")},
			{"menuAboutApropos", new String("Credits")},
			{"menuComm", new String("Communication")},
			{"menuCommSel", new String("Select port")},
			{"menuCommConnect", new String("Connect")},

			// Paramètres
			{"paramTel1", new String("Tel. Number 1")},
			{"paramTel2", new String("Tel. Number 2")},
			{"paramMode", new String("Mode")},
			{"paramInter", new String("Interval")},
			{"paramDispo", new String("Disponibility")},
			{"paramMdpU", new String("User Password")},
			{"paramMdpA", new String("Admin Password")},
			{"paramOffsetTemp", new String("Temp. Offset")},
			{"paramCompt1", new String("Counter 1")},
			{"paramCompt2", new String("Counter 2")},
			{"paramUnitName", new String("Unit Name")},
			{"paramMonthLim", new String("Months Limits")},
			{"paramMeasureStat", new String("Measure Statement")},

			// Boutons
			{"buttonRead", new String("Read")},
			{"buttonSave", new String("Save")},
			{"buttonGetConsomm", new String("Read")},
			{"buttonWrLimits", new String("Save limits")},

			// Graphiques
			{"graphConsTit", new String("Monthly consumption")},
			{"graphMois", new String("Months")},
			{"graphVol", new String("Volume[m3]")},
			
			{"graphMoisJanv", new String("January")},
			{"graphMoisFev", new String("February")},
			{"graphMoisMar", new String("March")},
			{"graphMoisAvr", new String("April")},
			{"graphMoisMai", new String("May")},
			{"graphMoisJuin", new String("June")},
			{"graphMoisJuil", new String("July")},
			{"graphMoisAou", new String("August")},
			{"graphMoisSept", new String("September")},
			{"graphMoisOct", new String("October")},
			{"graphMoisNov", new String("November")},
			{"graphMoisDec", new String("December")},

			{"consomMois", new String("Monthly consumption")},
			{"limiteMois", new String("Monthly limit")},
			{"consomJourn", new String("Daily consumption")},
			
			//Tableau
			{"tabHeaderMois", new String("Months")},
			{"tabHeaderLimit", new String("Limit")},
			
			
			// Tabs
			{"tabPAram", new String("Parameters")},
			{"tabSimu", new String("Simulation")},
			{"tabConsoMois", new String("Monthly consumption")},
			{"tabConsoJour", new String("Daily consumption")},
			{"tabCompt", new String("Counters")},
			};
}
