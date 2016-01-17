
package edu.nps.moves.websocket;

import javax.servlet.http.HttpServletRequest;
import org.eclipse.jetty.websocket.WebSocketHandler;
import org.eclipse.jetty.websocket.WebSocket;
import java.util.*;
import java.util.concurrent.*;
/**
 *
 * @author mcgredo
 */
public class DisWebSocketHandler extends WebSocketHandler
{
    public Set participants = new CopyOnWriteArraySet();
    /*
     * Performa a connection operation
     * 
     */
 @Override
 public WebSocket doWebSocketConnect(HttpServletRequest request,
                                    String protocol)
 {
     System.out.println("in doWebSocketConnect");
    return new DisWebSocket(participants);
 }
    
}
