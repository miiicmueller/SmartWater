package ch.hearc.SmartWater.gui.panelCompteur;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class JPanelCompteurs extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelCompteurs(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

		// Initialisation de deux données des compteurs
		this.aManufacturer = new String[2];
		this.aFluide = new String[2];
		this.aVersNum = new String[2];
		this.aSerialNum = new String[2];
		this.aFabDate = new String[2];
		this.aNominalSize = new String[2];

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
		this.btnRead.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// TODO Auto-generated method stub

			}
		});
	}

	private void geometrie() {

		this.setLayout(new BorderLayout());

		JPanel jPanelCmptrs = new JPanel(new GridLayout(1, 2));
		JPanel jPanelCmptrsCtrl = new JPanel(new FlowLayout(FlowLayout.CENTER));

		this.cmpt1 = new JTextArea();
		this.cmpt2 = new JTextArea();
		this.btnRead = new JButton("Read");

		jPanelCmptrs.add(this.cmpt1);
		jPanelCmptrs.add(this.cmpt2);

		jPanelCmptrsCtrl.add(btnRead);

		this.add(jPanelCmptrs, BorderLayout.CENTER);
		this.add(jPanelCmptrsCtrl, BorderLayout.SOUTH);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;

	private JTextArea cmpt1;
	private JTextArea cmpt2;
	private JButton btnRead;

	private String[] aManufacturer;
	private String[] aFluide;
	private String[] aVersNum;
	private String[] aSerialNum;
	private String[] aFabDate;
	private String[] aNominalSize;

}
