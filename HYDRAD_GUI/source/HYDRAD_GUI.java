package GUI;

import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.DefaultComboBoxModel;
import javax.swing.DefaultListModel;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.GroupLayout.ParallelGroup;
import javax.swing.GroupLayout.SequentialGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.ListModel;

public class HYDRAD_GUI extends JFrame
{
  private JPanel collisionsPanel;
  private JPanel gravityPanel;
  private JPanel gridPanel;
  private JPanel heatingPanel;
  private JPanel initialconditionsPanel;
  private JButton jButton1;
  private JButton jButton10;
  private JButton jButton11;
  private JButton jButton12;
  private JButton jButton13;
  private JButton jButton2;
  private JButton jButton3;
  private JButton jButton4;
  private JButton jButton5;
  private JButton jButton6;
  private JButton jButton7;
  private JButton jButton8;
  private JButton jButton9;
  private JCheckBox jCheckBox1;
  private JCheckBox jCheckBox10;
  private JCheckBox jCheckBox11;
  private JCheckBox jCheckBox12;
  private JCheckBox jCheckBox13;
  private JCheckBox jCheckBox14;
  private JCheckBox jCheckBox15;
  private JCheckBox jCheckBox16;
  private JCheckBox jCheckBox17;
  private JCheckBox jCheckBox18;
  private JCheckBox jCheckBox19;
  private JCheckBox jCheckBox2;
  private JCheckBox jCheckBox20;
  private JCheckBox jCheckBox21;
  private JCheckBox jCheckBox22;
  private JCheckBox jCheckBox23;
  private JCheckBox jCheckBox3;
  private JCheckBox jCheckBox4;
  private JCheckBox jCheckBox5;
  private JCheckBox jCheckBox6;
  private JCheckBox jCheckBox7;
  private JCheckBox jCheckBox8;
  private JCheckBox jCheckBox9;
  private JComboBox jComboBox1;
  private JComboBox jComboBox3;
  private JComboBox jComboBox4;
  private JFileChooser jFileChooser1;
  private JLabel jLabel1;
  private JLabel jLabel10;
  private JLabel jLabel100;
  private JLabel jLabel101;
  private JLabel jLabel102;
  private JLabel jLabel103;
  private JLabel jLabel104;
  private JLabel jLabel105;
  private JLabel jLabel106;
  private JLabel jLabel109;
  private JLabel jLabel11;
  private JLabel jLabel110;
  private JLabel jLabel111;
  private JLabel jLabel112;
  private JLabel jLabel113;
  private JLabel jLabel116;
  private JLabel jLabel12;
  private JLabel jLabel13;
  private JLabel jLabel14;
  private JLabel jLabel15;
  private JLabel jLabel16;
  private JLabel jLabel17;
  private JLabel jLabel18;
  private JLabel jLabel2;
  private JLabel jLabel20;
  private JLabel jLabel21;
  private JLabel jLabel22;
  private JLabel jLabel23;
  private JLabel jLabel29;
  private JLabel jLabel3;
  private JLabel jLabel30;
  private JLabel jLabel31;
  private JLabel jLabel32;
  private JLabel jLabel33;
  private JLabel jLabel34;
  private JLabel jLabel35;
  private JLabel jLabel36;
  private JLabel jLabel37;
  private JLabel jLabel38;
  private JLabel jLabel39;
  private JLabel jLabel4;
  private JLabel jLabel40;
  private JLabel jLabel41;
  private JLabel jLabel42;
  private JLabel jLabel43;
  private JLabel jLabel44;
  private JLabel jLabel45;
  private JLabel jLabel46;
  private JLabel jLabel47;
  private JLabel jLabel48;
  private JLabel jLabel49;
  private JLabel jLabel5;
  private JLabel jLabel50;
  private JLabel jLabel51;
  private JLabel jLabel52;
  private JLabel jLabel53;
  private JLabel jLabel54;
  private JLabel jLabel55;
  private JLabel jLabel56;
  private JLabel jLabel57;
  private JLabel jLabel58;
  private JLabel jLabel59;
  private JLabel jLabel6;
  private JLabel jLabel60;
  private JLabel jLabel61;
  private JLabel jLabel62;
  private JLabel jLabel63;
  private JLabel jLabel64;
  private JLabel jLabel65;
  private JLabel jLabel66;
  private JLabel jLabel67;
  private JLabel jLabel68;
  private JLabel jLabel69;
  private JLabel jLabel7;
  private JLabel jLabel70;
  private JLabel jLabel71;
  private JLabel jLabel72;
  private JLabel jLabel75;
  private JLabel jLabel76;
  private JLabel jLabel77;
  private JLabel jLabel78;
  private JLabel jLabel79;
  private JLabel jLabel8;
  private JLabel jLabel80;
  private JLabel jLabel82;
  private JLabel jLabel83;
  private JLabel jLabel84;
  private JLabel jLabel85;
  private JLabel jLabel9;
  private JLabel jLabel91;
  private JLabel jLabel92;
  private JLabel jLabel93;
  private JLabel jLabel94;
  private JLabel jLabel95;
  private JLabel jLabel96;
  private JLabel jLabel97;
  private JLabel jLabel98;
  private JLabel jLabel99;
  private JList jList4;
  private JList jList5;
  private JList jList6;
  private JPanel jPanel5;
  private JPanel jPanel6;
  private JPanel jPanel7;
  private JScrollPane jScrollPane4;
  private JScrollPane jScrollPane5;
  private JScrollPane jScrollPane6;
  private JTabbedPane jTabbedPane1;
  private JTabbedPane jTabbedPane2;
  private JTabbedPane jTabbedPane3;
  private JTextField jTextField1;
  private JTextField jTextField10;
  private JTextField jTextField11;
  private JTextField jTextField12;
  private JTextField jTextField13;
  private JTextField jTextField14;
  private JTextField jTextField15;
  private JTextField jTextField16;
  private JTextField jTextField17;
  private JTextField jTextField18;
  private JTextField jTextField19;
  private JTextField jTextField2;
  private JTextField jTextField20;
  private JTextField jTextField21;
  private JTextField jTextField22;
  private JTextField jTextField23;
  private JTextField jTextField24;
  private JTextField jTextField25;
  private JTextField jTextField26;
  private JTextField jTextField27;
  private JTextField jTextField28;
  private JTextField jTextField29;
  private JTextField jTextField3;
  private JTextField jTextField30;
  private JTextField jTextField31;
  private JTextField jTextField32;
  private JTextField jTextField33;
  private JTextField jTextField35;
  private JTextField jTextField38;
  private JTextField jTextField4;
  private JTextField jTextField42;
  private JTextField jTextField43;
  private JTextField jTextField44;
  private JTextField jTextField45;
  private JTextField jTextField46;
  private JTextField jTextField47;
  private JTextField jTextField49;
  private JTextField jTextField5;
  private JTextField jTextField50;
  private JTextField jTextField51;
  private JTextField jTextField52;
  private JTextField jTextField54;
  private JTextField jTextField6;
  private JPanel outputPanel;
  private JPanel physicsPanel;
  private JPanel radiationPanel;
  private JPanel runPanel;
  private JPanel solverPanel;
  private JPanel thermalconductionPanel;
  private static int iMaxNumHeatingEvents = 100;
  private int iNumHeatingEvents = 0;
  private int iCurrentHeatingEvent = 0;
  private CHeatingEvent[] HeatingEvent = new CHeatingEvent[iMaxNumHeatingEvents];
  private DefaultListModel lmEmissivityFilesListModel;
  private DefaultListModel lmAbundanceFilesListModel;
  private DefaultListModel lmRateFilesListModel;
  private static int iMaxNumElements = 30;
  private int iNumEqElements;
  private int iNumNEqElements;
  private String[] szMasterElementsList = { "Hydrogen", "Helium", "Lithium", "Beryllium", "Boron", "Carbon", "Nitrogen", "Oxygen", "Fluorine", "Neon", "Sodium", "Magnesium", "Aluminium", "Silicon", "Phosphorous", "Sulphur", "Chlorine", "Argon", "Potassium", "Calcium", "Scandium", "Titanium", "Vanadium", "Chromium", "Manganese", "Iron", "Cobalt", "Nickel", "Copper", "Zinc" };

  private int[] iMasterElementsListState = new int[iMaxNumElements];
  private String[] szMasterAtomicSymbolsList = { "h", "he", "li", "be", "b", "c", "n", "o", "f", "ne", "na", "mg", "al", "si", "p", "s", "cl", "ar", "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn" };

