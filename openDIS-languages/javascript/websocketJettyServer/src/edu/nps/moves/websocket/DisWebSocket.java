
package edu.nps.moves.websocket;

import org.eclipse.jetty.websocket.WebSocket;

import java.util.concurrent.*;
import java.io.*;
import java.net.*;
import java.util.*;

/**
 * Represents one web socket connection between the server and the web page.
 * Includes a list of the other connections so we can relay out messages to
 * them as they arrive to us.
 * 
 * @author mcgredo
 */
public class DisWebSocket implements WebSocket.OnTextMessage 
{
       Set<DisWebSocket> participants;

        private Connection connection;
        
        DisWebSocket(Set<DisWebSocket> participants)
        {
            this.participants = participants;
        }
        
        @Override
        public void onOpen(Connection connection) 
        {
            System.out.println("onOpen called in DisWebSocket");
            // a client (Browser) 
            // 1) Store the opened connection
            this.connection = connection;

            // 2) Add new websocket in the global list of DisWebSocket 
            participants.add(this);
            try
            {
                connection.sendMessage("Hello from server");
            }
            catch(Exception e)
            {
                System.out.println(e);
            }
        }
 
        /** Received a message from the web browser on the other side of the
         * websocket connection.
         * 
         * @param data 
         */
        @Override
        public void onMessage(String data) 
        {
            System.out.println("Got message of " + data);
            
            // Send any received DIS messages back out to the other clients
            /*
            try 
            {
                
                for (DisWebSocket webSocket : participants) 
                {
                    if(webSocket != this) // Don't resend to the sender
                    {
                        webSocket.connection.sendMessage(data);
                    }
                }
                 
                
                // Also send on the local network--careful about infinite
                // loop feedback...
                
            } 
            catch (IOException x) 
            {
                // Error was detected, close the DisWebSocket client side
                this.connection.disconnect();
            }
            */
 
        }
 
        @Override
        public void onClose(int closeCode, String message) 
        {
            System.out.println("onClose()");
            // Remove DisWebSocket in the global list of DisWebSocket
            // instance.
            participants.remove(this);
        }
    }
