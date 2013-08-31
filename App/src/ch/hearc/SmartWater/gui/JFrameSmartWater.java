package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.IOException;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import ch.hearc.SmartWater.commUsb.ComConnexion;
import ch.hearc.SmartWater.commUsb.dialogSel.JFramePortSel;
import ch.hearc.SmartWater.dataManager.DataManager;
import ch.hearc.SmartWater.gui.login.JFrameLogin;
import ch.hearc.SmartWater.gui.login.Session;
import ch.hearc.SmartWater.lang.JLanguages;

public class JFrameSmartWater extends JFrame {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/

	public JFrameSmartWater() {

		this.dataManager = new DataManager();
		this.parametres = new TreeMap<String, String>();

		this.userCountry = System.getProperty("user.country");
		this.userLang = System.getProperty("user.language");

		this.language = new JLanguages(new Locale(this.userLang));

		this.comUSB = new ComConnexion();

		this.session = new Session(this.comUSB, this.language.getResBundle());

		geometrie();
		control();
		apparence();

	}

	public static void setLookAndFeel() {
		try {
			for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void control() {
		setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);

		// Si on appuie sur Quitter
		this.menuFichierExit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				exitSoftware();
				JFrameSmartWater.this.dispose();
				System.exit(0);
			}
		});

		// Si on appuie sur enregistrer
		this.menuFichierSave.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// Appel de la classes enregistrement des
				// paramètres
				try {
					// Sauvegarde des limites
					JFrameSmartWater.this.jPanelPrincipal
							.getJPanelChartTabMonthParam().saveLimitEtConso();
					JFrameSmartWater.this.jPanelPrincipal
							.getJPanelChartJourPanParam().saveConso();
					JFrameSmartWater.this.jPanelPrincipal.getJPanelAdmin()
							.saveToFile();
					JFrameSmartWater.this.jPanelPrincipal.getJPanelParam()
							.saveToFile();
					JFrameSmartWater.this.dataManager.saveFile(parametres);
				} catch (IOException e) {
				}
			}
		});

		// Si on appuie sur enregistrer
		this.menuFichierOpen.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// Appel de la classes enregistrement des
				// paramètres
				// Map<String, String> parametres = null;

				try {
					JFrameSmartWater.this.dataManager
							.openFile(JFrameSmartWater.this.parametres);
					JFrameSmartWater.this.jPanelPrincipal.getJPanelParam()
							.updateParams();
					// Ouverture des limites des limites
					JFrameSmartWater.this.jPanelPrincipal
							.getJPanelChartTabMonthParam().updateLimits();
					JFrameSmartWater.this.jPanelPrincipal
							.getJPanelChartTabMonthParam().updateMonthCons();
					JFrameSmartWater.this.jPanelPrincipal
							.getJPanelChartJourPanParam().updateJourCons();
					JFrameSmartWater.this.jPanelPrincipal.getJPanelAdmin()
							.updateParams();

				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});

		this.menuCommSel.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				JFrameSmartWater.this.jFramePortSel.refreshPortAff();
				JFrameSmartWater.this.jFramePortSel.setVisible(true);

			}
		});

		this.menuLoginLog.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				JFrameSmartWater.this.jFramLog.setVisible(true);
			}
		});

		this.menuCommConnect.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent event) {
				// Si on n'a pas entré de nom d'utilisateur
				if (!JFrameSmartWater.this.session.isIdentified()) {
					JOptionPane jOptionLogErr = new JOptionPane();
					jOptionLogErr.showConfirmDialog(JFrameSmartWater.this,
							(String) JFrameSmartWater.this.language
									.getResBundle().getObject("notLogged"),
							(String) JFrameSmartWater.this.language
									.getResBundle().getObject("notLoggedTit"),
							JOptionPane.DEFAULT_OPTION,
							JOptionPane.ERROR_MESSAGE);
					JFrameSmartWater.this.jFramLog.setVisible(true);
					// Si on n'est déja connecté c'est que l'on veut se
					// déconnecter
				} else if (JFrameSmartWater.this.session.isLogged()) {
					try {
						switch (JFrameSmartWater.this.session.logOut()) {
							case 0 :
								JOptionPane jOptionLogOk = new JOptionPane();
								jOptionLogOk.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"decSucc"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"decSuccTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.INFORMATION_MESSAGE);
								// Changement en bouton de déconnexion
								JFrameSmartWater.this.menuCommConnect
										.setLabel("Disconnect");
								break;
							case 1 :
								JOptionPane jOptionTimeoutErr = new JOptionPane();
								jOptionTimeoutErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"timeOut"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"timeOutTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								break;
							case 2 :
								JOptionPane jOptionUserPasswdErr = new JOptionPane();
								jOptionUserPasswdErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"decFail"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"decFailTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								break;
							case 4 :
								JOptionPane jOptionUnkErr = new JOptionPane();
								jOptionUnkErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"unkErr"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"unkErrTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								JFrameSmartWater.this.jFramePortSel
										.refreshPortAff();
								JFrameSmartWater.this.jFramePortSel
										.setVisible(true);

								break;
							default :

						}
					} catch (Exception e) {
					}
					JFrameSmartWater.this.menuCommConnect
							.setLabel((String) JFrameSmartWater.this.language
									.getResBundle()
									.getObject("menuCommConnect"));
				} else {
					try {
						switch (JFrameSmartWater.this.session.logIn()) {
							case 0 :
								JOptionPane jOptionLogOk = new JOptionPane();
								jOptionLogOk.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"conSucc"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"conSuccTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.INFORMATION_MESSAGE);
								// Changement en bouton de déconnexion
								JFrameSmartWater.this.menuCommConnect
										.setLabel("Disconnect");
								break;
							case 1 :
								JOptionPane jOptionTimeoutErr = new JOptionPane();
								jOptionTimeoutErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"timeOut"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"timeOutTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								break;
							case 2 :
								JOptionPane jOptionUserPasswdErr = new JOptionPane();
								jOptionUserPasswdErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"userPassErr"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"userPassErrTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								JFrameSmartWater.this.jFramLog.setVisible(true);
								break;
							case 3 :
								JOptionPane jOptionConnErr = new JOptionPane();
								jOptionConnErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"noPortSel"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"noPortSelTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								JFrameSmartWater.this.jFramePortSel
										.refreshPortAff();
								JFrameSmartWater.this.jFramePortSel
										.setVisible(true);

								break;
							case 4 :
								JOptionPane jOptionUnkErr = new JOptionPane();
								jOptionUnkErr.showConfirmDialog(
										JFrameSmartWater.this,
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"unkErr"),
										(String) JFrameSmartWater.this.language
												.getResBundle().getObject(
														"unkErrTit"),
										JOptionPane.DEFAULT_OPTION,
										JOptionPane.ERROR_MESSAGE);
								JFrameSmartWater.this.jFramePortSel
										.refreshPortAff();
								JFrameSmartWater.this.jFramePortSel
										.setVisible(true);

								break;
							default :

						}
					} catch (Exception e) {

						e.printStackTrace();
					}
				}
			}
		});

		// Définition de l'écouteur à l'aide d'une classe interne anonyme
		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				JOptionPane jOptionpane = new JOptionPane();
				int reponse = jOptionpane
						.showConfirmDialog(
								JFrameSmartWater.this,
								(String) JFrameSmartWater.this.language
										.getResBundle().getObject("exitFrame"),
								(String) JFrameSmartWater.this.language
										.getResBundle().getObject(
												"exitFrameTit"),
								JOptionPane.YES_NO_OPTION,
								JOptionPane.QUESTION_MESSAGE);
				if (reponse == jOptionpane.YES_OPTION) {
					JFrameSmartWater.this.exitSoftware();
					JFrameSmartWater.this.dispose();
				}
				else
				{
					
				}
			}
		});
	}
	private void geometrie() {
		this.setLayout(new BorderLayout());
		this.menuBar = new MenuBar();

		this.jFramePortSel = new JFramePortSel(this.language.getResBundle(),
				this.comUSB, this, this.session);

		this.jFramLog = new JFrameLogin(this.session);

		// Construction du Menu
		this.menuFichier = new Menu((String) this.language.getResBundle()
				.getObject("menuFichier"));
		this.menuAbout = new Menu((String) this.language.getResBundle()
				.getObject("menuAbout"));
		this.menuComm = new Menu((String) this.language.getResBundle()
				.getObject("menuComm"));
		this.menuLogin = new Menu((String) this.language.getResBundle()
				.getObject("menuLogin"));

		// Menu Fichier
		{
			this.menuFichierSave = new MenuItem((String) this.language
					.getResBundle().getObject("menuFichierSave"));
			this.menuFichierOpen = new MenuItem((String) this.language
					.getResBundle().getObject("menuFichierOpen"));
			this.menuFichierExit = new MenuItem((String) this.language
					.getResBundle().getObject("menuFichierExit"));
			this.menuFichier.add(menuFichierOpen);
			this.menuFichier.add(menuFichierSave);
			this.menuFichier.add(menuFichierExit);

			this.menuBar.add(menuFichier);
		}

		// Menu Communication
		{
			this.menuCommSel = new MenuItem((String) this.language
					.getResBundle().getObject("menuCommSel"));
			this.menuComm.add(menuCommSel);

			this.menuCommConnect = new MenuItem((String) this.language
					.getResBundle().getObject("menuCommConnect"));
			this.menuComm.add(menuCommConnect);

			this.menuBar.add(menuComm);
		}

		// Menu login
		{
			this.menuLoginLog = new MenuItem((String) this.language
					.getResBundle().getObject("menuLoginLog"));
			this.menuLogin.add(menuLoginLog);
			this.menuBar.add(menuLogin);
		}

		// Menu About
		{
			this.menuAboutApropos = new MenuItem((String) this.language
					.getResBundle().getObject("menuAboutApropos"));
			this.menuAbout.add(menuAboutApropos);

			this.menuBar.add(menuAbout);
		}

		this.jPanelPrincipal = new JPanelPrincipal(this.parametres,
				this.language.getResBundle(), this.session);

		this.setMenuBar(menuBar);
		this.add(jPanelPrincipal, BorderLayout.CENTER);
	}

	private void apparence() {
		setSize(800, 600);
		setTitle("SmartWater " + SOFT_VERSION);
		setLocation(30, 30);
		setResizable(true);
		this.setBackground(Color.GRAY);

		// Display the window.
		this.setVisible(true);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	private void exitSoftware() {
		if (JFrameSmartWater.this.session.isConnected()) {
			try {
				if (JFrameSmartWater.this.session.isLogged()) {
					JFrameSmartWater.this.session.logOut();
				}
				JFrameSmartWater.this.session.disconnect();
			} catch (Exception e1) {
				e1.printStackTrace();
				System.exit(-1);
			}
		}
	}

	// User + Password
	private Session session;

	// Tools
	private static final String SOFT_VERSION = "v0.1";
	private JLanguages language;

	private ComConnexion comUSB;
	private JFramePortSel jFramePortSel;

	// Login
	private JFrameLogin jFramLog;

	private String userLang;
	private String userCountry;

	// Barre de menu
	private MenuBar menuBar;

	// Panel qui contient les onglet
	private JPanelPrincipal jPanelPrincipal;

	// Menu
	private Menu menuFichier;
	private Menu menuAbout;
	private Menu menuComm;
	private Menu menuLogin;

	// Menu Fichier
	private MenuItem menuFichierOpen;
	private MenuItem menuFichierSave;
	private MenuItem menuFichierExit;
	private MenuItem menuCommSel;
	private MenuItem menuCommConnect;
	private MenuItem menuLoginLog;

	// Menu About
	private MenuItem menuAboutApropos;

	// Travail dur fichier
	private DataManager dataManager;

	Map<String, String> parametres;

}
