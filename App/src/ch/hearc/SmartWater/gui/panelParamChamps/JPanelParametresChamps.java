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
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdminParam;

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
		StringBuilder aReply = new StringBuilder();
		for (int i = 0; i < DEFAULT_PAR_NUM; i++) {
			if (!this.session.isLogged()) {
				JOptionPane jOptionLogErr = new JOptionPane();
				jOptionLogErr.showConfirmDialog(this.session,
						(String) this.resourceLang.getObject("notLogged"),
						(String) this.resourceLang.getObject("notLoggedTit"),
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
				return;
			}

			if (this.jCheckBox[i].isSelected()) {
				switch (this.jChampsParam[i].getName()) {
					case "paramTelAlarm" :
						this.session.writeCmd(this.session.CMD_ALARM_NUM,
								this.jChampsParam[i].getText());
						break;
					case "paramMdpU" :
						this.session.writeCmd(this.session.CMD_MDP_USER,
								this.jChampsParam[i].getText());
						break;
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
			JOptionPane jOptionLogOk = new JOptionPane();
			jOptionLogOk.showConfirmDialog(this, "ParamWrite Succes",
					"Success", JOptionPane.DEFAULT_OPTION,
					JOptionPane.INFORMATION_MESSAGE);

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
					if (JPanelParametresChamps.this.jCheckBox[j].isSelected()) {
						switch (JPanelParametresChamps.this.jCheckBox[j]
								.getName()) {
							case "paramTelAlarm" :
								if (!JPanelParametresChamps.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelParametresChamps.REGEX_TEL_NUM_ALARM)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelParametresChamps.this,
													(String) JPanelParametresChamps.this.resourceLang
															.getObject("formatError")
															+ "+41798184833",
													(String) JPanelParametresChamps.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelParametresChamps.this.jCheckBox[j]
											.setSelected(false);
								}
								break;

							case "paramMdpU" :
								if (!JPanelParametresChamps.this.jChampsParam[j]
										.getText()
										.matches(
												JPanelParametresChamps.REGEX_MDP_USER)) {
									JOptionPane jOptionLogErr = new JOptionPane();
									jOptionLogErr
											.showConfirmDialog(
													JPanelParametresChamps.this,
													(String) JPanelParametresChamps.this.resourceLang
															.getObject("formatError")
															+ "aZ6Hg4GD.... (20 max.)",
													(String) JPanelParametresChamps.this.resourceLang
															.getObject("formatErrorTit"),
													JOptionPane.DEFAULT_OPTION,
													JOptionPane.ERROR_MESSAGE);
									JPanelParametresChamps.this.jCheckBox[j]
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
					if (JPanelParametresChamps.this.jCheckBox[j].isSelected()) {
						JPanelParametresChamps.this.jCheckBox[j]
								.setSelected(false);
					}
					if (JPanelParametresChamps.this.jChampsParam[j].getText()
							.equals("")) {
						JPanelParametresChamps.this.parameters
								.remove(JPanelParametresChamps.this.jChampsParam[j]
										.getName());
						System.out.println("Objet eff");
					} else {
						JPanelParametresChamps.this.parameters.put(
								JPanelParametresChamps.this.jChampsParam[j]
										.getName(),
								JPanelParametresChamps.this.jChampsParam[j]
										.getText());
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

	// Tools
	private JTextField jChampsParam[];
	private JLabel jLabelChampsParam[];
	private JCheckBox jCheckBox[];
	private Session session;

	private Map<String, String> parameters;

	private ResourceBundle resourceLang;

	private static String[] tableParamName = {"paramTelAlarm", "paramMdpU"};

	private static int DEFAULT_PAR_NUM = tableParamName.length;

	private static String REGEX_TEL_NUM_ALARM = "\\+41[0-9]{9}";
	private static String REGEX_MDP_USER = "[0-9a-zA-Z]{4,19}";

}
