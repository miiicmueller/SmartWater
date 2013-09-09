package ch.hearc.SmartWater.commUsb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.List;

import ch.hearc.SmartWater.commUsb.trame.TrameEncoder;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class ComConnexion implements ComConnexions_I {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public ComConnexion() {
		this("", null);
	}

	public ComConnexion(String portName, ComOption comOption) {
		this.comOption = comOption;
		this.portName = portName;
		this.inputTrame = new StringBuilder();

		portOpened = false;

	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/
	public void setPortName(String portName) {
		this.portName = portName;
	}

	public boolean isPortOpened() {
		return portOpened;
	}

	public void setComOption(ComOption comOption) {
		this.comOption = comOption;
	}
	/**
	 * Instanciation du listener ainsi qu'ouverture des flux
	 */
	@Override
	public void start() throws Exception {

		// OUverture du flux de lecture
		this.reader = new BufferedReader(new InputStreamReader(
				this.serialPort.getInputStream()));

		// Ouverture du flux de ecriture
		this.writer = this.serialPort.getOutputStream();

		this.serialPort.addEventListener(new SerialPortEventListener() {

			@Override
			public void serialEvent(SerialPortEvent event) {
				switch (event.getEventType()) {
					case SerialPortEvent.DATA_AVAILABLE :

						break;
				}

			}
		});

		this.serialPort.notifyOnDataAvailable(true);

	}

	/**
	 * Ne pas fermer les flux d'entrées sorties !! Les trames peuvent encore
	 * être entrain d'être traitées
	 */
	@Override
	public void stop() throws Exception {
		this.serialPort.removeEventListener();
	}

	/**
	 * Connexion a la carte meteo
	 */
	@Override
	public void connect() throws Exception {

		try {
			// Obtenir le port
			CommPortIdentifier portId = CommPortIdentifier
					.getPortIdentifier(this.portName);
			// Ouverture du port
			this.serialPort = (SerialPort) portId.open("SmartWater Station",
					1000);
			System.out.println("[ComConnexion]Port successful opened");
			portOpened = true;
		} catch (Exception e) {
			throw new Exception("[ComConnexion]Impossible d'ouvrir le port "
					+ this.portName + " : " + e.getMessage(), e);
		}

		// Configuration du port
		this.comOption.applyTo(this.serialPort);

		// Start du service rs232
		start();
	}

	/**
	 * Fermeture du port RS-232
	 */
	@Override
	public void disconnect() throws Exception {
		try {
			// arret du service rs232
			stop();
			// On vide le buffer du port serie
			// this.serialPort.getInputStream().reset();
			// this.writer.flush();

			// fermeture des flux
			// this.writer.close();
			System.out.println("[ComConnexion]Stopped");

			this.reader.close();
			System.out.println("[ComConnexion]Reader closed");

			this.serialPort.close();

			System.out.println("[ComConnexion]Serial port closed");
			portOpened = false;
		} catch (Exception e) {
			throw new Exception("[ComConnexion]Impossible de fermer le port "
					+ this.portName + " : " + e.getMessage(), e);
		}
	}

	public void write(String strToSend) throws Exception {
		char[] charTab = strToSend.toCharArray();
		System.out.println(strToSend);
		byte[] tabByteToSend = new byte[charTab.length];
		for (int i = 0; i < charTab.length; i++) {
			tabByteToSend[i] = (byte) charTab[i];
		}
		this.writer.write(tabByteToSend);
	}

	public boolean isAnswerAvailable(StringBuilder aAnswer) {
		String aReponse;
		try {
			aReponse = this.reader.readLine();
			aAnswer.append(aReponse);
			return true;
		} catch (IOException e) {
			// Nothing to read
			return false;
		}
	}

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static List<String> findAllSerialPort() {
		List<String> listePortSeriel = new ArrayList<String>();
		// Lister tout les port disponibles de type Seriels
		Enumeration<CommPortIdentifier> portEnum = CommPortIdentifier
				.getPortIdentifiers();

		while (portEnum.hasMoreElements()) {
			CommPortIdentifier portIdentifier = portEnum.nextElement();
			// Si c'est un type seriel
			if (portIdentifier.getPortType() == CommPortIdentifier.PORT_SERIAL) {

				listePortSeriel.add(portIdentifier.getName());

			}

		}
		return listePortSeriel;
	}

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	@Override
	public String getNamePort() {
		return portName;
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	public static String getPortTypeName(int portType) {
		switch (portType) {
			case CommPortIdentifier.PORT_I2C :
				return "I2C";
			case CommPortIdentifier.PORT_PARALLEL :
				return "Parallel";
			case CommPortIdentifier.PORT_RAW :
				return "Raw";
			case CommPortIdentifier.PORT_RS485 :
				return "RS485";
			case CommPortIdentifier.PORT_SERIAL :
				return "Serial";
			default :
				return "unknown type";
		}
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Input
	private ComOption comOption;
	private String portName;

	// Tools
	private SerialPort serialPort;
	private OutputStream writer;
	private BufferedReader reader;

	private StringBuilder inputTrame; // Une seule instanciation

	private boolean portOpened;

}
