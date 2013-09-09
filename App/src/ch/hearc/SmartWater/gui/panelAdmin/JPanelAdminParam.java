package ch.hearc.SmartWater.gui.panelAdmin;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.beans.PropertyChangeListener;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;
import java.util.Map.Entry;

import javax.swing.Action;
import javax.swing.Box;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ch.hearc.SmartWater.gui.JFrameSmartWater;
import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelParametresChamps;

public class JPanelAdminParam extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelAdminParam(Map<String, String> parameters,
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

	public void saveToFile() {
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (JPanelAdminParam.this.jChampsParam[i].getText().equals("")) {
			} else {
				JPanelAdminParam.this.parameters.put(
						JPanelAdminParam.this.jChampsParam[i].getName(),
						JPanelAdminParam.this.jChampsParam[i].getText());
			}

		}
	}

	/**
	 * Sauve tout les paramètres checkés par le checkbox
	 */
	public void saveParameters() {
		StringBuilder aReply = new StringBuilder();

		if (!this.session.isLogged()) {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(this.session,
					(String) this.resourceLang.getObject("notLogged"),
					(String) this.resourceLang.getObject("notLoggedTit"),
					JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
			return;
		}

		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (this.jCheckBox[i].isSelected()) {
				switch (this.jChampsParam[i].getName()) {
					case "paramMode" :
						this.session.writeCmd(this.session.CMD_MODE,
								this.jChampsParam[i].getText());
						break;
					case "paramTelCarte" :
						this.session.writeCmd(this.session.CMD_SIMCRD_NUM,
								this.jChampsParam[i].getText());
						break;
					case "paramDispo" :
						this.session.writeCmd(this.session.CMD_DISPO,
								this.jChampsParam[i].getText());
						break;
					case "paramPinNum" :
						this.session.writeCmd(this.session.CMD_PIN_CODE,
								this.jChampsParam[i].getText());
						break;
					case "paramMdpA" :
						this.session.writeCmd(this.session.CMD_MDP_ADMIN,
								this.jChampsParam[i].getText()+"_"+this.jChampsParam[i].getText());
						break;
					case "paramOffsetTemp" :
						this.session.writeCmd(this.session.CMD_OFF_TEMP,
								this.jChampsParam[i].getText());
						break;
					case "paramUnitName" :
						this.session.writeCmd(this.session.CMD_UNIT_NAME,
								this.jChampsParam[i].getText());
						break;
					default :

				}
				if (this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					String[] aStrTab = aStrAnalyse.split("_");

					switch (aStrTab[1]) {
						case "OK" :
							aReply.delete(0, aReply.length());
							break;
						case "ERROR" :
							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(this,
									"Error write param : "
											+ this.jChampsParam[i].getText(),
									"Error", JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;
						default :
							return;
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(this,
							(String) this.resourceLang.getObject("timeOut"),
							(String) this.resourceLang.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}

			}
		}
		JOptionPane jOptionLogOk = new JOptionPane();
		jOptionLogOk.showConfirmDialog(this, "ParamWrite Succes", "Success",
				JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE);
	}
	/**
	 * Lit tout les paramètres checkés
	 */
	public void readParameters() {
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (!this.session.isLogged()) {
				JOptionPane jOptionLogErr = new JOptionPane();
				jOptionLogErr.showConfirmDialog(this.session,
						(String) this.resourceLang.getObject("notLogged"),
						(String) this.resourceLang.getObject("notLoggedTit"),
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
			// this.jCheckBox[i].setSelected(aState);
			this.jCheckBox[i].doClick();
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

			this.jCheckBox[i].addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent event) {
					if (JPanelAdminParam.this.jCheckBox[j].isSelected()) {
						switch (JPanelAdminParam.this.jCheckBox[j].getName()) {
							case "paramMode" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText().matches(
												JPanelAdminParam.REGEX_MODE)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "E | S",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramTelCarte" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText().matches(
												JPanelAdminParam.REGEX_TELNUM)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "+41791311249",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramDispo" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText().matches(
												JPanelAdminParam.REGEX_DISPO)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "hh:mm_hh:mm",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramPinNum" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelAdminParam.REGEX_PIN_CODE)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "5906",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramMdpA" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelAdminParam.REGEX_MDP_ADMIN)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "aZ6Hg4GD.... (20 max.)",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramOffsetTemp" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelAdminParam.REGEX_TEMP_OFFSET)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "0.3",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							case "paramUnitName" :
								if (!JPanelAdminParam.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelAdminParam.REGEX_UNIT_NAME)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelAdminParam.this,
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatError")
															+ "xXx1x4xCxx.... (20 max.)",
													(String) JPanelAdminParam.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelAdminParam.this.jCheckBox[j]
											.setSelected(false);
								}
								break;
							default :
						}
					}

				}
			});

			this.jChampsParam[i].addCaretListener(new CaretListener() {

				@Override
				public void caretUpdate(CaretEvent event) {
					// On désactive si on modifie
					if (JPanelAdminParam.this.jCheckBox[j].isSelected()) {
						JPanelAdminParam.this.jCheckBox[j].setSelected(false);
					}

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
			this.jCheckBox[i].setName(tableParamName[i]);
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

	// Input
	private ResourceBundle resourceLang;
	private Map<String, String> parameters;
	private Session session;

	// Tools
	private JTextField jChampsParam[];
	private JLabel jLabelChampsParam[];
	private JCheckBox jCheckBox[];
	private static String[] tableParamName = {"paramDispo", "paramUnitName",
			"paramMode", "paramOffsetTemp", "paramMdpA", "paramPinNum",
			"paramTelCarte"};

	private static int DEFAULT_PAR_NUM = tableParamName.length;

	private static String REGEX_TELNUM = "\\+41[0-9]{9}";
	private static String REGEX_PIN_CODE = "[0-9]{4}";
	private static String REGEX_MDP_ADMIN = "[0-9a-zA-Z]{4,19}";
	private static String REGEX_TEMP_OFFSET = "-*[0-9]{1,}.[0-9]{1,}";
	private static String REGEX_MODE = "E|S";
	private static String REGEX_UNIT_NAME = "[0-9a-zA-Z]{1,19}";
	private static String REGEX_DISPO = "[0-9]{2}:[0-9]{2}_[0-9]{2}:[0-9]{2}";

}