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
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelCompteur.JPanelCompteurs;
import ch.hearc.SmartWater.gui.panelDiag.JPanelDiag;
import ch.hearc.SmartWater.gui.panelGraphJour.JPanelComsomJour;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelConsomMois;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelParametres;

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

	public void saveToFile() {
		this.jPanelAdminParam.saveToFile();
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

		this.ongletAdmin = new JTabbedPane(SwingConstants.BOTTOM);

		this.add(this.ongletAdmin, BorderLayout.CENTER);

		// The following line enables to use scrolling tabs.
		this.ongletAdmin.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

		this.jPanelAdminParam = new JPanelAdminParam(this.parameters,
				this.resourceLang, this.session);
		this.jPanelAdminCtrl = new JPanelAdminControl(this.resourceLang,
				this.jPanelAdminParam);
		this.jPanelAdminState = new JPanelAdminState(parameters, resourceLang,
				session);

		JPanel jPanelAdminParamPlusCtrl = new JPanel(new BorderLayout());
		jPanelAdminParamPlusCtrl.add(jPanelAdminParam, BorderLayout.CENTER);
		jPanelAdminParamPlusCtrl.add(jPanelAdminCtrl, BorderLayout.SOUTH);

		this.ongletAdmin.addTab("Paramètres", jPanelAdminParamPlusCtrl);
		this.ongletAdmin.addTab("Etats Carte", this.jPanelAdminState);

	}
	public void saveParams() {
		this.jPanelAdminParam.saveParameters();
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private Session session;
	private Map<String, String> parameters;
	private ResourceBundle resourceLang;

	// Tools
	private JTabbedPane ongletAdmin;

	// Panel de contrôle
	private JPanelAdminControl jPanelAdminCtrl;
	private JPanelAdminParam jPanelAdminParam;
	private JPanelAdminState jPanelAdminState;

}
