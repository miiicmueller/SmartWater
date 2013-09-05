package ch.hearc.SmartWater.gui.panelAdmin;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;
import java.util.Date;
import java.util.Map;
import java.util.ResourceBundle;
import java.util.Set;
import java.util.Map.Entry;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelParamChamps.JPanelParametresChamps;

public class JPanelAdminState extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelAdminState(Map<String, String> parameters,
			ResourceBundle resourceLang, Session session) {
		this.parameters = parameters;
		this.resourceLang = resourceLang;
		this.session = session;

		JPanelAdminState.this.stateEEPROM = "NA";
		JPanelAdminState.this.stateCOMP = "NA";
		JPanelAdminState.this.stateGSM = "NA";
		JPanelAdminState.this.stateSIM = "NA";
		JPanelAdminState.this.stateTEMP = "NA";

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

	private void updateStateField() {

		this.jEtatCarte.setText("");
		this.jEtatCarte.append("ETAT DE LA CARTE : \r\n\r\n");
		this.jEtatCarte.append("Eeprom : " + this.stateEEPROM + "\r\n");
		this.jEtatCarte.append("Compteur d'eau : " + this.stateCOMP + "\r\n");
		this.jEtatCarte.append("Module GSM : " + this.stateGSM + "\r\n");
		this.jEtatCarte.append("Carte SIM : " + this.stateSIM + "\r\n");
		this.jEtatCarte.append("Capteur de température :" + this.stateTEMP
				+ "\r\n");
		this.jEtatCarte
				.append("\r\n\r\nPour consulter une nouvelle fois, appuyez sur le bouton : \"Etat carte\"");

	}

	private void apparence() {
		this.jEtatCarte.setAutoscrolls(true);
		this.jEtatCarte.setEditable(false);
		this.updateStateField();

	}

	private void controle() {

		this.btnMAH.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				StringBuilder aReply = new StringBuilder();
				String aParamH;

				int heure = Calendar.getInstance().get(Calendar.HOUR_OF_DAY);
				int minutes = Calendar.getInstance().get(Calendar.MINUTE);
				int jourDuMois = Calendar.getInstance().get(
						Calendar.DAY_OF_MONTH);
				int mois = Calendar.getInstance().get(Calendar.MONTH) + 1;
				int année = Calendar.getInstance().get(Calendar.YEAR);
				System.out.println(mois);
				aParamH = new String(String.valueOf(heure) + ":"
						+ String.valueOf(minutes) + "_"
						+ String.valueOf(jourDuMois) + ":"
						+ String.valueOf(mois) + ":" + String.valueOf(année));

				JPanelAdminState.this.session.writeCmd(
						JPanelAdminState.this.session.CMD_MISEAHEURE, aParamH);

				if (JPanelAdminState.this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					String[] aStrTab = aStrAnalyse.split("_");

					switch (aStrTab[1]) {
						case "OK" :
							aReply.delete(0, aReply.length());
							JOptionPane jOptionOk = new JOptionPane();
							jOptionOk.showConfirmDialog(JPanelAdminState.this,
									"MAH success", "Success",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							break;
						case "ERROR" :
							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(
									JPanelAdminState.this,
									"Cannot MAH the module", "Error",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;
						default :
							return;
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(JPanelAdminState.this,
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOut"),
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}

			}
		});

		this.btnConsult.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {

				StringBuilder aReply = new StringBuilder();

				JPanelAdminState.this.session.writeCmd(
						JPanelAdminState.this.session.CMD_DIAG_UNIT, "");

				if (JPanelAdminState.this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					if (aStrAnalyse.matches(REGEX_TEST_FRAME)) {
						String[] aStrTab = aStrAnalyse.split("_");
						String[] aStrParam = aStrTab[1].split(":");

						JPanelAdminState.this.stateEEPROM = aStrParam[0];
						JPanelAdminState.this.stateCOMP = aStrParam[1];
						JPanelAdminState.this.stateGSM = aStrParam[2];
						JPanelAdminState.this.stateSIM = aStrParam[3];
						JPanelAdminState.this.stateTEMP = aStrParam[4];

						// Mise à jour de l'affichage de l'etat
						updateStateField();

					} else {
						String[] aStrTab = aStrAnalyse.split("_");
						switch (aStrTab[1]) {
							case "ERROR" :
								JOptionPane jOptionLogOk = new JOptionPane();
								jOptionLogOk.showConfirmDialog(
										JPanelAdminState.this,
										"Cannot consult state", "Error",
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								return;
							default :
								return;
						}
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(JPanelAdminState.this,
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOut"),
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}

			}
		});

		this.btnMemReset.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {

				StringBuilder aReply = new StringBuilder();

				JPanelAdminState.this.session.writeCmd(
						JPanelAdminState.this.session.CMD_MEM_RESET, "");

				if (JPanelAdminState.this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					String[] aStrTab = aStrAnalyse.split("_");

					switch (aStrTab[1]) {
						case "OK" :
							aReply.delete(0, aReply.length());
							JOptionPane jOptionOk = new JOptionPane();
							jOptionOk.showConfirmDialog(JPanelAdminState.this,
									"Factory reset success", "Success",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							break;
						case "ERROR" :
							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(
									JPanelAdminState.this,
									"Cannot reset memory", "Error",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;
						default :
							return;
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(JPanelAdminState.this,
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOut"),
							(String) JPanelAdminState.this.resourceLang
									.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}

			}
		});

	}
	private void geometrie() {

		this.setLayout(new GridLayout(1, 2));

		this.btnMAH = new JButton("Mise à l'heure");
		this.btnConsult = new JButton("Etat carte");
		this.btnMemReset = new JButton("Factory reset");

		this.jEtatCarte = new JTextArea("Etat de la carte");

		JPanel jPanBtn = new JPanel(new GridLayout(10, 1));

		Box boxBtnMAH = Box.createHorizontalBox();
		Box boxBtnCons = Box.createHorizontalBox();
		Box boxBtnRes = Box.createHorizontalBox();

		Box boxVert1 = Box.createVerticalBox();
		Box boxVert2 = Box.createVerticalBox();
		Box boxVert3 = Box.createVerticalBox();

		boxVert1.add(boxBtnMAH);
		boxVert2.add(boxBtnCons);
		boxVert3.add(boxBtnRes);

		boxBtnMAH.add(btnMAH);
		boxBtnCons.add(btnConsult);
		boxBtnRes.add(btnMemReset);

		jPanBtn.add(boxVert1);
		jPanBtn.add(boxVert2);
		jPanBtn.add(boxVert3);

		this.add(jPanBtn);
		this.add(jEtatCarte);
	}
	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs
	private Session session;
	private Map<String, String> parameters;
	private ResourceBundle resourceLang;

	// Tools
	private JButton btnMAH;
	private JButton btnConsult;
	private JButton btnMemReset;
	private JTextArea jEtatCarte;

	private String stateEEPROM;
	private String stateCOMP;
	private String stateGSM;
	private String stateSIM;
	private String stateTEMP;

	private static String REGEX_TEST_FRAME = "(_[a-zA-Z0-9]{1,}:){5}_";
}
