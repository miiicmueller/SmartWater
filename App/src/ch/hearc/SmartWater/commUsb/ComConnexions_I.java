
package ch.hearc.SmartWater.commUsb;

/**
 * Le cosntructeur de ComConnexions doit avoir comme paramètre d'entrée un MeteoServiceCallback_I
 */
public interface ComConnexions_I
	{

	public void connect() throws Exception;

	public void disconnect() throws Exception;

	public String getNamePort();

	public void start() throws Exception;
	public void stop() throws Exception;

	}
