package ch.hearc.SmartWater.gui.simulation;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdminState;
import ch.hearc.SmartWater.gui.panelDiag.JPanelDiag;

public class JPanelSimulation extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelSimulation(ResourceBundle resourceLang, Session session) {
		this.resourceLang = resourceLang;
		this.session = session;

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
		this.simBtn1.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				StringBuilder aReply = new StringBuilder();
				
				if (!JPanelSimulation.this.session.isLogged()) {
					JOptionPane jOptionLogErr = new JOptionPane();
					jOptionLogErr.showConfirmDialog(JPanelSimulation.this.session,
							(String) JPanelSimulation.this.resourceLang.getObject("notLogged"),
							(String) JPanelSimulation.this.resourceLang.getObject("notLoggedTit"),
							JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
					return;
				}


				JPanelSimulation.this.session.writeCmd(
						JPanelSimulation.this.session.CMD_SIMUL, "1");

				if (JPanelSimulation.this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					String[] aStrTab = aStrAnalyse.split("_");

					switch (aStrTab[1]) {
						case "OK" :
							aReply.delete(0, aReply.length());
							JOptionPane jOptionOk = new JOptionPane();
							jOptionOk.showConfirmDialog(JPanelSimulation.this,
									"Sim cmpt 1 success", "Success",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							break;
						case "ERROR" :
							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(
									JPanelSimulation.this,
									"Simulation error", "Error",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;
						default :
							return;
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(JPanelSimulation.this,
							(String) JPanelSimulation.this.resourceLang
									.getObject("timeOut"),
							(String) JPanelSimulation.this.resourceLang
									.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}
				
				
			}
		});
		
		this.simBtn2.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				StringBuilder aReply = new StringBuilder();
				
				if (!JPanelSimulation.this.session.isLogged()) {
					JOptionPane jOptionLogErr = new JOptionPane();
					jOptionLogErr.showConfirmDialog(JPanelSimulation.this.session,
							(String) JPanelSimulation.this.resourceLang.getObject("notLogged"),
							(String) JPanelSimulation.this.resourceLang.getObject("notLoggedTit"),
							JOptionPane.DEFAULT_OPTION, JOptionPane.ERROR_MESSAGE);
					return;
				}


				JPanelSimulation.this.session.writeCmd(
						JPanelSimulation.this.session.CMD_SIMUL, "2");

				if (JPanelSimulation.this.session.getReponse(aReply) == 0) {
					System.out.println(aReply.toString());
					// analyse de la réponse
					String aStrAnalyse = aReply.toString();
					String[] aStrTab = aStrAnalyse.split("_");

					switch (aStrTab[1]) {
						case "OK" :
							aReply.delete(0, aReply.length());
							JOptionPane jOptionOk = new JOptionPane();
							jOptionOk.showConfirmDialog(JPanelSimulation.this,
									"Sim cmpt 1 success", "Success",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.INFORMATION_MESSAGE);
							break;
						case "ERROR" :
							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(
									JPanelSimulation.this,
									"Simulation error", "Error",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;
						default :
							return;
					}
				} else {
					JOptionPane jOptionTimeoutErr = new JOptionPane();
					jOptionTimeoutErr.showConfirmDialog(JPanelSimulation.this,
							(String) JPanelSimulation.this.resourceLang
									.getObject("timeOut"),
							(String) JPanelSimulation.this.resourceLang
									.getObject("timeOutTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;

				}
				
				
			}
		});

	}
	private void geometrie() {

		this.setLayout(new FlowLayout(FlowLayout.CENTER));

		simBtn1 = new JButton("Sim cmt1");
		simBtn2 = new JButton("Sim cmt2");

		this.add(simBtn1);
		this.add(simBtn2);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private Session session;
	private ResourceBundle resourceLang;

	// Tools
	private JButton simBtn1;
	private JButton simBtn2;

}