//------------------------------------------------------------------------------
// <copyright company="Microsoft Corporation">
//      Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------
using System;
using System.Collections.Generic;
namespace SQLConfigurator
{
	/// <summary>
	/// Provide a default implementation for the storage of DataConnection Dialog UI configuration.
	/// </summary>
	public class DataConnectionConfiguration : IDataConnectionConfiguration
	{
		private string connectionString = null;
        private string servertype = "SQLSERVER";
        private string connectiontype = "OLE DB";
		
		// Available data sources:
		private IDictionary<string, DataSource> dataSources;

		// Available data providers: 
		private IDictionary<string, DataProvider> dataProviders;

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="path">Configuration file path.</param>
		public DataConnectionConfiguration(string connectstring, string serverType, string connectionType)
		{
            connectionString = connectstring;
            servertype = serverType;
            connectiontype = connectionType;
		}

		public void LoadConfiguration(DataConnectionDialog dialog)
		{
            if (connectiontype == "OLE DB")
            {
                dialog.DataSources.Add(DataSource.SqlDataSource);
                //dialog.DataSources.Add(DataSource.SqlFileDataSource); // PEAL no OLEDB
                dialog.DataSources.Add(DataSource.OracleDataSource);
                //dialog.DataSources.Add(DataSource.AccessDataSource);  // PEAL no OLEDB
            }
            else
            {
                dialog.DataSources.Add(DataSource.OdbcDataSource);                
            }

            if (connectiontype == "OLE DB")
            {
                //dialog.UnspecifiedDataSource.Providers.Add(DataProvider.SqlDataProvider);  // PEAL no OLEDB
                dialog.UnspecifiedDataSource.Providers.Add(DataProvider.OracleDataProvider);
                dialog.UnspecifiedDataSource.Providers.Add(DataProvider.OleDBDataProvider);
                dialog.UnspecifiedDataSource.Providers.Add(DataProvider.OracleOleDBDataProvider);
            }
            else
            {
                dialog.UnspecifiedDataSource.Providers.Add(DataProvider.OdbcDataProvider);
                dialog.DataSources.Add(dialog.UnspecifiedDataSource);
            }

			this.dataSources = new Dictionary<string, DataSource>();

            if (connectiontype == "OLE DB")
            {
                this.dataSources.Add(DataSource.SqlDataSource.Name, DataSource.SqlDataSource);
                //this.dataSources.Add(DataSource.SqlFileDataSource.Name, DataSource.SqlFileDataSource); // PEAL no OLEDB
                this.dataSources.Add(DataSource.OracleDataSource.Name, DataSource.OracleDataSource);
                //this.dataSources.Add(DataSource.AccessDataSource.Name, DataSource.AccessDataSource); // PEAL no OLEDB
            }
            else
            {
                this.dataSources.Add(DataSource.OdbcDataSource.Name, DataSource.OdbcDataSource);
                this.dataSources.Add(dialog.UnspecifiedDataSource.DisplayName, dialog.UnspecifiedDataSource);
            }

			this.dataProviders = new Dictionary<string, DataProvider>();

            if (connectiontype == "OLE DB")
            {
                //this.dataProviders.Add(DataProvider.SqlDataProvider.Name, DataProvider.SqlDataProvider); // PEAL no OLEDB
                this.dataProviders.Add(DataProvider.OleDBDataProvider.Name, DataProvider.OleDBDataProvider);
                this.dataProviders.Add(DataProvider.OracleDataProvider.Name, DataProvider.OracleDataProvider);
                this.dataProviders.Add(DataProvider.OracleOleDBDataProvider.Name, DataProvider.OracleOleDBDataProvider);
            }
            else
            {
                this.dataProviders.Add(DataProvider.OdbcDataProvider.Name, DataProvider.OdbcDataProvider);
            }
			
			DataSource ds = null;
			string dsName = this.GetSelectedSource();
			if (!String.IsNullOrEmpty(dsName) && this.dataSources.TryGetValue(dsName, out ds))
			{
				dialog.SelectedDataSource = ds;
			}

			DataProvider dp = null;
			string dpName = this.GetSelectedProvider();
			if (!String.IsNullOrEmpty(dpName) && this.dataProviders.TryGetValue(dpName, out dp))
			{
				dialog.SelectedDataProvider = dp;
			}
		}

		public void SaveConfiguration(DataConnectionDialog dcd)
		{
		}

		public string GetSelectedSource()
		{
			try
			{                
                if (connectionString.ToUpper().IndexOf("DSN", 0) >= 0)
                {
                    return "OdbcDsn";
                }

                if (connectionString.ToUpper().IndexOf("PROVIDER", 0) >= 0)
                {
                    if (connectionString.ToUpper().IndexOf("MSDAORA", 0) > 0)
                        return "Oracle";


                    if (connectionString.ToUpper().IndexOf("ORAOLEDB.ORACLE", 0) > 0)
                        return "Oracle";                           
                }

                if (servertype == "ORACLE")
                    return "Oracle";

                if (connectionString.ToUpper().IndexOf("ATTACHDBFILENAME", 0) >= 0)
                    return "MicrosoftSqlServerFile";

                return "MicrosoftSqlServer";
			}
			catch
			{
				return null;
			}
		}

		public string GetSelectedProvider()
		{
			try
			{
                
                if (connectionString.ToUpper().IndexOf("PROVIDER", 0) >= 0)
                {
                    if (connectionString.ToUpper().IndexOf("SQLOLEDB", 0) > 0)
                        return "System.Data.OleDb";
                    else
                    {
                        if (connectionString.IndexOf("MSDAORA", 0) > 0)
                            return "System.Data.OracleClient";

                        if (connectionString.ToUpper().IndexOf("ORAOLEDB.ORACLE", 0) > 0)
                            return "System.Data.OracleOleDb";  
                    }                
                }
                if (connectionString.ToUpper().IndexOf("DSN", 0) >= 0)
                {
                    return "System.Data.Odbc";
                }

                if (servertype == "SQLSERVER")
                    return "System.Data.SqlClient";     
                
			}
			catch
			{				
			}

			return null;
		}

		public void SaveSelectedSource(string source)
		{
		}

		public void SaveSelectedProvider(string provider)
		{
		}
	}
}
