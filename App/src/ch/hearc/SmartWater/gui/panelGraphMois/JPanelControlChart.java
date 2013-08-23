package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.FlowLayout;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

public class JPanelControlChart extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelControlChart(ResourceBundle resourceLang) {

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

	}

	private void geometrie() {
		
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		this.buttonGetConsomm = new JButton((String)resourceLang.getObject("buttonGetConsomm"));
		
		this.add(buttonGetConsomm);
		

	}

	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	
	private JButton buttonGetConsomm ;
}
