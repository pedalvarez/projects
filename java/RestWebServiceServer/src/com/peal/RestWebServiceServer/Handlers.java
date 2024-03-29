package com.peal.RestWebServiceServer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
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

public class Handlers 
{
	public static class RootHandler implements HttpHandler 
	{
		@Override
		public void handle(HttpExchange he) throws IOException 
		{
			String response = "<h1>Server is up and running</h1>" + "<h1>Port: " + Main.port + "</h1>";
			he.sendResponseHeaders(200, response.length());
			OutputStream os = he.getResponseBody();
			os.write(response.getBytes());
			os.close();
		}
	}

	public static class HeaderHandler implements HttpHandler 
	{
		@Override
		public void handle(HttpExchange he) throws IOException 
		{
			Headers headers = he.getRequestHeaders();
			Set<Map.Entry<String, List<String>>> entries = headers.entrySet();
			String response = "";
			for (Map.Entry<String, List<String>> entry : entries)
				response += entry.toString() + "\n";
			he.sendResponseHeaders(200, response.length());
			OutputStream os = he.getResponseBody();
			os.write(response.toString().getBytes());
			os.close();
		}
	}

	public static class GetHandler implements HttpHandler 
	{
		@Override
		public void handle(HttpExchange he) throws IOException 
		{		
			Map<String, Object> parameters = new HashMap<String, Object>();
			parseQuery(he.getRequestURI().getRawQuery(), parameters);		
			String response = "";
			for (String key : parameters.keySet())
			{
				response += key + " = " + parameters.get(key) + "\n";
			}
			he.sendResponseHeaders(200, response.length());
			OutputStream os = he.getResponseBody();
			os.write(response.toString().getBytes());
			os.close();
		}

	}

	public static class PostHandler implements HttpHandler {

		@Override
		public void handle(HttpExchange he) throws IOException 
		{
			Map<String, Object> parameters = new HashMap<String, Object>();
			InputStreamReader isr = new InputStreamReader(he.getRequestBody(), "utf-8");
			BufferedReader br = new BufferedReader(isr);
			parseQuery(br.readLine(), parameters);	
			String response = "";
			for (String key : parameters.keySet())
			{
				response += key + " = " + parameters.get(key) + "\n";
			}
			he.sendResponseHeaders(200, response.length());
			OutputStream os = he.getResponseBody();
			os.write(response.toString().getBytes());
			os.close();
		}
	}

	public static void parseQuery(String query, Map<String, Object> parameters) throws UnsupportedEncodingException 
	{
		if (query != null) 
		{
			String pairs[] = query.split("[&]");
			for (String pair : pairs) 
			{
				String param[] = pair.split("[=]");
				String key = null;
				String value = null;
				if (param.length > 0)
				{
					key = URLDecoder.decode(param[0], System.getProperty("file.encoding"));
				}
				if (param.length > 1) 
				{
					value = URLDecoder.decode(param[1], System.getProperty("file.encoding"));
				}
				if (parameters.containsKey(key)) 
				{
					Object obj = parameters.get(key);
					if (obj instanceof List<?>) 
					{
						List<String> values = (List<String>) obj;
						values.add(value);
					} 
					else if (obj instanceof String) 
					{
						List<String> values = new ArrayList<String>();
						values.add((String) obj);
						values.add(value);
						parameters.put(key, values);
					}
				} 
				else 
				{
					parameters.put(key, value);
				}
			}
		}
	}
}