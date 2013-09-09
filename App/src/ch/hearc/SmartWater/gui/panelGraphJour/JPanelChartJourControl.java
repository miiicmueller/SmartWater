package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

public class JPanelChartJourControl extends JPanel {

	public JPanelChartJourControl(ResourceBundle resourceLang,
			JPanelComsomJour jPanelComsomJour) {
		this.resourceLang = resourceLang;
		this.jPanelComsomJour = jPanelComsomJour;
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
		this.buttonGetConsomm.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JPanelChartJourControl.this.jPanelComsomJour.readConsom();

			}
		});
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
	private JPanelComsomJour jPanelComsomJour;
	// Tools
	private JButton buttonGetConsomm;

}
