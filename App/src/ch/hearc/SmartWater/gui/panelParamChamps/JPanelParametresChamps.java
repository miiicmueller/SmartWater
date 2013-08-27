package ch.hearc.SmartWater.gui.panelParamChamps;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.Map;
import java.util.Map.Entry;
import java.util.ResourceBundle;
import java.util.Set;

import javax.swing.Box;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import ch.hearc.SmartWater.commUsb.ComConnexion;

public class JPanelParametresChamps extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelParametresChamps(Map<String, String> parameters,
			ResourceBundle resourceLang, ComConnexion comConnection) {
		this.parameters = parameters;
		this.resourceLang = resourceLang;
		this.comConnection = comConnection;

		// Contruction de la liste dynamique de paramètres
		this.jChampsParam = new JTextField[DEFAULT_PAR_NUM];
		this.jLabelChampsParam = new JLabel[DEFAULT_PAR_NUM];

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	public void updateParams() {
		Set<Entry<String, String>> entry = this.parameters.entrySet();
		for (Entry<String, String> ligne : entry) {
			String key = ligne.getKey();
			String valeur = ligne.getValue();
			switch (key) {
				case "paramTel1" :
					// this.jChampsTel.setText(valeur);
					break;
				case "Mode" :
					// this.jChampsMode.setText(valeur);
					break;
				default :
			}
		}
	}

	/**
	 * Sauve tout les paramètres checkés par le checkbox
	 */
	public void saveParameters() {
		System.out.println("[JPanelParametresChamps] Sauvegarde en cours");
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (this.jCheckBox[i].isSelected()) {
				switch (this.jChampsParam[i].getName()) {
					case "paramMode" :
						try {
							this.comConnection.getNamePort();
							this.comConnection.write("_A_PassAdmin_mode_"
									+ this.jChampsParam[i].getText() + "_\r\n");
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
						break;
				}
			}

		}
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void apparence() {
		for (JTextField entreeText : this.jChampsParam) {
			entreeText.setEditable(true);
		}
		// Mettre dans les champs les paramètres
		updateParams();

	}

	private void controle() {
		// Rien
	}

	private void geometrie() {
		GridLayout gridLayout = new GridLayout();
		gridLayout.setColumns(2);
		gridLayout.setRows(10);

		this.setLayout(gridLayout);

		// Contruction des box
		Box[] boxChamps = new Box[DEFAULT_PAR_NUM];
		Box[] boxChampsEntree = new Box[DEFAULT_PAR_NUM];
		Box[] boxChampsLabel = new Box[DEFAULT_PAR_NUM];

		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			boxChamps[i] = Box.createVerticalBox();
			boxChampsEntree[i] = Box.createHorizontalBox();
			boxChampsLabel[i] = Box.createHorizontalBox();
		}

		// Construction des checks boxs
		this.jCheckBox = new JCheckBox[DEFAULT_PAR_NUM];
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			this.jCheckBox[i] = new JCheckBox();
		}

		// Constructions des paramètres
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			this.jLabelChampsParam[i] = new JLabel(
					(String) resourceLang.getObject(tableParamName[i]));
			this.jChampsParam[i] = new JTextField("");
			this.jChampsParam[i].setName(tableParamName[i]);
		}
		// Contruction des box
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			boxChampsLabel[i].add(this.jLabelChampsParam[i]);
			boxChamps[i].add(boxChampsLabel[i]);
			boxChampsEntree[i].add(this.jChampsParam[i]);
			boxChampsEntree[i].add(this.jCheckBox[i]);
			boxChamps[i].add(boxChampsEntree[i]);
		}

		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			this.add(boxChamps[i]);
		}
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private JTextField jChampsParam[];
	private JLabel jLabelChampsParam[];
	private JCheckBox jCheckBox[];
	private ComConnexion comConnection;

	private static int DEFAULT_PAR_NUM = 9;

	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	private static String[] tableParamName = {"paramTel1", "paramTel2",
			"paramMode", "paramInter", "paramDispo", "paramMdpU", "paramMdpA",
			"paramOffsetTemp", "paramUnitName"};
}
