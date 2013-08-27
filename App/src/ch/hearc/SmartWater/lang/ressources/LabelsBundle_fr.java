package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle_fr extends ListResourceBundle
	{
		public Object[][] getContents()
			{
				return contents;
			}

		private Object[][] contents =
			{
				//Menus
				{ "menuFichier", new String("Fichier") },
				{ "menuAbout", new String("A Propos") },
				{ "menuFichierOpen", new String("Ouvrir") },
				{ "menuFichierSave", new String("Enregistrer") },
				{ "menuFichierExit", new String("Quitter") },
				{ "menuAboutApropos", new String("cr�dits") },
				{ "menuComm", new String("Communication") },
				{ "menuCommSel", new String("Selection port") },
				{ "menuCommConnect", new String("Connection") },
				{"menuLogin", new String("Identification")},
				{"menuLoginLog", new String("s'identifier")},
				
				//Param�tres
				{ "paramTel1", new String("Num�ro tel. 1") },
				{ "paramTel2", new String("Num�ro tel. 2") },
				{ "paramMode", new String("Mode[0-1]:") },
				{ "paramInter", new String("Intervalle [min] :") },
				{ "paramDispo", new String("Disponibilit�") },
				{ "paramMdpU", new String("Mot de passe utilisateur") },
				{ "paramMdpA", new String("Mot de passe administrateur") },
				{ "paramOffsetTemp", new String("Offset Temp�rature") },
				{ "paramCompt1", new String("Compteur 1") },
				{ "paramCompt2", new String("Compteur 2") },
				{ "paramUnitName", new String("Nom de l'unit�") },
				{ "paramMonthLim", new String("Limites du mois") },
				{ "paramMeasureStat", new String("Etat des mesures") },
				
				// Boutons
				{ "buttonRead", new String("Lire") },
				{ "buttonSave", new String("Sauver") },
				{ "buttonGetConsomm", new String("Read") },
				{"buttonWrLimits", new String("Sauver limites")},

				// Graphiques
				{"graphConsTit", new String("Consommations mensuelle")},
				{"graphMois", new String("Mois")},
				{"graphVol", new String("Volume[m3]")},
				
				{"graphMoisJanv", new String("Janvier")},
				{"graphMoisFev", new String("F�vrier")},
				{"graphMoisMar", new String("Mars")},
				{"graphMoisAvr", new String("Avril")},
				{"graphMoisMai", new String("Mai")},
				{"graphMoisJuin", new String("Juin")},
				{"graphMoisJuil", new String("Juillet")},
				{"graphMoisAou", new String("Ao�t")},
				{"graphMoisSept", new String("Septembre")},
				{"graphMoisOct", new String("Octobre")},
				{"graphMoisNov", new String("Novembre")},
				{"graphMoisDec", new String("D�cembre")},

				{"consomMois", new String("Consommation mensuelle")},
				{"limiteMois", new String("Limites mensuelles")},
				{"consomJourn", new String("Consommation journali�re")},

				//Tableau
				{"tabHeaderMois", new String("Mois")},
				{"tabHeaderLimit", new String("Limites")},
				
				//Tabs
				{"tabPAram", new String("Param�tres")},
				{"tabSimu", new String("Simulation")},
				{"tabConsoMois", new String("Consommation mensuelle")},
				{"tabConsoJour", new String("Consommation journali�re")},
				{"tabCompt", new String("Compteurs")},
				};

	}
