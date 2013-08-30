package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.BorderLayout;
import java.util.ResourceBundle;

import javax.swing.JPanel;

public class JPanelComsomJour extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelComsomJour(ResourceBundle resourceLang) {
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

		this.setLayout(new BorderLayout());

		this.jPanelChartJour = new JPanelChartJour(resourceLang);
		this.jPanelChartJourControl = new JPanelChartJourControl(resourceLang);

		this.add(this.jPanelChartJour, BorderLayout.CENTER);
		this.add(this.jPanelChartJourControl, BorderLayout.SOUTH);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ResourceBundle resourceLang;

	// Tools
	private JPanelChartJour jPanelChartJour;
	private JPanelChartJourControl jPanelChartJourControl;

}
