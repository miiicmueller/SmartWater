package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.util.Map;
import java.util.Map.Entry;
import java.util.ResourceBundle;
import java.util.Set;

import javax.swing.Box;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class JPanelParametres extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelParametres(Map<String, String> parameters,
			ResourceBundle resourceLang) {
		this.parameters = parameters;
		this.resourceLang = resourceLang;

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void updateParams() {
		this.jPanelParametresChamps.updateParams();
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {
		// Rien
	}

	private void geometrie() {
		BorderLayout bl = new BorderLayout();
		this.setLayout(bl);

		this.jPanelControleParam = new JPanelControleParam(this.resourceLang);
		this.jPanelParametresChamps = new JPanelParametresChamps(
				this.parameters, this.resourceLang);
		
		this.add(jPanelParametresChamps, BorderLayout.CENTER);
		this.add(jPanelControleParam, BorderLayout.SOUTH);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	// Panel de contrôle
	private JPanelControleParam jPanelControleParam;
	private JPanelParametresChamps jPanelParametresChamps;

}
