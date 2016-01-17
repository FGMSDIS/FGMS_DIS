/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.nps.moves.websocket;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.DefaultHandler;

/**
 *
 * @author mcgredo
 */
public class WebsocketServer
{
    public static void main(String args[])
    {
        try
        {
            Server server = new Server(8081);
            
            DisWebSocketHandler disWebSocketHandler = new DisWebSocketHandler();
            disWebSocketHandler.setHandler(new DefaultHandler());
            server.setHandler(disWebSocketHandler);
            
            server.start();
            server.join();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }
        
    }
    
}
