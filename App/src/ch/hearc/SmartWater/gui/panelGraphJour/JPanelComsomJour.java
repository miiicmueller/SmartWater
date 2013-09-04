package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.BorderLayout;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JPanel;
import javax.swing.JSplitPane;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonth;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonthParam;

public class JPanelComsomJour extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelComsomJour(ResourceBundle resourceLang,
			Map<String, String> parameters, Session session) {
		this.resourceLang = resourceLang;
		this.parameters = parameters;
		this.session = session;
		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/


	public JPanelChartJourPanParam getJPanelChartJourPanParam() {
		return this.jPanelChartJourPanParam;
	}

	public void readConsom() {
		this.jPanelChartJourPanParam.readConso();
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

		this.jPanelChartJourPanGraph = new JPanelChartJourPanGraph(resourceLang,this);
		this.jPanelChartJourPanParam = new JPanelChartJourPanParam(
				resourceLang, this.parameters, this.jPanelChartJourPanGraph,
				this.session);

		this.jSplitTabChart = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);

		jSplitTabChart.add(jPanelChartJourPanGraph, JSplitPane.LEFT);
		jSplitTabChart.add(jPanelChartJourPanParam, JSplitPane.RIGHT);

		jSplitTabChart.setDividerLocation(500);

		this.add(jSplitTabChart, BorderLayout.CENTER);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ResourceBundle resourceLang;
	private Map<String, String> parameters;
	private Session session;

	// Panel de contrôle
	private JPanelChartJourPanParam jPanelChartJourPanParam;
	private JPanelChartJourPanGraph jPanelChartJourPanGraph;

	// Séparation
	private JSplitPane jSplitTabChart;

}
