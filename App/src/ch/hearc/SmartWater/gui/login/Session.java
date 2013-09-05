package ch.hearc.SmartWater.gui.login;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

import javax.swing.JOptionPane;
import javax.swing.Timer;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.ComOption;
import ch.hearc.SmartWater.commUsb.dialogSel.JPanelPortSelControl;
import ch.hearc.SmartWater.gui.JFrameSmartWater;
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdminState;

public class Session extends Component {

	public Session(ComConnexion connexion, ResourceBundle resourceLang) {
		this.logged = false;
		this.resourceLang = resourceLang;
		this.connected = false;
		this.comConnection = connexion;
		this.identified = false;
		this.listPort = new ArrayList<String>();

	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public						*|
	\*------------------------------------------------------------------*/

	public List<String> updatePort() {
		return ComConnexion.findAllSerialPort();
	}

	public void connect(String portName) {
		ComOption comOpt = new ComOption();

		if (portName != null) {
			System.out.println("ComPort :" + portName);
			try {
				Session.this.comConnection.setPortName(portName);
				Session.this.comConnection.setComOption(comOpt);

				Session.this.comConnection.connect();
				Session.this.connected = true;
			} catch (Exception e) {
				Session.this.connected = false;
			}
		} else {

		}

	}

	public void disconnect() throws Exception {
		this.comConnection.disconnect();
		this.connected = false;
	}

	/**
	 * Permet de se logger sur la carte
	 * 
	 * @return : 0 = ok, 1 = timeout, 2 = user or password incorrect, 3 = port
	 *         non sélectionné, 4 = unknow error
	 * 
	 * @throws Exception
	 */
	public int logIn() throws Exception {
		int aResult = 0;
		aResult = this.testLog();
		if (aResult == 0) {
			// this.timerLog.start();
		} else if (aResult == 1) {
			// this.timerLog.stop();
		}
		return aResult;
	}

	/**
	 * Permet de se délogger de la carte
	 * 
	 * @return : 0 = ok, 1 = timeout, 2 = Error , 4 = unknow error
	 * @throws Exception
	 */
	public int logOut() throws Exception {
		StringBuilder aAnswer = new StringBuilder(); // Pour récupérer la
		// réponse

		if (this.connected == false) {
			return 1;
		}
		// Initialise l'ouverture d'une session
		this.comConnection.write(new String("_" + this.userName + "_"
				+ this.userPassword + "_" + this.CMD_DISCONNECT + "\r"));

		// Démmarage du timeout
		this.timeOut = false;
		startTimeout(DELAY_TIMEOUT);

		do {
			// On attend une trame complète ou un timeout
		} while (!this.comConnection.isAnswerAvailable(aAnswer)
				&& this.timeOut == false);

		// Si on a été en timeout
		if (this.timeOut) {
			this.logged = false;
			System.out.println("Timeout !!");
			return 1;
		} else {
			// analyse de la réponse
			String aStrAnalyse = aAnswer.toString();
			String[] aStrTab = aStrAnalyse.split("_");

			switch (aStrTab[1]) {
				case "OK" :
					this.logged = false;
					// On démmare le timer auto
					return 0;
				case "ERROR" :
					this.logged = false;
					return 2;
				default :
					this.logged = false;
					return 4;
			}
		}
	}

	/**
	 * Permet de tester si l'utilisateur est identifié
	 */
	public boolean isIdentified() {
		return this.identified;
	}

	/**
	 * Permet de tester si l'utilisateur est loggé
	 * 
	 * @return
	 */
	public boolean isLogged() {
		return logged;
	}

	/**
	 * Permet de tester si l'utilisateur à ouvert un port
	 * 
	 * @return
	 */
	public boolean isConnected() {

		return this.connected;
	}

	/**
	 * Permet de rentrer les paramètres de login
	 * 
	 * @param name
	 * @param password
	 */
	public void setLogData(String name, String password) {
		// Test si l'utilisateur entre qqch vide
		if (!name.equals("") && !password.equals("")) {
			this.userName = name;
			this.userPassword = password;
			this.identified = true;
		}
	}

	public String getUserName() {
		return this.userName;
	}

	/**
	 * Methode qui permet d'écrire sur le port
	 * 
	 * @return
	 * @throws Exception
	 */
	public void write(String strToSend) {
		if (this.isLogged()) {

			try {
				this.comConnection.write(strToSend);
			} catch (Exception e) {
				JOptionPane jOptionWriteErr = new JOptionPane();
				jOptionWriteErr.showConfirmDialog(Session.this,
						(String) Session.this.resourceLang
								.getObject("writeErr"),
						(String) Session.this.resourceLang
								.getObject("writeErrTit"),
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
			}
		} else {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(Session.this,
					(String) Session.this.resourceLang.getObject("notLogged"),
					(String) Session.this.resourceLang
							.getObject("notLoggedTit"),
					JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
		}
	}

	/**
	 * Methode qui permet d'écrire sur le port
	 * 
	 * @return
	 * @throws Exception
	 */
	public void writeCmd(String aCommand, String aParam) {
		if (this.isLogged()) {

			try {
				this.comConnection.write(new String("_" + this.userName + "_"
						+ this.userPassword + "_" + aCommand + aParam + "_\r"));
			} catch (Exception e) {
				JOptionPane jOptionWriteErr = new JOptionPane();
				jOptionWriteErr.showConfirmDialog(Session.this,
						(String) Session.this.resourceLang
								.getObject("writeErr"),
						(String) Session.this.resourceLang
								.getObject("writeErrTit"),
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
			}
		} else {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(Session.this,
					(String) Session.this.resourceLang.getObject("notLogged"),
					(String) Session.this.resourceLang
							.getObject("notLoggedTit"),
					JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
		}
	}

	public void readCmd(String aCommand) {
		if (this.isLogged()) {

			try {
				this.comConnection.write(new String("_" + this.userName + "_"
						+ this.userPassword + "_" + aCommand + "\r"));
			} catch (Exception e) {
				JOptionPane jOptionWriteErr = new JOptionPane();
				jOptionWriteErr.showConfirmDialog(Session.this,
						(String) Session.this.resourceLang
								.getObject("writeErr"),
						(String) Session.this.resourceLang
								.getObject("writeErrTit"),
						JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
			}
		} else {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(Session.this,
					(String) Session.this.resourceLang.getObject("notLogged"),
					(String) Session.this.resourceLang
							.getObject("notLoggedTit"),
					JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
		}
	}

	public int getReponse(StringBuilder aReponse) {
		// Démmarage du timeout
		this.timeOut = false;
		startTimeout(DELAY_TIMEOUT);
		do {
			// On attend une trame complète ou un timeout
		} while (!this.comConnection.isAnswerAvailable(aReponse)
				&& this.timeOut == false);

		// Si on a été en timeout
		if (this.timeOut) {
			// this.logged = false;
			System.out.println("Timeout !!");
			return 1;
		} else {
			return 0;
		}
	}
	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private int testLog() throws Exception {
		StringBuilder aAnswer = new StringBuilder(); // Pour récupérer la
		// réponse

		if (this.connected == false) {
			return 3;
		}
		// Initialise l'ouverture d'une session
		this.comConnection.write(new String("_" + this.userName + "_"
				+ this.userPassword + "_" + this.CMD_CONNECT + "\r"));

		// Démmarage du timeout
		this.timeOut = false;
		startTimeout(DELAY_TIMEOUT);
		do {
			// On attend une trame complète ou un timeout
		} while (!this.comConnection.isAnswerAvailable(aAnswer)
				&& this.timeOut == false);

		// Si on a été en timeout
		if (this.timeOut) {
			this.logged = false;
			System.out.println("Timeout !!");
			return 1;
		} else {
			// analyse de la réponse
			String aStrAnalyse = aAnswer.toString();
			System.out.println("Reponse : " + aStrAnalyse);
			String[] aStrTab = aStrAnalyse.split("_");

			switch (aStrTab[1]) {
				case "OK" :
					this.logged = true;
					// On démmare le timer auto
					return 0;
				case "ERROR" :
					this.logged = false;
					return 2;
				default :
					this.logged = false;
					return 4;
			}
		}
	}
	private void startTimeout(final long aDelay) {
		// Initialisation du timeout à false
		this.timeOut = false;

		// On attend que l'ancien thread soit mort
		if (this.threadTimeout != null) {
			if (this.threadTimeout.isAlive()) {
				this.threadTimeout.interrupt();
			}
		}

		this.threadTimeout = new Thread(new Runnable() {

			@Override
			public void run() {
				try {
					Thread.sleep(aDelay);
					Session.this.timeOut = true;
				} catch (InterruptedException e) {
				}

			}
		});

		// Démmarage du thread
		threadTimeout.start();
	}

	// Inputs
	private ComConnexion comConnection;
	private ResourceBundle resourceLang;

	// Tools
	private boolean logged;
	private boolean connected;
	private boolean identified;
	private boolean timeOut;
	private String userName;
	private String userPassword;
	private List<String> listPort;
	private Thread threadTimeout;

	public final long DELAY_TIMEOUT = 20000;

	// Nom des commandes
	public final String CMD_MODE = "mode_";
	public final String CMD_MISEAHEURE = "clock_";
	public final String CMD_DISPO = "dispo_";
	public final String CMD_OFF_TEMP = "offset_";
	public final String CMD_MDP_ADMIN = "passa_";
	public final String CMD_MEM_RESET = "reset_";
	public final String CMD_PIN_CODE = "pin_";
	public final String CMD_SIMCRD_NUM = "own_";
	public final String CMD_SIMUL = "simulate_";
	public final String CMD_DIAG_UNIT = "dysfuntion_";
	public final String CMD_ALARM_NUM = "alarm_";
	public final String CMD_LIMITES = "limits_";
	public final String CMD_STATE = "state_";
	public final String CMD_MDP_USER = "passu_";
	public final String CMD_MONTH_CONS = "monthlyconsumption_";
	public final String CMD_DAY_CONS = "dailyconsumption_";
	public final String CMD_CONNECT = "connect_";
	public final String CMD_DISCONNECT = "disconnect_";
	public final String CMD_UNIT_NAME = "unitname_";

}
