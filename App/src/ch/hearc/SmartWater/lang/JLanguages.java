package ch.hearc.SmartWater.lang;

import java.util.Enumeration;
import java.util.Locale;
import java.util.ResourceBundle;
import ch.hearc.SmartWater.lang.*;

public class JLanguages
	{

		public JLanguages(Locale aLocale)
			{
				this.currentLocale = aLocale;
				labels = ResourceBundle.getBundle(
						"ch.hearc.SmartWater.lang.ressources.LabelsBundle",
						this.currentLocale);
			};

		public Locale[] getAvailableLocale()
			{
				Locale[] supportedLocales =
					{ Locale.FRENCH, Locale.GERMAN };
				return supportedLocales;
			}

		public ResourceBundle getResBundle()
			{
				return this.labels;
			}

		// Input
		Locale currentLocale;
		// Tools
		private ResourceBundle labels;

	}
