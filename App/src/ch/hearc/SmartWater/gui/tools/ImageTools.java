package ch.hearc.SmartWater.gui.tools;

import java.awt.Image;
import java.awt.Toolkit;
import java.net.URL;

import javax.swing.ImageIcon;

public class ImageTools {

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * extension : .png ou .jpg marche aussi si image dans jar, qui est dans le
	 * classe path
	 */
	public static ImageIcon loadIconJar(String nameFile, boolean isBloquant) {
		URL url = ClassLoader.getSystemResource(nameFile);

		if (!isBloquant) {
			return new ImageIcon(Toolkit.getDefaultToolkit().getImage(url));
		} else {
			return new ImageIcon(url);
		}
	}

	/**
	 * extension : .png ou .jpg marche aussi si image dans jar, qui est dans le
	 * classe path
	 */
	public static Image loadJar(String nameFile, boolean isBloquant) {
		return loadIconJar(nameFile, isBloquant).getImage();
	}

	/**
	 * extension : .png ou .jpg
	 */
	public static ImageIcon loadIcon(String nameFile, boolean isBloquant) {
		if (!isBloquant) {
			return new ImageIcon(Toolkit.getDefaultToolkit().getImage(nameFile));
		} else {
			return new ImageIcon(nameFile);
		}
	}

	/**
	 * extension : .png ou .jpg
	 */
	public static Image load(String nameFile, boolean isBloquant) {
		return loadIcon(nameFile, isBloquant).getImage();
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/
}
