package ch.hearc.SmartWater.gui.panelParamChamps;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Map;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.SwingConstants;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import ch.hearc.SmartWater.commUsb.ComConnexion;

public class JPanelControleParam extends JPanel {

	/*------------------------------------------------------------------*\
	 |*							Constructeurs							*|
	 \*------------------------------------------------------------------*/
	public JPanelControleParam(ResourceBundle resourceLang, JPanelParametres jPanelParametres) {

		this.resourceLang = resourceLang;
		this.jPanelParametres = jPanelParametres;

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
		
		this.buttonSave.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent event) {
				System.out.println("[JPanelControleParam] Btn save pressé");
				JPanelControleParam.this.jPanelParametres.saveParams();
			}
		});

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
	private JPanelParametres jPanelParametres;
	
	private JButton buttonRead ;
	private JButton buttonSave ;
	
}
