package ch.hearc.SmartWater.commUsb.dialogSel;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JPanel;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.gui.login.Session;

public class JPanelPortSelAff extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelPortSelAff(ResourceBundle resourceLang, Session session) {
		this.resourceLang = resourceLang;
		
		this.session = session ;

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void refresh() {
		List<String> listPort ;
		listPort = this.session.updatePort();
		this.jComboPorts.removeAllItems();
		for (String port : listPort) {
			this.jComboPorts.addItem(port);
		}
	}

	public String getComboValue() {
		return (String) this.jComboPorts.getSelectedItem();
	}
	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {
		this.jComboPorts.setEditable(false);
	}

	private void controle() {

		this.jComboPorts.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {

			}
		});

	}

	private void geometrie() {
		this.setLayout(new BorderLayout());
		this.jComboPorts = new JComboBox<String>();

		this.jComboPorts.setMinimumSize(new Dimension(400, 50));
		this.add(jComboPorts, BorderLayout.CENTER);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/
	// Input
	private Session session;
	// Tools
	private ResourceBundle resourceLang;
	private JComboBox<String> jComboPorts;

}
