package ch.hearc.SmartWater.gui.login;

import ch.hearc.SmartWater.commUsb.ComConnexion;

public class Session {

	public Session(ComConnexion connexion) {
		Logged = false;
	}

	public boolean isLogged() {
		return Logged;
	}
	public void setUserName(String name) {
		this.userName = name;
	}

	public void setUserPassword(String password) {
		this.userPassword = password;
	}

	private boolean Logged;
	private String userName;
	private String userPassword;

}
