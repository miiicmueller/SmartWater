package ch.hearc.SmartWater.commUsb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.util.Arrays;
import java.util.Enumeration;

import gnu.io.CommPortIdentifier;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;

public class ComConnexion implements ComConnexions_I
	{

		/*------------------------------------------------------------------*\
		|*							Constructeurs							*|
		\*------------------------------------------------------------------*/

		public ComConnexion(String portName, ComOption comOption)
			{
				this.comOption = comOption;
				this.portName = portName;
				this.inputTrame = new StringBuilder();

			}

		/*------------------------------------------------------------------*\
		|*							Methodes Public							*|
		\*------------------------------------------------------------------*/

		/**
		 * Instanciation du listener ainsi qu'ouverture des flux
		 */
		@Override
		public void start() throws Exception
			{

				// OUverture du flux de lecture
				this.reader = new BufferedReader(new InputStreamReader(
						this.serialPort.getInputStream()));

				// Ouverture du flux de ecriture
				this.writer = this.serialPort.getOutputStream();

				this.serialPort.addEventListener(new SerialPortEventListener()
					{

						@Override
						public void serialEvent(SerialPortEvent event)
							{
								switch (event.getEventType())
									{
									case SerialPortEvent.DATA_AVAILABLE:

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
		public void stop() throws Exception
			{
				this.serialPort.removeEventListener();
			}

		/**
		 * Connexion a la carte meteo
		 */
		@Override
		public void connect() throws Exception
			{

				try
					{
						// Obtenir le port
						CommPortIdentifier portId = CommPortIdentifier
								.getPortIdentifier(this.portName);
						// Ouverture du port
						this.serialPort = (SerialPort) portId.open(
								"Carte Meteo", 1000);
					} catch (Exception e)
					{

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
		public void disconnect() throws Exception
			{
				try
					{
						// arret du service rs232
						stop();
						// On vide le buffer du port serie
						// this.serialPort.getInputStream().reset();
						this.writer.flush();

						// fermeture des flux
						this.writer.close();

						this.reader.close();

						this.serialPort.close();
					} catch (Exception e)
					{

					}
			}

		/*------------------------------*\
		|*			  Static			*|
		\*------------------------------*/

		/**
		 * Fonction de debug pour lister tout les ports de la machine
		 */
		public static void listPorts()
			{
				Enumeration<CommPortIdentifier> portEnum = CommPortIdentifier
						.getPortIdentifiers();
				while (portEnum.hasMoreElements())
					{
						CommPortIdentifier portIdentifier = portEnum
								.nextElement();
						System.out
								.println(portIdentifier.getName()
										+ " - "
										+ getPortTypeName(portIdentifier
												.getPortType()));
					}
			}

		/*------------------------------*\
		|*				Get				*|
		\*------------------------------*/

		@Override
		public String getNamePort()
			{
				return portName;
			}

		/*------------------------------------------------------------------*\
		|*							Methodes Private						*|
		\*------------------------------------------------------------------*/

		/*------------------------------*\
		|*			  Static			*|
		\*------------------------------*/

		public static String getPortTypeName(int portType)
			{
				switch (portType)
					{
					case CommPortIdentifier.PORT_I2C:
						return "I2C";
					case CommPortIdentifier.PORT_PARALLEL:
						return "Parallel";
					case CommPortIdentifier.PORT_RAW:
						return "Raw";
					case CommPortIdentifier.PORT_RS485:
						return "RS485";
					case CommPortIdentifier.PORT_SERIAL:
						return "Serial";
					default:
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

		private static final double K_FACTOR = 0.5;

	}
