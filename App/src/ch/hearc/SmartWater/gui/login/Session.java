package ch.hearc.SmartWater.gui.login;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JOptionPane;
import javax.swing.Timer;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.ComOption;
import ch.hearc.SmartWater.commUsb.dialogSel.JPanelPortSelControl;
import ch.hearc.SmartWater.gui.JFrameSmartWater;

public class Session extends Component {

	public Session(ComConnexion connexion) {
		this.logged = false;
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
	 * @return : 0 = ok , 1 = deja connecté
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
				+ this.userPassword + "_disconnect_\r\n"));

		this.logged = false;
		return 0;
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
		this.userName = name;
		this.userPassword = password;
		this.identified = true;
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
				jOptionWriteErr.showConfirmDialog(Session.this, "Write Error ",
						"Fatal Error", JOptionPane.DEFAULT_OPTION,
						JOptionPane.ERROR_MESSAGE);
			}
		} else {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(Session.this,
					"Veuillez-vous logger !", "Not Logged",
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
						+ this.userPassword + "_" + aCommand + "_" + aParam
						+ "_\r\n"));
			} catch (Exception e) {
				JOptionPane jOptionWriteErr = new JOptionPane();
				jOptionWriteErr.showConfirmDialog(Session.this, "Write Error ",
						"Fatal Error", JOptionPane.DEFAULT_OPTION,
						JOptionPane.ERROR_MESSAGE);
			}
		} else {
			JOptionPane jOptionLogErr = new JOptionPane();
			jOptionLogErr.showConfirmDialog(Session.this,
					"Veuillez-vous logger !", "Not Logged",
					JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
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
				+ this.userPassword + "_connect_\r\n"));

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
		Thread threadTimeout = new Thread(new Runnable() {

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
	// Tools
	private boolean logged;
	private boolean connected;
	private boolean identified;
	private boolean timeOut;
	private String userName;
	private String userPassword;
	private List<String> listPort;

	private final long DELAY_TIMEOUT = 2000;

}
