package ch.hearc.SmartWater.gui.panelParamChamps;

import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.InputMethodEvent;
import java.awt.event.InputMethodListener;
import java.util.Map;
import java.util.Map.Entry;
import java.util.ResourceBundle;
import java.util.Set;

import javax.swing.Box;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.gui.login.Session;

public class JPanelParametresChamps extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelParametresChamps(Map<String, String> parameters,
			ResourceBundle resourceLang, Session session) {
		this.parameters = parameters;
		this.resourceLang = resourceLang;
		this.session = session;

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
			for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
				if (key.equals(this.jChampsParam[i].getName())) {
					this.jChampsParam[i].setText(valeur);
					break;
				}
			}
		}
	}
	/**
	 * Sauve tout les paramètres checkés par le checkbox
	 */
	public void saveParameters() {
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (!this.session.isLogged()) {
				JOptionPane jOptionLogErr = new JOptionPane();
				jOptionLogErr.showConfirmDialog(this.session,
						"Veuillez-vous connecter !", "Not Logged",
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
				return;
			}

			if (this.jCheckBox[i].isSelected()) {
				switch (this.jChampsParam[i].getName()) {
					case "paramMode" :
						this.session.writeCmd("mode",
								this.jChampsParam[i].getText());
						break;
					case "paramTelCarte" :
						this.session.writeCmd("unum",
								this.jChampsParam[i].getText());
						break;
					case "paramTelAlarm1" :
						this.session.writeCmd("alarm1",
								this.jChampsParam[i].getText());
						break;
					case "paramTelAlarm2" :
						this.session.writeCmd("alarm2",
								this.jChampsParam[i].getText());
						break;
					case "paramInter" :
						// this.session.write();
						break;
					case "paramDispo" :
						// this.session.write();
						break;
					case "paramMdpU" :
						this.session.writeCmd("passu",
								this.jChampsParam[i].getText());
						break;
					case "paramMdpA" :
						this.session.writeCmd("passa",
								this.jChampsParam[i].getText());
						break;
					case "paramOffsetTemp" :
						this.session.writeCmd("offset",
								this.jChampsParam[i].getText());
						break;
					case "paramUnitName" :
						this.session.writeCmd("uname",
								this.jChampsParam[i].getText());
						break;

				}
			}

		}
	}

	/**
	 * Lit tout les paramètres checkés
	 */
	public void readParameters() {
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (!this.session.isLogged()) {
				JOptionPane jOptionLogErr = new JOptionPane();
				jOptionLogErr.showConfirmDialog(this.session,
						"Veuillez-vous connecter !", "Not Logged",
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
				return;
			}
		}

	}

	/**
	 * Permet de changer tout l'état des checkbox en meme temps et prennent la
	 * valeur de aState
	 * 
	 * @param aState
	 */
	public void controlCheckBox(boolean aState) {
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			this.jCheckBox[i].setSelected(aState);
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

		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			final int j = i;
			this.jChampsParam[i].addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent event) {
					JPanelParametresChamps.this.parameters.put(
							JPanelParametresChamps.this.jChampsParam[j]
									.getName(),
							JPanelParametresChamps.this.jChampsParam[j]
									.getText());
					System.out
							.println("[JPanelParametresChamps] : Paramètre AL "
									+ JPanelParametresChamps.this.jChampsParam[j]
											.getName());
				}

			});

			this.jChampsParam[i].addFocusListener(new FocusListener() {

				@Override
				public void focusLost(FocusEvent event) {
					JPanelParametresChamps.this.parameters.put(
							JPanelParametresChamps.this.jChampsParam[j]
									.getName(),
							JPanelParametresChamps.this.jChampsParam[j]
									.getText());
				}

				@Override
				public void focusGained(FocusEvent event) {
					// TODO Auto-generated method stub

				}
			});

			this.jChampsParam[i].addCaretListener(new CaretListener() {

				@Override
				public void caretUpdate(CaretEvent event) {
					System.out.println("Param sauvegardé");

				}
			});
		}
	}
	private void geometrie() {
		GridLayout gridLayout = new GridLayout();
		gridLayout.setColumns(1);
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
	private Session session;

	private static int DEFAULT_PAR_NUM = 11;

	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	private static String[] tableParamName = {"paramTelCarte",
			"paramTelAlarm1", "paramTelAlarm2", "paramPinNum", "paramMode",
			"paramInter", "paramDispo", "paramMdpU", "paramMdpA",
			"paramOffsetTemp", "paramUnitName"};

}
