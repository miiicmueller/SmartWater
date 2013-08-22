package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

public class JPanelControleParam extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelControleParam(ResourceBundle resourceLang) {

		this.resourceLang = resourceLang;

		geometrie();
		controle();
		apparence();
	}

	/*------------------------------*\
	 |*				Set				*|
	 \*------------------------------*/

	/*------------------------------------------------------------------*\
	 |*							Methodes Private						*|
	 \*------------------------------------------------------------------*/

	private void apparence() {

	}

	private void controle() {

	}

	private void geometrie() {
		
		this.setLayout(new FlowLayout(FlowLayout.CENTER));
		
		this.buttonRead = new JButton((String)resourceLang.getObject("buttonRead"));
		this.buttonSave = new JButton((String)resourceLang.getObject("buttonSave"));
		
		this.add(buttonRead);
		this.add(buttonSave);
		

	}

	/*------------------------------------------------------------------*\
	 |*							Attributs Private						*|
	 \*------------------------------------------------------------------*/

	// Tools
	private ResourceBundle resourceLang;
	
	private JButton buttonRead ;
	private JButton buttonSave ;
	
}
