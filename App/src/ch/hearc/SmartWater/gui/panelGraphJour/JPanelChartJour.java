package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.util.ResourceBundle;

import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;

import ch.hearc.SmartWater.gui.panelGraphMois.JPanelControlChart;

public class JPanelChartJour extends JPanel {

	public JPanelChartJour(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

		this.dayConsom = new int[31];

		this.consomJour = (String) this.resourceLang.getObject("consomJourn");

		initDataGraph();

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/
	
	public void updateGraph(int[] dayConsom) {
		CategoryDataset donneeGraph = getGraphDataSet(dayConsom);
		this.chartConsommation.getCategoryPlot().setDataset(donneeGraph);
	}
	
	
	private void initDataGraph() {
		for (int i = 0; i < 31; i++) {
			this.dayConsom[i] = i;
		}
	}

	public void createGraph(CategoryDataset donneeGraph) {
		// Construction du graph
		this.chartConsommation = ChartFactory.createLineChart(
				(String) this.resourceLang.getObject("graphConsTitJour"),
				(String) this.resourceLang.getObject("graphJour"),
				(String) this.resourceLang.getObject("graphVol"), donneeGraph,
				PlotOrientation.VERTICAL, true, false, false);

		// NOW DO SOME OPTIONAL CUSTOMISATION OF THE CHART...
		chartConsommation.setBackgroundPaint(Color.white);

		CategoryPlot plot = (CategoryPlot) chartConsommation.getPlot();
		plot.setBackgroundPaint(new Color(0xEE, 0xEE, 0xFF));
		plot.setDomainAxisLocation(AxisLocation.BOTTOM_OR_RIGHT);
		ValueAxis yAxis = plot.getRangeAxis();
		yAxis.setRange(0, MAX_CONSOM_SIZE);
		yAxis.setAutoRange(false);
		yAxis.setMinorTickCount(100);
		yAxis.setAutoRangeMinimumSize(100, true);

		// add the chart to a panel...
		this.chartPanel = new ChartPanel(chartConsommation);
		chartPanel.setPreferredSize(new java.awt.Dimension(MIN_HEIGHT,
				MIN_WIDTH));

		chartPanel.setDomainZoomable(false);
		chartPanel.setRangeZoomable(false);
		chartPanel.setDisplayToolTips(false);
		chartPanel.setPopupMenu(null);
		chartPanel.setMinimumSize(new Dimension(MIN_HEIGHT, MIN_WIDTH));

		this.add(chartPanel, BorderLayout.CENTER);
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
		BorderLayout bl = new BorderLayout();
		this.setLayout(bl);

		CategoryDataset donneeGraph = getGraphDataSet(this.dayConsom);

		this.createGraph(donneeGraph);

	}

	private CategoryDataset getGraphDataSet(int[] dayConsum) {

		final DefaultCategoryDataset setData = new DefaultCategoryDataset();

		for (int i = 0; i < dayConsum.length; i++) {
			this.dayConsom[i] = dayConsum[i];
			// Consommation du mois
			setData.addValue(this.dayConsom[i], this.consomJour,
					String.valueOf(i + 1));

		}

		return setData;

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ResourceBundle resourceLang;

	private JFreeChart chartConsommation;
	private ChartPanel chartPanel;

	// Séries
	private String consomJour;

	// Colonnes

	// Valeurs des séries
	private int[] dayConsom;

	private final int MIN_HEIGHT = 600;
	private final int MIN_WIDTH = 600;
	private final int MAX_CONSOM_SIZE = 100;

}
