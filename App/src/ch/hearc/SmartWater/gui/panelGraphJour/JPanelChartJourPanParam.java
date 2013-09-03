package ch.hearc.SmartWater.gui.panelGraphJour;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;
import java.util.Map.Entry;

import javax.swing.Action;
import javax.swing.Box;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;

import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonth;
import ch.hearc.SmartWater.gui.panelGraphMois.JPanelChartTabMonthParamControl;

public class JPanelChartJourPanParam extends JPanel
		implements
			PropertyChangeListener,
			Runnable {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelChartJourPanParam(ResourceBundle resourceLang,
			Map<String, String> parameters,
			JPanelChartJourPanGraph jPanelChartJourPanGraph) {

		// Aquisition des entrées
		this.resourceLang = resourceLang;
		this.parameters = parameters;
		this.jPanelChartJourPanGraph = jPanelChartJourPanGraph;

		// Tableaux de données
		this.dayConsom = new int[31];
		this.tableJours = new String[31];

		// Entetes de table
		this.tabHeaderJours = (String) this.resourceLang
				.getObject("tabHeaderJours");
		this.tabHeaderConsom = (String) this.resourceLang
				.getObject("tabHeaderConsom");

		this.tableEntete = new String[2];
		this.tableEntete[0] = this.tabHeaderJours;
		this.tableEntete[1] = this.tabHeaderConsom;

		for (int i = 0; i < this.tableJours.length; i++) {
			this.tableJours[i] = String.valueOf(i + 1);
		}

		geometrie();
		controle();
		apparence();
	}
	/*------------------------------*\
	 |*				Set				*|
	 \*------------------------------*/

	/**
	 * Sauve les limites dans la map
	 */
	public void saveConso() {

		for (int i = 0; i < this.dayConsom.length; i++) {
			this.dayConsom[i] = Integer.valueOf(this.jTable.getValueAt(i, 1)
					.toString());
			this.parameters.put(PARAM_KEY_BASE_CONS + String.valueOf(i),
					String.valueOf(this.dayConsom[i]));
		}
	}

	public void updateJourCons() {
		Set<Entry<String, String>> entry = this.parameters.entrySet();
		for (Entry<String, String> ligne : entry) {
			String key = ligne.getKey();
			String valeur = ligne.getValue();
			String[] strI = key.split(PARAM_KEY_BASE_CONS);
			// Tester si c'est bien la clé d'un mois
			if (strI.length > 1) {
				this.dayConsom[Integer.valueOf(strI[1])] = Integer
						.valueOf(valeur);
			}
		}

		for (int i = 0; i < this.dayConsom.length; i++) {
			this.jTable.setValueAt(String.valueOf(this.dayConsom[i]), i, 1);
		}

		// On recharge le graph
		updateGraphTable();
	}

	/**
	 * Rafraichit le graphique
	 */
	public void updateGraphTable() {
		this.jPanelChartJourPanGraph.updateGraph(dayConsom);
	}

	@Override
	public void run() {
		this.rowA = this.jTable.convertRowIndexToModel(this.jTable
				.getEditingRow());
		this.columnA = this.jTable.convertColumnIndexToModel(this.jTable
				.getEditingColumn());
		this.oldValue = this.jTable.getModel().getValueAt(this.rowA,
				this.columnA);
		this.newValue = null;

	}
	@Override
	public void propertyChange(PropertyChangeEvent e) {
		// A cell has started/stopped editing

		if ("tableCellEditor".equals(e.getPropertyName())) {
			if (this.jTable.isEditing()) {
				processEditingStarted();
			} else {
				processEditingStopped();
			}
		}

	}
	/**
	 * Save information of the cell about to be edited
	 */
	private void processEditingStarted() {
		// The invokeLater is necessary because the editing row and editing
		// column of the table have not been set when the "tableCellEditor"
		// PropertyChangeEvent is fired.
		// This results in the "run" method being invoked
		SwingUtilities.invokeLater(this);
	}

	/**
	 * Update the Cell history when necessary
	 */
	private void processEditingStopped() {
		newValue = this.jTable.getModel().getValueAt(rowA, columnA);

		// The data has changed, invoke the supplied Action

		if (!this.newValue.equals(this.oldValue)) {
			// Make a copy of the data in case another cell starts editing
			// while processing this change
			if (columnA == 1) {
				this.dayConsom[rowA] = Integer.valueOf((String) this.newValue);
			} else if (columnA == 2) {
				this.dayConsom[rowA] = Integer.valueOf((String) this.newValue);
			}
			this.updateGraphTable();

		}
	}

	/*------------------------------------------------------------------*\
	 |*							Methodes Private						*|
	 \*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {

	}

	private void geometrie() {
		BorderLayout bl = new BorderLayout();
		this.setLayout(bl);

		Object[][] donnees = new Object[this.tableJours.length][];

		for (int row = 0; row < this.tableJours.length; row++) {
			donnees[row] = new Object[3]; // allocate an array of int.
			donnees[row][0] = this.tableJours[row]; // initialize it to the
													// product.
			donnees[row][1] = this.dayConsom[row]; // initialize it to the
		}

		// this.jPanelChartTabMonthParamControl = new
		// JPanelChartTabMonthParamControl(
		// resourceLang);
		this.jTable = new JTable(donnees, this.tableEntete) {
			public boolean isCellEditable(int rowIndex, int columnIndex) {
				// ici la cellule (1, 2) est non-editable
				if (columnIndex == 0) {
					return false;
				}
				// le reste est editable
				return true;
			}
		};

		this.jTable.addPropertyChangeListener(this);
		this.jTable.setMaximumSize(new Dimension(MAX_WIDTH, this.jTable
				.getRowCount() * this.jTable.getRowHeight()));
		this.jTable.setPreferredSize(new Dimension(MAX_WIDTH, this.jTable
				.getRowCount() * this.jTable.getRowHeight()));

		jTable.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);

		Box boxTableBtn = Box.createVerticalBox();

		boxTableBtn.add(new JScrollPane(jTable), BorderLayout.CENTER);

		this.add(jTable.getTableHeader(), BorderLayout.NORTH);
		this.add(boxTableBtn, BorderLayout.CENTER);

	}
	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	private Map<String, String> parameters;
	private JPanelChartJourPanGraph jPanelChartJourPanGraph;

	private Action action;

	// Tableau
	private JTable jTable;
	private DefaultTableModel tableModel;
	private String[] tableEntete;
	private String[] tableJours;

	// Header
	private String tabHeaderJours;
	private String tabHeaderConsom;

	private int rowA;
	private int columnA;
	private Object oldValue;
	private Object newValue;

	// Valeurs des séries
	private int[] dayConsom;

	private final int MIN_HEIGHT = 100;
	private final int MAX_WIDTH = 100000;
	private final String PARAM_KEY_BASE_CONS = "ConsJours";

}