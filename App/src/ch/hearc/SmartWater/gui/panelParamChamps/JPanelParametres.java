package ch.hearc.SmartWater.gui.panelParamChamps;

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

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.gui.login.Session;

public class JPanelParametres extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelParametres(Map<String, String> parameters,
			ResourceBundle resourceLang, Session session) {
		this.parameters = parameters;
		this.resourceLang = resourceLang;
		this.session = session;

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
	public void saveToFile() {
		this.jPanelParametresChamps.saveToFile();
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

		this.jPanelParametresChamps = new JPanelParametresChamps(
				this.parameters, this.resourceLang, this.session);
		this.jPanelControleParam = new JPanelControleParam(this.resourceLang,
				this.jPanelParametresChamps);

		this.add(jPanelParametresChamps, BorderLayout.CENTER);
		this.add(jPanelControleParam, BorderLayout.SOUTH);

	}

	public void saveParams() {
		this.jPanelParametresChamps.saveParameters();
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private Session session;

	// Tools
	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	// Panel de contrôle
	private JPanelControleParam jPanelControleParam;
	private JPanelParametresChamps jPanelParametresChamps;

}
