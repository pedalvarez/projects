package com.peal.RestWebServiceServer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.URLDecoder;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import com.sun.net.httpserver.Headers;
import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import com.sun.net.httpserver.HttpServer;

public class RestWebServiceServerHttp 
{
	private int port;
	private HttpServer server;

	public void Start(int port) 
	{
		try 
		{
			this.port = port;
			server = HttpServer.create(new InetSocketAddress(port), 0);
			System.out.println("started:" + port);
			server.createContext("/", new Handlers.RootHandler());
			server.createContext("/Header", new Handlers.HeaderHandler());
			server.createContext("/Get", new Handlers.GetHandler());
			server.createContext("/Post", new Handlers.PostHandler());
			server.setExecutor(null);
			server.start();
		} 
		catch (IOException e)
		{
			e.printStackTrace();
		}
	}

	public void Stop() 
	{
		server.stop(0);
		System.out.println("stopped");
	}
}
