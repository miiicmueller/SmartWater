package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.ContainerEvent;
import java.awt.event.ContainerListener;
import java.awt.event.HierarchyEvent;
import java.awt.event.HierarchyListener;
import java.awt.event.InputMethodEvent;
import java.awt.event.InputMethodListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
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
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.SwingUtilities;
import javax.swing.event.CellEditorListener;
import javax.swing.event.ChangeEvent;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableColumn;

public class JPanelChartTabMonthParam extends JPanel
		implements
			PropertyChangeListener,
			Runnable {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelChartTabMonthParam(ResourceBundle resourceLang,
			Map<String, String> parameters,
			JPanelChartTabMonth jPanelChartTabMonth) {
		this.resourceLang = resourceLang;
		this.parameters = parameters;
		this.jPanelChartTabMonth = jPanelChartTabMonth;

		this.monthLim = new int[12];
		this.tableMois = new String[12];

		this.tabHeaderMois = (String) this.resourceLang
				.getObject("tabHeaderMois");
		this.tabHeaderLimit = (String) this.resourceLang
				.getObject("tabHeaderLimit");

		this.tableEntete = new String[2];
		this.tableEntete[0] = this.tabHeaderMois;
		this.tableEntete[1] = this.tabHeaderLimit;

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

		this.tableMois[0] = graphMoisJanv;
		this.tableMois[1] = graphMoisFev;
		this.tableMois[2] = graphMoisMar;
		this.tableMois[3] = graphMoisAvr;
		this.tableMois[4] = graphMoisMai;
		this.tableMois[5] = graphMoisJuin;
		this.tableMois[6] = graphMoisJuil;
		this.tableMois[7] = graphMoisAou;
		this.tableMois[8] = graphMoisSept;
		this.tableMois[9] = graphMoisOct;
		this.tableMois[10] = graphMoisNov;
		this.tableMois[11] = graphMoisDec;

		geometrie();
		controle();
		apparence();
	}
	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/
	public void saveLimits() {

		for (int i = 0; i < 12; i++) {
			this.monthLim[i] = (int) this.jTable.getValueAt(i, 1);
			this.parameters.put(PARAM_KEY_BASE + String.valueOf(i),
					String.valueOf(this.monthLim[i]));
		}
	}
	public void updateLimits() {
		Set<Entry<String, String>> entry = this.parameters.entrySet();
		for (Entry<String, String> ligne : entry) {
			String key = ligne.getKey();
			String valeur = ligne.getValue();
			String[] strI = key.split(PARAM_KEY_BASE);
			// Tester si c'est bien la clé d'un mois
			if (strI.length > 1) {
				this.monthLim[Integer.valueOf(strI[1])] = Integer
						.valueOf(valeur);
			}
		}

		for (int i = 0; i < 12; i++) {
			this.jTable.setValueAt(String.valueOf(this.monthLim[i]), i, 1);
		}

		// On recharge le graph
		updateGraphTable();
	}

	public void updateGraphTable() {
		this.jPanelChartTabMonth.updateGraphLim(this.monthLim);
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
			if (this.jTable.isEditing())
				processEditingStarted();
			else
				processEditingStopped();
		}

	}

	/*
	 * Save information of the cell about to be edited
	 */
	private void processEditingStarted() {
		// The invokeLater is necessary because the editing row and editing
		// column of the table have not been set when the "tableCellEditor"
		// PropertyChangeEvent is fired.
		// This results in the "run" method being invoked

		SwingUtilities.invokeLater(this);
	}

	/*
	 * Update the Cell history when necessary
	 */
	private void processEditingStopped() {
		newValue = this.jTable.getModel().getValueAt(rowA, columnA);

		// The data has changed, invoke the supplied Action

		if (!this.newValue.equals(this.oldValue)) {
			// Make a copy of the data in case another cell starts editing
			// while processing this change
			this.monthLim[rowA] = Integer.valueOf((String) this.newValue);
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

		Object[][] donnees = new Object[12][];

		for (int row = 0; row < 12; row++) { // For each element of that array,
			donnees[row] = new Object[2]; // allocate an array of int.
			donnees[row][0] = this.tableMois[row]; // initialize it to the
													// product.
			donnees[row][1] = this.monthLim[row]; // initialize it to the
													// product.
		}

		this.jPanelChartTabMonthParamControl = new JPanelChartTabMonthParamControl(
				resourceLang);
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

		boxTableBtn.add(jTable, BorderLayout.CENTER);
		boxTableBtn.add(jPanelChartTabMonthParamControl);

		this.add(jTable.getTableHeader(), BorderLayout.NORTH);
		this.add(boxTableBtn, BorderLayout.CENTER);

	}
	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	private Map<String, String> parameters;
	private JPanelChartTabMonth jPanelChartTabMonth;

	private Action action;

	// Tableau
	private JTable jTable;
	private DefaultTableModel tableModel;
	private String[] tableEntete;
	private String[] tableMois;

	// Panel de contrôle
	private JPanelChartTabMonthParamControl jPanelChartTabMonthParamControl;

	// Header
	private String tabHeaderMois;
	private String tabHeaderLimit;

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

	private int rowA;
	private int columnA;
	private Object oldValue;
	private Object newValue;

	// Valeurs des séries
	private int[] monthLim;

	private final int MIN_HEIGHT = 100;
	private final int MAX_WIDTH = 100000;
	private final String PARAM_KEY_BASE = "LimMonth";

}
