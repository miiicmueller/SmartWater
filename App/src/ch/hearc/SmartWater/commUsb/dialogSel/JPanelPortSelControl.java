package ch.hearc.SmartWater.commUsb.dialogSel;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.ComOption;

public class JPanelPortSelControl extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelPortSelControl(ResourceBundle resourceLang,
			JFramePortSel jFramePortSel, ComConnexion comConnexion) {
		this.resourceLang = resourceLang;
		this.jFramePortSel = jFramePortSel;
		this.comConnexion = comConnexion;

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
				JPanelPortSelControl.this.jFramePortSel.updatePort();
			}
		});

		this.buttonConnect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// Tester si un port est déja ouvert
				if (JPanelPortSelControl.this.jFramePortSel.isConnected()) {
					// Fermeture du port
					System.out.println("Fermeture du port");
					try {
						JPanelPortSelControl.this.comConnexion.disconnect();
						connectPort();
					} catch (Exception e) {
						e.printStackTrace();
					}

				} else {
					connectPort();
				}
			}

			private void connectPort() {
				String comPort;
				ComOption comOpt = new ComOption();
				comPort = JPanelPortSelControl.this.jFramePortSel
						.getSelectedPort();
				if (comPort != null) {
					System.out.println("ComPort :" + comPort);
					try {
						JPanelPortSelControl.this.comConnexion
								.setPortName(comPort);
						JPanelPortSelControl.this.comConnexion
								.setComOption(comOpt);

						JPanelPortSelControl.this.comConnexion.connect();
						JPanelPortSelControl.this.jFramePortSel
								.setConnected(true);
					} catch (Exception e) {
						JPanelPortSelControl.this.jFramePortSel
								.setConnected(false);
					}
				} else {

				}
			}
		});

	}
	private void geometrie() {
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.buttonConnect = new JButton("Connect");
		this.buttonRefresh = new JButton("Refresh");

		this.add(buttonConnect);
		this.add(buttonRefresh);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	// Input
	private JFramePortSel jFramePortSel;
	private ComConnexion comConnexion;

	// Tools
	private ResourceBundle resourceLang;

	private JButton buttonConnect;
	private JButton buttonRefresh;
}
