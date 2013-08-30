package ch.hearc.SmartWater.commUsb.dialogSel;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.ComOption;
import ch.hearc.SmartWater.gui.login.Session;

public class JPanelPortSelControl extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelPortSelControl(ResourceBundle resourceLang,
			JPanelPortSelAff jPanelPortSelAff, Session session,
			JFramePortSel jFramePortSel) {
		this.resourceLang = resourceLang;
		this.jPanelPortSelAff = jPanelPortSelAff;
		this.session = session;
		this.jFramePortSel = jFramePortSel;

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
		this.buttonRefresh.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				System.out.println("[JPanelPortSelControl] : Btn Refresh");
				JPanelPortSelControl.this.session.updatePort();
				JPanelPortSelControl.this.jPanelPortSelAff.refresh();
			}
		});

		this.buttonConnect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				String comPort;
				System.out.println("[JPanelPortSelControl] : Btn Open");

				comPort = JPanelPortSelControl.this.jPanelPortSelAff
						.getComboValue();
				// Tester si un port est déja ouvert
				if (JPanelPortSelControl.this.session.isConnected()) {
					// Fermeture du port
					System.out.println("Fermeture du port");
					try {
						JPanelPortSelControl.this.session.disconnect();
						JPanelPortSelControl.this.session.connect(comPort);
						JPanelPortSelControl.this.jFramePortSel
								.setVisible(false);
					} catch (Exception e) {
						e.printStackTrace();
					}

				} else {
					JPanelPortSelControl.this.session.connect(comPort);
					JPanelPortSelControl.this.jFramePortSel
					.setVisible(false);
				}
			}

		});

	}
	private void geometrie() {
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.buttonConnect = new JButton("Open");
		this.buttonRefresh = new JButton("Refresh");

		this.add(buttonConnect);
		this.add(buttonRefresh);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	// Input
	private JPanelPortSelAff jPanelPortSelAff;
	private Session session;
	private JFramePortSel jFramePortSel;
	// Tools
	private ResourceBundle resourceLang;

	private JButton buttonConnect;
	private JButton buttonRefresh;
}
