package ch.hearc.SmartWater.commUsb.dialogSel;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.TreeMap;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JOptionPane;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.dataManager.DataManager;
import ch.hearc.SmartWater.gui.JFrameSmartWater;
import ch.hearc.SmartWater.gui.JPanelPrincipal;
import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.lang.JLanguages;

public class JFramePortSel extends JFrame {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFramePortSel(ResourceBundle resourceBundle,
			ComConnexion comConnexion, JFrameSmartWater jFrameSmartWater,
			Session session) {

		this.comConnexion = comConnexion;
		this.session = session;

		geometrie();
		control();
		apparence();

	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public						*|
	\*------------------------------------------------------------------*/
	public void refreshPortAff() {
		this.jPanelPortSelAff.refresh();
	}
	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void control() {
		setDefaultCloseOperation(HIDE_ON_CLOSE);

		Thread threadOpen = new Thread(new Runnable() {

			@Override
			public void run() {
				do {
					try {
						Thread.sleep(100);
					} catch (InterruptedException e) {
					}
				} while (!JFramePortSel.this.session.isConnected());

			}
		});

		threadOpen.start();
	}
	private void geometrie() {
		this.setLayout(new BorderLayout());

		this.jPanelPortSelAff = new JPanelPortSelAff(resourceLang, this.session);
		this.jPanelPortSelControl = new JPanelPortSelControl(resourceLang,
				this.jPanelPortSelAff, this.session,this);

		this.add(this.jPanelPortSelAff, BorderLayout.CENTER);
		this.add(this.jPanelPortSelControl, BorderLayout.SOUTH);
	}
	private void apparence() {
		setSize(400, 90);
		setTitle("USB Port Selection ");
		setLocation(30, 30);
		setResizable(false);

		// Display the window.
		this.setVisible(false);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ComConnexion comConnexion;
	private Session session;

	// Tools
	private JPanelPortSelControl jPanelPortSelControl;
	private JPanelPortSelAff jPanelPortSelAff;

	private ResourceBundle resourceLang;

}