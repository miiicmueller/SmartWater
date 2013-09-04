package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;

public class JPanelControlChart extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelControlChart(ResourceBundle resourceLang,
			JPanelChartTabMonth jPanelChartTabMonth) {

		this.resourceLang = resourceLang;
		this.jPanelChartTabMonth = jPanelChartTabMonth;
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

		this.buttonGetConsomm.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// Lire les consommations
				JPanelControlChart.this.jPanelChartTabMonth.getConsom();
			}
		});

	}

	private void geometrie() {

		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		this.buttonGetConsomm = new JButton(
				(String) resourceLang.getObject("buttonGetConsomm"));

		this.add(buttonGetConsomm);

	}

	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	private JPanelChartTabMonth jPanelChartTabMonth;

	private JButton buttonGetConsomm;
}
