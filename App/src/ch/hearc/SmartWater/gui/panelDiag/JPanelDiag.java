package ch.hearc.SmartWater.gui.panelDiag;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ResourceBundle;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextArea;

import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.gui.panelAdmin.JPanelAdminState;

public class JPanelDiag extends JPanel {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public JPanelDiag(ResourceBundle resourceLang, Session session) {
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

	private void setTextEtat(String Etat) {
		this.jEtat.setText(Etat);
	}

	private void apparence() {

	}

	private void controle() {
		// Rien
		this.btnRead.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				StringBuilder aReply = new StringBuilder();

				if (!JPanelDiag.this.session.isLogged()) {
					JOptionPane jOptionLogErr = new JOptionPane();
					jOptionLogErr.showConfirmDialog(JPanelDiag.this.session,
							(String) JPanelDiag.this.resourceLang
									.getObject("notLogged"),
							(String) JPanelDiag.this.resourceLang
									.getObject("notLoggedTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					return;
				}

				JPanelDiag.this.session.writeCmd(
						JPanelDiag.this.session.CMD_STATE, "");

				for (int i = 0; i < LINE_NUM; i++) {
					if (JPanelDiag.this.session.getReponse(aReply) == 0) {
						System.out.println(aReply.toString());
						String aStrAnalyse = aReply.toString();
						String[] aStrTab = aStrAnalyse.split("_");

						if (aStrTab[1] == null) {
							JPanelDiag.this.jEtat.append(aStrAnalyse + "\r\n");
						} else if (aStrTab[1].equals("ERROR")) {

							JOptionPane jOptionLogOk = new JOptionPane();
							jOptionLogOk.showConfirmDialog(JPanelDiag.this,
									"Cannot read module state", "Error",
									JOptionPane.DEFAULT_OPTION,
									JOptionPane.ERROR_MESSAGE);
							return;

						}

					} else {
						JOptionPane jOptionTimeoutErr = new JOptionPane();
						jOptionTimeoutErr.showConfirmDialog(JPanelDiag.this,
								(String) JPanelDiag.this.resourceLang
										.getObject("timeOut"),
								(String) JPanelDiag.this.resourceLang
										.getObject("timeOutTit"),
								JOptionPane.DEFAULT_OPTION,
								JOptionPane.ERROR_MESSAGE);
						return;

					}
				}
			}

		});
	}
	private void geometrie() {

		this.setLayout(new BorderLayout());

		JPanel jPanelCmptrs = new JPanel(new BorderLayout());
		JPanel jPanelCmptrsCtrl = new JPanel(new FlowLayout(FlowLayout.CENTER));

		this.jEtat = new JTextArea();
		this.btnRead = new JButton("Read");

		jPanelCmptrs.add(this.jEtat, BorderLayout.CENTER);

		jPanelCmptrsCtrl.add(btnRead);

		this.add(jPanelCmptrs, BorderLayout.CENTER);
		this.add(jPanelCmptrsCtrl, BorderLayout.SOUTH);

	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private Session session;
	private ResourceBundle resourceLang;

	private JTextArea jEtat;
	private JButton btnRead;
	private static String REGEX_TEST_FRAME = "^Unite";
	private static int LINE_NUM = 10;
}
