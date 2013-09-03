package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdminParam;
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdministrator;
import ch.hearc.SmartWater.gui.panelCompteur.JPanelCompteurs;
import ch.hearc.SmartWater.gui.panelDiag.JPanelDiag;
import ch.hearc.SmartWater.gui.panelGraphJour.JPanelChartJourPanParam;
import ch.hearc.SmartWater.gui.panelGraphJour.JPanelComsomJour;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonthParam;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelConsomMois;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelParametres;

public class JPanelPrincipal extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelPrincipal(Map<String, String> parameters,
			ResourceBundle resourceLang, Session session) {

		this.parameters = parameters;
		this.resourceLang = resourceLang;
		this.session = session;

		this.tabPAram = (String) this.resourceLang.getObject("tabPAram");
		this.tabSimu = (String) this.resourceLang.getObject("tabSimu");
		this.tabConsoMois = (String) this.resourceLang
				.getObject("tabConsoMois");
		this.tabConsoJour = (String) this.resourceLang
				.getObject("tabConsoJour");
		this.tabCompt = (String) this.resourceLang.getObject("tabCompt");
		this.tabAdmin = (String) this.resourceLang.getObject("tabAdmin");
		this.tabDiag = (String) this.resourceLang.getObject("tabDiag");

		geometrie();
		controle();
		apparence();
	}
	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public JPanelParametres getJPanelParam() {
		return this.jPanelParametres;
	}

	public JPanelAdministrator getJPanelAdmin() {
		return this.jPanelAdministrator;
	}

	public JPanelChartTabMonthParam getJPanelChartTabMonthParam() {
		return this.jPanelConsomMois.getJPanelChartTabMonthParam();
	}

	public JPanelChartJourPanParam getJPanelChartJourPanParam() {
		return this.jPanelComsomJour.getJPanelChartJourPanParam();
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {
		this.ongletPrincipaux.addChangeListener(new ChangeListener() {

			@Override
			public void stateChanged(ChangeEvent arg0) {
				if (ongletPrincipaux.getTitleAt(
						ongletPrincipaux.getSelectedIndex()).equals(
						JPanelPrincipal.this.tabAdmin)) {

					// Test si on est loggé en admin sur la carte
					if (JPanelPrincipal.this.session.isLogged()
							&& JPanelPrincipal.this.session.getUserName()
									.equals(ADMIN_USERNAME)) {

					} else {
						// JOptionPane jOptionWriteErr = new JOptionPane();
						// jOptionWriteErr.showConfirmDialog(JPanelPrincipal.this,
						// (String) JPanelPrincipal.this.resourceLang
						// .getObject("adminLogErr"),
						// (String) JPanelPrincipal.this.resourceLang
						// .getObject("adminLogErrTit"),
						// JOptionPane.DEFAULT_OPTION,
						// JOptionPane.ERROR_MESSAGE);
						//
						// ongletPrincipaux.setSelectedIndex(0);
					}
				}
			}
		});
	}

	private void geometrie() {
		BorderLayout layout = new BorderLayout();
		layout.setHgap(30);
		layout.setVgap(50);
		this.setLayout(layout);

		this.ongletPrincipaux = new JTabbedPane(SwingConstants.LEFT);

		// Construction des panels
		this.jPanelParametres = new JPanelParametres(this.parameters,
				this.resourceLang, this.session);
		this.jPanelAdministrator = new JPanelAdministrator(parameters,
				resourceLang, session);
		this.jPanelConsomMois = new JPanelConsomMois(resourceLang,
				this.parameters, session);
		this.jPanelComsomJour = new JPanelComsomJour(resourceLang, parameters,
				session);
		this.jPanelCompteurs = new JPanelCompteurs(resourceLang);
		this.jPanelDiag = new JPanelDiag(resourceLang, this.session);

		this.add(ongletPrincipaux, BorderLayout.CENTER);

		// The following line enables to use scrolling tabs.
		ongletPrincipaux.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

		this.ongletPrincipaux.addTab(this.tabPAram, this.jPanelParametres);
		this.ongletPrincipaux.addTab(this.tabSimu, new JButton("Salut"));
		this.ongletPrincipaux.addTab(this.tabConsoMois, this.jPanelConsomMois);
		this.ongletPrincipaux.addTab(this.tabConsoJour, this.jPanelComsomJour);
		this.ongletPrincipaux.addTab(this.tabCompt, this.jPanelCompteurs);
		this.ongletPrincipaux.addTab(this.tabDiag, this.jPanelDiag);
		this.ongletPrincipaux.addTab(this.tabAdmin, this.jPanelAdministrator);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private Session session;
	// Tools
	private JTabbedPane ongletPrincipaux;
	private JPanelParametres jPanelParametres;
	private JPanelConsomMois jPanelConsomMois;
	private JPanelComsomJour jPanelComsomJour;
	private JPanelCompteurs jPanelCompteurs;
	private JPanelDiag jPanelDiag;
	private JPanelAdministrator jPanelAdministrator;

	private Map<String, String> parameters;
	private ResourceBundle resourceLang;

	private String tabPAram;
	private String tabSimu;
	private String tabConsoMois;
	private String tabConsoJour;
	private String tabCompt;
	private String tabAdmin;
	private String tabDiag;

	private final String ADMIN_USERNAME = "A";

}
