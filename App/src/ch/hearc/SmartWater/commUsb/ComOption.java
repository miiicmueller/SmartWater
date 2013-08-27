
package ch.hearc.SmartWater.commUsb;

import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

public class ComOption
	{

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public ComOption(int speed, int dataBit, int parity, int stopBit)
		{
		this.speed = speed;
		this.dataBit = dataBit;
		this.parity = parity;
		this.stopBit = stopBit;
		}

	public ComOption()
		{
		this(SPEED, DATA_BITS, PARITY, STOP_BITS);
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	@Override
	public String toString()
		{
		StringBuilder builder = new StringBuilder();
		builder.append("ComOption [speed=");
		builder.append(this.speed);
		builder.append(", dataBit=");
		builder.append(this.dataBit);
		builder.append(", parity=");
		builder.append(this.parity);
		builder.append(", stopBit=");
		builder.append(this.stopBit);
		builder.append("]");
		return builder.toString();
		}

	public void applyTo(SerialPort serialPort) throws UnsupportedCommOperationException
		{
		serialPort.setSerialPortParams(speed, dataBit, stopBit, parity);
		}

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	public int getSpeed()
		{
		return this.speed;
		}

	public int getDataBit()
		{
		return this.dataBit;
		}

	public int getParity()
		{
		return this.parity;
		}

	public int getStopBit()
		{
		return this.stopBit;
		}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Inputs/Outputs
	private int speed;
	private int dataBit;
	private int parity;
	private int stopBit;

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	private static final int SPEED = 57600;
	private static final int DATA_BITS = SerialPort.DATABITS_8;
	private static final int PARITY = SerialPort.PARITY_NONE;
	private static final int STOP_BITS = SerialPort.STOPBITS_1;

	}
