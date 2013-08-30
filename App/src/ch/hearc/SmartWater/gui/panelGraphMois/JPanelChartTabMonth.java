package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JPanel;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.CategoryLabelPositions;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.labels.StandardCategoryToolTipGenerator;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.DatasetRenderingOrder;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.LineAndShapeRenderer;
import org.jfree.data.category.CategoryDataset;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.time.Month;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;
import org.jfree.data.xy.XYDataset;

public class JPanelChartTabMonth extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelChartTabMonth(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

		this.monthConsom = new int[12];
		this.monthLim = new int[12];

		this.consomMois = (String) this.resourceLang.getObject("consomMois");
		this.limiteMois = (String) this.resourceLang.getObject("limiteMois");

		this.graphMoisJanv = (String) this.resourceLang
				.getObject("graphMoisJanv");
		this.graphMoisFev = (String) this.resourceLang
				.getObject("graphMoisFev");
		this.graphMoisMar = (String) this.resourceLang
				.getObject("graphMoisMar");
		this.graphMoisAvr = (String) this.resourceLang
				.getObject("graphMoisAvr");
		this.graphMoisMai = (String) this.resourceLang
				.getObject("graphMoisMai");
		this.graphMoisJuin = (String) this.resourceLang
				.getObject("graphMoisJuin");
		this.graphMoisJuil = (String) this.resourceLang
				.getObject("graphMoisJuil");
		this.graphMoisAou = (String) this.resourceLang
				.getObject("graphMoisAou");
		this.graphMoisSept = (String) this.resourceLang
				.getObject("graphMoisSept");
		this.graphMoisOct = (String) this.resourceLang
				.getObject("graphMoisOct");
		this.graphMoisNov = (String) this.resourceLang
				.getObject("graphMoisNov");
		this.graphMoisDec = (String) this.resourceLang
				.getObject("graphMoisDec");

		initDataGraph();

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void updateGraph(int[] MonthConsum, int[] MonthLim) {
		this.monthConsom = MonthConsum;
		updateGraphLim(MonthLim);

	}

	public void updateGraphLim(int[] MonthLim) {

		CategoryDataset donneeGraph = getGraphDataSet(this.monthConsom,
				MonthLim);
		this.chartConsommation.getCategoryPlot().setDataset(donneeGraph);
	}

	public void createGraph(CategoryDataset donneeGraph) {
		// Construction du graph
		this.chartConsommation = ChartFactory.createBarChart(
				(String) this.resourceLang.getObject("graphConsTit"), // chart
				// title
				(String) this.resourceLang.getObject("graphMois"), // domain
																	// axis
																	// label
				(String) this.resourceLang.getObject("graphVol"), // range axis
																	// label
				donneeGraph, // data
				PlotOrientation.VERTICAL, true, // include legend
				false, // tooltips?
				false // URL generator? Not required...
				);

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
		// chartPanel.setDisplayToolTips(false);
		// chartPanel.setPopupMenu(null);
		chartPanel.setMinimumSize(new Dimension(MIN_HEIGHT, MIN_WIDTH));

		this.add(chartPanel, BorderLayout.CENTER);
		this.add(jPanelControlChart, BorderLayout.SOUTH);
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

		this.jPanelControlChart = new JPanelControlChart(resourceLang);

		CategoryDataset donneeGraph = getGraphDataSet(this.monthConsom,
				this.monthLim);

		this.createGraph(donneeGraph);
	}

	private void initDataGraph() {
		for (int i = 0; i < 12; i++) {
			this.monthConsom[i] = 0 + i;
			this.monthLim[i] = 0 + i;
		}
	}

	private CategoryDataset getGraphDataSet(int[] MonthConsum, int[] MonthLim) {

		final DefaultCategoryDataset setData = new DefaultCategoryDataset();

		for (int i = 0; i < MonthConsum.length; i++) {
			this.monthLim[i] = MonthLim[i];
			this.monthConsom[i] = MonthConsum[i];
		}
		// Limites du mois
		setData.addValue(this.monthLim[0], this.limiteMois, this.graphMoisJanv);
		setData.addValue(this.monthLim[1], this.limiteMois, this.graphMoisFev);
		setData.addValue(this.monthLim[2], this.limiteMois, this.graphMoisMar);
		setData.addValue(this.monthLim[3], this.limiteMois, this.graphMoisAvr);
		setData.addValue(this.monthLim[4], this.limiteMois, this.graphMoisMai);
		setData.addValue(this.monthLim[5], this.limiteMois, this.graphMoisJuin);
		setData.addValue(this.monthLim[6], this.limiteMois, this.graphMoisJuil);
		setData.addValue(this.monthLim[7], this.limiteMois, this.graphMoisAou);
		setData.addValue(this.monthLim[8], this.limiteMois, this.graphMoisSept);
		setData.addValue(this.monthLim[9], this.limiteMois, this.graphMoisOct);
		setData.addValue(this.monthLim[10], this.limiteMois, this.graphMoisNov);
		setData.addValue(this.monthLim[11], this.limiteMois, this.graphMoisDec);

		// Consommation du mois
		setData.addValue(this.monthConsom[0], this.consomMois,
				this.graphMoisJanv);
		setData.addValue(this.monthConsom[1], this.consomMois,
				this.graphMoisFev);
		setData.addValue(this.monthConsom[2], this.consomMois,
				this.graphMoisMar);
		setData.addValue(this.monthConsom[3], this.consomMois,
				this.graphMoisAvr);
		setData.addValue(this.monthConsom[4], this.consomMois,
				this.graphMoisMai);
		setData.addValue(this.monthConsom[5], this.consomMois,
				this.graphMoisJuin);
		setData.addValue(this.monthConsom[6], this.consomMois,
				this.graphMoisJuil);
		setData.addValue(this.monthConsom[7], this.consomMois,
				this.graphMoisAou);
		setData.addValue(this.monthConsom[8], this.consomMois,
				this.graphMoisSept);
		setData.addValue(this.monthConsom[9], this.consomMois,
				this.graphMoisOct);
		setData.addValue(this.monthConsom[10], this.consomMois,
				this.graphMoisNov);
		setData.addValue(this.monthConsom[11], this.consomMois,
				this.graphMoisDec);

		return setData;

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;

	// Panel de contrôle
	private JPanelControlChart jPanelControlChart;
	private JFreeChart chartConsommation;
	private ChartPanel chartPanel;

	// Séries
	private String consomMois;
	private String limiteMois;

	// Colonnes
	private String graphMoisJanv;
	private String graphMoisFev;
	private String graphMoisMar;
	private String graphMoisAvr;
	private String graphMoisMai;
	private String graphMoisJuin;
	private String graphMoisJuil;
	private String graphMoisAou;
	private String graphMoisSept;
	private String graphMoisOct;
	private String graphMoisNov;
	private String graphMoisDec;

	// Valeurs des séries
	private int[] monthConsom;
	private int[] monthLim;

	private final int MIN_HEIGHT = 600;
	private final int MIN_WIDTH = 600;
	private final int MAX_CONSOM_SIZE = 5000;

}
