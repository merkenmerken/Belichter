/*
    AVR8 Burn-O-Mat
 
    Copyright (C) 2007  Torsten Brischalle
 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
 
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
 
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/
 */

package avr8_burn_o_mat;

import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Vector;
import javax.swing.ButtonGroup;
import javax.swing.JLabel;
import javax.swing.JRadioButton;

public class JPanelBrownOutDetection
extends javax.swing.JPanel
implements FusesObserver, ActionListener {
    
    private Vector <JRadioButton> m_radioButtonList;
    private ButtonGroup m_buttonGroup;
    
    private BrownOutDetection m_brownOutDetection = null;
    
    private JLabel m_labelNotSupported;
    
    private FusesEditor m_fusesEditor;
    
    /** Creates new form JPanelBrownOutDetection */
    public JPanelBrownOutDetection(FusesEditor fusesEditor) {
        initComponents();
        
        m_fusesEditor = fusesEditor;
        m_fusesEditor.getFusesObservable().addObserver(this);
        
        m_buttonGroup = new ButtonGroup();
        m_radioButtonList = new Vector <JRadioButton>();

        m_labelNotSupported = new JLabel("not supported for selected MCU");
        m_labelNotSupported.setBounds(20, 20, 400, 25);
    }

    public void fusesChanged() {
        fuseState2Selection();
    }
    
    public void fuseState2Selection() {
        
        if (m_brownOutDetection == null)
            return;
        
        int idx = m_brownOutDetection.getSettingIndexFromFusesState();
        if (idx == -1) {
            m_buttonGroup.clearSelection();
        } else {
            m_radioButtonList.elementAt(idx).setSelected(true);
        }
    }
    
    public void actionPerformed(ActionEvent e) {
        
        assert m_brownOutDetection != null;
        
        int i, idx = -1;
        
        for (i = 0; i < m_radioButtonList.size(); i++) {
            if (m_radioButtonList.elementAt(i) == e.getSource()) {
                idx = i;
                break;
            }
        }
        
        assert idx != -1;
        
        m_brownOutDetection.applyFusesFromSetting(idx);
        
        m_fusesEditor.getFusesObservable().fusesChanged(this);
    }
    
    public void setAVR(AVR avr) {
        
        removeRadioButtons();
        
        m_brownOutDetection = avr.getBrownOutDetection();
        if (m_brownOutDetection == null) {
            add(m_labelNotSupported);
            setPreferredSize(new Dimension(500, 100));
            return;
        }
        else
            remove(m_labelNotSupported);
        
        createRadioButtons();
        fuseState2Selection();
    }
    
    private void removeRadioButtons() {
        
         for (JRadioButton r : m_radioButtonList) {
             r.removeActionListener(this);
             m_buttonGroup.remove(r);
             remove(r);
        }
        
        m_radioButtonList.clear();
    }
    
    private void createRadioButtons() {
        
        final int LINE_HEIGHT = 25;
        final int LINE_SPACE = 10;
        
        assert m_brownOutDetection != null;
        
        int idx = 0;
        
        for (BrownOutDetection.Setting s : m_brownOutDetection.m_settingList) {
            JRadioButton r = new JRadioButton(s.getName());
            
            add(r);
            r.setBounds(20, (idx + 1) * LINE_SPACE + idx * LINE_HEIGHT, 400, LINE_HEIGHT);
            r.addActionListener(this);
            
            m_buttonGroup.add(r);
            m_radioButtonList.add(r);
            
            idx++;
        }
        
        m_buttonGroup.clearSelection();
        
        setPreferredSize(new Dimension(500, (idx + 1) * LINE_SPACE + idx * LINE_HEIGHT));
    }
    
    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        setPreferredSize(new java.awt.Dimension(100, 100));
        setLayout(null);
    }// </editor-fold>//GEN-END:initComponents
    
    
    // Variables declaration - do not modify//GEN-BEGIN:variables
    // End of variables declaration//GEN-END:variables
    
}