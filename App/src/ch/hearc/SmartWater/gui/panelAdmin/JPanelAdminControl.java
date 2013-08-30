package ch.hearc.SmartWater.gui.panelAdmin;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JPanel;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelControleParam;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelParametresChamps;

public class JPanelAdminControl extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelAdminControl(ResourceBundle resourceLang,
			JPanelAdminParam jPanelAdminParam) {

		this.resourceLang = resourceLang;
		this.jPanelAdminParam = jPanelAdminParam;

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
				JPanelAdminControl.this.jPanelAdminParam
						.saveParameters();
			}
		});

		this.buttonRead.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				JPanelAdminControl.this.jPanelAdminParam
						.readParameters();
			}
		});

		this.chBtnAll.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				JPanelAdminControl.this.jPanelAdminParam
						.controlCheckBox(JPanelAdminControl.this.chBtnAll
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
	private JPanelAdminParam jPanelAdminParam;

	private JButton buttonRead;
	private JButton buttonSave;
	private JButton chBtnAll;

}
