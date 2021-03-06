/**
 * Pr&aacute;ctricas de Sistemas Inform&aacute;ticos II
 * VisaCancelacionJMSBean.java
 */

package ssii2.visa;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import javax.ejb.EJBException;
import javax.ejb.MessageDriven;
import javax.ejb.MessageDrivenContext;
import javax.ejb.ActivationConfigProperty;
import javax.jms.MessageListener;
import javax.jms.Message;
import javax.jms.TextMessage;
import javax.jms.JMSException;
import javax.annotation.Resource;
import java.util.logging.Logger;

/**
 * @author jaime
 */
@MessageDriven(mappedName = "jms/VisaPagosQueue")
public class VisaCancelacionJMSBean extends DBTester implements MessageListener {
  static final Logger logger = Logger.getLogger("VisaCancelacionJMSBean");
  @Resource
  private MessageDrivenContext mdc;

  private static final String UPDATE_CANCELA_QRY = "update pago set codRespuesta=999 where pago.idAutorizacion=?";
  private static final String UPDATE_RECTIFICAR_QRY = "update tarjeta set saldo =? where tarjeta.numeroTarjeta=?";
  private static final String SELECT_PAGO_QRY = "select numeroTarjeta, importe from pago where idAutorizacion=?";
  private static final String SELECT_SALDO_QRY ="select saldo from tarjeta where numeroTarjeta=?"; 
   // TODO : Definir UPDATE sobre la tabla pagos para poner
   // codRespuesta a 999 dado un código de autorización


  public VisaCancelacionJMSBean() {
  }

  // TODO : Método onMessage de ejemplo
  // Modificarlo para ejecutar el UPDATE definido más arriba,
  // asignando el idAutorizacion a lo recibido por el mensaje
  // Para ello conecte a la BD, prepareStatement() y ejecute correctamente
  // la actualización
  public void onMessage(Message inMessage) {
	Connection con = null;
	TextMessage msg = null;
	PreparedStatement pstmt = null;
	ResultSet rs = null;
	String numTarj="";
	double importe=0;
	double saldo=0;
      try {
	con = getConnection();	
          if (inMessage instanceof TextMessage) {
              msg = (TextMessage) inMessage;
              logger.info("MESSAGE BEAN: Message received: " + msg.getText());
	String newSaldo = UPDATE_CANCELA_QRY;
        pstmt = con.prepareStatement(newSaldo);
        pstmt.setInt(1,Integer.parseInt(msg.getText()));
        pstmt.executeUpdate();

	String selectPago=SELECT_PAGO_QRY;
 	
	pstmt = con.prepareStatement(selectPago);
        pstmt.setInt(1,Integer.parseInt(msg.getText()));
        rs=pstmt.executeQuery();

	if(rs.next()){
		 numTarj = rs.getString("numeroTarjeta");
		 importe = rs.getDouble("importe");
	logger.warning("NT:"+numTarj+" y importe:"+Double.toString(importe));
	}else{
		throw new EJBException("Error cancelar");
	}	

	String selectSaldo=SELECT_SALDO_QRY;
 	
	pstmt = con.prepareStatement(selectSaldo);
        pstmt.setString(1,numTarj);
        rs=pstmt.executeQuery();

	if(rs.next()){
		
		 saldo = rs.getDouble("saldo");
	logger.warning("saldo:"+Double.toString(saldo));
	}else{
		throw new EJBException("Error cancelar");
	}	
	saldo=saldo+importe;

	newSaldo = UPDATE_RECTIFICAR_QRY;
        
        pstmt = con.prepareStatement(newSaldo);
        pstmt.setDouble(1,saldo);
	pstmt.setString(2,numTarj);
        pstmt.executeUpdate();

          } else {
              logger.warning(
                      "Message of wrong type: "
                      + inMessage.getClass().getName());
          }


	
	
      } catch (JMSException e) {
          e.printStackTrace();
          mdc.setRollbackOnly();
      } catch (Throwable te) {
          te.printStackTrace();
      }
  }


}
