
package ch.hearc.SmartWater.commUsb.trame ;

public class TrameEncoder
	{

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/

	/**
	 * <pre>
	 * Input : 	Une trame du type :
	 * 				010X00
	 * 			ou X appartient a [0,2], selon (pression,temperature,altitude)
	 *
	 * Outputs: le tableu de byte a écrire sur le flux outputStream en direction de la station meteo
	 *
	 * Note:
	 *
	 * 		(N1)	Le flux a ete instantie de la maniere suivante :
	 *  				outputStream = port.getOutputStream();
	 *
	 * 		(N2)	L'ecriture sur le flux se fait de la maniere suivante :
	 * 					outputStream.write(coder("010100"))
	 * </pre>
	 */
	public static byte[] coder(String trame)
		{
		int len = trame.length();
		byte[] data = new byte[len / 2];
		for(int i = 0; i < len; i += 2)
			{
			data[i / 2] = (byte)((Character.digit(trame.charAt(i), 16) << 4) + Character.digit(trame.charAt(i + 1), 16));
			}
		return data;
		}
	}
