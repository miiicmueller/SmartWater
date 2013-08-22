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
				{ "buttonSave", new String("Sauver") },};

	}