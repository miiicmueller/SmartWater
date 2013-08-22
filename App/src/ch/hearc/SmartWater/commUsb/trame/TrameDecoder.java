package ch.hearc.SmartWater.commUsb.trame;

public class TrameDecoder
	{

		/*------------------------------------------------------------------*\
		|*							Methodes Public							*|
		\*------------------------------------------------------------------*/

		/*------------------------------*\
		|*			  Static			*|
		\*------------------------------*/

		/**
		 * <pre>
		 * 
		 * Inputs : Une trame du type : 00 0X YY ZZ TT UU VV 00 0D 0A
		 * 
		 * Outputs : valeur du float coder dans les octest YY ZZ UU VV
		 * 
		 * Note :
		 * 
		 * 		(N1) Le reader a ete instantie de la maniere suivante :
		 *  					bufferedReader = new BufferedReader(new InputStreamReader(port.getInputStream()));
		 * 
		 * 		(N2) La lecture du flux doit s'employer de la maniere suivante :
		 * 				String trame=bufferedReader.readLine();
		 * 				float valeurReponse = TrameDecoder.valeur(trame);
		 * 
		 * </pre>
		 */
		public static float valeur(String trame)
			{
				try
					{
						byte[] tabByte = trame.getBytes();
						int valueInt = ((0xff & tabByte[6])
								| ((0xff & tabByte[5]) << 8)
								| ((0xff & tabByte[3]) << 16) | ((0xff & tabByte[2]) << 24));

						float valeur = Float.intBitsToFloat(valueInt);

						return valeur;
					} catch (Exception e)
					{
						return 0;
					}
			}

		public static float valeur(byte[] trame)
			{
				try
					{
						byte[] tabByte = trame;
						int valueInt = ((0xff & tabByte[6])
								| ((0xff & tabByte[5]) << 8)
								| ((0xff & tabByte[3]) << 16) | ((0xff & tabByte[2]) << 24));

						float valeur = Float.intBitsToFloat(valueInt);

						return valeur;
					} catch (Exception e)
					{
						return 0;
					}
			}

	}
