package ch.hearc.SmartWater.gui.panelAdmin;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;
import java.util.Map.Entry;

import javax.swing.Box;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import ch.hearc.SmartWater.gui.login.Session;

public class JPanelAdministrator extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelAdministrator(Map<String, String> parameters,
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
		this.jPanelAdminParam.updateParams();
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

		this.jPanelAdminParam = new JPanelAdminParam(this.parameters,
				this.resourceLang, this.session);
		this.jPanelAdminCtrl = new JPanelAdminControl(this.resourceLang,
				this.jPanelAdminParam);

		this.add(jPanelAdminParam, BorderLayout.CENTER);
		this.add(jPanelAdminCtrl, BorderLayout.SOUTH);

	}

	public void saveParams() {
		this.jPanelAdminParam.saveParameters();
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private Session session;

	// Tools
	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	// Panel de contrôle
	private JPanelAdminControl jPanelAdminCtrl;
	private JPanelAdminParam jPanelAdminParam;

}
