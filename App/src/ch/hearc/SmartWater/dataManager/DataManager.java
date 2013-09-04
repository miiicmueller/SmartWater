package ch.hearc.SmartWater.dataManager;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;
import java.util.StringTokenizer;

import javax.swing.JFileChooser;

public class DataManager {

	/*------------------------------------------------------------------*\
	|*							Constructeurs							*|
	\*------------------------------------------------------------------*/
	public DataManager() {
		this.fileChooser = new JFileChooser();
	}

	/*------------------------------------------------------------------*\
	|*							Methodes Public							*|
	\*------------------------------------------------------------------*/

	/**
	 * saveFile renvoie un chemin pour travailler sur un fichier
	 * 
	 * @return chemin du fichier
	 * @throws IOException
	 */
	public int saveFile(Map<String, String> parameters) throws IOException {
		switch (this.fileChooser.showSaveDialog(null)) {
			case JFileChooser.CANCEL_OPTION :
				System.out.println("Saving: cancelled");
				return -1;
			case JFileChooser.APPROVE_OPTION :
				File file = this.fileChooser.getSelectedFile();

				// Travail sur le fichier
				File dirParent = file.getParentFile();
				dirParent.mkdirs();

				if (!file.exists()) {
					saveIOText(file.getPath(), parameters);
				} else {
					file.delete();
					saveIOText(file.getPath(), parameters);
				}
				return 0;

			case JFileChooser.ERROR_OPTION :
				return -2;

			default :
				return -3;

		}
	}

	/**
	 * openFile renvoie un chemin pour travailler sur un fichier
	 * 
	 * @return
	 * @throws IOException
	 */
	public int openFile(Map<String, String> parameters) throws IOException {
		switch (this.fileChooser.showOpenDialog(null)) {
			case JFileChooser.CANCEL_OPTION :
				System.out.println("Opening: cancelled");
				return -1;
			case JFileChooser.APPROVE_OPTION :
				File file = this.fileChooser.getSelectedFile();

				if (!file.exists()) {
					return -4;
				} else {
					loadIOText(file.getPath(), parameters);
				}
				return 0;

			case JFileChooser.ERROR_OPTION :
				return -2;

			default :
				return -3;

		}
	}

	/*------------------------------*\
	|*				Set				*|
	\*------------------------------*/

	/*------------------------------*\
	|*				Get				*|
	\*------------------------------*/

	/*------------------------------------------------------------------*\
	|*							Methodes Private						*|
	\*------------------------------------------------------------------*/
	private static void saveIOText(String fileName,
			Map<String, String> parametersMap) throws IOException {
		// Les poupée russe
		FileWriter fw = new FileWriter(fileName);
		BufferedWriter bw = new BufferedWriter(fw);

		// On enregistre la map
		Set<Entry<String, String>> entry = parametersMap.entrySet(); // Ensemble
																		// des
																		// lignes
																		// du
																		// dico
		for (Entry<String, String> ligne : entry) {
			String key = ligne.getKey();
			String valeur = ligne.getValue();

			bw.write(key + SEPARATEUR + valeur + "\r\n");
		}

		bw.close();
		fw.close();
	}

	private static void loadIOText(String fileName,
			Map<String, String> parameters) throws IOException {
		FileReader fr = new FileReader(fileName);
		BufferedReader br = new BufferedReader(fr);

		String ligne;
		//parameters.clear();

		// Lecture première ligne
		ligne = br.readLine();

		// On itère
		while (ligne != null) {

			// Parsing
			StringTokenizer parser = new StringTokenizer(ligne, SEPARATEUR);
			parameters.put(parser.nextToken(), parser.nextToken());
			// Lire ligne suivante
			ligne = br.readLine();
		}

		br.close();
		fr.close();
		System.out.println(parameters);
		return;
	}

	/*------------------------------------------------------------------*\
	|*							Attributs Private						*|
	\*------------------------------------------------------------------*/

	// Tools
	private JFileChooser fileChooser;

	private static final String SEPARATEUR = "=";
}
