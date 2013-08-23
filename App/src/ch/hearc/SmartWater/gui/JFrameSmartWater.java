package ch.hearc.SmartWater.gui;

import java.awt.BorderLayout;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.MenuItem;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Locale;
import java.util.Map;
import java.util.TreeMap;

import javax.swing.JFrame;

import ch.hearc.SmartWater.dataManager.DataManager;
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

		geometrie();
		control();
		apparence();

	}

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/

	private void control() {
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		// Si on appuie sur Quitter
		this.menuFichierExit.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});

		// Si on appuie sur enregistrer
		this.menuFichierSave.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// Appel de la classes enregistrement des
				// paramètres
				parametres.put("NumAlarme", "+417981838565");
				parametres.put("Mode", "4");
				parametres.put("PasswdRoot", "toto");
				parametres.put("PasswdUser", "tata");

				try {
					JFrameSmartWater.this.dataManager.saveFile(parametres);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});

		// Si on appuie sur enregistrer
		this.menuFichierOpen.addActionListener(new ActionListener() {

			@Override
			public void actionPerformed(ActionEvent arg0) {
				// Appel de la classes enregistrement des
				// paramètres
				Map<String, String> parametres = null;

				try {
					JFrameSmartWater.this.dataManager.openFile(parametres);
					JFrameSmartWater.this.jPanelPrincipal.getJPanelParam()
							.updateParams();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		});
	}

	private void geometrie() {
		this.setLayout(new BorderLayout());
		this.menuBar = new MenuBar();

		// Construction du Menu
		this.menuFichier = new Menu((String) this.language.getResBundle()
				.getObject("menuFichier"));
		this.menuAbout = new Menu((String) this.language.getResBundle()
				.getObject("menuAbout"));
		this.menuComm = new Menu((String) this.language.getResBundle()
				.getObject("menuComm"));

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

		// Menu About
		{
			this.menuAboutApropos = new MenuItem((String) this.language
					.getResBundle().getObject("menuAboutApropos"));
			this.menuAbout.add(menuAboutApropos);

			this.menuBar.add(menuAbout);
		}

		this.jPanelPrincipal = new JPanelPrincipal(this.parametres,
				this.language.getResBundle());

		this.setMenuBar(menuBar);
		this.add(jPanelPrincipal, BorderLayout.CENTER);
	}

	private void apparence() {
		setSize(800, 600);
		setTitle("SmartWater " + SOFT_VERSION);
		setLocation(30, 30);
		setResizable(true);

		// Display the window.
		this.setVisible(true);
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private static final String SOFT_VERSION = "v0.1";
	private JLanguages language;

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

	// Menu Fichier
	private MenuItem menuFichierOpen;
	private MenuItem menuFichierSave;
	private MenuItem menuFichierExit;
	private MenuItem menuCommSel;
	private MenuItem menuCommConnect;

	// Menu About
	private MenuItem menuAboutApropos;

	// Travail dur fichier
	private DataManager dataManager;

	Map<String, String> parametres;
}
