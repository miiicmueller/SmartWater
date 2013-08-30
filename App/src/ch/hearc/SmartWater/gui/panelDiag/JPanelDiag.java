package ch.hearc.SmartWater.gui.panelDiag;

import java.util.ResourceBundle;

import javax.swing.JPanel;

public class JPanelDiag  extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelDiag(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {
		// Rien
	}

	private void geometrie() {
	
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	
	// Tools
	private ResourceBundle resourceLang;


}
