package ch.hearc.SmartWater.gui.login;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import ch.hearc.SmartWater.gui.JFrameSmartWater;

public class JFrameLogin extends JFrame implements ActionListener {
	JButton SUBMIT;
	JPanel panel;
	JLabel label1, label2;

	final JTextField text1, text2;

	public JFrameLogin(Session session) {
		this.session = session;
		label1 = new JLabel();
		label1.setText("Username:");
		text1 = new JTextField(1);

		label2 = new JLabel();
		label2.setText("Password:");
		text2 = new JPasswordField(20);

		SUBMIT = new JButton("Ok");

		Box boxPanel = Box.createVerticalBox();
		Box boxBtn = Box.createVerticalBox();
		Box box = Box.createVerticalBox();

		SUBMIT.setPreferredSize(new Dimension(60, 30));
		SUBMIT.setMaximumSize(new Dimension(60, 30));

		panel = new JPanel(new GridLayout(2, 1));
		panel.add(label1);
		panel.add(text1);
		panel.add(label2);
		panel.add(text2);
		JPanel panel2 = new JPanel(new FlowLayout(FlowLayout.CENTER));
		panel2.add(SUBMIT);

		panel.setMaximumSize(new Dimension(350, 100));
		panel.setPreferredSize(new Dimension(350, 100));

		boxPanel.add(panel);
		boxBtn.add(panel2);
		box.add(boxPanel);
		box.add(boxBtn);

		add(box, BorderLayout.CENTER);
		SUBMIT.addActionListener(this);
		this.setTitle("Login");
		this.setSize(250, 170);

		// Display the window.
		this.setVisible(false);
		this.setResizable(true);
		this.setMaximumSize(new Dimension(350, 170));
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		String value1 = text1.getText();
		String value2 = text2.getText();
		this.session.setLogData(value1, value2);

		this.setVisible(false);

	}

	private Session session;

	// User + Password
	private String user;
	private String password;
}
