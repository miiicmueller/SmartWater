package ch.hearc.SmartWater.gui.login;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.ComOption;
import ch.hearc.SmartWater.commUsb.dialogSel.JPanelPortSelControl;

public class Session {

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
	 *         non sélectionné
	 * 
	 * @throws Exception
	 */
	public int logIn() throws Exception {
		StringBuilder aAnswer = new StringBuilder(); // Pour récupérer la
														// réponse

		if (this.connected == false) {
			return 3;
		}
		// Initialise l'ouverture d'une session
		this.comConnection.write(new String("_" + this.userName + "_"
				+ this.userPassword + "_Connect\r\n"));

		// Démmarage du timeout
		startTimeout(DELAY_TIMEOUT);
		do {
			// On attend une trame complète ou un timeout
		} while (!this.comConnection.isAnswerAvailable(aAnswer)
				&& this.timeOut == false);

		// Si on a été en timeout
		if (this.timeOut) {
			this.logged = false;
			return 1;
		} else {
			// analyse de la réponse
			String aStrAnalyse = aAnswer.toString();
			String[] aStrTab = new String[aStrAnalyse.split("_").length];
			aStrTab = aStrAnalyse.split("_");
			return 0;
		}

	}

	public void logOut() {
		this.logged = false;
	}

	public boolean isIdentified() {
		return this.identified;
	}

	public boolean isLogged() {
		return logged;
	}

	public boolean isConnected() {

		return this.connected;
	}

	public void setLogData(String name, String password) {
		this.userName = name;
		this.userPassword = password;
		this.identified = true;
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

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

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

	private final long DELAY_TIMEOUT = 10000;

}
