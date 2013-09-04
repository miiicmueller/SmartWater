package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.FlowLayout;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

public class JPanelChartJourControl extends JPanel {

	public JPanelChartJourControl(ResourceBundle resourceLang) {
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

		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		this.buttonGetConsomm = new JButton(
				(String) resourceLang.getObject("buttonGetConsomm"));

		this.add(buttonGetConsomm);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ResourceBundle resourceLang;

	// Tools
	private JButton buttonGetConsomm;

}
