package ch.hearc.SmartWater.lang.ressources;

import java.util.ListResourceBundle;

public class LabelsBundle extends ListResourceBundle {
	public Object[][] getContents() {
		return contents;
	}

	private Object[][] contents = {

			// Texte Erreur
			{"notLogged", new String("Veuillez-vous logger !")},
			{"notLoggedTit", new String("Not logged")},
			{"conSucc", new String("Connecté avec succès!")},
			{"conSuccTit", new String("Connecté")},
			{"decSucc", new String("Déconneté avec succès!")},
			{"decSuccTit", new String("Déconnecté")},
			{"decFail", new String("Erreur déconnexion!")},
			{"decFailTit", new String("Erreur")},
			{"timeOut",
					new String("Vérifiez la connexion à la carte ou le port !")},
			{"timeOutTit", new String("Timeout")},
			{"unkErr", new String("Erreur inconnue !")},
			{"unkErrTit", new String("Erreur")},
			{"userPassErr",
					new String("Nom d'utilisateur ou mot de passe incorrect !")},
			{"userPassErrTit", new String("Erreur d'authentification")},
			{"noPortSel", new String("Aucun port selectionné !")},
			{"noPortSelTit", new String("Port COM")},
			{"exitFrame", new String("Voulez-vous quitter l'application ?")},
			{"exitFrameTit", new String("Confirmation")},
			{"writeErr", new String("Erreur d'écriture !")},
			{"writeErrTit", new String("Erreur fatale")},
			{"adminLogErr", new String("Veuillez-vous logger en adminstrateur!")},
			{"adminLogErrTit", new String("Droit administrateur requis")},
			
			{"formatError", new String("Le champs ne contient pas un donnée valide ! Ex.: ")},
			{"formatErrorTit", new String("Erreur de format")},
			
			
			

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
			{"menuLogin", new String("Login")},
			{"menuLoginLog", new String("Connect")},

			// Paramètres
			{"paramTelCarte", new String("Station Tel. Number")},
			{"paramTelAlarm", new String("Alarm Tel. Number 1")},
			// {"paramTelAlarm2", new String("Alarm Tel. Number 1")},
			{"paramPinNum", new String("Pin Number")},
			{"paramMode", new String("Mode")},
			// {"paramInter", new String("Interval")},
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

			{"graphConsTitJour", new String("Daily consumption")},
			{"graphJour", new String("Days")},

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

			// Tableau
			{"tabHeaderMois", new String("Months")},
			{"tabHeaderLimit", new String("Limit")},

			// Tabs
			{"tabPAram", new String("Parameters")},
			{"tabSimu", new String("Simulation")},
			{"tabConsoMois", new String("Monthly consumption")},
			{"tabConsoJour", new String("Daily consumption")},
			{"tabCompt", new String("Counters")},
			{"tabAdmin", new String("Administration")},
			{"tabDiag", new String("State")},
					
	};
}
