package ch.hearc.SmartWater.gui.panelGraphMois;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.util.ResourceBundle;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JSplitPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.JTableHeader;
import javax.swing.table.TableColumn;

public class JPanelChartTabMonthParam extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelChartTabMonthParam(ResourceBundle resourceLang) {
		this.resourceLang = resourceLang;

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

		this.jTable.setMinimumSize(new Dimension(MIN_HEIGHT, MIN_WIDTH));

		jTable.setAutoResizeMode(JTable.AUTO_RESIZE_ALL_COLUMNS);

		this.add(jTable.getTableHeader(), BorderLayout.NORTH);
		this.add(new JScrollPane(jTable), BorderLayout.CENTER);
		this.add(jPanelChartTabMonthParamControl, BorderLayout.SOUTH);

	}
	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;

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

	// Valeurs des séries
	private int[] monthLim;

	private final int MIN_HEIGHT = 100;
	private final int MIN_WIDTH = 100;

}
