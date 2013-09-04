package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.table.JTableHeader;

public class JPanelChartTabMonthParamControl extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelChartTabMonthParamControl(ResourceBundle resourceLang,
			JPanelChartTabMonthParam jPanelChartTabMonthParam) {

		this.resourceLang = resourceLang;
		this.jPanelChartTabMonthParam = jPanelChartTabMonthParam;

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
		this.buttonWrLimits.setEnabled(true);
	}

	private void controle() {

		this.buttonWrLimits.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				jPanelChartTabMonthParam.sendLimits();
			}
		});

		this.buttonGetConsomm.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				jPanelChartTabMonthParam.readLimits();
			}
		});

	}

	private void geometrie() {

		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		this.buttonWrLimits = new JButton(
				(String) resourceLang.getObject("buttonWrLimits"));
		this.buttonGetConsomm = new JButton(
				(String) resourceLang.getObject("buttonGetConsomm"));

		this.add(buttonWrLimits);
		this.add(buttonGetConsomm);

	}
	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	private JButton buttonWrLimits;
	private JPanelChartTabMonthParam jPanelChartTabMonthParam;
	private JButton buttonGetConsomm;
}
