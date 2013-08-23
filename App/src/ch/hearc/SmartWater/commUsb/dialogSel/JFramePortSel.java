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

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.dataManager.DataManager;
import ch.hearc.SmartWater.gui.JFrameSmartWater;
import ch.hearc.SmartWater.gui.JPanelPrincipal;
import ch.hearc.SmartWater.lang.JLanguages;

public class JFramePortSel extends JFrame {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFramePortSel(ResourceBundle resourceBundle,
			ComConnexion comConnexion) {

		listPort = new ArrayList<String>();
		this.comConnexion = comConnexion;
		this.isConnected = false;

		geometrie();
		control();
		apparence();

	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public						*|
	\*------------------------------------------------------------------*/

	public void updatePort() {
		// On vide la liste
		listPort.clear();
		listPort = ComConnexion.findAllSerialPort();
		this.jPanelPortSelAff.refresh(listPort);
	}

	public String getSelectedPort() {
		return this.jPanelPortSelAff.getComboValue();
	}

	public boolean isConnected() {
		return this.isConnected;
	}
	
	public void setConnected(boolean aState) {
		this.isConnected = aState;
		if(aState)
		{
			this.setVisible(false);
		}
	}
	
	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void control() {
		setDefaultCloseOperation(HIDE_ON_CLOSE);

	}
	private void geometrie() {
		this.setLayout(new BorderLayout());

		this.jPanelPortSelControl = new JPanelPortSelControl(resourceLang,
				this, comConnexion);
		this.jPanelPortSelAff = new JPanelPortSelAff(resourceLang);

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

	// Tools
	private JPanelPortSelControl jPanelPortSelControl;
	private JPanelPortSelAff jPanelPortSelAff;

	private ResourceBundle resourceLang;
	private boolean isConnected;
	private List<String> listPort;

}