  public HYDRAD_GUI()
  {
    initComponents();

    initHeatingEvents();
    try
    {
      initEmissivitiesList();
      initAbundancesList();
      initRatesList();
    } catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
    initElementLists();

    String szCurrentDirectory = System.getProperty("user.dir");
    this.jTextField44.setText(szCurrentDirectory + "//HYDRAD_GUI//config//default.cfg");
    try {
      restoreConfigSettings();
    } catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  private void initComponents()
  {
    this.jFileChooser1 = new JFileChooser();
    this.jTabbedPane1 = new JTabbedPane();
    this.runPanel = new JPanel();
    this.jLabel94 = new JLabel();
    this.jTextField44 = new JTextField();
    this.jButton10 = new JButton();
    this.jButton11 = new JButton();
    this.jButton12 = new JButton();
    this.jButton13 = new JButton();
    this.jLabel95 = new JLabel();
    this.jLabel116 = new JLabel();
    this.jCheckBox7 = new JCheckBox();
    this.jLabel98 = new JLabel();
    this.jTextField54 = new JTextField();
    this.initialconditionsPanel = new JPanel();
    this.jTabbedPane3 = new JTabbedPane();
    this.jPanel6 = new JPanel();
    this.jLabel2 = new JLabel();
    this.jLabel4 = new JLabel();
    this.jTextField3 = new JTextField();
    this.jTextField1 = new JTextField();
    this.jLabel9 = new JLabel();
    this.jLabel17 = new JLabel();
    this.jLabel96 = new JLabel();
    this.jTextField45 = new JTextField();
    this.jLabel97 = new JLabel();
    this.jPanel5 = new JPanel();
    this.jLabel20 = new JLabel();
    this.jTextField5 = new JTextField();
    this.jLabel21 = new JLabel();
    this.jLabel22 = new JLabel();
    this.jTextField6 = new JTextField();
    this.jLabel23 = new JLabel();
    this.jCheckBox6 = new JCheckBox();
    this.jPanel7 = new JPanel();
    this.jLabel29 = new JLabel();
    this.jLabel30 = new JLabel();
    this.jLabel31 = new JLabel();
    this.jLabel32 = new JLabel();
    this.jLabel33 = new JLabel();
    this.jLabel34 = new JLabel();
    this.jTextField11 = new JTextField();
    this.jTextField12 = new JTextField();
    this.jTextField13 = new JTextField();
    this.jTextField14 = new JTextField();
    this.jTextField15 = new JTextField();
    this.jLabel35 = new JLabel();
    this.jLabel36 = new JLabel();
    this.jLabel37 = new JLabel();
    this.jLabel38 = new JLabel();
    this.jCheckBox22 = new JCheckBox();
    this.jLabel46 = new JLabel();
    this.jLabel47 = new JLabel();
    this.jLabel1 = new JLabel();
    this.jLabel18 = new JLabel();
    this.jTextField4 = new JTextField();
    this.outputPanel = new JPanel();
    this.jLabel39 = new JLabel();
    this.jLabel40 = new JLabel();
    this.jLabel41 = new JLabel();
    this.jTextField10 = new JTextField();
    this.jTextField16 = new JTextField();
    this.jTextField17 = new JTextField();
    this.jLabel42 = new JLabel();
    this.jLabel43 = new JLabel();
    this.jCheckBox2 = new JCheckBox();
    this.jLabel44 = new JLabel();
    this.jCheckBox3 = new JCheckBox();
    this.jCheckBox4 = new JCheckBox();
    this.jCheckBox5 = new JCheckBox();
    this.jLabel70 = new JLabel();
    this.jTextField19 = new JTextField();
    this.jLabel71 = new JLabel();
    this.physicsPanel = new JPanel();
    this.jTabbedPane2 = new JTabbedPane();
    this.heatingPanel = new JPanel();
    this.jLabel5 = new JLabel();
    this.jLabel10 = new JLabel();
    this.jLabel48 = new JLabel();
    this.jLabel49 = new JLabel();
    this.jLabel50 = new JLabel();
    this.jLabel51 = new JLabel();
    this.jButton1 = new JButton();
    this.jButton2 = new JButton();
    this.jButton3 = new JButton();
    this.jButton4 = new JButton();
    this.jLabel54 = new JLabel();
    this.jTextField22 = new JTextField();
    this.jTextField23 = new JTextField();
    this.jTextField24 = new JTextField();
    this.jTextField25 = new JTextField();
    this.jTextField26 = new JTextField();
    this.jLabel56 = new JLabel();
    this.jLabel57 = new JLabel();
    this.jLabel58 = new JLabel();
    this.jLabel59 = new JLabel();
    this.jLabel60 = new JLabel();
    this.jLabel3 = new JLabel();
    this.jTextField2 = new JTextField();
    this.jLabel6 = new JLabel();
    this.jButton5 = new JButton();
    this.jLabel7 = new JLabel();
    this.jTextField20 = new JTextField();
    this.jLabel8 = new JLabel();
    this.jCheckBox23 = new JCheckBox();
    this.jCheckBox8 = new JCheckBox();
    this.radiationPanel = new JPanel();
    this.jScrollPane4 = new JScrollPane();
    this.jList4 = new JList();
    this.jLabel11 = new JLabel();
    this.jLabel12 = new JLabel();
    this.jButton6 = new JButton();
    this.jButton7 = new JButton();
    this.jScrollPane5 = new JScrollPane();
    this.jList5 = new JList();
    this.jLabel13 = new JLabel();
    this.jScrollPane6 = new JScrollPane();
    this.jList6 = new JList();
    this.jButton8 = new JButton();
    this.jButton9 = new JButton();
    this.jLabel14 = new JLabel();
    this.jLabel15 = new JLabel();
    this.jComboBox3 = new JComboBox();
    this.jLabel16 = new JLabel();
    this.jComboBox4 = new JComboBox();
    this.jCheckBox1 = new JCheckBox();
    this.jLabel72 = new JLabel();
    this.jComboBox1 = new JComboBox();
    this.jCheckBox11 = new JCheckBox();
    this.jCheckBox18 = new JCheckBox();
    this.jCheckBox21 = new JCheckBox();
    this.thermalconductionPanel = new JPanel();
    this.jCheckBox12 = new JCheckBox();
    this.gravityPanel = new JPanel();
    this.jCheckBox14 = new JCheckBox();
    this.jLabel45 = new JLabel();
    this.jTextField18 = new JTextField();
    this.collisionsPanel = new JPanel();
    this.jLabel52 = new JLabel();
    this.jTextField21 = new JTextField();
    this.jLabel53 = new JLabel();
    this.jCheckBox17 = new JCheckBox();
    this.solverPanel = new JPanel();
    this.jLabel55 = new JLabel();
    this.jLabel61 = new JLabel();
    this.jLabel62 = new JLabel();
    this.jLabel63 = new JLabel();
    this.jLabel64 = new JLabel();
    this.jLabel65 = new JLabel();
    this.jTextField27 = new JTextField();
    this.jTextField28 = new JTextField();
    this.jTextField29 = new JTextField();
    this.jTextField30 = new JTextField();
    this.jTextField31 = new JTextField();
    this.jCheckBox19 = new JCheckBox();
    this.jLabel66 = new JLabel();
    this.jTextField32 = new JTextField();
    this.jLabel67 = new JLabel();
    this.jLabel68 = new JLabel();
    this.jTextField33 = new JTextField();
    this.jLabel69 = new JLabel();
    this.jLabel99 = new JLabel();
    this.jTextField46 = new JTextField();
    this.jLabel100 = new JLabel();
    this.jLabel101 = new JLabel();
    this.jLabel102 = new JLabel();
    this.jLabel103 = new JLabel();
    this.jLabel104 = new JLabel();
    this.jTextField47 = new JTextField();
    this.jLabel105 = new JLabel();
    this.jLabel106 = new JLabel();
    this.jLabel109 = new JLabel();
    this.jTextField49 = new JTextField();
    this.jLabel110 = new JLabel();
    this.jTextField50 = new JTextField();
    this.jLabel111 = new JLabel();
    this.jLabel112 = new JLabel();
    this.jLabel113 = new JLabel();
    this.jTextField51 = new JTextField();
    this.jTextField52 = new JTextField();
    this.gridPanel = new JPanel();
    this.jCheckBox20 = new JCheckBox();
    this.jLabel75 = new JLabel();
    this.jTextField35 = new JTextField();
    this.jLabel76 = new JLabel();
    this.jLabel77 = new JLabel();
    this.jLabel78 = new JLabel();
    this.jLabel79 = new JLabel();
    this.jLabel80 = new JLabel();
    this.jLabel83 = new JLabel();
    this.jTextField38 = new JTextField();
    this.jLabel84 = new JLabel();
    this.jLabel91 = new JLabel();
    this.jTextField42 = new JTextField();
    this.jLabel92 = new JLabel();
    this.jTextField43 = new JTextField();
    this.jLabel93 = new JLabel();
    this.jLabel82 = new JLabel();
    this.jLabel85 = new JLabel();
    this.jCheckBox9 = new JCheckBox();
    this.jCheckBox10 = new JCheckBox();
    this.jCheckBox13 = new JCheckBox();
    this.jCheckBox15 = new JCheckBox();
    this.jCheckBox16 = new JCheckBox();

    setDefaultCloseOperation(3);
    setTitle("HYDRAD Configuration Options");
    setResizable(false);

    this.jLabel94.setText("Path and filename of configuration settings:");

    this.jButton10.setText("Open");
    this.jButton10.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton10ActionPerformed(evt);
      }
    });
    this.jButton11.setText("Save");
    this.jButton11.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton11ActionPerformed(evt);
      }
    });
    this.jButton12.setText("Generate Initial Conditions");
    this.jButton12.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton12ActionPerformed(evt);
      }
    });
    this.jButton13.setText("Launch HYDRAD");
    this.jButton13.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton13ActionPerformed(evt);
      }
    });
    this.jLabel95.setText("____I n i t i a l  C o n d i t i o n s____");

    this.jLabel116.setText("____H Y D R A D____");

    this.jCheckBox7.setText("Use default initial conditions");
    this.jCheckBox7.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox7ActionPerformed(evt);
      }
    });
    this.jLabel98.setText("Alternative initial conditions path and filename (no spaces):");

    this.jTextField54.addFocusListener(new FocusAdapter() {
      public void focusGained(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField54FocusGained(evt);
      }
    });
    GroupLayout runPanelLayout = new GroupLayout(this.runPanel);
    this.runPanel.setLayout(runPanelLayout);
    runPanelLayout.setHorizontalGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(runPanelLayout.createSequentialGroup().addContainerGap().addGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox7).addComponent(this.jLabel94).addGroup(runPanelLayout.createSequentialGroup().addGap(10, 10, 10).addGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField44, -2, 511, -2).addGroup(runPanelLayout.createSequentialGroup().addComponent(this.jButton10).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton11)))).addComponent(this.jLabel95).addComponent(this.jLabel116).addGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING, false).addComponent(this.jButton13, GroupLayout.Alignment.LEADING, -1, -1, 32767).addComponent(this.jButton12, GroupLayout.Alignment.LEADING, -1, -1, 32767)).addGroup(runPanelLayout.createSequentialGroup().addGap(24, 24, 24).addGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField54, -1, 499, 32767).addComponent(this.jLabel98)))).addGap(18, 18, 18)));

    runPanelLayout.linkSize(0, new Component[] { this.jButton10, this.jButton11 });

    runPanelLayout.setVerticalGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(runPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jLabel94).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jTextField44, -2, -1, -2).addGap(11, 11, 11).addGroup(runPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jButton10).addComponent(this.jButton11)).addGap(26, 26, 26).addComponent(this.jLabel95).addGap(18, 18, 18).addComponent(this.jButton12).addGap(38, 38, 38).addComponent(this.jLabel116).addGap(18, 18, 18).addComponent(this.jButton13).addGap(18, 18, 18).addComponent(this.jCheckBox7).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel98).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField54, -2, -1, -2).addGap(254, 254, 254)));

    this.jTabbedPane1.addTab("Files", this.runPanel);

    this.jLabel2.setText("Loop length:");

    this.jLabel4.setText("Foot-point height:");

    this.jTextField1.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField1ActionPerformed(evt);
      }
    });
    this.jTextField1.addFocusListener(new FocusAdapter() {
      public void focusLost(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField1FocusLost(evt);
      }
    });
    this.jLabel9.setText("cm");

    this.jLabel17.setText("cm");

    this.jLabel96.setText("Loop inclination from the vertical direction:");

    this.jLabel97.setText("degrees");

    GroupLayout jPanel6Layout = new GroupLayout(this.jPanel6);
    this.jPanel6.setLayout(jPanel6Layout);
    jPanel6Layout.setHorizontalGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel6Layout.createSequentialGroup().addContainerGap().addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel6Layout.createSequentialGroup().addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel2).addComponent(this.jLabel4)).addGap(12, 12, 12).addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel6Layout.createSequentialGroup().addComponent(this.jTextField1, -2, 90, -2).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel9)).addGroup(jPanel6Layout.createSequentialGroup().addComponent(this.jTextField3, -2, -1, -2).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel17)))).addGroup(jPanel6Layout.createSequentialGroup().addComponent(this.jLabel96).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField45, -2, 84, -2).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel97))).addContainerGap(196, 32767)));

    jPanel6Layout.linkSize(0, new Component[] { this.jTextField1, this.jTextField3 });

    jPanel6Layout.setVerticalGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel6Layout.createSequentialGroup().addContainerGap().addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextField1, -2, -1, -2).addComponent(this.jLabel2).addComponent(this.jLabel9)).addGap(18, 18, 18).addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel4).addComponent(this.jTextField3, -2, -1, -2).addComponent(this.jLabel17)).addGap(18, 18, 18).addGroup(jPanel6Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel96).addComponent(this.jTextField45, -2, -1, -2).addComponent(this.jLabel97)).addContainerGap(471, 32767)));

    this.jTabbedPane3.addTab("Geometrical Properties", this.jPanel6);

    this.jLabel20.setText("Foot-point temperature:");

    this.jTextField5.addFocusListener(new FocusAdapter() {
      public void focusLost(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField5FocusLost(evt);
      }
    });
    this.jLabel21.setText("K");

    this.jLabel22.setText("Foot-point density");

    this.jLabel23.setText("/ cm^3");

    this.jCheckBox6.setText("Isothermal initial conditions");
    this.jCheckBox6.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox6ActionPerformed(evt);
      }
    });
    GroupLayout jPanel5Layout = new GroupLayout(this.jPanel5);
    this.jPanel5.setLayout(jPanel5Layout);
    jPanel5Layout.setHorizontalGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel5Layout.createSequentialGroup().addContainerGap().addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox6).addGroup(jPanel5Layout.createSequentialGroup().addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel22).addComponent(this.jLabel20)).addGap(12, 12, 12).addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING, false).addComponent(this.jTextField6).addComponent(this.jTextField5, -2, 87, -2)).addGap(10, 10, 10).addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel23).addComponent(this.jLabel21)))).addContainerGap(276, 32767)));

    jPanel5Layout.setVerticalGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel5Layout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox6).addGap(18, 18, 18).addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextField5, -2, -1, -2).addComponent(this.jLabel20).addComponent(this.jLabel21)).addGap(20, 20, 20).addGroup(jPanel5Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel22).addComponent(this.jTextField6, -2, -1, -2).addComponent(this.jLabel23)).addContainerGap(470, 32767)));

    this.jTabbedPane3.addTab("Boundary Conditions", this.jPanel5);

    this.jLabel29.setText("Heating properties");

    this.jLabel30.setText("Min. (log_10 order of magnitude):");

    this.jLabel31.setText("Max. (log_10 order of magnitude):");

    this.jLabel32.setText("Heating location:");

    this.jLabel33.setText("Heating scale length:");

    this.jLabel34.setText("Log space search step size:");

    this.jTextField12.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField12ActionPerformed(evt);
      }
    });
    this.jTextField12.addFocusListener(new FocusAdapter() {
      public void focusLost(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField12FocusLost(evt);
      }
    });
    this.jTextField15.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField15ActionPerformed(evt);
      }
    });
    this.jLabel35.setText("cm");

    this.jLabel36.setText("cm");

    this.jLabel37.setText("erg / cm^3 / s");

    this.jLabel38.setText("erg / cm^3 / s");

    this.jCheckBox22.setText("Uniform heating");
    this.jCheckBox22.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox22ActionPerformed(evt);
      }
    });
    this.jLabel46.setText("(");

    this.jLabel47.setText(")");

    this.jLabel1.setText("dex");

    this.jLabel18.setText("Linear space fine tune intervals:");

    GroupLayout jPanel7Layout = new GroupLayout(this.jPanel7);
    this.jPanel7.setLayout(jPanel7Layout);
    jPanel7Layout.setHorizontalGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.TRAILING, jPanel7Layout.createSequentialGroup().addContainerGap().addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.TRAILING).addGroup(GroupLayout.Alignment.LEADING, jPanel7Layout.createSequentialGroup().addGap(12, 12, 12).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.TRAILING, jPanel7Layout.createSequentialGroup().addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel30).addComponent(this.jLabel31).addComponent(this.jLabel34).addComponent(this.jLabel18)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, -1, 32767).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel7Layout.createSequentialGroup().addComponent(this.jTextField14, -2, -1, -2).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel38, -1, -1, 32767)).addGroup(jPanel7Layout.createSequentialGroup().addComponent(this.jTextField13, -1, 89, 32767).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel37)).addGroup(jPanel7Layout.createSequentialGroup().addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.TRAILING, false).addComponent(this.jTextField4, GroupLayout.Alignment.LEADING).addComponent(this.jTextField15, GroupLayout.Alignment.LEADING, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel1)))).addGroup(jPanel7Layout.createSequentialGroup().addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel7Layout.createSequentialGroup().addGap(2, 2, 2).addComponent(this.jLabel46).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jCheckBox22).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jLabel47)).addComponent(this.jLabel33)).addGap(269, 269, 269)))).addComponent(this.jLabel29, GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.LEADING, jPanel7Layout.createSequentialGroup().addGap(162, 162, 162).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField11, -2, 89, -2).addComponent(this.jTextField12, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel35).addComponent(this.jLabel36))).addGroup(GroupLayout.Alignment.LEADING, jPanel7Layout.createSequentialGroup().addGap(12, 12, 12).addComponent(this.jLabel32))).addGap(144, 144, 144)));

    jPanel7Layout.linkSize(0, new Component[] { this.jTextField11, this.jTextField12, this.jTextField13, this.jTextField14, this.jTextField15 });

    jPanel7Layout.setVerticalGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanel7Layout.createSequentialGroup().addContainerGap().addComponent(this.jLabel29).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.TRAILING, jPanel7Layout.createSequentialGroup().addComponent(this.jLabel33).addGap(5, 5, 5)).addGroup(jPanel7Layout.createSequentialGroup().addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextField11, -2, -1, -2).addComponent(this.jLabel35).addComponent(this.jLabel32)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextField12, -2, -1, -2).addComponent(this.jLabel36)))).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel47).addComponent(this.jLabel46).addComponent(this.jCheckBox22)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel30).addComponent(this.jTextField13, -2, -1, -2).addComponent(this.jLabel37)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextField14, -2, -1, -2).addComponent(this.jLabel31).addComponent(this.jLabel38)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel34).addComponent(this.jTextField15, -2, -1, -2).addComponent(this.jLabel1)).addGap(18, 18, 18).addGroup(jPanel7Layout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel18).addComponent(this.jTextField4, -2, -1, -2)).addContainerGap(346, 32767)));

    this.jTabbedPane3.addTab("Parameter Space", this.jPanel7);

    GroupLayout initialconditionsPanelLayout = new GroupLayout(this.initialconditionsPanel);
    this.initialconditionsPanel.setLayout(initialconditionsPanelLayout);
    initialconditionsPanelLayout.setHorizontalGroup(initialconditionsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane3));

    initialconditionsPanelLayout.setVerticalGroup(initialconditionsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane3));

    this.jTabbedPane1.addTab("Initial Conditions", this.initialconditionsPanel);

    this.jLabel39.setText("Output results every");

    this.jLabel40.setText("Initial conditions output path and filename:");

    this.jLabel41.setText("Run time:");

    this.jTextField10.setMaximumSize(new Dimension(6, 20));

    this.jLabel42.setText("s");

    this.jLabel43.setText("s");

    this.jCheckBox2.setText("Primitive variables");

    this.jLabel44.setText("Output data");

    this.jCheckBox3.setText("Ion populations");

    this.jCheckBox4.setText("Time scales");

    this.jCheckBox5.setText("Equation terms");

    this.jLabel70.setText("Show progress every");

    this.jLabel71.setText("time steps");

    GroupLayout outputPanelLayout = new GroupLayout(this.outputPanel);
    this.outputPanel.setLayout(outputPanelLayout);
    outputPanelLayout.setHorizontalGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(outputPanelLayout.createSequentialGroup().addContainerGap().addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(outputPanelLayout.createSequentialGroup().addGap(12, 12, 12).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox2).addComponent(this.jCheckBox3).addComponent(this.jCheckBox4).addComponent(this.jCheckBox5))).addComponent(this.jLabel40).addGroup(outputPanelLayout.createSequentialGroup().addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addGroup(outputPanelLayout.createSequentialGroup().addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel39).addComponent(this.jLabel41)).addGap(12, 12, 12).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING, false).addComponent(this.jTextField17).addComponent(this.jTextField16, -1, 87, 32767))).addComponent(this.jTextField19, -2, 85, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel42).addComponent(this.jLabel43).addComponent(this.jLabel71))).addComponent(this.jLabel44).addComponent(this.jLabel70).addGroup(outputPanelLayout.createSequentialGroup().addGap(10, 10, 10).addComponent(this.jTextField10, -2, 511, -2))).addGap(20, 20, 20)));

    outputPanelLayout.setVerticalGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(outputPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jLabel40).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jTextField10, -2, -1, -2).addGap(18, 18, 18).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel41).addComponent(this.jTextField16, -2, -1, -2).addComponent(this.jLabel42)).addGap(18, 18, 18).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel39).addComponent(this.jTextField17, -2, -1, -2).addComponent(this.jLabel43)).addGap(18, 18, 18).addComponent(this.jLabel44).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jCheckBox2).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jCheckBox3).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jCheckBox4).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jCheckBox5).addGap(18, 18, 18).addGroup(outputPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel70).addComponent(this.jLabel71).addComponent(this.jTextField19, -2, -1, -2)).addContainerGap(305, 32767)));

    this.jTabbedPane1.addTab("Output", this.outputPanel);

    this.jLabel5.setText("Dynamic heating event");

    this.jLabel10.setText("Volumetric heating rate:");

    this.jLabel48.setText("Spatial location:");

    this.jLabel49.setText("Spatial scale:");

    this.jLabel50.setText("Temporal scale (rise phase):");

    this.jLabel51.setText("Temporal scale (decay phase):");

    this.jButton1.setText("Add event");
    this.jButton1.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton1ActionPerformed(evt);
      }
    });
    this.jButton2.setText("Remove event");
    this.jButton2.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton2ActionPerformed(evt);
      }
    });
    this.jButton3.setText("Next event");
    this.jButton3.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton3ActionPerformed(evt);
      }
    });
    this.jButton4.setText("Previous event");
    this.jButton4.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton4ActionPerformed(evt);
      }
    });
    this.jLabel54.setText("0/0");

    this.jLabel56.setText("erg / cm^3 / s");

    this.jLabel57.setText("cm");

    this.jLabel58.setText("cm");

    this.jLabel59.setText("s");

    this.jLabel60.setText("s");

    this.jLabel3.setText("Total duration of heating event:");

    this.jLabel6.setText("s");

    this.jButton5.setText("Modify event");
    this.jButton5.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton5ActionPerformed(evt);
      }
    });
    this.jLabel7.setText("Onset time:");

    this.jLabel8.setText("s");

    this.jCheckBox23.setText("Background heating");

    this.jCheckBox8.setText("Preferentially heat electrons");

    GroupLayout heatingPanelLayout = new GroupLayout(this.heatingPanel);
    this.heatingPanel.setLayout(heatingPanelLayout);
    heatingPanelLayout.setHorizontalGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(heatingPanelLayout.createSequentialGroup().addContainerGap().addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(heatingPanelLayout.createSequentialGroup().addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel10).addComponent(this.jLabel48).addComponent(this.jLabel49).addComponent(this.jLabel7).addComponent(this.jLabel3).addComponent(this.jLabel50).addComponent(this.jLabel51)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField22, -1, 86, 32767).addComponent(this.jTextField23, -1, 86, 32767).addComponent(this.jTextField24, -2, -1, -2).addComponent(this.jTextField20, -2, -1, -2).addComponent(this.jTextField2, -2, -1, -2).addComponent(this.jTextField25, -2, -1, -2).addComponent(this.jTextField26, -1, 86, 32767)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel57).addComponent(this.jLabel56).addComponent(this.jLabel58).addComponent(this.jLabel8).addComponent(this.jLabel6).addComponent(this.jLabel59).addComponent(this.jLabel60))).addComponent(this.jCheckBox23).addGroup(heatingPanelLayout.createSequentialGroup().addGap(2, 2, 2).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(heatingPanelLayout.createSequentialGroup().addComponent(this.jLabel5).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabel54)).addGroup(heatingPanelLayout.createSequentialGroup().addComponent(this.jButton4).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton3)).addComponent(this.jCheckBox8).addGroup(heatingPanelLayout.createSequentialGroup().addComponent(this.jButton1).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton5).addGap(18, 18, 18).addComponent(this.jButton2))))).addGap(696, 696, 696)));

    heatingPanelLayout.linkSize(0, new Component[] { this.jButton1, this.jButton2, this.jButton3, this.jButton4, this.jButton5 });

    heatingPanelLayout.linkSize(0, new Component[] { this.jTextField2, this.jTextField20, this.jTextField22, this.jTextField23, this.jTextField24, this.jTextField25, this.jTextField26 });

    heatingPanelLayout.setVerticalGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(heatingPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox23).addGap(18, 18, 18).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel5).addComponent(this.jLabel54)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jButton4).addComponent(this.jButton3)).addGap(18, 18, 18).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel10).addComponent(this.jTextField22, -2, -1, -2).addComponent(this.jLabel56)).addGap(10, 10, 10).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel48).addComponent(this.jTextField23, -2, -1, -2).addComponent(this.jLabel57)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel49).addComponent(this.jTextField24, -2, -1, -2).addComponent(this.jLabel58)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel7).addComponent(this.jTextField20, -2, 22, -2).addComponent(this.jLabel8)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel3).addComponent(this.jTextField2, -2, -1, -2).addComponent(this.jLabel6)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel50).addComponent(this.jTextField25, -2, -1, -2).addComponent(this.jLabel59)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel51).addComponent(this.jTextField26, -2, -1, -2).addComponent(this.jLabel60)).addGap(18, 18, 18).addGroup(heatingPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jButton1).addComponent(this.jButton5).addComponent(this.jButton2)).addGap(28, 28, 28).addComponent(this.jCheckBox8).addContainerGap(165, 32767)));

    this.jTabbedPane2.addTab("Heating", this.heatingPanel);

    this.jList4.setAutoscrolls(false);
    this.jScrollPane4.setViewportView(this.jList4);

    this.jLabel11.setText("Elements");

    this.jLabel12.setText("Equilibrium");

    this.jButton6.setText("Remove");
    this.jButton6.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton6ActionPerformed(evt);
      }
    });
    this.jButton7.setText("Add");
    this.jButton7.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton7ActionPerformed(evt);
      }
    });
    this.jScrollPane5.setViewportView(this.jList5);

    this.jLabel13.setText("Non-equilibrium");

    this.jScrollPane6.setViewportView(this.jList6);

    this.jButton8.setText("Add");
    this.jButton8.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton8ActionPerformed(evt);
      }
    });
    this.jButton9.setText("Remove");
    this.jButton9.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jButton9ActionPerformed(evt);
      }
    });
    this.jLabel14.setText("Choose the elements to include in the radiation calculation:");

    this.jLabel15.setText("Choose the abundance set:");

    this.jLabel16.setText("Choose the ionisation data:");

    this.jComboBox4.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jComboBox4ActionPerformed(evt);
      }
    });
    this.jCheckBox1.setText("Use power-law approximations for the radiation calculation");
    this.jCheckBox1.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox1ActionPerformed(evt);
      }
    });
    this.jLabel72.setText("Choose the ion emissivities:");

    this.jCheckBox11.setText("Optically-thick photosphere and chromosphere");
    this.jCheckBox11.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox11ActionPerformed(evt);
      }
    });
    this.jCheckBox18.setText("Density dependent ionisation data");
    this.jCheckBox18.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox18ActionPerformed(evt);
      }
    });
    this.jCheckBox21.setText("Solve for the non-equilibrium ionisation state decoupled from the radiation calculation");
    this.jCheckBox21.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox21ActionPerformed(evt);
      }
    });
    GroupLayout radiationPanelLayout = new GroupLayout(this.radiationPanel);
    this.radiationPanel.setLayout(radiationPanelLayout);
    radiationPanelLayout.setHorizontalGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(radiationPanelLayout.createSequentialGroup().addContainerGap().addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox21).addComponent(this.jCheckBox18).addComponent(this.jLabel14).addComponent(this.jCheckBox1).addGroup(radiationPanelLayout.createSequentialGroup().addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel16).addComponent(this.jLabel15).addComponent(this.jLabel72)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jComboBox3, 0, 229, 32767).addComponent(this.jComboBox4, 0, 229, 32767).addComponent(this.jComboBox1, 0, 229, 32767))).addGroup(radiationPanelLayout.createSequentialGroup().addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jScrollPane4, -2, 126, -2).addComponent(this.jLabel11)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel12).addComponent(this.jButton6).addComponent(this.jButton7).addComponent(this.jScrollPane5, -2, 111, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel13).addComponent(this.jScrollPane6, -2, 114, -2).addComponent(this.jButton8).addComponent(this.jButton9))).addComponent(this.jCheckBox11)).addGap(671, 671, 671)));

    radiationPanelLayout.linkSize(0, new Component[] { this.jButton6, this.jButton7, this.jButton8, this.jButton9, this.jScrollPane5, this.jScrollPane6 });

    radiationPanelLayout.linkSize(0, new Component[] { this.jComboBox1, this.jComboBox3, this.jComboBox4 });

    radiationPanelLayout.setVerticalGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(radiationPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox1).addGap(18, 18, 18).addComponent(this.jLabel14).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addGroup(radiationPanelLayout.createSequentialGroup().addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel12).addComponent(this.jLabel11)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addGroup(radiationPanelLayout.createSequentialGroup().addComponent(this.jScrollPane5, -2, 126, -2).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton7).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton6)).addComponent(this.jScrollPane4, -2, 186, -2))).addGroup(radiationPanelLayout.createSequentialGroup().addComponent(this.jLabel13).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jScrollPane6, 0, 0, 32767).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton8).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jButton9))).addGap(20, 20, 20).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel72).addComponent(this.jComboBox1, -2, -1, -2)).addGap(18, 18, 18).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel15).addComponent(this.jComboBox3, -2, -1, -2)).addGap(18, 18, 18).addGroup(radiationPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel16, -2, 24, -2).addComponent(this.jComboBox4, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jCheckBox18).addGap(17, 17, 17).addComponent(this.jCheckBox21).addGap(18, 18, 18).addComponent(this.jCheckBox11).addContainerGap()));

    radiationPanelLayout.linkSize(1, new Component[] { this.jScrollPane5, this.jScrollPane6 });

    this.jTabbedPane2.addTab("Radiation", this.radiationPanel);

    this.jCheckBox12.setText("Use kinetic model");

    GroupLayout thermalconductionPanelLayout = new GroupLayout(this.thermalconductionPanel);
    this.thermalconductionPanel.setLayout(thermalconductionPanelLayout);
    thermalconductionPanelLayout.setHorizontalGroup(thermalconductionPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(thermalconductionPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox12).addContainerGap(1001, 32767)));

    thermalconductionPanelLayout.setVerticalGroup(thermalconductionPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(thermalconductionPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox12).addContainerGap(548, 32767)));

    this.jTabbedPane2.addTab("Thermal Conduction", this.thermalconductionPanel);

    this.jCheckBox14.setText("Use a tabulated function for gravity");
    this.jCheckBox14.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox14ActionPerformed(evt);
      }
    });
    this.jLabel45.setText("Specify path and filename:");

    this.jTextField18.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField18ActionPerformed(evt);
      }
    });
    GroupLayout gravityPanelLayout = new GroupLayout(this.gravityPanel);
    this.gravityPanel.setLayout(gravityPanelLayout);
    gravityPanelLayout.setHorizontalGroup(gravityPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(gravityPanelLayout.createSequentialGroup().addContainerGap().addGroup(gravityPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox14).addGroup(gravityPanelLayout.createSequentialGroup().addGap(12, 12, 12).addComponent(this.jLabel45).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField18, -2, 376, -2))).addContainerGap(588, 32767)));

    gravityPanelLayout.setVerticalGroup(gravityPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(gravityPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox14).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(gravityPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel45).addComponent(this.jTextField18, -2, -1, -2)).addContainerGap(526, 32767)));

    this.jTabbedPane2.addTab("Gravity", this.gravityPanel);

    this.jLabel52.setText("Min. collisional coupling time scale:");

    this.jLabel53.setText("s");

    this.jCheckBox17.setText("Force single-fluid");

    GroupLayout collisionsPanelLayout = new GroupLayout(this.collisionsPanel);
    this.collisionsPanel.setLayout(collisionsPanelLayout);
    collisionsPanelLayout.setHorizontalGroup(collisionsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(collisionsPanelLayout.createSequentialGroup().addContainerGap().addGroup(collisionsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(collisionsPanelLayout.createSequentialGroup().addComponent(this.jLabel52).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jTextField21, -2, 85, -2).addGap(10, 10, 10).addComponent(this.jLabel53)).addComponent(this.jCheckBox17)).addContainerGap(831, 32767)));

    collisionsPanelLayout.setVerticalGroup(collisionsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(collisionsPanelLayout.createSequentialGroup().addContainerGap().addGroup(collisionsPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel52).addComponent(this.jTextField21, -2, -1, -2).addComponent(this.jLabel53)).addGap(18, 18, 18).addComponent(this.jCheckBox17).addContainerGap(506, 32767)));

    this.jTabbedPane2.addTab("Collisions", this.collisionsPanel);

    GroupLayout physicsPanelLayout = new GroupLayout(this.physicsPanel);
    this.physicsPanel.setLayout(physicsPanelLayout);
    physicsPanelLayout.setHorizontalGroup(physicsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane2, -1, 1119, 32767));

    physicsPanelLayout.setVerticalGroup(physicsPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane2));

    this.jTabbedPane1.addTab("Physics", this.physicsPanel);

    this.jLabel55.setText("CFL condition safety coefficients (<=1.0)");

    this.jLabel61.setText("Radiation:");

    this.jLabel62.setText("Atomic processes:");

    this.jLabel63.setText("Thermal conduction:");

    this.jLabel64.setText("Transport:");

    this.jLabel65.setText("Viscosity:");

    this.jTextField28.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField28ActionPerformed(evt);
      }
    });
    this.jTextField29.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField29ActionPerformed(evt);
      }
    });
    this.jCheckBox19.setText("Include artificial viscosity");
    this.jCheckBox19.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox19ActionPerformed(evt);
      }
    });
    this.jLabel66.setText("Damping time scale:");

    this.jLabel67.setText("(in multiples of the CFL transport time step)");

    this.jLabel68.setText("Min. plasma species temperature:");

    this.jTextField33.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField33ActionPerformed(evt);
      }
    });
    this.jLabel69.setText("K");

    this.jLabel99.setText("Limit time-step increases to");

    this.jLabel100.setText("% greater than the previous time-step");

    this.jLabel102.setText("Min. temperature of radiation:");

    this.jLabel104.setText("Decrease to zero over temperature interval:");

    this.jLabel105.setText("K");

    this.jLabel106.setText("K");

    this.jLabel109.setText("Ion fraction cut-off:");

    this.jLabel110.setText("Max. density of optically-thin plasma:");

    this.jLabel111.setText("cm^-3");

    this.jLabel112.setText("Major ion control parameter:");

    this.jLabel113.setText("Minor ion control parameter:");

    GroupLayout solverPanelLayout = new GroupLayout(this.solverPanel);
    this.solverPanel.setLayout(solverPanelLayout);
    solverPanelLayout.setHorizontalGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addContainerGap().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel62).addComponent(this.jLabel61)).addGap(14, 14, 14).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField27, -1, 83, 32767).addComponent(this.jTextField28, -1, 83, 32767))).addGroup(solverPanelLayout.createSequentialGroup().addGap(21, 21, 21).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel102).addComponent(this.jLabel104).addComponent(this.jLabel110)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING, false).addComponent(this.jTextField50).addComponent(this.jTextField47).addComponent(this.jLabel103, -2, 86, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel105, -2, 16, -2).addComponent(this.jLabel106, -2, 14, -2).addComponent(this.jLabel111))).addGroup(solverPanelLayout.createSequentialGroup().addComponent(this.jLabel113).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField52, -2, 84, -2)).addGroup(solverPanelLayout.createSequentialGroup().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel109).addComponent(this.jLabel112)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING, false).addComponent(this.jTextField51).addComponent(this.jTextField49, -1, 82, 32767)))))).addGap(137, 137, 137).addComponent(this.jLabel101)).addGroup(solverPanelLayout.createSequentialGroup().addGap(10, 10, 10).addComponent(this.jLabel55)).addGroup(solverPanelLayout.createSequentialGroup().addContainerGap().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addGap(21, 21, 21).addComponent(this.jLabel66).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField32, -2, -1, -2).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jLabel67)).addComponent(this.jCheckBox19).addGroup(solverPanelLayout.createSequentialGroup().addComponent(this.jLabel68).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField33, -2, -1, -2).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jLabel69)).addGroup(solverPanelLayout.createSequentialGroup().addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel65).addComponent(this.jLabel64).addComponent(this.jLabel63)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField29, -1, 83, 32767).addComponent(this.jTextField30, -1, 83, 32767).addComponent(this.jTextField31, -1, 83, 32767))).addGroup(solverPanelLayout.createSequentialGroup().addComponent(this.jLabel99).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextField46, -2, 83, -2).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jLabel100))))).addContainerGap(-1, 32767)));

    solverPanelLayout.linkSize(0, new Component[] { this.jTextField27, this.jTextField28, this.jTextField29, this.jTextField30, this.jTextField31, this.jTextField32, this.jTextField33 });

    solverPanelLayout.setVerticalGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jLabel55).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(solverPanelLayout.createSequentialGroup().addGap(40, 40, 40).addComponent(this.jLabel101)).addGroup(solverPanelLayout.createSequentialGroup().addGap(18, 18, 18).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel61).addComponent(this.jTextField27, -2, -1, -2)).addGap(16, 16, 16).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel102).addComponent(this.jLabel103, -2, 14, -2).addComponent(this.jLabel106)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel104).addComponent(this.jTextField47, -2, -1, -2).addComponent(this.jLabel105)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel110).addComponent(this.jTextField50, -2, -1, -2).addComponent(this.jLabel111)).addGap(26, 26, 26).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel62).addComponent(this.jTextField28, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel109).addComponent(this.jTextField49, -2, -1, -2)))).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel112).addComponent(this.jTextField51, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel113).addComponent(this.jTextField52, -2, -1, -2)).addGap(28, 28, 28).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel63).addComponent(this.jTextField29, -2, -1, -2)).addGap(18, 18, 18).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel64).addComponent(this.jTextField30, -2, -1, -2)).addGap(18, 18, 18).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel65).addComponent(this.jTextField31, -2, -1, -2)).addGap(24, 24, 24).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel99).addComponent(this.jTextField46, -2, -1, -2).addComponent(this.jLabel100)).addGap(30, 30, 30).addComponent(this.jCheckBox19).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel66).addComponent(this.jTextField32, -2, -1, -2).addComponent(this.jLabel67)).addGap(29, 29, 29).addGroup(solverPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel68).addComponent(this.jLabel69).addComponent(this.jTextField33, -2, -1, -2)).addGap(420, 420, 420)));

    this.jTabbedPane1.addTab("Solver", this.solverPanel);

    this.jCheckBox20.setText("Uniform grid");
    this.jCheckBox20.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox20ActionPerformed(evt);
      }
    });
    this.jLabel75.setText("Min. number of grid cells:");

    this.jTextField35.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jTextField35ActionPerformed(evt);
      }
    });
    this.jTextField35.addFocusListener(new FocusAdapter() {
      public void focusLost(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField35FocusLost(evt);
      }
    });
    this.jLabel76.setText("Min. grid cell width:");

    this.jLabel77.setText("Max. grid cell width:");

    this.jLabel78.setText("cm");

    this.jLabel80.setText("cm");

    this.jLabel83.setText("aim for a difference of <=");

    this.jLabel84.setText("% between quantities in adjacent cells");

    this.jLabel91.setText("Max. refinement levels:");

    this.jTextField42.addFocusListener(new FocusAdapter() {
      public void focusLost(FocusEvent evt) {
        HYDRAD_GUI.this.jTextField42FocusLost(evt);
      }
    });
    this.jLabel92.setText("Aim for a difference of >=");

    this.jLabel93.setText("% and");

    this.jLabel85.setText("Refine on:");

    this.jCheckBox9.setText("Density");

    this.jCheckBox10.setText("Electron energy");

    this.jCheckBox13.setText("Hydrogen energy");
    this.jCheckBox13.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent evt) {
        HYDRAD_GUI.this.jCheckBox13ActionPerformed(evt);
      }
    });
    this.jCheckBox15.setText("Use linear restriction");

    this.jCheckBox16.setText("Enforce conservation upon restriction");

    GroupLayout gridPanelLayout = new GroupLayout(this.gridPanel);
    this.gridPanel.setLayout(gridPanelLayout);
    gridPanelLayout.setHorizontalGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(gridPanelLayout.createSequentialGroup().addContainerGap().addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.TRAILING, gridPanelLayout.createSequentialGroup().addGap(0, 0, 32767).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel75).addComponent(this.jLabel91).addComponent(this.jLabel76).addComponent(this.jLabel77).addComponent(this.jLabel85).addComponent(this.jCheckBox15).addComponent(this.jCheckBox16)).addGap(2, 2, 2).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField35, -1, 87, 32767).addComponent(this.jTextField42, -1, 87, 32767).addComponent(this.jLabel82, -2, 83, -2).addComponent(this.jLabel79, -1, 87, 32767)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel80).addComponent(this.jLabel78)).addGap(302, 302, 302)).addGroup(gridPanelLayout.createSequentialGroup().addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jCheckBox20).addGroup(gridPanelLayout.createSequentialGroup().addGap(21, 21, 21).addComponent(this.jCheckBox9).addGap(18, 18, 18).addComponent(this.jCheckBox10).addGap(18, 18, 18).addComponent(this.jCheckBox13)).addGroup(gridPanelLayout.createSequentialGroup().addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel92).addComponent(this.jLabel83)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTextField43, -1, 87, 32767).addComponent(this.jTextField38, -1, 87, 32767)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabel93).addComponent(this.jLabel84)))).addContainerGap(-1, 32767)))));

    gridPanelLayout.linkSize(0, new Component[] { this.jLabel79, this.jLabel82, this.jTextField35, this.jTextField38, this.jTextField42, this.jTextField43 });

    gridPanelLayout.setVerticalGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(gridPanelLayout.createSequentialGroup().addContainerGap().addComponent(this.jCheckBox20).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel75).addComponent(this.jTextField35, -2, -1, -2)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel91).addComponent(this.jTextField42, -2, -1, -2)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(gridPanelLayout.createSequentialGroup().addComponent(this.jLabel76).addGap(21, 21, 21).addComponent(this.jLabel77).addGap(18, 18, 18).addComponent(this.jLabel85)).addGroup(gridPanelLayout.createSequentialGroup().addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addComponent(this.jLabel78).addComponent(this.jLabel82, -2, 14, -2)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addComponent(this.jLabel79, -2, 17, -2).addComponent(this.jLabel80)))).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jCheckBox9).addComponent(this.jCheckBox10).addComponent(this.jCheckBox13)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel92).addComponent(this.jTextField43, -2, -1, -2).addComponent(this.jLabel93)).addGap(18, 18, 18).addGroup(gridPanelLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabel83).addComponent(this.jTextField38, -2, -1, -2).addComponent(this.jLabel84)).addGap(18, 18, 18).addComponent(this.jCheckBox15).addGap(18, 18, 18).addComponent(this.jCheckBox16).addContainerGap(213, 32767)));

    this.jTabbedPane1.addTab("Grid", this.gridPanel);

    GroupLayout layout = new GroupLayout(getContentPane());
    getContentPane().setLayout(layout);
    layout.setHorizontalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane1, -2, 556, -2));

    layout.setVerticalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jTabbedPane1, -2, 634, -2));

    pack();
  }

  private void checkEnabledStatus() {
    checkFilesEnabledStatus();
    checkGeometricalPropertiesEnabledStatus();
    checkBoundaryConditionsEnabledStatus();
    checkParameterSpaceEnabledStatus();
    checkOutputEnabledStatus();
    checkHeatingEnabledStatus();
    checkRadiationEnabledStatus();
    checkGravityEnabledStatus();
    checkSolverEnabledStatus();
    checkGridEnabledStatus();
  }

  private void initHeatingEvents() {
    for (int i = 0; i < iMaxNumHeatingEvents; i++)
      this.HeatingEvent[i] = new CHeatingEvent();
  }

  private void initEmissivitiesList() throws IOException {
    BufferedReader inputStream = null;

    int iNumEmissivitiesSets = 0;

    DefaultComboBoxModel cbmEmissivitiesListModel = new DefaultComboBoxModel();
    this.jComboBox1.setModel(cbmEmissivitiesListModel);
    this.lmEmissivityFilesListModel = new DefaultListModel();
    try
    {
      inputStream = new BufferedReader(new FileReader("Radiation_Model/atomic_data/emissivities/emissivities.lst"));

      if (inputStream != null) {
        String szBuffer = inputStream.readLine();
        iNumEmissivitiesSets = Integer.valueOf(szBuffer).intValue();
        for (int i = 0; i < iNumEmissivitiesSets; i++) {
          szBuffer = inputStream.readLine();
          cbmEmissivitiesListModel.addElement(szBuffer);
          szBuffer = inputStream.readLine();
          this.lmEmissivityFilesListModel.addElement(szBuffer);
        }
      }
    } finally {
      if (inputStream != null)
        inputStream.close();
    }
  }

  private void initAbundancesList() throws IOException
  {
    BufferedReader inputStream = null;

    int iNumAbundancesSets = 0;

    DefaultComboBoxModel cbmAbundancesListModel = new DefaultComboBoxModel();
    this.jComboBox3.setModel(cbmAbundancesListModel);
    this.lmAbundanceFilesListModel = new DefaultListModel();
    try
    {
      inputStream = new BufferedReader(new FileReader("Radiation_Model/atomic_data/abundances/abundances.lst"));

      if (inputStream != null) {
        String szBuffer = inputStream.readLine();
        iNumAbundancesSets = Integer.valueOf(szBuffer).intValue();
        for (int i = 0; i < iNumAbundancesSets; i++) {
          szBuffer = inputStream.readLine();
          cbmAbundancesListModel.addElement(szBuffer);
          szBuffer = inputStream.readLine();
          this.lmAbundanceFilesListModel.addElement(szBuffer);
        }
      }
    } finally {
      if (inputStream != null)
        inputStream.close();
    }
  }

  private void initRatesList() throws IOException
  {
    BufferedReader inputStream = null;

    int iNumRatesSets = 0;

    DefaultComboBoxModel cbmRatesListModel = new DefaultComboBoxModel();
    this.jComboBox4.setModel(cbmRatesListModel);
    this.lmRateFilesListModel = new DefaultListModel();
    try
    {
      inputStream = new BufferedReader(new FileReader("Radiation_Model/atomic_data/rates/rates.lst"));

      if (inputStream != null) {
        String szBuffer = inputStream.readLine();
        iNumRatesSets = Integer.valueOf(szBuffer).intValue();
        for (int i = 0; i < iNumRatesSets; i++) {
          szBuffer = inputStream.readLine();
          cbmRatesListModel.addElement(szBuffer);
          szBuffer = inputStream.readLine();
          this.lmRateFilesListModel.addElement(szBuffer);
        }
      }
    } finally {
      if (inputStream != null)
        inputStream.close();
    }
  }

  private void initElementLists()
  {
    for (int i = 0; i < iMaxNumElements; i++) {
      this.iMasterElementsListState[i] = 0;
    }

    DefaultListModel lmMasterElementsListModel = new DefaultListModel();
    this.jList4.setModel(lmMasterElementsListModel);
    lmMasterElementsListModel.setSize(iMaxNumElements);
    for (int i = 0; i < iMaxNumElements; i++)
      lmMasterElementsListModel.set(i, this.szMasterElementsList[i]);
  }

  private void checkFilesEnabledStatus() {
    if (!this.jCheckBox7.isSelected()) {
      this.jLabel98.setEnabled(true);
      this.jTextField54.setEnabled(true);
    } else {
      this.jLabel98.setEnabled(false);
      this.jTextField54.setEnabled(false);
    }
  }

  private void checkGeometricalPropertiesEnabledStatus() {
    if (this.jCheckBox14.isSelected()) {
      this.jLabel96.setEnabled(false);
      this.jTextField45.setEnabled(false);
      this.jLabel97.setEnabled(false);
    } else {
      this.jLabel96.setEnabled(true);
      this.jTextField45.setEnabled(true);
      this.jLabel97.setEnabled(true);
    }
  }

  private void checkBoundaryConditionsEnabledStatus() {
    if (this.jCheckBox6.isSelected())
      this.jLabel18.setEnabled(false);
    else {
      this.jLabel18.setEnabled(true);
    }
    updateBoundaryConditionsLabels();
  }

  private void updateBoundaryConditionsLabels() {
    if (this.jCheckBox6.isSelected())
      this.jLabel20.setText("Loop temperature:");
    else
      this.jLabel20.setText("Foot-point temperature:");
  }

  private void checkParameterSpaceEnabledStatus()
  {
    if (this.jCheckBox6.isSelected())
    {
      this.jLabel29.setEnabled(false);
      this.jLabel32.setEnabled(false);
      this.jTextField11.setEnabled(false);
      this.jLabel35.setEnabled(false);
      this.jLabel33.setEnabled(false);
      this.jTextField12.setEnabled(false);
      this.jLabel36.setEnabled(false);
      this.jLabel46.setEnabled(false);
      this.jCheckBox22.setEnabled(false);
      this.jLabel47.setEnabled(false);
      this.jLabel30.setEnabled(false);
      this.jTextField13.setEnabled(false);
      this.jLabel37.setEnabled(false);
      this.jLabel31.setEnabled(false);
      this.jTextField14.setEnabled(false);
      this.jLabel38.setEnabled(false);
      this.jLabel34.setEnabled(false);
      this.jTextField15.setEnabled(false);
      this.jLabel1.setEnabled(false);
      this.jLabel8.setEnabled(false);
      this.jTextField4.setEnabled(false);
    }
    else {
      this.jLabel29.setEnabled(true);
      this.jLabel32.setEnabled(true);
      this.jTextField11.setEnabled(true);
      this.jLabel35.setEnabled(true);
      this.jLabel33.setEnabled(true);
      this.jTextField12.setEnabled(true);
      this.jLabel36.setEnabled(true);
      this.jLabel46.setEnabled(true);
      this.jCheckBox22.setEnabled(true);
      this.jLabel47.setEnabled(true);
      this.jLabel30.setEnabled(true);
      this.jTextField13.setEnabled(true);
      this.jLabel37.setEnabled(true);
      this.jLabel31.setEnabled(true);
      this.jTextField14.setEnabled(true);
      this.jLabel38.setEnabled(true);
      this.jLabel34.setEnabled(true);
      this.jTextField15.setEnabled(true);
      this.jLabel1.setEnabled(true);
      this.jLabel8.setEnabled(true);
      this.jTextField4.setEnabled(true);
    }
  }

  private void checkOutputEnabledStatus()
  {
    if (((!this.jCheckBox1.isSelected()) || (this.jCheckBox21.isSelected())) && (this.jList6.getModel().getSize() > 0))
      this.jCheckBox3.setEnabled(true);
    else
      this.jCheckBox3.setEnabled(false);
  }

  private void checkHeatingEnabledStatus()
  {
    if (this.jCheckBox6.isSelected())
      this.jCheckBox23.setEnabled(false);
    else {
      this.jCheckBox23.setEnabled(true);
    }

    this.jLabel5.setEnabled(true);
    this.jLabel54.setEnabled(true);
    this.jLabel10.setEnabled(true);
    this.jTextField22.setEnabled(true);
    this.jLabel56.setEnabled(true);
    this.jLabel48.setEnabled(true);
    this.jTextField23.setEnabled(true);
    this.jLabel57.setEnabled(true);
    this.jLabel49.setEnabled(true);
    this.jTextField24.setEnabled(true);
    this.jLabel58.setEnabled(true);
    this.jLabel7.setEnabled(true);
    this.jTextField20.setEnabled(true);
    this.jLabel8.setEnabled(true);
    this.jLabel3.setEnabled(true);
    this.jTextField2.setEnabled(true);
    this.jLabel6.setEnabled(true);
    this.jLabel50.setEnabled(true);
    this.jTextField25.setEnabled(true);
    this.jLabel59.setEnabled(true);
    this.jLabel51.setEnabled(true);
    this.jTextField26.setEnabled(true);
    this.jLabel60.setEnabled(true);
    this.jButton1.setEnabled(true);
    if (this.iNumHeatingEvents > 0) {
      if (this.iNumHeatingEvents > 1) {
        this.jButton4.setEnabled(true);
        this.jButton3.setEnabled(true);
      } else {
        this.jButton4.setEnabled(false);
        this.jButton3.setEnabled(false);
      }
      this.jButton5.setEnabled(true);
      this.jButton2.setEnabled(true);
      this.jCheckBox8.setEnabled(true);
    } else {
      this.jButton4.setEnabled(false);
      this.jButton3.setEnabled(false);
      this.jButton5.setEnabled(false);
      this.jButton2.setEnabled(false);
      this.jCheckBox8.setEnabled(false);
    }
    updateHeatingPanelTextFields();
  }

  private boolean checkforEmptyHeatingPanelTextFields() {
    if ((this.jTextField22.getText().equals("")) || (this.jTextField23.getText().equals("")) || (this.jTextField24.getText().equals("")) || (this.jTextField20.getText().equals("")) || (this.jTextField2.getText().equals("")) || (this.jTextField25.getText().equals("")) || (this.jTextField26.getText().equals("")))
    {
      return true;
    }
    return false;
  }

  private void updateHeatingPanelTextFields() {
    if (this.iCurrentHeatingEvent == 0) {
      this.jTextField22.setText("");
      this.jTextField23.setText("");
      this.jTextField24.setText("");
      this.jTextField20.setText("");
      this.jTextField2.setText("");
      this.jTextField25.setText("");
      this.jTextField26.setText("");
    }
    else {
      this.jTextField22.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fVHR);
      this.jTextField23.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSL);
      this.jTextField24.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSS);
      this.jTextField20.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fOT);
      this.jTextField2.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTD);
      this.jTextField25.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSRP);
      this.jTextField26.setText("" + this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSDP);
    }

    this.jLabel54.setText(this.iCurrentHeatingEvent + "/" + this.iNumHeatingEvents);
  }

  private void checkRadiationEnabledStatus() {
    if (!this.jCheckBox1.isSelected())
    {
      this.jLabel14.setEnabled(true);
      this.jLabel11.setEnabled(true);
      this.jScrollPane4.setEnabled(true);
      this.jList4.setEnabled(true);
      this.jLabel12.setEnabled(true);
      this.jScrollPane5.setEnabled(true);
      this.jList5.setEnabled(true);
      this.jButton7.setEnabled(true);
      if (this.jList5.getModel().getSize() > 0)
        this.jButton6.setEnabled(true);
      else
        this.jButton6.setEnabled(false);
      this.jLabel13.setEnabled(true);
      this.jScrollPane6.setEnabled(true);
      this.jList6.setEnabled(true);
      this.jButton8.setEnabled(true);
      if (this.jList6.getModel().getSize() > 0)
        this.jButton9.setEnabled(true);
      else {
        this.jButton9.setEnabled(false);
      }
      this.jLabel72.setEnabled(true);
      this.jComboBox1.setEnabled(true);
      this.jLabel15.setEnabled(true);
      this.jComboBox3.setEnabled(true);
      this.jLabel16.setEnabled(true);
      this.jComboBox4.setEnabled(true);

      this.jCheckBox18.setEnabled(true);
    }
    else {
      this.jLabel14.setEnabled(false);
      this.jLabel11.setEnabled(false);
      this.jScrollPane4.setEnabled(false);
      this.jList4.setEnabled(false);
      this.jLabel12.setEnabled(false);
      this.jScrollPane5.setEnabled(false);
      this.jList5.setEnabled(false);
      this.jButton7.setEnabled(false);
      this.jButton6.setEnabled(false);
      this.jLabel13.setEnabled(false);
      this.jScrollPane6.setEnabled(false);
      this.jList6.setEnabled(false);
      this.jButton8.setEnabled(false);
      this.jButton9.setEnabled(false);

      this.jLabel72.setEnabled(false);
      this.jComboBox1.setEnabled(false);
      this.jLabel15.setEnabled(false);
      this.jComboBox3.setEnabled(false);
      this.jLabel16.setEnabled(false);
      this.jComboBox4.setEnabled(false);

      this.jCheckBox18.setEnabled(false);
    }
    updateRadiationLabels();
    setDefaultPropertiesforVALChromosphere();
  }

  private void updateRadiationLabels() {
    this.jLabel11.setText("Elements (" + iMaxNumElements + ")");
    this.jLabel12.setText("Equilibrium (" + this.iNumEqElements + ")");
    this.jLabel13.setText("Non-equilibrium (" + this.iNumNEqElements + ")");
  }

  private void setDefaultPropertiesforVALChromosphere() {
    if (this.jCheckBox11.isSelected())
    {
      this.jTextField3.setText("2.2E8");

      this.jTextField5.setText("2.4E4");

      this.jTextField6.setText("1.932E10");

      this.jLabel102.setEnabled(false);
      this.jLabel103.setEnabled(false);
      this.jLabel106.setEnabled(false);

      this.jLabel104.setEnabled(false);
      this.jTextField47.setEnabled(false);
      this.jLabel105.setEnabled(false);

      this.jCheckBox19.setSelected(true);

      this.jTextField33.setText("4170");
    }
    else
    {
      this.jLabel102.setEnabled(true);
      this.jLabel103.setEnabled(true);
      this.jLabel106.setEnabled(true);

      this.jLabel104.setEnabled(true);
      this.jTextField47.setEnabled(true);
      this.jLabel105.setEnabled(true);
    }
    checkSolverEnabledStatus();
  }

  private void checkGravityEnabledStatus() {
    if (!this.jCheckBox14.isSelected()) {
      this.jLabel45.setEnabled(false);
      this.jTextField18.setEnabled(false);
    } else {
      this.jLabel45.setEnabled(true);
      this.jTextField18.setEnabled(true);
    }
  }

  private void checkSolverEnabledStatus()
  {
    if ((!this.jCheckBox1.isSelected()) || (this.jCheckBox21.isSelected())) {
      if (this.jList6.getModel().getSize() > 0)
      {
        this.jLabel62.setEnabled(true);
        this.jTextField28.setEnabled(true);
        this.jLabel109.setEnabled(true);
        this.jTextField49.setEnabled(true);
        this.jLabel112.setEnabled(true);
        this.jTextField51.setEnabled(true);
        this.jLabel113.setEnabled(true);
        this.jTextField52.setEnabled(true);
      }
      else {
        this.jLabel62.setEnabled(false);
        this.jTextField28.setEnabled(false);
        this.jLabel109.setEnabled(false);
        this.jTextField49.setEnabled(false);
        this.jLabel112.setEnabled(false);
        this.jTextField51.setEnabled(false);
        this.jLabel113.setEnabled(false);
        this.jTextField52.setEnabled(false);
      }
    } else {
      this.jLabel62.setEnabled(false);
      this.jTextField28.setEnabled(false);
      this.jLabel109.setEnabled(false);
      this.jTextField49.setEnabled(false);
      this.jLabel112.setEnabled(false);
      this.jTextField51.setEnabled(false);
      this.jLabel113.setEnabled(false);
      this.jTextField52.setEnabled(false);
    }

    if (!this.jCheckBox19.isSelected()) {
      this.jLabel66.setEnabled(false);
      this.jTextField32.setEnabled(false);
      this.jLabel67.setEnabled(false);
    } else {
      this.jLabel66.setEnabled(true);
      this.jTextField32.setEnabled(true);
      this.jLabel67.setEnabled(true);
    }
    updateSolverLabels();
  }

  private void updateSolverLabels() {
    this.jLabel103.setText(this.jTextField5.getText());
  }

  private void checkGridEnabledStatus() {
    if (!this.jCheckBox20.isSelected()) {
      this.jLabel91.setEnabled(true);
      this.jTextField42.setEnabled(true);
      this.jLabel76.setEnabled(true);
      this.jLabel82.setEnabled(true);
      this.jLabel78.setEnabled(true);
      this.jLabel85.setEnabled(true);
      this.jCheckBox9.setEnabled(true);
      this.jCheckBox10.setEnabled(true);
      this.jCheckBox13.setEnabled(true);
      this.jLabel92.setEnabled(true);
      this.jTextField43.setEnabled(true);
      this.jLabel93.setEnabled(true);
      this.jLabel83.setEnabled(true);
      this.jTextField38.setEnabled(true);
      this.jLabel84.setEnabled(true);
      this.jCheckBox15.setEnabled(true);
      this.jCheckBox16.setEnabled(true);
    } else {
      this.jLabel91.setEnabled(false);
      this.jTextField42.setEnabled(false);
      this.jLabel76.setEnabled(false);
      this.jLabel82.setEnabled(false);
      this.jLabel78.setEnabled(false);
      this.jLabel85.setEnabled(false);
      this.jCheckBox9.setEnabled(false);
      this.jCheckBox10.setEnabled(false);
      this.jCheckBox13.setEnabled(false);
      this.jLabel92.setEnabled(false);
      this.jTextField43.setEnabled(false);
      this.jLabel93.setEnabled(false);
      this.jLabel83.setEnabled(false);
      this.jTextField38.setEnabled(false);
      this.jLabel84.setEnabled(false);
      this.jCheckBox15.setEnabled(false);
      this.jCheckBox16.setEnabled(false);
    }
    updateGridLabels();
  }

  private void updateGridLabels() {
    if (!this.jCheckBox20.isSelected()) {
      this.jLabel75.setText("Min. number of grid cells:");
      this.jLabel77.setText("Max. grid cell width:");
    } else {
      this.jLabel75.setText("Number of grid cells:");
      this.jLabel77.setText("Grid cell width:");
    }
    this.jLabel79.setText("" + Double.valueOf(this.jTextField1.getText()).doubleValue() / Double.valueOf(this.jTextField35.getText()).doubleValue());
    this.jLabel82.setText("" + Double.valueOf(this.jLabel79.getText()).doubleValue() / Math.pow(2.0D, Double.valueOf(this.jTextField42.getText()).doubleValue()));
  }

  private void RepopulateEquilibriumElementsList()
  {
    DefaultListModel lmEqElementsListModel = new DefaultListModel();
    this.jList5.setModel(lmEqElementsListModel);
    lmEqElementsListModel.setSize(this.iNumEqElements);
    int j = 0;
    for (int i = 0; i < iMaxNumElements; i++)
      if (this.iMasterElementsListState[i] == 1) {
        lmEqElementsListModel.set(j, this.szMasterElementsList[i]);
        j++;
      }
  }

  private void RepopulateNonEquilibriumElementsList()
  {
    DefaultListModel lmNEqElementsListModel = new DefaultListModel();
    this.jList6.setModel(lmNEqElementsListModel);
    lmNEqElementsListModel.setSize(this.iNumNEqElements);
    int j = 0;
    for (int i = 0; i < iMaxNumElements; i++)
      if (this.iMasterElementsListState[i] == 2) {
        lmNEqElementsListModel.set(j, this.szMasterElementsList[i]);
        j++;
      }
  }

  private void jButton6ActionPerformed(ActionEvent evt)
  {
    Object[] objSelectedElements = this.jList5.getSelectedValues();

    for (int i = 0; i < objSelectedElements.length; i++) {
      for (int j = 0; j < iMaxNumElements; j++) {
        if (objSelectedElements[i].equals(this.szMasterElementsList[j])) {
          this.iMasterElementsListState[j] = 0;
        }
      }
    }
    this.iNumEqElements -= objSelectedElements.length;

    RepopulateEquilibriumElementsList();

    checkRadiationEnabledStatus();
  }

  private void jButton7ActionPerformed(ActionEvent evt)
  {
    Object[] objSelectedElements = this.jList4.getSelectedValues();

    int iAlreadySelected = 0; int iDecrementNumNEqElements = 0;
    for (int i = 0; i < objSelectedElements.length; i++) {
      for (int j = 0; j < iMaxNumElements; j++) {
        if (objSelectedElements[i].equals(this.szMasterElementsList[j])) {
          if (this.iMasterElementsListState[j] != 1) {
            if (this.iMasterElementsListState[j] == 2)
              iDecrementNumNEqElements++;
            this.iMasterElementsListState[j] = 1;
          }
          else {
            iAlreadySelected++;
          }
        }
      }
    }

    this.iNumEqElements += objSelectedElements.length;
    this.iNumEqElements -= iAlreadySelected;

    this.iNumNEqElements -= iDecrementNumNEqElements;

    RepopulateEquilibriumElementsList();
    RepopulateNonEquilibriumElementsList();

    checkOutputEnabledStatus();
    checkRadiationEnabledStatus();
    checkSolverEnabledStatus();
  }

  private void jButton8ActionPerformed(ActionEvent evt)
  {
    Object[] objSelectedElements = this.jList4.getSelectedValues();

    int iAlreadySelected = 0; int iDecrementNumEqElements = 0;
    for (int i = 0; i < objSelectedElements.length; i++) {
      for (int j = 0; j < iMaxNumElements; j++) {
        if (objSelectedElements[i].equals(this.szMasterElementsList[j])) {
          if (this.iMasterElementsListState[j] != 2) {
            if (this.iMasterElementsListState[j] == 1)
              iDecrementNumEqElements++;
            this.iMasterElementsListState[j] = 2;
          }
          else {
            iAlreadySelected++;
          }
        }
      }
    }

    this.iNumEqElements -= iDecrementNumEqElements;

    this.iNumNEqElements += objSelectedElements.length;
    this.iNumNEqElements -= iAlreadySelected;

    RepopulateEquilibriumElementsList();
    RepopulateNonEquilibriumElementsList();

    checkOutputEnabledStatus();
    checkRadiationEnabledStatus();
    checkSolverEnabledStatus();
  }

  private void jButton9ActionPerformed(ActionEvent evt)
  {
    Object[] objSelectedElements = this.jList6.getSelectedValues();

    for (int i = 0; i < objSelectedElements.length; i++) {
      for (int j = 0; j < iMaxNumElements; j++) {
        if (objSelectedElements[i].equals(this.szMasterElementsList[j])) {
          this.iMasterElementsListState[j] = 0;
        }
      }
    }
    this.iNumNEqElements -= objSelectedElements.length;

    RepopulateNonEquilibriumElementsList();

    checkOutputEnabledStatus();
    checkRadiationEnabledStatus();
    checkSolverEnabledStatus();
  }

  private void jCheckBox1ActionPerformed(ActionEvent evt) {
    checkOutputEnabledStatus();
    checkRadiationEnabledStatus();
    checkSolverEnabledStatus();
  }

  private void jCheckBox6ActionPerformed(ActionEvent evt) {
    checkBoundaryConditionsEnabledStatus();
    checkParameterSpaceEnabledStatus();
    checkHeatingEnabledStatus();
    checkGridEnabledStatus();
  }

  private void jCheckBox14ActionPerformed(ActionEvent evt) {
    checkGeometricalPropertiesEnabledStatus();
    checkGravityEnabledStatus();
  }

  private void jTextField18ActionPerformed(ActionEvent evt)
  {
  }

  private void jButton1ActionPerformed(ActionEvent evt)
  {
    if ((checkforEmptyHeatingPanelTextFields()) || (this.iNumHeatingEvents == iMaxNumHeatingEvents)) {
      return;
    }
    this.iNumHeatingEvents += 1;

    for (int i = this.iNumHeatingEvents - 1; i > this.iCurrentHeatingEvent; i--) {
      this.HeatingEvent[i].fVHR = this.HeatingEvent[(i - 1)].fVHR;
      this.HeatingEvent[i].fSL = this.HeatingEvent[(i - 1)].fSL;
      this.HeatingEvent[i].fSS = this.HeatingEvent[(i - 1)].fSS;
      this.HeatingEvent[i].fOT = this.HeatingEvent[(i - 1)].fOT;
      this.HeatingEvent[i].fTD = this.HeatingEvent[(i - 1)].fTD;
      this.HeatingEvent[i].fTSRP = this.HeatingEvent[(i - 1)].fTSRP;
      this.HeatingEvent[i].fTSDP = this.HeatingEvent[(i - 1)].fTSDP;
    }

    this.iCurrentHeatingEvent += 1;
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fVHR = Double.valueOf(this.jTextField22.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSL = Double.valueOf(this.jTextField23.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSS = Double.valueOf(this.jTextField24.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fOT = Double.valueOf(this.jTextField20.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTD = Double.valueOf(this.jTextField2.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSRP = Double.valueOf(this.jTextField25.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSDP = Double.valueOf(this.jTextField26.getText()).doubleValue();

    checkHeatingEnabledStatus();
  }

  private void jButton2ActionPerformed(ActionEvent evt)
  {
    for (int i = this.iCurrentHeatingEvent; i < this.iNumHeatingEvents; i++) {
      this.HeatingEvent[(i - 1)].fVHR = this.HeatingEvent[i].fVHR;
      this.HeatingEvent[(i - 1)].fSL = this.HeatingEvent[i].fSL;
      this.HeatingEvent[(i - 1)].fSS = this.HeatingEvent[i].fSS;
      this.HeatingEvent[(i - 1)].fOT = this.HeatingEvent[i].fOT;
      this.HeatingEvent[(i - 1)].fTD = this.HeatingEvent[i].fTD;
      this.HeatingEvent[(i - 1)].fTSRP = this.HeatingEvent[i].fTSRP;
      this.HeatingEvent[(i - 1)].fTSDP = this.HeatingEvent[i].fTSDP;
    }

    this.iNumHeatingEvents -= 1;
    if (this.iNumHeatingEvents < 0) {
      this.iNumHeatingEvents = 0;
    }

    if (this.iCurrentHeatingEvent > this.iNumHeatingEvents) {
      this.iCurrentHeatingEvent = this.iNumHeatingEvents;
    }
    checkHeatingEnabledStatus();
  }

  private void jButton4ActionPerformed(ActionEvent evt)
  {
    this.iCurrentHeatingEvent -= 1;
    if (this.iCurrentHeatingEvent < 1) {
      if (this.iNumHeatingEvents > 0)
        this.iCurrentHeatingEvent = 1;
      else
        this.iCurrentHeatingEvent = 0;
    }
    checkHeatingEnabledStatus();
  }

  private void jButton3ActionPerformed(ActionEvent evt)
  {
    this.iCurrentHeatingEvent += 1;
    if (this.iCurrentHeatingEvent > this.iNumHeatingEvents) {
      this.iCurrentHeatingEvent = this.iNumHeatingEvents;
    }
    checkHeatingEnabledStatus();
  }

  private void jButton5ActionPerformed(ActionEvent evt)
  {
    if (checkforEmptyHeatingPanelTextFields()) {
      return;
    }
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fVHR = Double.valueOf(this.jTextField22.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSL = Double.valueOf(this.jTextField23.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fSS = Double.valueOf(this.jTextField24.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fOT = Double.valueOf(this.jTextField20.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTD = Double.valueOf(this.jTextField2.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSRP = Double.valueOf(this.jTextField25.getText()).doubleValue();
    this.HeatingEvent[(this.iCurrentHeatingEvent - 1)].fTSDP = Double.valueOf(this.jTextField26.getText()).doubleValue();

    checkHeatingEnabledStatus();
  }

  private void jComboBox4ActionPerformed(ActionEvent evt)
  {
  }

  private void jTextField28ActionPerformed(ActionEvent evt)
  {
  }

  private void jCheckBox19ActionPerformed(ActionEvent evt) {
    checkSolverEnabledStatus();
  }

  private void jTextField33ActionPerformed(ActionEvent evt)
  {
  }

  private void jTextField35ActionPerformed(ActionEvent evt) {
    updateGridLabels();
  }

  private void jTextField1ActionPerformed(ActionEvent evt) {
    updateGridLabels();
  }

  private void jCheckBox20ActionPerformed(ActionEvent evt) {
    checkGridEnabledStatus();
  }

  private void jButton10ActionPerformed(ActionEvent evt) {
    openFileDialogBox();
  }

  private void openFileDialogBox() {
    this.jFileChooser1.setFileSelectionMode(2);
    this.jFileChooser1.showOpenDialog(null);

    File jFile1 = this.jFileChooser1.getSelectedFile();
    this.jTextField44.setText(jFile1.getPath());
    try
    {
      restoreConfigSettings();
    } catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  private void restoreConfigSettings() throws IOException
  {
    BufferedReader inputStream = null;
    try
    {
      inputStream = new BufferedReader(new FileReader(this.jTextField44.getText()));

      if (inputStream != null)
      {
        String szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox7.setSelected(true);
        else {
          this.jCheckBox7.setSelected(false);
        }
        this.jTextField54.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        this.jTextField1.setText(inputStream.readLine());
        this.jTextField3.setText(inputStream.readLine());
        this.jTextField45.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox6.setSelected(true);
        else {
          this.jCheckBox6.setSelected(false);
        }
        this.jTextField5.setText(inputStream.readLine());
        this.jTextField6.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        this.jTextField11.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true")) {
          this.jCheckBox22.setSelected(true);
          szBuffer = inputStream.readLine();
          this.jTextField12.setText("Infinity");
        } else {
          this.jCheckBox22.setSelected(false);
          this.jTextField12.setText(inputStream.readLine());
        }
        this.jTextField13.setText(inputStream.readLine());
        this.jTextField14.setText(inputStream.readLine());
        this.jTextField15.setText(inputStream.readLine());
        this.jTextField4.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        this.jTextField10.setText(inputStream.readLine());
        this.jTextField16.setText(inputStream.readLine());
        this.jTextField17.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox2.setSelected(true);
        else {
          this.jCheckBox2.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox3.setSelected(true);
        else {
          this.jCheckBox3.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox4.setSelected(true);
        else {
          this.jCheckBox4.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox5.setSelected(true);
        else {
          this.jCheckBox5.setSelected(false);
        }
        this.jTextField19.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox23.setSelected(true);
        else {
          this.jCheckBox23.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        this.iCurrentHeatingEvent = Integer.valueOf(szBuffer).intValue();
        szBuffer = inputStream.readLine();
        this.iNumHeatingEvents = Integer.valueOf(szBuffer).intValue();
        for (int i = 0; i < this.iNumHeatingEvents; i++) {
          szBuffer = inputStream.readLine();
          this.HeatingEvent[i].fVHR = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fSL = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fSS = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fOT = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fTD = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fTSRP = Double.valueOf(inputStream.readLine()).doubleValue();
          this.HeatingEvent[i].fTSDP = Double.valueOf(inputStream.readLine()).doubleValue();
          szBuffer = inputStream.readLine();
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox8.setSelected(true);
        else {
          this.jCheckBox8.setSelected(false);
        }
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox1.setSelected(true);
        else {
          this.jCheckBox1.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        this.iNumEqElements = Integer.valueOf(szBuffer).intValue();
        szBuffer = inputStream.readLine();
        this.iNumNEqElements = Integer.valueOf(szBuffer).intValue();
        for (int i = 0; i < iMaxNumElements; i++) {
          szBuffer = inputStream.readLine();
          this.iMasterElementsListState[i] = Integer.valueOf(szBuffer).intValue();
        }
        szBuffer = inputStream.readLine();
        this.jComboBox1.setSelectedIndex(Integer.valueOf(szBuffer).intValue());
        szBuffer = inputStream.readLine();
        this.jComboBox3.setSelectedIndex(Integer.valueOf(szBuffer).intValue());
        szBuffer = inputStream.readLine();
        this.jComboBox4.setSelectedIndex(Integer.valueOf(szBuffer).intValue());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox18.setSelected(true);
        else {
          this.jCheckBox18.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox21.setSelected(true);
        else {
          this.jCheckBox21.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox11.setSelected(true);
        else {
          this.jCheckBox11.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        RepopulateEquilibriumElementsList();
        RepopulateNonEquilibriumElementsList();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox12.setSelected(true);
        else {
          this.jCheckBox12.setSelected(false);
        }
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox14.setSelected(true);
        else {
          this.jCheckBox14.setSelected(false);
        }
        this.jTextField18.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        this.jTextField21.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox17.setSelected(true);
        else {
          this.jCheckBox17.setSelected(false);
        }
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        this.jTextField27.setText(inputStream.readLine());
        this.jTextField47.setText(inputStream.readLine());
        this.jTextField50.setText(inputStream.readLine());
        this.jTextField28.setText(inputStream.readLine());
        this.jTextField49.setText(inputStream.readLine());
        this.jTextField51.setText(inputStream.readLine());
        this.jTextField52.setText(inputStream.readLine());
        this.jTextField29.setText(inputStream.readLine());
        this.jTextField30.setText(inputStream.readLine());
        this.jTextField31.setText(inputStream.readLine());
        this.jTextField46.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox19.setSelected(true);
        else {
          this.jCheckBox19.setSelected(false);
        }
        this.jTextField32.setText(inputStream.readLine());
        this.jTextField33.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();

        szBuffer = inputStream.readLine();
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox20.setSelected(true);
        else {
          this.jCheckBox20.setSelected(false);
        }
        this.jTextField35.setText(inputStream.readLine());
        this.jTextField42.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox9.setSelected(true);
        else {
          this.jCheckBox9.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox10.setSelected(true);
        else {
          this.jCheckBox10.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox13.setSelected(true);
        else {
          this.jCheckBox13.setSelected(false);
        }
        this.jTextField43.setText(inputStream.readLine());
        this.jTextField38.setText(inputStream.readLine());
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox15.setSelected(true);
        else {
          this.jCheckBox15.setSelected(false);
        }
        szBuffer = inputStream.readLine();
        if (szBuffer.equals("true"))
          this.jCheckBox16.setSelected(true);
        else {
          this.jCheckBox16.setSelected(false);
        }
        szBuffer = inputStream.readLine();
      }
    }
    finally {
      if (inputStream != null) {
        inputStream.close();
      }
    }
    checkEnabledStatus();
  }

  private void jButton12ActionPerformed(ActionEvent evt) {
    String szOS = System.getProperty("os.name");
    try
    {
      GenerateInitialConditionsSourceCode();
      if (szOS.contains("Windows"))
        GenerateWindowsICLaunchFile();
      else
        GenerateUnixVariantICLaunchFile();
    }
    catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
    try
    {
      if (szOS.contains("Windows")) {
        Runtime.getRuntime().exec("cmd /c start Initial_Conditions.bat");
      } else {
        Runtime.getRuntime().exec("chmod +x Initial_Conditions.bat");
        Runtime.getRuntime().exec("./Initial_Conditions.bat");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void GenerateInitialConditionsSourceCode() throws IOException {
    PrintWriter outputStream = null;
    double fLog_10H0 = 0.0D; double fLog_10H1 = 0.0D; double fdLog_10H = 0.0D; double fHintervals = 0.0D;
    try
    {
      outputStream = new PrintWriter(new FileWriter("Initial_Conditions/config/initial_conditions.cfg"));

      if (outputStream != null) {
        outputStream.println(this.jTextField10.getText());
        outputStream.println("");
        outputStream.println(String.valueOf(Double.valueOf(this.jTextField1.getText())));
        outputStream.println(this.jTextField45.getText());
        outputStream.println(this.jTextField3.getText());
        outputStream.println("");
        outputStream.println(this.jTextField5.getText());
        outputStream.println("");
        outputStream.println(this.jTextField6.getText());
        outputStream.println("");
        outputStream.println(this.jTextField11.getText());
        if ((this.jCheckBox22.isSelected()) || (this.jTextField12.getText().equals("Infinity")))
          outputStream.println("1E308");
        else {
          outputStream.println(this.jTextField12.getText());
        }
        if (this.jCheckBox6.isSelected()) {
          fLog_10H0 = 0.0D;
          fLog_10H1 = 0.0D;
          fdLog_10H = 1.0D;
          fHintervals = 1.0D;
        } else {
          fLog_10H0 = Double.valueOf(this.jTextField13.getText()).doubleValue();
          fLog_10H1 = Double.valueOf(this.jTextField14.getText()).doubleValue();
          fdLog_10H = Double.valueOf(this.jTextField15.getText()).doubleValue();
          fHintervals = Double.valueOf(this.jTextField4.getText()).doubleValue();
        }
        outputStream.println(String.valueOf(fLog_10H0));
        outputStream.println(String.valueOf(fLog_10H1));
        outputStream.println(String.valueOf(fdLog_10H));
        outputStream.println(String.valueOf(fHintervals));
        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Radiation_Model/config/elements_eq.cfg"));

      if (outputStream != null) {
        outputStream.println("ranges");
        int i = this.jComboBox1.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmEmissivityFilesListModel.get(i)));
        i = this.jComboBox3.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmAbundanceFilesListModel.get(i)));
        i = this.jComboBox4.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmRateFilesListModel.get(i)));
        outputStream.println(String.valueOf(this.iNumEqElements));
        for (i = 0; i < iMaxNumElements; i++) {
          if (this.iMasterElementsListState[i] == 1) {
            outputStream.println(this.szMasterAtomicSymbolsList[i]);
            outputStream.println(String.valueOf(i + 1));
          }
        }
        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Initial_Conditions/source/config.h"));

      if (outputStream != null) {
        outputStream.println("// ****");
        outputStream.println("// *");
        outputStream.println("// * #defines for configuring the hydrostatic model");
        outputStream.println("// *");
        outputStream.println("// * (c) Dr. Stephen J. Bradshaw");
        outputStream.println("// *");
        outputStream.println("// * Source code generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("// *");
        outputStream.println("// ****");
        outputStream.println("");
        outputStream.println("// **** Output ****");
        outputStream.println("// **** End of Output ****");
        outputStream.println("");
        outputStream.println("// **** Physics ****");
        if (this.jCheckBox6.isSelected()) {
          outputStream.println("#define ISOTHERMAL");
        }
        outputStream.println("// Heating //");
        outputStream.println("// End of Heating //");
        outputStream.println("// Radiation //");
        if ((!this.jCheckBox6.isSelected()) && ((this.jCheckBox1.isSelected()) || (this.jList5.getModel().getSize() == 0))) {
          outputStream.println("#define USE_POWER_LAW_RADIATIVE_LOSSES");
        }
        if (this.jCheckBox18.isSelected()) {
          outputStream.println("#define DENSITY_DEPENDENT_RATES");
        }
        if (this.jCheckBox11.isSelected()) {
          outputStream.println("#define OPTICALLY_THICK_RADIATION");
        }
        outputStream.println("// End of Radiation //");
        outputStream.println("// Thermal Conduction //");
        outputStream.println("// End of Thermal Conduction //");
        outputStream.println("// Gravity //");
        if (this.jCheckBox14.isSelected()) {
          outputStream.println("#define USE_TABULATED_GRAVITY");
          outputStream.println("#define TABULATED_GRAVITY_FILE \"" + this.jTextField18.getText() + "\"");
        }
        outputStream.println("// End of Gravity //");
        outputStream.println("// **** End of Physics ****");
        outputStream.println("");
        outputStream.println("// **** Solver ****");
        outputStream.println("#define EPSILON 0.01");
        outputStream.println("// **** End of Solver ****");
        outputStream.println("");
        outputStream.println("// **** Grid ****");
        if (!this.jCheckBox20.isSelected()) {
          outputStream.println("#define ADAPT");
        }
        outputStream.println("#define MIN_CELLS " + String.valueOf(Integer.valueOf(this.jTextField35.getText())));
        outputStream.println("#define MAX_CELLS 30000");
        outputStream.println("#define MAX_REFINEMENT_LEVEL " + this.jTextField42.getText());
        outputStream.println("#define MIN_DS 1e0");
        outputStream.println("#define MAX_VARIATION 1.10");
        outputStream.println("// **** End of Grid ****");
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Radiation_Model/source/config.h"));

      if (outputStream != null) {
        outputStream.println("// ****");
        outputStream.println("// *");
        outputStream.println("// * #defines for configuring the radiation model");
        outputStream.println("// *");
        outputStream.println("// * (c) Dr. Stephen J. Bradshaw");
        outputStream.println("// *");
        outputStream.println("// * Source code generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("// *");
        outputStream.println("// ****");
        outputStream.println("");
        outputStream.println("// **** Physics ****");
        outputStream.println("// Radiation //");
        if (this.jCheckBox18.isSelected()) {
          outputStream.println("#define DENSITY_DEPENDENT_RATES");
        }
        outputStream.println("// End of Radiation //");
        outputStream.println("// Collisions //");
        outputStream.println("#define MINIMUM_COLLISIONAL_COUPLING_TIME_SCALE " + this.jTextField21.getText());
        outputStream.println("// End of Collisions //");
        outputStream.println("// **** End of Physics ****");
        outputStream.println("");
        outputStream.println("// **** Solver ****");
        outputStream.println("#define MAX_OPTICALLY_THIN_DENSITY " + String.valueOf(Math.log10(Double.valueOf(this.jTextField50.getText()).doubleValue())));
        outputStream.println("#define SAFETY_ATOMIC " + this.jTextField28.getText());
        outputStream.println("#define CUTOFF_ION_FRACTION " + this.jTextField49.getText());
        outputStream.println("#define EPSILON_D " + this.jTextField51.getText());

        double t0 = Math.abs(Math.pow(10.0D, -Double.valueOf(this.jTextField52.getText()).doubleValue()) - 1.0D);
        double t1 = Math.pow(10.0D, Double.valueOf(this.jTextField52.getText()).doubleValue()) - 1.0D;
        double t2 = (t0 + t1) / 2.0D;

        outputStream.println("#define EPSILON_R " + String.valueOf(t2));
        outputStream.println("// **** End of Solver ****");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void GenerateWindowsICLaunchFile() throws IOException
  {
    PrintWriter outputStream = null;
    try
    {
      outputStream = new PrintWriter(new FileWriter("Initial_Conditions.bat"));

      if (outputStream != null) {
        outputStream.println("# Script file generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("cd Initial_Conditions/build_scripts");
        outputStream.println("call build_initial_conditions.bat");
        outputStream.println("cd ../..");
        outputStream.println("Initial_Conditions.exe");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void GenerateUnixVariantICLaunchFile() throws IOException
  {
    PrintWriter outputStream = null;
    try
    {
      outputStream = new PrintWriter(new FileWriter("Initial_Conditions.bat"));

      if (outputStream != null) {
        outputStream.println("# Script file generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("cd Initial_Conditions/build_scripts");
        outputStream.println("./build_initial_conditions.bat");
        outputStream.println("cd ../..");
        outputStream.println("./Initial_Conditions.exe > Initial_Conditions.txt");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void jButton13ActionPerformed(ActionEvent evt)
  {
    String szOS = System.getProperty("os.name");
    try
    {
      GenerateHYDRADSourceCode();
      if (szOS.contains("Windows"))
        GenerateWindowsHLaunchFile();
      else
        GenerateUnixVariantHLaunchFile();
    }
    catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
    try
    {
      if (szOS.contains("Windows")) {
        Runtime.getRuntime().exec("cmd /c start HYDRAD.bat");
      } else {
        Runtime.getRuntime().exec("chmod +x HYDRAD.bat");
        Runtime.getRuntime().exec("./HYDRAD.bat");
      }
    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private void GenerateHYDRADSourceCode() throws IOException {
    BufferedReader inputStream = null;
    PrintWriter outputStream = null;

    double fDuration = 0.0D; double fH = 0.0D;
    try
    {
      outputStream = new PrintWriter(new FileWriter("HYDRAD/config/HYDRAD.cfg"));

      if (outputStream != null) {
        if (this.jCheckBox7.isSelected())
          outputStream.println(this.jTextField10.getText());
        else {
          outputStream.println(this.jTextField54.getText());
        }
        if (this.jCheckBox14.isSelected())
          outputStream.println(this.jTextField18.getText());
        else {
          outputStream.println(this.jTextField10.getText() + ".gravity");
        }
        outputStream.println(this.jTextField16.getText());
        outputStream.println(this.jTextField17.getText());
        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Heating_Model/config/heating_model.cfg"));

      if (outputStream != null)
      {
        for (int i = 0; i < this.iNumHeatingEvents; i++) {
          if (this.HeatingEvent[i].fOT + this.HeatingEvent[i].fTD > fDuration) {
            fDuration = this.HeatingEvent[i].fOT + this.HeatingEvent[i].fTD;
          }
        }
        outputStream.println(String.valueOf(fDuration));
        outputStream.println("");
        try
        {
          inputStream = new BufferedReader(new FileReader(this.jTextField10.getText() + ".sol"));

          if (inputStream != null) {
            String szBuffer = inputStream.readLine();
            fH = Double.valueOf(szBuffer).doubleValue();
          }
        }
        finally
        {
        }

        if ((this.jCheckBox23.isEnabled()) && (this.jCheckBox23.isSelected()))
        {
          if (this.jCheckBox22.isSelected())
          {
            outputStream.println(this.jTextField11.getText() + " " + "1E308" + " " + String.valueOf(fH));
          }
          else outputStream.println(this.jTextField11.getText() + " " + this.jTextField12.getText() + " " + String.valueOf(fH));
        }
        else {
          outputStream.println("0.0 0.0 0.0");
        }
        outputStream.println("");
        outputStream.println(String.valueOf(this.iNumHeatingEvents));
        outputStream.println("");
        for (i = 0; i < this.iNumHeatingEvents; i++) {
          double t0 = this.HeatingEvent[i].fOT;
          double t1 = this.HeatingEvent[i].fOT + this.HeatingEvent[i].fTSRP;
          double t3 = this.HeatingEvent[i].fOT + this.HeatingEvent[i].fTD;
          double t2 = t3 - this.HeatingEvent[i].fTSDP;
          outputStream.println(String.valueOf(this.HeatingEvent[i].fSL) + " " + String.valueOf(this.HeatingEvent[i].fSS) + " " + String.valueOf(this.HeatingEvent[i].fVHR) + " " + t0 + " " + t1 + " " + t2 + " " + t3);
        }

        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Radiation_Model/config/elements_eq.cfg"));

      if (outputStream != null) {
        outputStream.println("ranges");
        int i = this.jComboBox1.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmEmissivityFilesListModel.get(i)));
        i = this.jComboBox3.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmAbundanceFilesListModel.get(i)));
        i = this.jComboBox4.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmRateFilesListModel.get(i)));
        outputStream.println(String.valueOf(this.iNumEqElements));
        for (i = 0; i < iMaxNumElements; i++) {
          if (this.iMasterElementsListState[i] == 1) {
            outputStream.println(this.szMasterAtomicSymbolsList[i]);
            outputStream.println(String.valueOf(i + 1));
          }
        }
        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Radiation_Model/config/elements_neq.cfg"));

      if (outputStream != null) {
        outputStream.println("ranges");
        int i = this.jComboBox1.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmEmissivityFilesListModel.get(i)));
        i = this.jComboBox3.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmAbundanceFilesListModel.get(i)));
        i = this.jComboBox4.getSelectedIndex();
        outputStream.println(String.valueOf(this.lmRateFilesListModel.get(i)));
        outputStream.println(String.valueOf(this.iNumNEqElements));
        for (i = 0; i < iMaxNumElements; i++) {
          if (this.iMasterElementsListState[i] == 2) {
            outputStream.println(this.szMasterAtomicSymbolsList[i]);
            outputStream.println(String.valueOf(i + 1));
          }
        }
        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("HYDRAD/source/config.h"));

      if (outputStream != null) {
        outputStream.println("// ****");
        outputStream.println("// *");
        outputStream.println("// * #defines for configuring the hydrodynamic model");
        outputStream.println("// *");
        outputStream.println("// * (c) Dr. Stephen J. Bradshaw");
        outputStream.println("// *");
        outputStream.println("// * Source code generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("// *");
        outputStream.println("// ****");
        outputStream.println("");
        outputStream.println("// **** Output ****");
        if (this.jCheckBox2.isSelected()) {
          outputStream.println("#define WRITE_FILE_PHYSICAL");
        }
        if ((this.jCheckBox3.isEnabled()) && (this.jCheckBox3.isSelected())) {
          outputStream.println("#define WRITE_FILE_ION_POPULATIONS");
        }
        if (this.jCheckBox4.isSelected()) {
          outputStream.println("#define WRITE_FILE_SCALES");
        }
        if (this.jCheckBox5.isSelected()) {
          outputStream.println("#define WRITE_FILE_TERMS");
        }
        outputStream.println("#define OUTPUT_EVERY_N_TIME_STEPS " + this.jTextField19.getText());
        outputStream.println("// **** End of Output ****");
        outputStream.println("");
        outputStream.println("// **** Physics ****");
        outputStream.println("// Heating //");
        if (this.jCheckBox8.isSelected())
          outputStream.println("#define HEATED_SPECIES 0");
        else {
          outputStream.println("#define HEATED_SPECIES 1");
        }
        outputStream.println("// End of Heating //");
        outputStream.println("// Radiation //");
        if ((this.jTextField28.isEnabled()) && (!this.jCheckBox21.isSelected())) {
          outputStream.println("#define NON_EQUILIBRIUM_RADIATION");
        }
        else {
          if ((this.jCheckBox1.isSelected()) || (this.jList5.getModel().getSize() == 0)) {
            outputStream.println("#define USE_POWER_LAW_RADIATIVE_LOSSES");
          }
          if ((this.jCheckBox21.isSelected()) && (this.jList6.getModel().getSize() > 0)) {
            outputStream.println("#define DECOUPLE_IONISATION_STATE_SOLVER");
            outputStream.println("#define NON_EQUILIBRIUM_RADIATION");
          }
        }
        if (this.jCheckBox18.isSelected()) {
          outputStream.println("#define DENSITY_DEPENDENT_RATES");
        }
        if (this.jCheckBox11.isSelected()) {
          outputStream.println("#define OPTICALLY_THICK_RADIATION");
        }
        outputStream.println("// End of Radiation //");
        outputStream.println("// Thermal Conduction //");
        if (this.jCheckBox12.isSelected()) {
          outputStream.println("#define USE_KINETIC_MODEL");
        }
        outputStream.println("// End of Thermal Conduction //");
        outputStream.println("// Gravity //");
        if (this.jCheckBox14.isSelected()) {
          outputStream.println("#define USE_TABULATED_GRAVITY");
          outputStream.println("#define TABULATED_GRAVITY_FILE \"" + this.jTextField18.getText() + "\"");
        }
        outputStream.println("// End of Gravity //");
        outputStream.println("// Collisions //");
        outputStream.println("#define MINIMUM_COLLISIONAL_COUPLING_TIME_SCALE " + this.jTextField21.getText());
        if (this.jCheckBox17.isSelected()) {
          outputStream.println("#define FORCE_SINGLE_FLUID");
        }
        outputStream.println("// End of Collisions //");
        outputStream.println("// **** End of Physics ****");
        outputStream.println("");
        outputStream.println("// **** Solver ****");
        outputStream.println("#define SAFETY_RADIATION " + this.jTextField27.getText());
        outputStream.println("#define SAFETY_CONDUCTION " + this.jTextField29.getText());
        outputStream.println("#define SAFETY_ADVECTION " + this.jTextField30.getText());
        outputStream.println("#define SAFETY_VISCOSITY " + this.jTextField31.getText());
        outputStream.println("#define TIME_STEP_INCREASE_LIMIT " + String.valueOf(1.0D + Double.valueOf(this.jTextField46.getText()).doubleValue() / 100.0D));
        if (this.jCheckBox19.isSelected()) {
          outputStream.println("#define NUMERICAL_VISCOSITY ");
          outputStream.println("#define RELATIVE_VISCOUS_TIME_SCALE " + this.jTextField32.getText());
        }
        outputStream.println("#define MINIMUM_RADIATION_TEMPERATURE " + this.jLabel103.getText());
        outputStream.println("#define ZERO_OVER_TEMPERATURE_INTERVAL " + this.jTextField47.getText());
        outputStream.println("#define MINIMUM_TEMPERATURE " + this.jTextField33.getText());
        outputStream.println("// **** End of Solver ****");
        outputStream.println("");
        outputStream.println("// **** Grid ****");
        if (!this.jCheckBox20.isSelected()) {
          outputStream.println("#define ADAPT");
          outputStream.println("#define MAX_REFINEMENT_LEVEL " + this.jTextField42.getText());
          if (this.jCheckBox9.isSelected()) {
            outputStream.println("#define REFINE_ON_DENSITY");
          }
          if (this.jCheckBox10.isSelected()) {
            outputStream.println("#define REFINE_ON_ELECTRON_ENERGY");
          }
          if (this.jCheckBox13.isSelected()) {
            outputStream.println("#define REFINE_ON_HYDROGEN_ENERGY");
          }
          outputStream.println("#define MIN_FRAC_DIFF " + String.valueOf(Double.valueOf(this.jTextField43.getText()).doubleValue() / 100.0D));
          outputStream.println("#define MAX_FRAC_DIFF " + String.valueOf(Double.valueOf(this.jTextField38.getText()).doubleValue() / 100.0D));
          if (this.jCheckBox15.isSelected()) {
            outputStream.println("#define LINEAR_RESTRICTION");
          }
          if (this.jCheckBox16.isSelected())
            outputStream.println("#define ENFORCE_CONSERVATION");
        }
        else {
          outputStream.println("#define MAX_REFINEMENT_LEVEL " + this.jTextField42.getText());
        }
        outputStream.println("// **** End of Grid ****");
      }
    } finally {
      if (outputStream != null) {
        outputStream.close();
      }
    }

    try
    {
      outputStream = new PrintWriter(new FileWriter("Radiation_Model/source/config.h"));

      if (outputStream != null) {
        outputStream.println("// ****");
        outputStream.println("// *");
        outputStream.println("// * #defines for configuring the radiation model");
        outputStream.println("// *");
        outputStream.println("// * (c) Dr. Stephen J. Bradshaw");
        outputStream.println("// *");
        outputStream.println("// * Source code generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("// *");
        outputStream.println("// ****");
        outputStream.println("");
        outputStream.println("// **** Physics ****");
        outputStream.println("// Radiation //");
        if (this.jCheckBox18.isSelected()) {
          outputStream.println("#define DENSITY_DEPENDENT_RATES");
        }
        outputStream.println("// End of Radiation //");
        outputStream.println("// Collisions //");
        outputStream.println("#define MINIMUM_COLLISIONAL_COUPLING_TIME_SCALE " + this.jTextField21.getText());
        outputStream.println("// End of Collisions //");
        outputStream.println("// **** End of Physics ****");
        outputStream.println("");
        outputStream.println("// **** Solver ****");
        outputStream.println("#define MAX_OPTICALLY_THIN_DENSITY " + String.valueOf(Math.log10(Double.valueOf(this.jTextField50.getText()).doubleValue())));
        outputStream.println("#define SAFETY_ATOMIC " + this.jTextField28.getText());
        outputStream.println("#define CUTOFF_ION_FRACTION " + this.jTextField49.getText());
        outputStream.println("#define EPSILON_D " + this.jTextField51.getText());

        double t0 = Math.abs(Math.pow(10.0D, -Double.valueOf(this.jTextField52.getText()).doubleValue()) - 1.0D);
        double t1 = Math.pow(10.0D, Double.valueOf(this.jTextField52.getText()).doubleValue()) - 1.0D;
        double t2 = (t0 + t1) / 2.0D;

        outputStream.println("#define EPSILON_R " + String.valueOf(t2));
        outputStream.println("// **** End of Solver ****");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void GenerateWindowsHLaunchFile() throws IOException
  {
    PrintWriter outputStream = null;
    try
    {
      outputStream = new PrintWriter(new FileWriter("HYDRAD.bat"));

      if (outputStream != null) {
        outputStream.println("# Script file generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("cd HYDRAD/build_scripts");
        outputStream.println("call build_HYDRAD.bat");
        outputStream.println("cd ../..");
        outputStream.println("HYDRAD.exe");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void GenerateUnixVariantHLaunchFile() throws IOException
  {
    PrintWriter outputStream = null;
    try
    {
      outputStream = new PrintWriter(new FileWriter("HYDRAD.bat"));

      if (outputStream != null) {
        outputStream.println("# Script file generated by HYDRAD_GUI on " + CDateUtils.now());
        outputStream.println("cd HYDRAD/build_scripts");
        outputStream.println("./build_HYDRAD.bat");
        outputStream.println("cd ../..");
        outputStream.println("./HYDRAD.exe > HYDRAD.txt");
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void jButton11ActionPerformed(ActionEvent evt)
  {
    saveFileDialogBox();
  }

  private void saveFileDialogBox() {
    this.jFileChooser1.setFileSelectionMode(2);
    this.jFileChooser1.showSaveDialog(null);

    File jFile1 = this.jFileChooser1.getSelectedFile();
    this.jTextField44.setText(jFile1.getPath());
    try
    {
      saveConfigSettings();
    } catch (IOException ex) {
      Logger.getLogger(HYDRAD_GUI.class.getName()).log(Level.SEVERE, null, ex);
    }
  }

  private void saveConfigSettings() throws IOException
  {
    PrintWriter outputStream = null;
    try
    {
      outputStream = new PrintWriter(new FileWriter(this.jTextField44.getText()));

      if (outputStream != null)
      {
        outputStream.println("**** Files ****");
        if (this.jCheckBox7.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField54.getText());
        outputStream.println("**** End of Files ****");

        outputStream.println("**** Initial Conditions ****");

        outputStream.println("// Geometrical Properties //");
        outputStream.println(this.jTextField1.getText());
        outputStream.println(this.jTextField3.getText());
        outputStream.println(this.jTextField45.getText());
        outputStream.println("// End of Geometrical Properties //");

        outputStream.println("// Boundary Conditions //");
        if (this.jCheckBox6.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField5.getText());
        outputStream.println(this.jTextField6.getText());
        outputStream.println("// End of Boundary Conditions //");

        outputStream.println("// Parameter Space //");
        outputStream.println(this.jTextField11.getText());
        if (this.jCheckBox22.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField12.getText());
        outputStream.println(this.jTextField13.getText());
        outputStream.println(this.jTextField14.getText());
        outputStream.println(this.jTextField15.getText());
        outputStream.println(this.jTextField4.getText());
        outputStream.println("// End of Parameter Space //");

        outputStream.println("**** End of Initial Conditions ****");

        outputStream.println("**** Output ****");
        outputStream.println(this.jTextField10.getText());
        outputStream.println(this.jTextField16.getText());
        outputStream.println(this.jTextField17.getText());
        if (this.jCheckBox2.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox3.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox4.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox5.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField19.getText());
        outputStream.println("**** End of Output ****");

        outputStream.println("**** Physics ****");

        outputStream.println("// Heating //");
        if (this.jCheckBox23.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(Integer.toString(this.iCurrentHeatingEvent));
        outputStream.println(Integer.toString(this.iNumHeatingEvents));
        for (int i = 0; i < this.iNumHeatingEvents; i++) {
          outputStream.println("Event " + (i + 1));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fVHR));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fSL));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fSS));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fOT));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fTD));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fTSRP));
          outputStream.println(String.valueOf(this.HeatingEvent[i].fTSDP));
          outputStream.println("End of event " + (i + 1));
        }
        if (this.jCheckBox8.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println("// End of Heating //");

        outputStream.println("// Radiation //");
        if (this.jCheckBox1.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(Integer.toString(this.iNumEqElements));
        outputStream.println(Integer.toString(this.iNumNEqElements));
        for (int i = 0; i < iMaxNumElements; i++) {
          outputStream.println(Integer.toString(this.iMasterElementsListState[i]));
        }
        outputStream.println(Integer.toString(this.jComboBox1.getSelectedIndex()));
        outputStream.println(Integer.toString(this.jComboBox3.getSelectedIndex()));
        outputStream.println(Integer.toString(this.jComboBox4.getSelectedIndex()));
        if (this.jCheckBox18.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox21.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox11.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println("// End of Radiation //");

        outputStream.println("// Thermal Conduction //");
        if (this.jCheckBox12.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println("// End of Thermal Conduction //");

        outputStream.println("// Gravity //");
        if (this.jCheckBox14.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField18.getText());
        outputStream.println("// End of Gravity //");

        outputStream.println("// Collisions //");
        outputStream.println(this.jTextField21.getText());
        if (this.jCheckBox17.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println("// End of Collisions //");

        outputStream.println("**** End of Physics ****");

        outputStream.println("**** Solver ****");
        outputStream.println(this.jTextField27.getText());
        outputStream.println(this.jTextField47.getText());
        outputStream.println(this.jTextField50.getText());
        outputStream.println(this.jTextField28.getText());
        outputStream.println(this.jTextField49.getText());
        outputStream.println(this.jTextField51.getText());
        outputStream.println(this.jTextField52.getText());
        outputStream.println(this.jTextField29.getText());
        outputStream.println(this.jTextField30.getText());
        outputStream.println(this.jTextField31.getText());
        outputStream.println(this.jTextField46.getText());
        if (this.jCheckBox19.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField32.getText());
        outputStream.println(this.jTextField33.getText());
        outputStream.println("**** End of Solver ****");

        outputStream.println("**** Grid ****");
        if (this.jCheckBox20.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField35.getText());
        outputStream.println(this.jTextField42.getText());
        if (this.jCheckBox9.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox10.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox13.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println(this.jTextField43.getText());
        outputStream.println(this.jTextField38.getText());
        if (this.jCheckBox15.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        if (this.jCheckBox16.isSelected())
          outputStream.println("true");
        else {
          outputStream.println("false");
        }
        outputStream.println("**** End of Grid ****");

        outputStream.println("");
        outputStream.println("Configuration file generated by HYDRAD_GUI on " + CDateUtils.now());
      }
    } finally {
      if (outputStream != null)
        outputStream.close();
    }
  }

  private void jTextField35FocusLost(FocusEvent evt)
  {
    updateGridLabels();
  }

  private void jTextField1FocusLost(FocusEvent evt) {
    updateGridLabels();
  }

  private void jTextField15ActionPerformed(ActionEvent evt)
  {
  }

  private void jTextField29ActionPerformed(ActionEvent evt)
  {
  }

  private void jCheckBox22ActionPerformed(ActionEvent evt) {
    checkUniformHeatingStatus();
  }

  private void jTextField12ActionPerformed(ActionEvent evt) {
    checkUniformHeatingStatus();
  }

  private void jTextField12FocusLost(FocusEvent evt) {
    checkUniformHeatingStatus();
  }

  private void jTextField5FocusLost(FocusEvent evt) {
    updateSolverLabels();
  }

  private void jCheckBox7ActionPerformed(ActionEvent evt) {
    checkFilesEnabledStatus();
  }

  private void jTextField54FocusGained(FocusEvent evt) {
  }

  private void jTextField42FocusLost(FocusEvent evt) {
    updateGridLabels();
  }

  private void jCheckBox13ActionPerformed(ActionEvent evt)
  {
  }

  private void jCheckBox11ActionPerformed(ActionEvent evt) {
    checkRadiationEnabledStatus();
  }

  private void jCheckBox18ActionPerformed(ActionEvent evt)
  {
  }

  private void jCheckBox21ActionPerformed(ActionEvent evt) {
    checkOutputEnabledStatus();
    checkSolverEnabledStatus();
  }

  private void checkUniformHeatingStatus() {
    if (this.jCheckBox22.isSelected())
      this.jTextField12.setText("Infinity");
  }

  public static void main(String[] args)
  {
    EventQueue.invokeLater(new Runnable() {
      public void run() {
        new HYDRAD_GUI().setVisible(true);
      }
    });
  }
}