package ch.hearc.SmartWater.gui.panelParamChamps;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ch.hearc.SmartWater.commUsb.ComConnexion;

public class JPanelControleParam extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelControleParam(ResourceBundle resourceLang,
			JPanelParametresChamps JPanelParametresChamps) {

		this.resourceLang = resourceLang;
		this.JPanelParametresChamps = JPanelParametresChamps;

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
		this.buttonSave.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				JPanelControleParam.this.JPanelParametresChamps
						.saveParameters();
			}
		});

		this.buttonRead.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JPanelControleParam.this.JPanelParametresChamps
						.readParameters();
			}
		});

		this.chBtnAll.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				JPanelControleParam.this.JPanelParametresChamps
						.controlCheckBox(JPanelControleParam.this.chBtnAll
								.isSelected());

			}
		});

	}
	private void geometrie() {

		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		this.buttonRead = new JButton(
				(String) resourceLang.getObject("buttonRead"));
		this.buttonSave = new JButton(
				(String) resourceLang.getObject("buttonSave"));
		this.chBtnAll = new JButton("All");

		this.add(buttonRead);
		this.add(buttonSave);
		this.add(chBtnAll);

	}

	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	private JPanelParametresChamps JPanelParametresChamps;

	private JButton buttonRead;
	private JButton buttonSave;
	private JButton chBtnAll;

}
