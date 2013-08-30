package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.BorderLayout;
import java.util.ResourceBundle;

import javax.swing.JPanel;
import javax.swing.JSplitPane;

import org.jfree.data.category.CategoryDataset;

import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonth;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonthParam;

public class JPanelChartJourPanGraph extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelChartJourPanGraph(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void updateGraph(int[] dayConsom) {
		this.jPanelChartJour.updateGraph(dayConsom);
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {
		// Rien
	}

	private void geometrie() {
		this.setLayout(new BorderLayout());

		this.jPanelChartJour = new JPanelChartJour(resourceLang);
		this.jPanelChartJourControl = new JPanelChartJourControl(resourceLang);

		this.add(this.jPanelChartJour, BorderLayout.CENTER);
		this.add(this.jPanelChartJourControl, BorderLayout.SOUTH);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ResourceBundle resourceLang;

	// Tools
	private JPanelChartJour jPanelChartJour;
	private JPanelChartJourControl jPanelChartJourControl;

}
