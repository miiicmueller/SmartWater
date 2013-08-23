package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.util.ResourceBundle;

import javax.swing.Box;
import javax.swing.JPanel;
import javax.swing.JSplitPane;
import javax.swing.JTabbedPane;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

public class JPanelConsomMois extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelConsomMois(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

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
	}

	private void geometrie() {
		this.setLayout(new BorderLayout());

		this.jPanelChartTabMonth = new JPanelChartTabMonth(resourceLang);
		this.jPanelChartTabMonthParam = new JPanelChartTabMonthParam(
				resourceLang);

		this.jSplitTabChart = new JSplitPane(JSplitPane.HORIZONTAL_SPLIT);

		jSplitTabChart.add(jPanelChartTabMonth, JSplitPane.LEFT);
		jSplitTabChart.add(jPanelChartTabMonthParam, JSplitPane.RIGHT);

		jSplitTabChart.setDividerLocation(500);

		this.add(jSplitTabChart, BorderLayout.CENTER);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;

	// Panel de contrôle
	private JPanelChartTabMonth jPanelChartTabMonth;
	private JPanelChartTabMonthParam jPanelChartTabMonthParam;

	// Séparation
	private JSplitPane jSplitTabChart;

}
