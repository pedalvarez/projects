package com.peal.RestWebServiceServer;
public class Main {
	public static int port = 8080;
	public static void main(String[] args)
	{
		RestWebServiceServerHttp httpServer = new RestWebServiceServerHttp();
		httpServer.Start(port);
	}
}