package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class JPanelPrincipal extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelPrincipal(Map<String, String> parameters,
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

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public JPanelParametres getJPanelParam() {
		return this.jPanelParametres;
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
						"Paramètres")) {

					System.out.println("Tab paramètre selectionné");
				}
			}
		});
	}

	private void geometrie() {
		BorderLayout layout = new BorderLayout();
		layout.setHgap(30);
		layout.setVgap(50);
		this.setLayout(layout);

		// Construction des panels
		this.jPanelParametres = new JPanelParametres(this.parameters,
				this.resourceLang);

		this.ongletPrincipaux = new JTabbedPane(SwingConstants.LEFT);

		this.add(ongletPrincipaux, BorderLayout.CENTER);

		// The following line enables to use scrolling tabs.
		ongletPrincipaux.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);

		this.ongletPrincipaux.addTab("Paramètres", jPanelParametres);
		this.ongletPrincipaux.addTab("Simulation", new JButton("Salut"));
		this.ongletPrincipaux.addTab("Consommation", new JButton("Hello"));

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private JTabbedPane ongletPrincipaux;
	private JPanelParametres jPanelParametres;
	private Map<String, String> parameters;
	private ResourceBundle resourceLang;
}
