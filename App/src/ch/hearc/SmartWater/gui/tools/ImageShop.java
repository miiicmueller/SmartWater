package ch.hearc.SmartWater.gui.tools;



import java.awt.Image;

import javax.swing.ImageIcon;


public class ImageShop {

	/*------------------------------*\
	|*			  Static			*|
	\*------------------------------*/
	private static final String PATH = "ressource/";

	private static final String NAME_IMAGE_LOGO = "smartwater4.png";

	private static final boolean IS_BLOQUANT = true;

	public static final ImageIcon IMAGE_LOGO_ICON = ImageTools.loadIcon(PATH
			+ NAME_IMAGE_LOGO, IS_BLOQUANT);
}
